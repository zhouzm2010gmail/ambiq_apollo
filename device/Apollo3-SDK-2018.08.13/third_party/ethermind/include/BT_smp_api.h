/**
 *  \file BT_smp_api.h
 *
 *  \brief This Header File contains the APIs exported by EtherMind Bluetooth
 *  Stack for the SMP Layer.
 */

/*
 *  Copyright (C) 2014. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_BT_SMP_API_
#define _H_BT_SMP_API_

/* -------------------------------------------- Header File Inclusion */
#include "BT_common.h"
#include "BT_device_queue.h"

/* -------------------------------------------- Global Definitions */

/**
 * \defgroup smp_module SMP (Security Manager Protocol)
 * \{
 *  This section describes the interfaces & APIs offered by the EtherMind
 *  Security Manager Protocol (SMP) module to the Application and other upper
 *  layers of the stack.
 */

/**
 * \defgroup smp_defines Defines
 * \{
 * This section describes the defines for SMP
 */

/**
 * \defgroup smp_constants Constants
 * \{
 *  This section describes the various constant defines used in SMP
 */

/** SMP Boolean True */
#define SMP_TRUE                                    BT_TRUE

/** SMP Boolean False */
#define SMP_FALSE                                   BT_FALSE

/** Invalid SMP Device handle */
#define SMP_BD_INVALID_HANDLE                       0xFF

/**
 * \defgroup smp_config Configurations
 * \{
 *  This section lists SMP configuration paramters as in specification
 */

#ifndef SMP_LESC
/** SMP L2CAP Channel Maximum Transfer Unit */
#define SMP_MTU                                     23
#else
#define SMP_MTU                                     65
#endif /* SMP_LESC */

/** SMP L2CAP Flush Timout, set to Infinite as per specification */
#define SMP_FLUSH_TIMEOUT                           0xFFFF

/** SMP L2CAP Quality of Service, set to Best Effort as per specification */
#define SMP_QOS                                     0x01 /* Best Effort (Default) */

/** SMP L2CAP operation mode, set to Basic Mode as per specification */
#define SMP_MODE                                    L2CAP_MODE_BASIC

/** SMP Procedure Timeout */
#define SMP_PROCEDURE_TIMEOUT                       30 /* Seconds */

/** \} */


/**
 * \defgroup smp_cmds Commands
 * \{
 *  This section lists the commands of SMP protcol defined by specification
 */

/** SMP Pairing Request Command Code */
#define SMP_CODE_PAIRING_REQUEST                    0x01

/** SMP Pairing Response Command Code */
#define SMP_CODE_PAIRING_RESPONSE                   0x02

/** SMP Pairing Confirm Command Code */
#define SMP_CODE_PAIRING_CONFIRM                    0x03

/** SMP Pairing Random Command Code */
#define SMP_CODE_PAIRING_RANDOM                     0x04

/** SMP Pairing Failed Command Code */
#define SMP_CODE_PAIRING_FAILED                     0x05

/** SMP Encryptino Information Command Code */
#define SMP_CODE_ENCRYPTION_INFORMATION             0x06

/** SMP Master Identification Command Code */
#define SMP_CODE_MASTER_IDENTIFICATION              0x07

/** SMP Identity Information Command Code */
#define SMP_CODE_IDENTITY_INFORMATION               0x08

/** SMP Identity Address Information Command Code */
#define SMP_CODE_IDENTITY_ADDRESS_INFORMATION       0x09

/** SMP Signing Information Command Code */
#define SMP_CODE_SIGNING_INFORMATION                0x0A

/** SMP Security Request Command Code */
#define SMP_CODE_SECURITY_REQUEST                   0x0B

#ifdef SMP_LESC
/** SMP Pairing Public Key  Code */
#define SMP_CODE_PAIRING_PUBLIC_KEY                 0x0C

/** SMP Pairing DHkey Check Code */
#define SMP_CODE_PAIRING_DHKEY_CHECK                0x0D

/** SMP Pairing Keypress notification Code */
#define SMP_CODE_PAIRING_KEYPRESS_NTF               0x0E
#endif /* SMP_LESC */

/** \} */


/**
 * \defgroup smp_security Security Procedure Constants
 * \{
 *  This section lists constants used in the security procedures of SMP
 */

/** LE Security Mode 1 */
#define SMP_SEC_MODE_1                              0x10

/** LE Security Mode 2 */
#define SMP_SEC_MODE_2                              0x20

/** LE Security Mode Mask */
#define SMP_SEC_MODE_MASK                           0xF0

/**
 * Level 0 -
 * For Mode 1: No Security (No Authentication & No Encryption)
 * For Mode 2: NA
 */
#define SMP_SEC_LEVEL_0                             0x00

/**
 * Level 1 -
 * For Mode 1: Unauthenticated pairing with encryption (No MITM)
 * For Mode 2: Unauthenticated pairing with data signing (No MITM)
 */
#define SMP_SEC_LEVEL_1                             0x01

/**
 * Level 2 -
 * For Mode 1: Authenticated pairing with encryption (With MITM)
 * For Mode 2: Authenticated pairing with data signing (With MITM)
 */
#define SMP_SEC_LEVEL_2                             0x02

#ifdef SMP_LESC
/**
 * Level 3 -
 * For Mode 1: Authenticated LE Secure Connections pairing with encryption
 * For Mode 2: ???
 */
#define SMP_SEC_LEVEL_3                             0x03
#endif /* SMP_LESC */

/** LE Security Level Mask */
#define SMP_SEC_LEVEL_MASK                          0x0F

#ifdef SMP_LESC
#define SMP_LEGACY_MODE                             0x01
#define SMP_LESC_MODE                               0x02

/** LE Pairing Mode Mask */
#define SMP_PAIRING_MODE_MASK                       0x03
#endif /* SMP_LESC */

#ifdef SMP_LESC
/** LE Secure Connection Bit */
#define SMP_SEC_LESC                                0x80
#define SMP_LESC_AUTH_REQ_BIT_SET_MASK              0x08
#define SMP_LESC_KEY_PRESS_AUTH_REQ_BIT_SET_MASK    0x10
#endif /* SMP_LESC */

/** SMP No Bonding support */
#define SMP_BONDING_NONE                            0x00

/** SMP availability of Bonding support */
#define SMP_BONDING                                 0x01

/** SMP Display Only IO Capability */
#define SMP_IOCAP_DISPLAY_ONLY                      0x00

/** SMP Display Yes/No IO Capability */
#define SMP_IOCAP_DISPLAY_YESNO                     0x01

