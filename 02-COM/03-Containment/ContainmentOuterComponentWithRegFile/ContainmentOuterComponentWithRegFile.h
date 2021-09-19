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

// {BE25C712-A1A3-4A65-B58C-918950712421}
const CLSID CLSID_SumSubtract =
{ 0xbe25c712, 0xa1a3, 0x4a65, 0xb5, 0x8c, 0x91, 0x89, 0x50, 0x71, 0x24, 0x21 };

// {F49B5A6A-A162-4591-869C-999BFA3CB4A3}
const IID IID_ISum =
{ 0xf49b5a6a, 0xa162, 0x4591, 0x86, 0x9c, 0x99, 0x9b, 0xfa, 0x3c, 0xb4, 0xa3 };

// {55BF0D3A-D67E-4C73-A2B2-7932EFADB6AF}
const IID IID_ISubtract =
{ 0x55bf0d3a, 0xd67e, 0x4c73, 0xa2, 0xb2, 0x79, 0x32, 0xef, 0xad, 0xb6, 0xaf };
