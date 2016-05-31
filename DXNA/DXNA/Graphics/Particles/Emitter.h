#include "Common.h"
#include "GraphicsManager.h"
#include "Material.h"

#pragma once

class Emitter
{
private:
	Vector3 position;
	Vector3 direction;
	float speed;

	Vector3* particles;
	Vector3* trajectories;
	int particleStartIndex;
	int liveParticleCount;
	int maxParticleCount;

	float lifespan;
	float timeBetweenFire;
	float timeSinceFirstLiveParticle;
	float timeSinceLastSpawn;

	Material* material;
	ID3D11Buffer* vbuffer;
	bool valid = false;

public:
	inline Emitter(int maxParticles, float rate, float pLifespan, Material* mat) : maxParticleCount(maxParticles), timeBetweenFire(1.0f / rate), lifespan(pLifespan), material(mat)
	{
		particles = new Vector3[maxParticles];
		trajectories = new Vector3[maxParticles];

		particleStartIndex = 0;
		liveParticleCount = 1;
		timeSinceFirstLiveParticle = 0.0f;
		timeSinceLastSpawn = 0.0f;

		//Vertex Buffer
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_DYNAMIC;
		vbd.ByteWidth = sizeof(Vector3) * maxParticleCount;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = particles;
		HRESULT hr = GraphicsManager::currentDevice()->CreateBuffer(&vbd, &vinitData, &vbuffer);
		if (FAILED(hr))
			MessageBox(NULL, "Error Creating Vertex Buffer for Particle Emitter.", "DirectX Error", MB_OK);
	}

	inline Vector3 const Direction() { return direction; }
	inline void SetDirection(const Vector3& dir) { direction = Vector3::Normalize(dir); trajectories[0] = direction; }

	inline float const Speed() { return speed; }
	inline void SetSpeed(const float& spd) { speed = spd; }

	inline void Update(float t)
	{
		timeSinceFirstLiveParticle += t;
		timeSinceLastSpawn += t;

		//Kill Live Particles
		while (liveParticleCount > 0 && timeSinceFirstLiveParticle >= lifespan)
		{
			particleStartIndex = (particleStartIndex + 1) % maxParticleCount;
			liveParticleCount--;
			timeSinceFirstLiveParticle -= timeBetweenFire;
		}

		//Update Live Particles
		for (int i = 0; i < liveParticleCount; i++)
		{
			int idx = (i + particleStartIndex) % maxParticleCount;
			particles[idx] = particles[idx] + trajectories[idx] * speed * t;

		}

		//Spawn New Particles
		while (timeSinceLastSpawn >= timeBetweenFire)
		{
			int idx = (particleStartIndex + liveParticleCount) % maxParticleCount;
			timeSinceLastSpawn -= timeBetweenFire;
			trajectories[idx] = direction;
			particles[idx] = position + trajectories[idx] * speed * timeSinceLastSpawn;
			liveParticleCount++;
		}

		float si = 1.0f;
		float sf = 0.0f;
		material->SetParameter("InitialScale", &si);
		material->SetParameter("FinalScale", &sf);

		float ai = 1.0f;
		float af = 0.0f;
		material->SetParameter("InitialAlpha", &ai);
		material->SetParameter("FinalAlpha", &af);

		float ri = 0.0f;
		float rf = 8 * 3.14f;
		material->SetParameter("InitialRotation", &ri);
		material->SetParameter("FinalRotation", &rf);

		material->SetParameter("NumLiveParticles", &liveParticleCount);
		material->SetParameter("ParticleStartIndex", &particleStartIndex);
		material->SetParameter("MaxParticleCount", &maxParticleCount);
		material->SetParameter("TimeSinceFirstLiveParticle", &timeSinceFirstLiveParticle);
		material->SetParameter("TimeBetweenParticles", &timeBetweenFire);
		material->SetParameter("Lifespan", &lifespan);
		material->SetParameter("EmitterPosition", &position);
		material->SetParameter("Speed", &speed);

		valid = false;
	}

	inline void Draw()
	{
		ID3D11DeviceContext* context = GraphicsManager::currentContext();

		if (!valid)
		{
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			context->Map(vbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, particles, maxParticleCount * sizeof(Vector3));
			context->Unmap(vbuffer, 0);
			valid = true;
		}

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		UINT stride = sizeof(Vector3);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);

		material->Apply();

		context->Draw(maxParticleCount, 0);
	}

};