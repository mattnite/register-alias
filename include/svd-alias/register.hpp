// Register class
//
// Author: Matthew Knight
// File Name: register.hpp
// Date: 2019-05-14

#pragma once

#include "bit-field.hpp"

/** Register access class
 *
 * This class provides a zero overhead method for managing special function
 * registers.
 */

template <auto address, typename T = std::uint32_t>
struct RegisterReadOnly {
    template <auto offset, auto width>
    using Field = BitFieldReadOnly<address, offset, width, T>;

	static T read() {
		return *reinterpret_cast<volatile T*>(address);
	}
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

	void write(T const val) {
		*reinterpret_cast<volatile T*>(address) = val;
	}
};

template <auto address, typename T = std::uint32_t>
struct Register : public RegisterReadOnly<address, T>, public RegisterWriteOnly<address, T> {
    template <auto offset, auto width>
    using Field = BitField<address, offset, width, T>;

    static T& reg() { return *reinterpret_cast<volatile T*>(address); }
};
