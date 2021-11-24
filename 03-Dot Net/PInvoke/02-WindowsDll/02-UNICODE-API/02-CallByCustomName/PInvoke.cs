using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    //code
    // This will give chinese message [DllImport("user32.dll")]
    //So adding Unicode CharSet
    [DllImport("user32.dll", EntryPoint = "MessageBoxW", CharSet = CharSet.Unicode)]
    // handle in Win32 is int in .net
    public static extern int MyMessageBox(int hwnd, string message, string caption, int flag);

    public static void Main()
    {
        //code
         
        MyMessageBox(0, "My MessageBox() As Unicode API!!", "Win32 Unicode API", 0);
    }
}