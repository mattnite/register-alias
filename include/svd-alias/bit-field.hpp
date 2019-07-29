// Bit field Abstraction
//
// Author: Matthew Knight
// File Name: bit-field.hpp
// Date: 2019-05-15

#pragma once

#include <cstdint>

template <auto address, auto position, auto width, typename T = std::uint32_t>
struct BitFieldReadOnly {
    constexpr static auto max = (1 << width) - 1;
    constexpr static auto mask = max << position;
    constexpr static auto offset = position;

    volatile static T read() {
        return (*reinterpret_cast<T*>(address) & mask) >> position;
    }
};

template <auto address, auto position, auto width, typename T = std::uint32_t>
struct BitField : public BitFieldReadOnly<address, position, width, T> {
    using BitFieldReadOnly<address, position, width, T>::mask;
    using BitFieldReadOnly<address, position, width, T>::offset;

    volatile static void write(const T& val) {
        auto ptr = reinterpret_cast<T*>(address);
        *ptr = (*ptr & ~mask) | (mask & (val << position));
    }
};
