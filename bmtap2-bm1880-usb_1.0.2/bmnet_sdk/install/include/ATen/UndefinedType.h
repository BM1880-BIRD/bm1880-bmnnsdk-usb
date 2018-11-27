#pragma once

#include "ATen/Type.h"
#include "ATen/Context.h"
#include "ATen/CheckGenerator.h"

#ifdef _MSC_VER
#ifdef Type
#undef Type
#endif
#endif

namespace at {

struct UndefinedType final : public Type {
  explicit UndefinedType(Context* context);
  virtual ScalarType scalarType() const override;
  virtual Backend backend() const override;
  virtual bool is_cuda() const override;
  virtual bool is_sparse() const override;
  virtual bool is_distributed() const override;
  virtual Storage storage(bool resizable = false) const override;
  virtual Storage storage(size_t size, bool resizable = false) const override;
  virtual Storage storageFromBlob(void * data, int64_t size, const std::function<void(void*)> & deleter) const override;
  virtual Storage storageWithAllocator(int64_t size, Allocator* allocator) const override;
  virtual std::unique_ptr<Generator> generator() const override;
  virtual const char * toString() const override;
  virtual size_t elementSizeInBytes() const override;
  virtual Type & toBackend(Backend b) const override;
  virtual Type & toScalarType(ScalarType s) const override;
  virtual TypeID ID() const override;
  static const char * typeString();
  virtual Storage unsafeStorageFromTH(void * th_pointer, bool retain) const override;
  virtual Tensor unsafeTensorFromTH(void * th_pointer, bool retain) const override;

  virtual Tensor & s_copy_(Tensor & self, const Tensor & src, bool non_blocking) const override;
  virtual Tensor & _s_copy_from(const Tensor & self, Tensor & dst, bool non_blocking) const override;
};

} // namespace at
