#include "Loader.h"
#include "TexturedModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model Loader::loadToVao(GLfloat positions[],  GLuint size_pos, GLuint indices[], GLuint size_ind, 
						GLfloat textureCoorinates[], GLuint size_tex, GLfloat normals[], GLuint size_normals)
{
	GLuint vaoID = createVAO();
	bindVAO(vaoID);
	bindIndicesBuffer(indices, size_ind);
	dataToAttributes(0, 3, positions, size_pos);
	dataToAttributes(1, 2, textureCoorinates, size_tex);
	dataToAttributes(2, 3, normals, size_normals);
	unBindVAO();
	return Model(vaoID, size_ind);
}

Model Loader::loadToVao(GLfloat positions[], GLuint size)
{
	GLuint vaoId = createVAO();
	glBindVertexArray(vaoId);
	this->dataToAttributes(0, 2, positions, size);
	glBindVertexArray(0);
	return Model(vaoId, size/2);
}

GLuint Loader::loadTexture(GLchar * path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object		
											 // Set the texture wrapping parameters
	textures.push_back(textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image
	int width, height;
	unsigned char * img = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	//Binding the image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);
	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::dataToAttributes(GLint attribNum, GLuint coordinateSize, GLfloat data[], GLuint size)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(GLuint indices[], GLuint size)
{
	GLuint eboID;
	glGenBuffers(1, &eboID);
	vbos.push_back(eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, indices, GL_STATIC_DRAW);// TODO should we unbind?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Why shouldn't we do this?
}


void Loader::releaseVOs()
{
	for(GLuint v : vaos)
		glDeleteVertexArrays(1, &v);
	for(GLuint v : vbos)
		glDeleteBuffers(1, &v);
	for (GLuint v : textures)
		glDeleteTextures(1, &v);
}

TexturedModel processMesh(aiMesh* mesh, const aiScene* scene, string directory)
{
	Loader loader = Loader();
	string texturePath;
	Texture texture;
	vector<GLfloat> vertices;
	vector<GLfloat> texturesCoords;
	vector<GLfloat> normals;
	vector<GLuint> indices;
	// Vertices
	for (unsigned int vID = 0; vID < mesh->mNumVertices; vID++)
	{
		// Vertices
		GLfloat x_vertex = mesh->mVertices[vID].x;
		GLfloat y_vertex = mesh->mVertices[vID].y;
		GLfloat z_vertex = mesh->mVertices[vID].z;
		vertices.push_back(x_vertex);
		vertices.push_back(y_vertex);
		vertices.push_back(z_vertex);
		// Normal vectors
		GLfloat x_normal = mesh->mNormals[vID].x;
		GLfloat y_normal = mesh->mNormals[vID].y;
		GLfloat z_normal = mesh->mNormals[vID].z;
		normals.push_back(x_normal);
		normals.push_back(y_normal);
		normals.push_back(z_normal);
		//Texture coordinates
		GLfloat textX, textY;
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			textX = mesh->mTextureCoords[0][vID].x;
			textY = mesh->mTextureCoords[0][vID].y;
		}
		else
		{
			textX = 0;
			textY = 0;
		}
		texturesCoords.push_back(textX);
		texturesCoords.push_back(textY);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString str;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		string fullPath = directory + "/" + string(str.C_Str());
		//fullPath = string("../opengllearn/models/stallTexture.png"); // HARDCODED 
		texture = Texture(loader.loadTexture((GLchar*)(fullPath.c_str())));
	}
	Model model = loader.loadToVao(&vertices[0], vertices.size(), &indices[0], indices.size(), 
								   &texturesCoords[0], texturesCoords.size(), &normals[0], normals.size());
	TexturedModel textModel = TexturedModel(model, texture);
	return textModel;
}
vector<TexturedModel> processNode(aiNode* node, const aiScene* scene, string directory)
{
	vector <TexturedModel> models;
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		models.push_back(processMesh(mesh, scene, directory));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		vector<TexturedModel> newModels = processNode(node->mChildren[i], scene, directory);
		models.insert(models.begin(), newModels.begin(), newModels.end());
	}
	return models;
}
vector<TexturedModel> Loader::objToModel(string path)
{
	vector <TexturedModel> models;
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return models;
	}
	string directory = path.substr(0, path.find_last_of('/'));

	vector <TexturedModel> newModels = processNode(scene->mRootNode, scene, directory);
	models.insert(models.begin(), newModels.begin(), newModels.end());
	return models;
}