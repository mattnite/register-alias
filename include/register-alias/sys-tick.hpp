// SysTick timer class
//
// Author: Matthew Knight
// File Name: sys-tick.hpp
// Date: 2019-08-05

#pragma once

#include "register-alias/register.hpp"
#include "register-alias/util.hpp"

#include <chrono>

namespace RegisterAlias {
    using Milliseconds = std::chrono::duration<std::uint32_t, std::milli>;

    template <typename Mcu>
    struct SysTick {
        SysTick(Milliseconds const& period) {
            Mcu::STK::RVR::RELOAD::write(period.count());
            Mcu::STK::CVR::CURRENT::write(0);
            /*
            Mcu::STK::CSR::write<
                Svd::SetField<Mcu::STK::CSR::TICKINT>>();
                Svd::SetField<Mcu::STK::CSR::ENABLE>>();
            */
        }

        ~SysTick() {
            /*
            Mcu::STK::write<Svd::ClearField<Mcu::STK::CSR::ENABLE>,
                            Svd::ClearField<Mcu::STK::CSR::TICKINT>>();
            */
        }
    };
} // namespace RegisterAlias
