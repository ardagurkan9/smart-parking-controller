#include "vehicle.h"
#include <stdlib.h>
#include <string.h>

bool vehicle_list_init(
    vehicle_list_t *list,
    size_t capacity
){
    if (list == NULL || capacity == 0) {
        return false;
    }

    list->records = NULL;
    list->count = 0;
    list->capacity = 0;

    list->records = malloc(sizeof(vehicle_t) * capacity);
    if (list->records == NULL) {
        return false;
    }

    list->capacity = capacity;
    return true;
}

bool vehicle_list_destroy(
    vehicle_list_t *list
){
    if (list == NULL) {
        return false;
    }

    free(list->records);
    list->records = NULL;
    list->count = 0;
    list->capacity = 0;

    return true;
}

bool vehicle_list_add(
    vehicle_list_t *list,
    const vehicle_t *vehicle
){
    if (list == NULL || vehicle == NULL) {
        return false;
    }

    size_t plate_length = 0;
    while (plate_length <= PLATE_MAX_LENGTH &&
           vehicle->plate[plate_length] != '\0') {
        plate_length++;
    }

    if (plate_length == 0 || plate_length > PLATE_MAX_LENGTH) {
        return false;
    }

    if (list->count >= list->capacity) {
        return false;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (list->records[i].id == vehicle->id ||
            strcmp(list->records[i].plate, vehicle->plate) == 0) {
            return false;
        }
    }

    list->records[list->count] = *vehicle;
    list->count++;

    return true;
}

bool vehicle_list_find_by_plate(
    const vehicle_list_t *list,
    const char *plate,
    vehicle_t *out_vehicle
){
    if (list == NULL || plate == NULL || out_vehicle == NULL) {return false;}

    for (size_t i = 0; i < list->count; i++) {
        if (strcmp(list->records[i].plate, plate) == 0) {
            *out_vehicle = list->records[i];
            return true;
        }
    }

    return false;
}

bool vehicle_list_remove_by_plate(
    vehicle_list_t *list,
    const char *plate
){
    if (list == NULL || plate == NULL) {
        return false;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (strcmp(list->records[i].plate, plate) == 0) {
            for (size_t j = i; j < list->count - 1; j++) {
                list->records[j] = list->records[j + 1];
            }
            list->count--;
            return true;
        }
    }

    return false;
}