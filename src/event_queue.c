#include "event_queue.h"

result_t event_queue_init(
    event_queue_t *queue,
    size_t capacity
){
    if(queue == NULL){
        return RESULT_NULL_POINTER;
    }

    if(capacity == 0 || capacity > EVENT_QUEUE_MAX_CAPACITY){
        return RESULT_INVALID_ARGUMENT;
    }

    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;

    return RESULT_OK;
}

result_t event_queue_push(
    event_queue_t *queue,
    system_event_type_t event
){
    if(queue == NULL){
        return RESULT_NULL_POINTER;
    }

    if(event_queue_is_full(queue)){
        return RESULT_QUEUE_FULL;
    }

    queue->events[queue->tail] = event;
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count++;

    return RESULT_OK;
}

result_t event_queue_pop(
    event_queue_t *queue,
    system_event_type_t *out_event
){
    if(queue == NULL || out_event == NULL){
        return RESULT_NULL_POINTER;
    }

    if(event_queue_is_empty(queue)){
        return RESULT_QUEUE_EMPTY;
    }

    *out_event = queue->events[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;

    return RESULT_OK;
}

result_t event_queue_peek(
    const event_queue_t *queue,
    system_event_type_t *out_event
){
    if(queue == NULL || out_event == NULL){
        return RESULT_NULL_POINTER;
    }

    if(event_queue_is_empty(queue)){
        return RESULT_QUEUE_EMPTY;
    }

    *out_event = queue->events[queue->head];
    return RESULT_OK;
}

bool event_queue_is_full(
    const event_queue_t *queue
){
    if(queue == NULL){
        return false;
    }

    return queue->count == queue->capacity;
}

bool event_queue_is_empty(
    const event_queue_t *queue
){
    if(queue == NULL){
        return true;
    }

    return queue->count == 0;
}

size_t event_queue_count(
    const event_queue_t *queue
){
    if(queue == NULL){
        return 0;
    }

    return queue->count;
}
