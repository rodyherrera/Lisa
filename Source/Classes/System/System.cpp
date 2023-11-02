#include <iostream>
#include <uv.h>
#include "System.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::System::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef SystemObject = JSCWrapper::CreateObject(Context, GlobalObject, "System");
    JSCWrapper::CreateFunction(Context, SystemObject, "HRTime", System::HRTime);
    JSCWrapper::CreateFunction(Context, SystemObject, "Uptime", System::Uptime);
    JSCWrapper::CreateFunction(Context, SystemObject, "Uname", System::Uname);
    JSCWrapper::CreateFunction(Context, SystemObject, "Environ", System::Environ);
    JSCWrapper::CreateFunction(Context, SystemObject, "GetEnviron", System::GetEnviron);
    JSCWrapper::CreateFunction(Context, SystemObject, "SetEnviron", System::SetEnviron);
    JSCWrapper::CreateFunction(Context, SystemObject, "UnsetEnviron", System::UnsetEnviron);
    JSCWrapper::CreateFunction(Context, SystemObject, "ChangeWorkingDirectory", System::ChangeWorkingDirectory);
    JSCWrapper::CreateFunction(Context, SystemObject, "CurrentWorkingDirectory", System::CurrentWorkingDirectory);
    JSCWrapper::CreateFunction(Context, SystemObject, "HomeDirectory", System::HomeDirectory);
    JSCWrapper::CreateFunction(Context, SystemObject, "TempDirectory", System::TempDirectory);
    JSCWrapper::CreateFunction(Context, SystemObject, "CPUInfo", System::CPUInfo);
    JSCWrapper::CreateFunction(Context, SystemObject, "NetworkInterfaces", System::NetworkInterfaces);
    JSCWrapper::CreateFunction(Context, SystemObject, "GetHostname", System::GetHostname);
    JSCWrapper::CreateFunction(Context, SystemObject, "Sleep", System::Sleep);
    JSCWrapper::CreateFunction(Context, SystemObject, "GetPID", System::GetPID);
    JSCWrapper::CreateFunction(Context, SystemObject, "GetPPID", System::GetPPID);
};

JSValueRef Classes::System::HRTime(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    uint64_t Time = uv_hrtime();
    return JSValueMakeNumber(Context, Time);
};

JSValueRef Classes::System::Uptime(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    double Uptime;
    uv_uptime(&Uptime);
    return JSValueMakeNumber(Context, Uptime);
};

JSValueRef Classes::System::Uname(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    uv_utsname_t Uname;
    uv_os_uname(&Uname);
    JSObjectRef UnameObject = JSCWrapper::CreateObject(Context, JSObjectMake(Context, nullptr, nullptr), "Uname");
    JSCWrapper::SetStringProperty(Context, UnameObject, "Sysname", Uname.sysname);
    JSCWrapper::SetStringProperty(Context, UnameObject, "Release", Uname.release);
    JSCWrapper::SetStringProperty(Context, UnameObject, "Version", Uname.version);
    JSCWrapper::SetStringProperty(Context, UnameObject, "Machine", Uname.machine);
    return UnameObject;
};

JSValueRef Classes::System::Environ(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    uv_env_item_t *Environ;
    int EnvironmentVariableCount;
    int Result = uv_os_environ(&Environ, &EnvironmentVariableCount);
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    JSObjectRef EnvironObject = JSCWrapper::CreateObject(Context, JSObjectMake(Context, nullptr, nullptr), "Environ");
    for(int EnvironmentVariableIterator = 0; EnvironmentVariableIterator < EnvironmentVariableCount; EnvironmentVariableIterator++){
        JSCWrapper::SetStringProperty(Context, EnvironObject, Environ[EnvironmentVariableIterator].name, Environ[EnvironmentVariableIterator].value);
    }
    return EnvironObject;
};

JSValueRef Classes::System::GetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    if(ArgumentsLength < 1){
        return JSValueMakeUndefined(Context);
    }
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    char* Value = getenv(Name.c_str());
    if(Value == nullptr){
        return JSValueMakeUndefined(Context);
    }
    return JSValueMakeString(Context, JSStringCreateWithUTF8CString(Value));
};

JSValueRef Classes::System::SetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    if(ArgumentsLength < 2){
        return JSValueMakeUndefined(Context);
    }
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string Value = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    int Result = setenv(Name.c_str(), Value.c_str(), 1);
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    return JSValueMakeBoolean(Context, true);
};

JSValueRef Classes::System::UnsetEnviron(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    if(ArgumentsLength < 1){
        return JSValueMakeUndefined(Context);
    }
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    int Result = unsetenv(Name.c_str());
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    return JSValueMakeBoolean(Context, true);
};

JSValueRef Classes::System::ChangeWorkingDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    if(ArgumentsLength < 1){
        return JSValueMakeUndefined(Context);
    }
    const std::string Directory = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    int Result = chdir(Directory.c_str());
    return JSValueMakeBoolean(Context, Result == 0);
};

JSValueRef Classes::System::CurrentWorkingDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    char* CurrentWorkingDirectory = getcwd(nullptr, 0);
    JSStringRef CurrentWorkingDirectoryString = JSStringCreateWithUTF8CString(CurrentWorkingDirectory);
    JSValueRef CurrentWorkingDirectoryJSString = JSValueMakeString(Context, CurrentWorkingDirectoryString);
    free(CurrentWorkingDirectory);
    return CurrentWorkingDirectoryJSString;
};

