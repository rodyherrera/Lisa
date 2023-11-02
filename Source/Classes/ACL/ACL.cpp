#include <iostream>
#include "ACL.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"
#include <thread>
#include <acl_cpp/lib_acl.hpp>
#include <fiber/go_fiber.hpp>
#include <fiber/http_server.hpp>

void Lisa::Classes::ACL::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef ACLObject = Lisa::Utilities::JSCWrapper::CreateObject(Context, GlobalObject, "ACL");
    Lisa::Utilities::JSCWrapper::CreateFunction(Context, ACLObject, "TCPServer", ACL::TCPServer);
    Lisa::Utilities::JSCWrapper::CreateFunction(Context, ACLObject, "TCPClient", ACL::TCPClient);
};

JSValueRef Lisa::Classes::ACL::TCPClient(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    if(!JSValueIsString(Context, Arguments[0])){
        std::cout << "Connect: Expected argument 1 to be a string, got " << JSValueGetType(Context, Arguments[0]) << std::endl;
        return JSValueMakeUndefined(Context);
    }
    JSStringRef AddressStringRef = JSValueToStringCopy(Context, Arguments[0], NULL);
    size_t AddressLength = JSStringGetMaximumUTF8CStringSize(AddressStringRef);
    char Address[AddressLength];
    JSStringGetUTF8CString(AddressStringRef, Address, AddressLength);
    JSStringRelease(AddressStringRef);
    int ConnectionTimeout = 5;
    int ReadWriteTimeout = 10;
    acl::socket_stream Connection;
    const bool IsConnected = Connection.open(Address, ConnectionTimeout, ReadWriteTimeout);
    if(!IsConnected){
        std::cout << "Connect: Failed to connect to " << Address << std::endl;
        return JSValueMakeUndefined(Context);
    }else{
        JSObjectRef CallbackFunction = JSValueToObject(Context, Arguments[1], NULL);
        JSObjectCallAsFunction(Context, CallbackFunction, NULL, 0, NULL, NULL);
    }
    // Get data
    JSStringRef DataStringRef = JSValueToStringCopy(Context, Arguments[2], NULL);
    size_t DataLength = JSStringGetMaximumUTF8CStringSize(DataStringRef);
    char Data[DataLength];
    JSStringGetUTF8CString(DataStringRef, Data, DataLength);
    JSStringRelease(DataStringRef);
    int BytesSend = Connection.write(Data, DataLength);
    if(BytesSend == -1){
        std::cout << "Connect: Failed to send data to " << Address << std::endl;
        return JSValueMakeUndefined(Context);
    }
    char Buffer[256];
    int Result = Connection.read(Buffer, sizeof(Buffer) - 1, false);
    if(Result > 0){
        Buffer[Result] = 0;
        JSObjectRef CallbackFunction = JSValueToObject(Context, Arguments[3], NULL);
        JSStringRef BufferStringRef = JSStringCreateWithUTF8CString(Buffer);
        JSValueRef BufferValue = JSValueMakeString(Context, BufferStringRef);
        JSStringRelease(BufferStringRef);
        JSObjectCallAsFunction(Context, CallbackFunction, NULL, 1, &BufferValue, NULL);
    }
    return JSValueMakeUndefined(Context);
};

JSValueRef Lisa::Classes::ACL::TCPServer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    if(!JSValueIsObject(Context, Arguments[0])){
        std::cout << "Listen: Expected argument 1 to be an object, got " << JSValueGetType(Context, Arguments[0]) << std::endl;
        return JSValueMakeUndefined(Context);
    }

    JSStringRef HostnameKey = JSStringCreateWithUTF8CString("Hostname");
    JSStringRef PortKey = JSStringCreateWithUTF8CString("Port");
    JSObjectRef HostnameAndPortObject = JSValueToObject(Context, Arguments[0], NULL);
    JSValueRef HostnameValue = JSObjectGetProperty(Context, HostnameAndPortObject, HostnameKey, NULL);
    JSValueRef PortValue = JSObjectGetProperty(Context, HostnameAndPortObject, PortKey, NULL);
    JSStringRelease(HostnameKey);
    JSStringRelease(PortKey);

    if(!JSValueIsString(Context, HostnameValue)){
        std::cout << "Listen: Expected argument 1 to be a string, got " << JSValueGetType(Context, HostnameValue) << std::endl;
        return JSValueMakeUndefined(Context);
    }
    if(!JSValueIsNumber(Context, PortValue)){
        std::cout << "Listen: Expected argument 2 to be a number, got " << JSValueGetType(Context, PortValue) << std::endl;
        return JSValueMakeUndefined(Context);
    }

    JSStringRef HostnameStringRef = JSValueToStringCopy(Context, HostnameValue, NULL);
    size_t HostnameLength = JSStringGetMaximumUTF8CStringSize(HostnameStringRef);
    char Hostname[HostnameLength];
    JSStringGetUTF8CString(HostnameStringRef, Hostname, HostnameLength);
    JSStringRelease(HostnameStringRef);

    int Port = JSValueToNumber(Context, PortValue, NULL);
    std::string ServerAddress = std::string(Hostname) + ":" + std::to_string(Port);

    acl::server_socket Server;
    const bool IsServerOpened = Server.open(ServerAddress.c_str()); 

    if(!IsServerOpened){
        std::cout << "Listen: Failed to open server on " << ServerAddress << std::endl;
        return JSValueMakeUndefined(Context);
    }

    if(JSValueIsObject(Context, Arguments[1])){
        JSObjectRef CallbackFunction = JSValueToObject(Context, Arguments[1], NULL);
        JSObjectCallAsFunction(Context, CallbackFunction, NULL, 0, NULL, NULL);
    }

    while(true){
        acl::socket_stream* Connection = Server.accept();
        if(Connection == NULL){
            std::cout << "Listen: Failed to accept connection on " << ServerAddress << std::endl;
            return JSValueMakeUndefined(Context);
        }
        Connection->set_rw_timeout(0);
        char Buffer[256];
        int Result = Connection->read(Buffer, sizeof(Buffer) - 1, false);
        if(Result > 0){
            Buffer[Result] = 0;
            JSObjectRef CallbackFunction = JSValueToObject(Context, Arguments[2], NULL);
            JSStringRef BufferStringRef = JSStringCreateWithUTF8CString(Buffer);
            JSValueRef BufferValue = JSValueMakeString(Context, BufferStringRef);
            JSStringRelease(BufferStringRef);
            JSValueRef ReturnValue = JSObjectCallAsFunction(Context, CallbackFunction, NULL, 1, &BufferValue, NULL);
            if(JSValueIsString(Context, ReturnValue)){
                JSStringRef ReturnValueStringRef = JSValueToStringCopy(Context, ReturnValue, NULL);
                size_t ReturnValueLength = JSStringGetMaximumUTF8CStringSize(ReturnValueStringRef);
                char ReturnValueString[ReturnValueLength];
                JSStringGetUTF8CString(ReturnValueStringRef, ReturnValueString, ReturnValueLength);
                JSStringRelease(ReturnValueStringRef);
                int BytesSend = Connection->write(ReturnValueString, ReturnValueLength);
                if(BytesSend == -1){
                    std::cout << "Listen: Failed to send data to " << ServerAddress << std::endl;
                    return JSValueMakeUndefined(Context);
                }
            }

        }
        Connection->close();
    }

    acl::fiber::schedule();

    return JSValueMakeUndefined(Context);
};