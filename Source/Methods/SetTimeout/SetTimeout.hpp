#include <iostream>
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Methods{
    JSValueRef SetTimeout(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
};
