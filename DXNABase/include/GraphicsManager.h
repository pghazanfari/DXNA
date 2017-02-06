#include "Window.h"
#include "RenderTarget.h"
#include <vector>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "RenderTarget.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")


#pragma once


class GraphicsManager
{
	private:
		static ID3D11Device* currentdevice;
		static ID3D11DeviceContext* currentcontext;

		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		IDXGISwapChain* swapChain;
		D3D_FEATURE_LEVEL featureLevel;

		ID3D11Texture2D* depthstencilBuffer;
		ID3D11DepthStencilView* depthstencilView;

		Window* window;
		RenderTarget* backbuffer;

		ID3D11Buffer** globalbuffers;

		inline GraphicsManager() {}

	public:
		inline GraphicsManager(Window* w) : window(w)
		{
			globalbuffers = new ID3D11Buffer*[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
			for (int i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; i++)
				globalbuffers[i] = NULL;
		}
		inline ~GraphicsManager()
		{
			for (int i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; i++)
				if (globalbuffers[i] != NULL)
					globalbuffers[i]->Release();

			swapChain->Release();
			depthstencilBuffer->Release();
			depthstencilView->Release();
			delete backbuffer;
			delete globalbuffers;
			deviceContext->Release();
			device->Release();
		}

		HRESULT initialize();

		void clearBackBuffer(float* color);
		void clearDepthStencilView();

		inline ID3D11Buffer* GetGlobalBuffer(int index)
		{
			return globalbuffers[index];
		}

		inline ID3D11Buffer* CreateGlobalBuffer(int index, void* data, size_t sz)
		{
			if (index >= D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT || index < 0)
			{
				string message = "Invalid Index: ";
				message.append(to_string(index));
				MessageBox(NULL, message.c_str(), "DirectX Error", MB_OK);
				return NULL;
			}

			if (globalbuffers[index] != NULL)
			{

				string message = "Global Buffer Already Set at Index ";
				message.append(to_string(index));
				MessageBox(NULL, message.c_str() , "DirectX Error", MB_OK);
				return NULL;
			}

			globalbuffers[index] = CreateConstantBuffer(data, sz);

			return globalbuffers[index];
		}

		inline IDXGISwapChain* getSwapChan() { return swapChain; }

		static ID3D11Device* CurrentDevice();
		static ID3D11DeviceContext* CurrentContext();

		static HRESULT CreateInputLayout(const std::vector<char>& bytes, ID3D11InputLayout** pInputLayout);
		static ID3D11Buffer* CreateConstantBuffer(void* data, size_t sz);
};