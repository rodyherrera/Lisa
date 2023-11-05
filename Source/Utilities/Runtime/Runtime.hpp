#include <iostream>
#include <JavaScriptCore/JavaScript.h>

#define LISA_JS_FUNC_DEF(Name) JSValueRef Name(JSContextRef Context, JSObjectRef Function, \
    JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

#define LISA_JS_FUNC(Namespace, Name) JSValueRef Namespace::Name(JSContextRef Context, JSObjectRef Function, \
    JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

namespace Lisa::Utilities::Runtime{
    const std::string ReadFile(const std::string Path);
    void ClearUVTimer(JSContextRef Context, JSValueRef TimerValue);
};