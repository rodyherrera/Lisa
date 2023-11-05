#include <iostream>
#include <filesystem>
#include <fstream>
#include "FileSystem.hpp"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

void Classes::FileSystem::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef FileSystemObject = JSCWrapper::CreateObject(Context, GlobalObject, "FileSystem");
    JSCWrapper::CreateFunction(Context, FileSystemObject, "AbsolutePath", FileSystem::AbsolutePath);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CanonicalPath", FileSystem::CanonicalPath);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "ReadLines", FileSystem::ReadLines);  
    JSCWrapper::CreateFunction(Context, FileSystemObject, "RelativePath", FileSystem::RelativePath);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Copy", FileSystem::Copy);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CopyFileContent", FileSystem::CopyFileContent);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CopySymlink", FileSystem::CopySymlink);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CreateDirectory", FileSystem::CreateDirectory);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CreateDirectories", FileSystem::CreateDirectories);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CreateHardLink", FileSystem::CreateHardLink);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CreateSymlink", FileSystem::CreateSymlink);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CreateDirectorySymlink", FileSystem::CreateDirectorySymlink);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "WriteFile", FileSystem::WriteFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "CurrentPath", FileSystem::CurrentPath);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Exists", FileSystem::Exists);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Equivalent", FileSystem::Equivalent);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "ReadFile", FileSystem::ReadFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "FileSize", FileSystem::FileSize);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "HardLinkCount", FileSystem::HardLinkCount);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "GetLastWriteTime", FileSystem::GetLastWriteTime);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "SetLastWriteTime", FileSystem::SetLastWriteTime);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "SetPermissions", FileSystem::SetPermissions);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "ReadSymlink", FileSystem::ReadSymlink);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Remove", FileSystem::Remove);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "RemoveRecursively", FileSystem::RemoveRecursively);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Rename", FileSystem::Rename);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "ResizeFile", FileSystem::ResizeFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "Space", FileSystem::Space);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "TempDirectoryPath", FileSystem::TempDirectoryPath);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsBlockFile", FileSystem::IsBlockFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsCharacterFile", FileSystem::IsCharacterFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsDirectory", FileSystem::IsDirectory);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsEmpty", FileSystem::IsEmpty);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsFifo", FileSystem::IsFifo);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsOther", FileSystem::IsOther);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsRegularFile", FileSystem::IsRegularFile);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsSocket", FileSystem::IsSocket);
    JSCWrapper::CreateFunction(Context, FileSystemObject, "IsSymlink", FileSystem::IsSymlink);
};

JSC_FUNC(Classes::FileSystem, AbsolutePath){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string AbsolutePath = std::filesystem::absolute(Path).string();
    return JSCWrapper::CreateString(Context, AbsolutePath.c_str());
};

JSC_FUNC(Classes::FileSystem, CanonicalPath){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string CanonicalPath = std::filesystem::canonical(Path).string();
    return JSCWrapper::CreateString(Context, CanonicalPath.c_str());
}

JSC_FUNC(Classes::FileSystem, RelativePath){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string RelativePath = std::filesystem::relative(Path).string();
    return JSCWrapper::CreateString(Context, RelativePath.c_str());
}

