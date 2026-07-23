#include "controller.h"

void controller_init(
    controller_t *controller,
    controller_status_t initial_status,
    uint8_t capacity
){
    controller->status = initial_status;
    controller->capacity = capacity;
    controller->occupancy = 0;
}

bool controller_status_check(
    const controller_t *controller,
    controller_status_t status
){
    return (controller -> status & status) == status;
}

void controller_set_light(
    controller_t *controller,
    controller_status_t light_status
){
    if(light_status == STATUS_RED ||
       light_status == STATUS_YELLOW ||
       light_status == STATUS_GREEN)
    {
        controller -> status &= ~(STATUS_RED | STATUS_YELLOW | STATUS_GREEN);
        controller -> status |= light_status;
    }
}

bool controller_open_barrier(
    controller_t *controller
)
{
    if ((controller->status & STATUS_SYSTEM_ON) != 0 &&
        (controller->status & STATUS_FULL) == 0 &&
        (controller->status & STATUS_EMERGENCY) == 0 &&
        (controller->status & STATUS_ALARM) == 0)

    {
        controller->status |= STATUS_BARRIER;
        return true;
    }
    return false;
}

bool controller_close_barrier(
    controller_t *controller
){
    controller -> status &= ~STATUS_BARRIER;
    return true;
}

void controller_enable(
    controller_t *controller
){
    controller -> status |= STATUS_SYSTEM_ON;
    controller -> status &= ~STATUS_BARRIER;
    controller_set_light(controller, STATUS_RED);
}

void controller_disable(
    controller_t *controller
){
    controller -> status &= ~STATUS_SYSTEM_ON;
    controller -> status &= ~STATUS_BARRIER;
    controller -> status &= ~STATUS_RED;
    controller -> status &= ~STATUS_YELLOW;
    controller -> status &= ~STATUS_GREEN;
}

void controller_enter_emergency(
    controller_t *controller
){
    controller ->status |= STATUS_EMERGENCY;
    controller -> status &= ~STATUS_BARRIER;
    controller_set_light(controller, STATUS_RED);

}

void controller_exit_emergency(
    controller_t *controller
){
    controller ->status &= ~STATUS_EMERGENCY;
}

bool controller_vehicle_enter(
    controller_t *controller
){
    if (controller->occupancy < controller->capacity) {
        controller->occupancy++;
        if(controller->occupancy >= controller->capacity) {
            controller->status |= STATUS_FULL;
        }
        return true;
    }
    controller->status |= STATUS_FULL;
    return false;
}

bool controller_vehicle_exit(
    controller_t *controller
){
    if (controller->occupancy > 0) {
        controller->occupancy--;
        if(controller->occupancy < controller->capacity) {
            controller->status &= ~STATUS_FULL;
        }
        return true;
    }
    return false;
}

int controller_available_spaces(
    const controller_t *controller
){
    return controller->capacity - controller->occupancy;
}

void controller_activate_alarm(
    controller_t *controller
){
    controller->status |= STATUS_ALARM;
    controller_set_light(controller, STATUS_RED);
    controller -> status &= ~STATUS_BARRIER;
}

void controller_reset_alarm(
    controller_t *controller
){
    controller->status &= ~STATUS_ALARM;
}
