#pragma once
#include "Enums.h"

namespace XedNet
{
    public ref class XedException : System::Exception
    {
    public:
        XedException(XedError error) : System::Exception("XED error: " + error.ToString())
        {
            _errorCode = error;
        }

        property XedError ErrorCode
        {
            XedError get() { return _errorCode; }
        }

    internal:
        static void Check(xed_error_enum_t error);
        static void Check(XedError error);

    private:
        XedError _errorCode;
    };
}
