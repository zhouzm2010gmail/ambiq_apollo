/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplexorFade.h
****************************************************************************
*
*     Description:  Selects one of N inputs with cross fading
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2017
*                   1800 Wyatt Drive, Suite 14
*                   Santa Clara, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Selects one of N inputs with cross fading
 */

#ifndef _MOD_MULTIPLEXORFADE_H
#define _MOD_MULTIPLEXORFADE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplexorFade_index 0x00000100
#define MASK_MultiplexorFade_smoothingTime 0x00000200
#define MASK_MultiplexorFade_smoothingCoeff 0x00000400
#define MASK_MultiplexorFade_currentIndex 0x00000800
#define MASK_MultiplexorFade_currentGain 0x00001000
#define OFFSET_MultiplexorFade_index 0x00000008
#define OFFSET_MultiplexorFade_smoothingTime 0x00000009
#define OFFSET_MultiplexorFade_smoothingCoeff 0x0000000A
#define OFFSET_MultiplexorFade_currentIndex 0x0000000B
#define OFFSET_MultiplexorFade_currentGain 0x0000000C

#define CLASSID_MULTIPLEXORFADE (CLASS_ID_MODBASE + 2029)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplexorFadeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              index;               // Specifies which input pin to route to the output. The index is zero based.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32              currentIndex;        // This is the index that is currently being used and the module smoothly transitions to index.
    FLOAT32            currentGain;         // Instantaneous gain being applied. This is an internal variable used in the smoothing process.
    
} awe_modMultiplexorFadeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplexorFadeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplexorFadeConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLEXORFADE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplexorFadeProcess(void *pInstance);

UINT32 awe_modMultiplexorFadeSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLEXORFADE_H

/**
 * @}
 *
 * End of file.
 */
