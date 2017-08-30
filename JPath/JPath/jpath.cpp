#include "jpath.h"
using namespace std;
using namespace rapidjson;

JNode::JNode(const std::string& path, JPath* parent) :
	m_name(*(ExString::split(path, { "/" }).end() - 1)),
	m_path(string(path)),
	m_parent(parent)
{ }

JPath::JPath(const string& file)
{
	char* jsonStr;
	if (!loadFile(file, &jsonStr))
	{
		cout << "JPath | Cannot open json file!" << endl;
		return;
	}

	m_document.Parse(jsonStr);
	m_loaded = true;
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
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return true;
	return Pointer(path.data()).Get(this->m_document)->IsNull();
}
template<> bool JPath::hasValue<bool>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsBool();
}
template<> bool JPath::hasValue<uint32_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsUint();
}
template<> bool JPath::hasValue<int32_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsInt();
}
template<> bool JPath::hasValue<int64_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsInt64();
}
template<> bool JPath::hasValue<uint64_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsUint64();
}
template<> bool JPath::hasValue<float_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsFloat();
}
template<> bool JPath::hasValue<double_t>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsDouble();
}
template<> bool JPath::hasValue<string>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsString();
}
template<> bool JPath::hasValue<JArray>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsArray();
}
template<> bool JPath::hasValue<JObject>(const std::string & path)
{
	if (Pointer(path.data()).Get(this->m_document) == nullptr) return false;
	return Pointer(path.data()).Get(this->m_document)->IsObject();
}

template<> void JPath::getValue<void>(const std::string & path)
{ return; }
template<> bool JPath::getValue<bool>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetBool();
}
template<> uint32_t JPath::getValue<uint32_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetUint();
}
template<> int32_t JPath::getValue<int32_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetInt();
}
template<> int64_t JPath::getValue<int64_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetInt64();
}
template<> uint64_t JPath::getValue<uint64_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetUint64();
}
template<> float_t JPath::getValue<float_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetFloat();
}
template<> double_t JPath::getValue<double_t>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetDouble();
}
template<> string JPath::getValue<string>(const std::string & path)
{
	return Pointer(path.data()).Get(this->m_document)->GetString();
}
template<> JArray JPath::getValue<JArray>(const std::string & path)
{
	JArray result = JArray(path, this);
	Value::Array source = Pointer(path.data()).Get(this->m_document)->GetArray();
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
	JObject result = JObject(path, this);
	Value::Object source = Pointer(path.data()).Get(this->m_document)->GetObject();
	stringstream ss;
	for (auto& object : source)
	{
		ss << path << "/" << object.name.GetString();
		result.insert(ss.str());
		ss.str("");
	}
	return result;
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
template<> bool JNode::hasValue<float_t>(const string& relative_path)
{
	return m_parent->hasValue<float_t>(m_path + relative_path);
}
template<> bool JNode::hasValue<double_t>(const string& relative_path)
{
	return m_parent->hasValue<double_t>(m_path + relative_path);
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
template<> float_t JNode::getValue<float_t>(const string& relative_path)
{
	return m_parent->getValue<float_t>(m_path + relative_path);
}
template<> double_t JNode::getValue<double_t>(const string& relative_path)
{
	return m_parent->getValue<double_t>(m_path + relative_path);
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

JArray::JArray(const std::string & path, JPath * parent) :
	m_name(*(ExString::split(path, { "/" }).end() - 1)),
	m_path(string(path)),
	m_parent(parent)
{ }
JNode JArray::operator[](size_t index)
{
	if (!m_map.count(index))
	{
		stringstream ss;
		ss << "JPath | Cannot find index of " << index << " in node : " << m_path << "!" << endl;
		throw out_of_range(ss.str().data());
	}
	return JNode(m_map[index], m_parent);
}
void JArray::insert(size_t index, std::string path)
{
	m_map.insert(pair<size_t, string>(index, path));
}
size_t JArray::size()
{
	return m_map.size();
}

JObject::JObject(const std::string & path, JPath * parent) :
	m_name(*(ExString::split(path, { "/" }).end() - 1)),
	m_path(string(path)),
	m_parent(parent)
{ }
JNode JObject::operator[](std::string index)
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
size_t JObject::size()
{
	return m_vec.size();
}
