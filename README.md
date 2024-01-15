# LisaJS
Lisa is a C++ application that provides a fast and lightweight runtime environment for JavaScript scripts. It uses JavaScriptCore, providing an integrated environment with specific functionalities and utilities.

## Main Features
- Integration with JavaScriptCore for script execution.
- Built-in modules for functionalities such as `Console`, `System`, `FileSystem`, `UUID`, `SQLite3` and `Network`.
- Custom methods like `SetTimeout`, `SetInterval` and `ClearTimer`.
- Support for running scripts from external files.

## Installation
Before starting the compilation, you need to clone the repository if you have not already done so, to do this, you must execute the following command in your terminal:
```bash
git clone https://github.com/rodyherrera/Lisa/
```

In order to compile Lisa, you must have a series of dependencies, which are installed by using the `make` command within the root of the repository, which will execute the `Makefile` file.

You may prefer to install the dependencies yourself using:
```bash
sudo apt-get install libwebkit2gtk-4.0-dev libboost-all-dev libsqlite3-dev libpoco-dev libuv1-dev
```

Once you have the cloned repository and the required dependencies installed, we can proceed to compile the source code!

```bash
# Assuming you are at the root of the repository.
make
```

Or you can also prefer the following way to install and compile Lisa:
```bash
git clone https://github.com/rodyherrera/Lisa/ && cd Lisa && make
```

## Examples 
Explore the functionality of LisaJS by checking out the examples provided in the `Examples` folder. These examples demonstrate the usage of the various modules and objects available in LisaJS. 

You must run the files from the root of the repository, for example:
```bash
./Lisa Examples/Console.js
# Or
./Lisa Examples/SQLite3.js
```

## Description of Makefile Targets and Variables

| Target                | Description                                                                                     |
|-----------------------|-------------------------------------------------------------------------------------------------|
| **all**               | The default target that installs dependencies, adds the current directory to the `PATH` (if not added), and compiles the project.                       |
| **install_dependencies** | Installs the necessary dependencies for building the project using `apt-get`. Requires administrator privileges.                        |
| **build**             | Compiles the project, generating the `Lisa` executable. This target uses the defined rules to compile the source code.                                  |
| **add_path**          | Adds the current directory to the `PATH`. This allows running the `Lisa` executable from any location on your system without specifying the full path. |
| **clean**             | Removes object files and the executable generated during compilation.                           |

### Variables:

| Variable              | Description                                                                                     |
|-----------------------|-------------------------------------------------------------------------------------------------|
| **CXX**               | Specifies the compiler to be used for compiling the source code. In this case, it is set to `g++`.                         |
| **CXXFLAGS**          | Defines compilation flags. In this case, it sets the C++ version to C++2a and enables warning generation (`-Wall`).                        |
| **INCLUDES**          | Specifies the include directories for the compiler. It includes the necessary directories to find required headers.                      |
| **LDFLAGS**           | Defines linker flags. Specifies the necessary libraries for linking the executable.                         |
| **SOURCE_DIR**        | Specifies the directory where the project's source files are located.                          |
| **SOURCES**           | Generates the list of source files (.cpp) in the directory specified by SOURCE_DIR.                         |
| **OBJECTS**           | Generates the list of object files (.o) corresponding to the source files.                           |
| **IS_PATH_ADDED**     | Checks if the current directory has already been added to the `PATH`.                          |
| **EXECUTABLE**        | Specifies the name of the executable that will be generated during compilation. |

## API Reference

### FileSystem
The `FileSystem` module in LisaJS provides a set of functions for interacting with the file system. It allows you to perform various operations such as file manipulation, directory creation, checking file existence, and more.

