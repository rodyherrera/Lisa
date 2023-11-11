#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Utilities::JSCWrapper{
    JSObjectRef CreateObject(JSContextRef Context, JSObjectRef GlobalObject, const char* ObjectName);
    JSObjectRef CreateFunction(JSContextRef Context, JSObjectRef GlobalObject, 
            const char* FunctionName, JSObjectCallAsFunctionCallback FunctionCallback);
    JSObjectRef GetGlobalObject(JSContextRef Context, const char* Object);
    const std::string GetStringFromJSValue(JSContextRef Context, JSValueRef Value);
    void SetDoubleProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const double Value);
    const std::string GetKeyValueFromJSObjectAsString(JSContextRef Context, JSObjectRef Object, const char* Key);
    const int GetKeyValueFromJSObjectAsInteger(JSContextRef Context, JSObjectRef Object, const char* Key);
    JSValueRef CallCallbackFunctionFromJSObject(JSContextRef Context, JSObjectRef Object, const char* FunctionName, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception);
    const std::string GetFormattedJSONFromJSValue(JSContextRef Context, JSValueRef Value);
    void SetStringProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const char* Value);
    void SetIntegerProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const int Value);
    JSValueRef CreateString(JSContextRef Context, const char* String);
    JSObjectRef GetKeyValueFromJSObjectAsFunction(JSContextRef Context, JSObjectRef Object, const char* Key);
    void SetObjectInObject(JSContextRef Context, JSObjectRef ParentObject, const char* PropertyName, void* ChildObject);
    void* GetObjectFromObject(JSContextRef Context, JSObjectRef ParentObject, const char* PropertyName);
    void CallFunction(JSContextRef Context, JSValueRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[]);
    const std::string GetStringFromJSString(JSStringRef String);
    const double GetNumberFromJSValue(JSContextRef Context, JSValueRef Value);
    const bool GetKeyValueFromJSObjectAsBoolean(JSContextRef Context, JSObjectRef Object, const char* Key);
};