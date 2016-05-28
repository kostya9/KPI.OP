#pragma once
#include "request_dispatcher.h"
#include "student.h"
void set_callback_info(request_dispatcher_t * dispatcher, student * student);
void set_callback_external(request_dispatcher_t * dispatcher);
void set_callback_database(request_dispatcher_t * dispatcher);
void set_callback_dir(request_dispatcher_t * dispatcher);