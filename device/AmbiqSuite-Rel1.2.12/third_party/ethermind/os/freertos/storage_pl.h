
/**
 *  \file storage_pl.h
 *
 *  Platform specific header file for persistant storage module.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_STORAGE_PL_
#define _H_STORAGE_PL_

/* --------------------------------------------- Header File Inclusion */
#include "BT_common.h"
#include "device_queue_pl.h"
#include "smp_pl.h"

/* --------------------------------------------- Global Definitions */
/* Platform/Appl module persistent storage IDs */
#define STORAGE_GATT_PID                         (STORAGE_NUM_PIDS + 0)

/* Number of platform/appl module persistent storage IDs */
#define STORAGE_NUM_PIDS_PL                      1

/* Platform/Appl module retention storage IDs */
#define STORAGE_GATT_RID                         (STORAGE_NUM_RIDS + 0)

/* Number of platform/appl module retention storage IDs */
#define STORAGE_NUM_RIDS_PL                      1

/* Persistent and Retention Array sizes */
#define STORAGE_PERSISTENT_ARRAY_SIZE            (STORAGE_NUM_PIDS + STORAGE_NUM_PIDS_PL)
#define STORAGE_RETENTION_ARRAY_SIZE             (STORAGE_NUM_RIDS + STORAGE_NUM_RIDS_PL)

/* Storage signature size */
#define STORAGE_SKEY_SIZE                        0

/* Storage access modes */
#define STORAGE_OPEN_MODE_WRITE                  0x00
#define STORAGE_OPEN_MODE_READ                   0x01

/* --------------------------------------------- Structures/Data Types */

/* --------------------------------------------- Macros */

/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */
void storage_bt_init_pl (void);
void storage_bt_shutdown_pl (void);

API_RESULT storage_open_pl (UCHAR type, UCHAR mode);
API_RESULT storage_close_pl (UCHAR type, UCHAR mode);

#ifdef STORAGE_CHECK_CONSISTENCY_ON_RESTORE
API_RESULT storage_check_consistency_pl(UCHAR type);
#else
#define storage_check_consistency_pl(type)
#endif /* STORAGE_CHECK_CONSISTENCY_ON_RESTORE */

INT16 storage_write_pl (UCHAR type, void * buffer, UINT16 size);
INT16 storage_read_pl (UCHAR type, void * buffer, UINT16 size);

INT16 storage_write_signature_pl (UCHAR type);
INT16 storage_read_signature_pl (UCHAR type);

#endif /* _H_STORAGE_PL_ */