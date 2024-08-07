#include "system_control_block.h"
#include "lib/system_control_block.h"


[[gnu::aligned(16)]]
SystemControlBlock g_scb = {
    .version_major = 1,
    .version_minor = 0,
    .version_release_type = SCB_ALPHA_RELEASE,
    .version_prelease = 1,
    .drive_search_chain = { 0xfe, 0xff },
    .auxin_redirection = 0xff,
    .auxout_redirection = 0xff,
    .lst_redirection = 0xff,
    .page_mode = true,
    .error_mode = SCB_NORMAL_ERROR_MODE,
    .error_drive = 0xff,
    .show_exapnded_error_messages = true,
};


static const void* g_scb_parameter_address[] = {
    [SCB_VERSION_MAJOR] = &g_scb.version_major,
    [SCB_VERSION_MINOR] = &g_scb.version_minor,
    [SCB_VERSION_RELEASE_TYPE] = &g_scb.version_release_type,
    [SCB_VERSION_PRELEASE] = &g_scb.version_prelease,
    [SCB_USER_FLAGS] = &g_scb.user_flags,
    [SCB_PROGRAM_RETURN_CODE] = &g_scb.program_return_code,
    [SCB_CONSOLE_WIDTH] = &g_scb.console_width,
    [SCB_CONSOLE_COLUMN] = &g_scb.console_column,
    [SCB_CONSOLE_PAGE_LENGTH] = &g_scb.console_page_length,
    [SCB_CONIN_REDIRECTION] = &g_scb.conin_redirection,
    [SCB_CONOUT_REDIRECTION] = &g_scb.conout_redirection,
    [SCB_AUXIN_REDIRECTION] = &g_scb.auxin_redirection,
    [SCB_AUXOUT_REDIRECTION] = &g_scb.auxout_redirection,
    [SCB_LST_REDIRECTION] = &g_scb.lst_redirection,
    [SCB_PAGE_MODE] = &g_scb.page_mode,
    [SCB_CONSOLE_MODE] = &g_scb.console_mode,
    [SCB_OUTPUT_DELIMITER] = &g_scb.output_delimiter,
    [SCB_LIST_OUTPUT_FLAG] = &g_scb.list_output_flag,
    [SCB_CURRENT_DRIVE] = &g_scb.current_drive,
    [SCB_CURRENT_USER] = &g_scb.current_user,
    [SCB_ERROR_MODE] = &g_scb.error_mode,
    [SCB_DRIVE_SEARCH_CHAIN] = &g_scb.drive_search_chain,
    [SCB_TEMPORARY_DRIVE] = &g_scb.temporary_drive,
    [SCB_ERROR_DRIVE] = &g_scb.error_drive,
    [SCB_SHOW_EXAPNDED_ERROR_MESSAGES] = &g_scb.show_exapnded_error_messages,
    [SCB_MULTISECTOR_COUNT] = &g_scb.multisector_count,
};


typedef enum: uint8_t {
    SCB_8_BIT_PARAMETER,
    SCB_16_BIT_PARAMETER,
    SCB_32_BIT_PARAMETER,
    SCB_64_BIT_PARAMETER,
} ScbParameterWidth;

typedef struct {
    ScbParameterWidth width: 2;
    bool rw : 1;     // false = read only, true = read/write
} ScbParameterInfo;

