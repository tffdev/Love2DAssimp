#include "lua.hpp"
#include "string"
#include "memory"
#include "ModelBuilder.h"
#include "lauxlib.h"

void lua_pushpair_intint(lua_State *L, int key, float value) {
    lua_pushnumber(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

void lua_pushpair_strstr(lua_State *L, std::string key, std::string value) {
    lua_pushstring(L, key.c_str());
    lua_pushstring(L, value.c_str());
    lua_settable(L, -3);
}

/**
 * Load a model using ModelBuilder, translate it to an arrays of meshes 
 * where each mesh is a list of vertices with the data: [x, y, z, u, v], 
 * then push that table to the Lua state.
 * @param L Present Lua state
 * @return 1 Number of results to return: one table containing the model's data
 */
int love2dassimp_assimp_import(lua_State *L) {
    std::string dae_filename = luaL_checkstring(L, 1);

    ModelBuilder modelBuilder;
    std::vector<Mesh> list_of_meshes = modelBuilder.load_model(dae_filename);

    printf("[Love2DAssimp] Pushing model with %zi mesh(es).\n", list_of_meshes.size());

    lua_createtable(L, 0, 0); // Table of meshes
    for (size_t mesh_index = 0; mesh_index < list_of_meshes.size(); ++mesh_index) {
        Mesh m = list_of_meshes.at(mesh_index);

        lua_pushnumber(L, mesh_index + 1); // Push current mesh index as key
        lua_createtable(L, 0, 0); // Create new table to hold all vertices in mesh

        for(size_t i = 0; i < m.vertices.size(); i++) {
            MeshVertex v = m.vertices.at(i);
            MeshUV uv = m.uvs.at(i);
            // Push vertex as a table
            lua_pushnumber(L, i + 1); // Vertex index
            lua_createtable(L, 0, 0); // Single vertex
            lua_pushpair_intint(L, 1, v.x);
            lua_pushpair_intint(L, 2, v.y);
            lua_pushpair_intint(L, 3, v.z);
            // Push UVs
            lua_pushpair_intint(L, 4, uv.x);
            lua_pushpair_intint(L, 5, uv.y);
            lua_settable(L, -3); // Push to vertices table
        }
        lua_pushpair_strstr(L, "texture", m.texture_filename);
        lua_settable(L, -3); // Push to mesh to mesh table
    }

    return 1;
}

/**
 * List of Lua C functions to register into the state on DLL load.
 */
static const struct luaL_Reg functions[] = {
        {"assimp_import", love2dassimp_assimp_import},
        {NULL, NULL} // Sentinel
};

// Library load function + export
extern "C" __declspec( dllexport ) int luaopen_Love2DAssimp(lua_State *L);

int luaopen_Love2DAssimp(lua_State *L) {
    luaL_register(L, "Love2DAssimp", functions);
    return 1;
}
