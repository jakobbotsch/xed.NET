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

// xed_decoded_inst_t
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

G(Byte, ModRM, xed_decoded_inst_get_modrm)
G(int, NumPrefixes, xed_decoded_inst_get_nprefixes)
GB(HasMpxPrefix, xed_decoded_inst_has_mpx_prefix)
GB(IsXAcquire, xed_decoded_inst_is_xacquire)
GB(IsXRelease, xed_decoded_inst_is_xrelease)
GB(IsMaskedVectorOperation, xed_decoded_inst_masked_vector_operation)
G(int, VectorLengthBits, xed_decoded_inst_vector_length_bits)
GB(IsValid, xed_decoded_inst_valid)
G(InstCategory, Category, xed_decoded_inst_get_category)
G(InstExtension, Extension, xed_decoded_inst_get_extension)
G(InstSet, IsaSet, xed_decoded_inst_get_isa_set)
G(InstClass, Class, xed_decoded_inst_get_iclass)
M1B(HasAttribute, InstAttribute, xed_attribute_enum_t, xed_decoded_inst_get_attribute)
M1(int, GetOperandLengthBits, int, int, xed_decoded_inst_operand_length_bits)
G(int, NumOperands, xed_decoded_inst_noperands)
M1(int, GetNumOperandElements, int, int, xed_decoded_inst_operand_elements)
M1(int, GetOperandElementSizeBits, int, int, xed_decoded_inst_operand_element_size_bits)
M1(OperandElementType, GetOperandElementType, int, int, xed_decoded_inst_operand_element_type)
M1(OperandAction, GetOperandAction, int, int, xed_decoded_inst_operand_action)
GB(UsesMasking, xed_decoded_inst_masking)
GB(UsesMerging, xed_decoded_inst_merging)
GB(UsesZeroing, xed_decoded_inst_zeroing)
G(int, Length, xed_decoded_inst_get_length)
M1(Byte, GetByte, int, int, xed_decoded_inst_get_byte)
G(int, MachineModeBits, xed_decoded_inst_get_machine_mode_bits)
G(int, StackAddressModeBits, xed_decoded_inst_get_stack_address_mode_bits)
G(int, OperandWidth, xed_decoded_inst_get_operand_width)
G(Chip, InputChip, xed_decoded_inst_get_input_chip)
void DecodedInstruction::InputChip::set(Chip value) { pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); xed_decoded_inst_set_input_chip(ptr, static_cast<xed_chip_enum_t>(value)); }
M1B(IsValidForChip, Chip, xed_chip_enum_t, xed_decoded_inst_valid_for_chip)
G(InstForm, Form, xed_decoded_inst_get_iform_enum)
G(UInt32, FormDispatch, xed_decoded_inst_get_iform_enum_dispatch)
M1(Register, GetSegReg, int, int, xed_decoded_inst_get_seg_reg)
M1(Register, GetBaseReg, int, int, xed_decoded_inst_get_base_reg)
M1(int, GetScale, int, int, xed_decoded_inst_get_scale)
M1(Int64, GetMemoryDisplacement, int, int, xed_decoded_inst_get_memory_displacement)
M1(int, GetMemoryDisplacementWidth, int, int, xed_decoded_inst_get_memory_displacement_width)
M1(int, GetMemoryDisplacementWidthBits, int, int, xed_decoded_inst_get_memory_displacement_width_bits)
G(int, BranchDisplacement, xed_decoded_inst_get_branch_displacement)
G(int, BranchDisplacementWidth, xed_decoded_inst_get_branch_displacement_width)
G(int, BranchDisplacementWidthBits, xed_decoded_inst_get_branch_displacement_width_bits)
G(UInt64, UnsignedImmediate, xed_decoded_inst_get_unsigned_immediate)
GB(ImmediateIsSigned, xed_decoded_inst_get_immediate_is_signed)
G(int, ImmediateWidth, xed_decoded_inst_get_immediate_width)
G(int, ImmediateWidthBits, xed_decoded_inst_get_immediate_width_bits)
G(int, SignedImmediate, xed_decoded_inst_get_signed_immediate)
G(Byte, SecondImmediate, xed_decoded_inst_get_second_immediate)
M1(Register, GetReg, OperandName, xed_operand_enum_t, xed_decoded_inst_get_reg)
Object^ DecodedInstruction::RFlagsInfo::get() { return nullptr; }
GB(UsesRFlags, xed_decoded_inst_uses_rflags)
G(int, NumMemOperands, xed_decoded_inst_number_of_memory_operands)
M1B(MemRead, int, int, xed_decoded_inst_mem_read)
M1B(MemWritten, int, int, xed_decoded_inst_mem_written)
M1B(MemWrittenOnly, int, int, xed_decoded_inst_mem_written_only)
GB(ConditionallyWritesRegisters, xed_decoded_inst_conditionally_writes_registers)
M1(int, GetMemoryOperandLength, int, int, xed_decoded_inst_get_memory_operand_length)
M1(int, GetMemopAddressWidth, int, int, xed_decoded_inst_get_memop_address_width)
GB(IsPrefetch, xed_decoded_inst_is_prefetch)
M1(Register, GetIndexReg, int, int, xed_decoded_inst_get_index_reg)

