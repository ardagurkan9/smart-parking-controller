#ifndef access_h
#define access_h

#include <stdint.h>
#include <stdbool.h>

#define PIN_LENGTH 4

typedef enum{
    ACCESS_OK = 0,
    ACCESS_ERROR_NULL = -1,
    ACCESS_ERROR_ATTEMPTS = -2,
    ACCESS_ERROR_PIN_LENGTH = -3,
    ACCESS_ERROR_PIN_FORMAT = -4
} access_result_t;  

typedef struct {
    char pin[PIN_LENGTH + 1];
    uint8_t failed_attempts;
    uint8_t max_attempts;
} access_t;

access_result_t access_init(
    access_t *access,
    const char *pin,
    uint8_t max_attempts
);

bool access_validate_pin(
    access_t* access,
    const char* pin
);

bool access_is_locked(
    const access_t* access
);

void access_reset_attempts(
    access_t* access
);

#endif
