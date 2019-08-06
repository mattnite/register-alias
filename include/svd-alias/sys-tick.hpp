// SysTick timer class
//
// Author: Matthew Knight
// File Name: sys-tick.hpp
// Date: 2019-08-05

#pragma once

#include "svd-alias/register.hpp"

#include <chrono>

namespace Svd {
    using Milliseconds = std::chrono::duration<std::uint32_t, std::milli>;

    template <typename Mcu>
    struct SysTick {
        SysTick(Milliseconds const& period) {
            // To initialize:
            // - Program reload value
            Mcu::STK::RVR::RELOAD::write(period.count());
            // - clear current value
            Mcu::STK::CVR::CURRENT::write(0);
            // - program control and status register
            // set TICKINT and ENABLE
            Mcu::STK::CSR::TICKINT::write(1);
            Mcu::STK::CSR::ENABLE::write(1);
        }

        ~SysTick() {
            // set TICKINT and ENABLE
            Mcu::STK::CSR::ENABLE::write(0);
            Mcu::STK::CSR::TICKINT::write(0);
        }
    };
}