/** SMP Keyboard Only IO Capability */
#define SMP_IOCAP_KEYBOARD_ONLY                     0x02

/** SMP No IO Capability */
#define SMP_IOCAP_NOINPUT_NOOUTPUT                  0x03

/** SMP Keyboard Display IO Capability */
#define SMP_IOCAP_KEYBOARD_DISPLAY                  0x04

/** SMP Unavailability of OOB Data */
#define SMP_OOB_AUTH_DATA_UNAVAILABLE               0x00

/** SMP Availability of OOB Data */
#define SMP_OOB_AUTH_DATA_AVAILABLE                 0x01

/**
 * SMP Encryption Key bit-mask, to indicate LTK, EDIV and RAND sharing during
 * the key distribution
 */
#define SMP_DIST_MASK_ENC_KEY                       0x01

/**
 * SMP Id Key bit-mask, to indicate IRK and Address sharing during
 * the key distribution
 */
#define SMP_DIST_MASK_ID_KEY                        0x02

/**
 * SMP Sign bit-mask, to indicate CSRK sharing during the key distribution
 */
#define SMP_DIST_MASK_SIGN_KEY                      0x04


/**
 * SMP Minimum Encryption Key size that can be supported
 */
#define SMP_MIN_ENCRYPTION_KEY_SIZE                 7

/**
* SMP Maximum Encryption Key size that can be supported
*/
#define SMP_MAX_ENCRYPTION_KEY_SIZE                 16

/** SMP Entity Authentication state masks for security attribute */
#define SMP_ENTITY_AUTH_OFF                         0x00
#define SMP_ENTITY_AUTH_IN_PROGRESS                 0x01
#define SMP_ENTITY_AUTH_ON                          0x02
#define SMP_ENTITY_AUTH_MASK                        0xFC

#ifdef SMP_LESC
/* SMP Numeric Key Comparison User Response Types */
#define SMP_NUM_COMP_CNF_POSITIVE                   0x00
#define SMP_NUM_COMP_CNF_NEGATIVE                   0x01
#endif /* SMP_LESC */

/** \} */


/**
 * \defgroup smp_key_size Key size Constants
 * \{
 *  This section lists the sizes of different keys used in SMP
 */

/** User Passkey size */
#define SMP_USER_PASSKEY_SIZE                       6

/** Identity Address data size */
#define SMP_IDADDR_SIZE                             7

/** Identity Resolving Key size */
#define SMP_IRK_SIZE                                16

/** Connection Signature Resolving key size */
#define SMP_CSRK_SIZE                               16

/** Long Term Key Size size */
#define SMP_LTK_SIZE                                16

/** Encrypted Diversifier size */
#define SMP_EDIV_SIZE                               2

/** 24 Bit Random Number size */
#define SMP_RAND_24B_SIZE                           3

/** 64 Bit Random Number size */
#define SMP_RAND_64B_SIZE                           8

/** 128 Bit Random Number size */
#define SMP_RAND_128B_SIZE                          16

#ifdef SMP_LESC
/* 64 Byte Public Key */
#define SMP_LESC_PUBLIC_KEY_SIZE                    64

/* 32 Byte Public Key X Coordinate */
#define SMP_LESC_PUBLIC_KEY_X_SIZE                  32

/* 32 Byte Public Key Y Coordinate */
#define SMP_LESC_PUBLIC_KEY_Y_SIZE                  32

/* 256 bit DHkey */
#define SMP_LESC_DHKEY_SIZE                         32

/* 32 Byte Private Key */
#define SMP_LESC_PRIVATE_KEY_SIZE                   32

/* 128 bit MACKEY */
#define SMP_LESC_MACKEY_SIZE                        16
#endif /* SMP_LESC */

/** \} */

/**
 * \defgroup smp_sign_consts Signing Constants
 * \{
 *  This section lists the sizes of different constants used in SMP data signing
 */

/* Generate signature action */
#define SMP_SIGN_GENERATE                           0x00

/* Verify signature action */
#define SMP_SIGN_VERIFY                             0x01

/** 64 Bit signature Message Authentication Code size */
#define SMP_SIGN_MAC_SIZE                           8
/**
 * NOTE: 'TO BE Depricated'
 * Having the old Signature MAC size definition for Appl Backward compatibility.
 */
#define SMP_MAC_SIZE                                SMP_SIGN_MAC_SIZE

/** \} */

/**
 * \defgroup smp_aes_cmac_operations AES CMAC operations
 * \{
 *  This section lists the types of different operations used in SMP AES CMAC
 */
#define SMP_AES_CMAC_SIGN_OP                        0x81
#define SMP_AES_CMAC_LESC_CONF_VAL_GEN_OP           0x82
#define SMP_AES_CMAC_LESC_T_KEY_GEN_OP              0x83
#define SMP_AES_CMAC_LESC_LTK_GEN_OP                0x84
#define SMP_AES_CMAC_LESC_MACKEY_GEN_OP             0x85
#define SMP_AES_CMAC_LESC_CHK_VAL_GEN_OP            0x86
#define SMP_AES_CMAC_LESC_NUM_COMP_VAL_GEN_OP       0x87
#define SMP_AES_CMAC_LESC_LINK_KEY_CONV_OP          0x88
#define SMP_AES_CMAC_INVALID_OP                     0xFF
/** \} */

/** 128 Bit AES_CMAC Message Authentication Code size */
#define SMP_AES_CMAC_MAC_SIZE                       16

/**
 * \defgroup smp_reply_cmds Reply Command Codes
 * \{
 *  This section describes SMP parameter request reply command codes
 */

/** SMP Authentication Request Reply command */
#define SMP_AUTHENTICATION_REQUEST_REPLY            0x81

/** SMP Passkey Entry Request Reply command */
#define SMP_PASSKEY_ENTRY_REQUEST_REPLY             0x82

/** SMP Long Term Key Request Reply command */
#define SMP_LONG_TERM_KEY_REQUEST_REPLY             0x83

/** SMP Key Exchange Info Request Reply command */
#define SMP_KEY_EXCHANGE_INFO_REQUEST_REPLY         0x84

#ifdef SMP_LESC
/** SMP Numeric Comparision generation */
#define SMP_NKEY_COMP_GEN                           0x85

/** SMP LESC Key Generation */
#define SMP_LESC_KEY_GENERATION                     0x86

/** SMP Numeric Comparision User Confirmation */
#define SMP_NKEY_COMP_CNF_USER_REPLY                0x87

/** SMP PASSKEY Key Press Notification Command */
#define SMP_LESC_KEY_PRESS_NTF                      0x88
#endif /* SMP_LESC */