JSValueRef Classes::System::HomeDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    char* HomeDirectory = getenv("HOME");
    JSStringRef HomeDirectoryString = JSStringCreateWithUTF8CString(HomeDirectory);
    JSValueRef HomeDirectoryJSString = JSValueMakeString(Context, HomeDirectoryString);
    return HomeDirectoryJSString;
};

JSValueRef Classes::System::TempDirectory(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    char* TempDirectory = getenv("TMPDIR");
    JSStringRef TempDirectoryString = JSStringCreateWithUTF8CString(TempDirectory);
    JSValueRef TempDirectoryJSString = JSValueMakeString(Context, TempDirectoryString);
    return TempDirectoryJSString;
};

JSValueRef Classes::System::CPUInfo(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    uv_cpu_info_t *CPUInformation;
    int CPUInformationCount;
    int Result = uv_cpu_info(&CPUInformation, &CPUInformationCount);
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    JSObjectRef CPUInformationArray = JSObjectMakeArray(Context, 0, nullptr, nullptr);
    for(int Iterator = 0; Iterator < CPUInformationCount; Iterator++){
        uv_cpu_info_t Information = CPUInformation[Iterator];
        JSObjectRef CPUInformationObject = JSCWrapper::CreateObject(Context, CPUInformationArray, "CPUInformation");
        JSCWrapper::SetStringProperty(Context, CPUInformationObject, "Model", Information.model);
        JSCWrapper::SetIntegerProperty(Context, CPUInformationObject, "Speed", Information.speed);
        JSObjectRef TimesObject = JSCWrapper::CreateObject(Context, CPUInformationObject, "Times");
        JSCWrapper::SetIntegerProperty(Context, TimesObject, "User", Information.cpu_times.user);
        JSCWrapper::SetIntegerProperty(Context, TimesObject, "Nice", Information.cpu_times.nice);
        JSCWrapper::SetIntegerProperty(Context, TimesObject, "Sys", Information.cpu_times.sys);
        JSCWrapper::SetIntegerProperty(Context, TimesObject, "Idle", Information.cpu_times.idle);
        JSCWrapper::SetIntegerProperty(Context, TimesObject, "Irq", Information.cpu_times.irq);
        JSObjectSetPropertyAtIndex(Context, CPUInformationArray, Iterator, CPUInformationObject, nullptr);

    }
    return CPUInformationArray;
};

JSValueRef Classes::System::NetworkInterfaces(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
    uv_interface_address_t* Interfaces;
    int InterfaceCount;
    int Result = uv_interface_addresses(&Interfaces, &InterfaceCount);
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    JSObjectRef InterfaceArray = JSObjectMakeArray(Context, 0, nullptr, nullptr);
    for(int Iterator = 0; Iterator < InterfaceCount; Iterator++){
        uv_interface_address_t Interface = Interfaces[Iterator];
        JSObjectRef InterfaceObject = JSCWrapper::CreateObject(Context, InterfaceArray, "Interface");
        JSCWrapper::SetStringProperty(Context, InterfaceObject, "Name", Interface.name);
        JSCWrapper::SetStringProperty(Context, InterfaceObject, "Internal", Interface.is_internal ? "true" : "false");
        JSCWrapper::SetStringProperty(Context, InterfaceObject, "Mac", Interface.phys_addr);
        char Buffer[INET6_ADDRSTRLEN + 1];
        char Mac[18];
        uv_ip4_name(&Interface.address.address4, Buffer, INET6_ADDRSTRLEN);
        JSCWrapper::SetStringProperty(Context, InterfaceObject, "Address", Buffer);
        snprintf(Mac, sizeof(Mac), "%02x:%02x:%02x:%02x:%02x:%02x", 
            (unsigned char) Interface.phys_addr[0],
            (unsigned char) Interface.phys_addr[1],
            (unsigned char) Interface.phys_addr[2],
            (unsigned char) Interface.phys_addr[3],
            (unsigned char) Interface.phys_addr[4],
            (unsigned char) Interface.phys_addr[5]);
        JSCWrapper::SetStringProperty(Context, InterfaceObject, "Mac", Mac);
        JSObjectSetPropertyAtIndex(Context, InterfaceArray, Iterator, InterfaceObject, nullptr);
    }
    return InterfaceArray;
};

JSValueRef Classes::System::GetHostname(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    char Hostname[256];
    int Result = gethostname(Hostname, sizeof(Hostname));
    if(Result != 0){
        return JSValueMakeUndefined(Context);
    }
    JSStringRef HostnameString = JSStringCreateWithUTF8CString(Hostname);
    JSValueRef HostnameJSString = JSValueMakeString(Context, HostnameString);
    return HostnameJSString;
};

JSValueRef Classes::System::GetPID(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    return JSValueMakeNumber(Context, getpid());
};

JSValueRef Classes::System::GetPPID(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    return JSValueMakeNumber(Context, getppid());
};

JSValueRef Classes::System::Sleep(JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) {
    if(ArgumentsLength < 1){
        return JSValueMakeUndefined(Context);
    }
    const int Milliseconds = JSCWrapper::GetKeyValueFromJSObjectAsInteger(Context, ThisObject, "Milliseconds");
    uv_sleep(Milliseconds);
    return JSValueMakeUndefined(Context);
};