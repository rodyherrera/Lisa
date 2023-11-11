#include <iostream>
#include <Poco/Net/IPAddress.h>
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