/** \} */

/** \} */

/** \} */

/**
 * \defgroup smp_error_code Error Codes
 * \{
 *  This section describes the various error codes used in SMP
 */

/**
 * No Error
 */
#define SMP_ERROR_NONE                              0x00

/**
 * User input of passkey failed, for example, the user cancelled the operation
 */
#define SMP_ERROR_PASSKEY_ENTRY_FAILED              0x01

/**
 * Out Of Band data is not available
 */
#define SMP_ERROR_OOB_NOT_AVAILABLE                 0x02

/**
 * Pairing procedure cannot be performed as authentication
 * requirements cannot be met due to IO capabilities of one or both devices
 */
#define SMP_ERROR_AUTHENTICATION_REQUIREMENTS       0x03

/**
 * Confirm value does not match the calculated compare value
 */
#define SMP_ERROR_CONFIRM_VALUE_FAILED              0x04

/**
 * Pairing is not supported by the device
 */
#define SMP_ERROR_PAIRING_NOT_SUPPORTED             0x05

/**
 * Insufficient key size for the security requirements of this device
 */
#define SMP_ERROR_ENCRYPTION_KEY_SIZE               0x06

/**
 * SMP command received is not supported
 */
#define SMP_ERROR_COMMAND_NOT_SUPPORTED             0x07

/**
 * Pairing failed due to an unspecified reason
 */
#define SMP_ERROR_UNSPECIFIED_REASON                0x08

/**
 * Pairing or authentication procedure is disallowed because too little time
 * has elapsed since last pairing request or security request
 */
#define SMP_ERROR_REPEATED_ATTEMTS                  0x09

/**
 * Invalid Parameters in Request - Invalid Command length and Parameter value
 * outside range
 */
#define SMP_ERROR_INVALID_PARAMETERS                0x0A

#ifdef SMP_LESC
/**
 * Pairing Failed due to DH key check failed
 */
#define SMP_ERROR_DHKEY_CHECK_FAILED               0x0B

/**
 * Pairing Failed due to Numeric Comparision Failed
 */
#define SMP_ERROR_NUMERIC_COMPARISON_FAILED        0x0C

/**
 * Pairing Failed due to BR/EDR pairing process in progress
 */
#define SMP_ERROR_BREDR_PAIRING_IN_PROGRESS        0x0D

/**
 * Pairing Failed due to CrossTransport Key generation not allowed
 */
#define SMP_ERROR_CT_KEY_GEN_NOT_ALLOWED           0x0E
#endif /* SMP_LESC */

/** \} */

/**
 * \defgroup smp_events Events
 * \{
 *  This section describes the events notified through
 *  \ref SMP_UI_NOTIFY_CB callback.
 */

/**
 * This event indicates Authentication procedure is completed, with the
 * following values as parameters in the \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_AUTHENTICATION_COMPLETE
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to object of type \ref SMP_AUTH_INFO,
 * 'param' member unused. In case of encryption initiated with BT_smp_encrypt
 * API, the event_data will be NULL. In case result is not API_SUCCESS, this
 * may be NULL and shall be ignored
 * \param [in] event_datalen  size of \ref SMP_AUTH_INFO. In case of encryption
 * initiated with BT_smp_encrypt API, the event_datalen will be zero. In case
 * result is not API_SUCCESS, this may be zero and shall be ignored
 *
 * \return \ref API_SUCCESS (always)
 */
#define SMP_AUTHENTICATION_COMPLETE                 0x01

/**
 * This event indicates Authentication Request received from the peer device,
 * with the following values as parameters in the \ref SMP_UI_NOTIFY_CB
 * callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_AUTHENTICATION_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to object of type \ref SMP_AUTH_INFO,
 * 'param' member unused
 * \param [in] event_datalen  size of \ref SMP_AUTH_INFO
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to reply using the
 * \ref BT_smp_authentication_request_reply API
 */
#define SMP_AUTHENTICATION_REQUEST                  0x02

/**
 * This event indicates SMP has requested for a passkey to be used during
 * the pairing procedure, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_PASSKEY_ENTRY_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  NULL
 * \param [in] event_datalen  0
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to reply using the
 * \ref BT_smp_passkey_entry_request_reply API
 */
#define SMP_PASSKEY_ENTRY_REQUEST                   0x03

/**
 * This event indicates SMP has requested to display passkey during
 * the pairing procedure, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_PASSKEY_DISPLAY_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to UINT32 type decimal passkey value
 * \param [in] event_datalen  sizeof (UINT32)
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note In case if the application does not have an actual display but intends
 * to have MITM protection using SMP_IOCAP_DISPLAY_ONLY IO Capability, it would
 * require the application to have a fixed 6 digit passkey in its manual that
 * will be shared with the peer device in an Out of Band fashion.
 *
 * To enable the SMP to use this fixed application passkey instead of the
 * generated passkey for the pairing algorithm computations, the application
 * shall update the 'event_data' pointer to assign the required passkey and
 * update the callback return value to SMP_DISPLAY_PASSKEY_UPDATED as
 * illustrated below
 *
 *     *((UINT32 *)event_data) = APPL_SMP_PASSKEY;
 *     return SMP_DISPLAY_PASSKEY_UPDATED;
 */
#define SMP_PASSKEY_DISPLAY_REQUEST                 0x04

/**
 * This event indicates that peer Master device has started an encryption
 * procedure, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback. This event is valid only when the local
 * device is Slave to the LE physical link.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_LONG_TERM_KEY_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  RAND and EDIV Byte stream as interpreted below
 *        byte[0-7] - 8 octet RAND value
 *        byte[8-9] - 2 octect Encrypted Diversifier
 * \param [in] event_datalen  0
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to reply using the
 * \ref BT_smp_long_term_key_request_reply API
 */
#define SMP_LONG_TERM_KEY_REQUEST                   0x05

/**
 * This event indicates that pairing procedure has requested for Key
 * Exchange Information, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_KEY_EXCHANGE_INFO_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to the structure \ref SMP_KEY_XCHG_PARAM,
 * where
 *  - 'keys' refers to the local key distribution negotiated
 *  - 'ekey_size' refers to the encryption key size negotiated
 *  - 'keys_info' pointer member shall be ignored
 * \param [in] event_datalen  sizeof \ref SMP_KEY_XCHG_PARAM
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to reply using the
 * \ref BT_smp_key_exchange_info_request_reply API
 */
#define SMP_KEY_EXCHANGE_INFO_REQUEST               0x06

