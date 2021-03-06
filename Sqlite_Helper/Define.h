#pragma  once
#include <type_traits>
#include <cstdint>
#include "sqlite3.h"
#include "Varaint.hpp"

const string BEGIN = "BEGIN";
const string COMMIT = "COMMIT";
const string ROLLBACK = "ROLLBACK";	


//二进制类型，statement支持帮顶二进制
struct blob
{
	const char * pBuf;
	int size;
};

/**
*类型定义，数据库操作要用到的类型，如表、行、字段和值等类型
*/
typedef Variant<double, int, uint32_t, sqlite3_int64, char*, const char*, blob, string, nullptr_t> SqliteValue;	//数据表中的值类型
