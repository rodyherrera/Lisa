#ifndef UTILITIES_JSCWRAPPER_HPP
#define UTILITIES_JSCWRAPPER_HPP
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Utilities::JSCWrapper{
    JSObjectRef CreateObject(JSContextRef Context, JSObjectRef GlobalObject, const char* ObjectName);
    JSObjectRef CreateFunction(JSContextRef Context, JSObjectRef GlobalObject, 
            const char* FunctionName, JSObjectCallAsFunctionCallback FunctionCallback);
    JSObjectRef GetGlobalObject(JSContextRef Context, const char* Object);

    JSObjectRef CreateFunctionWithCapturedVariables(JSContextRef Context, JSObjectRef ThisObject, const char* name, JSObjectCallAsFunctionCallback callback, void* data);
};

#endif