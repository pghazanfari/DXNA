#include "Common.h"
#include"Material.h"

struct PerObjectBuffer {
	Matrix World;
};

class BasicTexturedModelMaterial : public Material
{
	private:
		PerObjectBuffer bufferData;
		ID3D11Buffer* perObjectBuffer;
		ID3D11SamplerState* sampler;

		const char* textureName;
		ID3D11ShaderResourceView* texture;

	public:
		BasicTexturedModelMaterial();
		~BasicTexturedModelMaterial();

		inline Matrix World() { return bufferData.World; }
		inline void SetWorld(const Matrix& w) { bufferData.World = w; }
		
		inline ID3D11ShaderResourceView* Texture() { return texture; }
		void SetTexture(const char* fn);

		void SetParameter(string name, void* value);

	protected:
		void apply();
};