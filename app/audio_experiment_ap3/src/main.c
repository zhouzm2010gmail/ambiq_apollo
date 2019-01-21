/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* This file is the main file of the audio experiment platform. */

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#include "board_setup.h"
#include "audio_driver.h"
/* app utils include file */
//#include "am_app_utils.h"
/* opus include file */
//#include "am_opus_config.h"

#include "opus.h"
//#include "debug.h"
//#include "opus_types.h"
//#include "opus_private.h"
//#include "opus_multistream.h"

#define ARM_MATH_CM4
#include <arm_math.h>

#define MAX_PACKET_SIZE         1500



int main(void)
{
    //
    // OPUS codec configuration
    //
    OpusEncoder *g_opusEnc = NULL;
    int g_opusErr;
    uint32_t g_audioSampleRate = 16000;
    int32_t g_audioChannel = 1;
    opus_int32 g_opusComplexity = 0;
    opus_int32 g_opusEncRet;
    int16_t g_opusTestData[FRAME_SIZE] = {
    0x8284, 0x8684, 0x8A84, 0x8E84, 0x9284, 0x9684, 0x9A84, 0x9E84, 0xA284, 0xA684, 0xAA84, 0xAE84, 0xB284, 0xB684, 0xBA84, 0xBE84,
    0xC184, 0xC384, 0xC584, 0xC784, 0xC984, 0xCB84, 0xCD84, 0xCF84, 0xD184, 0xD384, 0xD584, 0xD784, 0xD984, 0xDB84, 0xDD84, 0xDF84,
    0xE104, 0xE204, 0xE304, 0xE404, 0xE504, 0xE604, 0xE704, 0xE804, 0xE904, 0xEA04, 0xEB04, 0xEC04, 0xED04, 0xEE04, 0xEF04, 0xF004,
    0xF0C4, 0xF144, 0xF1C4, 0xF244, 0xF2C4, 0xF344, 0xF3C4, 0xF444, 0xF4C4, 0xF544, 0xF5C4, 0xF644, 0xF6C4, 0xF744, 0xF7C4, 0xF844,
    0xF8A4, 0xF8E4, 0xF924, 0xF964, 0xF9A4, 0xF9E4, 0xFA24, 0xFA64, 0xFAA4, 0xFAE4, 0xFB24, 0xFB64, 0xFBA4, 0xFBE4, 0xFC24, 0xFC64,
    0xFC94, 0xFCB4, 0xFCD4, 0xFCF4, 0xFD14, 0xFD34, 0xFD54, 0xFD74, 0xFD94, 0xFDB4, 0xFDD4, 0xFDF4, 0xFE14, 0xFE34, 0xFE54, 0xFE74,
    0xFE8C, 0xFE9C, 0xFEAC, 0xFEBC, 0xFECC, 0xFEDC, 0xFEEC, 0xFEFC, 0xFF0C, 0xFF1C, 0xFF2C, 0xFF3C, 0xFF4C, 0xFF5C, 0xFF6C, 0xFF7C,
    0xFF88, 0xFF90, 0xFF98, 0xFFA0, 0xFFA8, 0xFFB0, 0xFFB8, 0xFFC0, 0xFFC8, 0xFFD0, 0xFFD8, 0xFFE0, 0xFFE8, 0xFFF0, 0xFFF8, 0x0000,
    0x7D7C, 0x797C, 0x757C, 0x717C, 0x6D7C, 0x697C, 0x657C, 0x617C, 0x5D7C, 0x597C, 0x557C, 0x517C, 0x4D7C, 0x497C, 0x457C, 0x417C,
    0x3E7C, 0x3C7C, 0x3A7C, 0x387C, 0x367C, 0x347C, 0x327C, 0x307C, 0x2E7C, 0x2C7C, 0x2A7C, 0x287C, 0x267C, 0x247C, 0x227C, 0x207C,
    0x1EFC, 0x1DFC, 0x1CFC, 0x1BFC, 0x1AFC, 0x19FC, 0x18FC, 0x17FC, 0x16FC, 0x15FC, 0x14FC, 0x13FC, 0x12FC, 0x11FC, 0x10FC, 0x0FFC,
    0x0F3C, 0x0EBC, 0x0E3C, 0x0DBC, 0x0D3C, 0x0CBC, 0x0C3C, 0x0BBC, 0x0B3C, 0x0ABC, 0x0A3C, 0x09BC, 0x093C, 0x08BC, 0x083C, 0x07BC,
    0x075C, 0x071C, 0x06DC, 0x069C, 0x065C, 0x061C, 0x05DC, 0x059C, 0x055C, 0x051C, 0x04DC, 0x049C, 0x045C, 0x041C, 0x03DC, 0x039C,
    0x036C, 0x034C, 0x032C, 0x030C, 0x02EC, 0x02CC, 0x02AC, 0x028C, 0x026C, 0x024C, 0x022C, 0x020C, 0x01EC, 0x01CC, 0x01AC, 0x018C,
    0x0174, 0x0164, 0x0154, 0x0144, 0x0134, 0x0124, 0x0114, 0x0104, 0x00F4, 0x00E4, 0x00D4, 0x00C4, 0x00B4, 0x00A4, 0x0094, 0x0084,
    0x0078, 0x0070, 0x0068, 0x0060, 0x0058, 0x0050, 0x0048, 0x0040, 0x0038, 0x0030, 0x0028, 0x0020, 0x0018, 0x0010, 0x0008, 0x0000,
    0x0158, 0x0148, 0x0178, 0x0168, 0x0118, 0x0108, 0x0138, 0x0128, 0x01D8, 0x01C8, 0x01F8, 0x01E8, 0x0198, 0x0188, 0x01B8, 0x01A8, 
    0x0058, 0x0048, 0x0078, 0x0068, 0x0018, 0x0008, 0x0038, 0x0028, 0x00D8, 0x00C8, 0x00F8, 0x00E8, 0x0098, 0x0088, 0x00B8, 0x00A8, 
    0x0560, 0x0520, 0x05E0, 0x05A0, 0x0460, 0x0420, 0x04E0, 0x04A0, 0x0760, 0x0720, 0x07E0, 0x07A0, 0x0660, 0x0620, 0x06E0, 0x06A0, 
    0x02B0, 0x0290, 0x02F0, 0x02D0, 0x0230, 0x0210, 0x0270, 0x0250, 0x03B0, 0x0390, 0x03F0, 0x03D0, 0x0330, 0x0310, 0x0370, 0x0350
    };
    uint8_t g_opusOutputBuff[MAX_PACKET_SIZE] = {0};
    
    //
    // Set the clock frequency.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);
    
    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();
    
    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

#if defined(AM_BSP_NUM_BUTTONS) && defined(AM_BSP_NUM_LEDS)
    //
    // Configure the button pin.
    //
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON0, g_deepsleep_button0);
    
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
    //
    // Enable the GPIO/button interrupt.
    //
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
    //
    // Configure the LEDs.
    //
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
    
    //
    // Turn the LEDs off
    //
    for (int ix = 0; ix < AM_BSP_NUM_LEDS; ix++) 
    {
        am_devices_led_off(am_bsp_psLEDs, ix);
    }
    //
    // TimerA0 init.
    //
    timerA0_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)


