/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     TargetInfo.h
********************************************************************************
*
*     Description:  All target specific information
*
*     Copyright: (c) 2016 DSP Concepts, Inc. All rights reserved.
*                         1800 Wyatt Drive, Suite 14
*                         Sunnyvale, CA 95054
*
*******************************************************************************/
#ifndef _TARGETINFO_H
#define _TARGETINFO_H

// Version Information
#define VER_DAY                 20
#define VER_MONTH               10
#define VER_YEAR                17

#define CORE_ID                 0
#define CORE_SPEED              48e6f
#define SAMPLE_SPEED            48e6f
#define HAS_FLOAT_SUPPORT       1
#define HAS_FLASH_FILESYSTEM    0
#define NO_HW_INPUT_PINS        1
#define NO_HW_OUTPUT_PINS       1
#define IS_SMP                  0
#define NO_THREADS_SUPPORTED    2
#define FIXED_SAMPLE_RATE       16000.0f
#define IS_COMPLEX              0
#define SAMPLE_SIZE_IN_BYTES    4

/* ----------------------------------------------------------------------
** Specify the size of each of the heaps on this target
** ------------------------------------------------------------------- */
#define MASTER_HEAP_SIZE		(1024*9)
#define FASTB_HEAP_SIZE			(1024*8)
#define SLOW_HEAP_SIZE			(1024*1) 

/* ----------------------------------------------------------------------
** Specify communication buffer size
** ------------------------------------------------------------------- */
#define MAX_COMMAND_BUFFER_LEN  272

/* ----------------------------------------------------------------------
** Specify which modules to include on this target
** ------------------------------------------------------------------- */
#include "AM_2cm_FBF_SCNR_THF_NT_ModuleList.h"

#endif	// _TARGETINFO_H
