# SEH_Handler
Windows application to raise different types of Win32 exceptions, which will be filtered by SEH handler. GUI is created using MFC.

Application is written in VS19 using v142 toolset. In source code you can find how to set your own custom unhandled exception filter,
which will be called every time, when an exception is raised.
There're 2 way of showing some exception information - by showing MessageBox or creating a little info dump with different fields of
ExceptionInfo struct + some part of registers.
