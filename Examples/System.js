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

const HRTime = System.HRTime();
Console.Log('HRTime ->', HRTime);

const Uptime = System.Uptime();
Console.Log('Uptime ->', Uptime);

const Uname = System.Uname();
Console.Log('Uname ->', Uname);

//const Environ = System.Environ;
//Console.Log('Environment ->', Environ);

// System.GetEnviron(EnvironmentVariableName);
// System.SetEnviron(EnvironmentVariableName, EnvironmentVariableValue);
// System.UnsetEnviron(EnvironmentVariableName);
// System.ChangeWorkingDirectory(NewWorkingDirectory);
const CurrentWorkingDirectory = System.CurrentWorkingDirectory();
Console.Log('Current Working Directory ->', CurrentWorkingDirectory);

const HomeDirectory = System.HomeDirectory();
Console.Log('Home Directory ->', HomeDirectory);

const TempDirectory = System.TempDirectory();
Console.Log('Temp Directory ->', TempDirectory);

const CPUInfo = System.CPUInfo();
Console.Log('CPU Info ->', CPUInfo);

const Platform = System.Platform();
Console.Log('Platform ->', Platform);

const NetworkInterfaces = System.NetworkInterfaces();
Console.Log('Network Interfaces ->', NetworkInterfaces);

const Hostname = System.GetHostname();
Console.Log('Hostname ->', Hostname);

// System.Sleep(1000) // The argument must be the time as ms, 1000ms -> 1s
const PID = System.GetPID();
Console.Log('PID ->', PID);

const PPID = System.GetPPID();
Console.Log('PPID ->', PPID);