| Method                                            | Description                                                                                                          |
|---------------------------------------------------|----------------------------------------------------------------------------------------------------------------------|
| `AbsolutePath(path: string): string`               | Returns the absolute path of the given path.                                                                         |
| `CanonicalPath(path: string): string`              | Returns the canonical path of the given path.                                                                        |
| `ReadLines(path: string): string[]`                | Reads the contents of the file specified by path and returns an array containing each line as a separate string.    |
| `RelativePath(path: string): string`               | Returns the relative path of the given path.                                                                         |
| `Copy(sourcePath: string, destinationPath: string): void` | Copies the file or directory from sourcePath to destinationPath.                                                  |
| `CopyFileContent(sourcePath: string, destinationPath: string): void` | Copies the contents of the file from sourcePath to destinationPath.                                           |
| `CopySymlink(sourcePath: string, destinationPath: string): void` | Copies the symlink from sourcePath to destinationPath.                                                         |
| `CreateDirectory(path: string): boolean`           | Creates a new directory specified by path. Returns true if successful.                                            |
| `CreateDirectories(path: string): boolean`         | Creates directories specified by path, including all parent directories if they do not exist. Returns true if successful.|
| `CreateHardLink(sourcePath: string, destinationPath: string): void` | Creates a hard link from sourcePath to destinationPath.                                                         |
| `CreateSymlink(sourcePath: string, destinationPath: string): void` | Creates a symbolic link from sourcePath to destinationPath.                                                       |
| `CreateDirectorySymlink(sourcePath: string, destinationPath: string): void` | Creates a directory symbolic link from sourcePath to destinationPath.                                       |
| `WriteFile(path: string, content: string): boolean`| Writes the specified content to the file specified by path. Returns true if successful.                             |
| `CurrentPath(): string`                             | Returns the current working directory.                                                                              |
| `Exists(path: string): boolean`                     | Checks if the file or directory specified by path exists. Returns true if it exists.                               |
| `Equivalent(path1: string, path2: string): boolean` | Checks if the paths path1 and path2 refer to the same file system entity. Returns true if they are equivalent.       |
| `ReadFile(path: string): string`                    | Reads the entire contents of the file specified by path and returns it as a string.                                  |
| `FileSize(path: string): number`                    | Returns the size of the file specified by path in bytes.                                                            |
| `HardLinkCount(path: string): number`               | Returns the number of hard links to the file specified by path.                                                     |
| `GetLastWriteTime(path: string): number`            | Returns the last write time of the file specified by path in milliseconds since the epoch.                          |
| `SetLastWriteTime(path: string, time: number): void` | Sets the last write time of the file specified by path to the provided time (in milliseconds since the epoch).      |
| `SetPermissions(path: string, permissions: number): void` | Sets the permissions of the file or directory specified by path to the provided permissions.                   |
| `ReadSymlink(path: string): string`                 | Reads the target of the symlink specified by path and returns it as a string.                                       |
| `Remove(path: string): boolean`                     | Removes the file or directory specified by path. Returns true if successful.                                        |
| `RemoveRecursively(path: string): boolean`          | Recursively removes the file or directory specified by path. Returns true if successful.                            |
| `Rename(sourcePath: string, destinationPath: string): void` | Renames the file or directory from sourcePath to destinationPath.                                                |
| `ResizeFile(path: string, fileSize: number): void`  | Resizes the file specified by path to the given fileSize in bytes.                                                 |
| `Space(path: string): { Capacity: number, Free: number, Available: number }` | Returns an object containing information about the disk space at the specified path, including capacity, free space, and available space.|
| `TempDirectoryPath(): string`                       | Returns the path of the temporary directory.                                                                        |
| `IsBlockFile(path: string): boolean`                | Checks if the file specified by path is a block special file. Returns true if it is.                                 |
| `IsCharacterFile(path: string): boolean`            | Checks if the file specified by path is a character special file. Returns true if it is.                             |
| `IsDirectory(path: string): boolean`                | Checks if the path specified by path refers to a directory. Returns true if it is.                                   |
| `IsEmpty(path: string): boolean`                    | Checks if the directory specified by path is empty. Returns true if it is.                                           |
| `IsFifo(path: string): boolean`                     | Checks if the file specified by path is a FIFO (named pipe). Returns true if it is.                                   |
| `IsOther(path: string): boolean`                    | Checks if the file specified by path is of an unknown type. Returns true if it is.                                   |
| `IsRegularFile(path: string): boolean`              | Checks if the file specified by path is a regular file. Returns true if it is.                                       |
| `IsSocket(path: string): boolean`                   | Checks if the file specified by path is a socket. Returns true if it is.                                              |
| `IsSymlink(path: string): boolean`                  | Checks if the file specified by path is a symbolic link. Returns true if it is.                                       |

