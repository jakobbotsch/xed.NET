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

        [Fact]
        public void TestSizeOfRexJmp()
        {
            XedState state = new XedState
                             {
                                 Mode = MachineMode.LONG_64,
                                 StackAddressWidth = AddressWidth._64b,
                             };
            DecodedInstruction inst = new DecodedInstruction(state);
            Span<byte> bytes = stackalloc byte[15];
            for (uint i = 0; i < 0x1000000; i++)
            {
                bytes[0] = (byte)(i >> 0);
                bytes[1] = (byte)(i >> 8);
                bytes[2] = (byte)(i >> 16);
                int ourLen = GetLength(bytes);
                if (ourLen == -1)
                    continue;

                inst.IldDecode(bytes);
                Assert.Equal(inst.Length, ourLen);
            }

            static int GetLength(Span<byte> bytes)
            {
                if ((bytes[0] & 0xf8) == 0x48 &&
                    (bytes[1] == 0xff) &&
                    (bytes[2] & 0x38) == 0x20)
                {
                    int size = 3;
                    int mod = bytes[2] >> 6;
                    int rm = bytes[2] & 0b111;
                    if (mod != 0b11)
                    {
                        if (rm == 0b100)
                            size++;

                        if (mod == 0b01)
                            size++;
                        else if (mod == 0b10 || (mod == 0b00 && rm == 0b101))
                            size += 4;
                    }

                    return size;
                }

                return -1;
            }
        }
    }
}
