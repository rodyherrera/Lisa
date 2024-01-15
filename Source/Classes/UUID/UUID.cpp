/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodyherrera/Lisa/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "UUID.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::UUID::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef UUIDObject = JSCWrapper::CreateObject(Context, GlobalObject, "UUID");
    JSCWrapper::CreateFunction(Context, UUIDObject, "v1", UUID::v1);
    JSCWrapper::CreateFunction(Context, UUIDObject, "v4", UUID::v4);
    JSCWrapper::CreateFunction(Context, UUIDObject, "v5", UUID::v5);
}

JSC_FUNC(Classes::UUID, v1){
    boost::uuids::basic_random_generator<boost::mt19937> Generator;
    boost::uuids::uuid UUID = Generator();
    std::string UUIDString = boost::uuids::to_string(UUID);
    return JSCWrapper::CreateString(Context, UUIDString.data());
}

JSC_FUNC(Classes::UUID, v4){
    boost::uuids::random_generator Generator;
    boost::uuids::uuid UUID = Generator();
    std::string UUIDString = boost::uuids::to_string(UUID);
    return JSCWrapper::CreateString(Context, UUIDString.data());
}

JSC_FUNC(Classes::UUID, v5){
    const std::string Namespace = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);

    boost::uuids::name_generator Generator(boost::uuids::string_generator()(Namespace));
    boost::uuids::uuid UUID = Generator(Name);
    std::string UUIDString = boost::uuids::to_string(UUID);

    return JSCWrapper::CreateString(Context, UUIDString.data());
}