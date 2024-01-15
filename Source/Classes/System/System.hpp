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

#ifndef LISA_CLASSES_SYSTEM_HPP
#define LISA_CLASSES_SYSTEM_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class System{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(HRTime);
            JSC_FUNC_DEF(Uptime);
            JSC_FUNC_DEF(Uname);
            JSC_FUNC_DEF(Environ);
            JSC_FUNC_DEF(Platform);
            JSC_FUNC_DEF(GetEnviron);
            JSC_FUNC_DEF(SetEnviron);
            JSC_FUNC_DEF(UnsetEnviron);
            JSC_FUNC_DEF(ChangeWorkingDirectory);
            JSC_FUNC_DEF(CurrentWorkingDirectory);
            JSC_FUNC_DEF(HomeDirectory);
            JSC_FUNC_DEF(TempDirectory);
            JSC_FUNC_DEF(CPUInfo);
            JSC_FUNC_DEF(NetworkInterfaces);
            JSC_FUNC_DEF(GetHostname);
            JSC_FUNC_DEF(GetPID);
            JSC_FUNC_DEF(GetPPID);
            JSC_FUNC_DEF(Sleep);
    };
};

#endif