/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCMultiplierFract32.h
****************************************************************************
*
*     Description:  Mono x N-channel multiplier
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
 * @brief Mono x N-channel multiplier
 */

#ifndef _MOD_AGCMULTIPLIERFRACT32_H
#define _MOD_AGCMULTIPLIERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCMultiplierFract32_postShift 0x00000100
#define OFFSET_AGCMultiplierFract32_postShift 0x00000008

#define CLASSID_AGCMULTIPLIERFRACT32 (CLASS_ID_MODBASE + 131)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCMultiplierFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              postShift;           // Number of bits to shift
    
} awe_modAGCMultiplierFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCMultiplierFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCMultiplierFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCMULTIPLIERFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCMultiplierFract32Process(void *pInstance);

 

void awe_modAGCMultiplierFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCMULTIPLIERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
