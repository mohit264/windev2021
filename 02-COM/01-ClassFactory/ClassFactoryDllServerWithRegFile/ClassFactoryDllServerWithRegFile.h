class ISum : public IUnknown
{
public:
    virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubtract : public IUnknown
{
public:
    virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

// {E9CE19D5-0869-4F9D-BB3F-C31C3310556E}
const CLSID CLSID_SumSubtract = 
{ 0xe9ce19d5, 0x869, 0x4f9d, 0xbb, 0x3f, 0xc3, 0x1c, 0x33, 0x10, 0x55, 0x6e };

// {BF3E71FF-97AE-492D-A3DD-DDFC2A261469}
const IID IID_ISum = 
{ 0xbf3e71ff, 0x97ae, 0x492d, 0xa3, 0xdd, 0xdd, 0xfc, 0x2a, 0x26, 0x14, 0x69 };

// {6C13746F-9F32-4CA4-A7E8-640506D36406}
const IID IID_ISubtract =
{ 0x6c13746f, 0x9f32, 0x4ca4, 0xa7, 0xe8, 0x64, 0x5, 0x6, 0xd3, 0x64, 0x6 };



