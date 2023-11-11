#include <iostream>
#include <vector>
#include "JSCWrapper.hpp"

const std::string Lisa::Utilities::JSCWrapper::GetFormattedJSONFromJSValue(JSContextRef Context, JSValueRef Value){
    JSStringRef JSONString = JSValueCreateJSONString(Context, Value, 4, NULL);
    size_t JSONStringLength = JSStringGetMaximumUTF8CStringSize(JSONString);
    char* JSONStringBuffer = new char[JSONStringLength];
    JSStringGetUTF8CString(JSONString, JSONStringBuffer, JSONStringLength);
    std::string FormattedJSONString = std::string(JSONStringBuffer);
    delete[] JSONStringBuffer;
    JSStringRelease(JSONString);
    return FormattedJSONString;
};

void Lisa::Utilities::JSCWrapper::SetDoubleProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const double Value){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSObjectSetProperty(Context, Object, KeyString, JSValueMakeNumber(Context, Value), kJSPropertyAttributeNone, NULL);
    JSStringRelease(KeyString);
};

const double Lisa::Utilities::JSCWrapper::GetNumberFromJSValue(JSContextRef Context, JSValueRef Value){
    return JSValueToNumber(Context, Value, NULL);
};

const std::string Lisa::Utilities::JSCWrapper::GetStringFromJSString(JSStringRef String){
    size_t StringLength = JSStringGetMaximumUTF8CStringSize(String);
    char StringBuffer[StringLength];
    JSStringGetUTF8CString(String, StringBuffer, StringLength);
    return std::string(StringBuffer);
};

JSValueRef Lisa::Utilities::JSCWrapper::CreateString(JSContextRef Context, const char* String){
    JSStringRef StringRef = JSStringCreateWithUTF8CString(String);
    JSValueRef Value = JSValueMakeString(Context, StringRef);
    JSStringRelease(StringRef);
    return Value;
};

JSObjectRef Lisa::Utilities::JSCWrapper::GetKeyValueFromJSObjectAsFunction(JSContextRef Context, JSObjectRef Object, const char* Key){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSValueRef Value = JSObjectGetProperty(Context, Object, KeyString, NULL);
    JSStringRelease(KeyString);
    return JSValueToObject(Context, Value, NULL);
};

void Lisa::Utilities::JSCWrapper::SetStringProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const char* Value){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSStringRef ValueString = JSStringCreateWithUTF8CString(Value);
    JSObjectSetProperty(Context, Object, KeyString, JSValueMakeString(Context, ValueString), kJSPropertyAttributeNone, NULL);
    JSStringRelease(KeyString);
    JSStringRelease(ValueString);
};

void Lisa::Utilities::JSCWrapper::SetIntegerProperty(JSContextRef Context, JSObjectRef Object, const char* Key, const int Value){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSObjectSetProperty(Context, Object, KeyString, JSValueMakeNumber(Context, Value), kJSPropertyAttributeNone, NULL);
    JSStringRelease(KeyString);
};

JSValueRef Lisa::Utilities::JSCWrapper::CallCallbackFunctionFromJSObject(JSContextRef Context, JSObjectRef Object, const char* FunctionName, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    JSStringRef FunctionNameString = JSStringCreateWithUTF8CString(FunctionName);
    JSObjectRef Function = (JSObjectRef)JSObjectGetProperty(Context, Object, FunctionNameString, NULL);
    JSStringRelease(FunctionNameString);
    return JSObjectCallAsFunction(Context, Function, Object, ArgumentsLength, Arguments, Exception);
};

const std::string Lisa::Utilities::JSCWrapper::GetKeyValueFromJSObjectAsString(JSContextRef Context, JSObjectRef Object, const char* Key){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSValueRef Value = JSObjectGetProperty(Context, Object, KeyString, NULL);
    JSStringRelease(KeyString);
    return Lisa::Utilities::JSCWrapper::GetStringFromJSValue(Context, Value);
};

const int Lisa::Utilities::JSCWrapper::GetKeyValueFromJSObjectAsInteger(JSContextRef Context, JSObjectRef Object, const char* Key){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSValueRef Value = JSObjectGetProperty(Context, Object, KeyString, NULL);
    JSStringRelease(KeyString);
    return JSValueToNumber(Context, Value, NULL);
};

