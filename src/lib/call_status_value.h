#ifndef LIB_CALL_STATUS_VALUE_H
#define LIB_CALL_STATUS_VALUE_H

#include <stdint.h>

typedef enum : int64_t {
    CSV_E_INVALID_ARG_6 = -16,
    CSV_E_INVALID_ARG_5,
    CSV_E_INVALID_ARG_4,
    CSV_E_INVALID_ARG_3,
    CSV_E_INVALID_ARG_2,
    CSV_E_INVALID_ARG_1,
    CSV_E_INVALID_ARG_0,
    CSV_E_NOT_SUPPORTED = -1,
    CSV_E_IO_ERROR = -2,
    CSV_OK = 0,
} CallStatusValue;

#endif //LIB_CALL_STATUS_VALUE_H
