#ifndef LISA_CLASSES_CHTTPL_HPP
#define LISA_CLASSES_CHTTPL_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class CHTTPL{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            static LISA_JS_FUNC_DEF(CreateServer);
    };
};

#endif