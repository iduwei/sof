// classloader.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include "TestClass.h"
#include "ObjectLoader.h"
#include "Object.h"
#include "ObjectLoadingException.h"

#include <iostream>

using namespace std;
using namespace sof::classloading;

int main(int argc, char* argv[])
{
	typedef ObjectLoader<BaseTestClass> OL;	
	
	try
	{
		BaseTestClass* obj = OL::loadObject( "TestClass" );
		string text = ( ( TestClass* ) obj)->getText();
		cout << "Text:" << text << endl;
	}
	catch( ObjectLoadingException &exc )
	{
		cout << "exception occured: " << exc.what() << endl;
	}
	return 0;
}

