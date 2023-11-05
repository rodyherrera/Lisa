#ifndef LISA_CLASSES_FILESYSTEM_HPP
#define LISA_CLASSES_FILESYSTEM_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class FileSystem{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(AbsolutePath);
            JSC_FUNC_DEF(CanonicalPath);
            JSC_FUNC_DEF(RelativePath);
            JSC_FUNC_DEF(Copy);
            JSC_FUNC_DEF(CopyFileContent);
            JSC_FUNC_DEF(CopySymlink);
            JSC_FUNC_DEF(CreateDirectory);
            JSC_FUNC_DEF(CreateDirectories);
            JSC_FUNC_DEF(CreateHardLink);
            JSC_FUNC_DEF(CreateSymlink);
            JSC_FUNC_DEF(CreateDirectorySymlink);
            JSC_FUNC_DEF(WriteFile);
            JSC_FUNC_DEF(ReadLines);
            JSC_FUNC_DEF(CurrentPath);
            JSC_FUNC_DEF(Exists);
            JSC_FUNC_DEF(Equivalent);
            JSC_FUNC_DEF(FileSize);
            JSC_FUNC_DEF(HardLinkCount);
            JSC_FUNC_DEF(LastModification);
            JSC_FUNC_DEF(ReadSymlink);
            JSC_FUNC_DEF(SetPermissions);
            JSC_FUNC_DEF(Remove);
            JSC_FUNC_DEF(RemoveRecursively);
            JSC_FUNC_DEF(Rename);
            JSC_FUNC_DEF(ResizeFile);
            JSC_FUNC_DEF(GetLastWriteTime);
            JSC_FUNC_DEF(SetLastWriteTime);
            JSC_FUNC_DEF(Space);
            JSC_FUNC_DEF(TempDirectoryPath);
            JSC_FUNC_DEF(IsBlockFile);
            JSC_FUNC_DEF(IsCharacterFile);
            JSC_FUNC_DEF(IsDirectory);
            JSC_FUNC_DEF(IsEmpty);
            JSC_FUNC_DEF(IsFifo);
            JSC_FUNC_DEF(IsOther);
            JSC_FUNC_DEF(IsRegularFile);
            JSC_FUNC_DEF(IsSocket);
            JSC_FUNC_DEF(IsSymlink);
            JSC_FUNC_DEF(ReadFile);
    };
};

#endif