#!/bin/bash

SESSION_NAME="snapshot-example"
TRIGGER_NAME="snapshot-on-high-temp"

lttng add-trigger --name $TRIGGER_NAME \
	--condition event-rule-matches --capture=temperature \
		--type=user \
		--name=embedded_sys:current_temp \
		--filter="temperature > 95" \
	--action=snapshot-session $SESSION_NAME \
	--action=notify


lttng create $SESSION_NAME --snapshot

lttng enable-event --userspace  "embedded_sys:*"

lttng start

lttng status

lttng list-triggers

./instrumented-app

lttng stop
lttng remove-trigger $TRIGGER_NAME
