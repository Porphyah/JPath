#include <iostream>
#include "jpath.h"
using namespace std;

int main()
{
	JPath test = JPath("test.json");
	if (!test.isLoaded()) return 0;
	
	JObject object = test.getValue<JObject>("/object");
	cout << "/object : " << endl
		<< "\tvalue1 = " << object["value1"].getValue<string>() << endl
		<< "\tvalue2 = " << object["value2"].getValue<string>() << endl
		<< "\tvalue3 = " << object["value3"].getValue<string>() << endl
		<< "\t" << object["value4"].getValue<string>("/hidden") << endl;

	cout << endl;

	JArray array = test.getValue<JArray>("/array");
	cout << "/array : " << endl;
	for (size_t i = 0; i < array.size(); i++)
		cout << "\t[" << i << "] = " << array[i].getValue<double>() << endl;

	return 0;
}