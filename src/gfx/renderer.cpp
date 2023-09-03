#include "renderer.h"

renderer& renderer::get_instance()
{
	static renderer instance;
	return instance;
}

void renderer::init(HWND hwnd, HINSTANCE hInstance)
{
	this->hwnd = hwnd;
	this->hInstance = hInstance;

	driver_type = D3D_DRIVER_TYPE_HARDWARE;
	feature_level = D3D_FEATURE_LEVEL_11_0;

	d3d_device = nullptr;
	d3d_context = nullptr;
	swap_chain = nullptr;
	backbuffer_target = nullptr;

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swap_chain_desc.BufferCount = 1;

	RECT rect;
	GetClientRect(hwnd, &rect);
	swap_chain_desc.BufferDesc.Width = rect.right - rect.left;
	swap_chain_desc.BufferDesc.Height = rect.bottom - rect.top;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.Windowed = true;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;

	screen_width = swap_chain_desc.BufferDesc.Width;
	screen_height = swap_chain_desc.BufferDesc.Height;

	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, driver_type, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain, &d3d_device, &feature_level, &d3d_context);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"Failed to create device and swap chain", L"Error", MB_OK);
		return;
	}

	ID3D11Texture2D* backbuffer_texture;

	result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer_texture);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"Failed to get backbuffer", L"Error", MB_OK);
		return;
	}

	result = d3d_device->CreateRenderTargetView(backbuffer_texture, nullptr, &backbuffer_target);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"Failed to create render target view", L"Error", MB_OK);
		return;
	}

	if (backbuffer_texture)
	{
		backbuffer_texture->Release();
	}

	d3d_context->OMSetRenderTargets(1, &backbuffer_target, nullptr);

	D3D11_VIEWPORT viewport;

	viewport.Width = (float)screen_width;
	viewport.Height = (float)screen_height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	d3d_context->RSSetViewports(1, &viewport);
}

void renderer::update(float dt)
{
}

void renderer::render()
{
	float color[4] = { 0.01f, 0.02f, 0.08f, 1.0f };
	d3d_context->ClearRenderTargetView(backbuffer_target, color);
	swap_chain->Present(0, 0);
}

renderer::~renderer()
{
	release();
}

void renderer::release()
{
	if (backbuffer_target)
	{
		backbuffer_target->Release();
	}

	if (swap_chain)
	{
		swap_chain->Release();
	}

	if (d3d_context)
	{
		d3d_context->Release();
	}

	if (d3d_device)
	{
		d3d_device->Release();
	}

	d3d_device = nullptr;
	d3d_context = nullptr;
	swap_chain = nullptr;
	backbuffer_target = nullptr;
}