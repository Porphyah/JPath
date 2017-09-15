#include <iostream>
#include "jpath.h"
using namespace std;

int main()
{
	JPath test = JPath::fromFile("test.json");
	if (!test.isLoaded()) return 0;
	
	JObject object = test.getValue<JObject>("/object");
	cout << "/object : " << endl
		<< "\tvalue1 = " << object["value1"].getValue<string>() << endl
		<< "\tvalue2 = " << object["value2"].getValue<string>() << endl
		<< "\tvalue3 = " << object["value3"].getValue<string>() << endl
		<< "\t" << object.getValue<string>("/value4/hidden") << endl;

	cout << endl;

	JArray array = test.getValue<JArray>("/array");
	cout << "/array : " << endl;
	size_t i = 0;
	for (auto& item : array)
		cout << "\t[" << i++ << "] = " << item.getValue<double>() << endl;

	cout << endl;

	cout << "/array2 : " << endl;
	cout << "\t[0] = " << test.getValue<string>("/array2[0]/hidden") << endl;
	cout << "\t[1] = " << test.getValue<string>("/array2[1]/hidden") << endl;

	getchar();

	return 0;
}