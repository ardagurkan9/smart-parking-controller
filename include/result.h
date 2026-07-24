#ifndef RESULT_H
#define RESULT_H

typedef enum{
    RESULT_OK,
    RESULT_NULL_POINTER,
    RESULT_INVALID_ARGUMENT,
    RESULT_INVALID_TRANSITION,
    RESULT_QUEUE_FULL,
    RESULT_QUEUE_EMPTY,
    RESULT_NOT_FOUND
}result_t;

const char *result_to_string(
    result_t result
);

#endif
