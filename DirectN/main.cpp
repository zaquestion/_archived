#include "DirectN.h"

using namespace DirectN;

int WINAPI WinMain(HINSTANCE cur, HINSTANCE pre, LPSTR CmdLine, int CmdShow)
{
	WindowClass::hInstance = cur;
	DeviceManager::VSync = 1;
	
	DeviceManager::IntializeDevice();
	//DeviceManager::ApplyChanges();
	//DeviceManager::ToggleFullScreen();
	Input::Initialize();
	ContentManager Content = ContentManager(L"");
	Device::Content = &Content;
	//Effect* effect = Content.Load<Effect>(L"basic.fx");
	//Texture2D* tex1 = Content.Load<Texture2D>(L"frag.png");
	//Texture2D* tex2 = Content.Load<Texture2D>(L"punc.bmp");
	//Texture2D* tex3 = Content.Load<Texture2D>(L"runon.jpg");

	//D3DSURFACE_DESC* desc;
	//IDirect3DTexture9* tex;
	//Device.device->CreateTexture(200, 150, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, 0);
	//tex->GetLevelDesc(0, desc);
	//Device.device->GetTexture(

	IDirect3DSurface9* surface;
	Device::device->CreateRenderTarget(800, 600, SurfaceFormat::A8R8G8B8, D3DMULTISAMPLE_NONE, 0, 0, &surface, 0);

	IDirect3DTexture9* texture;
	Device::device->CreateTexture(800, 600, 1, D3DUSAGE_RENDERTARGET, SurfaceFormat::A8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	

	int blah = 0;

	//V::PT v[] =
 //   {
 //     /*
	//    V::PC(Vector3(400.0f, 200.0f - 173.0f, 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(500.0f, 200.0f         , 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(300.0f, 200.0f         , 0.0f), Color(255, 0, 0, 255)),

	//	V::PC(Vector3(300.0f, 200.0f         , 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(400.0f, 200.0f + 173.0f, 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(200.0f, 200.0f + 173.0f, 0.0f), Color(255, 0, 0, 255)),

	//	V::PC(Vector3(500.0f, 200.0f         , 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(600.0f, 200.0f + 173.0f, 0.0f), Color(255, 0, 0, 255)),
 //       V::PC(Vector3(400.0f, 200.0f + 173.0f, 0.0f), Color(255, 0, 0, 255)),
 //     */
	//	
	//	V::PT(Vector3(150, 50, 0), Vector2(0.0f, 0.0f)),
	//	V::PT(Vector3(650, 50, 0), Vector2(1.0f, 0.0f)),
	//	V::PT(Vector3(650, 550, 0), Vector2(1.0f, 1.0f)),
	//	
	//	V::PT(Vector3(650, 550, 0), Vector2(1.0f, 1.0f)),
	//	V::PT(Vector3(150, 550, 0), Vector2(0.0f, 1.0f)),
	//	V::PT(Vector3(150, 50, 0), Vector2(0.0f, 0.0f)),
 //   };
	
	MSG msg;
	while(1)
	{
		Mouse::Update();
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(msg.message == WM_QUIT) 
			break;
 
		Keyboard::Update();
		GamePads::Update();

		if(Keyboard::Cur.KeyDown(Keys::Esc)) PostMessage(Window::hWnd, WM_DESTROY, 0, 0);
		if(Keyboard::KeyPressed(Keys::F)) DeviceManager::ToggleFullScreen();

		//----------------------------------------------------------------------------------------------------//
		//Draw                                                                                                //
		//----------------------------------------------------------------------------------------------------//
			
		//Device::Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//
		//effect->SetValue("W", Matrix4::Identity());
		//effect->SetValue("P", Matrix4::CreateOrthographicOffCenter(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, 1.0f));
		//effect->SetValue<Texture2D>("Texture", tex1);

		//int i[] = { 0, 1, 2, 2, 3, 0 };
		//
		//Device::BeginScene();
		//	
		//effect->Begin();
		//
		//Device::DrawUserPrimitive<V::PT>(PrimitiveType::TriangleList, v, 2);

		//effect->End();
		//
		//Device::EndScene();

	}
}