/**
 * This event indicates that pairing procedure is notifying Key exchange data
 * of peer device, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_KEY_EXCHANGE_INFO
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to the structure \ref SMP_KEY_XCHG_PARAM,
 * where
 *  - 'keys' refers to the peer key distribution negotiated
 *  - 'ekey_size' refers to the encryption key size negotiated, may be ignored
 *  - 'keys_info' points to the structure \ref SMP_KEY_DIST
 * \param [in] event_datalen  sizeof \ref SMP_KEY_XCHG_PARAM
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to store the keys
 * that may be required for future procedures
 */
#define SMP_KEY_EXCHANGE_INFO                       0x07

/**
 * This event indicates that the resolvable private address is created
 * for the local device, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to invalid device handle
 * \ref SMP_BD_INVALID_HANDLE
 * \param [in] event  \ref SMP_RESOLVABLE_PVT_ADDR_CREATE_CNF
 * \param [in] bd_addr  Private address created
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  BD Address created
 * \param [in] event_datalen  \ref BT_BD_ADDR_SIZE
 *
 * \return \ref API_SUCCESS (always)
 */
#define SMP_RESOLVABLE_PVT_ADDR_CREATE_CNF            0x08

/**
 * This event indicates that the resolvable private address is verified
 * for the Identity Resolving Key set, with the following values as parameters
 * in the \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to invalid device handle \ref SMP_BD_INVALID_HANDLE
 * \param [in] event  \ref SMP_RESOLVABLE_PVT_ADDR_VERIFY_CNF
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  BD Address verified
 * \param [in] event_datalen  \ref BT_BD_ADDR_SIZE
 *
 * \return \ref API_SUCCESS (always)
 */
#define SMP_RESOLVABLE_PVT_ADDR_VERIFY_CNF            0x09

/**
 * This event indicates the completion of signature generation for a data that
 * was input to be signed, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] event  \ref SMP_DATA_SIGNING_COMPLETE
 * \param [in] bd_addr  Peer device address information
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Signature byte stream. The last 8 octects represent
 * the generated MAC
 * \param [in] event_datalen  Number of bytes in event_data
 *
 * \return \ref API_SUCCESS (always)
 */
#define SMP_DATA_SIGNING_COMPLETE                     0x0A

/**
 * This event indicates the completion of verification of signed data received
 * from peer device, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] event  \ref SMP_SIGN_DATA_VERIFICATION_COMPLETE
 * \param [in] bd_addr  Peer device address information
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Signature byte stream. The last 8 octects represent
 * the generated MAC
 * \param [in] event_datalen  Number of bytes in event_data
 *
 * \return \ref API_SUCCESS (always)
 */
#define SMP_SIGN_DATA_VERIFICATION_COMPLETE           0x0B

#ifdef SMP_LESC
/**
 * This event indicates SMP has requested for a numeric comparison to be used during
 * the pairing procedure, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_NUMERIC_KEY_COMPARISON_CNF_REQUEST
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to UINT32 type numeric comparison value
 * \param [in] event_datalen  sizeof (UINT32)
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note On receiving this event, the application is expected to reply using the
 * \ref BT_smp_nkey_comp_cnf_reply API
 */
#define SMP_NUMERIC_KEY_COMPARISON_CNF_REQUEST        0x0C

/**
 * This event indicates that pairing procedure is notifying KeyPress Events
 * of peer device, with the following values as parameters in the
 * \ref SMP_UI_NOTIFY_CB callback.
 *
 * \param [in] bd_handle  Pointer to peer device handle \ref SMP_BD_HANDLE
 * \param [in] event  \ref SMP_KEY_PRESS_NOTIFICATION_EVENT
 * \param [in] result  \ref API_SUCCESS on successful procedure completion, else
 * an Error Code
 * \param [in] event_data  Pointer to UCHAR type KeyPress notification values
 * \param [in] event_datalen  sizeof (UCHAR)
 *
 * \return \ref API_SUCCESS (always)
 *
 * \note This event is an informative event for the Upper Layer
 */
#define SMP_KEY_PRESS_NOTIFICATION_EVENT              0x0D
#endif /* SMP_LESC */

/**
 * This event indicates an invalid event received through
 * \ref SMP_UI_NOTIFY_CB callback.
 */
#define SMP_EVENT_INVALID                             0xFF

/** \} */

/* -------------------------------------------- Macros */
/**
 * \defgroup smp_utility_macros Utility macros
 * \{
 * This section defines utility macros for SMP
 */

/**
 * This macro can be used to pack one byte parameter into little endian format.
 */
#define smp_pack_1_byte_param      BT_PACK_LE_1_BYTE

/**
 * This macro can be used to pack two byte parameter into little endian format.
 */
#define smp_pack_2_byte_param      BT_PACK_LE_2_BYTE

/**
 * This macro can be used to pack three byte parameter into little endian format.
 */
#define smp_pack_3_byte_param      BT_PACK_LE_3_BYTE

/**
 * This macro can be used to pack four byte parameter into little endian format.
 */
#define smp_pack_4_byte_param      BT_PACK_LE_4_BYTE

/**
 * This macro can be used to unpack one byte little endian formated parameter.
 */
#define smp_unpack_1_byte_param    BT_UNPACK_LE_1_BYTE

/**
 * This macro can be used to unpack two byte little endian formated parameter.
 */
#define smp_unpack_2_byte_param    BT_UNPACK_LE_2_BYTE

/**
 * This macro can be used to unpack three byte little endian formated parameter.
 */
#define smp_unpack_3_byte_param    BT_UNPACK_LE_3_BYTE

/**
 * This macro can be used to unpack four byte little endian formated parameter.
 */
#define smp_unpack_4_byte_param    BT_UNPACK_LE_4_BYTE

/**
 * This macro validates a Bluetooth device address type as in \ref SMP_BD_ADDR
 */ /* TODO: Make it generic across LE */
#define SMP_IS_VALID_BD_ADDR(bd_addr)                                       \
    (((NULL != (bd_addr)) && (BT_BD_RANDOM_ADDRESS_TYPE >= (bd_addr)->type))?  \
    (SMP_TRUE): (SMP_FALSE))

/**
 * This macro validates a Bluetooth device handle type as in \ref SMP_BD_HANDLE
 */ /* TODO: Make it generic across LE */
#define SMP_IS_VALID_BD_HANDLE(bd_handle) \
    (((NULL != (bd_handle)) && (0xFF != *(bd_handle)))? (SMP_TRUE): (SMP_FALSE))

/**
 * \}
 */

