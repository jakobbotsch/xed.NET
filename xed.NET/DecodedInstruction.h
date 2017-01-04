// xed.NET.h

#pragma once
#include "InlineNative.h"
#include "Enums.h"

namespace XedNet
{
    ref class XedState;

    public ref class DecodedInstruction
    {
    public:
        DecodedInstruction(XedState^ state);

        property bool ConditionallyWritesRegisters { bool get(); }
        Register GetBaseReg(int index);
        property int BranchDisplacement { int get(); }
        property int BranchDisplacementWidth { int get(); }
        property int BranchDisplacementWidthBits { int get(); }
        property bool ImmediateIsSigned { bool get(); }
        property int ImmediateWidth { int get(); }
        property int ImmediateWidthBits { int get(); }
        Register GetIndexReg(int index);
        int GetMemopAddressWidth(int index);
        System::Int64 GetMemoryDisplacement(int index);
        int GetMemoryDisplacementWidth(int index);
        int GetMemoryDisplacementWidthBits(int index);
        int GetMemoryOperandLength(int index);
        Register GetReg(Operand operand);
        property System::Object^ RFlagsInfo { System::Object^ get(); }
        int GetScale(int index);
        property Byte SecondImmediate { Byte get(); }
        Register GetSegReg(int index);
        property int SignedImmediate { int get(); }
        property System::UInt64 UnsignedImmediate { System::UInt64 get(); }
        property bool IsPrefetch { bool get(); }
        bool MemRead(int index);
        bool MemWritten(int index);
        bool MemWrittenOnly(int index);
        property int NumMemOperands { int get(); }
        property bool UsesRFlags { bool get(); }
        bool HasAttribute(Attribute attribute);
        System::Byte GetByte(int index);
        property InstCategory Category { InstCategory get(); }
        property InstExtension Extension { InstExtension get(); }
        property InstClass Class { InstClass get(); }
        property InstSet IsaSet { InstSet get(); }
        property bool IsValid { bool get(); }
        property System::Object^ Instruction { System::Object^ get(); }
        property InstForm Form { InstForm get(); }
        property System::UInt32 FormDispatch { System::UInt32 get(); }
        property Chip InputChip { Chip get(); void set(Chip value); }
        property int MachineModeBits { int get(); }
        property int OperandWidth { int get(); }
        property int StackAddressModeBits { int get(); }
        bool IsValidForChip(Chip chip);
        property int Length { int get(); }
        property int NumOperands { int get(); }
        int GetOperandElementSizeBits(int index);
        OperandElementType GetOperandElementType(int index);
        int GetNumOperandElements(int index);
        int GetOperandLengthBits(int index);
        property System::Object^ OperandValues { System::Object^ get(); }
        property System::Byte ModRM { System::Byte get(); }
        property int NumPrefixes { int get(); }
        property bool HasMpxPrefix { bool get(); }
        property bool IsXAcquire { bool get(); }
        property bool IsXRelease { bool get(); }
        property bool IsMaskedVectorOperation { bool get(); }
        property int VectorLengthBits { int get(); }

        void Decode(array<System::Byte>^ bytes);
        void Decode(array<System::Byte>^ bytes, int index, int count);
        void IldDecode(array<System::Byte>^ bytes);
        void IldDecode(array<System::Byte>^ bytes, int index, int count);
    internal:
        InlineNative<xed_decoded_inst_t> _native;
    };
}
