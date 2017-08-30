#ifndef __EXSTRING_H__
#define __EXSTRING_H__

#include <string>
#include <sstream>
#include <vector>

class ExString
{
public:
	static const size_t CountAll = 0;

	inline static std::vector<std::string> split(const std::string& source,
		std::vector<std::string> separators, const size_t count = 0, bool ignoreEmpty = true);
	inline static std::string remove(const std::string& source, const std::string& target);
	inline static std::string replace(const std::string& source,
		const std::string& oldValue, const std::string& newValue);
	inline static bool startsWith(const std::string& source, const std::string& target);
	inline static bool endsWith(const std::string& source, const std::string& target);
	inline static bool contains(const std::string& source, const std::string& target);

	inline static int32_t toInt32(const std::string& source);
	inline static std::string toString(const int& source);
};

#endif // __EXSTRING_H__