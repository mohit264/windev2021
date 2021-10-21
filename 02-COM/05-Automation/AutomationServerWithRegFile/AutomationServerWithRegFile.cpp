//Use cl /c /EHsc -DUNICODE  AutomationServerWithRegFile.cpp for compilation
// in Developer command prompt. 
#include<Windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFile.h"

//class declarations
//co class
class CMyMath :public IMyMath
{
    private:
        long m_cRef;
        ITypeInfo *m_pITypeInfo;
    public:
        CMyMath (/* args */);
        ~CMyMath ();

        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);

        HRESULT __stdcall GetTypeInfoCount(UINT*);
        HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
        HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
        HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*,
                                EXCEPINFO*, UINT*);

        HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
        HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
        HRESULT InitInstance(void);
};

class CMyMathFactory: public IClassFactory
{
    private:
        long m_cRef;
    public:
        CMyMathFactory(/* args */);
        ~CMyMathFactory();

        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);

        HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
        HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// {FE3BC724-3D4B-44A3-B512-0DB23FB5BDA0}
const GUID LIBID_AutomationServer = 
{ 0xfe3bc724, 0x3d4b, 0x44a3, 0xb5, 0x12, 0xd, 0xb2, 0x3f, 0xb5, 0xbd, 0xa0 };

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        break;
    
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

CMyMath::CMyMath()
{
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CMyMath::~CMyMath()
{
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<IMyMath*>(this);
    }
    else if (riid == IID_IDispatch)
    {
        *ppv = static_cast<IMyMath*>(this);
    }    
    else if (riid == IID_IMyMath)
    {
        *ppv = static_cast<IMyMath*>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return (S_OK);
    
}

ULONG CMyMath::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return m_cRef;
}

ULONG CMyMath::Release(void)
{
    InterlockedDecrement(&m_cRef);

    if (m_cRef == 0)
    {
        m_pITypeInfo->Release();
        m_pITypeInfo = NULL;
        delete(this);
        return 0;
    }
    return(m_cRef);
}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
    *pSum = num1 + num2;
    return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtraction)
{
    *pSubtraction = num1 - num2;
    return (S_OK);
}

HRESULT CMyMath::InitInstance()
{
    void COMErrorDescriptionString(HWND, HRESULT);

    HRESULT hr;
    ITypeLib *pITypelib = NULL;

    if (m_pITypeInfo == NULL)
    {
        hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypelib);

        if (FAILED(hr))
        {
            COMErrorDescriptionString(NULL, hr);
            return(hr);
        }
        hr = pITypelib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
        if (FAILED(hr))
        {
            COMErrorDescriptionString(NULL, hr);
            pITypelib->Release();
            return(hr);
        }
        pITypelib->Release();
    }
    return (S_OK);
}

CMyMathFactory::CMyMathFactory(/* args */)
{
    m_cRef = 1;
}

CMyMathFactory::~CMyMathFactory()
{
}

HRESULT CMyMathFactory::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else
    {
        *ppv = NULL;
        return(E_NOINTERFACE);
    }
    
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return(S_OK);
}

ULONG CMyMathFactory::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMyMathFactory::Release()
{
    InterlockedDecrement(&m_cRef);

    if (m_cRef == 0)
    {
        delete(this);
        return 0;
    }
    return(m_cRef);
}

HRESULT CMyMathFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    CMyMath *pCMyMath = NULL;
    HRESULT hr;
    if(pUnkOuter != NULL)
        return (CLASS_E_NOAGGREGATION);
    pCMyMath = new CMyMath;
    if (pCMyMath == NULL)
    {
        return(E_OUTOFMEMORY);
    }
    
    pCMyMath->InitInstance();

    hr = pCMyMath->QueryInterface(riid, ppv);
    pCMyMath->Release();
    return(hr);
}

HRESULT CMyMathFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        InterlockedIncrement(&glNumberOfServerLocks);
    }
    else
    {
        InterlockedDecrement(&glNumberOfServerLocks);
    }
    return(S_OK);
}

//Implementation of IDispatch methods

HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo)
{
    *pCountTypeInfo = 1;
    return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
    *ppITypeInfo = NULL;

    if (iTypeInfo != 0)
    {
        return(DISP_E_BADINDEX);
    }
    m_pITypeInfo->AddRef();
    *ppITypeInfo = m_pITypeInfo;

    return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, 
                    LCID lcid, DISPID *rgDispid)
{
    return (DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispid));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO 
                *pExcepInfo, UINT *puArgErr)
{
    // variable declarations
    HRESULT hr;

    //code
    hr = DispInvoke(this, m_pITypeInfo, dispIdMember, wFlags, pDispParams, 
                    pVarResult, pExcepInfo, puArgErr);
    return(hr);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, 
                            void **ppv)
{
    // variable declarations
    CMyMathFactory *pCMyMathClassFactory;
    HRESULT hr;

    //code
    if (rclsid != CLSID_MyMath)
    {
        return (CLASS_E_CLASSNOTAVAILABLE);
    }

    pCMyMathClassFactory = new CMyMathFactory;

    if (pCMyMathClassFactory == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    
    hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
    pCMyMathClassFactory->Release();

    return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
    //code
    if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
    {
        return (S_OK);
    }
    else
    {
        return (S_FALSE);
    }
    
}

void COMErrorDescriptionString(HWND hwnd, HRESULT hr)
{
    // variable declarations
    TCHAR *szErrorMessage;
    TCHAR str[255];

    //code
    if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
    {
        hr = HRESULT_CODE(hr);
    }
    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
        NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &szErrorMessage, 
        0, NULL) != 0 )
    {
        /* code */
        swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
        LocalFree(szErrorMessage);
    }
    else
    {
        swprintf_s(str, TEXT("[ Could not find a description for error # %#x.]\n"), 
        hr);
    }

    MessageBox(NULL, str, TEXT("COM Error"), MB_OK);
}