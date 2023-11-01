#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include "../../Utilities/Runtime/Runtime.hpp"
#include "ClearTimer.hpp"

JSValueRef Lisa::Methods::ClearTimer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    Lisa::Utilities::Runtime::ClearUVTimer(Context, Arguments[0]);
    return JSValueMakeUndefined(Context);
}