/**
 * \addtogroup smp_defines Defines
 * \{
 */

/**
 * \defgroup smp_structures Structures
 * \{
 * This section defines the structures used in SMP.
 */

/* -------------------------------------------- Structures/Data Types */
/** SMP Device BD Address type */
typedef BT_DEVICE_ADDR SMP_BD_ADDR;

/** SMP device handle type */
typedef DEVICE_HANDLE SMP_BD_HANDLE;

/** Authentication Parameters Information type for Security calls */
typedef struct _SMP_AUTH_INFO
{
    /**
     * Security Mode setting:
     * (\ref SMP_SEC_MODE_1, \ref SMP_SEC_LEVEL_0)
     * (\ref SMP_SEC_MODE_1, \ref SMP_SEC_LEVEL_1)
     * (\ref SMP_SEC_MODE_1, \ref SMP_SEC_LEVEL_2)
     * (\ref SMP_SEC_MODE_2, \ref SMP_SEC_LEVEL_1)
     * (\ref SMP_SEC_MODE_2, \ref SMP_SEC_LEVEL_2)
     */
    UCHAR    security;

#ifdef SMP_LESC
    /**
     * Pairing Mode:
     * \ref SMP_LEGACY_MODE
     * \ref SMP_LESC_MODE
     */
    UCHAR    pair_mode;
#endif /* SMP_LESC */

    /**
     * Bonding Type setting:
     * \ref SMP_BONDING_NONE
     * \ref SMP_BONDING
     */
    UCHAR    bonding;

    /**
     * Encryption Key Size
     */
    UCHAR    ekey_size;

    /**
     * Parameter with related information based on API/Event
     */
    UCHAR    param;

} SMP_AUTH_INFO;


/** Security Manager Key Distribution data */
typedef struct _SMP_KEY_DIST
{
    /** Long Term Key */
    UCHAR enc_info[SMP_LTK_SIZE];

    /** Encrypted Diversifier and Randdom Number */
    UCHAR mid_info[SMP_EDIV_SIZE + SMP_RAND_64B_SIZE];

    /** Identity Resolving Key */
    UCHAR id_info[SMP_IRK_SIZE];

    /** Public device/Static Random address type */
    UCHAR id_addr_info[SMP_IDADDR_SIZE];

    /** Connection Signature Resolving Key */
    UCHAR sign_info[SMP_CSRK_SIZE];

} SMP_KEY_DIST;


/** Key Exchange Parameter */
typedef struct _SMP_KEY_XCHG_PARAM
{
    /** Peer Key Information */
    SMP_KEY_DIST * keys_info;

    /**
     * Negotiated Local/Peer Key distribution
     *
     * Bit 0: Encryption information
     * Bit 1: Identity information
     * Bit 2: Signature Key
     * Bit 3-7: Reserved
     */
    UCHAR keys;

    /** Negotiated Encryption Key size */
    UCHAR ekey_size;

} SMP_KEY_XCHG_PARAM;


#ifdef HOST_RESOLVE_PVT_ADDR
/** SMP Host Address Resolution Information */
typedef struct _SMP_RPA_RESOLV_INFO
{
    /** The new address of peer device being resolved */
    BT_DEVICE_ADDR n_addr;

    /** Existing old address of the peer device */
    BT_DEVICE_ADDR o_addr;

    /** Device handle of peer device in stack */
    SMP_BD_HANDLE bd_handle;

} SMP_RPA_RESOLV_INFO;
#endif /* HOST_RESOLVE_PVT_ADDR */

/** \} */

/** \} */

/**
 * \defgroup smp_callback Application Callback
 * \{
 * This section defines the callback through which SMP provides asyncrhonous
 * notifications to application/higher layers.
 */

/**
 * SMP User Interface Notification Callback.
 * Security Manager Protocol calls the registered callback
 * to indicate events occured.
 *
 * \param [in] bd_handle      Pointer to peer device handle as in \ref SMP_BD_HANDLE
 * \param [in] event_type     Any of the Event occured from the list at \ref smp_events.
 * \param [in] event_result   \ref API_SUCCESS or an error code in \ref smp_error_code or any
 *                           other internal error code from the stack.
 * \param [in] event_data     Data associated with the event if any or NULL.
 * \param [in] event_datalen  Size of the event data. 0 if event data is NULL.
 */
typedef API_RESULT (* SMP_UI_NOTIFY_CB)
                   (
                       /* IN */ SMP_BD_HANDLE * bd_handle,
                       /* IN */ UCHAR           event_type,
                       /* IN */ UINT16          event_result,
                       /* IN */ void          * event_data,
                       /* IN */ UINT16          event_datalen
                   ) DECL_REENTRANT;

#ifdef HOST_RESOLVE_PVT_ADDR
/**
 * SMP Private Address Resolution complete callback.
 * Security Manager Protocol calls the registered callback
 * to indicate address resolution procedure completion.
 *
 * \param [in] rpa_info  Pointer to resolved rpa info structure as in \ref SMP_RPA_RESOLV_INFO
 * \param [in] status    Resolution status
 */
typedef void (* SMP_PVT_ADDR_RESOLV_COMPLETE_CB)
             (
                 /* IN */ SMP_RPA_RESOLV_INFO * rpa_info,
                 /* IN */ UINT16  status
             ) DECL_REENTRANT;
#endif /* HOST_RESOLVE_PVT_ADDR */

#ifdef SMP_TBX_TEST_LESC_FUNCTIONS
/**
 * SMP Application AES CMAC Utility callback.
 * Security Manager Protocol calls the registered callback
 * to indicate AES CMAC procedure completion.
 * This Callback is used by the application only to test
 * the SMP LE Secure Connections security Algorithms which makes use of
 * AES CMAC module. This is controlled by the feature flag
 * SMP_TBX_TEST_LESC_FUNCTIONS.
 *
 * \param [in] plain_text       Pointer to plain text
 * \param [in] plain_text_len   Length of the plain text data
 * \param [in] key              Key with with plain text is encrypted
 * \param [in] op               The type of Algorithm/operation the
 *                             plain text is part off
 * \param [out] enc_out         Pointer to hold the Encrypted Plain text output
 */
typedef void (* SMP_APPL_AES_CMAC_UTILITY_CB)
             (
                 /* IN */  UCHAR  * plain_text,
                 /* IN */  UINT16   plain_text_len,
                 /* IN */  UCHAR  * key,
                 /* IN */  UCHAR    op,
                 /* OUT */ UCHAR  * enc_out
             ) DECL_REENTRANT;
