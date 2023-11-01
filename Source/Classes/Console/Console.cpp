#include <iostream>
#include "Console.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

void Lisa::Classes::Console::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef ConsoleObject = Lisa::Utilities::JSCWrapper::CreateObject(Context, GlobalObject, "Console");
    Lisa::Utilities::JSCWrapper::CreateFunction(Context, ConsoleObject, "Log", Console::LogCallback);
};

JSValueRef Lisa::Classes::Console::LogCallback(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    for(size_t ArgumentIterator = 0; ArgumentIterator < ArgumentsLength; ArgumentIterator++){
        if(JSValueIsObject(Context, Arguments[ArgumentIterator])){
            JSStringRef JSONString = JSValueCreateJSONString(Context, Arguments[ArgumentIterator], 4, NULL);
            size_t JSONStringLength = JSStringGetMaximumUTF8CStringSize(JSONString);
            char* JSONStringBuffer = new char[JSONStringLength];
            JSStringGetUTF8CString(JSONString, JSONStringBuffer, JSONStringLength);
            std::cout << JSONStringBuffer;
            delete[] JSONStringBuffer;
            JSStringRelease(JSONString);
        }else{
            JSStringRef String = JSValueToStringCopy(Context, Arguments[ArgumentIterator], NULL);
            size_t StringLength = JSStringGetMaximumUTF8CStringSize(String);
            char* StringBuffer = new char[StringLength];
            JSStringGetUTF8CString(String, StringBuffer, StringLength);
            std::cout << StringBuffer;
            delete[] StringBuffer;
            JSStringRelease(String);
        }
        if(ArgumentIterator != ArgumentsLength - 1){
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return JSValueMakeUndefined(Context);
};
