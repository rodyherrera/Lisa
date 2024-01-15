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
#include <fstream>
#include <uv.h>
#include <JavaScriptCore/JavaScript.h>
#include "Runtime.hpp"

const std::string Lisa::Utilities::Runtime::ReadFile(const std::string Path){
    std::ifstream File(Path);
    if (!File.is_open()) {
        std::cout << "Failed to open file: " << Path << std::endl;
        return "";
    }
    std::string Content((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.close();
    return Content;
};

void Lisa::Utilities::Runtime::ClearUVTimer(JSContextRef Context, JSValueRef TimerValue){
    double Timer = JSValueToNumber(Context, TimerValue, NULL);
    uv_timer_stop((uv_timer_t*)(uintptr_t)Timer);
    uv_close((uv_handle_t*)(uintptr_t)Timer, [](uv_handle_t *Timer) {
        delete (uv_timer_t*)Timer;
    });
};