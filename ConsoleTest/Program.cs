using System;
using XedNet;

namespace ConsoleTest
{
    internal class Program
    {
        internal static void Main(string[] args)
        {
            Console.WriteLine("Test");
            XedState state = new XedState
                             {
                                 Mode = MachineMode.Legacy32,
                                 StackAddressWidth = AddressWidth.Width32
                             };

            EncoderRequest enc = new EncoderRequest(state);
            enc.Class = InstClass.Push;
            enc.SetOperandOrder(0, OperandName.Reg0);
            enc.SetReg(OperandName.Reg0, Register.Eax);
            byte[] bytes = enc.Encode();

            DecodedInstruction inst = new DecodedInstruction(state);
            inst.Decode(bytes);

            enc = new EncoderRequest(inst);
            enc.SetBase0(Register.Edx);
            bytes = enc.Encode();
            inst = new DecodedInstruction(state);
            inst.Decode(bytes);

            Console.ReadLine();
        }
    }
}
