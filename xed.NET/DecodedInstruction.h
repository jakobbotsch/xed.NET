// xed.NET.h

#pragma once
#include "InlineNative.h"
#include "Enums.h"
#include "Error.h"
#include "Operand.h"
#include "RFlagsInfo.h"

namespace XedNet
{
    ref class XedState;

    public ref class DecodedInstruction
    {
    public:
        DecodedInstruction(XedState^ state);

        property System::Byte ModRM { System::Byte get(); }
        property int NumPrefixes { int get(); }
        property bool HasMpxPrefix { bool get(); }
        property bool IsXAcquire { bool get(); }
        property bool IsXRelease { bool get(); }
        property bool IsMaskedVectorOperation { bool get(); }
        property int VectorLengthBits { int get(); }
        property bool IsValid { bool get(); }
        property InstCategory Category { InstCategory get(); }
        property InstExtension Extension { InstExtension get(); }
        property InstSet IsaSet { InstSet get(); }
        property InstClass Class { InstClass get(); }
        bool HasAttribute(InstAttribute attribute);
        int GetOperandLengthBits(int index);
        property int NumOperands { int get(); }
        int GetNumOperandElements(int index);
        int GetOperandElementSizeBits(int index);
        OperandElementType GetOperandElementType(int index);
        OperandAction GetOperandAction(int index);
        property bool UsesMasking { bool get(); }
        property bool UsesMerging { bool get(); }
        property bool UsesZeroing { bool get(); }
        property int Length { int get(); }
        System::Byte GetByte(int index);
        property int MachineModeBits { int get(); }
        property int StackAddressModeBits { int get(); }
        property int OperandWidth { int get(); }
        property Chip InputChip { Chip get(); void set(Chip value); }
        bool IsValidForChip(Chip chip);
        property InstForm Form { InstForm get(); }
        property System::UInt32 FormDispatch { System::UInt32 get(); }
        Register GetSegReg(int index);
        Register GetBaseReg(int index);
        int GetScale(int index);
        System::Int64 GetMemoryDisplacement(int index);
        int GetMemoryDisplacementWidth(int index);
        int GetMemoryDisplacementWidthBits(int index);
        property int BranchDisplacement { int get(); }
        property int BranchDisplacementWidth { int get(); }
        property int BranchDisplacementWidthBits { int get(); }
        property System::UInt64 UnsignedImmediate { System::UInt64 get(); }
        property bool ImmediateIsSigned { bool get(); }
        property int ImmediateWidth { int get(); }
        property int ImmediateWidthBits { int get(); }
        property int SignedImmediate { int get(); }
        property Byte SecondImmediate { Byte get(); }
        Register GetReg(OperandName operand);
        property Nullable<XedNet::RFlagsInfo> RFlagsInfo { Nullable<XedNet::RFlagsInfo> get(); }
        property bool UsesRFlags { bool get(); }
        property int NumMemOperands { int get(); }
        bool MemRead(int index);
        bool MemWritten(int index);
        bool MemWrittenOnly(int index);
        property bool ConditionallyWritesRegisters { bool get(); }
        int GetMemoryOperandLength(int index);
        int GetMemopAddressWidth(int index);
        property bool IsPrefetch { bool get(); }
        Register GetIndexReg(int index);

        Operand GetOperand(int index);
        property InstException Exception { InstException get(); }

        property bool HasBranchNotTakenHint { bool get(); }
        property bool HasBranchTakenHint { bool get(); }
        property bool IsLongMode { bool get(); }
        property bool IsRealMode { bool get(); }
        property bool Has66Prefix { bool get(); }
        property bool HasAddressSizePrefix { bool get(); }
        property bool HasBranchDisplacement { bool get(); }
        property bool HasDisplacement { bool get(); }
        property bool HasImmediate { bool get(); }
        property bool HasMemoryDisplacement { bool get(); }
        property bool HasOperandSizePrefix { bool get(); }
        property bool HasRexwPrefix { bool get(); }
        property bool HasSegmentPrefix { bool get(); }
        property bool IsNop { bool get(); }
        property Register SegmentPrefix { Register get(); }
        bool UsesDefaultSegment(int index);
        property bool HasRealRepPrefix { bool get(); }
        property bool HasRepPrefix { bool get(); }
        property bool HasRepnePrefix { bool get(); }
        property bool IsAtomic { bool get(); }
        property bool HasLockPrefix { bool get(); }
        property bool IsLockable { bool get(); }
        property bool AccessesMemory { bool get(); }
        property bool IsMemopWithoutModrm { bool get(); }
        property bool HasModRM { bool get(); }
        property bool HasSib { bool get(); }

        property String^ Disassembly { String^ get(); }
        String^ Format(Syntax syntax);
        String^ Format(Syntax syntax, System::UInt64 runtimeInstAddress);

        String^ ToString() override;

        XedError TryDecode(array<System::Byte>^ bytes);
        XedError TryDecode(array<System::Byte>^ bytes, int index, int count);
        XedError TryDecode(System::Byte* bytes, int count);
        XedError TryIldDecode(array<System::Byte>^ bytes);
        XedError TryIldDecode(array<System::Byte>^ bytes, int index, int count);
        XedError TryIldDecode(System::Byte* bytes, int count);
        void Decode(array<System::Byte>^ bytes);
        void Decode(array<System::Byte>^ bytes, int index, int count);
        void Decode(System::Byte* bytes, int count);
        void IldDecode(array<System::Byte>^ bytes);
        void IldDecode(array<System::Byte>^ bytes, int index, int count);
        void IldDecode(System::Byte* bytes, int count);
    internal:
        InlineNative<xed_decoded_inst_t> _native;
    };
}
