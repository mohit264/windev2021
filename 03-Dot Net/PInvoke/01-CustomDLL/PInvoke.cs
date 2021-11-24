using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    //code
    [DllImport("MyDllServer.dll")]
    public static extern int SumOfTwoIntergers(int n1, int n2);

    public static void Main()
    {
        //code
        int iNum1 = 155;
        int iNum2 = 145;

        int iNum3 = SumOfTwoIntergers(iNum1, iNum2);

        Console.WriteLine($"Sum of {iNum1} and {iNum2} is {iNum3}");
    }
}