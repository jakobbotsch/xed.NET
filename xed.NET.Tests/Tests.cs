using System;
using Xunit;
using XedNet;

namespace xed.NET.Tests
{
    public class Tests
    {
        [Fact]
        public void TestRoundtrip32()
        {
            XedState state = new XedState
                             {
                                 Mode = MachineMode.LEGACY_32,
                                 StackAddressWidth = AddressWidth._32b,
                             };

            EncoderRequest enc = new EncoderRequest(state);
            enc.Class = InstClass.PUSH;
            enc.SetOperandOrder(0, OperandName.REG0);
            enc.SetReg(OperandName.REG0, Register.EAX);
            byte[] bytes = enc.Encode();

            DecodedInstruction inst = new DecodedInstruction(state);
            inst.Decode(bytes);

            Assert.Equal("push eax", inst.Format(Syntax.INTEL));
        }

        [Fact]
        public void TestRoundtrip64()
        {
            XedState state = new XedState
                             {
                                 Mode = MachineMode.LONG_64,
                             };

            EncoderRequest enc = new EncoderRequest(state);
            enc.Class = InstClass.PUSH;
            enc.SetEffectiveOperandWidth(64);
            enc.SetOperandOrder(0, OperandName.REG0);
            enc.SetReg(OperandName.REG0, Register.RAX);
            byte[] bytes = enc.Encode();

            DecodedInstruction inst = new DecodedInstruction(state);
            inst.Decode(bytes);

            Assert.Equal("push rax", inst.Format(Syntax.INTEL));
        }

        [Fact]
        public void TestDecode64()
        {
            XedState state = new XedState
                             {
                                 Mode = MachineMode.LONG_64,
                                 StackAddressWidth = AddressWidth._64b,
                             };
            DecodedInstruction inst = new DecodedInstruction(state);
            inst.Decode(stackalloc byte[] { 0x50 });

            Assert.Equal("push rax", inst.Format(Syntax.INTEL));
        }
    }
}
