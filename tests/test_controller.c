#include <stdio.h>
#include <stdlib.h>
#include "controller.h"

int main(void) {
    controller_t controller;
    controller_status_t initial_status = STATUS_RED | STATUS_SYSTEM_ON;

    controller_init(&controller, initial_status, 100);

    if (controller.status != initial_status ||
        controller.capacity != 100 ||
        controller.occupancy != 0) {
        printf("Controller init test failed.\n");
        return EXIT_FAILURE;
    }

    controller_set_light(&controller, STATUS_GREEN);
    if (controller.status != (STATUS_SYSTEM_ON | STATUS_GREEN)) {
        printf("Controller light test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON | STATUS_RED, 100);
    if (!controller_open_barrier(&controller) ||
        !controller_status_check(&controller, STATUS_BARRIER)) {
        printf("Controller open barrier test failed.\n");
        return EXIT_FAILURE;
    }

    controller_close_barrier(&controller);
    if (controller_status_check(&controller, STATUS_BARRIER)) {
        printf("Controller close barrier test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON | STATUS_FULL, 100);
    if (controller_open_barrier(&controller)) {
        printf("Full parking barrier test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON | STATUS_ALARM, 100);
    if (controller_open_barrier(&controller)) {
        printf("Alarm barrier test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_GREEN | STATUS_BARRIER, 100);
    controller_enable(&controller);
    if (controller.status != (STATUS_SYSTEM_ON | STATUS_RED)) {
        printf("Controller enable test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON | STATUS_RED | STATUS_ALARM, 100);
    controller_disable(&controller);
    if (controller.status != STATUS_ALARM) {
        printf("Controller disable test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(
        &controller,
        STATUS_SYSTEM_ON | STATUS_GREEN | STATUS_BARRIER | STATUS_ALARM,
        100
    );
    controller_enter_emergency(&controller);
    if (controller.status !=
        (STATUS_SYSTEM_ON | STATUS_RED | STATUS_ALARM | STATUS_EMERGENCY)) {
        printf("Enter emergency test failed.\n");
        return EXIT_FAILURE;
    }

    controller_exit_emergency(&controller);
    if (controller.status != (STATUS_SYSTEM_ON | STATUS_RED | STATUS_ALARM)) {
        printf("Exit emergency test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON, 2);
    if (!controller_vehicle_enter(&controller) ||
        !controller_vehicle_enter(&controller) ||
        controller_vehicle_enter(&controller) ||
        !controller_status_check(&controller, STATUS_FULL) ||
        controller_available_spaces(&controller) != 0) {
        printf("Vehicle enter/full test failed.\n");
        return EXIT_FAILURE;
    }

    if (!controller_vehicle_exit(&controller) ||
        controller_status_check(&controller, STATUS_FULL) ||
        controller_available_spaces(&controller) != 1) {
        printf("Vehicle exit test failed.\n");
        return EXIT_FAILURE;
    }

    printf("All controller tests passed.\n");
    return EXIT_SUCCESS;
}
