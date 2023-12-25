#include "microdbc.hpp"

using namespace std;

void Microdbc::print_error(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR sqlState[1024];
	SQLCHAR message[1024];
	
	if (SQL_SUCCESS	== SQLGetDiagRec(handleType, handle, 1, sqlState, NULL, message, 1024, NULL))
		cout << "Message: " << message << "\nSQLSTATE: " << sqlState << endl;
}

Microdbc::Microdbc()
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		throw "SqlAllocHandle failed1";
	
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		throw "SqlSetEnvAttr failed!";
}

Microdbc::~Microdbc()
{
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

bool Microdbc::connect(const string& connectionString)
{
	connString = connectionString;
	
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnectionHandle))
		throw "SQLAllocHandle failed!";
	
	cout << "Connecting to the database..." << endl;
	
	retcode = SQLDriverConnect(sqlConnectionHandle, NULL, (SQLCHAR*)connString.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	
	if (SQL_SUCCESS == retcode)
		return true;
	else
	{
		cout << "Connection failed!" << endl;
		print_error(SQL_HANDLE_DBC, sqlConnectionHandle);
		throw "Connection failed!";
		return false;
	}
}

void Microdbc::disconnect()
{
	SQLDisconnect(sqlConnectionHandle);
}

string Microdbc::executeQuery(const string query)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnectionHandle, &sqlStatementHandle))
		throw "SQLAllocHandle failed!";
	
	if (SQL_SUCCESS != SQLExecDirect(sqlStatementHandle, (SQLCHAR*)query.c_str(), SQL_NTS))
	{
		print_error(SQL_HANDLE_STMT, sqlStatementHandle);
		throw "SQLExecDirect failed!";
		return "";
	}
	else
	{
		string result = "";
		
		SQLSMALLINT column_count;
		SQLNumResultCols(sqlStatementHandle, &column_count);
		
		while (SQLFetch(sqlStatementHandle) == SQL_SUCCESS)
		{
			for (int i = 1; i <= column_count; i++)
			{
				SQLCHAR value[1024];
				SQLGetData(sqlStatementHandle, i, SQL_CHAR, value, 1024, NULL);
				
				result += (char*)value;
				
				result += "\n";
			}
			
			return result;
		}
		
		SQLFreeHandle(SQL_HANDLE_STMT, sqlStatementHandle);
	}
}