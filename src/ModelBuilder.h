#pragma once
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "string"
#include "vector"
#include "map"

struct MeshVertex {
    float x, y, z;
};

struct MeshUV {
    float x, y;
};

struct Mesh {
    std::vector<MeshVertex> vertices;
    std::vector<MeshUV> uvs;
    std::string texture_filename;
};

class ModelBuilder {
public:
    ModelBuilder() {};
    ~ModelBuilder() {};
    std::vector<Mesh> load_model(std::string dae_filename);
};
