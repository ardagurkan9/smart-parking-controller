#include "controller.h"

void controller_init(
    controller_t *controller,
    controller_status_t initial_status
){
    controller-> status = initial_status;
}

void controller_set_status(
    controller_t *controller,
    controller_status_t status
){
    controller -> status |= status; 
}

void controller_clear_status(
    controller_t *controller,
    controller_status_t status
){
    controller -> status &= ~status; 
}

bool controller_status_check(
    const controller_t *controller,
    controller_status_t status
){
    return (controller -> status & status) == status;
}

/* controller.h icinde bildirdigin fonksiyonlari burada gerceklestir. */
