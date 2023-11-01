#include <iostream>
#include "ServerWrapper.hpp"
#include "CPP-HTTP-LIB.hpp"

Lisa::Utilities::ServerWrapper::ServerWrapper(){
    ServerInstance = nullptr;
};

void Lisa::Utilities::ServerWrapper::StartServer(const std::string Hostname, int Port){
    ServerInstance->set_default_headers({
        {"Server", "LisaJS-1.0.0"},
    });
    ServerInstance->listen(Hostname.c_str(), Port);
};

httplib::Server* Lisa::Utilities::ServerWrapper::GetServer(){
    return ServerInstance;
};

void Lisa::Utilities::ServerWrapper::SetServer(httplib::Server* ServerInstance){
    this->ServerInstance = ServerInstance;
};