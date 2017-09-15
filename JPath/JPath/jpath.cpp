#define _CRT_SECURE_NO_WARNINGS
#include "jpath.h"
using namespace std;
using namespace rapidjson;

JNode::JNode(const std::string& path, JPath* parent) :
	m_name(*(ExString::split(path, { "/" }).end() - 1)),
	m_path(string(path)),
	m_parent(parent)
{ }

JPath JPath::fromFile(const std::string & file)
{
	JPath result = JPath();
	char* jsonStr;
	if (!result.loadFile(file, &jsonStr))
	{
		cout << "JPath | Cannot open json file!" << endl;
		throw invalid_argument("Cannot open json file");
	}

	result.m_document.Parse(jsonStr);
	result.m_loaded = true;
	return result;
}
JPath JPath::fromStr(const std::string & str)
{
	JPath result = JPath();
	result.m_document.Parse(str.data());
	result.m_loaded = true;
	return result;
}

std::string JPath::getJsonStr(const std::string & path)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	Pointer(path.data()).Get(this->m_document)->Accept(writer);
	return string(buffer.GetString());
}

bool JPath::loadFile(const string & file_name, char ** buffer)
{
	FILE* file = fopen(file_name.data(), "rb");
	if (file != NULL)
	{
		uint32_t file_size;
		fseek(file, 0, SEEK_END);
		file_size = ftell(file);
		fseek(file, 0, SEEK_SET);
		*buffer = (char*)malloc(file_size + 1);
		fread(*buffer, 1, file_size, file);
		(*buffer)[file_size] = 0; //add terminating NULL
		fclose(file);
		return true;
	}
	else
		return false;
}

template<> bool JPath::hasValue<void>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return true;
	return Pointer(temp.data()).Get(this->m_document)->IsNull();
}
template<> bool JPath::hasValue<bool>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsBool();
}
template<> bool JPath::hasValue<uint32_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsUint();
}
template<> bool JPath::hasValue<int32_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsInt();
}
template<> bool JPath::hasValue<int64_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsInt64();
}
template<> bool JPath::hasValue<uint64_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsUint64();
}
template<> bool JPath::hasValue<float>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsFloat();
}
template<> bool JPath::hasValue<double>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsDouble();
}
template<> bool JPath::hasValue<string>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsString();
}
template<> bool JPath::hasValue<JArray>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsArray();
}
template<> bool JPath::hasValue<JObject>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	if (Pointer(temp.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(temp.data()).Get(this->m_document)->IsObject();
}

template<> void JPath::getValue<void>(const std::string & path)
{
	return;
}
template<> bool JPath::getValue<bool>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetBool();
}
template<> uint32_t JPath::getValue<uint32_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetUint();
}
template<> int32_t JPath::getValue<int32_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetInt();
}
template<> int64_t JPath::getValue<int64_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetInt64();
}
template<> uint64_t JPath::getValue<uint64_t>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetUint64();
}
template<> float JPath::getValue<float>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetFloat();
}
template<> double JPath::getValue<double>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetDouble();
}
template<> string JPath::getValue<string>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	return Pointer(temp.data()).Get(this->m_document)->GetString();
}
template<> JArray JPath::getValue<JArray>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	JArray result = JArray(temp, this);
	Value::Array source = Pointer(temp.data()).Get(this->m_document)->GetArray();
	stringstream ss;
	for (SizeType i = 0; i < source.Size(); i++)
	{
		ss << path << "/" << i;
		result.insert(i, ss.str());
		ss.str("");
	}
	return result;
}
template<> JObject JPath::getValue<JObject>(const std::string & path)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	JObject result = JObject(temp, this);
	Value::Object source = Pointer(temp.data()).Get(this->m_document)->GetObject();
	stringstream ss;
	for (auto& object : source)
	{
		ss << path << "/" << object.name.GetString();
		result.insert(ss.str());
		ss.str("");
	}
	return result;
}

