using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    //code
    // This will give chinese message
    //[DllImport("user32.dll")]
    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    // handle in Win32 is int in .net
    public static extern int MessageBoxW(int hwnd, string message, string caption, int flag);

    public static void Main()
    {
        //code
         
        MessageBoxW(0, "MessageBox() As Unicode API!!", "Win32 Ansi API", 0);
    }
}