#endif /* SMP_TBX_TEST_LESC_FUNCTIONS */

/** \} */

/* -------------------------------------------- Macros */

/* -------------------------------------------- Internal Functions */

/* -------------------------------------------- API Declarations */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * \cond ignore_this Ignore this block while generating doxygen document
 */
API_RESULT BT_smp_param_request_reply
           (
               /* IN */ SMP_BD_HANDLE   * bd_handle,
               /* IN */ UCHAR              command,
               /* IN */ void             * param,
               /* IN */ UINT16             size
           );
/**
 * \endcond
 */


/**
 * \defgroup smp_api_defs API Definitions
 * \{
 *  This section describes API for SMP.
 */

/**
 * \brief To register SMP event handler callback function
 *
 * \par Description:
 *      This function registers a SMP event handler callback function.
 *
 * \param [in] smp_notify_cb  Function pointer to SMP event handler
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
API_RESULT BT_smp_register_user_interface
           (
               /* IN */ SMP_UI_NOTIFY_CB     smp_notify_cb
           );

#ifdef SMP_LESC
/**
 * \brief To enable BT LE 4.2 Secure Connections pairing mode
 *
 * \par Description:
 *      This function enables/disables the BT LE 4.2 Secure
 *      Connections
 *
 * \param [in] lesc_mode  Flag to enable or disable request for
 *        SMP LE Secure Connections mode. Valid input values are:
 *        SMP_TURE  - To enable SMP LESC mode
 *        SMP_FLASE - To Disable SMP LESC mode
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
API_RESULT BT_smp_set_lesc_pairing_mode
           (
               /* IN */ UCHAR  lesc_mode
           );
#endif /* SMP_LESC */

/**
 * \brief To intiate authentication/pairing procedure
 *
 * \par Description:
 *      This API starts authentication/pairing procedure with remote device.
 *      If local device is Master for the link, the pairing request is sent
 *      if the remote device is not authenctiated, LTK is not available or
 *      authentication is requested with higher security requirement.
 *      Otherwise link encryption/re-encryption procedure is initiated.
 *      If local device is Slave for the link, a Security Request is sent.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] auth_info  Authentication Information to be used as in
 * \ref SMP_AUTH_INFO, 'param' member unused
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \note If SMP feature SMP_NO_STORED_KEYS is enabled, this API sends pairing
 * request to peer only for a new unbonded pairing or if the requested security
 * is greater than the current security level with the device. To encrypt the
 * link with bonded information, BT_smp_encrypt API is enabled in this case.
 *
 * \sa smp_events
 */
API_RESULT BT_smp_authenticate
           (
               /* IN */ SMP_BD_HANDLE  * bd_handle,
               /* IN */ SMP_AUTH_INFO  * auth_info
           );


/**
 * \brief To intiate encryption procedure
 *
 * \par Description:
 *      This API starts encryption procedure with remote device, with given
 *      Random Number, Encryption Diversifier and Long Term Keys.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] n_rand  Random Number
 * \param [in] ediv    Encryption Diversifier
 * \param [in] ltk     Long Term Key
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \note This API is enabled by defining SMP feature flag
 * SMP_HAVE_ENCRYPT_API
 *
 * \sa smp_events
 */
API_RESULT BT_smp_encrypt
           (
               /* IN */ SMP_BD_HANDLE   * bd_handle,
               /* IN */ UCHAR           * n_rand,
               /* IN */ UINT16            ediv,
               /* IN */ UCHAR           * ltk
           );

/**
 * \brief To reply to authentication and security requests from peer
 *
 * \par Description:
 *      This API can be used to send the authentication request reply.
 *      This API must be used to reply when Security Manager Protocol calls the
 *      registered UI Notification Callback with \ref SMP_AUTHENTICATION_REQUEST
 *      as the event identifier. The application can send either a positive or
 *      a negative reply.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] auth_info  Pointer to Authentication Information to be used as in
 * \ref SMP_AUTH_INFO, 'param' member referring to Accept
 * (with \ref SMP_ERROR_NONE) or Reject (with specific Error Code)
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_authentication_request_reply(bd_handle, auth_info)   \
        BT_smp_param_request_reply                                  \
        ((bd_handle), SMP_AUTHENTICATION_REQUEST_REPLY,             \
        (auth_info), sizeof (SMP_AUTH_INFO))

/**
 * \brief To reply to passkey entry request from SMP
 *
 * \par Description:
 *      This API enables application to enter passkey for authentication
 *      procedure. This API must be used to reply when Security Manager
 *      Protocol calls the registered UI Notification Callback with \ref
 *      SMP_PASSKEY_ENTRY_REQUEST as the event identifier. The application
 *      should send the passkey which is being displayed on remote device
 *      or the passkey on which both the device agree upon.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] pass_key  Pointer to the 6 digit UINT32 decimal passkey
 *
 * \param [in] status  \ref SMP_TRUE - Accept, \ref SMP_FALSE - Reject
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_passkey_entry_request_reply(bd_handle, pass_key, status) \
        BT_smp_param_request_reply                                      \
        ((bd_handle), SMP_PASSKEY_ENTRY_REQUEST_REPLY,                  \
        (SMP_TRUE == (status))? (pass_key): NULL,                       \
        (SMP_TRUE == (status))? sizeof(UINT32): 0)                      \

/**
 * \brief To reply to Long Term Key request from SMP
 *        (Applicable only if local device is Slave)
 *
 * \par Description:
 *      This API enables application to enter the Long Term Key when the peer
 *      Master device has initiated and Encryption procedure. This API must be
 *      used to reply when Security Manager Protocol calls the registered UI
 *      Notification Callback with \ref SMP_LONG_TERM_KEY_REQUEST as the event
 *      identifier. The application should send the 128 bits Long Term Key
 *      generated for the peer device during pairing which maps with the
 *      Encryption DiverSifier and Random Number received in the above event.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] ltk  Pointer to the 128 bit LongTermKey array
 *
 * \param [in] status  \ref SMP_TRUE - Accept, \ref SMP_FALSE - Reject
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_long_term_key_request_reply(bd_handle, ltk, status)      \
        BT_smp_param_request_reply                                      \
        ((bd_handle), SMP_LONG_TERM_KEY_REQUEST_REPLY,                  \
        (SMP_TRUE == (status))? (ltk): NULL,                            \
        (SMP_TRUE == (status))? SMP_LTK_SIZE: 0)

/**
 * \brief To reply to Key Exchange Information Request from SMP
 *
 * \par Description:
 *      This API enables the application to reply when the Security Manager
 *      Protocol calls the registered UI Notification Callback with
 *      \ref SMP_KEY_EXCHANGE_INFO_REQUEST as the event identifier.
 *      The application should send the \ref SMP_KEY_DIST element
 *      after populating members with appropriate data.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] key_info  Pointer to the \ref SMP_KEY_DIST type structure
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_key_exchange_info_request_reply(bd_handle, key_info)     \
        BT_smp_param_request_reply                                      \
        ((bd_handle), SMP_KEY_EXCHANGE_INFO_REQUEST_REPLY,              \
        (key_info), sizeof (SMP_KEY_DIST))

#ifdef SMP_LESC
/**
 * \brief To reply to Numeric Key Comparison request from SMP
 *
 * \par Description:
 *      This API enables application to confirm numeric Key for authentication
 *      procedure. This API must be used to reply when Security Manager
 *      Protocol calls the registered UI Notification Callback with \ref
 *      SMP_NUMERIC_KEY_COMPARISON_CNF_REQUEST as the event identifier.
 *      The application should confirm if the Numeric Key Value which is being
 *      displayed on the local device matches with that shown on the remote
 *      device.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] status  \ref SMP_TRUE - Accept, \ref SMP_FALSE - Reject
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_nkey_comp_cnf_reply(bd_handle, status)                        \
        BT_smp_param_request_reply                                           \
        ((bd_handle), SMP_NKEY_COMP_CNF_USER_REPLY,                          \
        (status),                                                            \
        sizeof(UCHAR))

/**
 * \brief To send SMP Key Press Notification to Peer
 *
 * \par Description:
 *      This API enables application to send Keypress Notifications to Peer.
 *      This API must be used to reply when Security Manager
 *      Protocol calls the registered UI Notification Callback with \ref
 *      SMP_PASSKEY_ENTRY_REQUEST as the event identifier.
 *      The application should use this to inform peer of relevant Keypress
 *      status.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] ntf_val  KeyPress Notification Values
 *        \ref SMP_LESC_PASSKEY_ENTRY_STARTED   - Passkey entry started
 *        \ref SMP_LESC_PASSKEY_DIGIT_ENTERED   - Passkey digit entered
 *        \ref SMP_LESC_PASSKEY_DIGIT_ERASED    - Passkey digit erased
 *        \ref SMP_LESC_PASSKEY_CLEARED         - Passkey cleared
 *        \ref SMP_LESC_PASSKEY_ENTRY_COMPLETED - Passkey entry complete
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define BT_smp_keypress_notification(bd_handle, ntf_val)                     \
        BT_smp_param_request_reply                                           \
        ((bd_handle), SMP_LESC_KEY_PRESS_NTF,                                \
        (ntf_val),                                                           \
        sizeof(UCHAR))

#endif /* SMP_LESC */

