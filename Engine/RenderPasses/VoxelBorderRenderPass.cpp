#include "VoxelBorderRenderPass.h"

#include "Managers/ShaderManager.h"

#include "Renderer/Pipeline.h"

#include "VoxelVolume.h"

VoxelBorderRenderPass::~VoxelBorderRenderPass ()
{

}

void VoxelBorderRenderPass::Init ()
{
	ShaderManager::Instance ()->AddComputeShader ("VOXEL_BORDER_PASS_COMPUTE_SHADER",
		"Assets/Shaders/Voxelize/voxelBorderCompute.glsl");
}

RenderVolumeCollection* VoxelBorderRenderPass::Execute (const Scene* scene, const Camera* camera, RenderVolumeCollection* rvc)
{
	/*
	* Start mipmapping pass
	*/

	StartVoxelBordering ();

	/*
	* Mipmapping pass
	*/

	BorderVoxelVolume (rvc);

	/*
	* End mipmapping pass
	*/

	EndVoxelBordering ();

	return rvc;
}

void VoxelBorderRenderPass::StartVoxelBordering ()
{
	Pipeline::SetShader (ShaderManager::Instance ()->GetShader ("VOXEL_BORDER_PASS_COMPUTE_SHADER"));
}

#define MIPMAP_LEVELS 6

void VoxelBorderRenderPass::BorderVoxelVolume (RenderVolumeCollection* rvc)
{
	std::size_t dstMipRes = 512;
	Shader* computeShader = ShaderManager::Instance ()->GetShader ("VOXEL_BORDER_PASS_COMPUTE_SHADER");

	VoxelVolume* voxelVolume = (VoxelVolume*) rvc->GetRenderVolume ("VoxelVolume");

	voxelVolume->BindForReading ();

	for (int mipLevel = 0; mipLevel < MIPMAP_LEVELS; mipLevel++) {

		Pipeline::SendCustomAttributes ("VOXEL_BORDER_PASS_COMPUTE_SHADER",
			rvc->GetRenderVolume ("VoxelVolume")->GetCustomAttributes ());

		GL::Uniform1i (computeShader->GetUniformLocation ("SrcMipLevel"), mipLevel);
		GL::Uniform1i (computeShader->GetUniformLocation ("DstMipRes"), dstMipRes);

		voxelVolume->BindForWriting (mipLevel);

		int numWorkGroups = (int) std::ceil (dstMipRes / 4.0);
		GL::DispatchCompute (numWorkGroups, numWorkGroups, numWorkGroups);

		GL::MemoryBarrier (GL_TEXTURE_FETCH_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		dstMipRes >>= 1;
	}
}

void VoxelBorderRenderPass::EndVoxelBordering ()
{
	/*
	* Make sure writing to image has finished before read
	*/

	GL::MemoryBarrier (GL_TEXTURE_FETCH_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

