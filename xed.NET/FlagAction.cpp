#include "pch.h"
#include "FlagAction.h"

using namespace System;
using namespace XedNet;

FlagAction::FlagAction(const xed_flag_action_t* native)
{
    _native = native;
}

XedFlag FlagAction::Flag::get() { return static_cast<XedFlag>(_native->flag); }
FlagActionType FlagAction::Action::get() { return static_cast<FlagActionType>(_native->action); }
bool FlagAction::IsRead::get() { return xed_flag_action_read_flag(_native) != 0; }
bool FlagAction::IsWrite::get() { return xed_flag_action_writes_flag(_native) != 0; }

String^ FlagAction::ToString()
{
    char buf[1024] = { 0 };
    xed_flag_action_print(_native, buf, sizeof(buf));
    return gcnew String(buf);
}