/**
 * \brief To generate or verify signature of data with given key
 *
 * \par Description:
 *      This API enables the application to get data signing and verification
 *      done with the given key using the AES-CMAC Data Signing algorithm.
 *
 * \param [in] action SMP_SIGN_GENERATE to generate 8 octet signature for
 *                    given data. SMP_SIGN_VERIFY to verify the 8 octet
 *                    signature in given data.
 *
 * \param [in] buffer Data to be signed. This shall be the pointer to the buffer
 *                    containing data + 4 octet signature counter + 8 octet MAC
 *                    space
 *
 * \param [in] size Total size of buffer (actual data + 4 octets for signature
 *                  counter + 8 octets for MAC)
 *
 * \param [in] key Connection Signature Resolving Key
 *                 to be used for data signing
 *
 * \param [out] mac Buffer to hold generated MAC of size 8 octets, that will be
 *                  given through \ref SMP_UI_NOTIFY_CB \ref SMP_DATA_SIGNING_COMPLETE
 *                  event or \ref SMP_SIGN_DATA_VERIFICATION_COMPLETE event
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
API_RESULT  BT_smp_data_sign
            (
                /* IN */  UCHAR      action,
                /* IN */  UCHAR    * buffer,
                /* IN */  UINT16     size,
                /* IN */  UCHAR    * key,
                /* OUT */ UCHAR    * mac
            );


/**
 * \brief To sign data with given key for transmission
 *
 * \par Description:
 *      This API enables the application to get data signing done with the given
 *      key using the Data Signing algorithm.
 *
 * \param [in] buffer  Data to be signed. This shall be the pointer to the buffer
 *                    containing data + 4 octet signature counter + 8 octet MAC
 *                    space
 *
 * \param [in] size  Total size of buffer (actual data + 4 octets for signature
 *                  counter + 8 octets for MAC)
 *
 * \param [in] key  Connection Signature Resolving Key
 *                 to be used for data signing
 *
 * \param [out] mac  Buffer to hold generated MAC of size 8 octets, that will be
 *                  given through \ref SMP_UI_NOTIFY_CB \ref SMP_DATA_SIGNING_COMPLETE
 *                  event or \ref SMP_SIGN_DATA_VERIFICATION_COMPLETE event
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define  BT_smp_sign_data(buffer, size, key, mac)       \
         BT_smp_data_sign                               \
         (SMP_SIGN_GENERATE, (buffer), (size), (key), (mac));

/**
 * \brief To verify received signed data with given key
 *
 * \par Description:
 *      This API enables the application to verify a signed data with the given
 *      key using the Data Signing algorithm.
 *
 * \param [in] buffer Data to be signed. This shall be the pointer to the buffer
 *                    containing data + 4 octet signature counter + 8 octet MAC
 *                    space
 *
 * \param [in] size  Total size of buffer (actual data + 4 octets for signature
 *                  counter + 8 octets for MAC)
 *
 * \param [in] key  Connection Signature Resolving Key
 *                 to be used for data signing
 *
 * \param [out] mac  Buffer to hold generated MAC of size 8 octets, that will be
 *                  given through \ref SMP_UI_NOTIFY_CB \ref SMP_DATA_SIGNING_COMPLETE
 *                  event or \ref SMP_SIGN_DATA_VERIFICATION_COMPLETE event
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
#define  BT_smp_verify_sign_data(buffer, size, key, mac)       \
         BT_smp_data_sign                                      \
         (SMP_SIGN_VERIFY, (buffer), (size), (key), (mac));

/**
 * \brief To generate a resolvable private address
 *
 * \par Description:
 *      This API enables the application to generate a resolvable private
 *      address for the device using the Identity Resolving Key given
 *
 * \param [in] irk  Pointer to the 128 bits Identity Resolving Key array to
 * generate the resolvable private address
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
API_RESULT BT_smp_create_resolvable_pvt_addr (/* IN */ UCHAR   * irk);

