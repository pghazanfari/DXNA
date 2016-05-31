#include "RenderTarget.h"
#include "GraphicsManager.h"

RenderTarget::RenderTarget(const D3D11_TEXTURE2D_DESC& tex, const D3D11_RENDER_TARGET_VIEW_DESC& rt)
{
	ID3D11Device* dev = GraphicsManager::currentDevice();
	dev->CreateTexture2D(&tex, 0, &buffer);
	dev->CreateRenderTargetView(buffer, &rt, &target);
}
RenderTarget::RenderTarget(ID3D11RenderTargetView* rtv, ID3D11Texture2D* bff) : target(rtv), buffer(bff) {}