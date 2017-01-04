#pragma once

#define CheckNull(o) do { if ((o) == nullptr) throw gcnew ArgumentNullException(#o); } while (false)

#define CheckBounds(arr, index, count) do { if ((arr) == nullptr) throw gcnew ArgumentNullException(#arr); \
	if ((index) < 0) throw gcnew ArgumentOutOfRangeException(#index); \
	if ((count) < 0) throw gcnew ArgumentOutOfRangeException(#count); \
	if (static_cast<UInt32>((index) + static_cast<UInt32>(count)) > static_cast<UInt32>((arr)->Length)) throw gcnew ArgumentException(#index " + " #count " is beyond the end of the array"); } while (false)
