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

#ifndef LISA_CLASSES_SQLITE3_HPP
#define LISA_CLASSES_SQLITE3_HPP
#include "../../Utilities/Runtime/Runtime.hpp"
#include <JavaScriptCore/JavaScript.h>

namespace Lisa::Classes{
    class SQLite3{
        public:
            static void Init(JSContextRef Context, JSObjectRef GlobalObject);
            JSC_FUNC_DEF(Open);
            JSC_FUNC_DEF(Close);
            JSC_FUNC_DEF(Version);
            JSC_FUNC_DEF(VersionNumber);
            JSC_FUNC_DEF(SourceID);
            JSC_FUNC_DEF(Execute);
            JSC_FUNC_DEF(Prepare);
            JSC_FUNC_DEF(Step);
            JSC_FUNC_DEF(Finalize);
            JSC_FUNC_DEF(Reset);
            JSC_FUNC_DEF(ClearBindings);
            JSC_FUNC_DEF(BindInt);
            JSC_FUNC_DEF(BindDouble);
            JSC_FUNC_DEF(BindText);
            JSC_FUNC_DEF(BindBlob);
            JSC_FUNC_DEF(BindNull);
            JSC_FUNC_DEF(BindParameterCount);
            JSC_FUNC_DEF(BindParameterName);
            JSC_FUNC_DEF(CloseV2);
            JSC_FUNC_DEF(BindParameterIndex);
            JSC_FUNC_DEF(BindParameterIndexFromName);
            JSC_FUNC_DEF(ColumnCount);
            JSC_FUNC_DEF(ColumnName);
            JSC_FUNC_DEF(ColumnType);
            JSC_FUNC_DEF(Randomness);
            JSC_FUNC_DEF(ColumnDouble);
            JSC_FUNC_DEF(Remove);
            JSC_FUNC_DEF(OpenV2);
            JSC_FUNC_DEF(ColumnInt);
            JSC_FUNC_DEF(ColumnText);
            JSC_FUNC_DEF(ColumnBlob);
            JSC_FUNC_DEF(ColumnValue);
            JSC_FUNC_DEF(Backup);
            JSC_FUNC_DEF(Restore);
            JSC_FUNC_DEF(PrepareV2);
            JSC_FUNC_DEF(PrepareV3);
            JSC_FUNC_DEF(LoadExtension);
            JSC_FUNC_DEF(EnableLoadExtension);
            JSC_FUNC_DEF(Sleep);
            JSC_FUNC_DEF(Shutdown);

    };
};

#endif