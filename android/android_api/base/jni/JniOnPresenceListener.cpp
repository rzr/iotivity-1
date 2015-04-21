/*
* //******************************************************************
* //
* // Copyright 2015 Intel Corporation.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
* //
* // Licensed under the Apache License, Version 2.0 (the "License");
* // you may not use this file except in compliance with the License.
* // You may obtain a copy of the License at
* //
* //      http://www.apache.org/licenses/LICENSE-2.0
* //
* // Unless required by applicable law or agreed to in writing, software
* // distributed under the License is distributed on an "AS IS" BASIS,
* // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* // See the License for the specific language governing permissions and
* // limitations under the License.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
#include "JniOnPresenceListener.h"
#include "JniUtils.h"

using namespace std;

JniOnPresenceListener::JniOnPresenceListener(JNIEnv *env, jobject jListener)
{
    m_jwListener = env->NewWeakGlobalRef(jListener);
}

JniOnPresenceListener::~JniOnPresenceListener()
{
    LOGD("~JniOnPresenceListener");

    if (m_jwListener)
    {
        jint ret;
        JNIEnv *env = GetJNIEnv(ret);
        if (NULL == env) return;

        env->DeleteWeakGlobalRef(m_jwListener);

        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
    }
}

void JniOnPresenceListener::onPresenceCallback(OCStackResult result, const unsigned int nonce,
    const std::string& hostAddress)
{
    LOGI("JniOnPresenceListener::onPresenceCallback");

    jint ret;
    JNIEnv *env = GetJNIEnv(ret);
    if (NULL == env) return;

    std::string enumField = JniUtils::stackResultToStr(result);
    if (enumField.empty())
    {
        ThrowOcException(JNI_INVALID_VALUE, "Unexpected OCStackResult value");
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
        return;
    }

    jobject jPresenceStatus = env->CallStaticObjectMethod(g_cls_OcPresenceStatus,
        g_mid_OcPresenceStatus_get, env->NewStringUTF(enumField.c_str()));

    jobject jListener = env->NewLocalRef(m_jwListener);
    if (!jListener)
    {
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
        return;
    }

    jclass clsL = env->GetObjectClass(jListener);
    jmethodID midL = env->GetMethodID(clsL, "onPresence",
        "(Lorg/iotivity/base/OcPresenceStatus;ILjava/lang/String;)V");

    env->CallVoidMethod(jListener, midL, jPresenceStatus,
        (jint)nonce, env->NewStringUTF(hostAddress.c_str()));

    env->DeleteLocalRef(jListener);

    if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
}

jweak JniOnPresenceListener::getJWListener()
{
    return this->m_jwListener;
}