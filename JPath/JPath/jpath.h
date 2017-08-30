#ifndef __JPATH_H__
#define __JPATH_H__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <exception>
#include <document.h>
#include <pointer.h>
#include <stdlib.h>
#include "exstring.h"
#include "exstring.cpp"

class JPath;

class JNode
{
public:
	JNode() = default;
	JNode(const std::string& path, JPath* parent);

	inline std::string getPath() { return m_path; }
	inline std::string getName() { return m_name; }
	inline JNode& operator =(JNode& origin) { return origin; }
	inline operator std::string() { return getName(); }

	template<typename T> bool hasValue(const std::string& relative_path = "");
	template<typename T> T getValue(const std::string& relative_path = "");

protected:
	std::string m_path;
	std::string m_name;
	JPath* m_parent;
};

class JArray
{
public:
	JArray() = default;
	JArray(const std::string& path, JPath* parent);
	JNode operator [](size_t index);
	void insert(size_t index, std::string path);
	size_t size();

private:
	std::map<size_t, std::string> m_map;
	std::string m_path;
	std::string m_name;
	JPath* m_parent;
};

class JObject
{
public:
	JObject() = default;
	JObject(const std::string& path, JPath* parent);
	JNode operator [](std::string index);
	void insert(std::string path);
	size_t size();

private:
	std::vector<std::string> m_vec;
	std::string m_path;
	std::string m_name;
	JPath* m_parent;
};

class JPath
{
public:
	JPath(const std::string& file);
	inline bool isLoaded() { return m_loaded; }

	template<typename T> bool hasValue(const std::string& path);
	template<typename T> T getValue(const std::string& path);

private:
	rapidjson::Document m_document;
	bool m_loaded = false;

	bool loadFile(const std::string& file_name, char** buffer);
};

#endif // __JPATH_H__