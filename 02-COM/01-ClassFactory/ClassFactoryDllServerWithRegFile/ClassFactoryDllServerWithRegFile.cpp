#include<Windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

class CSumSubtract: public ISum, ISubtract
{
    private:
        long m_cRef;
    public:
        CSumSubtract(void);
        ~CSumSubtract(void);
        HRESULT  __stdcall QueryInterface(REFIID, void **);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);
        HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
        HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *); 
};

class CSumSubtractClassFactory: public IClassFactory
{
private:
    long m_cRef;
public:
    CSumSubtractClassFactory(/* args */);
    ~CSumSubtractClassFactory();
    HRESULT  __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef(void);
    ULONG __stdcall Release(void);
    HRESULT __stdcall CreateInstance(IUnknown *,REFIID, void **);
    HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents=0;
long glNumberOfActiveLocks=0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        /* code */
        break;
        case DLL_PROCESS_DETACH:
        break;
    }
    return (TRUE);
}

CSumSubtract::CSumSubtract(void)
{
    m_cRef=1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void)
{
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
    /*
    How come == is working as riid and IID are structures. By using Operator overloading.
    inline is like macro. It is recommended that inline function should be small.
    
    inline BOOL operator==(const GUID& guidOne, const GUID& guidTwo)
    {
        // code
        return IsEqualGuid(guidOne, guidTwo);
    }
    */
    if(riid == IID_IUnknown)
        *ppv=static_cast<ISum *>(this);
    else if (riid == IID_ISum)
    {
        *ppv = static_cast<ISum *>(this);
    }
    else if (riid == IID_ISubtract)
    {
        *ppv = static_cast<ISubtract *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    
    reinterpret_cast<IUnknown *> (*ppv)->AddRef();
    return (S_OK);
}

ULONG CSumSubtract::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CSumSubtract::Release()
{
    InterlockedDecrement(&m_cRef);
    if (m_cRef == 0)
    {
        delete(this);
        return(0);
    }
    return (m_cRef);
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
    *pSum = num1 + num2;
    return (S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
    *pSubtract = num1 - num2;
    return (S_OK);
}

CSumSubtractClassFactory::CSumSubtractClassFactory(/* args */)
{
    m_cRef =1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv =  static_cast<IClassFactory *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *> (*ppv)->AddRef();
    return (S_OK);
}

ULONG CSumSubtractClassFactory::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release()
{
    InterlockedDecrement(&m_cRef);
    if (m_cRef == 0)
    {
        delete(this);
        return(0);
    }
    return (m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid,
void **ppv)
{
    CSumSubtract *pCSumSubtract = NULL;
    HRESULT hr;
    if (pUnkOuter != NULL)
    {
        return (CLASS_E_NOAGGREGATION);
    }
    pCSumSubtract = new CSumSubtract;
    if (pCSumSubtract == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCSumSubtract->QueryInterface(riid, ppv);
    pCSumSubtract->Release();
    return(hr);
    
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        InterlockedIncrement(&glNumberOfActiveLocks);
    }
    else
    {
        InterlockedDecrement(&glNumberOfActiveLocks);
    }
    return (S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
    HRESULT hr;
    if (rclsid != CLSID_SumSubtract)
    {
        return(CLASS_E_CLASSNOTAVAILABLE);
    }
    pCSumSubtractClassFactory = new CSumSubtractClassFactory;
    if (pCSumSubtractClassFactory == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
    pCSumSubtractClassFactory->Release();
    return (hr);    
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
    if ((glNumberOfActiveLocks == 0) && (glNumberOfActiveComponents == 0))
    {
        return(S_OK);
    }
    return (S_FALSE);
}
