// USE: minilua use
#define LUA_IMPL
#include "minilua.h"
// gcc main.c -lm -o main && ./main # simple compilation with just GCC
// gcc *.c -lm && ./a.out test.lua

// USE: libluajit-5.1-dev use
// #include <stdio.h>
// #include <lua.h>
// #include <lualib.h> // gcc *.c $(pkgconf --cflags --libs luajit) && ./a.* # sudo apt install libluajit-5.1-dev
// #include <lauxlib.h>

/*
// Convenience stuff
static void close_state(lua_State **L) { lua_close(*L); }
#define cleanup(x) __attribute__((cleanup(x)))
#define auto_lclose cleanup(close_state)
*/

int main(int argc, char *argv[])
{
    // **********************************

    /* Create VM state */
    lua_State *L = luaL_newstate();
    if (L == NULL)
        return -1;
    luaL_openlibs(L); /* Open standard libraries */

    // **********************************

    // minilua source : https://github.com/arkenidar/minilua-exp

    luaL_loadstring(L, "print(  1.234 )"); // 'hello world -- ' ..
    lua_call(L, 0, 0);

    luaL_loadstring(L, "print( 'hello world -- ' .. 1.234 )"); // 'hello world -- ' ..
    lua_call(L, 0, 0);

    // luaL_loadstring(L, "print( 'hello world -- ' .. io.read('*line') )"); // 'hello world -- ' ..
    // lua_call(L, 0, 0);

    // **********************************

    // blog article as original source
    // https://en.blog.nic.cz/2015/08/12/embedding-luajit-in-30-minutes-or-so/

    /* Load config file */
    if (argc > 1)
    {
        luaL_loadfile(L, argv[1]); /* (1) */
        int ret = lua_pcall(L, 0, 0, 0);
        if (ret != 0)
        {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            return 1;
        }
    }

    /* Read out config */
    lua_getglobal(L, "address"); /* (2) */
    lua_getglobal(L, "port");
    printf("address: %s, port: %lld\n", /* (3) */
           lua_tostring(L, -2), lua_tointeger(L, -1));
    lua_settop(L, 0); /* (4) */

    // **********************************

    lua_close(L);

    return 0;
}