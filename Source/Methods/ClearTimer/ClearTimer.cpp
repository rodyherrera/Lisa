#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include "ClearTimer.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

JSValueRef Methods::ClearTimer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    Runtime::ClearUVTimer(Context, Arguments[0]);
    return JSValueMakeUndefined(Context);
}