// xed_inst_t
#undef G
#define G(type, name, getter)                                     \
type DecodedInstruction::name::get()                              \
{                                                                 \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();       \
    return static_cast<type>(getter(xed_decoded_inst_inst(ptr))); \
}

G(InstException, Exception, xed_inst_exception)

Operand DecodedInstruction::GetOperand(int index)
{
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();
    const xed_inst_t* inst = xed_decoded_inst_inst(ptr);
    if (index < 0 || static_cast<UInt32>(index) >= xed_inst_noperands(inst))
        throw gcnew ArgumentOutOfRangeException("index");

    return Operand(xed_inst_operand(inst, index));
}

// xed_operand_values
#undef GB
#define GB(name, getter)                                    \
bool DecodedInstruction::name::get()                        \
{                                                           \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer(); \
    return getter(xed_decoded_inst_operands(ptr)) != 0;     \
}

#undef G
#define G(retT, name, getter)                                         \
retT DecodedInstruction::name::get()                                  \
{                                                                     \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();           \
    return static_cast<retT>(getter(xed_decoded_inst_operands(ptr))); \
}

#undef M1B
#define M1B(name, argT, castT, getter)                                           \
bool DecodedInstruction::name(argT arg)                                          \
{                                                                                \
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();                      \
    return getter(xed_decoded_inst_operands(ptr), static_cast<castT>(arg)) != 0; \
}

GB(HasBranchNotTakenHint, xed_operand_values_branch_not_taken_hint)
GB(HasBranchTakenHint, xed_operand_values_branch_taken_hint)
GB(IsLongMode, xed_operand_values_get_long_mode)
GB(IsRealMode, xed_operand_values_get_real_mode)
GB(Has66Prefix, xed_operand_values_has_66_prefix)
GB(HasAddressSizePrefix, xed_operand_values_has_address_size_prefix)
GB(HasBranchDisplacement, xed_operand_values_has_branch_displacement)
GB(HasDisplacement, xed_operand_values_has_displacement)
GB(HasImmediate, xed_operand_values_has_immediate)
GB(HasMemoryDisplacement, xed_operand_values_has_memory_displacement)
GB(HasOperandSizePrefix, xed_operand_values_has_operand_size_prefix)
GB(HasRexwPrefix, xed_operand_values_has_rexw_prefix)
GB(HasSegmentPrefix, xed_operand_values_has_segment_prefix)
GB(IsNop, xed_operand_values_is_nop)
G(Register, SegmentPrefix, xed_operand_values_segment_prefix)
M1B(UsesDefaultSegment, int, int, xed_operand_values_using_default_segment)
GB(HasRealRepPrefix, xed_operand_values_has_real_rep)
GB(HasRepPrefix, xed_operand_values_has_rep_prefix)
GB(HasRepnePrefix, xed_operand_values_has_repne_prefix)
GB(IsAtomic, xed_operand_values_get_atomic)
GB(HasLockPrefix, xed_operand_values_has_lock_prefix)
GB(IsLockable, xed_operand_values_lockable)
GB(AccessesMemory, xed_operand_values_accesses_memory)
GB(IsMemopWithoutModrm, xed_operand_values_memop_without_modrm)
GB(HasModRM, xed_operand_values_has_modrm_byte)
GB(HasSib, xed_operand_values_has_sib_byte)

String^ DecodedInstruction::Disassembly::get() { return Format(Syntax::Intel); }

String^ DecodedInstruction::Format(Syntax syntax)
{
    return Format(syntax, 0);
}

String^ DecodedInstruction::Format(Syntax syntax, UInt64 runtimeInstAddress)
{
    char result[1024];
    pin_ptr<xed_decoded_inst_t> ptr = _native.GetPointer();
    if (xed_format_context(static_cast<xed_syntax_enum_t>(syntax),
                           ptr,
                           result, sizeof(result),
                           runtimeInstAddress,
                           nullptr, nullptr))
    {
        return gcnew String(result);
    }

    throw gcnew InvalidOperationException("Cannot format instruction");
}

String^ DecodedInstruction::ToString()
{
    return Disassembly;
}

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

    XedException::Check(error);
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

    XedException::Check(error);
}
