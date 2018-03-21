#include "luapusher.h"

#include <QtGlobal>
using namespace luabridge;

LuaPusher::LuaPusher()
{
    L = luaL_newstate();

    //LuaTest();
    //ClassTest();
}

void LuaPusher::LuaTest() {
    luaL_dofile(L, "lua/script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}

void LuaPusher::PushTest(){
    luabridge::getGlobalNamespace(L)
        .beginClass<LuaTestClass>("LuaTestClass")
            .addConstructor<void(*) ()>()
            .addFunction("Test", &LuaTestClass::Test)
        .endClass();
}

void LuaPusher::ClassTest(){

    luaL_dofile(L, "lua/classtest.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);

    PushTest();

    luabridge::LuaRef RunLoop = luabridge::getGlobal(L, "RunLoop");
    RunLoop();
}
