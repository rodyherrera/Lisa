#include <iostream>
#include "CPP-HTTP-LIB.hpp"
#include "HTTPServer.hpp"
#include "../JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

 void HTTPServer::SetDefaultHeaders(httplib::Server& Server){
    Server.set_default_headers({ {"Server", "LisaJS"} });
};

JSObjectRef HTTPServer::CreateRequestObject(JSContextRef Context, httplib::Request* Request){
    JSObjectRef RequestObject = JSObjectMake(Context, NULL, NULL);
    JSCWrapper::SetObjectInObject(Context, RequestObject, "Request", Request);
    
    JSObjectRef HeadersObject = JSObjectMake(Context, NULL, NULL);
    for(auto Header : Request->headers)
        JSCWrapper::SetStringProperty(Context, HeadersObject, Header.first.c_str(), Header.second.c_str());
    JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Headers"), HeadersObject, kJSPropertyAttributeNone, NULL);

    JSObjectRef ParamsObject = JSObjectMake(Context, NULL, NULL);
    for(auto Param : Request->params)
        JSCWrapper::SetStringProperty(Context, ParamsObject, Param.first.c_str(), Param.second.c_str());
    JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Params"), ParamsObject, kJSPropertyAttributeNone, NULL);

    JSCWrapper::SetStringProperty(Context, RequestObject, "Path", Request->path.c_str());
    JSCWrapper::SetStringProperty(Context, RequestObject, "Method", Request->method.c_str());
    JSCWrapper::SetStringProperty(Context, RequestObject, "Body", Request->body.c_str());
    JSCWrapper::SetStringProperty(Context, RequestObject, "Version", Request->version.c_str());
    JSCWrapper::SetStringProperty(Context, RequestObject, "Target", Request->target.c_str());
    JSCWrapper::SetIntegerProperty(Context, RequestObject, "RemotePort", Request->remote_port);
    JSCWrapper::SetStringProperty(Context, RequestObject, "RemoteAddress", Request->remote_addr.c_str());

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

    return RequestObject;
};

JSObjectRef HTTPServer::CreateResponseObject(JSContextRef Context, httplib::Response *Response){
    JSObjectRef ResponseObject = JSObjectMake(Context, NULL, NULL);
    JSCWrapper::SetObjectInObject(Context, ResponseObject, "Response", Response);

    JSCWrapper::CreateFunction(Context, ResponseObject, "GetHeaderValue", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string HeaderValue = Response.get_header_value(HeaderName.c_str());
        return JSCWrapper::CreateString(Context, HeaderValue.c_str());
    });
    
    JSCWrapper::CreateFunction(Context, ResponseObject, "GetHeaderValueCount", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const int HeaderValueCount = Response.get_header_value_count(HeaderName.c_str());
        return JSValueMakeNumber(Context, HeaderValueCount);
    });

    JSCWrapper::CreateFunction(Context, ResponseObject, "HasHeader", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const bool HasHeader = Response.has_header(HeaderName.c_str());
        return JSValueMakeBoolean(Context, HasHeader);
    });
    
    JSObjectRef ResponseHeadersObject = JSObjectMake(Context, NULL, NULL);
    for(auto Header : Response->headers)
        JSCWrapper::SetStringProperty(Context, ResponseHeadersObject, Header.first.c_str(), Header.second.c_str());
    JSObjectSetProperty(Context, ResponseObject, JSStringCreateWithUTF8CString("Headers"), ResponseHeadersObject, kJSPropertyAttributeNone, NULL);
    
    JSCWrapper::SetStringProperty(Context, ResponseObject, "Body", Response->body.c_str());
    JSCWrapper::SetStringProperty(Context, ResponseObject, "Location", Response->location.c_str());
    JSCWrapper::SetStringProperty(Context, ResponseObject, "Version", Response->version.c_str());
    JSCWrapper::SetIntegerProperty(Context, ResponseObject, "Status", Response->status);
    JSCWrapper::SetStringProperty(Context, ResponseObject, "Reason", Response->reason.c_str());

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

    JSCWrapper::CreateFunction(Context, ResponseObject, "SetStatus", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const int Status = JSValueToNumber(Context, Arguments[0], NULL);
        Response.status = Status;
        return JSValueMakeUndefined(Context);
    });

    JSCWrapper::CreateFunction(Context, ResponseObject, "Send", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string ResponseString = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string ContentType = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
        const int Status = JSValueToNumber(Context, Arguments[2], NULL);
        Response.status = Status;
        Response.set_content(ResponseString, ContentType.c_str());
        return JSValueMakeUndefined(Context);
    });

    return ResponseObject;
};

void HTTPServer::HandleHTTPRequest(JSContextRef Context, JSObjectRef ThisObject, httplib::Request& Request, httplib::Response& Response, JSObjectRef Callback){
    httplib::Request* RequestCopy = new httplib::Request(Request);

    JSObjectRef ResponseObject = CreateResponseObject(Context, &Response);
    JSObjectRef RequestObject = CreateRequestObject(Context, RequestCopy);

    JSValueRef CallbackArguments[2] = { RequestObject, ResponseObject };
    JSCWrapper::CallFunction(Context, Callback, ThisObject, 2, CallbackArguments);
};