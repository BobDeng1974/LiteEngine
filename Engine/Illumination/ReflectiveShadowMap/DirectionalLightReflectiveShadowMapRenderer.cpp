#include "DirectionalLightReflectiveShadowMapRenderer.h"

#include "Managers/ShaderManager.h"

DirectionalLightReflectiveShadowMapRenderer::DirectionalLightReflectiveShadowMapRenderer (Light* light) :
	DirectionalLightShadowMapRenderer (light),
	_rvc (nullptr)
{
	_shaderName = "REFLECTIVE_SHADOW_MAP_DIRECTIONAL_LIGHT";

	ShaderManager::Instance ()->AddShader (_shaderName,
		"Assets/Shaders/ReflectiveShadowMap/reflectiveDeferredDirVolShadowMapLightVertex.glsl",
		"Assets/Shaders/ReflectiveShadowMap/reflectiveDeferredDirVolShadowMapLightFragment.glsl");
}

DirectionalLightReflectiveShadowMapRenderer::~DirectionalLightReflectiveShadowMapRenderer ()
{
	
}

void DirectionalLightReflectiveShadowMapRenderer::Draw (Scene* scene, Camera* camera, RenderVolumeCollection* rvc)
{
	/*
	 * Keep render volumes for later
	*/

	_rvc = rvc;

	/*
	 * Draw the scene with shadows
	*/

	LightShadowMapRenderer::Draw (scene, camera, rvc);
}

std::vector<PipelineAttribute> DirectionalLightReflectiveShadowMapRenderer::GetCustomAttributes ()
{
	std::vector<PipelineAttribute> attributes = DirectionalLightShadowMapRenderer::GetCustomAttributes ();

	/*
	 * Attach all volume attributes to pipeline
	*/

	for (RenderVolumeI* renderVolume : *_rvc) {
		std::vector<PipelineAttribute> volumeAttributes = renderVolume->GetCustomAttributes ();

		attributes.insert (attributes.end (), volumeAttributes.begin (), volumeAttributes.end ());
	}

	return attributes;
}