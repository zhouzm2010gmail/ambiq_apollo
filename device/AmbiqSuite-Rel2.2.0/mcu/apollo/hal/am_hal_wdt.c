//*****************************************************************************
//
//  am_hal_wdt.c
//! @file
//!
//! @brief Hardware abstraction layer for the Watchdog Timer module.
//!
//! @addtogroup wdt1 Watchdog Timer (WDT)
//! @ingroup apollo1hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.2.0 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Dummy variable used to allow reads of WDT registers without triggering
// compiler warnings.
//
//*****************************************************************************
static volatile uint32_t g_ui32Bugfix;

//*****************************************************************************
//
//! @brief Configure the watchdog timer.
//!
//! @param psConfig - pointer to a configuration structure containing the
//! desired watchdog settings.
//!
//! This function will set the watchdog configuration register based on the
//! user's desired settings listed in the structure referenced by psConfig. If
//! the structure indicates that watchdog interrupts are desired, this function
//! will also set the interrupt enable bit in the configuration register.
//!
//! @note In order to actually receive watchdog interrupt and/or watchdog reset
//! events, the caller will also need to make sure that the watchdog interrupt
//! vector is enabled in the ARM NVIC, and that watchdog resets are enabled in
//! the reset generator module. Otherwise, the watchdog-generated interrupt and
//! reset events will have no effect.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_wdt_init(am_hal_wdt_config_t *psConfig)
{
    uint32_t ui32ConfigVal;
    uint16_t ui16IntCount, ui16ResetCount;
    bool bResetEnabled = psConfig->ui32Config & AM_HAL_WDT_ENABLE_RESET;
    bool bInterruptEnabled = psConfig->ui32Config
                                & AM_HAL_WDT_ENABLE_INTERRUPT;

    //
    // Read the desired settings from the psConfig structure.
    //
    ui16IntCount = psConfig->ui16InterruptCount;
    ui16ResetCount = psConfig->ui16ResetCount;

    //
    // Write the interrupt and reset count values to a temporary variable.
    //
    ui32ConfigVal = psConfig->ui32Config;
    ui32ConfigVal |= AM_WRITE_SM(AM_REG_WDT_CFG_INTVAL, ui16IntCount);
    ui32ConfigVal |= AM_WRITE_SM(AM_REG_WDT_CFG_RESVAL, ui16ResetCount);

    //
    // If interrupts should be enabled, set the appropriate bit in the
    // temporary variable. Also, enable the interrupt in INTEN register in the
    // watchdog module.
    //
    if ( bInterruptEnabled )
    {
        //
        // Enable the watchdog interrupt if the configuration calls for them.
        //
        AM_REGn(WDT, 0, INTEN) |= AM_REG_WDT_INTEN_WDTINT_M;
    }
    else
    {
        //
        // Disable the watchdog interrupt if the configuration doesn't call for
        // watchdog interrupts.
        //
        AM_REGn(WDT, 0, INTEN) &= ~AM_REG_WDT_INTEN_WDTINT_M;
    }

    //
    // If resets should be enabled, set the appropriate bit in the temporary
    // variable.
    //
    if ( bResetEnabled )
    {

        //
        // Also enable watchdog resets in the reset module.
        //
        AM_REG(RSTGEN, CFG) |= AM_REG_RSTGEN_CFG_WDREN_M;
    }
    else
    {
        //
        // Disable watchdog resets in the reset module.
        //
        AM_REG(RSTGEN, CFG) &= ~AM_REG_RSTGEN_CFG_WDREN_M;
    }

    //
    // Write the saved value to the watchdog configuration register.
    //
    AM_REGn(WDT, 0, CFG) = ui32ConfigVal;
}

//*****************************************************************************
//
//! @brief Starts the watchdog timer.
//!
//! Enables the watchdog timer tick using the 'enable' bit in the watchdog
//! configuration register.  This function does not perform any locking of the
//! watchdog timer, so it can be disabled or reconfigured later.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_wdt_start(void)
{
    //
    // Make sure the watchdog timer is in the "reset" state, and then set the
    // enable bit to start counting.
    //
    AM_REGn(WDT, 0, CFG)  |= AM_REG_WDT_CFG_WDTEN_M;
    AM_REGn(WDT, 0, RSTRT) = AM_REG_WDT_RSTRT_RSTRT_KEYVALUE;

    //
    // Bug workaround for all Apollo silicon.
    //
    g_ui32Bugfix = AM_REGn(WDT, 0, RSTRT);
}

//*****************************************************************************
//
//! @brief Stops the watchdog timer.
//!
//! Disables the watchdog timer tick by clearing the 'enable' bit in the
//! watchdog configuration register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_wdt_halt(void)
{

    //
    // Clear the watchdog enable bit.
    //
    AM_REGn(WDT, 0, CFG) &= ~AM_REG_WDT_CFG_WDTEN_M;
}

//*****************************************************************************
//
//! @brief Locks the watchdog configuration and starts the watchdog timer.
//!
//! This function sets the watchdog "lock" register, which prevents software
//! from re-configuring the watchdog. This action will also set the enable bit
//! for the watchdog timer, so it will start counting immediately.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_wdt_lock_and_start(void)
{
    //
    // Write the 'key' value to the watchdog lock register.
    //
    AM_REGn(WDT, 0, LOCK) = AM_REG_WDT_LOCK_LOCK_KEYVALUE;
}

//*****************************************************************************
//
//! @brief Read the state of the wdt interrupt status.
//!
//! @param bEnabledOnly - return the status of only the enabled interrupts.
//!
//! This function extracts the interrupt status bits and returns the enabled or
//! raw based on bEnabledOnly.
//!
//! @return WDT interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_wdt_int_status_get(bool bEnabledOnly)
{
    if (bEnabledOnly)
    {
        uint32_t u32RetVal = AM_REG(WDT, INTSTAT);
        return u32RetVal & AM_REG(WDT, INTEN);
    }
    else
    {
        return AM_REG(WDT, INTSTAT);
    }
}

//*****************************************************************************
//
//! @brief Set the state of the wdt interrupt status bit.
//!
//! This function sets the interrupt bit.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_wdt_int_set(void)
{
    AM_REG(WDT, INTSET) = AM_REG_WDT_INTSET_WDTINT_M;
}

//*****************************************************************************
//
//! @brief Clear the state of the wdt interrupt status bit.
//!
//! This function clear the interrupt bit.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_wdt_int_clear(void)
{
    AM_REGn(WDT, 0, INTCLR) = AM_REG_WDT_INTCLR_WDTINT_M;
}

//*****************************************************************************
//
//! @brief Enable the wdt interrupt.
//!
//! This function enable the interrupt.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_wdt_int_enable(void)
{
    AM_REG(WDT, INTEN) |= AM_REG_WDT_INTEN_WDTINT_M;
}

//*****************************************************************************
//
//! @brief Return the enabled WDT interrupts.
//!
//! This function returns the enabled WDT interrupts.
//!
//! @return enabled WDT interrupts.
//
//*****************************************************************************
uint32_t
am_hal_wdt_int_enable_get(void)
{
    return AM_REG(WDT, INTEN);
}

//*****************************************************************************
//
//! @brief Disable the wdt interrupt.
//!
//! This function disablee the interrupt.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_wdt_int_disable(void)
{
    AM_REG(WDT, INTEN) &= ~AM_REG_WDT_INTEN_WDTINT_M;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
