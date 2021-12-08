//cl /c /EHsc /ZW Hello.cpp
// link Hello.obj /SUBSYSTEM:CONSOLE
//cl /EHsc /ZW Hello.cpp /link vccorlib.lib runtimeobject.lib /SUBSYSTEM:CONSOLE
#include<iostream> // for << insertion operator and endl

using namespace Platform;
using namespace std;

int main(Array<String^>^ args)
{
    //code
    String^ str = "Hello, World !!!";
    wcout<<str->Data()<<endl;

    return(0);
}
