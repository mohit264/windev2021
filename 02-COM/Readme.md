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

## Overhead / hidden members in C++
1. this pointer
2. vptr
3. type_info
4. LPVTBL ( Added in COM)

## History of COM

1. ClipBoard - 1987
       
       
       |       
       V
2. DDE - 1989
       
       
       |       
       V
3. OLE1 - 1991
       
       
       |       
       V
4. OLE2 - 1993
       
       
       |       
       V
5.    COM - 1995


       |
       
       |   
       
                   OSF
       
    
                     |
                  /  |  \
                /    V    \
              DCE   RPC  UUID
       
       
       
       
       |
       
       
       V
       
    DCOM - 1996

### COM Lolly-Pop Diagram
![image](https://user-images.githubusercontent.com/19527422/130830926-a0b4a113-5637-495f-bc38-6d446e7c0963.png)

> COM's one of the important feature is binary encapsulation. This is implemented using declaration of class inside cpp file instead of header file (.h). So that it can't be seen by anyone.

**link objfilename /DEF:def-file-name ole32.lib oleaut32.lib /machine:64 (for 64 bit)**


`   HRESULT CoCreateInstance(REFCLSID rclsID, IUnknown *punkOuter, DWORD dwClsCtx, REFIID iid, void **ppv)
    {
     
     IClassFactory *pIClassfactory;
     
     HRESULT hr;
     
     hr = CoGetClassObject(rClsID, dwClsCtx, NULL, IID_ICLASSFACTORY, (void **) &pIClassFactory);
     
     if(SUCEEDED(hr))
     
     {
     
             hr = pIClassFactory->CreateInstance(NULL, IID_ISum, ppv);
             if(SUCCEEDED(hr))
             {
                     pIcClassFactory->Release();
             }
     
     }
     return(hr);
  }
     `
>CoGetClassObject observes first parameter which is your CLSID. It takes this CLSID and goes into registry and search for that CLSID and retrieve the path of the dll from the CLSID key against that registry. After that CoGetClassObject calls LoadLibrary Function and pass the retrieved path. It then calls GetProcAddress for each exported function from your server dll. i.e.
> 1. DllGetClassObject
> 2. DllCanUnloadNow 
> and retrieved their function pointers and calls DllGetClassObject method and passes parameters as below
> (CLSID of CSumSubtract, IID of IClassFactory, and the empty \*\* ppv object to get IClassFactory Instance)

*If CoLoadLibrary's second parameter is set to True, COM probes periodically whether Dll is required for any work if not then call DllCanUnloadNow() to free out the memory area used by server dll. If the second parameter is set to false then when client exe is destroyed, Dll automatically gets evicted by OS.

IUnknown Properties

![image](https://user-images.githubusercontent.com/19527422/132557930-487d5599-7ccc-4f37-8635-845671706c00.png)


1. Identity

### Containment

![image](https://user-images.githubusercontent.com/19527422/133134849-32562788-aef8-4afa-9fed-6f2bd89d6b4b.png)