#if AM_CMSIS_REGS
    NVIC_EnableIRQ(GPIO_IRQn);
    NVIC_EnableIRQ(CTIMER_IRQn);
#else   // AM_CMSIS_REGS
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);
#endif  // AM_CMSIS_REGS

    //
    // Enable interrupts to the core.
    //
    am_hal_interrupt_master_enable();
    
    // Turn on PDM
    pdm_init();
    
    //
    // Initialize the printf interface for UART output
    //
    am_bsp_uart_printf_enable();
    
    //
    // Print the banner.
    //
//    am_util_stdio_terminal_clear();
    DebugLog("Starting audio test\r\n\n");
    //
    // Start timer A0
    //
    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

    //
    // Opus codec init
    //
    g_opusEnc = opus_encoder_create((opus_int32)g_audioSampleRate, g_audioChannel, OPUS_APPLICATION_AUDIO, &g_opusErr);
    if (g_opusErr != OPUS_OK)
    {
        am_util_stdio_printf("Cannot create encoder: %s\r\n", opus_strerror(g_opusErr));
        while(1);
    }
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_BITRATE(bitrate_bps));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_MEDIUMBAND));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR(use_vbr));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_VBR_CONSTRAINT(cvbr));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_COMPLEXITY(g_opusComplexity));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_INBAND_FEC(use_inbandfec));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_FORCE_CHANNELS(forcechannels));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_DTX(use_dtx));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_PACKET_LOSS_PERC(packet_loss_perc));
    opus_encoder_ctl(g_opusEnc, OPUS_SET_LSB_DEPTH(16));
//    opus_encoder_ctl(g_opusEnc, OPUS_SET_EXPERT_FRAME_DURATION(variable_duration));

    DebugLog("Opus encoder initialization is finished!\r\n\n");
   
    g_opusEncRet = opus_encode(g_opusEnc, g_opusTestData, FRAME_SIZE, g_opusOutputBuff, MAX_PACKET_SIZE);
    if(g_opusEncRet < 0)
    {
        am_util_stdio_printf("encode failed: %s\r\n", opus_strerror(g_opusEncRet));
    }
    else
    {
        am_util_stdio_printf("encode finished: %d bytes is encoded.\r\n", g_opusEncRet);
    }

    while (1)
    {
//        am_hal_interrupt_master_disable();

         if (g_bPDMDataReady) 
        {
            g_bPDMDataReady = false;
            g_numFramesCaptured++;

            if (g_numFramesCaptured < NUM_FRAMES) 
            {
                pdm_data_get();  // Start converting the next set of PCM samples.
            }

            else 
            {
                g_numFramesCaptured = 0;
                g_audioRunningFlag = 0;
                am_hal_pdm_disable(PDMHandle);
                am_devices_led_off(am_bsp_psLEDs, 0);
                DebugLog("PDM data recording ends!\r\n");
            }
        }
        if (g_ui32TimerCount >=1)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 1);
        
        }
    //
    // Go to Deep Sleep.
    //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
