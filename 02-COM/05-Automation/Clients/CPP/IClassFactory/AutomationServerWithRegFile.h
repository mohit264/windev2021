class IMyMath:public IDispatch
{
    public:
        virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
        virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {9AEA1E50-D8C7-4353-9AA7-B91CB174D9AC}
const CLSID CLSID_MyMath = 
{ 0x9aea1e50, 0xd8c7, 0x4353, 0x9a, 0xa7, 0xb9, 0x1c, 0xb1, 0x74, 0xd9, 0xac };

// {BAC91261-3C2F-4CFB-9AFB-F823572F838F}
const IID IID_IMyMath = 
{ 0xbac91261, 0x3c2f, 0x4cfb, 0x9a, 0xfb, 0xf8, 0x23, 0x57, 0x2f, 0x83, 0x8f };

