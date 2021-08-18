# COM - Component Object Model
COM is discipline in Programming
COM is the best way of IPC

> COM is platform for building modular, Object Oriented, Customizable, Upgradable, Programming Language Independent, Distributable applications and libraries.

1. All User mode device driver foundations are developed in COM ( UMDF )
2. Windows explorer is developed in COM
3. IIS and Internet Explorer is COM based
4. DirectX is developed in COM
5. All Scripting languages run on Windows due to COM support
6. WMI is COM based
7. Registry is in COM
8. WinRT is based on COM

All popular softwares developed in other platform such as Opera Safari, ITUNES, FIREFOX, VLC which ported due to COM.

**OOP = Polymorphism + Late Binding + Syntactical Encapsualtion + Implementation Inheritance
COM = Polymorphism + Late Late Binding (Real Late Binding) + Binary Encapsulation + Interface Inheritance + Binary Code Reusability**

## Why COM

1. DLL has to be loaded by name. Where In COM DLL is loaded from Registry.
2. Not all programming languages are capable of creating DLL.
3. DLL doesn't get automatically loaded, It has to be loaded explictly and get the address of function. COM made dll loading automatically.
4. DLL is not object oriented. DLL can only export procedural functions. DLL can't expose the functions written inside the class! COM made exporting classes possible.
5. Because of Name Mangling, cliebnt has to be of same vendor. Extern "C" can only be applied to open functions.
6. When you modify the Dlls, firstly we don't know which clients have linked Dlls implicitly which requires the Dlls need to relink. In COM Dlls can have multiple versions. 
