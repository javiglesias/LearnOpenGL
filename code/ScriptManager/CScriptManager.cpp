#include "CScriptManager.h"

CScriptManager* CScriptManager::GetInstancePtr()
{
	if (m_instance == nullptr)
		m_instance = new CScriptManager();
	return m_instance;
}

void CScriptManager::executeLine(const char* _line)
{
	if (luaL_loadstring(m_instance->m_lua, _line) == 0)
		lua_call(m_instance->m_lua, 0, 0);
}

void CScriptManager::executeScript(const char* _file)
{
	if(luaL_loadfile(m_instance->m_lua, _file) == 0)
		lua_call(m_instance->m_lua, 0, 0);
}

CScriptManager::CScriptManager()
{
	m_instance = this;
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);
	luaopen_io(m_lua);
	luaopen_base(m_lua);
}

CScriptManager::~CScriptManager()
{
	lua_close(m_lua);
	m_instance = nullptr;
	delete m_instance;
}
