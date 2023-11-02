#include <iostream>
#include "Console.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::Console::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef ConsoleObject = JSCWrapper::CreateObject(Context, GlobalObject, "Console");
    JSCWrapper::CreateFunction(Context, ConsoleObject, "Log", Console::LogCallback);
};

JSValueRef Classes::Console::LogCallback(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
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
