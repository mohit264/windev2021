#pragma once

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

// {28B462B0-B9CA-4F73-808B-FE493049AD25}
const CLSID CLSID_MultiplicationDivision = 
{ 0x28b462b0, 0xb9ca, 0x4f73, 0x80, 0x8b, 0xfe, 0x49, 0x30, 0x49, 0xad, 0x25};

// {B802500E-23BD-4E35-BF77-291EEEAB69FE}
const IID IID_IMultiplication = 
{ 0xb802500e, 0x23bd, 0x4e35, 0xbf, 0x77, 0x29, 0x1e, 0xee, 0xab, 0x69, 0xfe };

// {B802500E-23BD-4E35-BF77-291EEEAB69FE}
static const IID IID_IDivision = 
{ 0xb802500e, 0x23bd, 0x4e35, 0xbf, 0x77, 0x29, 0x1e, 0xee, 0xab, 0x69, 0xfe };


