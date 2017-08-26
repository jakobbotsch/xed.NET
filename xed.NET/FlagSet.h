#pragma once
#include "InlineNative.h"

namespace XedNet
{
    public value class FlagSet
    {
    public:
        property System::UInt32 Flat { System::UInt32 get(); }
        property bool Cf { bool get(); }
        property bool Pf { bool get(); }
        property bool Af { bool get(); }
        property bool Zf { bool get(); }
        property bool Sf { bool get(); }
        property bool Tf { bool get(); }
        property bool If { bool get(); }
        property bool Df { bool get(); }
        property bool Of { bool get(); }
        property int Iopl { int get(); }
        property bool Nt { bool get(); }
        property bool Rf { bool get(); }
        property bool Vm { bool get(); }
        property bool Ac { bool get(); }
        property bool Vif { bool get(); }
        property bool Vip { bool get(); }
        property bool Id { bool get(); }
        property bool Fc0 { bool get(); }
        property bool Fc1 { bool get(); }
        property bool Fc2 { bool get(); }
        property bool Fc3 { bool get(); }

        virtual String^ ToString() override;
    private:
        InlineNative<xed_flag_set_t> _native;
    };
}