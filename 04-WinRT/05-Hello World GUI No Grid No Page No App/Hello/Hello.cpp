#include"pch.h"
#include"Hello.h"
#include"MyPage.h"

using namespace Platform;

//int Main(Array<String^>^ args)
//{
//	//code
//	Application::Start(ref new ApplicationInitializationCallback([](ApplicationInitializationCallbackParams^ params)
//		{
//			//code
//			App^ app = ref new App();
//		}));
//
//	return(0);
//}
void MyCallbackMethod(ApplicationInitializationCallbackParams^ params)
{
	//code
	App^ app = ref new App();
}

int main(Array<String^>^ args)
{
	// code
	ApplicationInitializationCallback^ callback = ref new 
		ApplicationInitializationCallback(MyCallbackMethod);
	Application::Start(callback);
	return(0);
}

App::App(void)
{
	//code
}

void App::OnLaunched(LaunchActivatedEventArgs^ args)
{
	//code
	MyPage^ page = ref new MyPage();
	Window::Current->Content = page;
	Window::Current->Activate();
}
