#include <d3d11.h>
#pragma once

class BlendStates {

public:
	static inline void AlphaBlend(int rt, D3D11_BLEND_DESC& desc)
	{
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.RenderTarget[rt].BlendEnable = TRUE;
		desc.RenderTarget[rt].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[rt].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[rt].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[rt].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[rt].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[rt].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[rt].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	static inline void AdditiveBlend(int rt, D3D11_BLEND_DESC& desc)
	{
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.RenderTarget[rt].BlendEnable = TRUE;
		desc.RenderTarget[rt].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[rt].DestBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[rt].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[rt].SrcBlendAlpha = D3D11_BLEND_ONE;//D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[rt].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[rt].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[rt].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
};