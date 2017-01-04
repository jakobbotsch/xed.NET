#pragma once

namespace XedNet
{
    public enum class XedError
    {
        None = XED_ERROR_NONE,
        BufferTooShort = XED_ERROR_BUFFER_TOO_SHORT,
        GeneralError = XED_ERROR_GENERAL_ERROR,
        InvalidForChip = XED_ERROR_INVALID_FOR_CHIP,
        BadRegister = XED_ERROR_BAD_REGISTER,
        BadLockPrefix = XED_ERROR_BAD_LOCK_PREFIX,
        BadRepPrefix = XED_ERROR_BAD_REP_PREFIX,
        BadLegacyPrefix = XED_ERROR_BAD_LEGACY_PREFIX,
        BadRexPrefix = XED_ERROR_BAD_REX_PREFIX,
        BadEvexUbit = XED_ERROR_BAD_EVEX_UBIT,
        BadMap = XED_ERROR_BAD_MAP,
        BadEvexVPrime = XED_ERROR_BAD_EVEX_V_PRIME,
        NoOutputPointer = XED_ERROR_NO_OUTPUT_POINTER,
        NoAgenCallbackRegistered = XED_ERROR_NO_AGEN_CALL_BACK_REGISTERED,
        BadMemopIndex = XED_ERROR_BAD_MEMOP_INDEX,
        CallbackProblem = XED_ERROR_CALLBACK_PROBLEM,
        GatherRegs = XED_ERROR_GATHER_REGS,
        InstrTooLong = XED_ERROR_INSTR_TOO_LONG,
        InvalidMode = XED_ERROR_INVALID_MODE,
    };

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

    private:
        XedError _errorCode;
    };
}