template<> void JPath::setValue<bool>(const std::string & path, bool value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<uint32_t>(const std::string & path, uint32_t value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<int32_t>(const std::string & path, int32_t value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<int64_t>(const std::string & path, int64_t value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<uint64_t>(const std::string & path, uint64_t value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<float>(const std::string & path, float value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<double>(const std::string & path, double value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value);
}
template<> void JPath::setValue<string>(const std::string & path, string value)
{
	string temp = ExString::replace(ExString::replace(path, "[", "/"), "]", "");
	Pointer(temp.data()).Set(this->m_document, value.data());
}

template<> bool JNode::hasValue<void>(const string& relative_path)
{
	return m_parent->hasValue<void>(m_path + relative_path);
}
template<> bool JNode::hasValue<bool>(const string& relative_path)
{
	return m_parent->hasValue<bool>(m_path + relative_path);
}
template<> bool JNode::hasValue<uint32_t>(const string& relative_path)
{
	return m_parent->hasValue<uint32_t>(m_path + relative_path);
}
template<> bool JNode::hasValue<int32_t>(const string& relative_path)
{
	return m_parent->hasValue<int32_t>(m_path + relative_path);
}
template<> bool JNode::hasValue<uint64_t>(const string& relative_path)
{
	return m_parent->hasValue<uint64_t>(m_path + relative_path);
}
template<> bool JNode::hasValue<int64_t>(const string& relative_path)
{
	return m_parent->hasValue<int64_t>(m_path + relative_path);
}
template<> bool JNode::hasValue<float>(const string& relative_path)
{
	return m_parent->hasValue<float>(m_path + relative_path);
}
template<> bool JNode::hasValue<double>(const string& relative_path)
{
	return m_parent->hasValue<double>(m_path + relative_path);
}
template<> bool JNode::hasValue<string>(const string& relative_path)
{
	return m_parent->hasValue<string>(m_path + relative_path);
}
template<> bool JNode::hasValue<JArray>(const string& relative_path)
{
	return m_parent->hasValue<JArray>(m_path + relative_path);
}
template<> bool JNode::hasValue<JObject>(const string& relative_path)
{
	return m_parent->hasValue<JObject>(m_path + relative_path);
}

template<> void JNode::getValue<void>(const string& relative_path)
{
	return;
}
template<> bool JNode::getValue<bool>(const string& relative_path)
{
	return m_parent->getValue<bool>(m_path + relative_path);
}
template<> uint32_t JNode::getValue<uint32_t>(const string& relative_path)
{
	return m_parent->getValue<uint32_t>(m_path + relative_path);
}
template<> int32_t JNode::getValue<int32_t>(const string& relative_path)
{
	return m_parent->getValue<int32_t>(m_path + relative_path);
}
template<> uint64_t JNode::getValue<uint64_t>(const string& relative_path)
{
	return m_parent->getValue<uint64_t>(m_path + relative_path);
}
template<> int64_t JNode::getValue<int64_t>(const string& relative_path)
{
	return m_parent->getValue<int64_t>(m_path + relative_path);
}
template<> float JNode::getValue<float>(const string& relative_path)
{
	return m_parent->getValue<float>(m_path + relative_path);
}
template<> double JNode::getValue<double>(const string& relative_path)
{
	return m_parent->getValue<double>(m_path + relative_path);
}
template<> string JNode::getValue<string>(const string& relative_path)
{
	return m_parent->getValue<string>(m_path + relative_path);
}
template<> JArray JNode::getValue<JArray>(const string& relative_path)
{
	return m_parent->getValue<JArray>(m_path + relative_path);
}
template<> JObject JNode::getValue<JObject>(const string& relative_path)
{
	return m_parent->getValue<JObject>(m_path + relative_path);
}

template<> void JNode::setValue<bool>(const std::string & relative_path, bool value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<uint32_t>(const std::string & relative_path, uint32_t value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<int32_t>(const std::string & relative_path, int32_t value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<int64_t>(const std::string & relative_path, int64_t value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<uint64_t>(const std::string & relative_path, uint64_t value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<float>(const std::string & relative_path, float value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<double>(const std::string & relative_path, double value)
{
	m_parent->setValue(m_path + relative_path, value);
}
template<> void JNode::setValue<string>(const std::string & relative_path, string value)
{
	m_parent->setValue(m_path + relative_path, value);
}

std::string JNode::getJsonStr(const std::string & relative_path)
{
	return m_parent->getJsonStr(m_path + relative_path);
}

JArray::JArray(const std::string & path, JPath * parent) :
	JNode(path, parent),
	m_map(map<size_t, string>())
{ }
JNode JArray::operator[](const size_t index) const
{
	if (!m_map.count(index))
	{
		stringstream ss;
		ss << "JPath | Cannot find index of " << index << " in node : " << m_path << "!" << endl;
		throw out_of_range(ss.str().data());
	}
	return JNode(m_map.find(index)->second, m_parent);
}
template<typename T> void JArray::setValue(T value)
{
	size_t index = this->size();
	stringstream ss;
	ss << m_path << "/" << index;

	m_parent->setValue<T>(ss.str(), value);
	m_map.insert(pair<size_t, string>(index, ss.str()));
}
void JArray::insert(size_t index, std::string path)
{
	m_map.insert(pair<size_t, string>(index, path));
}
size_t JArray::size() const
{
	return m_map.size();
}

template<> void JArray::operator[]<void>(const size_t index) const
{
	return;
}
template<> bool JArray::operator[]<bool>(const size_t index) const
{
	return (*this)[index].getValue<bool>();
}
template<> uint32_t JArray::operator[]<uint32_t>(const size_t index) const
{
	return (*this)[index].getValue<uint32_t>();
}
template<> int32_t JArray::operator[]<int32_t>(const size_t index) const
{
	return (*this)[index].getValue<int32_t>();
}
template<> uint64_t JArray::operator[]<uint64_t>(const size_t index) const
{
	return (*this)[index].getValue<uint64_t>();
}
template<> int64_t JArray::operator[]<int64_t>(const size_t index) const
{
	return (*this)[index].getValue<int64_t>();
}
template<> float JArray::operator[]<float>(const size_t index) const
{
	return (*this)[index].getValue<float>();
}
template<> double JArray::operator[]<double>(const size_t index) const
{
	return (*this)[index].getValue<double>();
}
template<> string JArray::operator[]<string>(const size_t index) const
{
	return (*this)[index].getValue<string>();
}
template<> JArray JArray::operator[]<JArray>(const size_t index) const
{
	return (*this)[index].getValue<JArray>();
}
template<> JObject JArray::operator[]<JObject>(const size_t index) const
{
	return (*this)[index].getValue<JObject>();
}

JObject::JObject(const std::string & path, JPath * parent) :
	JNode(path, parent),
	m_vec(vector<string>())
{ }
JNode JObject::operator[](const size_t index) const
{
	if (index < 0 || index >= m_vec.size())
	{
		stringstream ss;
		ss << "JPath | Cannot find index of " << index << " in node : " << m_path << "!" << endl;
		throw out_of_range(ss.str().data());
	}
	return JNode(m_vec[index], m_parent);
}
JNode JObject::operator[](const string& index) const
{
	for (auto& item : m_vec)
		if (*(ExString::split(item, { "/" }).end() - 1) == index) return JNode(item, m_parent);
	stringstream ss;
	ss << "JPath | Cannot find index of " << index << " in node : " << m_path << "!" << endl;
	throw out_of_range(ss.str().data());
}
void JObject::insert(std::string path)
{
	m_vec.push_back(path);
}
size_t JObject::size() const
{
	return m_vec.size();
}

template<> void JObject::operator[]<void>(const string& index) const
{
	return;
}
template<> bool JObject::operator[]<bool>(const string& index) const
{
	return (*this)[index].getValue<bool>();
}
template<> uint32_t JObject::operator[]<uint32_t>(const string& index) const
{
	return (*this)[index].getValue<uint32_t>();
}
template<> int32_t JObject::operator[]<int32_t>(const string& index) const
{
	return (*this)[index].getValue<int32_t>();
}
template<> uint64_t JObject::operator[]<uint64_t>(const string& index) const
{
	return (*this)[index].getValue<uint64_t>();
}
template<> int64_t JObject::operator[]<int64_t>(const string& index) const
{
	return (*this)[index].getValue<int64_t>();
}
template<> float JObject::operator[]<float>(const string& index) const
{
	return (*this)[index].getValue<float>();
}
template<> double JObject::operator[]<double>(const string& index) const
{
	return (*this)[index].getValue<double>();
}
template<> string JObject::operator[]<string>(const string& index) const
{
	return (*this)[index].getValue<string>();
}
template<> JArray JObject::operator[]<JArray>(const string& index) const
{
	return (*this)[index].getValue<JArray>();
}
template<> JObject JObject::operator[]<JObject>(const string& index) const
{
	return (*this)[index].getValue<JObject>();
}

template<typename JNodeType> JNodeIterator<JNodeType>::JNodeIterator(const JNodeType* parent, const size_t index) :
	m_parent(parent), m_currentIndex(index)
{ }

template<typename JNodeType> JNodeIterator<JNodeType> & JNodeIterator<JNodeType>::operator=(const JNodeIterator<JNodeType> & it)
{
	m_parent = it.m_parent;
	m_currentIndex = it.m_currentIndex;
	return *this;
}
template<typename JNodeType> JNodeIterator<JNodeType> & JNodeIterator<JNodeType>::operator++()
{
	m_currentIndex++;
	return *this;
}
template<typename JNodeType> JNodeIterator<JNodeType> & JNodeIterator<JNodeType>::operator--()
{
	m_currentIndex--;
	return *this;
}
template<typename JNodeType> JNodeIterator<JNodeType> JNodeIterator<JNodeType>::operator++(int)
{
	return JNodeIterator(m_parent, m_currentIndex++);
}
template<typename JNodeType> JNodeIterator<JNodeType> JNodeIterator<JNodeType>::operator--(int)
{
	return JNodeIterator(m_parent, m_currentIndex--);
}

template<typename JNodeType> JNodeIterator<JNodeType> JNodeIterator<JNodeType>::operator+(size_t n) const
{
	return JNodeIterator(m_parent, m_currentIndex + n);
}
template<typename JNodeType> JNodeIterator<JNodeType> JNodeIterator<JNodeType>::operator-(size_t n) const
{
	return JNodeIterator(m_parent, m_currentIndex - n);
}
template<typename JNodeType> JNodeIterator<JNodeType> & JNodeIterator<JNodeType>::operator+=(size_t n)
{
	m_currentIndex += n;
	return *this;
}
template<typename JNodeType> JNodeIterator<JNodeType> & JNodeIterator<JNodeType>::operator-=(size_t n)
{
	m_currentIndex -= n;
	return *this;
}

template<typename JNodeType> bool JNodeIterator<JNodeType>::operator==(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent == *m_parent &&
		that.m_currentIndex == this->m_currentIndex;
}
template<typename JNodeType> bool JNodeIterator<JNodeType>::operator!=(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent != *m_parent ||
		that.m_currentIndex != this->m_currentIndex;
}
template<typename JNodeType> bool JNodeIterator<JNodeType>::operator<=(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent == *m_parent &&
		this->m_currentIndex <= that.m_currentIndex;
}
template<typename JNodeType> bool JNodeIterator<JNodeType>::operator>=(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent == *m_parent &&
		this->m_currentIndex >= that.m_currentIndex;
}
template<typename JNodeType> bool JNodeIterator<JNodeType>::operator<(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent == *m_parent &&
		this->m_currentIndex < that.m_currentIndex;
}
template<typename JNodeType> bool JNodeIterator<JNodeType>::operator>(const JNodeIterator<JNodeType> that) const
{
	return *that.m_parent == *m_parent &&
		this->m_currentIndex > that.m_currentIndex;
}

template<> JNode JNodeIterator<JArray>::operator*() const
{
	return (*m_parent)[m_currentIndex];
}
template<> JNode JNodeIterator<JObject>::operator*() const
{
	return (*m_parent)[m_currentIndex];
}
template<> JNodePtr JNodeIterator<JArray>::operator->() const
{
	stringstream ss;
	ss << m_parent->getPath() << "[" << m_currentIndex << "]";
	return JNodePtr(ss.str(), m_parent->m_parent);
}
template<> JNodePtr JNodeIterator<JObject>::operator->() const
{
	stringstream ss;
	ss << m_parent->getPath() << "/" << m_parent->m_vec[m_currentIndex];
	return JNodePtr(ss.str(), m_parent->m_parent);
}
template<typename JNodeType> size_t JNodeIterator<JNodeType>::operator-(const JNodeIterator that) const
{
	return this->m_currentIndex - that.m_currentIndex;
}

