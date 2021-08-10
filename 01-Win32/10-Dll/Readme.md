# Library
1. Dll is windows only but dynamic linking is avaialable on all OS often called as **dynamic module, library module, shared objects, dynalink module.**
2. In windows .lib is extension for static linking
3. In Unix static linking is .sa (static archieve / shared archieve) and and dynamic linking is .so (shared objects)
4. In Mac dynamic linking libraries extension is .dylib
5. There are dynamic link libraries in windows even though there is no extension is not dll.
   e.g. .sys in windows system folder (after protected mode windows) are also dlls
6. Every files inside control panel are dlls where their extensions are .cpl
7. All font files whose extensions are .fon, .fot (Font object type), .ftf (Free type font) are dlls
8. Most user mode drivers are usually dynamic link libraries whose extensions can be .drv

## Search Locations of the dll
There are 4 paths where you can use dlls
1. The best location of the dll is where the executable of the dll resides
2. Windows directory
3. System32 directory or SysWOW64 directory inside Windows directory 
4. In any directory which is inside environmental path

## Process and Dlls
For every process in Windows operating system (32-bit) , virtual memory is 4GB. Out of 4GB, OS reserve (2GB for itself and 2GB for user process). So in case of your process memory footprint is growing and reaching near to 2GB ceiling then OS throws an error that not enough memory error for that process.

### In .h files, there are only declarations or signatures
### In .dll there is your code
### In .lib(Import Library) tells linker where to map the dll at runtime in virtual address space.
### The one who serves is server and the one who consumes the services is Client

#### When you use extern "C" , it is the proper way to create dlls.

## SDKs other than Win32 SDK used for development Windows GUI based application
1. MinGW (Minimum GNU for Windows)
2. DJGPP (Not much used in now)
3. Borland
4. Watcom (Not used much today)

### Two Ways of Creating Dlls
1. Using Declspec : Should be use when both client and server are in your control or if the client will be created using Microsoft
2. Using Def File : When client is not in your control. i.e. if client application which is going to develop other than Microsoft compiler then use this approach to create the dlls. Microsoft use this approach to create it's own dlls using DEF Files.

> What actually in def file does which gives dll such flexibility

Dll is language independent, that means dll can be created in any language.
However, this is not true in case of DLL clients. i.e. If you created dll in C++ then it will run smoothly in Client created using C++ language but such guarantee can't be given for clients created in other languages!

> What is the Problem with such Client!

*Object Orient Programming Paradigm* specially **Polymorphism** feature in OOPs
> OOP is for Human Mind! Machine only understand Procedural Oriented language 

For, early binding - ( Function Overloading ), we can write function with same name but with different parameters, types and order of parameters.
However during compilation compiler mangles the name and create different functions to uniquely identify which function should be called at runtime as at binary level everything is procedural oriented programming.

**The Problem (commercial benefit!) with C++**
Since C++ has given freedom to compiler creators to implement their own creativity to mangle the names uniquely. This created different ways of name mangling between different compiler vendors and that's why C++ didn't have it's own binary standard!

> So to have universally accepted name mangling standard to work with C++ dlls across different C++ compiler vendors, we should use **extern "C"** so that it gets compiled to *C binary format* which is universally accepted binary standard  
