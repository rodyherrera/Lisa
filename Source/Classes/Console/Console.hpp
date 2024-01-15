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

#ifndef LISA_CLASSES_CONSOLE_HPP
#define LISA_CLASSES_CONSOLE_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class Console{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(Log);
    };
};

#endif