#include "pch.h"
#include "RFlagsInfo.h"

using namespace System;
using namespace XedNet;

RFlagsInfo::RFlagsInfo(const xed_simple_flag_t* native)
{
    _native = native;
}

int RFlagsInfo::NumFlags::get() { return _native->nflags; }
bool RFlagsInfo::MayWrite::get() { return _native->may_write != 0; }
bool RFlagsInfo::MustWrite::get() { return _native->must_write != 0; }
FlagSet RFlagsInfo::Read::get()
{
    xed_flag_set_t flags = _native->read;
    return *(FlagSet*)&flags;
}
FlagSet RFlagsInfo::Written::get()
{
    xed_flag_set_t flags = _native->written;
    return *(FlagSet*)&flags;
}
FlagSet RFlagsInfo::Undefined::get()
{
    xed_flag_set_t flags = _native->undefined;
    return *(FlagSet*)&flags;
}
FlagAction RFlagsInfo::GetFlagAction(int index)
{
    if (index < 0 || index >= NumFlags)
        throw gcnew ArgumentOutOfRangeException("index");

    // Ok since this returns from a global table
    return FlagAction(xed_simple_flag_get_flag_action(_native, static_cast<UInt32>(index)));
}

String^ RFlagsInfo::ToString()
{
    char buf[1024] = { 0 };
    xed_simple_flag_print(_native, buf, sizeof(buf));
    return gcnew String(buf);
}