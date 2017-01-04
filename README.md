# xed.NET
.NET wrapper for Intel's x86 Encoder Decoder

## Building
Clone and install XED to somewhere on your system:
```
git clone https://github.com/intelxed/xed.git xed
git clone https://github.com/intelxed/mbuild.git mbuild
cd xed
C:/Python27/python.exe mfile.py install --host-cpu=ia32
C:/Python27/python.exe mfile.py install --host-cpu=x86-64
```

This will leave the results in the `xed\kits` folder.

In Visual Studio, go to View -> Other Windows -> Property Manager. Now add the proper
32-bit and 64-bit include/library directories here (ia32 = 32-bit, x86-64 = 64-bit).