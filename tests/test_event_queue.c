#include <stdio.h>
#include <stdlib.h>

#include "event_queue.h"

int main(void){
    event_queue_t queue;
    system_event_type_t event;

    if(event_queue_init(NULL, 3) != RESULT_NULL_POINTER ||
       event_queue_init(&queue, 0) != RESULT_INVALID_ARGUMENT ||
       event_queue_init(&queue, EVENT_QUEUE_MAX_CAPACITY + 1) != RESULT_INVALID_ARGUMENT){
        printf("Queue init validation test failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_init(&queue, 3) != RESULT_OK ||
       !event_queue_is_empty(&queue) ||
       event_queue_count(&queue) != 0){
        printf("Queue init test failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_pop(&queue, &event) != RESULT_QUEUE_EMPTY ||
       event_queue_peek(&queue, &event) != RESULT_QUEUE_EMPTY){
        printf("Queue empty test failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_push(&queue, EVENT_SYSTEM_ENABLE) != RESULT_OK ||
       event_queue_push(&queue, EVENT_VEHICLE_DETECTED) != RESULT_OK ||
       event_queue_push(&queue, EVENT_PIN_VALID) != RESULT_OK ||
       !event_queue_is_full(&queue) ||
       event_queue_count(&queue) != 3 ||
       event_queue_push(&queue, EVENT_BARRIER_OPENED) != RESULT_QUEUE_FULL){
        printf("Queue full test failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_peek(&queue, &event) != RESULT_OK ||
       event != EVENT_SYSTEM_ENABLE ||
       event_queue_count(&queue) != 3){
        printf("Queue peek test failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_pop(&queue, &event) != RESULT_OK ||
       event != EVENT_SYSTEM_ENABLE ||
       event_queue_push(&queue, EVENT_BARRIER_OPENED) != RESULT_OK){
        printf("Queue wrap-around setup failed.\n");
        return EXIT_FAILURE;
    }

    if(event_queue_pop(&queue, &event) != RESULT_OK ||
       event != EVENT_VEHICLE_DETECTED ||
       event_queue_pop(&queue, &event) != RESULT_OK ||
       event != EVENT_PIN_VALID ||
       event_queue_pop(&queue, &event) != RESULT_OK ||
       event != EVENT_BARRIER_OPENED ||
       !event_queue_is_empty(&queue)){
        printf("Queue FIFO/wrap-around test failed.\n");
        return EXIT_FAILURE;
    }

    printf("All event queue tests passed.\n");
    return EXIT_SUCCESS;
}
