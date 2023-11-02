#ifndef LISA_CLASSES_SYSTEM_HPP
#define LISA_CLASSES_SYSTEM_HPP
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class System{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static JSValueRef HRTime(JSContextRef Context, JSObjectRef Function, 
                JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef Uptime(JSContextRef Context, JSObjectRef Function,
                JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef Uname(JSContextRef Context, JSObjectRef Function,
                JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef Environ(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef GetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef SetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef UnsetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef ChangeWorkingDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef CurrentWorkingDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef HomeDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef TempDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef CPUInfo(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef NetworkInterfaces(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef GetHostname(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef GetPID(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef GetPPID(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
            static JSValueRef Sleep(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
    };
};

#endif