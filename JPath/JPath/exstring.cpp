#include "exstring.h"
using namespace std;

vector<string> ExString::split(const string& source,
	vector<string> separators, const size_t count, bool ignoreEmpty)
{
	string::size_type pos1, pos2;
	vector<string> result;
	string current_separator;

	for (size_t i = 0; i < separators.size(); i++)
	{
		size_t temp = source.find(separators[i]);
		if (i == 0 || temp < pos2)
		{
			pos2 = temp;
			current_separator = separators[i];
		}
	}
	pos1 = 0;
	while (string::npos != pos2)
	{
		if (!ignoreEmpty || source.substr(pos1, pos2 - pos1) != "")
			result.push_back(source.substr(pos1, pos2 - pos1));

		pos1 = pos2 + current_separator.size();
		for (size_t i = 0; i < separators.size(); i++)
		{
			size_t temp = source.find(separators[i], pos1);
			if (i == 0 || temp < pos2)
			{
				pos2 = temp;
				current_separator = separators[i];
			}
		}
	}
	if (pos1 != source.length())
		result.push_back(source.substr(pos1));

	return result;
}

string ExString::remove(const string& source, const string& target)
{
	string result(source);
	for (string::size_type pos = result.find(target);
		pos != string::npos; pos = result.find(target))
		result.erase(pos, target.size());
	return result;
}

string ExString::replace(const string& source, const string& oldValue, const string& newValue)
{
	string result(source);
	for (string::size_type pos = result.find(oldValue);
		pos != string::npos; pos = result.find(oldValue))
		result.replace(pos, oldValue.size(), newValue);
	return result;
}

bool ExString::startsWith(const string & source, const string & target)
{
	if (target.size() > source.size()) return false;
	return source.substr(0, target.size()) == target;
}

bool ExString::endsWith(const string & source, const string & target)
{
	if (target.size() > source.size()) return false;
	return source.substr(source.size() - target.size(), target.size()) == target;
}

bool ExString::contains(const string & source, const string & target)
{
	return source.find(target) != string::npos;
}

inline int32_t ExString::toInt32(const string & source)
{
	return atoi(source.data());
}

inline string ExString::toString(const int & source)
{
	stringstream ss;
	ss << source;
	return ss.str();
}


