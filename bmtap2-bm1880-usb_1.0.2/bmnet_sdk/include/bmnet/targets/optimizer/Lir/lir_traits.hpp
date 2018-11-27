

/* Copyright Bitmain Technologies Inc.
* Written by:
*   Mingkang Qin <mingkang.qin@bitmain.com>
* Created Time: 2018-05-11 14:27
*/
#ifndef _LIR_TRAITS_HPP_
#define _LIR_TRAITS_HPP_

namespace bmnet{

typedef unsigned long  size_t;
typedef unsigned char  u8;
typedef unsigned short  u16;
#define NOT_ALLOCATED 0xffffffff
constexpr int max_tensor_dimensions = 6;

#define BITS_OF_U8 8

class Named {
  std::string name_{};

public:
  explicit Named(std::string   &name): name_(name){}

  std::string & getName() {return name_;}

  bool hasNamed() {return !name_.empty();}

  void setName(std::string &name) { name_ = name; }

};

class Kinded{
public:
  enum class Kind{
#define DEF_INSTR(CLASS, NAME) CLASS##Kind,
#include <bmnet/targets/optimizer/Lir/InstructionsGen.def>
  };

  static const char * getKindName(Kind IK){
    const char * names[] = {
#define DEF_INSTR(CLASS, NAME) #NAME,
#include <bmnet/targets/optimizer/Lir/InstructionsGen.def>
    nullptr};

    return names[(int)IK];
  }

  explicit Kinded(Kind vk) : kind_(vk) {}
  Kind getKind() const { return kind_; }
private:
  Kind kind_;
};

}


#endif