# xed.NET
.NET Core wrapper for Intel's x86 Encoder Decoder.

## Building
Clone and install XED to somewhere on your system:
```powershell
git clone https://github.com/intelxed/xed.git xed
git clone https://github.com/intelxed/mbuild.git mbuild
cd xed
# Current version that xed.NET is based on.
git checkout 40125558530137444b4ee6fd26b445bfa105b543
python mfile.py install --host-cpu=ia32
python mfile.py install --host-cpu=x86-64
```

This will leave the results in the `xed\kits` folder.

In Visual Studio, go to View -> Other Windows -> Property Manager. Now add the proper
32-bit and 64-bit include/library directories here (ia32 = 32-bit, x86-64 = 64-bit).

After this process, the C++

## Naming conventions
The name of each enum is converted into a .NET style name (CamelCase). Each enum member
is preseved as is in XED, except the prefix is removed. For instance, `XED_ICLASS_ADD`
becomes `InstClass.ADD`. Members where this name is invalid are prefixed with underscore.
For example, `XED_ISA_SET_3DNOW` becomes `InstSet._3DNOW`.