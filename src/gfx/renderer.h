#ifndef GFX_H
#define GFX_H

#include <d3d11.h>
#include <cstdint>

class renderer
{
public:

	static renderer& get_instance();

	void init(HWND hwnd, HINSTANCE hInstance);
	void release();

	void update(float dt);
	void render();

private:
	~renderer();

	HWND hwnd;
	HINSTANCE hInstance;

	D3D_DRIVER_TYPE driver_type;
	D3D_FEATURE_LEVEL feature_level;

	ID3D11Device* d3d_device;
	ID3D11DeviceContext* d3d_context;
	IDXGISwapChain* swap_chain;
	ID3D11RenderTargetView* backbuffer_target;

	uint16_t screen_width;
	uint16_t screen_height;
	float dt;
};

#endif // GFX_H