#include <iostream>
#include <thread>
#include "CHTTPL.hpp"
#include "CPP-HTTP-LIB.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::CHTTPL::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef CHTTPLObject = JSCWrapper::CreateObject(Context, GlobalObject, "CHTTPL");
    JSCWrapper::CreateFunction(Context, CHTTPLObject, "CreateServer", CHTTPL::CreateServer);  
};

JSValueRef Classes::CHTTPL::CreateServer(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    httplib::Server* Server = new httplib::Server();

    Server->set_default_headers({
        {"Server", "LisaJS"}
    });

    JSObjectRef ReturnValue = JSObjectMake(Context, NULL, NULL);
    JSCWrapper::SetObjectInObject(Context, ReturnValue, "Server", Server);
    
    JSCWrapper::CreateFunction(Context, ReturnValue, "SetKeepAliveMaxCount", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int KeepAliveMaxCount = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "KeepAliveMaxCount");
        Server->set_keep_alive_max_count(KeepAliveMaxCount);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetKeepAliveTimeout", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int KeepAliveTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "KeepAliveTimeout");
        Server->set_keep_alive_timeout(KeepAliveTimeout);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetReadTimeout", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int ReadTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "ReadTimeout");
        Server->set_read_timeout(ReadTimeout);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetMountPoint", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string MountPoint = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string Directory = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
        bool IsMounted = Server->set_mount_point(MountPoint.c_str(), Directory.c_str());
        return JSValueMakeBoolean(Context, IsMounted);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetBaseDirectory", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string Directory = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Server->set_base_dir(Directory.c_str());
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetDefaultFileMimetype", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string Mimetype = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Server->set_default_file_mimetype(Mimetype.c_str());
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetFileExtensionAndMimetypeMapping", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
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
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "RemoveMountPoint", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const std::string MountPoint = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        bool IsRemoved = Server->remove_mount_point(MountPoint.c_str());
        return JSValueMakeBoolean(Context, IsRemoved);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetWriteTimeout", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int WriteTimeout = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "WriteTimeout");
        Server->set_write_timeout(WriteTimeout);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetIdleInterval", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int IdleInterval = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "IdleInterval");
        Server->set_idle_interval(IdleInterval);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetPayloadMaxLength", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const int PayloadMaxLength = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "PayloadMaxLength");
        Server->set_payload_max_length(PayloadMaxLength);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "SetTCPNoDelay", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        const bool TCPNoDelay = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "TCPNoDelay");
        Server->set_tcp_nodelay(TCPNoDelay);
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "IsValid", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        return JSValueMakeBoolean(Context, Server->is_valid());
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "Stop", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        Server->stop();
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "IsRunning", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        return JSValueMakeBoolean(Context, Server->is_running());
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "Get", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        httplib::Server* Server = (httplib::Server*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Server");
        std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Server->Get(Path, [Context, ThisObject, Arguments, Callback](const httplib::Request& Request, httplib::Response& Response){
            JSObjectRef ResponseObject = JSObjectMake(Context, NULL, NULL);
            JSCWrapper::SetObjectInObject(Context, ResponseObject, "Response", &Response);

            JSCWrapper::CreateFunction(Context, ResponseObject, "SetHeader", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
                httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string HeaderValue = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
                Response.set_header(HeaderName.c_str(), HeaderValue.c_str());
                return JSValueMakeUndefined(Context);
            });
            
            JSCWrapper::CreateFunction(Context, ResponseObject, "SetRedirect", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
                httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                Response.set_redirect(Path.c_str());
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "Send", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string ResponseString = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string ContentType = JSCWrapper::GetKeyValueFromJSObjectAsString(Context, ThisObject, "ContentType");
                Response.set_content(ResponseString, ContentType.c_str());
                return JSValueMakeUndefined(Context);
            });

            JSObjectRef RequestObject = JSObjectMake(Context, NULL, NULL);
            httplib::Request* RequestCopy = new httplib::Request(Request);
            JSCWrapper::SetObjectInObject(Context, RequestObject, "Request", RequestCopy);
            
            JSObjectRef HeadersObject = JSObjectMake(Context, NULL, NULL);
            for(auto Header : Request.headers)
                JSCWrapper::SetStringProperty(Context, HeadersObject, Header.first.c_str(), Header.second.c_str());
            JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Headers"), HeadersObject, kJSPropertyAttributeNone, NULL);

            JSObjectRef ParamsObject = JSObjectMake(Context, NULL, NULL);
            for(auto Param : Request.params)
                JSCWrapper::SetStringProperty(Context, ParamsObject, Param.first.c_str(), Param.second.c_str());
            JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Params"), ParamsObject, kJSPropertyAttributeNone, NULL);

            JSCWrapper::SetStringProperty(Context, RequestObject, "Path", Request.path.c_str());
            JSCWrapper::SetStringProperty(Context, RequestObject, "Method", Request.method.c_str());
            JSCWrapper::SetStringProperty(Context, RequestObject, "Body", Request.body.c_str());
            JSCWrapper::SetStringProperty(Context, RequestObject, "Version", Request.version.c_str());
            JSCWrapper::SetStringProperty(Context, RequestObject, "Target", Request.target.c_str());
            JSCWrapper::SetIntegerProperty(Context, RequestObject, "RemotePort", Request.remote_port);
            JSCWrapper::SetStringProperty(Context, RequestObject, "RemoteAddress", Request.remote_addr.c_str());

            JSCWrapper::CreateFunction(Context, RequestObject, "GetHeaderValue", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string HeaderValue = Request.get_header_value(HeaderName.c_str());
                return JSCWrapper::CreateString(Context, HeaderValue.c_str());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetHeaderValueCount", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const int HeaderValueCount = Request.get_header_value_count(HeaderName.c_str());
                return JSValueMakeNumber(Context, HeaderValueCount);
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetParamValue", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string ParamName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string ParamValue = Request.get_param_value(ParamName.c_str());
                return JSCWrapper::CreateString(Context, ParamValue.c_str());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetParamValueCount", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string ParamName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const int ParamValueCount = Request.get_param_value_count(ParamName.c_str());
                return JSValueMakeNumber(Context, ParamValueCount);
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "HasParam", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string ParamName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const bool HasParam = Request.has_param(ParamName.c_str());
                return JSValueMakeBoolean(Context, HasParam);
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "HasHeader", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const bool HasHeader = Request.has_header(HeaderName.c_str());
                return JSValueMakeBoolean(Context, HasHeader);
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "HasFile", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string FileName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const bool HasFile = Request.has_file(FileName.c_str());
                return JSValueMakeBoolean(Context, HasFile);
            });

            JSValueRef CallbackArguments[2] = { RequestObject, ResponseObject };
            JSCWrapper::CallFunction(Context, Callback, ThisObject, 2, CallbackArguments);
        });
        
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "Listen", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
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
        return JSValueMakeUndefined(Context);
    });

    return ReturnValue;
};