#include <iostream>
#include <Poco/Net/IPAddress.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include <uWebSockets/src/App.h>
#include <memory.h>
#include "Network.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::Network::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef NetworkObject = JSCWrapper::CreateObject(Context, GlobalObject, "Network");
    JSCWrapper::CreateFunction(Context, NetworkObject, "IPv4", Network::IPv4);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IPv6", Network::IPv6);
    JSCWrapper::CreateFunction(Context, NetworkObject, "Broadcast", Network::Broadcast);
    JSCWrapper::CreateFunction(Context, NetworkObject, "Any", Network::Any);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsWildcard", Network::IsWildcard);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsBroadcast", Network::IsBroadcast);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsLoopback", Network::IsLoopback);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsMulticast", Network::IsMulticast);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsUnicast", Network::IsUnicast);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsLinkLocal", Network::IsLinkLocal);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsSiteLocal", Network::IsSiteLocal);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsIPv4Compatible", Network::IsIPv4Compatible);
    JSCWrapper::CreateFunction(Context, NetworkObject, "IsIPv4Mapped", Network::IsIPv4Mapped);
    JSCWrapper::CreateFunction(Context, NetworkObject, "WebSocketServer", Network::WebSocketServer);
};

JSC_FUNC(Classes::Network, IPv4){
    const std::string IPAddress = Poco::Net::IPAddress(Poco::Net::IPAddress::IPv4).toString();
    return JSCWrapper::CreateString(Context, IPAddress.data());
};

JSC_FUNC(Classes::Network, IPv6){
    const std::string IPAddress = Poco::Net::IPAddress(Poco::Net::IPAddress::IPv6).toString();
    return JSCWrapper::CreateString(Context, IPAddress.data());
};

JSC_FUNC(Classes::Network, Broadcast){
    const std::string IPAddress = Poco::Net::IPAddress::broadcast().toString();
    return JSCWrapper::CreateString(Context, IPAddress.data());
};

JSC_FUNC(Classes::Network, Any){
    const std::string IPAddress = Poco::Net::IPAddress::wildcard().toString();
    return JSCWrapper::CreateString(Context, IPAddress.data());
};

JSC_FUNC(Classes::Network, IsWildcard){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsWildcard = IPAddressInstance.isWildcard();
    return JSValueMakeBoolean(Context, IsWildcard);
};

JSC_FUNC(Classes::Network, IsBroadcast){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsBroadcast = IPAddressInstance.isBroadcast();
    return JSValueMakeBoolean(Context, IsBroadcast);
};

JSC_FUNC(Classes::Network, IsLoopback){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsLoopback = IPAddressInstance.isLoopback();
    return JSValueMakeBoolean(Context, IsLoopback);
};

JSC_FUNC(Classes::Network, IsMulticast){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsMulticast = IPAddressInstance.isMulticast();
    return JSValueMakeBoolean(Context, IsMulticast);
};

JSC_FUNC(Classes::Network, IsUnicast){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsUnicast = IPAddressInstance.isUnicast();
    return JSValueMakeBoolean(Context, IsUnicast);
};

JSC_FUNC(Classes::Network, IsLinkLocal){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsLinkLocal = IPAddressInstance.isLinkLocal();
    return JSValueMakeBoolean(Context, IsLinkLocal);
};

JSC_FUNC(Classes::Network, IsSiteLocal){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsSiteLocal = IPAddressInstance.isSiteLocal();
    return JSValueMakeBoolean(Context, IsSiteLocal);
};

JSC_FUNC(Classes::Network, IsIPv4Compatible){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsIPv4Compatible = IPAddressInstance.isIPv4Compatible();
    return JSValueMakeBoolean(Context, IsIPv4Compatible);
};

JSC_FUNC(Classes::Network, IsIPv4Mapped){
    const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const Poco::Net::IPAddress IPAddressInstance(IPAddress);
    const bool IsIPv4Mapped = IPAddressInstance.isIPv4Mapped();
    return JSValueMakeBoolean(Context, IsIPv4Mapped);
};

std::map<JSObjectRef, uWS::App*> ApplicationInstances;

