/*
 * Copyright (C) 2020 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 *
 * SPDX-License-Identifier: MIT
 *
 */

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER embedded_sys

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./embedded-sys.h"

#if !defined(__EMBEDDED_SYS_H__) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __EMBEDDED_SYS_H__

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(embedded_sys, current_temp,
	TP_ARGS(uint64_t, curr_temp),
	TP_FIELDS(
		ctf_integer(uint64_t, temperature, curr_temp)
	)
)

TRACEPOINT_ENUM(
        embedded_sys,
        cmd,
        TP_ENUM_VALUES(
                ctf_enum_value("INIT", 0)
                ctf_enum_value("PREPARE", 1)
                ctf_enum_value("DO_WORK", 2)
                ctf_enum_value("ADJUST_CAPACITY", 3)
        )
)

TRACEPOINT_EVENT(embedded_sys, handle_command,
	TP_ARGS(int, cmd),
	TP_FIELDS(
		ctf_enum(embedded_sys, cmd, int, cmd, cmd)
	)
)

TRACEPOINT_EVENT(embedded_sys, large_event,
	TP_ARGS(char *, str),
	TP_FIELDS(
		ctf_string(str, str)
	)
)

#endif /* __EMBEDDED_SYS_H__ */

#include <lttng/tracepoint-event.h>
