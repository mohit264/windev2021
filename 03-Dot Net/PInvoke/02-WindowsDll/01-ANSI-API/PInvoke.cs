using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    //code
    [DllImport("user32.dll")]
    // handle in Win32 is int in .net
    public static extern int MessageBoxA(int hwnd, string message, string caption, int flag);

    public static void Main()
    {
        //code
        MessageBoxA(0, "MessageBox() As Ansi API!!", "Win32 Ansi API", 0);X
    }
}