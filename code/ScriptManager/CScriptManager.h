#pragma once

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
class CScriptManager
{
public:
	CScriptManager();
	~CScriptManager();
	CScriptManager *GetInstancePtr();
	void executeLine (const char* _line);
	void executeScript (const char* _line);
	
private:

	CScriptManager* m_instance;
	lua_State* m_lua;
};

