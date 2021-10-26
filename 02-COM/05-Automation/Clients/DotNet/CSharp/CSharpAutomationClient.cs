using System;
using System.Runtime.InteropServices;
using AutomationServerTlbForDotNet;

namespace AutomationClient
{
    public class CSharpAutomationClient
    {
        public static void Main()
        {
            //code
            MyMathClass objCMyMath = new MyMathClass();
            IMyMath objIMyMath = (IMyMath) objCMyMath;

            int num1 = 75;
            int num2 = 25;
            int sum = 0;
            int sub = 0;

            sum = objIMyMath.SumOfTwoIntegers(num1,num2);
            Console.WriteLine($"Sum of {num1} and {num2} is {sum}");

            sub = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
            Console.WriteLine($"Subtraction of {num1} and {num2} is {sub}");
        }
    }
}