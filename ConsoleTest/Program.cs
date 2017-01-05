using System;
using XedNet;

namespace ConsoleTest
{
    internal class Program
    {
        internal static void Main(string[] args)
        {
            Console.WriteLine("Test");
            DecodedInstruction inst = new DecodedInstruction(
                                          new XedState
                                          {
                                              Mode = MachineMode.Legacy32,
                                              StackAddressWidth = AddressWidth.Width32
                                          });

            inst.Decode(new byte[] {0x83, 0x00, 0x19});
            Console.ReadLine();
        }
    }
}
