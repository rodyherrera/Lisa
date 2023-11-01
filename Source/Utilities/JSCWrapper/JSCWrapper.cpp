#include <iostream>
#include "JSCWrapper.hpp"

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

JSObjectRef Lisa::Utilities::JSCWrapper::CreateFunctionWithCapturedVariables(JSContextRef Context, JSObjectRef ThisObject, const char* name, JSObjectCallAsFunctionCallback callback, void* data){
    JSStringRef NameString = JSStringCreateWithUTF8CString(name);
    std::cout << "Creating function " << name << std::endl;
    JSObjectRef Function = JSObjectMakeFunctionWithCallback(Context, NameString, callback);
    std::cout << "Setting private data" << std::endl;
    JSObjectSetPrivate(Function, data);
    std::cout << "Releasing name string" << std::endl;
    JSStringRelease(NameString);
    std::cout << "Returning function" << std::endl;
    return Function;
}


JSObjectRef Lisa::Utilities::JSCWrapper::GetGlobalObject(JSContextRef Context, const char* Object){
    JSStringRef GlobalName = JSStringCreateWithUTF8CString(Object);
    JSObjectRef GlobalObject = (JSObjectRef)JSObjectGetProperty(Context, JSContextGetGlobalObject(Context), GlobalName, NULL);
    JSStringRelease(GlobalName);
    return GlobalObject;
};