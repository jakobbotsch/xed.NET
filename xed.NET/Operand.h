#pragma once
#include "Enums.h"

namespace XedNet
{
    public value class Operand
    {
    public:
        property OperandName Name { OperandName get(); }
        property OperandVisibility Visibility { OperandVisibility get(); }
        property OperandType Type { OperandType get(); }
        property OperandXType XType { OperandXType get(); }
        property OperandWidth Width { OperandWidth get(); }
        property XedNet::NonterminalName NonterminalName { XedNet::NonterminalName get(); }
        property System::UInt32 Imm { System::UInt32 get(); }
        property bool IsRead { bool get(); }
        property bool IsReadOnly { bool get(); }
        property bool IsWritten { bool get(); }
        property bool IsWrittenOnly { bool get(); }
        property bool IsReadAndWritten { bool get(); }
        property bool IsConditionalRead { bool get(); }
        property bool IsConditionalWritten { bool get(); }

    internal:
        Operand(const xed_operand_t* native);

    private:
        const xed_operand_t* _native;
    };
}