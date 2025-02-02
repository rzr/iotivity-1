//******************************************************************
//
// Copyright 2015 Samsung Electronics All Rights Reserved.
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
#include "RCSDiscoveryManager.h"
#include "RCSDiscoveryManagerImpl.h"

#define TAG "RCSDiscoveryManager"

namespace OIC {
    namespace Service {

        RCSDiscoveryManager* RCSDiscoveryManager::getInstance() {
            static RCSDiscoveryManager instance;
            return &instance;
        }

        std::unique_ptr<RCSDiscoveryManager::DiscoveryTask> RCSDiscoveryManager::discoverResource
        (const RCSAddress& address, ResourceDiscoveredCallback cb) {
            return discoverResourceByType(address, OC_RSRVD_WELL_KNOWN_URI, "",
                    std::move(cb));
        }

        std::unique_ptr<RCSDiscoveryManager::DiscoveryTask> RCSDiscoveryManager::discoverResource
        (const RCSAddress& address, const std::string& relativeURI, ResourceDiscoveredCallback cb) {
            return discoverResourceByType(address, relativeURI, "", std::move(cb));
        }

        std::unique_ptr<RCSDiscoveryManager::DiscoveryTask> RCSDiscoveryManager::discoverResourceByType(
                const RCSAddress& address, const std::string& resourceType, ResourceDiscoveredCallback cb) {
            return discoverResourceByType(address, OC_RSRVD_WELL_KNOWN_URI,
                    resourceType, std::move(cb));
        }

        std::unique_ptr<RCSDiscoveryManager::DiscoveryTask> RCSDiscoveryManager::discoverResourceByType(
                const RCSAddress& address, const std::string& relativeURI,
                const std::string& resourceType, ResourceDiscoveredCallback cb) {
           return RCSDiscoveryManagerImpl::getInstance()->startDiscovery(address,
                   relativeURI.empty() ? OC_RSRVD_WELL_KNOWN_URI : relativeURI,
                   resourceType, std::move(cb));
        }
        RCSDiscoveryManager::DiscoveryTask::~DiscoveryTask(){
            cancel();
        }
        bool RCSDiscoveryManager::DiscoveryTask::isCanceled() {
            auto it = RCSDiscoveryManagerImpl::getInstance();

            if(it->m_discoveryMap.find(m_id) == it->m_discoveryMap.end())
            {
                    return true;
            }
            return false;
        }

        void RCSDiscoveryManager::DiscoveryTask::cancel(){
            RCSDiscoveryManagerImpl::getInstance()->cancel(m_id);
        }
    }
}
