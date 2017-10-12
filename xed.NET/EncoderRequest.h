#pragma once
#include "InlineNative.h"
#include "Enums.h"

namespace XedNet
{
    ref class DecodedInstruction;
    ref class XedState;

    public ref class EncoderRequest
    {
    public:
        EncoderRequest(XedState^ state);
        EncoderRequest(DecodedInstruction^ decoded);

        property InstClass Class { InstClass get(); void set(InstClass value); }
        void SetRepne();
        void SetRep();
        void ClearRep();
        void SetEffectiveOperandWidth(int bits);
        void SetEffectiveAddressSize(int bits);
        void SetReg(OperandName operand, Register reg);
        void SetOperandOrder(int index, OperandName name);
        OperandName GetOperandOrder(int index);
        property int NumOperandOrderEntries { int get(); }
        void SetRelbr();
        void SetBranchDisplacement(int displacement, int numBytes);
        void SetPtr();
        void SetUImm0(System::UInt64 uimm, int numBytes);
        void SetUImm0Bits(System::UInt64 uimm, int numBits);
        void SetUImm1(System::Byte uimm);
        void SetSImm(int simm, int numBytes);
        void SetMemoryDisplacement(System::Int64 disp, int numBytes);
        void SetAgen();
        void SetMem0();
        void SetMem1();
        void SetMemoryOperandLength(int numBytes);
        void SetSeg0(Register segReg);
        void SetSeg1(Register segReg);
        void SetBase0(Register baseReg);
        void SetBase1(Register baseReg);
        void SetIndex(Register indexReg);
        void SetScale(int scale);
        void ClearOperandOrder();

        void Encode(array<System::Byte>^ bytes, int index, int maxCount, [System::Runtime::InteropServices::Out] int% outLength);
        array<System::Byte>^ Encode();

        static bool EncodeNop(array<System::Byte>^ bytes, int index, int length, bool throwOnUnencodable);
        static array<Byte>^ EncodeNop(int length, bool throwOnUnencodable);
    internal:
        InlineNative<xed_encoder_request_t> _native;
    };
}