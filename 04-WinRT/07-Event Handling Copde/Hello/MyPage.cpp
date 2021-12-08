#include"pch.h"
#include"MyPage.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::Foundation;

MyPage::MyPage(void)
{
	Window::Current->CoreWindow->KeyDown +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MyPage::OnKeyDown);
	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);

	m_textBlock = ref new TextBlock();
	m_textBlock->Text = "Hello World !!!";
	m_textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI");
	m_textBlock->FontSize = 120;
	m_textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	m_textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	m_textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	m_textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	m_textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;

	grid->Children->Append(m_textBlock);


	Button^ button = ref new Button();
	button->Content = "Ok";
	button->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	button->Width = 400;
	button->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	button->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Times New Roman");
	button->FontSize = 80;
	button->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	button->FontWeight = Windows::UI::Text::FontWeights::Bold;
	button->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
	button->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	button->Click += ref new Windows::UI::Xaml::RoutedEventHandler(this, &MyPage::Button_Click);
	grid->Children->Append(button);

	this->Content = grid;
	
}


void MyPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_textBlock->Text = "A Button Is clicked";
}

void MyPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	m_textBlock->Text = "Key is pressed!";
}