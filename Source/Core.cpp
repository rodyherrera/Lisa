#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include <uv.h>
#include "Utilities/Runtime/Runtime.hpp"
#include "Classes/Console/Console.hpp"
#include "Classes/System/System.hpp"
#include "Classes/CHTTPL/CHTTPL.hpp"
#include "Classes/UUID/UUID.hpp"
#include "Classes/SQLite3/SQLite3.hpp"
#include "Classes/FileSystem/FileSystem.hpp"
#include "Methods/SetTimeout/SetTimeout.hpp"
#include "Methods/SetInterval/SetInterval.hpp"
#include "Methods/ClearTimer/ClearTimer.hpp"

int main(int argc, char const *argv[]){
    if(argc < 2){
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    for(int ArgumentIterator = 1; ArgumentIterator < argc; ArgumentIterator++){
        std::string Content = Lisa::Utilities::Runtime::ReadFile(argv[ArgumentIterator]);
        if(Content == ""){
            std::cout << "Failed to read file: " << argv[ArgumentIterator] << std::endl;
            return 1;
        }        
        
        uv_loop_t *Loop = uv_default_loop();
        
        JSContextGroupRef ContextGroup = JSContextGroupCreate();
        JSContextRef Context = JSGlobalContextCreateInGroup(ContextGroup, nullptr);
        JSObjectRef GlobalObject = JSContextGetGlobalObject(Context);

        Lisa::Classes::Console::Init(Context, GlobalObject);
        Lisa::Classes::System::Init(Context, GlobalObject);
        Lisa::Classes::CHTTPL::Init(Context, GlobalObject);
        Lisa::Classes::FileSystem::Init(Context, GlobalObject);
        Lisa::Classes::UUID::Init(Context, GlobalObject);
        Lisa::Classes::SQLite3::Init(Context, GlobalObject);

        JSStringRef SetTimeoutName = JSStringCreateWithUTF8CString("SetTimeout");
        JSObjectRef SetTimeoutFunction = JSObjectMakeFunctionWithCallback(Context, SetTimeoutName, Lisa::Methods::SetTimeout);
        JSObjectSetProperty(Context, GlobalObject, SetTimeoutName, SetTimeoutFunction, kJSPropertyAttributeNone, NULL);
        JSStringRelease(SetTimeoutName);

        JSStringRef SetIntervalName = JSStringCreateWithUTF8CString("SetInterval");
        JSObjectRef SetIntervalFunction = JSObjectMakeFunctionWithCallback(Context, SetIntervalName, Lisa::Methods::SetInterval);
        JSObjectSetProperty(Context, GlobalObject, SetIntervalName, SetIntervalFunction, kJSPropertyAttributeNone, NULL);
        JSStringRelease(SetIntervalName);

        JSStringRef ClearTimerName = JSStringCreateWithUTF8CString("ClearTimer");
        JSObjectRef ClearTimerFunction = JSObjectMakeFunctionWithCallback(Context, ClearTimerName, Lisa::Methods::ClearTimer);
        JSObjectSetProperty(Context, GlobalObject, ClearTimerName, ClearTimerFunction, kJSPropertyAttributeNone, NULL);
        JSStringRelease(ClearTimerName);

        JSStringRef Script = JSStringCreateWithUTF8CString(Content.c_str());
        JSValueRef Exception = nullptr;
        
        JSEvaluateScript(Context, Script, nullptr, nullptr, 0, &Exception);

        if(Exception){
            JSStringRef ExceptionString = JSValueToStringCopy(Context, Exception, nullptr);
            size_t ExceptionStringLength = JSStringGetMaximumUTF8CStringSize(ExceptionString);
            char *ExceptionStringBuffer = new char[ExceptionStringLength];
            JSStringGetUTF8CString(ExceptionString, ExceptionStringBuffer, ExceptionStringLength);
            std::cout << "Exception: " << ExceptionStringBuffer << std::endl;
            delete[] ExceptionStringBuffer;
            JSStringRelease(ExceptionString);
        }

        uv_run(Loop, UV_RUN_DEFAULT);

        JSStringRelease(Script);
        JSContextGroupRelease(ContextGroup);
    }

    return 0;
};