JSC_FUNC(Classes::Network, WebSocketServer){
    uWS::App* Application = new uWS::App();

    JSObjectRef ReturnValue = JSObjectMake(Context, NULL, NULL);
    ApplicationInstances[ReturnValue] = Application;
    
    JSCWrapper::CreateFunction(Context, ReturnValue, "AddServerName", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
        auto Iterator = ApplicationInstances.find(ThisObject);
        if(Iterator == ApplicationInstances.end()){
            return JSValueMakeUndefined(Context);
        };
        const std::string ServerName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Iterator->second->addServerName(ServerName.data());
        return JSValueMakeUndefined(Context);
    });
    
    JSCWrapper::CreateFunction(Context, ReturnValue, "NumSubscribers", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
        auto Iterator = ApplicationInstances.find(ThisObject);
        if(Iterator == ApplicationInstances.end()){
            return JSValueMakeUndefined(Context);
        };
        std::string_view Topic = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const int NumSubscribers = Iterator->second->numSubscribers(Topic);
        return JSValueMakeNumber(Context, NumSubscribers);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "Listen", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
        auto Iterator = ApplicationInstances.find(ThisObject);
        if(Iterator == ApplicationInstances.end()){
            return JSValueMakeUndefined(Context);
        };
        const std::string IPAddress = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const int Port = JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
        JSObjectRef Callback = (JSObjectRef) Arguments[2];
        Iterator->second->listen(IPAddress.data(), Port, [&](auto *Socket){
            JSValueRef Arguments[0] = { };
            JSCWrapper::CallFunction(Context, Callback, ThisObject, 0, Arguments);
        }).run();
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ReturnValue, "Get", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        auto Iterator = ApplicationInstances.find(ThisObject);
        if(Iterator == ApplicationInstances.end()){
            return JSValueMakeUndefined(Context);
        }

        const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        JSObjectRef Callback = (JSObjectRef)Arguments[1];

        Iterator->second->get(Path.data(), [Context, Callback, ThisObject](auto *Response, auto *Request) {
            JSObjectRef ResponseObject = JSObjectMake(Context, NULL, NULL);
            JSObjectRef RequestObject = JSObjectMake(Context, NULL, NULL);

            JSCWrapper::SetObjectInObject(Context, ResponseObject, "Response", (void*)Response);
            JSCWrapper::SetObjectInObject(Context, RequestObject, "Request", (void*)Request);

            JSCWrapper::CreateFunction(Context, RequestObject, "IsAncient", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const bool IsAncient = Request->isAncient();
                return JSValueMakeBoolean(Context, IsAncient);
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetCaseSensitiveMethod", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Method = Request->getCaseSensitiveMethod();
                return JSCWrapper::CreateString(Context, Method.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetFullURL", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Url = Request->getFullUrl();
                return JSCWrapper::CreateString(Context, Url.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetHeader", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Header = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string_view Value = Request->getHeader(Header.data());
                return JSCWrapper::CreateString(Context, Value.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetMethod", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Method = Request->getMethod();
                return JSCWrapper::CreateString(Context, Method.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetParamter", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const int ParameterIndex = JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
                const std::string_view Parameter = Request->getParameter(ParameterIndex);
                return JSCWrapper::CreateString(Context, Parameter.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetQuery", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Query = Request->getQuery();
                return JSCWrapper::CreateString(Context, Query.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetURL", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const std::string_view Url = Request->getUrl();
                return JSCWrapper::CreateString(Context, Url.data());
            });

            JSCWrapper::CreateFunction(Context, RequestObject, "GetYield", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)  -> JSValueRef{
                auto Request = (uWS::HttpRequest*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
                const bool Yield = Request->getYield();
                return JSValueMakeBoolean(Context, Yield);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "OnAborted", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                JSObjectRef Callback = (JSObjectRef)Arguments[0];
                Response->onAborted([Context, Callback, ThisObject]() {
                    JSValueRef CallbackArguments[0] = { };
                    JSCWrapper::CallFunction(Context, Callback, ThisObject, 0, CallbackArguments);
                });
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "OnData", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*) JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                JSObjectRef Callback = (JSObjectRef)Arguments[0];
                Response->onData([Context, Callback, ThisObject](std::string_view Data, bool IsLast) {
                    JSValueRef CallbackArguments[2] = { JSCWrapper::CreateString(Context, Data.data()), JSValueMakeBoolean(Context, IsLast) };
                    JSCWrapper::CallFunction(Context, Callback, ThisObject, 2, CallbackArguments);
                });
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "End", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string ResponseString = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                Response->end(ResponseString.data());
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "EndWithoutBody", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                Response->endWithoutBody();
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "WriteStatus", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string_view Status = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                Response->writeStatus(Status.data());
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "WriteContinue", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                Response->writeContinue();
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "Pause", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                Response->pause();
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "Resume", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                Response->resume();
                return JSValueMakeUndefined(Context);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "Close", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const bool Close = Response->close();
                return JSValueMakeBoolean(Context, Close);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "TryEnd", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string Data = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::pair<bool, bool> TryEnd = Response->tryEnd(Data);
                return JSValueMakeBoolean(Context, TryEnd.first && TryEnd.second);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "WriteHeader", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string_view Key = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const std::string_view Value = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
                Response->writeHeader(Key.data(), Value.data());
                return JSValueMakeUndefined(Context);
            });
            
            JSCWrapper::CreateFunction(Context, ResponseObject, "Write", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string_view Data = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
                const bool Write = Response->write(Data.data());
                return JSValueMakeBoolean(Context, Write);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "GetRemoteAddress", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception)->JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const std::string_view RemoteAddress = Response->getRemoteAddressAsText();
                return JSCWrapper::CreateString(Context, RemoteAddress.data());
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "GetWriteOffset", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const size_t WriteOffset = Response->getWriteOffset();
                return JSValueMakeNumber(Context, WriteOffset);
            });

            JSCWrapper::CreateFunction(Context, ResponseObject, "HasResponded", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
                auto Response = (uWS::HttpResponse<false>*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
                const bool HasResponded = Response->hasResponded();
                return JSValueMakeBoolean(Context, HasResponded);
            });

            JSValueRef CallbackArguments[2] = { RequestObject, ResponseObject };
            JSCWrapper::CallFunction(Context, Callback, ThisObject, 2, CallbackArguments);
        });

        return JSValueMakeUndefined(Context);
    });
    
    return ReturnValue;
};