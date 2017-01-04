#pragma once
#include "InlineNative.h"

namespace XedNet
{
    public enum class MachineMode
    {
        Invalid = XED_MACHINE_MODE_INVALID,
        Long64 = XED_MACHINE_MODE_LONG_64,
        LongCompat32 = XED_MACHINE_MODE_LONG_COMPAT_32,
        LongCompat16 = XED_MACHINE_MODE_LONG_COMPAT_16,
        Legacy32 = XED_MACHINE_MODE_LEGACY_32,
        Legacy16 = XED_MACHINE_MODE_LEGACY_16,
        Real16 = XED_MACHINE_MODE_REAL_16,
    };

    public enum class AddressWidth
    {
        Invalid = XED_ADDRESS_WIDTH_INVALID,
        Width16 = XED_ADDRESS_WIDTH_16b,
        Width32 = XED_ADDRESS_WIDTH_32b,
        Width64 = XED_ADDRESS_WIDTH_64b,
    };

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
