//******************************************************************
//
// Copyright 2014 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Do not remove the include below
#include "Arduino.h"

#include "logger.h"
#include "ocstack.h"
#include <string.h>

#include "common.h"
#include "networkHandler.h"
#include "resourceHandler.h"

typedef void (*EventCallback)(ES_RESULT);

OCStackResult Init();

ES_RESULT FindNetworkForOnboarding(NetworkType networkType, EventCallback);
ES_RESULT FindNetworkForOnboarding(NetworkType networkType, const char *name, const char *pass,
        EventCallback);

//OCStackResult FindNetworkForOnboarding(NetworkType networkType, char *name);
//OCStackResult FindNetworkForOnboarding(NetworkType networkType, char *name, char *pass);

ES_RESULT InitializeProvisioning(EventCallback);