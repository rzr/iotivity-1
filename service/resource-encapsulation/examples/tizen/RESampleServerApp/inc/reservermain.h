/******************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#ifndef RESERVERMAIN_H__
#define RESERVERMAIN_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#include "OCPlatform.h"
#include "OCApi.h"

using namespace OC;

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "reservermain"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.resampleserver"
#endif

#define ELM_DEMO_EDJ "opt/usr/apps/org.tizen.resampleserver/res/ui_controls.edj"

void start_server(void *data, Evas_Object *obj, void *event_info);

void start_server_cb(void *data, Evas_Object *obj, void *event_info);

#endif // RESERVERMAIN_H__