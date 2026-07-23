#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicle.h"

int main(void){
    vehicle_list_t list;
    vehicle_t vehicle1 = {"34ABC123", 1};
    vehicle_t vehicle2 = {"06XYZ456", 2};
    vehicle_t vehicle3 = {"35TEST789", 3};
    vehicle_t vehicle4 = {"16FULL000", 4};
    vehicle_t found;

    if(!vehicle_list_init(&list, 3)){
        printf("Vehicle list init test failed.\n");
        return EXIT_FAILURE;
    }

    if(!vehicle_list_add(&list, &vehicle1) ||
       !vehicle_list_add(&list, &vehicle2)){
        printf("Vehicle add test failed.\n");
        return EXIT_FAILURE;
    }

    if(vehicle_list_add(&list, &vehicle1)){
        printf("Duplicate vehicle test failed.\n");
        return EXIT_FAILURE;
    }

    if(!vehicle_list_add(&list, &vehicle3) ||
       vehicle_list_add(&list, &vehicle4)){
        printf("Vehicle capacity test failed.\n");
        return EXIT_FAILURE;
    }

    if(!vehicle_list_find_by_plate(&list, "06XYZ456", &found) ||
       found.id != 2){
        printf("Vehicle find test failed.\n");
        return EXIT_FAILURE;
    }

    if(!vehicle_list_remove_by_plate(&list, "06XYZ456") ||
       list.count != 2 ||
       strcmp(list.records[1].plate, "35TEST789") != 0){
        printf("Vehicle remove test failed.\n");
        return EXIT_FAILURE;
    }

    if(!vehicle_list_destroy(&list) ||
       list.records != NULL ||
       list.count != 0 ||
       list.capacity != 0){
        printf("Vehicle destroy test failed.\n");
        return EXIT_FAILURE;
    }

    printf("All vehicle tests passed.\n");
    return EXIT_SUCCESS;
}