### Network
The `Network` module in LisaJS provides functions related to network information.
| Method                          | Description                                                       |
|---------------------------------|-------------------------------------------------------------------|
| `IPv4(): string`                 | Returns a string representing an IPv4 address.                    |
| `IPv6(): string`                 | Returns a string representing an IPv6 address.                    |
| `Broadcast(): string`            | Returns a string representing the broadcast address.              |
| `Any(): string`                  | Returns a string representing the wildcard address (any).         |
| `IsWildcard(ip: string): boolean`| Checks if the provided IP address is a wildcard address. Returns true if it is.|
| `IsBroadcast(ip: string): boolean`| Checks if the provided IP address is a broadcast address. Returns true if it is.|
| `IsLoopback(ip: string): boolean`| Checks if the provided IP address is a loopback address. Returns true if it is.|
| `IsMulticast(ip: string): boolean`| Checks if the provided IP address is a multicast address. Returns true if it is.|
| `IsUnicast(ip: string): boolean`| Checks if the provided IP address is a unicast address. Returns true if it is.|
| `IsLinkLocal(ip: string): boolean`| Checks if the provided IP address is a link-local address. Returns true if it is.|
| `IsSiteLocal(ip: string): boolean`| Checks if the provided IP address is a site-local address. Returns true if it is.|
| `IsIPv4Compatible(ip: string): boolean`| Checks if the provided IP address is IPv4-compatible. Returns true if it is.|
| `IsIPv4Mapped(ip: string): boolean`| Checks if the provided IP address is mapped to IPv4. Returns true if it is.|

### SQLite3
The `SQLite3` module in LisaJS provides functions for working with SQLite databases.

| Method                           | Description                                               |
|----------------------------------|-----------------------------------------------------------|
| `Open(Path: string): number`      | Opens a SQLite database at the specified path. Returns a unique identifier for the database. |
| `OpenV2(Path: string): number`    | Opens a SQLite database at the specified path with extended options. Returns a unique identifier for the database. |
| `Remove(Path: string): number`    | Removes (deletes) the SQLite database at the specified path. Returns 0 on success. |
| `Close(DatabaseId: number): number`| Closes the SQLite database identified by the given identifier. Returns 0 on success. |
| `Execute(DatabaseId: number, Query: string): number` | Executes an SQL query on the specified database. Returns 0 on success. |
| `PrepareV2(DatabaseId: number, Query: string): number` | Prepares an SQL statement for execution with extended options. Returns a statement object or an error code. |
| `Prepare(DatabaseId: number, Query: string): number` | Prepares an SQL statement for execution. Returns a statement object or an error code. |
| `Step(Statement: object): number` | Executes a prepared statement. Returns a result code. |
| `Reset(Statement: object): number` | Resets a prepared statement. Returns a result code. |
| `ClearBindings(Statement: object): number` | Clears the bindings on a prepared statement. Returns a result code. |
| `BindInt(Statement: object, Index: number, Value: number): number` | Binds an integer value to a parameter in a prepared statement. Returns a result code. |
| `Randomness(Length: number): string` | Generates random data of the specified length. Returns a string. |
| `CloseV2(DatabaseId: number): number` | Closes a SQLite database with extended options. Returns 0 on success. |
| `BindText(Statement: object, Index: number, Value: string): number` | Binds a text value to a parameter in a prepared statement. Returns a result code. |
| `BindBlob(Statement: object, Index: number, Value: string): number` | Binds a blob value to a parameter in a prepared statement. Returns a result code. |
| `BindDouble(Statement: object, Index: number, Value: number): number` | Binds a double value to a parameter in a prepared statement. Returns a result code. |
| `BindNull(Statement: object, Index: number): number` | Binds a null value to a parameter in a prepared statement. Returns a result code. |
| `BindParameterCount(Statement: object): number` | Returns the number of parameters in a prepared statement. |
| `BindParameterName(Statement: object, Index: number): string` | Returns the name of the specified parameter in a prepared statement. |
| `BindParameterIndex(Statement: object, Name: string): number` | Returns the index of the specified parameter in a prepared statement. |
| `BindParameterIndexFromName(Statement: object, Name: string): number` | Returns the index of the specified parameter in a prepared statement. |
| `Finalize(Statement: object): number` | Finalizes a prepared statement. Returns a result code. |
| `Version(): string` | Returns the SQLite library version. |
| `VersionNumber(): number` | Returns the SQLite library version number. |
| `SourceID(): string` | Returns the SQLite library source ID. |
| `ColumnCount(Statement: object): number` | Returns the number of columns in the result set of a prepared statement. |
| `ColumnName(Statement: object, Index: number): string` | Returns the name of the specified column in the result set of a prepared statement. |
| `ColumnType(Statement: object, Index: number): number` | Returns the data type of the specified column in the result set of a prepared statement. |
| `ColumnInt(Statement: object, Index: number): number` | Returns the integer value of the specified column in the result set of a prepared statement. |
| `ColumnDouble(Statement: object, Index: number): number` | Returns the double value of the specified column in the result set of a prepared statement. |
| `ColumnText(Statement: object, Index: number): string` | Returns the text value of the specified column in the result set of a prepared statement. |
| `ColumnBlob(Statement: object, Index: number): string` | Returns the blob value of the specified column in the result set of a prepared statement. |
| `ColumnValue(Statement: object, Index: number): any` | Returns the value of the specified column in the result set of a prepared statement. |
| `Backup(SourceDatabaseId: number, DestinationDatabaseId: number): number` | Initiates a backup from the source database to the destination database. Returns a result code. |
| `Restore(SourceDatabaseId: number, DestinationDatabaseId: number): number` | Initiates a restore from the source database to the destination database. Returns a result code. |
| `PrepareV3(DatabaseId: number, Query: string): number` | Prepares an SQL statement for execution with extended options. Returns a statement object or an error code. |
| `LoadExtension(DatabaseId: number, Path: string, FunctionName: string): number` | Loads a SQLite extension from the specified path with the given function name. Returns a result code. |
| `EnableLoadExtension(DatabaseId: number, OnOff: number): number` | Enables or disables the loading of SQLite extensions for the specified database. Returns a result code. |
| `Sleep(Milliseconds: number): undefined` | Sleeps (pauses) the execution for the specified number of milliseconds. |
| `Shutdown(): number` | Shuts down the SQLite library. Returns a result code. |

