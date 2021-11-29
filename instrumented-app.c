/*
 * Copyright (C) 2021 Francis Deslauriers <francis.deslauriers@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "embedded-sys.h"

#include <lttng/tracepoint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

enum {
        INIT = 0,
        PREPARE = 1,
        DO_WORK = 2,
        ADJUST_CAPACITY = 3
};

#define NB_ITER 50
#define TIMING_RAND 302121
int main(int argc, char **argv)
{
	uint64_t i;

	srand(time(NULL));

	tracepoint(embedded_sys, handle_command, INIT);
	usleep(124);
	tracepoint(embedded_sys, handle_command, PREPARE);

	while (1) {
		for (i = 0; i < NB_ITER; i++) {
			tracepoint(embedded_sys, current_temp, (rand() % 33) + 50);

			usleep(rand() % 1331);
			if (rand() % 5 == 0 ) {
				tracepoint(embedded_sys, handle_command, DO_WORK);
			}
			usleep(rand() % TIMING_RAND);
		}

		tracepoint(embedded_sys, handle_command, ADJUST_CAPACITY);
		usleep(rand() % TIMING_RAND);

		tracepoint(embedded_sys, current_temp, 67);
		usleep(rand() % TIMING_RAND);

		tracepoint(embedded_sys, handle_command, DO_WORK);
		tracepoint(embedded_sys, current_temp, 78);
		usleep(rand() % TIMING_RAND);

		tracepoint(embedded_sys, current_temp, 84);
		usleep(rand() % TIMING_RAND);

		tracepoint(embedded_sys, current_temp, 95);
		usleep(rand() % TIMING_RAND);

		tracepoint(embedded_sys, current_temp, 98);
		usleep(rand() % TIMING_RAND);

		for (i = 0; i < NB_ITER; i++) {
			tracepoint(embedded_sys, large_event,
				"This text would take off a lot of space in the ringbuffer.");

			usleep(rand() % 1331);
		}
	}

	return 0;
}
