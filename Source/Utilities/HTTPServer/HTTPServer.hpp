#include <iostream>
#include "CPP-HTTP-LIB.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Utilities::HTTPServer{
    void HandleHTTPRequest(JSContextRef Context, JSObjectRef ThisObject, httplib::Request& Request, httplib::Response& Response, JSObjectRef Callback);
    JSObjectRef CreateResponseObject(JSContextRef Context, httplib::Response *Response);
    JSObjectRef CreateRequestObject(JSContextRef Context, httplib::Request* Request);
    void SetDefaultHeaders(httplib::Server& Server);
};