### System
The `System` module in LisaJS provides functions for interacting with system-related information.

| Method                                  | Description                                               |
| --------------------------------------- | --------------------------------------------------------- |
| `HRTime`                                | Returns the high-resolution time.                          |
| `Uptime`                                | Returns the system uptime.                                 |
| `Uname`                                 | Returns information about the system name and version.    |
| `Environ`                               | Returns an object containing the environment variables.   |
| `GetEnviron(name)`                      | Returns the value of the specified environment variable.  |
| `SetEnviron(name, value)`               | Sets the value of the specified environment variable.     |
| `UnsetEnviron(name)`                    | Unsets the specified environment variable.                |
| `ChangeWorkingDirectory(directory)`     | Changes the current working directory.                    |
| `CurrentWorkingDirectory()`             | Returns the current working directory.                    |
| `HomeDirectory()`                       | Returns the home directory.                                |
| `TempDirectory()`                       | Returns the temporary directory.                           |
| `CPUInfo()`                             | Returns information about the CPU.                         |
| `Platform()`                            | Returns information about the platform.                    |
| `NetworkInterfaces()`                   | Returns information about network interfaces.             |
| `GetHostname()`                         | Returns the hostname of the system.                        |
| `GetPID()`                              | Returns the process ID.                                    |
| `GetPPID()`                             | Returns the parent process ID.                             |
| `Sleep(milliseconds)`                   | Pauses execution for the specified number of milliseconds. |

### UUID
The `UUID` module in LisaJS provides functions for generating UUIDs.

| Method         | Description                               |
| -------------- | ----------------------------------------- |
| `v1()`         | Generates a UUID using the v1 algorithm.   |
| `v4()`         | Generates a UUID using the v4 algorithm.   |
| `v5(namespace, name)` | Generates a UUID using the v5 algorithm with a specified namespace and name. |


### Console
The `Console` module in LisaJS provides a set of functions for interacting with the console. It allows you to log messages and information.


| Method         | Description                                    |
| -------------- | ---------------------------------------------- |
| `Log(...args)` | Logs messages to the console with a line break. |