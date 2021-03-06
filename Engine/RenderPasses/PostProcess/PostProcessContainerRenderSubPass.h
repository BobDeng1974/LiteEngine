#ifndef POSTPROCESSCONTAINERRENDERSUBPASS_H
#define POSTPROCESSCONTAINERRENDERSUBPASS_H

#include "RenderPasses/Container/ContainerRenderSubPassI.h"

#include <vector>
#include <string>

#include "RenderPasses/PostProcess/PostProcessMapVolume.h"

#include "Renderer/PipelineAttribute.h"

#define POST_PROCESS_MAP_VOLUME_NOT_INIT 354

class PostProcessContainerRenderSubPass : public ContainerRenderSubPassI
{
protected:
	PostProcessMapVolume* _postProcessMapVolume;

public:
	PostProcessContainerRenderSubPass ();
	virtual ~PostProcessContainerRenderSubPass ();

	void Init ();
	RenderVolumeCollection* Execute (const Scene* scene, const Camera* camera, RenderVolumeCollection* rvc);
protected:
	virtual void StartPostProcessPass ();
	virtual void PostProcessPass (const Scene* scene, const Camera* camera, RenderVolumeCollection* rvc);
	virtual void EndPostProcessPass ();

	virtual std::vector<PipelineAttribute> GetCustomAttributes (RenderVolumeCollection* rvc);

	virtual std::string GetPostProcessFragmentShaderPath () const = 0;
	virtual std::string GetPostProcessVolumeName () const = 0;
	virtual PostProcessMapVolume* CreatePostProcessVolume () const = 0;
};

#endif