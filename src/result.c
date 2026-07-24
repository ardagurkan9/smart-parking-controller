#include "result.h"

const char *result_to_string(
    result_t result
){
    switch(result){
        case RESULT_OK:
            return "Success";
        case RESULT_NULL_POINTER:
            return "Null pointer";
        case RESULT_INVALID_ARGUMENT:
            return "Invalid argument";
        case RESULT_INVALID_TRANSITION:
            return "Invalid state transition";
        case RESULT_QUEUE_FULL:
            return "Queue is full";
        case RESULT_QUEUE_EMPTY:
            return "Queue is empty";
        case RESULT_NOT_FOUND:
            return "Not found";
        default:
            return "Unknown result";
    }
}
