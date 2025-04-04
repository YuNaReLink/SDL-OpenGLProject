#pragma once
#include <GL/glew.h>
#include <string>
#include "Math.h"
#include "Mesh.h"

class Shader
{
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// Set this as the active shader program
	void SetActive();
	// Sets a Matrix uniform
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	// Sets an array of matrix uniforms
	void SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count);
	// Sets a Vector3 uniform
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetVector2Uniform(const char* name, const Vector2& vector);
	// Sets a float uniform
	void SetFloatUniform(const char* name, float value);
	// Sets an integer uniform
	void SetIntUniform(const char* name, int value);

	void SetMaterialColor(const Vector4& color);

	void SetColorUniform(const char* name,const MaterialInfo info);

	void SetMaterialUniform(const char* name, const Vector3& color);

	void SetNoTexture();
private:
	// Tries to compile the specified shader
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// Tests whether shader compiled successfully
	bool IsCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool IsValidProgram();
private:
	// Store the shader object IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
	Vector4 mMaterialColor;
};

class MaterialShader 
{
	MaterialShader();
	~MaterialShader();
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// Set this as the active shader program
	void SetActive();

	void SetMaterialColor(const Vector4& color);

	void SetColorUniform(const char* name);

	void SetMaterialUniform(const char* name, const Vector3& color);
private:
	// Tries to compile the specified shader
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// Tests whether shader compiled successfully
	bool IsCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool IsValidProgram();
private:
	// Store the shader object IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
	Vector4 mMaterialColor;
};