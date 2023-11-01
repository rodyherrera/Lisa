#include <iostream>
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Utilities::Runtime{
    const std::string ReadFile(const std::string Path);
    void ClearUVTimer(JSContextRef Context, JSValueRef TimerValue);
};