JSC_FUNC(Classes::FileSystem, Copy){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::copy(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CopyFileContent){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::copy_file(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CopySymlink){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::copy_symlink(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CreateDirectory){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::create_directory(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, CreateDirectories){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::create_directories(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, CreateHardLink){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::create_hard_link(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CreateSymlink){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::create_symlink(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CreateDirectorySymlink){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::create_directory_symlink(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, CurrentPath){
    const std::string CurrentPath = std::filesystem::current_path().string();
    return JSCWrapper::CreateString(Context, CurrentPath.c_str());
}

JSC_FUNC(Classes::FileSystem, Exists){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::exists(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, Equivalent){
    const std::string Path1 = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string Path2 = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    const bool Status = std::filesystem::equivalent(Path1, Path2);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, FileSize){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const uintmax_t FileSize = std::filesystem::file_size(Path);
    return JSValueMakeNumber(Context, FileSize);
}

JSC_FUNC(Classes::FileSystem, HardLinkCount){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const uintmax_t HardLinkCount = std::filesystem::hard_link_count(Path);
    return JSValueMakeNumber(Context, HardLinkCount);
}

JSC_FUNC(Classes::FileSystem, GetLastWriteTime){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::filesystem::file_time_type LastModification = std::filesystem::last_write_time(Path);
    return JSValueMakeNumber(Context, LastModification.time_since_epoch().count());
}

JSC_FUNC(Classes::FileSystem, SetLastWriteTime){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::filesystem::file_time_type LastModification = std::filesystem::file_time_type(std::chrono::nanoseconds(static_cast<int64_t>(JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]))));
    std::filesystem::last_write_time(Path, LastModification);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, SetPermissions){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::filesystem::perms Permissions = static_cast<std::filesystem::perms>(JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]));
    std::filesystem::permissions(Path, Permissions);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, ReadSymlink){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string Symlink = std::filesystem::read_symlink(Path).string();
    return JSCWrapper::CreateString(Context, Symlink.c_str());
}

JSC_FUNC(Classes::FileSystem, Remove){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::remove(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, RemoveRecursively){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::remove_all(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, Rename){
    const std::string SourcePath = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string DestinationPath = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::filesystem::rename(SourcePath, DestinationPath);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, ResizeFile){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const uintmax_t FileSize = static_cast<uintmax_t>(JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]));
    std::filesystem::resize_file(Path, FileSize);
    return JSC_MAKE_UNDEFINED;
}

JSC_FUNC(Classes::FileSystem, Space){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::filesystem::space_info Space = std::filesystem::space(Path);
    JSObjectRef SpaceObject = JSObjectMake(Context, NULL, NULL);
    JSCWrapper::SetIntegerProperty(Context, SpaceObject, "Capacity", Space.capacity);
    JSCWrapper::SetIntegerProperty(Context, SpaceObject, "Free", Space.free);
    JSCWrapper::SetIntegerProperty(Context, SpaceObject, "Available", Space.available);
    return SpaceObject;
}

JSC_FUNC(Classes::FileSystem, TempDirectoryPath){
    const std::string TempDirectoryPath = std::filesystem::temp_directory_path().string();
    return JSCWrapper::CreateString(Context, TempDirectoryPath.c_str());
}

JSC_FUNC(Classes::FileSystem, IsBlockFile){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_block_file(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsCharacterFile){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_character_file(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsDirectory){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_directory(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsEmpty){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_empty(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsFifo){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_fifo(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsOther){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_other(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsRegularFile){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_regular_file(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsSocket){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_socket(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, IsSymlink){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const bool Status = std::filesystem::is_symlink(Path);
    return JSValueMakeBoolean(Context, Status);
}

JSC_FUNC(Classes::FileSystem, ReadFile){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    std::ifstream File(Path, std::ios::ate);
    if(!File.is_open()){
        return JSValueMakeBoolean(Context, false);
    }
    const std::streamsize FileSize = File.tellg();
    File.seekg(0, std::ios::beg);
    std::string Content;
    Content.resize(FileSize);
    File.read(&Content[0], FileSize);
    File.close();
    return JSCWrapper::CreateString(Context, Content.data());
};

JSC_FUNC(Classes::FileSystem, ReadLines){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    std::ifstream File(Path);
    if(!File.is_open()){
        return JSValueMakeBoolean(Context, false);
    }
    JSObjectRef Array = JSObjectMakeArray(Context, 0, NULL, NULL);
    std::string Line;
    int Index = 0;
    while(std::getline(File, Line)){
        JSStringRef LineString = JSStringCreateWithUTF8CString(Line.c_str());
        JSObjectSetPropertyAtIndex(Context, Array, Index, JSValueMakeString(Context, LineString), NULL);
        JSStringRelease(LineString);
        Index++;
    }
    File.close();
    return Array;
}

JSC_FUNC(Classes::FileSystem, WriteFile) {
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    const std::string Content = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    std::ofstream File(Path, std::ios::trunc);
    if(!File.is_open()){
        return JSValueMakeBoolean(Context, false);
    }
    File << Content;
    if(File.good()){
        File.close();
        return JSValueMakeBoolean(Context, true);
    }else{
        File.close();
        return JSValueMakeBoolean(Context, false);
    }
}