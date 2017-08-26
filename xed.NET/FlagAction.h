#pragma once
#include "InlineNative.h"
#include "Enums.h"

namespace XedNet
{
    public value class FlagAction
    {
    public:
        property XedFlag Flag { XedFlag get(); }
        property FlagActionType Action { FlagActionType get(); }
        property bool IsRead { bool get(); }
        property bool IsWrite { bool get(); }

        virtual String^ ToString() override;
    internal:
        FlagAction(const xed_flag_action_t* native);
    private:
        const xed_flag_action_t* _native;
    };
}