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
#include "Console.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::Console::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef ConsoleObject = JSCWrapper::CreateObject(Context, GlobalObject, "Console");
    JSCWrapper::CreateFunction(Context, ConsoleObject, "Log", Console::Log);
};

JSC_FUNC(Classes::Console, Log){
    for(size_t ArgumentIterator = 0; ArgumentIterator < ArgumentsLength; ArgumentIterator++){
        if(JSValueIsObject(Context, Arguments[ArgumentIterator])){
            const std::string JSON = JSCWrapper::GetFormattedJSONFromJSValue(Context, Arguments[ArgumentIterator]);
            std::cout << JSON;
        }else{
            const std::string String = JSCWrapper::GetStringFromJSValue(Context, Arguments[ArgumentIterator]);
            std::cout << String;
        }
        (ArgumentIterator != (ArgumentsLength - 1)) && (std::cout << " ");
    }
    std::cout << std::endl;
    return JSValueMakeUndefined(Context);
};