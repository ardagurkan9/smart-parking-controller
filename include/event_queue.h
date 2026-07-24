#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "result.h"
#include "system_event.h"

#define EVENT_QUEUE_MAX_CAPACITY 32

typedef struct{
    system_event_type_t events[EVENT_QUEUE_MAX_CAPACITY];
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
}event_queue_t;

result_t event_queue_init(
    event_queue_t *queue,
    size_t capacity
);

result_t event_queue_push(
    event_queue_t *queue,
    system_event_type_t event
);

result_t event_queue_pop(
    event_queue_t *queue,
    system_event_type_t *out_event
);

result_t event_queue_peek(
    const event_queue_t *queue,
    system_event_type_t *out_event
);

bool event_queue_is_full(
    const event_queue_t *queue
);

bool event_queue_is_empty(
    const event_queue_t *queue
);

size_t event_queue_count(
    const event_queue_t *queue
);

#endif
