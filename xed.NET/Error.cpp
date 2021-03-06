#include "pch.h"
#include "Enums.h"
#include "Error.h"

using namespace XedNet;

void XedException::Check(xed_error_enum_t error)
{
    if (error != XED_ERROR_NONE)
        throw gcnew XedException(static_cast<XedError>(error));
}

void XedException::Check(XedError error)
{
    if (error != XedError::NONE)
        throw gcnew XedException(error);
}
