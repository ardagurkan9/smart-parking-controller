#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdbool.h>    
#include <stddef.h>
#include <stdint.h>

#define PLATE_MAX_LENGTH 15

typedef struct {
    char plate[PLATE_MAX_LENGTH + 1];
    uint32_t id;
} vehicle_t;

typedef struct {
    vehicle_t *records;
    size_t count;
    size_t capacity;
} vehicle_list_t;

bool vehicle_list_init(
    vehicle_list_t *list,
    size_t capacity
);

bool vehicle_list_destroy(
    vehicle_list_t *list
);

bool vehicle_list_add(
    vehicle_list_t *list,
    const vehicle_t *vehicle
);

bool vehicle_list_find_by_plate(
    const vehicle_list_t *list,
    const char *plate,
    vehicle_t *out_vehicle
);

 bool vehicle_list_remove_by_plate(
    vehicle_list_t *list,
    const char *plate
 );
 
#endif