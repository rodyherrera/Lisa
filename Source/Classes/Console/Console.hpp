#ifndef LISA_CLASSES_CONSOLE_HPP
#define LISA_CLASSES_CONSOLE_HPP
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class Console{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static JSValueRef LogCallback(JSContextRef Context, JSObjectRef Function, 
                JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
    };
};

#endif