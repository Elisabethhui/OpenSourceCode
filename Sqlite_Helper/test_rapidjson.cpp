#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "json_helper.h"
#include "Json.hpp"
#include <iostream>
using namespace std;
using namespace rapidjson;

/*����rapidjson�Ĳ��Ժ���*/
void test_rapidjson()
{
	const char* json = "[ { \"hello\":\"world\"}]";
	//����
	Document document;
	if (document.Parse<0>(json).HasParseError())
	{
		cout << document.GetParseError() << endl;
		return;
	}
	//����json����ļ�ֵ��
	for (size_t i = 0, len = document.Size(); i < len; i++)
	{
		const Value& val = document[i];
		cout << val["hello"].GetString() << endl;
	}
}
/*writer,��������json�����demo*/
void test_writer()
{
	rapidjson::StringBuffer  buf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	writer.StartArray();
	for (size_t i = 0; i < 10;i++)
	{
		writer.StartObject(); //��ʼ����json����
		writer.String("ID");
		writer.Int(i+1);

		writer.String("Name");
		writer.String("Peter");

		writer.String("Address");
		writer.String("wuhan");
		writer.EndObject();
	}

	writer.EndArray();
	cout << buf.GetString() << endl;
}

void test_json_helper()
{
	JsonCpp jcp;
	jcp.StartArray();
	for (size_t i = 0; i < 10;i++)
	{
		jcp.StartObject();
		jcp.WriteJson("ID", i);
		jcp.WriteJson("Name", "Peter");
		jcp.EndObject();
	}
	jcp.EndArray();
	cout << jcp.GetString();
}

/*����json_helper�࣬ûд��*/
void test_execute_json()
{

}

#if 0
int main()
{
	test_json_helper();
	system("pause");
	return 0;
}
#endif