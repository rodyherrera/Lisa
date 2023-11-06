#ifndef LISA_CLASSES_UUID_HPP
#define LISA_CLASSES_UUID_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class UUID{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(v1);
            JSC_FUNC_DEF(v5);
            JSC_FUNC_DEF(v4);
    };
};

#endif