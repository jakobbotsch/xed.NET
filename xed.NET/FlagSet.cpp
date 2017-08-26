#include "stdafx.h"
#include "FlagSet.h"

using namespace System;
using namespace XedNet;

#define G(nameOurs, nameTheirs) \
bool FlagSet::nameOurs::get() { return _native->s.nameTheirs; }

UInt32 FlagSet::Flat::get() { return _native->flat; }
G(Cf, cf)
G(Pf, pf)
G(Af, af)
G(Zf, zf)
G(Sf, sf)
G(Tf, tf)
G(If, _if)
G(Df, df)
G(Of, of)
int FlagSet::Iopl::get() { return _native->s.iopl; }
G(Nt, nt)
G(Rf, rf)
G(Vm, vm)
G(Ac, ac)
G(Vif, vif)
G(Vip, vip)
G(Id, id)
G(Fc0, fc0)
G(Fc1, fc1)
G(Fc2, fc2)
G(Fc3, fc3)

String^ FlagSet::ToString()
{
    xed_flag_set_t flags = *_native.GetPointer();
    char buf[1024] = { 0 };
    xed_flag_set_print(&flags, buf, sizeof(flags));
    return gcnew String(buf);
}