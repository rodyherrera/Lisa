#include <iostream>
#include <JavaScriptCore/JavaScript.h>
#include <map>
#include <vector>
#include "SQLite3.hpp"
#include "sqlite3.h"
#include "../../Utilities/Runtime/Runtime.hpp"
#include "../../Utilities/JSCWrapper/JSCWrapper.hpp"

using namespace Lisa;
using namespace Lisa::Utilities;

std::map<int, sqlite3*> SQLiteDBMap;
unsigned int NextDatabaseId = 0;

void Classes::SQLite3::Init(JSContextRef Context, JSObjectRef GlobalObject){
    JSObjectRef SQLite3Object = JSCWrapper::CreateObject(Context, GlobalObject, "SQLite3");
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Open", SQLite3::Open);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Remove", SQLite3::Remove);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Shutdown", SQLite3::Shutdown);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Sleep", SQLite3::Sleep);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "EnableLoadExtension", SQLite3::EnableLoadExtension);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "LoadExtension", SQLite3::LoadExtension);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Close", SQLite3::Close);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Version", SQLite3::Version);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Randomness", SQLite3::Randomness);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "VersionNumber", SQLite3::VersionNumber);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "SourceID", SQLite3::SourceID);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Execute", SQLite3::Execute);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Prepare", SQLite3::Prepare);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Step", SQLite3::Step);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Reset", SQLite3::Reset);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ClearBindings", SQLite3::ClearBindings);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "CloseV2", SQLite3::BindInt);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindInt", SQLite3::BindInt);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Finalize", SQLite3::Finalize);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindDouble", SQLite3::BindDouble);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindText", SQLite3::BindText);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindBlob", SQLite3::BindBlob);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindNull", SQLite3::BindNull);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindParameterCount", SQLite3::BindParameterCount);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindParameterName", SQLite3::BindParameterName);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindParameterIndex", SQLite3::BindParameterIndex);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "BindParameterIndexFromName", SQLite3::BindParameterIndexFromName);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnCount", SQLite3::ColumnCount);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnName", SQLite3::ColumnName);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnType", SQLite3::ColumnType);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnDouble", SQLite3::ColumnDouble);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnInt", SQLite3::ColumnInt);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnText", SQLite3::ColumnText);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnBlob", SQLite3::ColumnBlob);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "OpenV2", SQLite3::OpenV2);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "ColumnValue", SQLite3::ColumnValue);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Backup", SQLite3::Backup);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "PrepareV2", SQLite3::PrepareV2);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "PrepareV3", SQLite3::PrepareV3);
    JSCWrapper::CreateFunction(Context, SQLite3Object, "Restore", SQLite3::Restore);

    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OK", SQLITE_OK);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "ERROR", SQLITE_ERROR);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "INTERNAL", SQLITE_INTERNAL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "PERM", SQLITE_PERM);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "ABORT", SQLITE_ABORT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "BUSY", SQLITE_BUSY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "LOCKED", SQLITE_LOCKED);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NOMEM", SQLITE_NOMEM);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "READONLY", SQLITE_READONLY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "INTERRUPT", SQLITE_INTERRUPT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "IOERR", SQLITE_IOERR);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "CORRUPT", SQLITE_CORRUPT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NOTFOUND", SQLITE_NOTFOUND);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "FULL", SQLITE_FULL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "CANTOPEN", SQLITE_CANTOPEN);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "PROTOCOL", SQLITE_PROTOCOL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "EMPTY", SQLITE_EMPTY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "SCHEMA", SQLITE_SCHEMA);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "TOOBIG", SQLITE_TOOBIG);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "CONSTRAINT", SQLITE_CONSTRAINT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "MISMATCH", SQLITE_MISMATCH);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "MISUSE", SQLITE_MISUSE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NOLFS", SQLITE_NOLFS);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "AUTH", SQLITE_AUTH);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "FORMAT", SQLITE_FORMAT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "RANGE", SQLITE_RANGE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NOTADB", SQLITE_NOTADB);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NOTICE", SQLITE_NOTICE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "WARNING", SQLITE_WARNING);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "ROW", SQLITE_ROW);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "DONE", SQLITE_DONE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "INTEGER", SQLITE_INTEGER);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "FLOAT", SQLITE_FLOAT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "TEXT", SQLITE_TEXT);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "BLOB", SQLITE_BLOB);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "NULL", SQLITE_NULL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_READONLY", SQLITE_OPEN_READONLY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_READWRITE", SQLITE_OPEN_READWRITE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_CREATE", SQLITE_OPEN_CREATE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_URI", SQLITE_OPEN_URI);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_MEMORY", SQLITE_OPEN_MEMORY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_NOMUTEX", SQLITE_OPEN_NOMUTEX);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_FULLMUTEX", SQLITE_OPEN_FULLMUTEX);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_SHAREDCACHE", SQLITE_OPEN_SHAREDCACHE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_PRIVATECACHE", SQLITE_OPEN_PRIVATECACHE);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_WAL", SQLITE_OPEN_WAL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_NOFOLLOW", SQLITE_OPEN_NOFOLLOW);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_AUTOPROXY", SQLITE_OPEN_AUTOPROXY);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_MAIN_DB", SQLITE_OPEN_MAIN_DB);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_TEMP_DB", SQLITE_OPEN_TEMP_DB);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_TRANSIENT_DB", SQLITE_OPEN_TRANSIENT_DB);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_MAIN_JOURNAL", SQLITE_OPEN_MAIN_JOURNAL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_TEMP_JOURNAL", SQLITE_OPEN_TEMP_JOURNAL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_SUBJOURNAL", SQLITE_OPEN_SUBJOURNAL);
    JSCWrapper::SetIntegerProperty(Context, SQLite3Object, "OPEN_MASTER_JOURNAL", SQLITE_OPEN_MASTER_JOURNAL);
};

