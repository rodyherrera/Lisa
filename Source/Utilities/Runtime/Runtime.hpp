#include <iostream>
#include <JavaScriptCore/JavaScript.h>

#define JSC_FUNC_DEF(Name) static JSValueRef Name(JSContextRef Context, JSObjectRef Function, \
    JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

#define JSC_FUNC_NON_STATIC_DEF(Name) JSValueRef Name(JSContextRef Context, JSObjectRef Function, \
    JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

#define JSC_FUNC(Namespace, Name) JSValueRef Namespace::Name(JSContextRef Context, JSObjectRef Function, \
    JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

#define JSC_MAKE_UNDEFINED JSValueMakeUndefined(Context)

#define JW_CREATE_FUNC(FunctionName, Object) JSCWrapper::CreateFunction(Context, Object, #FunctionName, [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)

namespace Lisa::Utilities::Runtime{
    const std::string ReadFile(const std::string Path);
    void ClearUVTimer(JSContextRef Context, JSValueRef TimerValue);
};