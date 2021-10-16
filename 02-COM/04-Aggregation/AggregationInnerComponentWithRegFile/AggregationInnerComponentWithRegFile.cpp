#include<Windows.h>
#include"AggregationInnerComponentWithRegFile.h"

interface INoAggregation
{
    virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
    virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
    virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

class CMultiplicationDivision : public INoAggregation, IMultiplication, IDivision
{
    private:
        long m_cRef;
        IUnknown *m_pIUnknownOuter;
    
    public:
        CMultiplicationDivision(IUnknown*);
        ~CMultiplicationDivision(void);

        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);

        HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
        ULONG __stdcall AddRef_NoAggregation(void);
        ULONG __stdcall Release_NoAggregation(void); 

        HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
        HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory:public IClassFactory
{
    private:
        long m_cRef;
    public:
        CMultiplicationDivisionClassFactory (void);
        ~CMultiplicationDivisionClassFactory (void);

        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void); 

        HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
        HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DLLMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
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

CMultiplicationDivisionClassFactory ::CMultiplicationDivisionClassFactory (void)
{
    m_cRef = 1;
}

CMultiplicationDivisionClassFactory ::~CMultiplicationDivisionClassFactory ()
{
}

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, 
    REFIID riid, void **ppv)
{
    CMultiplicationDivision *pCMultiplicarionDivision = NULL;
    HRESULT hr;

    if (pUnkOuter != NULL && riid != IID_IUnknown)
    {
        return (CLASS_E_NOAGGREGATION);
    }
    pCMultiplicarionDivision = new CMultiplicationDivision(pUnkOuter);
    
    if (pCMultiplicarionDivision == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCMultiplicarionDivision->QueryInterface_NoAggregation(riid, ppv);
    pCMultiplicarionDivision->Release_NoAggregation();
    return hr;
}

ULONG CMultiplicationDivisionClassFactory::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release()
{
    InterlockedDecrement(&m_cRef);
    if (m_cRef == 0)
    {
        delete(this);
        return(0);
    }
    return (m_cRef);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        InterlockedIncrement(&glNumberOfServerLocks);
    }
    else
    {
        InterlockedDecrement(&glNumberOfServerLocks);
    }
    return (S_OK);
}

CMultiplicationDivision::CMultiplicationDivision(IUnknown *pUnkownOuter)
{
    if (pUnkownOuter != NULL)
    {
        m_pIUnknownOuter = pUnkownOuter;
    }
    else
    {
        m_pIUnknownOuter = reinterpret_cast<IUnknown *> (static_cast<INoAggregation *> (this));
    }
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CMultiplicationDivision::~CMultiplicationDivision()
{
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
    return m_pIUnknownOuter->QueryInterface(riid, ppv);
}

ULONG CMultiplicationDivision::AddRef()
{
    return m_pIUnknownOuter->AddRef();
}

ULONG CMultiplicationDivision::Release()
{
    return m_pIUnknownOuter->Release();
}

HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<INoAggregation*>(this);
    }
    else if (riid == IID_IMultiplication)
    {
        *ppv = static_cast<IMultiplication*>(this);
    }
    else if (riid == IID_IDivision)
    {
        *ppv = static_cast<IDivision*>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(this)->AddRef();
    return (S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation()
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation()
{
    InterlockedDecrement(&m_cRef);
    if (m_cRef == 0)
    {
        delete(this);
        return(0);
    }
    return (m_cRef);
}

HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
    *pMultiplication = num1 * num2;
    return (S_OK);
}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
    *pDivision = num1 / num2;
    return (S_OK);
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
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

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
    HRESULT hr;
    if (rclsid != CLSID_MultiplicationDivision)
    {
        return(CLASS_E_CLASSNOTAVAILABLE);
    }
    pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
    if (pCMultiplicationDivisionClassFactory == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
    pCMultiplicationDivisionClassFactory->Release();
    return (hr);    
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
    if ((glNumberOfServerLocks == 0) && (glNumberOfActiveComponents == 0))
    {
        return(S_OK);
    }
    return (S_FALSE);
}