/**
 * \brief To verify a given resolvable private address
 *
 * \par Description:
 *      This API enables the application to verify a resolvable private
 *      address with the Identity Resolving Key given
 *
 * \param [in] bd_addr  Resolvable Private Bluetooth Device Address information
 * as in \ref SMP_BD_ADDR
 *
 * \param [in] irk  Pointer to the 128 bits Identity Resolving Key array used to
 * generate the resolvable private address
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \sa smp_events
 */
API_RESULT BT_smp_verify_resolvable_pvt_addr
           (
               /* IN */ UCHAR   * bd_addr,
               /* IN */ UCHAR   * irk
           );

/**
 * \brief To get the existing security information for a given device
 *
 * \par Description:
 *      This API enables the application to query and know the existing
 *      security information for a given peer device.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [out] info  Pointer to \ref SMP_AUTH_INFO type to get the security
 * information for the device.
 * - 'security' refers to the Security Level exchanged, which is to
 *   be retrieved with \ref SMP_SEC_LEVEL_MASK
 * - 'bond' refers to the Bonding support exchanged
 * - 'param' refers to the  the current Authentication state
 *   (\ref SMP_ENTITY_AUTH_OFF, \ref SMP_ENTITY_AUTH_IN_PROGRESS,
 *   \ref SMP_ENTITY_AUTH_ON) of the link
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
API_RESULT BT_smp_get_device_security_info
           (
               /* IN */  SMP_BD_HANDLE   * bd_handle,
               /* OUT */ SMP_AUTH_INFO   * info
           );

/**
 * \brief To get the keys information for a given device
 *
 * \par Description:
 *      This API enables the application to know the keys information
 *      shared by a given peer device.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [out] keys  Pointer to a byte to get the peers key exchange information
 * on the keys that have been distributed by the peer.
 *
 * \param [out] key_info  Pointer to the structure \ref SMP_KEY_DIST to get the
 * peer distributed key values
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
API_RESULT BT_smp_get_device_keys
           (
               /* IN */  SMP_BD_HANDLE   * bd_handle,
               /* OUT */ UCHAR           * keys,
               /* OUT */ SMP_KEY_DIST    * key_info
           );

#ifdef HOST_RESOLVE_PVT_ADDR
/**
 * \brief To resolve a device address with the remote device database in SMP
 *
 * \par Description:
 *      This API enables the application to start resolution procedure for
 * a device that has connected using resolvable private address. The procedure
 * makes use of the SMP remote database for resolving the device.
 *
 * \param [in] bd_addr  Pointer to peer device address
 *
 * \param [in] rpa_resolv_handler  Handler to be called by SMP after address resolution
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 *
 * \note
 * This API is enabled only when SMP_NO_STORED_KEYS is not defined.
 * This API typically will be called from the platform interface
 * 'smp_resolve_connection_address_pl ()'. End of resolution procedure
 * is handled internally by the stack.
 */
API_RESULT BT_smp_resolve_device
           (
               UCHAR * bd_addr,
               SMP_PVT_ADDR_RESOLV_COMPLETE_CB rpa_resolv_handler
           );
#endif /* HOST_RESOLVE_PVT_ADDR */


/**
 * \brief To get the bluetooth device handle for a given device address
 *
 * \par Description:
 *      This API enables the application to query and know the device handle
 *      for for a given peer device address.
 *
 * \param [in] bd_addr  Pointer to peer device address as in \ref SMP_BD_ADDR
 *
 * \param [out] bd_handle  Pointer to \ref SMP_BD_HANDLE type to get the device
 *                        handle
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
#define BT_smp_get_bd_handle(bd_addr, bd_handle) \
        device_queue_search_remote_addr((bd_handle), (bd_addr))


/**
 * \brief To get the bluetooth device address for a given device handle
 *
 * \par Description:
 *      This API enables the application to query and know the device handle
 *      for for a given peer device address.
 *
 * \param [in] bd_handle  Pointer to peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [out] bd_addr  Pointer to \ref SMP_BD_ADDR type to get the device
 * address
 *
 * \return API_SUCCESS if Successful else and Error code describing
 * cause of failure.
 */
#define BT_smp_get_bd_addr(bd_handle, bd_addr) \
        device_queue_get_remote_addr((bd_handle), (bd_addr))


/**
 * \brief To update the RPA of a peer device
 *
 * \par Description:
 *      This API enables the application to update the Address of a peer device
 * in the stack database. If required, this call may be invoked on completion of
 * private address resolution procedure initiated using the BT_smp_resolve_device() API
 * when the callback handler is called
 *
 * \param [in] bd_handle  Pointer to the peer device handle as in \ref SMP_BD_HANDLE
 *
 * \param [in] bd_addr  Pointer to new peer RPA device address as in \ref BT_DEVICE_ADDR
 *
 * \return API_SUCCESS
 */
#define BT_smp_update_peer_address(bd_handle, bd_addr) \
        device_queue_set_remote_addr((bd_handle), (bd_addr))

#ifdef BT_4_2
/**
 * \brief To search the SMP Database for the incoming Peer Identity Address
 *
 * \par Description:
 *      This API enables the application to search for the peer identity address received
 * in the SMP Device Data Base and returns the corresponding SMP_BD_HANDLE if search succeeds
 *
 * \param [in] peer_id_addr  Pointer to peer Identity address as in \ref SMP_BD_ADDR
 *
 * \param [out] peer_dev_hndl  Pointer to the peer device handle as in \ref SMP_BD_HANDLE
 *
 * \return API_SUCCESS on succesful search of Identity Address else API_FAILURE
 */
API_RESULT BT_smp_search_identity_addr
           (
               /* IN */  SMP_BD_ADDR   * peer_id_addr,
               /* OUT */ SMP_BD_HANDLE * peer_dev_hndl
           );
#endif /* BT_4_2 */
/**
 * \}
 */

/**
 * \}
 */

#ifdef SMP_TBX_TEST_LESC_FUNCTIONS
API_RESULT smp_tbx_test_lesc_funcs
           (
               UCHAR                        * plain_text,
               UINT16                       plain_text_len,
               UCHAR                        * key,
               UCHAR                        * enc_out,
               UCHAR                        aes_op,
               SMP_APPL_AES_CMAC_UTILITY_CB cb
           );
#endif /* SMP_TBX_TEST_LESC_FUNCTIONS */

#ifdef __cplusplus
};
#endif

#endif /* _H_BT_SMP_API_ */
