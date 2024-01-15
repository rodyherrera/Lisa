/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodyherrera/Lisa/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include <uv.h>
#include "../../Utilities/Runtime/Runtime.hpp"
#include "SetInterval.hpp"

using namespace Lisa;

JSC_FUNC(Methods, SetInterval){
    if(!JSValueIsObject(Context, Arguments[0])){
        std::cout << "SetInterval: Expected argument 1 to be an object, got " << JSValueGetType(Context, Arguments[0]) << std::endl;
        return JSC_MAKE_UNDEFINED;
    }
    if(!JSValueIsNumber(Context, Arguments[1])){
        std::cout << "SetInterval: Expected argument 2 to be a number, got " << JSValueGetType(Context, Arguments[1]) << std::endl;
        return JSC_MAKE_UNDEFINED;
    }
    JSObjectRef FunctionObject = JSValueToObject(Context, Arguments[0], NULL);
    JSGlobalContextRef JSGlobalContext = JSContextGetGlobalContext(Context);
    struct TimerData {
        JSObjectRef FunctionObject;
        JSGlobalContextRef JSGlobalContext;
    };
    TimerData* TimerDataInstance = new TimerData{ FunctionObject, JSGlobalContext };
    uv_loop_t *Loop = uv_default_loop();
    uv_timer_t *Timer = new uv_timer_t;
    Timer->data = TimerDataInstance;
    uv_timer_init(Loop, Timer);
    uv_timer_start(Timer, [](uv_timer_t *Timer) {
        TimerData* TimerDataInstance = static_cast<TimerData*>(Timer->data);
        JSContextRef Context = TimerDataInstance->JSGlobalContext;
        JSObjectRef FunctionObject = TimerDataInstance->FunctionObject;
        JSObjectCallAsFunction(Context, FunctionObject, NULL, 0, NULL, NULL);
    }, JSValueToNumber(Context, Arguments[1], NULL), JSValueToNumber(Context, Arguments[1], NULL));
    return JSValueMakeNumber(Context, (double)(uintptr_t)Timer);
};