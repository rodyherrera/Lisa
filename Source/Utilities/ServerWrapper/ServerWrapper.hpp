#ifndef LISA_UTILITIES_SERVERWRAPPER_HPP
#define LISA_UTILITIES_SERVERWRAPPER_HPP
#include "CPP-HTTP-LIB.hpp"

namespace Lisa::Utilities{
    class ServerWrapper{
        public:
            ServerWrapper();
            void SetServer(httplib::Server* ServerInstance);
            void StartServer(const std::string Hostname, int Port);
            httplib::Server* GetServer();

        private:
            httplib::Server* ServerInstance;
    };
};

#endif