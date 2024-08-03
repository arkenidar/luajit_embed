#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* Convenience stuff */
static void close_state(lua_State **L) { lua_close(*L); }
#define cleanup(x) __attribute__((cleanup(x)))
#define auto_lclose cleanup(close_state) 

int main(int argc, char *argv[])
{
    /* Create VM state */
    auto_lclose lua_State *L = luaL_newstate();
    if (!L)
        return 1;
    luaL_openlibs(L); /* Open standard libraries */
    /* Load config file */
    if (argc > 1) {
        luaL_loadfile(L, argv[1]); /* (1) */
        int ret = lua_pcall(L, 0, 0, 0);
        if (ret != 0) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            return 1;
        }
    }
    /* Read out config */
    lua_getglobal(L, "address"); /* (2) */
    lua_getglobal(L, "port");
    printf("address: %s, port: %ld\n", /* (3) */
        lua_tostring(L, -2), lua_tointeger(L, -1));
    lua_settop(L, 0); /* (4) */
    return 0;
}