#include "Stdafx.h"
#include "Enums.h"

using namespace System;
using namespace XedNet;

bool EnumExtensions::IsRegister(OperandName name)
{
    return xed_operand_is_register(static_cast<xed_operand_enum_t>(name)) != 0;
}

bool EnumExtensions::IsMemoryAddressingRegister(OperandName name)
{
    return xed_operand_is_memory_addressing_register(static_cast<xed_operand_enum_t>(name)) != 0;
}

InstClass EnumExtensions::RemoveRep(InstClass iclass)
{
    return static_cast<InstClass>(xed_rep_remove(static_cast<xed_iclass_enum_t>(iclass)));
}

InstClass EnumExtensions::WithRepe(InstClass iclass)
{
    return static_cast<InstClass>(xed_repe_map(static_cast<xed_iclass_enum_t>(iclass)));
}

InstClass EnumExtensions::WithRepne(InstClass iclass)
{
    return static_cast<InstClass>(xed_repne_map(static_cast<xed_iclass_enum_t>(iclass)));
}

InstClass EnumExtensions::WithRep(InstClass iclass)
{
    return static_cast<InstClass>(xed_rep_map(static_cast<xed_iclass_enum_t>(iclass)));
}