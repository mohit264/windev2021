#pragma once
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Core;

ref class MyPage sealed : Page
{
public:
	MyPage(void);
	void OnKeyDown(CoreWindow^, KeyEventArgs^);
	void Button_Click(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^);
private:
	TextBlock^ m_textBlock;
	//void OnClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
};
