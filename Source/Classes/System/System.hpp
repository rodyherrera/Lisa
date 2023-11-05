#ifndef LISA_CLASSES_SYSTEM_HPP
#define LISA_CLASSES_SYSTEM_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class System{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            LISA_JS_FUNC_DEF(HRTime);
            LISA_JS_FUNC_DEF(Uptime);
            LISA_JS_FUNC_DEF(Uname);
            LISA_JS_FUNC_DEF(Environ);
            LISA_JS_FUNC_DEF(GetEnviron);
            LISA_JS_FUNC_DEF(SetEnviron);
            LISA_JS_FUNC_DEF(UnsetEnviron);
            LISA_JS_FUNC_DEF(ChangeWorkingDirectory);
            LISA_JS_FUNC_DEF(CurrentWorkingDirectory);
            LISA_JS_FUNC_DEF(HomeDirectory);
            LISA_JS_FUNC_DEF(TempDirectory);
            LISA_JS_FUNC_DEF(CPUInfo);
            LISA_JS_FUNC_DEF(NetworkInterfaces);
            LISA_JS_FUNC_DEF(GetHostname);
            LISA_JS_FUNC_DEF(GetPID);
            LISA_JS_FUNC_DEF(GetPPID);
            LISA_JS_FUNC_DEF(Sleep);
    };
};

#endif