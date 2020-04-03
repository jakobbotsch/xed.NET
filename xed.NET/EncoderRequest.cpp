#include "pch.h"
#include "EncoderRequest.h"
#include "XedState.h"
#include "DecodedInstruction.h"
#include "Common.h"
#include "Error.h"

using namespace System;
using namespace XedNet;

EncoderRequest::EncoderRequest(XedState^ state)
{
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer();
    pin_ptr<xed_state_t> statePtr = state->_native.GetPointer();

    xed_encoder_request_zero_set_mode(ptr, statePtr);
    GC::KeepAlive(this);
}

EncoderRequest::EncoderRequest(DecodedInstruction^ decoded)
{
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer();

    *ptr = *decoded->_native.GetPointer();
    xed_encoder_request_init_from_decode(ptr);
    GC::KeepAlive(this);
}

#define G(type, name, getter)                                  \
type EncoderRequest::name::get()                               \
{                                                              \
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); \
    type ret = static_cast<type>(getter(ptr));                 \
    GC::KeepAlive(this);                                       \
    return ret;                                                \
}

#define M0V(name, fn)                                          \
void EncoderRequest::name()                                    \
{                                                              \
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); \
    fn(ptr);                                                   \
    GC::KeepAlive(this);                                       \
}

#define M1V(name, argT, argCastT, fn)                          \
void EncoderRequest::name(argT arg0)                           \
{                                                              \
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); \
    fn(ptr, static_cast<argCastT>(arg0));                      \
    GC::KeepAlive(this);                                       \
}

#define M2V(name, arg0T, arg0CastT, arg1T, arg1CastT, fn)      \
void EncoderRequest::name(arg0T arg0, arg1T arg1)              \
{                                                              \
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); \
    fn(ptr,                                                    \
       static_cast<arg0CastT>(arg0),                           \
       static_cast<arg1CastT>(arg1));                          \
    GC::KeepAlive(this);                                       \
}

G(InstClass, Class, xed_encoder_request_get_iclass)
void EncoderRequest::Class::set(InstClass value) { pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); xed_encoder_request_set_iclass(ptr, static_cast<xed_iclass_enum_t>(value)); }
M1V(SetEffectiveOperandWidth, int, int, xed_encoder_request_set_effective_operand_width)
M1V(SetEffectiveAddressSize, int, int, xed_encoder_request_set_effective_address_size)
M2V(SetReg, OperandName, xed_operand_enum_t, Register, xed_reg_enum_t, xed_encoder_request_set_reg)
M2V(SetOperandOrder, int, int, OperandName, xed_operand_enum_t, xed_encoder_request_set_operand_order)
OperandName EncoderRequest::GetOperandOrder(int index) { pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer(); return static_cast<OperandName>(xed_encoder_request_get_operand_order(ptr, static_cast<unsigned int>(index))); }
G(int, NumOperandOrderEntries, xed_encoder_request_operand_order_entries)
M0V(SetRelbr, xed_encoder_request_set_relbr)
M2V(SetBranchDisplacement, int, int, int, int, xed_encoder_request_set_branch_displacement)
M0V(SetPtr, xed_encoder_request_set_ptr)
M2V(SetUImm0, UInt64, UInt64, int, int, xed_encoder_request_set_uimm0)
M2V(SetUImm0Bits, UInt64, UInt64, int, int, xed_encoder_request_set_uimm0_bits)
M1V(SetUImm1, Byte, Byte, xed_encoder_request_set_uimm1)
M2V(SetSImm, int, int, int, int, xed_encoder_request_set_simm)
M2V(SetMemoryDisplacement, Int64, Int64, int, int, xed_encoder_request_set_memory_displacement)
M0V(SetAgen, xed_encoder_request_set_agen)
M0V(SetMem0, xed_encoder_request_set_mem0)
M0V(SetMem1, xed_encoder_request_set_mem1)
M1V(SetMemoryOperandLength, int, int, xed_encoder_request_set_memory_operand_length)
M1V(SetSeg0, Register, xed_reg_enum_t, xed_encoder_request_set_seg0)
M1V(SetSeg1, Register, xed_reg_enum_t, xed_encoder_request_set_seg1)
M1V(SetBase0, Register, xed_reg_enum_t, xed_encoder_request_set_base0)
M1V(SetBase1, Register, xed_reg_enum_t, xed_encoder_request_set_base1)
M1V(SetIndex, Register, xed_reg_enum_t, xed_encoder_request_set_index)
M1V(SetScale, int, int, xed_encoder_request_set_scale)
M0V(ClearOperandOrder, xed_encoder_request_zero_operand_order)


void EncoderRequest::Encode(Span<Byte> bytes, int% outLength)
{
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer();
    pin_ptr<Byte> pBytes = &MemoryMarshal::GetReference(bytes);
    pin_ptr<int> pOutLength = &outLength;

    xed_error_enum_t error = xed_encode(ptr, pBytes, static_cast<unsigned int>(bytes.Length),
                                        reinterpret_cast<unsigned int*>(pOutLength));

    XedException::Check(error);
    GC::KeepAlive(this);
}

array<Byte>^ EncoderRequest::Encode()
{
    pin_ptr<xed_encoder_request_t> ptr = _native.GetPointer();

    Byte bytes[15];
    unsigned int olen;
    xed_error_enum_t error = xed_encode(ptr, bytes, sizeof(bytes), &olen);

    GC::KeepAlive(this);
    XedException::Check(error);

    return Span<Byte>(bytes, static_cast<int>(olen)).ToArray();
}

XedError EncoderRequest::TryEncodeNop(Span<Byte> bytes)
{
    pin_ptr<Byte> pBytes = &MemoryMarshal::GetReference(bytes);
    xed_error_enum_t err = xed_encode_nop(pBytes, static_cast<unsigned int>(bytes.Length));

    return static_cast<XedError>(err);
}

void EncoderRequest::EncodeNop(Span<Byte> bytes)
{
    XedException::Check(TryEncodeNop(bytes));
}

array<Byte>^ EncoderRequest::EncodeNop(int length)
{
    if (length <= 0)
        throw gcnew ArgumentOutOfRangeException("length");

    array<Byte>^ bytes = gcnew array<Byte>(length);
    EncodeNop(bytes);
    return bytes;
}
