#include "pch.h"
#include "XedState.h"

using namespace XedNet;

XedState::XedState()
{
    pin_ptr<xed_state_t> xed = _native.GetPointer();
    xed_state_zero(xed);
    GC::KeepAlive(this);
}
