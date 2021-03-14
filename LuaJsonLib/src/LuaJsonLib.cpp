#include "cJSON.h"

#include <lua.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#define LIB_API extern "C" int

void CJson2LuaObj(cJSON* pJsonNode, lua_State* L)
{
	if (pJsonNode->string) lua_pushstring(L, pJsonNode->string);
	switch (pJsonNode->type)
	{
	case cJSON_False:
		lua_pushboolean(L, false);
		break;
	case cJSON_True:
		lua_pushboolean(L, true);
		break;
	case cJSON_Number:
		lua_pushnumber(L, pJsonNode->valuedouble);
		break;
	case cJSON_String:
		lua_pushstring(L, pJsonNode->valuestring);
		break;
	case cJSON_Array:
	{
		lua_newtable(L);
		cJSON* pElement = pJsonNode->child;
		size_t iIndex = 1;
		while (pElement)
		{
			lua_pushnumber(L, iIndex++);
			CJson2LuaObj(pElement, L);
			pElement = pElement->next;
			lua_settable(L, -3);
		}
	}
	break;
	case cJSON_Object:
	{
		lua_newtable(L);
		cJSON* pElement = pJsonNode->child;
		while (pElement)
		{
			CJson2LuaObj(pElement, L);
			pElement = pElement->next;
		}
	}
	break;
	default:
		lua_pushnil(L);
		break;
	}
	if (pJsonNode->string) lua_settable(L, -3);
}

void LuaObj2CJson(cJSON* pJsonNode, bool bHasKey, lua_State* L)
{
	switch (lua_type(L, 1))
	{
	case LUA_TNIL:
		pJsonNode = cJSON_CreateNull();
		break;
	case LUA_TBOOLEAN:
		pJsonNode = cJSON_CreateBool(lua_toboolean(L, 2));
		break;
	case LUA_TNUMBER:
		pJsonNode = cJSON_CreateNumber(lua_tonumber(L, 2));
		break;
	case LUA_TSTRING:
		pJsonNode = cJSON_CreateString(lua_tostring(L, 2));
		break;
	case LUA_TTABLE:
		lua_pushnil(L);
		pJsonNode = cJSON_CreateObject();
		break;
	default:
		luaL_argcheck(L, false, 1, string("type not support dump: ").append(lua_typename(L, 2)).c_str());
		break;
	}
	if (bHasKey) pJsonNode->string = const_cast<char*>(lua_tostring(L, 1));
}

LIB_API api_Load(lua_State* L)
{
	cJSON* pJsonRoot = cJSON_Parse(luaL_checkstring(L, 1));
	luaL_argcheck(L, pJsonRoot, 1, string("JSON parse error before: ").append(cJSON_GetErrorPtr()).c_str());
	CJson2LuaObj(pJsonRoot, L);
	cJSON_Delete(pJsonRoot);
	return 1;
}

LIB_API api_LoadFromFile(lua_State* L)
{
	std::ifstream fin(luaL_checkstring(L, 1));
	luaL_argcheck(L, fin.good(), 1, "no such JSON file");
	std::stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();
	cJSON* pJsonRoot = cJSON_Parse(ssContent.str().c_str());
	luaL_argcheck(L, pJsonRoot, 1, string("JSON parse error before: ").append(cJSON_GetErrorPtr()).c_str());
	CJson2LuaObj(pJsonRoot, L);
	ssContent.clear(); cJSON_Delete(pJsonRoot);
	return 1;
}

LIB_API api_Dump(lua_State* L)
{
	cJSON* pJsonRoot = nullptr;
	LuaObj2CJson(pJsonRoot, false, L);
	lua_pushstring(L, lua_toboolean(L, 2) ? cJSON_Print(pJsonRoot) : cJSON_PrintUnformatted(pJsonRoot));
	cJSON_Delete(pJsonRoot);
	return 1;
}

static luaL_Reg cMethods[] = {
	{ "Load", api_Load },
	{ "LoadFromFile", api_LoadFromFile },
	{ "Dump", api_Dump },
	{ nullptr, nullptr }
};

extern "C" __declspec(dllexport)
int luaopen_LuaJsonLib(lua_State * L)
{
	luaL_newlib(L, cMethods);
	return 1;
}