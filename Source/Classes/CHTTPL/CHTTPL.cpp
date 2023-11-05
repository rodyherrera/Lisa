#include <iostream>
#include <thread>
#include "CHTTPL.hpp"
#include "CPP-HTTP-LIB.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"
#include "../../Utilities/HTTPServer/HTTPServer.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::CHTTPL::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef CHTTPLObject = JSCWrapper::CreateObject(Context, GlobalObject, "CHTTPL");
    JSCWrapper::CreateFunction(Context, CHTTPLObject, "CreateServer", CHTTPL::CreateServer);  
};

JSC_FUNC(Classes::CHTTPL, CreateServer){
    httplib::Server* Server = new httplib::Server();
    HTTPServer::SetDefaultHeaders(*Server);

    JSObjectRef ReturnValue = JSObjectMake(Context, NULL, NULL);
    JSCWrapper::SetObjectInObject(Context, ReturnValue, "Server", Server);

    JW_CREATE_FUNC(SetKeepAliveMaxCount, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int KeepAliveMaxCount = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "KeepAliveMaxCount");
        Server->set_keep_alive_max_count(KeepAliveMaxCount);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetKeepAliveTimeout, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int KeepAliveTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "KeepAliveTimeout");
        Server->set_keep_alive_timeout(KeepAliveTimeout);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetReadTimeout, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int ReadTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "ReadTimeout");
        Server->set_read_timeout(ReadTimeout);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetRequestTimeout, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string MountPoint = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string Directory = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
        bool IsMounted = Server->set_mount_point(MountPoint.c_str(), Directory.c_str());
        return JSValueMakeBoolean(Context, IsMounted);
    });

    JW_CREATE_FUNC(SetMountPoint, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string Directory = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Server->set_base_dir(Directory.c_str());
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetDefaultFileMimetype, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string Mimetype = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Server->set_default_file_mimetype(Mimetype.c_str());
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetFileExtensionAndMimetypeMapping, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        JSObjectRef ArgumentsObject = JSValueToObject(Context, Arguments[0], NULL);
        JSPropertyNameArrayRef Keys = JSObjectCopyPropertyNames(Context, ArgumentsObject);
        size_t KeysCount = JSPropertyNameArrayGetCount(Keys);
        for(size_t i = 0; i < KeysCount; i++){
            JSStringRef Key = JSPropertyNameArrayGetNameAtIndex(Keys, i);
            JSValueRef Value = JSObjectGetProperty(Context, ArgumentsObject, Key, NULL);
            std::string KeyString = JSCWrapper::GetStringFromJSString(Key);
            std::string ValueString = JSCWrapper::GetStringFromJSValue(Context, Value);
            Server->set_file_extension_and_mimetype_mapping(KeyString.c_str(), ValueString.c_str());
        }
        JSPropertyNameArrayRelease(Keys);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(RemoveMountPoint, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string MountPoint = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        bool IsRemoved = Server->remove_mount_point(MountPoint.c_str());
        return JSValueMakeBoolean(Context, IsRemoved);
    });

    JW_CREATE_FUNC(SetWriteTimeout, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int WriteTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "WriteTimeout");
        Server->set_write_timeout(WriteTimeout);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetIdleInterval, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int IdleInterval = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "IdleInterval");
        Server->set_idle_interval(IdleInterval);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetPayloadMaxLength, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int PayloadMaxLength = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "PayloadMaxLength");
        Server->set_payload_max_length(PayloadMaxLength);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetTCPNoDelay, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const bool TCPNoDelay = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "TCPNoDelay");
        Server->set_tcp_nodelay(TCPNoDelay);
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(IsValid, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        return JSValueMakeBoolean(Context, Server->is_valid());
    });

    JW_CREATE_FUNC(Stop, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        Server->stop();
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(IsRunning, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        return JSValueMakeBoolean(Context, Server->is_running());
    });

    JW_CREATE_FUNC(Get, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Get(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Post, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Post(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Put, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Put(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Patch, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Patch(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Delete, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Delete(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Options, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Options(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            HTTPServer::HandleHTTPRequest(Context, ThisObject, const_cast<httplib::Request&>(Request), Response, Callback);
        });
        
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Listen, ReturnValue){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        JSObjectRef ArgumentsObject = JSValueToObject(Context, Arguments[0], NULL);
        const std::string Hostname = JSCWrapper::GetKeyValueFromJSObjectAsString(Context, ArgumentsObject, "Hostname");
        const int Port = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ArgumentsObject, "Port");
        bool IsError = false;
        std::thread ListenThread([&](){
            IsError = Server->listen(Hostname.c_str(), Port);
        });
        JSValueRef CallbackArguments[1] = { JSValueMakeBoolean(Context, IsError) };
        JSCWrapper::CallFunction(Context, Arguments[1], ThisObject, 1, CallbackArguments);
        ListenThread.join();

        return JSC_MAKE_UNDEFINED;
    });

    return ReturnValue;
};