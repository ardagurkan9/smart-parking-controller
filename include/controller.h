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
    uint8_t capacity;
    uint8_t occupancy;
} controller_t;


void controller_init(
    controller_t *controller,
    controller_status_t initial_status,
    uint8_t capacity
);

bool controller_status_check(
    const controller_t *controller,
    controller_status_t status
);

void controller_set_light(
    controller_t *controller,
    controller_status_t light_status
);

bool controller_open_barrier(
    controller_t *controller
);

bool controller_close_barrier(
    controller_t *controller
);

void controller_enable(
    controller_t *controller
);

void controller_disable(
    controller_t *controller
);

void controller_enter_emergency(
    controller_t *controller
);

void controller_exit_emergency(
    controller_t *controller
);

bool controller_vehicle_enter(
    controller_t *controller
);

bool controller_vehicle_exit(
    controller_t *controller
);

int controller_available_spaces(
    const controller_t *controller
);
#endif
