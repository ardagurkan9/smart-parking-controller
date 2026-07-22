#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t controller_status_t;

enum {
    STATUS_RED = (1U << 0),
    STATUS_YELLOW = (1U << 1),
    STATUS_GREEN = (1U << 2),
    STATUS_BARRIER = (1U << 3),
    STATUS_ALARM = (1U << 4),
    STATUS_FULL = (1U << 5),
    STATUS_EMERGENCY = (1U << 6),
    STATUS_SYSTEM_ON = (1U << 7)
};

typedef struct {
    controller_status_t status;
} controller_t;


void controller_init(
    controller_t *controller,
    controller_status_t initial_status
);

void controller_set_status(
    controller_t *controller,
    controller_status_t status
);

void controller_clear_status(
    controller_t *controller,
    controller_status_t status
);

bool controller_status_check(
    const controller_t *controller,
    controller_status_t status
);

#endif // CONTROLLER_H