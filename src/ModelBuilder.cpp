#include "ModelBuilder.h"

std::vector<Mesh> ModelBuilder::load_model(std::string dae_filename) {
    const aiScene *model = aiImportFile(dae_filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    // Get path from given filename
    std::string directory;
    const size_t last_slash_idx = dae_filename.rfind('/');
    if (std::string::npos != last_slash_idx) {
        directory = dae_filename.substr(0, last_slash_idx);
    }

    /*===================================
   * Load all textures
   *==================================*/
    // ASSUMES each material only has 1 texture
    size_t texIndex = 0;
    std::vector<std::string> textures;
    aiString path;
    for (size_t materialIndex = 0; materialIndex < model->mNumMaterials; ++materialIndex) {
        model->mMaterials[materialIndex]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        textures.push_back(
                (directory + path.C_Str())
        );
    }

    /*===================================
     * Convert model to array of verts,
     * generate meshes.
     *==================================*/
    std::vector<Mesh> meshes;
    for (size_t meshIndex = 0; meshIndex < model->mNumMeshes; ++meshIndex) {
        std::vector<MeshVertex> vertices;
        std::vector<MeshUV> uvs;
        aiMesh *root = model->mMeshes[meshIndex];

        // For all faces


        for (size_t faceIndex = 0; faceIndex < root->mNumFaces; faceIndex++) {
            // Push face to list
            for (size_t i = 0; i < root->mFaces->mNumIndices; i++) {
                size_t index = root->mFaces[faceIndex].mIndices[i];

                vertices.push_back(MeshVertex{
                        root->mVertices[index].x,
                        root->mVertices[index].y,
                        root->mVertices[index].z
                });

                uvs.push_back(MeshUV{
                        root->mTextureCoords[0][index].x,
                        1 - root->mTextureCoords[0][index].y
                });
            }
        }

        // Make mesh
        meshes.push_back({
                                 vertices,
                                 uvs,
                                 textures.at(root->mMaterialIndex)
                         });
    }

    aiReleaseImport(model);

    return meshes;
}