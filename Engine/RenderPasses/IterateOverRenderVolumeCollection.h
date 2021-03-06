#ifndef ONCERENDERCONTAINERVOLUMECOLLECTION_H
#define ONCERENDERCONTAINERVOLUMECOLLECTION_H

#include "RenderPasses/Container/ContainerRenderVolumeCollectionI.h"

#include "IdleRenderVolume.h"

class IterateOverRenderVolumeCollection : public ContainerRenderVolumeCollectionI
{
protected:
	std::size_t _iterations;
	std::size_t _iterationsElapsed;
	IdleRenderVolume* _idleRenderVolume;

public:
	IterateOverRenderVolumeCollection (std::size_t iterations);
	~IterateOverRenderVolumeCollection ();

	void Reset ();
	RenderVolumeI* GetNextVolume ();
};

#endif