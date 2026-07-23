#include <stdio.h>
#include <stdlib.h>
#include "access.h"
#include "controller.h"

int main(void){
    access_t access;
    controller_t controller;

    if(access_init(&access, "1234", 3) != ACCESS_OK){
        printf("Access init test failed.\n");
        return EXIT_FAILURE;
    }

    if(!access_validate_pin(&access, "1234")){
        printf("Correct PIN test failed.\n");
        return EXIT_FAILURE;
    }

    access_validate_pin(&access, "0000");
    access_validate_pin(&access, "1111");
    access_validate_pin(&access, "2222");

    if(!access_is_locked(&access)){
        printf("Access lock test failed.\n");
        return EXIT_FAILURE;
    }

    controller_init(&controller, STATUS_SYSTEM_ON | STATUS_RED, 10);
    controller_open_barrier(&controller);

    if(access_is_locked(&access)){
        controller_activate_alarm(&controller);
    }

    if(!controller_status_check(&controller, STATUS_ALARM) ||
       controller_status_check(&controller, STATUS_BARRIER)){
        printf("Alarm activation test failed.\n");
        return EXIT_FAILURE;
    }

    controller_reset_alarm(&controller);
    access_reset_attempts(&access);

    if(controller_status_check(&controller, STATUS_ALARM) ||
       access_is_locked(&access) ||
       !access_validate_pin(&access, "1234")){
        printf("Alarm reset test failed.\n");
        return EXIT_FAILURE;
    }

    printf("All access tests passed.\n");
    return EXIT_SUCCESS;
}
