#pragma once
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Xaml;

ref class App sealed : Application
{
public:
	App(void);
	virtual void OnLaunched(LaunchActivatedEventArgs^ args) override;

};