#ifndef LIB_CALL_STATUS_VALUE_H
#define LIB_CALL_STATUS_VALUE_H

#include <stdint.h>

typedef enum : int64_t {
    CSV_E_NOT_SUPPORTED = -1,
    CSV_OK = 0,
} CallStatusValue;

#endif //LIB_CALL_STATUS_VALUE_H
