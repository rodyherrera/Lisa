/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodyherrera/Lisa/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#ifndef LISA_CLASSES_NETWORK_HPP
#define LISA_CLASSES_NETWORK_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class Network{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(IPv4);
            JSC_FUNC_DEF(IPv6);
            JSC_FUNC_DEF(Broadcast);
            JSC_FUNC_DEF(Any);
            JSC_FUNC_DEF(IsWildcard);
            JSC_FUNC_DEF(IsBroadcast);
            JSC_FUNC_DEF(IsLoopback);
            JSC_FUNC_DEF(IsMulticast);
            JSC_FUNC_DEF(IsUnicast);
            JSC_FUNC_DEF(IsLinkLocal);
            JSC_FUNC_DEF(IsSiteLocal);
            JSC_FUNC_DEF(IsIPv4Compatible);
            JSC_FUNC_DEF(IsIPv4Mapped);
    };
};

#endif