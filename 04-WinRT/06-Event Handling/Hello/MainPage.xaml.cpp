//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Hello;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	Window::Current->CoreWindow->KeyDown += 
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MainPage::OnKeyDown);
}


void Hello::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//code
	textBlock->Text = "A Button Is Clicked!!";
}
void Hello::MainPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	//code
	textBlock->Text = "A Key Is Pressed";
}