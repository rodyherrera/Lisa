#ifndef LISA_CLASSES_ACL_HPP
#define LISA_CLASSES_ACL_HPP
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class ACL{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static JSValueRef TCPServer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef TCPClient(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef HTTPServer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
    };
};

#endif