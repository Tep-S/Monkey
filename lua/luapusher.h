#ifndef LUAPUSHER_H
#define LUAPUSHER_H

// main.cpp
#include "lua/luabridge/LuaBridge.h"
#include <iostream>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class LuaTestClass
{
public:
    LuaTestClass(){}
    void Test(std::string text){
        std::cout << text << std::endl;
    }
};

class LuaPusher
{
public:
    LuaPusher();
private:
    luabridge::lua_State* L;
    void LuaTest();
    void PushTest();
    void ClassTest();
};

#endif // LUAPUSHER_H
