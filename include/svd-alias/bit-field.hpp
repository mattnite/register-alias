// Bit field Abstraction
//
// Author: Matthew Knight
// File Name: bit-field.hpp
// Date: 2019-05-15

#pragma once

#include <cstdint>

template <auto address, auto position, auto width>
struct BitFieldBase {
    constexpr static auto max = (1 << width) - 1;
    constexpr static auto mask = max << position;
    constexpr static auto offset = position;
};

template <auto address, auto position, auto width, typename T = std::uint32_t>
struct BitFieldReadOnly : public BitFieldBase<address, position, width> {
	using BitFieldBase<address, position, width>::mask;
	using BitFieldBase<address, position, width>::offset;

    static T read() {
        return (*reinterpret_cast<volatile T*>(address) & mask) >> offset;
    }
};

template <auto address, auto position, auto width, typename T = std::uint32_t>
struct BitFieldWriteOnly : public BitFieldBase<address, position, width> {
	using BitFieldBase<address, position, width>::mask;
	using BitFieldBase<address, position, width>::offset;

    static void write(T const val) {
        auto ptr = reinterpret_cast<volatile T*>(address);
        *ptr = (*ptr & ~mask) | (mask & (val << offset));
    }
};

template <auto address, auto position, auto width, typename T = std::uint32_t>
struct BitField
	: virtual public BitFieldReadOnly<address, position, width, T>
	, virtual public BitFieldWriteOnly<address, position, width, T>
{};
