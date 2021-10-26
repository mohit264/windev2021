Imports System.Windows.Forms
Imports AutomationServerTlbForDotNet

Public Class VBAutomationClient 
    Inherits Form
    Public Sub New()
        Dim MyIDispatch As Object
        Dim MyRef As New MyMathClass

        MyIDispatch = MyRef
        Dim Num1 = 175
        Dim Num2 = 125
        Dim Sum = MyIDispatch.SumOfTwoIntegers(Num1, Num2)
        Dim str As String = String.Format("Sum Of {0} and {1} is {2}", Num1, Num2, Sum)
        MsgBox(str)

        Dim ObjSub = MyIDispatch.SubtractionOfTwoIntegers(Num1, Num2)
        str = String.Format("Subtraction Of {0} and {1} is {2}", Num1, Num2, ObjSub)
        MsgBox(str)

        End
    End Sub
    
    <STAThread>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomationClient())
    End Sub
End Class