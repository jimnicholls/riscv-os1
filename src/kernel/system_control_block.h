#ifndef KERNEL_SYSTEM_CONTROL_BLOCK_H
#define KERNEL_SYSTEM_CONTROL_BLOCK_H

#include <stdint.h>
#include "lib/console_io.h"
#include "lib/call_status_value.h"


typedef enum: uint8_t {
    SCB_ALPHA_RELEASE = 'a',
    SCB_BETA_RELEASE = 'b',
    SCB_RELEASE_CANDIDATE = 'r',
    SCB_PRODUCTION_RELEASE = ' ',
} SystemControlBlockReleaseType;

typedef enum: uint8_t {
    SCB_NORMAL_ERROR_MODE = 0x00,
    SCB_TERMINATE_ERROR_MODE = 0x01,
    SCB_SILENT_ERROR_MODE = 0xff
} SystemControlBlockErrorMode;

typedef enum: uint8_t {
    SCB_SEARCH_DEFAULT_DRIVE = 0xfe,
    SCB_SEARCH_END = 0xff,
} SystemControlBlockDriveSearchChain;

typedef struct {
    uint16_t version_major;
    uint16_t version_minor;
    SystemControlBlockReleaseType version_release_type;
    uint16_t version_prelease;
    uint64_t user_flags;
    uint64_t program_return_code;
    uint64_t multisector_count;         // Moved out of order to reduce padding within the struct
    uint8_t drive_search_chain[4];      // Moved out of order to align this 32-bit quantity on a 32-bit boundary
    uint16_t console_width;
    uint16_t console_column;
    uint16_t console_page_length;
    uint8_t conin_redirection;
    uint8_t conout_redirection;
    uint8_t auxin_redirection;
    uint8_t auxout_redirection;
    uint8_t lst_redirection;
    bool page_mode;
    ConsoleMode console_mode;
    uint8_t output_delimiter;
    bool list_output_flag;
    uint8_t current_drive;
    uint8_t current_user;
    SystemControlBlockErrorMode error_mode;
    uint8_t temporary_drive;
    uint8_t error_drive;
    bool show_exapnded_error_messages;
    bool timer_has_alarmed;
    bool rtc_has_alarmed;
    char typeahead_buffer[16];          // Circular queue. No overflow. Length is n-1. n must be a power of 2.
    uint8_t typeahead_buffer_head;
    uint8_t typeahaed_buffer_tail;
} SystemControlBlock;


extern SystemControlBlock g_scb;


CallStatusValue kernel_scb_reset(void);
CallStatusValue kernel_scb_get_parameter(uint64_t parameter, uint64_t* value);
CallStatusValue kernel_scb_set_parameter(uint64_t parameter, uint64_t value);


#endif //KERNEL_SYSTEM_CONTROL_BLOCK_H
