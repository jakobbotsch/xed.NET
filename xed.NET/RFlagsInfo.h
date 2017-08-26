#pragma once
#include "InlineNative.h"
#include "FlagSet.h"
#include "FlagAction.h"

namespace XedNet
{
    public value class RFlagsInfo
    {
    public:
        property int NumFlags { int get(); }
        property bool MayWrite { bool get(); }
        property bool MustWrite { bool get(); }
        property FlagSet Read { FlagSet get(); }
        property FlagSet Written { FlagSet get(); }
        property FlagSet Undefined { FlagSet get(); }
        FlagAction GetFlagAction(int index);

        virtual String^ ToString() override;
    internal:
        RFlagsInfo(const xed_simple_flag_t* native);
    private:
        const xed_simple_flag_t* _native;
    };
}