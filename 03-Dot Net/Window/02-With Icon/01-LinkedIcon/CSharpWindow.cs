using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow : Form
{
    public CSharpWindow()
    {
        //code
        //caption of window
        Icon = new Icon("Merc.ico");
        Text = "C# Window";
        Width = 800;
        Height = 600;
        BackColor = Color.Black;
        ResizeRedraw = true;


        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);
    }

    public void MyKeyDown(object sender, KeyEventArgs e)
    {
        //code
        MessageBox.Show("Some Key of Keyboard is pressed!");
    }

    public void MyMouseDown(object sender, MouseEventArgs e)
    {
        //code
        MessageBox.Show("Some button of Mouse is Clicked!");
    }

    protected override void OnPaint(PaintEventArgs pea)
    {
        //code
        Graphics graphics = pea.Graphics;
        StringFormat strFomat = new StringFormat();
        strFomat.Alignment = StringAlignment.Center;
        strFomat.LineAlignment = StringAlignment.Center;

        string str = "Hello, World!!!";
        graphics.DrawString(str, Font, new SolidBrush(System.Drawing.Color.Green), 
        ClientRectangle, strFomat);
    }

    public static void Main()
    {
        CSharpWindow obj = new CSharpWindow();
        Application.Run(obj);
    }
}