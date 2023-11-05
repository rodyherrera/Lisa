#ifndef LISA_CLASSES_CHTTPL_HPP
#define LISA_CLASSES_CHTTPL_HPP
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class CHTTPL{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static JSValueRef CreateServer(JSContextRef Context, JSObjectRef Function, 
                JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
    };
};

#endif