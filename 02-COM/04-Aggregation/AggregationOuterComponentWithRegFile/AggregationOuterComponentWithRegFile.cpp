#include<Windows.h>
#include"AggregationInnerComponentWithRegFile.h"
#include"AggregationOuterComponentWithRegFile.h"

class CSumSubtract:public ISum, ISubtract
{
    private:
        long m_cRef;
        IUnknown *m_pIUknownInner;
        IMultiplication *m_pIMultiplication;
        IDivision *m_pIDivision;

    public:
        CSumSubtract(void);
        ~CSumSubtract(void);

        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();

        HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
        HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
        HRESULT __stdcall InitializeInnerComponent();
};

class CSumSubtractClassFactory: public IClassFactory
{
private:
    long m_cRef;
public:
    CSumSubtractClassFactory(void);
    ~CSumSubtractClassFactory(void);
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
    m_pIMultiplication = NULL;
    m_pIDivision = NULL;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
    InterlockedDecrement(&glNumberOfActiveComponents);
    if (m_pIMultiplication)
    {
        m_pIMultiplication->Release();
        m_pIMultiplication = NULL;
    }

    if (m_pIDivision)
    {
        m_pIDivision->Release();
        m_pIDivision = NULL;
    }
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
    if(riid == IID_IUnknown)
        *ppv = static_cast<ISum *>(this);
    else if (riid == IID_ISum)
    {
        *ppv = static_cast<ISum *>(this);
    }
    else if (riid == IID_ISubtract)
    {
        *ppv = static_cast<ISubtract *>(this);
    }
    else if (riid == IID_IMultiplication)
    {
        return (m_pIUknownInner->QueryInterface(riid, ppv));
    }
    else if (riid == IID_IDivision)
    {
        return (m_pIUknownInner->QueryInterface(riid, ppv));
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
    return m_cRef;
}

ULONG CSumSubtract::Release()
{
    InterlockedDecrement(&m_cRef);
    if (m_cRef == 0)
    {
        delete(this);
        return 0;
    }
    return m_cRef;    
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *piSum)
{
    *piSum = num1 + num2;
    return(S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *piSubtraction)
{
    *piSubtraction = num1 - num2;
    return (S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
    HRESULT hr;
    hr = CoCreateInstance(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown*>(this),
    CLSCTX_INPROC_SERVER, IID_IUnknown, (void**) &m_pIUknownInner);

    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IUnknown Interface can not be obtained from Inner"),
        TEXT("Error"), MB_OK);
        
        return (E_FAIL);
    }

    hr = m_pIUknownInner->QueryInterface(IID_IMultiplication, (void**) &m_pIMultiplication);

    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IMultiplication interface can not be obtained"),
        TEXT("Error"), MB_OK);

        m_pIUknownInner->Release();
        m_pIUknownInner = NULL;
        return (E_FAIL);
    }
    
    hr = m_pIUknownInner->QueryInterface(IID_IDivision, (void**) &m_pIDivision);

    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IDivision interface can not be obtained"),
        TEXT("Error"), MB_OK);

        m_pIUknownInner->Release();
        m_pIUknownInner = NULL;

        m_pIMultiplication->Release();
        m_pIMultiplication = NULL;
        return (E_FAIL);
    }

    return (S_OK);
}

CSumSubtractClassFactory::CSumSubtractClassFactory(void)
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
    hr = pCSumSubtract->InitializeInnerComponent();
    if (FAILED(hr))
    {
        MessageBox(NULL, 
                    TEXT("Failed to Initialize Inner Component"),
                    TEXT("Error!!"), MB_OK);
        pCSumSubtract->Release();
        return(hr);
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
    if (rclsid != CLSID_CSumSubtract)
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
