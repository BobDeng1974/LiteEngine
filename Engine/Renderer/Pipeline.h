#ifndef PIPELINE_H
#define PIPELINE_H

#include <glm/glm.hpp>

#include "SceneGraph/Transform.h"
#include "Material/Material.h"
#include "Systems/Camera/Camera.h"

#include "PipelineAttribute.h"

#include "Shader/Shader.h"

#include "Material/Material.h"
#include "Texture/Texture.h"

// TODO: Refactor this

class Pipeline
{
private:
	static glm::mat4 _modelMatrix;
	static glm::mat4 _viewMatrix;
	static glm::mat4 _projectionMatrix;

	static glm::vec3 _cameraPosition;

	static std::size_t _textureCount;

	static Shader* _lockedShader;

	static Material* _defaultMaterial;
	static Texture* _defaultTexture;

public:
	static void Init ();

	static void SetShader (Shader* shader);

	static void LockShader (Shader* shader);
	static void UnlockShader ();

	static void CreateProjection (const Camera* camera);
	static void CreateProjection (glm::mat4 projectionMatrix);

	static void SetObjectTransform (Transform *transform);
	static void SendCamera (const Camera* camera);

	static void UpdateMatrices (Shader* shader);
	static void SendLights (Shader* shader);
	static void SendMaterial (Material* material, Shader* shader = nullptr);
	// TODO: Reimplement this
	static void SendCustomAttributes (const std::string& shadername, 
		const std::vector<PipelineAttribute>& attrs);

	static void ClearObjectTransform ();
};

#endif