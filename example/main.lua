local l2dassimp = require("Love2DAssimp")

love.window.setMode(800, 600)

-- Make a new framebuffer and depth buffer
local myDisplayBuffer = love.graphics.newCanvas(800, 600)
local myDepthBuffer = love.graphics.newCanvas(800, 600, {readable = false, format = "depth32fstencil8"})

-- Set depth function 
love.graphics.setDepthMode("less", true)

-- Import model using Love2DAssimp, where a model is a list of meshes
local importedMeshList = l2dassimp.assimp_import("samurai_hr/samurai_hr-dark.dae")
    
local format = {
    {"VertexPosition", "float", 3},
    {"VertexTexCoord", "float", 2},
}

-- Take our imported mesh list, convert them to a list of Love2D Mesh objects
local myListOfMeshes = {}
for k,modelMesh in pairs(importedMeshList) do
    local newMesh = love.graphics.newMesh(format, modelMesh, "triangles")
    -- texture path
    if modelMesh.texture ~= nil and modelMesh.texture ~= "" then
        newMesh:setTexture(love.graphics.newImage(modelMesh.texture))
    end
    table.insert(myListOfMeshes, newMesh)
end


-- Create default transformation
local objtransform = love.math.newTransform()
objtransform:scale(20)
objtransform:translate(10, 20, 0)
objtransform:rotate(math.pi)


function love.draw() 
	love.graphics.setColor(1,1,1,1)
	love.graphics.setCanvas({myDisplayBuffer, depthstencil = myDepthBuffer })
    love.graphics.clear(0.05,0.,0.)

    -- For every mesh in our list, draw the mesh!
	for k,m in pairs(myListOfMeshes) do
		love.graphics.draw(m, objtransform)
	end

	love.graphics.setCanvas()
	love.graphics.draw(myDisplayBuffer)
	love.graphics.print("Love2DAssimp test", 10, 10)
end