#include"pch.h"
#include"MyPage.h"
using namespace Windows::UI::Xaml::Media;

MyPage::MyPage(void)
{
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
