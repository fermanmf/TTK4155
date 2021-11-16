#include "em.h"

#include <stdint.h>
#include <stdio.h>

#include "can.h"

#define QUEUE_MAX_LENGTH 10

static volatile int8_t end_index = -1;
static volatile EmEvent queue[QUEUE_MAX_LENGTH] = {};

static void enqueue(EmEvent event) {
	if (end_index < QUEUE_MAX_LENGTH-1) {
		queue[++end_index] = event;
	}
}

static EmEvent dequeue(){
	const EmEvent event = queue[0];
	for (int i = 0; i<=end_index; i++) {
		queue[i] = queue[i+1];
	}
	end_index--;
	return event;
}
static void can_message_received (uint8_t id, uint8_t data[], uint8_t data_length) {
	const EmEvent event = {id, .value=data[0]};
	enqueue(event);
}

void em_init() {
	can_init(&can_message_received);	
}

EmEvent em_get_event() {
	while (end_index == -1);
	return dequeue();
}

void em_event(EmEventType type, uint8_t value) {
	const EmEvent event = {type, .value=value};
	enqueue(event);
	uint8_t data[1] = {value};
	can_send(type, data, 1);
}

void em_event_empty(EmEventType type) {
	const EmEvent event = {type};
	enqueue(event);
	can_send_empty(type);	
}
