#pragma once
class IMultiplication : public IUnknown
{
public:
    virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision : public IUnknown
{
public:
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;
};

// {4EEF351C-5BFB-4330-8CBB-A816603B050D}

const CLSID CLSID_MultiplicationDivision = 
{ 0x4eef351c, 0x5bfb, 0x4330, 0x8c, 0xbb, 0xa8, 0x16, 0x60, 0x3b, 0x5, 0xd };

// {85FA30CE-109E-433C-9B9C-EA852C1225ED}
const IID IID_IMultiplication = 
{ 0x85fa30ce, 0x109e, 0x433c, 0x9b, 0x9c, 0xea, 0x85, 0x2c, 0x12, 0x25, 0xed };

// {80A43D8C-939B-48EE-A65A-5916CF8CF22B}
const IID IID_IDivision =
{ 0x80a43d8c, 0x939b, 0x48ee, 0xa6, 0x5a, 0x59, 0x16, 0xcf, 0x8c, 0xf2, 0x2b };

