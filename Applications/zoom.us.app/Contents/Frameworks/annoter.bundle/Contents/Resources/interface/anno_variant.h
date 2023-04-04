/*****************************************************************************
*
* Copyright (C) 2022, Zoom Video Communications, Inc
*
* History:
*	Nov 2022 - Created - galen.yu@zoom.us
*	
*****************************************************************************/

#ifndef __ANNO_VARIANT_H__
#define __ANNO_VARIANT_H__

#include <stdint.h>

typedef enum AnnoVarType
{
  VarType_Unknow = -1,
  VarType_Void,
  VarType_Ptr,
  VarType_Bool,
  VarType_Int8,
  VarType_Int16,
  VarType_Int32,
  VarType_Int64,
  VarType_UInt8,
  VarType_UInt16,
  VarType_UInt32,
  VarType_UInt64,
  VarType_Float,
  VarType_Doulbe,
  VarType_Str,
  VarType_WStr,
}ANNOVARTYPE;

typedef class tagAnnoVariant
{
public:
  inline bool IsVoid()   { return VarType_Void == type_; }
  inline bool IsBool()   { return VarType_Bool == type_; }
  inline bool IsInt8()   { return VarType_Int8 == type_; }
  inline bool IsInt16()  { return VarType_Int16 == type_; }
  inline bool IsInt32()  { return VarType_Int32 == type_; }
  inline bool IsInt64()  { return VarType_Int64 == type_; }
  inline bool IsUInt8()  { return VarType_UInt8 == type_; }
  inline bool IsUInt16() { return VarType_UInt16 == type_; }
  inline bool IsUInt32() { return VarType_UInt32 == type_; }
  inline bool IsUInt64() { return VarType_UInt64 == type_; }
  inline bool IsFloat()  { return VarType_Float == type_; }
  inline bool IsDouble() { return VarType_Doulbe == type_; }
  inline bool IsPtr()    { return VarType_Ptr == type_; }
  inline bool IsStr()    { return VarType_Str == type_; }
  inline bool IsWStr()   { return VarType_WStr == type_; }

  void SetVoid() {
    type_ = AnnoVarType::VarType_Void;
  }
  void SetBool(bool Val) {
    type_ = AnnoVarType::VarType_Bool;
    bVal_ = Val;
  }
  void SetInt8(int8_t Val) {
    type_ = AnnoVarType::VarType_Int8;
    i8Val_ = Val;
  }
  void SetInt16(int16_t Val) {
    type_ = AnnoVarType::VarType_Int16;
    i16Val_ = Val;
  }
  void SetInt32(int32_t Val) {
    type_ = AnnoVarType::VarType_Int32;
    i32Val_ = Val;
  }
  void SetInt64(int64_t Val) {
    type_ = AnnoVarType::VarType_Int64;
    i64Val_ = Val;
  }
  void SetUInt8(uint8_t Val) {
    type_ = AnnoVarType::VarType_UInt8;
    u8Val_ = Val;
  }
  void SetUInt16(uint16_t Val) {
    type_ = AnnoVarType::VarType_UInt16;
    u16Val_ = Val;
  }
  void SetUInt32(uint32_t Val) {
    type_ = AnnoVarType::VarType_UInt32;
    u32Val_ = Val;
  }
  void SetUInt64(uint64_t Val) {
    type_ = AnnoVarType::VarType_UInt64;
    u64Val_ = Val;
  }
  void SetFloat(float Val) {
    type_ = AnnoVarType::VarType_Float;
    fltVal_ = Val;
  }
  void SetDouble(double Val) {
    type_ = AnnoVarType::VarType_Doulbe;
    dblVal_ = Val;
  }
  void SetPtr(void* Val) {
    type_ = AnnoVarType::VarType_Ptr;
    ptrVal_ = Val;
  }
  void SetStr(char* Val) {
    type_ = AnnoVarType::VarType_Str;
    strVal_ = Val;
  }
  void SetWStr(wchar_t* Val) {
    type_ = AnnoVarType::VarType_WStr;
    wstrVal_ = Val;
  }

  bool GetAsBool(bool& Val) {
    if (!IsBool())
      return false;

    Val = this->bVal_;
    return true;
  }
  bool GetAsInt8(int8_t& Val) {
    if (!IsInt8())
      return false;

    Val = this->i8Val_;
    return true;
  };
  bool GetAsInt16(int16_t& Val) {
    if (!IsInt16())
      return false;

    Val = this->i16Val_;
    return true;
  }
  bool GetAsInt32(int32_t& Val) {
    if (!IsInt32())
      return false;

    Val = this->i32Val_;
    return true;
  }
  bool GetAsInt64(int64_t& Val) {
    if (!IsInt64())
      return false;

    Val = this->i64Val_;
    return true;
  }
  bool GetAsUInt8(uint8_t& Val) {
    if (!IsUInt8())
      return false;

    Val = this->u8Val_;
    return true;
  }
  bool GetAsUInt16(uint16_t& Val) {
    if (!IsUInt16())
      return false;

    Val = this->u16Val_;
    return true;
  }
  bool GetAsUInt32(uint32_t& Val) {
    if (!IsUInt32())
      return false;

    Val = this->u32Val_;
    return true;
  }
  bool GetAsUInt64(uint64_t& Val) {
    if (!IsUInt64())
      return false;

    Val = this->u64Val_;
    return true;
  }
  bool GetAsFloat(float& Val) {
    if (!IsFloat())
      return false;

    Val = this->fltVal_;
    return true;
  }
  bool GetAsDouble(double& Val) {
    if (!IsDouble())
      return false;

    Val = this->dblVal_;
    return true;
  }
  bool GetAsPtr(void*& Val) {
    if (!IsPtr())
      return false;

    Val = this->ptrVal_;
    return true;
  }
  bool GetAsStr(char*& Val) {
    if (!IsStr())
      return false;

    Val = this->strVal_;
    return true;
  }
  bool GetAsPtr(wchar_t*& Val) {
    if (!IsWStr())
      return false;

    Val = this->wstrVal_;
    return true;
  }
private:
  AnnoVarType type_ = VarType_Unknow;
  union
  {
    void* ptrVal_;
    bool bVal_;
    int8_t i8Val_;
    int16_t i16Val_;
    int32_t i32Val_;
    int64_t i64Val_;
    uint8_t u8Val_;
    uint16_t u16Val_;
    uint32_t u32Val_;
    uint64_t u64Val_;
    float fltVal_;
    double dblVal_;
    char* strVal_;
    wchar_t* wstrVal_;
  };
}ANNOVARIANT;

#endif // __ANNO_VARIANT_H__
