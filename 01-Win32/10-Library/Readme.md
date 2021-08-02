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
