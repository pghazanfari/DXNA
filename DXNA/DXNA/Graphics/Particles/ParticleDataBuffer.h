#include "Common.h"
#pragma once

struct ParticleDataBuffer
{
	float alphaInitial;
	float alphaFinal;

	float rotationInitial;
	float rotationFinal;

	float scaleInitial;
	float scaleFinal;

	int NumLiveParticles;
	int ParticleStartIndex;

	int MaxParticleCount;
	float TimeBetweenParticles;
	float TimeSinceFirstLiveParticle;
	float Lifespan;

	Vector3 EmitterPosition;
	float Speed;
};