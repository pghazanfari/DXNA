#include "GraphicsManager.h"
#include <vector>

ID3D11Device* GraphicsManager::currentdevice = 0;
ID3D11DeviceContext* GraphicsManager::currentcontext = 0;

HRESULT GraphicsManager::initialize()
{
	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width = window->getWidth();
	scd.BufferDesc.Height = window->getHeight();
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = window->getHandle();
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	UINT flags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED;
	HRESULT h = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL, D3D11_SDK_VERSION, &scd, &swapChain, &device, NULL, &deviceContext);
	currentdevice = device;
	currentcontext = deviceContext;
	
	if (FAILED(h)) 
		return h;

	ID3D11Texture2D* bb = 0;
	ID3D11RenderTargetView* tgt = 0;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&bb));
	h = device->CreateRenderTargetView(bb, 0, &tgt);
	backbuffer = new RenderTarget(tgt, bb);
	bb->Release();//IDK IF I NEED THIS????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = window->getWidth();
	depthStencilDesc.Height = window->getHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	h = device->CreateTexture2D(&depthStencilDesc, 0, &depthstencilBuffer);
	if (FAILED(h)) 
		return h;

	h = device->CreateDepthStencilView(depthstencilBuffer, 0, &depthstencilView);

	deviceContext->OMSetRenderTargets(1, &tgt, depthstencilView);

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(window->getWidth());
	vp.Height = static_cast<float>(window->getHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	deviceContext->RSSetViewports(1, &vp);
	

	return h;
}

void GraphicsManager::clearBackBuffer(float* color)
{
	currentcontext->ClearRenderTargetView(backbuffer->getTarget(), color);
}
void GraphicsManager::clearDepthStencilView()
{
	currentcontext->ClearDepthStencilView(depthstencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11Device* GraphicsManager::currentDevice()
{
	return currentdevice;
}
ID3D11DeviceContext* GraphicsManager::currentContext()
{
	return currentcontext;
}

HRESULT GraphicsManager::CreateInputLayout(const std::vector<char>& bytes, ID3D11InputLayout** pInputLayout)
{
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(&bytes[0], bytes.size(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
		return S_FALSE;

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT i = 0; i< shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;//12 * i;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = currentDevice()->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), &bytes[0], bytes.size(), pInputLayout);

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return hr;
}

ID3D11Buffer* GraphicsManager::CreateConstantBuffer(void* data, UINT sz)
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sz;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = data;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	ID3D11Buffer* buffer = NULL;
	// Create the buffer.
	HRESULT hr = GraphicsManager::currentDevice()->CreateBuffer(&cbDesc, &InitData, &buffer);

	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Constant Buffer.", "DirectX Error", MB_OK);

	return buffer;
}