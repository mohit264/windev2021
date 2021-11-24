//Every .NET dll internally is dual interfacing OLE Automation Server 
// csc /t:Library DotNetServer.cs --> This will create DotNetServer.dll
// regasm DotNetServer.dll /tlb in administrator mode
using System;

public class DotNetServer
{
    public int SumOfTwoIntegers(int num1, int num2)
    {
        //code
        return num1 + num2;
    }

    public int SubtractionOfTwoIntegers(int num1, int num2)
    {
        return num1 - num2;
    }
}
