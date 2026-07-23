#include "access.h"
#include <stddef.h>

access_result_t access_init(
    access_t *access,
    const char *pin,
    uint8_t max_attempts
){
    if(access == NULL || pin == NULL){return ACCESS_ERROR_NULL;}
    if(max_attempts == 0){return ACCESS_ERROR_ATTEMPTS;}

    for(int i=0; i<PIN_LENGTH;i++){
        if(pin[i] == 0){return ACCESS_ERROR_PIN_LENGTH;}
        if(pin[i] < '0' || pin[i] > '9'){return ACCESS_ERROR_PIN_FORMAT;}
    }
    if(pin[PIN_LENGTH] != 0){return ACCESS_ERROR_PIN_LENGTH;}

    for (int i = 0; i < PIN_LENGTH; i++) {
        access->pin[i] = pin[i];
    }

    access->pin[PIN_LENGTH] = '\0';
    access->failed_attempts = 0;
    access->max_attempts = max_attempts;

    return ACCESS_OK;
}

bool access_validate_pin(
    access_t* access,
    const char* pin

){
    if(access == NULL || pin == NULL ){return false;}
    if(access->failed_attempts >= access->max_attempts){return false;}
     
    for(int i=0; i<PIN_LENGTH;i++){
        if(pin[i] == 0){access->failed_attempts++; return false;}
        if(pin[i] < '0' || pin[i] > '9'){ access->failed_attempts++; return false;}
    }

    if(pin[PIN_LENGTH] != 0){access->failed_attempts++; return false;}

    for (int i = 0; i < PIN_LENGTH; i++) {
        if (access->pin[i] != pin[i]) {
            access->failed_attempts++;
            return false;
        }
    }

    access ->failed_attempts = 0;

    return true;
}

bool access_is_locked(
    const access_t* access
){
    if(access == NULL){return true;}
    return access->failed_attempts >= access->max_attempts;
}

void access_reset_attempts(
    access_t* access
){
    if(access == NULL){return;}
    access->failed_attempts = 0;
}