static const ScbParameterInfo g_scb_parameter_info[] = {
    [SCB_VERSION_MAJOR]                 = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_VERSION_MINOR]                 = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_VERSION_RELEASE_TYPE]          = { .width = SCB_8_BIT_PARAMETER              },
    [SCB_VERSION_PRELEASE]              = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_USER_FLAGS]                    = { .width = SCB_64_BIT_PARAMETER, .rw = true },
    [SCB_PROGRAM_RETURN_CODE]           = { .width = SCB_64_BIT_PARAMETER, .rw = true },
    [SCB_CONSOLE_WIDTH]                 = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_CONSOLE_COLUMN]                = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_CONSOLE_PAGE_LENGTH]           = { .width = SCB_16_BIT_PARAMETER             },
    [SCB_CONIN_REDIRECTION]             = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_CONOUT_REDIRECTION]            = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_AUXIN_REDIRECTION]             = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_AUXOUT_REDIRECTION]            = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_LST_REDIRECTION]               = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_PAGE_MODE]                     = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_CONSOLE_MODE]                  = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_OUTPUT_DELIMITER]              = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_LIST_OUTPUT_FLAG]              = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_CURRENT_DRIVE]                 = { .width = SCB_8_BIT_PARAMETER              },
    [SCB_CURRENT_USER]                  = { .width = SCB_8_BIT_PARAMETER              },
    [SCB_ERROR_MODE]                    = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_DRIVE_SEARCH_CHAIN]            = { .width = SCB_32_BIT_PARAMETER, .rw = true },
    [SCB_TEMPORARY_DRIVE]               = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_ERROR_DRIVE]                   = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_SHOW_EXAPNDED_ERROR_MESSAGES]  = { .width = SCB_8_BIT_PARAMETER,  .rw = true },
    [SCB_MULTISECTOR_COUNT]             = { .width = SCB_64_BIT_PARAMETER, .rw = true },
};


static constexpr unsigned SCB_PARAMETER_COUNT = sizeof(g_scb_parameter_address) / sizeof(g_scb_parameter_address[0]);

_Static_assert(
    SCB_PARAMETER_COUNT == sizeof(g_scb_parameter_info) / sizeof(g_scb_parameter_info[0]),
    "g_scbParameterAddress and g_scbParameterAddress must be the same length"
);


CallStatusValue kernel_scb_reset(void) {
    g_scb.multisector_count = 0;
    g_scb.page_mode = true;
    g_scb.console_mode = (ConsoleMode) { 0 };
    g_scb.output_delimiter = '\0';
    g_scb.list_output_flag = false;
    g_scb.error_mode = SCB_NORMAL_ERROR_MODE;
    g_scb.show_exapnded_error_messages = true;
    g_scb.timer_has_alarmed = false;
    g_scb.rtc_has_alarmed = false;
    return CSV_OK;
}


CallStatusValue kernel_scb_get_parameter(uint64_t parameter, uint64_t* value) {
    if (parameter >= SCB_PARAMETER_COUNT) {
        return CSV_E_INVALID_ARG_1;
    }
    const ScbParameterInfo* const scbParameterInfo = g_scb_parameter_info + parameter;
    switch (scbParameterInfo->width) {
        case SCB_8_BIT_PARAMETER: {
            const auto scb_value = (uint8_t*) g_scb_parameter_address[parameter];
            *value = *scb_value;
            break;
        }
        case SCB_16_BIT_PARAMETER: {
            const auto scb_value = (uint16_t*) g_scb_parameter_address[parameter];
            *value = *scb_value;
            break;
        }
        case SCB_32_BIT_PARAMETER: {
            const auto scb_value = (uint32_t*) g_scb_parameter_address[parameter];
            *value = *scb_value;
            break;
        }
        case SCB_64_BIT_PARAMETER: {
            const auto scb_value = (uint64_t*) g_scb_parameter_address[parameter];
            *value = *scb_value;
            break;
        }
    }
    return CSV_OK;
}


CallStatusValue kernel_scb_set_parameter(uint64_t parameter, uint64_t value) {
    if (parameter >= SCB_PARAMETER_COUNT) {
        return CSV_E_INVALID_ARG_1;
    }
    const ScbParameterInfo* const scbParameterInfo = g_scb_parameter_info + parameter;
    if (!scbParameterInfo->rw) {
        return CSV_E_INVALID_ARG_1;
    }
    switch (scbParameterInfo->width) {
        case SCB_8_BIT_PARAMETER: {
            const auto scb_value = (uint8_t*) g_scb_parameter_address[parameter];
            *scb_value = value;
            break;
        }
        case SCB_16_BIT_PARAMETER: {
            const auto scb_value = (uint16_t*) g_scb_parameter_address[parameter];
            *scb_value = value;
            break;
        }
        case SCB_32_BIT_PARAMETER: {
            const auto scb_value = (uint32_t*) g_scb_parameter_address[parameter];
            *scb_value = value;
            break;
        }
        case SCB_64_BIT_PARAMETER: {
            uint64_t* scb_value = (uint64_t*) g_scb_parameter_address[parameter];
            *scb_value = value;
            break;
        }
    }
    return CSV_OK;
}
