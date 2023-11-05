#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include "ClearTimer.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

JSC_FUNC(Methods, ClearTimer){
    Runtime::ClearUVTimer(Context, Arguments[0]);
    return JSC_MAKE_UNDEFINED;
}