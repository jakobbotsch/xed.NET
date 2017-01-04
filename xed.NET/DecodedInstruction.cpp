#include "stdafx.h"
#include "DecodedInstruction.h"
#include "XedState.h"
#include "Error.h"

using namespace System;
using namespace XedNet;

DecodedInstruction::DecodedInstruction(XedState^ state)
{
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();
    pin_ptr<xed_state_t> statePtr = state->_native.GetPointer();
    xed_decoded_inst_zero_set_mode(ptr, statePtr);
}

#define G(type, name, getter)                               \
type DecodedInstruction::name::get()                        \
{                                                           \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); \
    return static_cast<type>(getter(ptr));                  \
}

#define GB(name, getter)                                    \
bool DecodedInstruction::name::get()                        \
{                                                           \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); \
    return getter(ptr) != 0;                                \
}

#define M1(retT, name, argT, castT, getter)                         \
retT DecodedInstruction::name(argT arg)                             \
{                                                                   \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();         \
    return static_cast<retT>(getter(ptr, static_cast<castT>(arg))); \
}

#define M1B(name, argT, castT, getter)                      \
bool DecodedInstruction::name(argT arg)                     \
{                                                           \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); \
    return getter(ptr, static_cast<castT>(arg)) != 0;       \
}

GB(ConditionallyWritesRegisters, xed_decoded_inst_conditionally_writes_registers)
M1(Register, GetBaseReg, int, int, xed_decoded_inst_get_base_reg)
G(int, BranchDisplacement, xed_decoded_inst_get_branch_displacement)
G(int, BranchDisplacementWidth, xed_decoded_inst_get_branch_displacement_width)
G(int, BranchDisplacementWidthBits, xed_decoded_inst_get_branch_displacement_width_bits)
GB(ImmediateIsSigned, xed_decoded_inst_get_immediate_is_signed)
G(int, ImmediateWidth, xed_decoded_inst_get_immediate_width)
G(int, ImmediateWidthBits, xed_decoded_inst_get_immediate_width_bits)
M1(Register, GetIndexReg, int, int, xed_decoded_inst_get_index_reg)
M1(int, GetMemopAddressWidth, int, int, xed_decoded_inst_get_memop_address_width)
M1(Int64, GetMemoryDisplacement, int, int, xed_decoded_inst_get_memory_displacement)
M1(int, GetMemoryDisplacementWidth, int, int, xed_decoded_inst_get_memory_displacement_width)
M1(int, GetMemoryDisplacementWidthBits, int, int, xed_decoded_inst_get_memory_displacement_width_bits)
M1(int, GetMemoryOperandLength, int, int, xed_decoded_inst_get_memory_operand_length)
M1(Register, GetReg, Operand, xed_operand_enum_t, xed_decoded_inst_get_reg)
Object^ DecodedInstruction::RFlagsInfo::get() { return nullptr; }
M1(int, GetScale, int, int, xed_decoded_inst_get_scale)
G(Byte, SecondImmediate, xed_decoded_inst_get_second_immediate)
M1(Register, GetSegReg, int, int, xed_decoded_inst_get_seg_reg)
G(int, SignedImmediate, xed_decoded_inst_get_signed_immediate)
G(UInt64, UnsignedImmediate, xed_decoded_inst_get_unsigned_immediate)
GB(IsPrefetch, xed_decoded_inst_is_prefetch)
M1B(MemRead, int, int, xed_decoded_inst_mem_read)
M1B(MemWritten, int, int, xed_decoded_inst_mem_written)
M1B(MemWrittenOnly, int, int, xed_decoded_inst_mem_written_only)
G(int, NumMemOperands, xed_decoded_inst_number_of_memory_operands)
GB(UsesRFlags, xed_decoded_inst_uses_rflags)
M1B(HasAttribute, XedNet::Attribute, xed_attribute_enum_t, xed_decoded_inst_get_attribute)
M1(Byte, GetByte, int, int, xed_decoded_inst_get_byte)
G(InstCategory, Category, xed_decoded_inst_get_category)
G(InstExtension, Extension, xed_decoded_inst_get_extension)
G(InstClass, Class, xed_decoded_inst_get_iclass)
G(InstSet, IsaSet, xed_decoded_inst_get_isa_set)
GB(IsValid, xed_decoded_inst_valid)
Object^ DecodedInstruction::Instruction::get() { return nullptr; }
G(InstForm, Form, xed_decoded_inst_get_iform_enum)
G(UInt32, FormDispatch, xed_decoded_inst_get_iform_enum_dispatch)
G(Chip, InputChip, xed_decoded_inst_get_input_chip)
void DecodedInstruction::InputChip::set(Chip value) { pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); xed_decoded_inst_set_input_chip(ptr, static_cast<xed_chip_enum_t>(value)); }
G(int, MachineModeBits, xed_decoded_inst_get_machine_mode_bits)
G(int, OperandWidth, xed_decoded_inst_get_operand_width)
G(int, StackAddressModeBits, xed_decoded_inst_get_stack_address_mode_bits)
M1B(IsValidForChip, Chip, xed_chip_enum_t, xed_decoded_inst_valid_for_chip)
G(int, Length, xed_decoded_inst_get_length)
G(int, NumOperands, xed_decoded_inst_noperands)
M1(int, GetOperandElementSizeBits, int, int, xed_decoded_inst_operand_element_size_bits)
M1(OperandElementType, GetOperandElementType, int, int, xed_decoded_inst_operand_element_type)
M1(int, GetNumOperandElements, int, int, xed_decoded_inst_operand_elements)
M1(int, GetOperandLengthBits, int, int, xed_decoded_inst_operand_length_bits)
Object^ DecodedInstruction::OperandValues::get() { return nullptr; }
G(Byte, ModRM, xed_decoded_inst_get_modrm)
G(int, NumPrefixes, xed_decoded_inst_get_nprefixes)
GB(HasMpxPrefix, xed_decoded_inst_has_mpx_prefix)
GB(IsXAcquire, xed_decoded_inst_is_xacquire)
GB(IsXRelease, xed_decoded_inst_is_xrelease)
GB(IsMaskedVectorOperation, xed_decoded_inst_masked_vector_operation)
G(int, VectorLengthBits, xed_decoded_inst_vector_length_bits)

void DecodedInstruction::Decode(array<Byte>^ bytes)
{
    CheckNull(bytes);
    Decode(bytes, 0, bytes->Length);
}

void DecodedInstruction::Decode(array<Byte>^ bytes, int index, int count)
{
    CheckBounds(bytes, index, count);

    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();
    xed_decoded_inst_zero_keep_mode(ptr);

    pin_ptr<Byte> pBytes = count > 0 ? &bytes[index] : nullptr;
    xed_error_enum_t error = xed_decode(ptr, pBytes, count);

    if (error != XED_ERROR_NONE)
        throw gcnew XedException(static_cast<XedError>(error));
}

void DecodedInstruction::IldDecode(array<Byte>^ bytes)
{
    CheckNull(bytes);
    IldDecode(bytes, 0, bytes->Length);
}

void DecodedInstruction::IldDecode(array<Byte>^ bytes, int index, int count)
{
    CheckBounds(bytes, index, count);

    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();
    xed_decoded_inst_zero_keep_mode(ptr);

    pin_ptr<Byte> pBytes = count > 0 ? &bytes[index] : nullptr;
    xed_error_enum_t error = xed_ild_decode(ptr, pBytes, count);

    if (error != XED_ERROR_NONE)
        throw gcnew XedException(static_cast<XedError>(error));
}
