#ifndef MICRODBC_H
#define MICRODBC_H

#include <windows.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

class Microdbc
{
private:
	SQLHANDLE sqlEnvHandle;
	SQLHANDLE sqlConnectionHandle;
	SQLHANDLE sqlStatementHandle;
	SQLRETURN retcode;
	
	void print_error(unsigned int handleType, const SQLHANDLE& handle);
	
public:
	Microdbc();
	~Microdbc();
	
	bool connect(const std::string& connectionString);
	void disconnect();
	std::string executeQuery(const std::string query);
};

#ifdef __cplusplus
}
#endif

#endif // MICRODBC_H
