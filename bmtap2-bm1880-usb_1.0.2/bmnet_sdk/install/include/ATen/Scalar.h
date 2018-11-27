#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdexcept>
#include <string>
#include <utility>

#include "ATen/core/ATenGeneral.h"
#include "ATen/core/ScalarType.h"
#include "ATen/TensorBase.h"
#include "ATen/core/Half.h"

namespace at {

struct Tensor;

class AT_API Scalar {
public:
  Scalar() : Scalar(int64_t(0)) {}

#define DEFINE_IMPLICIT_CTOR(type,name,member) \
  Scalar(type vv) \
  : tag(Tag::HAS_##member) { \
    v . member = convert<decltype(v.member),type>(vv); \
  }

  AT_FORALL_SCALAR_TYPES(DEFINE_IMPLICIT_CTOR)

#undef DEFINE_IMPLICIT_CTOR

  // return a new scalar that is guarenteed to be not backed by a tensor.
  Scalar local() const;

#define DEFINE_ACCESSOR(type,name,member) \
  type to##name () const { \
    if (Tag::HAS_t == tag) { \
      return local().to##name(); \
    } else if (Tag::HAS_d == tag) { \
      return checked_convert<type, double>(v.d, #type); \
    } else { \
      return checked_convert<type, int64_t>(v.i, #type); \
    } \
  }

  Tensor toTensor() const;

  AT_FORALL_SCALAR_TYPES(DEFINE_ACCESSOR)

  //also support scalar.to<int64_t>();
  template<typename T>
  T to();

#undef DEFINE_ACCESSOR
  bool isFloatingPoint() const {
    return Tag::HAS_d == tag;
  }
  bool isIntegral() const {
    return Tag::HAS_i == tag;
  }
  bool isBackedByTensor() const {
    return Tag::HAS_t == tag;
  }

  Scalar operator-() const;

private:
  enum class Tag { HAS_d, HAS_i, HAS_t };
  Tag tag;
  union {
    double d;
    int64_t i = 0;
  } v;
  detail::TensorBase t;
  friend struct Type;
};

// define the scalar.to<int64_t>() specializations
template<typename T>
inline T Scalar::to() {
  throw std::runtime_error("to() cast to unexpected type.");
}

#define DEFINE_TO(T,name,_) \
template<> \
inline T Scalar::to<T>() { \
  return to##name(); \
}
AT_FORALL_SCALAR_TYPES(DEFINE_TO)
#undef DEFINE_TO
}
