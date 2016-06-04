#include "GraphicsManager.h"
#include <unordered_map>

#pragma once

class Material 
{
	protected:
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D11GeometryShader* geometryShader;
		ID3D11InputLayout* inputLayout;
		const char* vs_name;
		const char* ps_name;
		const char* gs_name;
		const char* il_name;
		bool gs;

		inline Material() {}

	protected:
		virtual void apply() = 0;

	public:
		Material(const char* vs, const char* ps, const char* il);
		Material(const char* vs, const char* ps, const char* gs, const char* il);
		~Material();

		virtual void SetParameter(string name, void* value) = 0;

		static Material* Generate(string name);

		inline ID3D11VertexShader* getVertexShader() { return vertexShader; }
		inline ID3D11PixelShader* getPixelShader() { return pixelShader; }
		inline ID3D11GeometryShader* getGeometryShader() { return geometryShader; }

		inline void SetPreset(std::unordered_map<string, void*>* presets)
		{
			for (auto it = presets->begin(); it != presets->end(); ++it)
			{
				SetParameter(it->first, it->second);
			}
		}

		inline void Apply() 
		{
			ID3D11DeviceContext* context = GraphicsManager::currentContext();
			context->VSSetShader(vertexShader, 0, 0);
			context->PSSetShader(pixelShader, 0, 0);
			if (gs) context->GSSetShader(geometryShader, 0, 0);
			else context->GSSetShader(NULL, 0, 0);
			context->IASetInputLayout(inputLayout);
			apply();
		}
};