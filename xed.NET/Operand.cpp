
#include "stdafx.h"
#include "Operand.h"

using namespace System;
using namespace XedNet;

Operand::Operand(const xed_operand_t* native)
    : _native(native)
{
}

#define G(retT, name, getter) \
retT Operand::name::get() { return static_cast<retT>(getter(_native)); }

#define GB(name, getter) \
bool Operand::name::get() { return getter(_native) != 0; }

G(OperandName, Name, xed_operand_name)
G(OperandVisibility, Visibility, xed_operand_operand_visibility)
G(OperandType, Type, xed_operand_type)
G(OperandXType, XType, xed_operand_xtype)
G(OperandWidth, Width, xed_operand_width)
G(XedNet::NonterminalName, NonterminalName, xed_operand_nonterminal_name)
G(UInt32, Imm, xed_operand_imm)
GB(IsRead, xed_operand_read)
GB(IsReadOnly, xed_operand_read_only)
GB(IsWritten, xed_operand_written)
GB(IsWrittenOnly, xed_operand_written_only)
GB(IsReadAndWritten, xed_operand_read_and_written)
GB(IsConditionalRead, xed_operand_conditional_read)
GB(IsConditionalWritten, xed_operand_conditional_write)