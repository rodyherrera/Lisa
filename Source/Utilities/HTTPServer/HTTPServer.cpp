#include <iostream>
#include "CPP-HTTP-LIB.hpp"
#include "HTTPServer.hpp"
#include "../Runtime/Runtime.hpp"
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

    JSObjectRef PathParamsObject = JSObjectMake(Context, NULL, NULL);
    for(auto PathParam : Request->path_params)
        JSCWrapper::SetStringProperty(Context, PathParamsObject, PathParam.first.c_str(), PathParam.second.c_str());
    JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("PathParams"), PathParamsObject, kJSPropertyAttributeNone, NULL);

    JSObjectRef QueryParamsObject = JSObjectMake(Context, NULL, NULL);
    for(auto QueryParam : Request->params)
        JSCWrapper::SetStringProperty(Context, QueryParamsObject, QueryParam.first.c_str(), QueryParam.second.c_str());
    JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Query"), QueryParamsObject, kJSPropertyAttributeNone, NULL);

    JSCWrapper::CreateFunction(Context, RequestObject, "GetFileValue", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
        const std::string FileName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        httplib::MultipartFormData FormData = Request.get_file_value(FileName);
        JSObjectRef FileObject = JSObjectMake(Context, NULL, NULL);
        JSCWrapper::SetStringProperty(Context, FileObject, "Name", FormData.filename.c_str());
        JSCWrapper::SetStringProperty(Context, FileObject, "ContentType", FormData.content_type.c_str());
        JSCWrapper::SetStringProperty(Context, FileObject, "Data", FormData.content.c_str());
        return FileObject;
    });

    JSCWrapper::CreateFunction(Context, RequestObject, "IsMultipartFormData", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
        return JSValueMakeBoolean(Context, Request.is_multipart_form_data());
    });

    JSCWrapper::CreateFunction(Context, RequestObject, "GetFileValues", [](JSContextRef Context, JSObjectRef Function, JSObjectRef ThisObject, size_t ArgumentsLength, const JSValueRef Arguments[], JSValueRef* Exception) -> JSValueRef {
        httplib::Request& Request = *(httplib::Request*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Request");
        const std::string FileName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        std::vector<httplib::MultipartFormData> FormDatas = Request.get_file_values(FileName);
        JSObjectRef FileValuesObject = JSObjectMake(Context, NULL, NULL);
        for(size_t FileIterator = 0; FileIterator < FormDatas.size(); FileIterator++){
            JSObjectRef FileObject = JSObjectMake(Context, NULL, NULL);
            JSCWrapper::SetStringProperty(Context, FileObject, "Name", FormDatas[FileIterator].filename.c_str());
            JSCWrapper::SetStringProperty(Context, FileObject, "ContentType", FormDatas[FileIterator].content_type.c_str());
            JSCWrapper::SetStringProperty(Context, FileObject, "Data", FormDatas[FileIterator].content.c_str());
            JSCWrapper::SetObjectInObject(Context, FileValuesObject, std::to_string(FileIterator).c_str(), FileObject);
        }
        return FileValuesObject;
    });

    JSObjectRef FilesObject = JSObjectMake(Context, NULL, NULL);
    for(auto File : Request->files){
        JSObjectRef FileObject = JSObjectMake(Context, NULL, NULL);
        JSCWrapper::SetStringProperty(Context, FileObject, "Name", File.first.c_str());
        JSCWrapper::SetStringProperty(Context, FileObject, "ContentType", File.second.content_type.c_str());
        JSCWrapper::SetStringProperty(Context, FileObject, "Data", File.second.content.c_str());
        JSCWrapper::SetObjectInObject(Context, FilesObject, File.first.c_str(), FileObject);
    }
    JSObjectSetProperty(Context, RequestObject, JSStringCreateWithUTF8CString("Files"), FilesObject, kJSPropertyAttributeNone, NULL);

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

    JW_CREATE_FUNC(GetHeaderValue, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string HeaderValue = Response.get_header_value(HeaderName.c_str());
        return JSCWrapper::CreateString(Context, HeaderValue.c_str());
    });
    
    JW_CREATE_FUNC(GetHeaderValueCount, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const int HeaderValueCount = Response.get_header_value_count(HeaderName.c_str());
        return JSValueMakeNumber(Context, HeaderValueCount);
    });

    JW_CREATE_FUNC(HasHeader, ResponseObject){
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

    JW_CREATE_FUNC(SetHeader, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string HeaderName = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string HeaderValue = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
        Response.set_header(HeaderName.c_str(), HeaderValue.c_str());
        return JSC_MAKE_UNDEFINED;
    });
    
    JW_CREATE_FUNC(SetRedirect, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        Response.set_redirect(Path.c_str());
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(SetStatus, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const int Status = JSValueToNumber(Context, Arguments[0], NULL);
        Response.status = Status;
        return JSC_MAKE_UNDEFINED;
    });

    JW_CREATE_FUNC(Send, ResponseObject){
        httplib::Response& Response = *(httplib::Response*)JSCWrapper::GetObjectFromObject(Context, ThisObject, "Response");
        const std::string ResponseString = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
        const std::string ContentType = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
        const int Status = JSValueToNumber(Context, Arguments[2], NULL);
        Response.status = Status;
        Response.set_content(ResponseString, ContentType.c_str());
        return JSC_MAKE_UNDEFINED;
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