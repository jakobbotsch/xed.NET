#pragma once
#include "InlineNative.h"
#include "Enums.h"

namespace XedNet
{
    public ref class XedState
    {
    public:
        XedState();

        property MachineMode Mode
        {
            MachineMode get() { return static_cast<MachineMode>(_native->mmode); }
            void set(MachineMode val) { _native->mmode = static_cast<xed_machine_mode_enum_t>(val); }
        }

        property AddressWidth StackAddressWidth
        {
            AddressWidth get() { return static_cast<AddressWidth>(_native->stack_addr_width); }
            void set(AddressWidth val) { _native->stack_addr_width = static_cast<xed_address_width_enum_t>(val); }
        }
    internal:
        InlineNative<xed_state_t> _native;
    };
}
