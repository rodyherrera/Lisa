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
#include <JavaScriptCore/JavaScript.h>
#include "ClearTimer.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

JSC_FUNC(Methods, ClearTimer){
    Runtime::ClearUVTimer(Context, Arguments[0]);
    return JSC_MAKE_UNDEFINED;
}