JSC_FUNC(Classes::SQLite3, OpenV2){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    sqlite3 *Database;
    int Result = sqlite3_open_v2(Path.data(), &Database, SQLITE_OPEN_READONLY, NULL);
    if(Result == SQLITE_OK){
        SQLiteDBMap[NextDatabaseId] = Database;
        Result = NextDatabaseId;
        NextDatabaseId++;
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Open){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    sqlite3 *Database;
    // FIX RETURN VALUE !!!
    int Result = sqlite3_open(Path.data(), &Database);
    if(Result == SQLITE_OK){
        SQLiteDBMap[NextDatabaseId] = Database;
        Result = NextDatabaseId;
        NextDatabaseId++;
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Remove){
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[0]);
    return JSValueMakeNumber(Context, remove(Path.data()));
};

JSC_FUNC(Classes::SQLite3, Close){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    int Result = sqlite3_close(Database);
    if(Result == SQLITE_OK){
        SQLiteDBMap.erase(DatabaseId);
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Execute){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    const std::string Query = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    char *ErrorMessage;
    int Result = sqlite3_exec(Database, Query.data(), NULL, NULL, &ErrorMessage);
    if(Result != SQLITE_OK){
        return JSCWrapper::CreateString(Context, ErrorMessage);
        sqlite3_free(ErrorMessage);
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, PrepareV2){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    const std::string Query = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement;
    int Result = sqlite3_prepare_v2(Database, Query.data(), Query.size(), &Statement, NULL);
    // FIX RETURN & V1 & V3
    if(Result == SQLITE_OK){
        JSObjectRef StatementObject = JSObjectMake(Context, nullptr, nullptr);
        JSCWrapper::SetObjectInObject(Context, StatementObject, "Statement", Statement);
        return StatementObject;
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Prepare){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    const std::string Query = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement;
    int Result = sqlite3_prepare(Database, Query.data(), Query.size(), &Statement, NULL);
    if(Result == SQLITE_OK){
        JSObjectRef StatementObject = JSObjectMake(Context, nullptr, nullptr);
        JSCWrapper::SetObjectInObject(Context, StatementObject, "Statement", Statement);
        return StatementObject;
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Step){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_step(Statement);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Reset){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_reset(Statement);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, ClearBindings){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_clear_bindings(Statement);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindInt){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement"); 
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    int Value = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[2]);
    int Result = sqlite3_bind_int(Statement, Index, Value);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Randomness){
    int Length = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    char Buffer[Length];
    sqlite3_randomness(Length, Buffer);
    return JSCWrapper::CreateString(Context, Buffer);
};

JSC_FUNC(Classes::SQLite3, CloseV2){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    int Result = sqlite3_close_v2(Database);
    if(Result == SQLITE_OK){
        SQLiteDBMap.erase(DatabaseId);
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindText){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    const std::string Value = JSCWrapper::GetStringFromJSValue(Context, Arguments[2]);
    int Result = sqlite3_bind_text(Statement, Index, Value.data(), Value.size(), SQLITE_TRANSIENT);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindBlob){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    const std::string Value = JSCWrapper::GetStringFromJSValue(Context, Arguments[2]);
    int Result = sqlite3_bind_blob(Statement, Index, Value.data(), Value.size(), SQLITE_TRANSIENT);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindDouble){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement"); 
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    double Value = JSCWrapper::GetNumberFromJSValue(Context, Arguments[2]);
    int Result = sqlite3_bind_double(Statement, Index, Value);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindNull){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement"); 
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    int Result = sqlite3_bind_null(Statement, Index);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindParameterCount){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_bind_parameter_count(Statement);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindParameterIndex){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement"); 
    int Result = sqlite3_bind_parameter_index(Statement, Name.data());
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindParameterName){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    const char *Result = sqlite3_bind_parameter_name(Statement, Index);
    return JSCWrapper::CreateString(Context, Result);
};

JSC_FUNC(Classes::SQLite3, BindParameterIndexFromName){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    const std::string Name = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_bind_parameter_index(Statement, Name.data());
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Finalize){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Result = sqlite3_finalize(Statement);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Version){
    return JSCWrapper::CreateString(Context, sqlite3_libversion());
};

JSC_FUNC(Classes::SQLite3, VersionNumber){
    return JSValueMakeNumber(Context, sqlite3_libversion_number());
};

JSC_FUNC(Classes::SQLite3, SourceID){
    return JSCWrapper::CreateString(Context, sqlite3_sourceid());
};

JSC_FUNC(Classes::SQLite3, ColumnCount){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSValueMakeNumber(Context, sqlite3_column_count(Statement));
};

JSC_FUNC(Classes::SQLite3, ColumnName){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSCWrapper::CreateString(Context, sqlite3_column_name(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnType){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSValueMakeNumber(Context, sqlite3_column_type(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnInt){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSValueMakeNumber(Context, sqlite3_column_int(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnDouble){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSValueMakeNumber(Context, sqlite3_column_double(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnText){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSCWrapper::CreateString(Context, (const char*)sqlite3_column_text(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnBlob){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    return JSCWrapper::CreateString(Context, (const char*)sqlite3_column_blob(Statement, Index));
};

JSC_FUNC(Classes::SQLite3, ColumnValue){
    JSObjectRef StatementObject = JSValueToObject(Context, Arguments[0], nullptr);
    int Index = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement = (sqlite3_stmt*)JSCWrapper::GetObjectFromObject(Context, StatementObject, "Statement");
    int Type = sqlite3_column_type(Statement, Index);
    switch(Type){
        case SQLITE_INTEGER:
            return JSValueMakeNumber(Context, sqlite3_column_int(Statement, Index));
        case SQLITE_FLOAT:
            return JSValueMakeNumber(Context, sqlite3_column_double(Statement, Index));
        case SQLITE_TEXT:
            return JSCWrapper::CreateString(Context, (const char*)sqlite3_column_text(Statement, Index));
        case SQLITE_BLOB:
            return JSCWrapper::CreateString(Context, (const char*)sqlite3_column_blob(Statement, Index));
        case SQLITE_NULL:
            return JSValueMakeNull(Context);
    }
    return JSValueMakeNull(Context);
};

JSC_FUNC(Classes::SQLite3, Backup){
    int SourceDatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    int DestinationDatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3 *SourceDatabase = SQLiteDBMap[SourceDatabaseId];
    sqlite3 *DestinationDatabase = SQLiteDBMap[DestinationDatabaseId];
    sqlite3_backup *Backup = sqlite3_backup_init(DestinationDatabase, "main", SourceDatabase, "main");
    int Result = sqlite3_backup_step(Backup, -1);
    if(Result == SQLITE_DONE){
        Result = sqlite3_backup_finish(Backup);
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Restore){
    int SourceDatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    int DestinationDatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    sqlite3 *SourceDatabase = SQLiteDBMap[SourceDatabaseId];
    sqlite3 *DestinationDatabase = SQLiteDBMap[DestinationDatabaseId];
    sqlite3_backup *Backup = sqlite3_backup_init(DestinationDatabase, "main", SourceDatabase, "main");
    int Result = sqlite3_backup_step(Backup, -1);
    if(Result == SQLITE_DONE){
        Result = sqlite3_backup_finish(Backup);
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, PrepareV3){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    const std::string Query = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    sqlite3_stmt *Statement;
    int Result = sqlite3_prepare_v3(Database, Query.data(), Query.size(), 0, &Statement, NULL);
    if(Result == SQLITE_OK){
        JSObjectRef StatementObject = JSObjectMake(Context, nullptr, nullptr);
        JSCWrapper::SetObjectInObject(Context, StatementObject, "Statement", Statement);
        return StatementObject;
    }
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, LoadExtension){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    const std::string Path = JSCWrapper::GetStringFromJSValue(Context, Arguments[1]);
    const std::string FunctionName = JSCWrapper::GetStringFromJSValue(Context, Arguments[2]);
    int Result = sqlite3_load_extension(Database, Path.data(), FunctionName.data(), 0);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, EnableLoadExtension){
    int DatabaseId = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3 *Database = SQLiteDBMap[DatabaseId];
    int OnOff = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[1]);
    int Result = sqlite3_enable_load_extension(Database, OnOff);
    return JSValueMakeNumber(Context, Result);
};

JSC_FUNC(Classes::SQLite3, Sleep){
    int Milliseconds = (int)JSCWrapper::GetNumberFromJSValue(Context, Arguments[0]);
    sqlite3_sleep(Milliseconds);
    return JSValueMakeUndefined(Context);
};

JSC_FUNC(Classes::SQLite3, Shutdown){
    int Result = sqlite3_shutdown();
    return JSValueMakeNumber(Context, Result);
};