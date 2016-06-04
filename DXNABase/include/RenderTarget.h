#include <d3d11.h>

#pragma once

class RenderTarget
{
private:
	ID3D11RenderTargetView* target;
	ID3D11Texture2D* buffer;

	inline RenderTarget(){}

public:
	RenderTarget(const D3D11_TEXTURE2D_DESC& tex, const D3D11_RENDER_TARGET_VIEW_DESC& rt);
	RenderTarget(ID3D11RenderTargetView* rtv, ID3D11Texture2D* bff);
	inline ~RenderTarget()
	{
		target->Release();
		buffer->Release();
	}

	inline ID3D11RenderTargetView* getTarget() const { return target; };
	inline ID3D11Texture2D* getBuffer() const { return buffer; };
};