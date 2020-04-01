# Love2DAssimp

<img src="https://raw.githubusercontent.com/tfcat/tfcat.github.io/master/files/love2dassimpexample.png" height="300">

### Compiling:
1) Download Lua5.1 and Assimp static libraries
2) Change CMakeLists include and link directories to match your own
3) `cmake .` 

[**Prebuilt Windows binary here!**](https://github.com/tfcat/tfcat.github.io/blob/master/files/Love2DAssimp.dll?raw=true)

### Requirements
With your Love2D game, you will need to include both `Love2DAssimp.dll` *and* `assimp.dll` from https://www.assimp.org/index.php/downloads. 

### Usage:
```lua
local Love2DAssimp = require("Love2DAssimp")
local importedMeshList = Love2DAssimp.assimp_import("my_model.dae")
```
The format of `importedMeshList` is: 
```
{
    [1] = {
        {x, y, z, u, v},
        {x, y, z, u, v},
        ...
    },
    [2] = {
        {x, y, z, u, v},
        ...   
    }
}
```
You can import each mesh into a Love2D mesh with:
```lua
local format = {
    {"VertexPosition", "float", 3},
    {"VertexTexCoord", "float", 2},
}
local mymesh = love.graphics.newMesh(format, importedMeshList[1], "triangles")
```

**Run `love .` in the `example` folder for a working example.**

Model used in example:
https://www.models-resource.com/mobile/summonerswar/model/9568/
