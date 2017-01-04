#pragma once
#pragma unmanaged
#include <type_traits>

#pragma managed

namespace XedNet
{
    using namespace System;
    using namespace System::Runtime::CompilerServices;
    using namespace System::Runtime::InteropServices;

    template<typename T>
    [UnsafeValueType]
    [StructLayout(LayoutKind::Explicit, Size = sizeof(T))]
    private value class InlineNative
    {
    public:
        interior_ptr<T> GetPointer() { return reinterpret_cast<interior_ptr<T>>(&_firstByte); }
        interior_ptr<T> operator->() { return GetPointer(); }

    private:
        static_assert(std::is_pod<T>::value, "Type must be plain old data type");
        [FieldOffset(0)]
        Byte _firstByte;
    };
}