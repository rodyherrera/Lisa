#ifndef LISA_CLASSES_CONSOLE_HPP
#define LISA_CLASSES_CONSOLE_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class Console{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static LISA_JS_FUNC_DEF(Log);
    };
};

#endif