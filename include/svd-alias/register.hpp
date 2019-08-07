// Register class
//
// Author: Matthew Knight
// File Name: register.hpp
// Date: 2019-05-14

#pragma once

#include "svd-alias/bit-field.hpp"
#include "svd-alias/util.hpp"

/** Register access class
 *
 * This class provides a zero overhead method for managing special function
 * registers.
 */

template <auto address, typename T = std::uint32_t>
struct RegisterReadOnly {
    template <auto offset, auto width>
    using Field = BitFieldReadOnly<address, offset, width, T>;

    static T read() { return *reinterpret_cast<volatile T*>(address); }
};

template <auto address, typename T = std::uint32_t>
struct RegisterWriteOnly {
    template <auto offset, auto width>
    using Field = BitFieldWriteOnly<address, offset, width, T>;

    static void set(T const val) {
        *reinterpret_cast<volatile T*>(address) |= 1 << val;
    }

    static void clear(T const val) {
        *reinterpret_cast<volatile T*>(address) &= ~(1 << val);
    }

    static void toggle(T const val) {
        *reinterpret_cast<volatile T*>(address) ^= 1 << val;
    }

    template <T... bits>
    static void set() {
        *reinterpret_cast<volatile T*>(address) |= ((1 << bits) | ...);
    }

    template <T... bits>
    static void clear() {
        *reinterpret_cast<volatile T*>(address) &= (~(1 << bits) & ...);
    }

    template <T... bits>
    static void toggle() {
        *reinterpret_cast<volatile T*>(address) ^= ((1 << bits) | ...);
    }

    static void write(T const val) {
        *reinterpret_cast<volatile T*>(address) = val;
    }

    template <typename... Pairs>
    static void write() {
        auto ptr = reinterpret_cast<volatile T*>(address);
        *ptr = (*ptr & ~(Pairs::Field::mask | ...)) |
               ((Pairs::Field::mask & ...) &
                ((Pairs::value << Pairs::Field::offset) | ...));
    }

    template <typename... FieldValues>
    static void write(FieldValues&&... fieldValues) {
        auto ptr = reinterpret_cast<volatile T*>(address);
        *ptr = (*ptr & ~(FieldValues::Field::mask | ...)) |
               ((FieldValues::Field::mask & ...) &
                ((fieldValues.value << FieldValues::Field::offset) | ...));
    }
};

template <auto address, typename T = std::uint32_t>
struct Register
    : public RegisterReadOnly<address, T>
    , public RegisterWriteOnly<address, T> {
    template <auto offset, auto width>
    using Field = BitField<address, offset, width, T>;

    volatile static T& reg() { return *reinterpret_cast<T*>(address); }
};
