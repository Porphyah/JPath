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
#include <writer.h>
#include <stringbuffer.h>
#include <stdlib.h>
#include "exstring.h"
#include "exstring.cpp"

class JPath;
class JArray;
class JObject;

class JNode
{
public:
	JNode() = default;
	JNode(const std::string& path, JPath* parent);

	inline std::string getPath() const { return m_path; }
	inline std::string getName() const { return m_name; }
	inline JNode& operator =(JNode& origin) { return origin; }
	inline bool operator ==(const JNode& that) const
	{
		return this->m_parent == that.m_parent &&
			this->m_path == that.m_path;
	}
	inline bool operator !=(const JNode& that) const
	{
		return this->m_parent != that.m_parent ||
			this->m_path != that.m_path;
	}
	inline operator std::string() { return m_path; }

	std::string getJsonStr(const std::string& relative_path = "");

	template<typename T> bool hasValue(const std::string& relative_path = "");
	template<typename T> T getValue(const std::string& relative_path = "");
	template<typename T> void setValue(const std::string& relative_path, T value);

protected:
	std::string m_path;
	std::string m_name;
	JPath* m_parent;
};

struct JNodePtr
{
private:
	JPath* m_parent;
	std::string m_path;
public:
	JNodePtr(const std::string& path, JPath* parent) : m_path(path), m_parent(parent) { }
	JNode& operator->() const { return JNode(m_path, m_parent); }
};

template<typename JNodeType>
struct JNodeIterator : public std::iterator<std::random_access_iterator_tag, JNodeType>
{
public:
	JNodeIterator(const JNodeType* parent, const size_t index = 0);

	JNodeIterator<JNodeType>& operator=(const JNodeIterator<JNodeType> & it);

	JNodeIterator<JNodeType>& operator++();
	JNodeIterator<JNodeType>& operator--();
	JNodeIterator<JNodeType>  operator++(int);
	JNodeIterator<JNodeType>  operator--(int);

	JNodeIterator<JNodeType> operator+(size_t n) const;
	JNodeIterator<JNodeType> operator-(size_t n) const;

	JNodeIterator<JNodeType>& operator+=(size_t n);
	JNodeIterator<JNodeType>& operator-=(size_t n);

	bool operator==(const JNodeIterator<JNodeType> that) const;
	bool operator!=(const JNodeIterator<JNodeType> that) const;
	bool operator<=(const JNodeIterator<JNodeType> that) const;
	bool operator>=(const JNodeIterator<JNodeType> that) const;
	bool operator< (const JNodeIterator<JNodeType> that) const;
	bool operator> (const JNodeIterator<JNodeType> that) const;

	JNode operator*() const;
	JNodePtr operator->() const;
	size_t operator-(const JNodeIterator<JNodeType> that) const;

private:
	const JNodeType* m_parent;
	size_t m_currentIndex;
};

template struct JNodeIterator<JArray>;
template struct JNodeIterator<JObject>;

class JArray : public JNode
{
public:
	friend struct JNodeIterator<JArray>;

	JArray() = default;
	JArray(const std::string& path, JPath* parent);

	JNode operator [](const size_t index) const;
	template<typename T> T operator [](const size_t index) const;

	template<typename T> void setValue(T value);

	void insert(size_t index, std::string path);
	size_t size() const;
	inline JNodeIterator<JArray> begin() const { return JNodeIterator<JArray>(this, 0); }
	inline JNodeIterator<JArray> end() const { return JNodeIterator<JArray>(this, size()); }

private:
	std::map<size_t, std::string> m_map;
};

class JObject : public JNode
{
public:
	friend struct JNodeIterator<JObject>;

	JObject() = default;
	JObject(const std::string& path, JPath* parent);

	JNode operator [](const size_t index) const;
	JNode operator [](const std::string& index) const;
	template<typename T> T operator [](const std::string& index) const;

	void insert(std::string path);
	size_t size() const;
	inline JNodeIterator<JObject> begin() const { return JNodeIterator<JObject>(this, 0); }
	inline JNodeIterator<JObject> end() const { return JNodeIterator<JObject>(this, size()); }

private:
	std::vector<std::string> m_vec;
};

struct IJsonSerializable
{
	virtual void Serialize(const std::string& json) = 0;
	virtual std::string Deserialize() = 0;
};

class JPath
{
public:
	JPath() { }
	static JPath fromFile(const std::string& file);
	static JPath fromStr(const std::string& str);

	inline bool isLoaded() { return m_loaded; }

	template<typename T> bool hasValue(const std::string& path = "");
	template<typename T> T getValue(const std::string& path = "");
	template<typename T> void setValue(const std::string& path, T value);

	std::string getJsonStr(const std::string& path = "");

private:
	rapidjson::Document m_document;
	bool m_loaded = false;

	bool loadFile(const std::string& file_name, char** buffer);
};

#endif // __JPATH_H__