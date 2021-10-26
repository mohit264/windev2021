#pragma once

#undef INTERFACE
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch)
{
    // Internally STDMETHOD means a pointer to a function returning HRESULT
    // Function with HRESULT return value
    // If the function is having parameters then first parameter should be THIS_
    STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;    
    //Function with Non-HRESULT return value
    // Function does not take any input parameters
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    STDMETHOD(GetTypeInfoCount)(THIS_ UINT*) PURE;
    STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo**) PURE;
    STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;
    STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO* 
                , UINT*) PURE;

    STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int *) PURE;
    STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int *) PURE;
};


// {9AEA1E50-D8C7-4353-9AA7-B91CB174D9AC}
const CLSID CLSID_MyMath = 
{ 0x9aea1e50, 0xd8c7, 0x4353, 0x9a, 0xa7, 0xb9, 0x1c, 0xb1, 0x74, 0xd9, 0xac };

// {BAC91261-3C2F-4CFB-9AFB-F823572F838F}
const IID IID_IMyMath = 
{ 0xbac91261, 0x3c2f, 0x4cfb, 0x9a, 0xfb, 0xf8, 0x23, 0x57, 0x2f, 0x83, 0x8f };

