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
using namespace Windows::UI::Xaml::Controls;// For Grid, TextBlock
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;// SolidColorBrush
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Text; // FontStyle

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	
	InitializeComponent();
	//My Code
	//^--> reference counted  pointer so you don't need to do AddRef and Release
	// WinRT will take care of it
	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);

	TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello World !!!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;


	grid->Children->Append(textBlock);
	this->Content = grid;
}