const bool Lisa::Utilities::JSCWrapper::GetKeyValueFromJSObjectAsBoolean(JSContextRef Context, JSObjectRef Object, const char* Key){
    JSStringRef KeyString = JSStringCreateWithUTF8CString(Key);
    JSValueRef Value = JSObjectGetProperty(Context, Object, KeyString, NULL);
    JSStringRelease(KeyString);
    return JSValueToBoolean(Context, Value);
};

const std::string Lisa::Utilities::JSCWrapper::GetStringFromJSValue(JSContextRef Context, JSValueRef Value){
    JSStringRef StringRef = JSValueToStringCopy(Context, Value, NULL);
    size_t StringLength = JSStringGetMaximumUTF8CStringSize(StringRef);
    char String[StringLength];
    JSStringGetUTF8CString(StringRef, String, StringLength);
    JSStringRelease(StringRef);
    return std::string(String);
};

void Lisa::Utilities::JSCWrapper::CallFunction(JSContextRef Context, JSValueRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[]){
    JSObjectCallAsFunction(Context, (JSObjectRef)Function, ThisObject, ArgumentsLength, Arguments, NULL);
};

void Lisa::Utilities::JSCWrapper::SetObjectInObject(JSContextRef Context, JSObjectRef ParentObject, const char* PropertyName, void* ChildObject) {
    JSStringRef JSPropertyName = JSStringCreateWithUTF8CString(PropertyName);
    JSClassDefinition Definition = kJSClassDefinitionEmpty;
    JSClassRef Class = JSClassCreate(&Definition);
    JSObjectRef JSChildObject = JSObjectMake(Context, Class, ChildObject);
    JSObjectSetProperty(Context, ParentObject, JSPropertyName, JSChildObject, kJSPropertyAttributeNone, NULL);
    JSStringRelease(JSPropertyName);
}

void* Lisa::Utilities::JSCWrapper::GetObjectFromObject(JSContextRef Context, JSObjectRef ParentObject, const char* PropertyName) {
    JSStringRef JSPropertyName = JSStringCreateWithUTF8CString(PropertyName);
    JSValueRef ChildValue = JSObjectGetProperty(Context, ParentObject, JSPropertyName, NULL);
    JSStringRelease(JSPropertyName);
    JSObjectRef ChildObject = JSValueToObject(Context, ChildValue, NULL);
    return JSObjectGetPrivate(ChildObject);
}

JSObjectRef Lisa::Utilities::JSCWrapper::CreateObject(JSContextRef Context, JSObjectRef GlobalObject, const char* ObjectName){
    JSClassDefinition ClassDefinition = kJSClassDefinitionEmpty;
    JSClassRef Class = JSClassCreate(&ClassDefinition);
    JSStringRef NameString = JSStringCreateWithUTF8CString(ObjectName);
    JSObjectRef Object = JSObjectMake(Context, Class, NULL);
    JSObjectSetProperty(Context, GlobalObject, NameString, Object, kJSPropertyAttributeNone, NULL);
    JSStringRelease(NameString);
    return Object;
};

JSObjectRef Lisa::Utilities::JSCWrapper::CreateFunction(JSContextRef Context, JSObjectRef GlobalObject, 
        const char* FunctionName, JSObjectCallAsFunctionCallback FunctionCallback){
    JSStringRef NameString = JSStringCreateWithUTF8CString(FunctionName);
    JSObjectRef Function = JSObjectMakeFunctionWithCallback(Context, NameString, FunctionCallback);
    JSObjectSetProperty(Context, GlobalObject, NameString, Function, kJSPropertyAttributeNone, NULL);
    JSStringRelease(NameString);
    return Function;
};

JSObjectRef Lisa::Utilities::JSCWrapper::GetGlobalObject(JSContextRef Context, const char* Object){
    JSStringRef GlobalName = JSStringCreateWithUTF8CString(Object);
    JSObjectRef GlobalObject = (JSObjectRef)JSObjectGetProperty(Context, JSContextGetGlobalObject(Context), GlobalName, NULL);
    JSStringRelease(GlobalName);
    return GlobalObject;
};