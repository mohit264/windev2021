#pragma once

class ISum : public IUnknown
{
    public:
        HRESULT virtual __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
    public:
        HRESULT virtual __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

class IMultiplication: public IUnknown
{
    public:
        virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision: public IUnknown
{
    public:
        virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// {A8B15FAC-4385-48C3-960A-0EFC65F75E7E}
const CLSID CLSID_CSumSubtract = 
{ 0xa8b15fac, 0x4385, 0x48c3, 0x96, 0xa, 0xe, 0xfc, 0x65, 0xf7, 0x5e, 0x7e };

// {F73DABAC-0B21-4C61-A271-7ABAD14BEB15}
const IID IID_ISum =
{ 0xf73dabac, 0xb21, 0x4c61, 0xa2, 0x71, 0x7a, 0xba, 0xd1, 0x4b, 0xeb, 0x15 };

// {BA857F55-6D85-4FA4-81B5-863F47EBA121}
const IID IID_ISubtract = 
{ 0xba857f55, 0x6d85, 0x4fa4, 0x81, 0xb5, 0x86, 0x3f, 0x47, 0xeb, 0xa1, 0x21 };

// {B802500E-23BD-4E35-BF77-291EEEAB69FE}
const IID IID_IMultiplication = 
{ 0xb802500e, 0x23bd, 0x4e35, 0xbf, 0x77, 0x29, 0x1e, 0xee, 0xab, 0x69, 0xfe };

// {B2EDAAE8-2A01-43DE-857A-7A4AE325F830}
static const IID IID_IDivision = 
{ 0xb2edaae8, 0x2a01, 0x43de, 0x85, 0x7a, 0x7a, 0x4a, 0xe3, 0x25, 0xf8, 0x30 };

