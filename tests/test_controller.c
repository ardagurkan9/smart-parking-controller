#include <stdio.h>
#include <stdlib.h>
#include "controller.h"

int main(void) {
    controller_t controller;
    controller_status_t initial_status = STATUS_RED | STATUS_SYSTEM_ON;

    controller_init(&controller, initial_status);

    if (controller.status != initial_status) {
        printf("Controller init test failed.\n");
        return EXIT_FAILURE;
    }

    controller_set_status(&controller, STATUS_BARRIER);
    if (!controller_status_check(&controller, STATUS_BARRIER)) {
        printf("Controller set/check test failed.\n");
        return EXIT_FAILURE;
    }

    controller_clear_status(&controller, STATUS_RED);
    if (controller_status_check(&controller, STATUS_RED)) {
        printf("Controller clear test failed.\n");
        return EXIT_FAILURE;
    }

    printf("All controller tests passed.\n");
    return EXIT_SUCCESS;
}
