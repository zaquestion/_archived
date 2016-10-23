#include "DirectN.h"

namespace DirectN
{

#pragma region Global

void CleanUp()
{
	Device::Release();
}

#pragma endregion

#pragma region Windows

#pragma region Window

#pragma region Members

HWND Window::hWnd;

#pragma endregion

#pragma region Methods

#pragma region private

void Window::CreateWindowed()
{
	hWnd = CreateWindowEx(0, L"freshman", WindowClass::WindowName, WS_OVERLAPPEDWINDOW, 75, 25, Device::Width, Device::Height, 0, 0, WindowClass::hInstance, 0);
}

void Window::CreateFullScreen()
{
	hWnd = CreateWindowEx(0, L"freshman", WindowClass::WindowName, WS_EX_TOPMOST | WS_POPUP, 0, 0, Device::Width, Device::Height, 0, 0, WindowClass::hInstance, 0);
}

#pragma endregion

#pragma region public

#pragma region SetupWindow

void Window::SetupWindow()
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WindowClass::WindowProcFunction;
	wc.hInstance = WindowClass::hInstance;
	wc.hCursor = WindowClass::hCursor;
	wc.style = WindowClass::Style;
	wc.lpszClassName = L"freshman";

	RegisterClassEx(&wc);

	DeviceManager::IsFullScreen ? CreateFullScreen() : CreateWindowed();	
	ShowWindow(hWnd, 1);
}
#pragma endregion

#pragma region WindowProc

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (message == WM_ACTIVATE)
	{	
		if(DeviceManager::IsFullScreen && wParam == WA_INACTIVE)
			DeviceManager::ToggleFullScreen();
		return 0;
	}
	else if (message == WM_INPUT)
	{
		RAWINPUT InputData;

        UINT DataSize = sizeof(RAWINPUT);
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &InputData, &DataSize, sizeof(RAWINPUTHEADER));

		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) Mouse::Cur.Left = 1;
		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) Mouse::Cur.Left = 0;

		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN) Mouse::Cur.Right = 1;
		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP) Mouse::Cur.Right = 0;

		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_MIDDLE_BUTTON_DOWN) Mouse::Cur.Middle = 1;
		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_MIDDLE_BUTTON_UP) Mouse::Cur.Middle = 0;

		if (InputData.data.mouse.usButtonFlags == RI_MOUSE_WHEEL) Mouse::Cur.Wheel += InputData.data.mouse.usButtonData;
		
		Mouse::Cur.Velocity.X = (FLOAT)InputData.data.mouse.lLastX;
		Mouse::Cur.Velocity.Y = (FLOAT)InputData.data.mouse.lLastY;

		return 0;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region WindowClass

#pragma region Members

HINSTANCE WindowClass::hInstance;
HCURSOR WindowClass::hCursor = LoadCursor(0, IDC_ARROW);
LPCTSTR WindowClass::WindowName = L"freshman 2.0"; /* Name for the WINDOW, not the Class. Classname is always "freshman". WindowName defaults to "freshman 2.0" */
HICON WindowClass::hIcon;
uint WindowClass::Style = CS_HREDRAW | CS_VREDRAW;

WNDPROC WindowClass::WindowProcFunction = Window::WindowProc;

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Math

#pragma region Vector2

//Defined in Inline Section (NGraphics.h at the bottom)

Vector2 Vector2::BaryCentric(const Vector2 &V1, const Vector2 &V2, const Vector2 &V3, const FLOAT &F, const FLOAT &G)
{
	return V1 + F * (V2 - V1) + G * (V3 - V1);
}

Vector2 Vector2::CatmullRom(const Vector2 &V1, const Vector2 &V2, const Vector2 &V3, const Vector2 &V4, const FLOAT &S)
{
	return 0.5 * ((2 * V2) + (-V1 + V3) * S + (2 * V1 -5 * V2 + 4 * V3 - V4) * (S * S) + (-V1 + 3 * V2 - 3 * V3 + V4) * (S * S * S));
}


#pragma endregion

#pragma region Vector3

//Defined in Inline Section (NGraphics.h at the bottom)

Vector3 Vector3::BaryCentric(const Vector3 &V1, const Vector3 &V2, const Vector3 &V3, const FLOAT &F, const FLOAT &G)
{
	return V1 + F * (V2 - V1) + G * (V3 - V1);
}

Vector3 Vector3::CatmullRom(const Vector3 &V1, const Vector3 &V2, const Vector3 &V3, const Vector3 &V4, const FLOAT &S)
{
	return 0.5 * ((2 * V2) + (-V1 + V3) * S + (2 * V1 -5 * V2 + 4 * V3 - V4) * (S * S) + (-V1 + 3 * V2 - 3 * V3 + V4) * (S * S * S));
}

#pragma endregion

#pragma region Vector4

//Defined in Inline Section (NGraphics.h at the bottom)

Vector4 Vector4::CreateQuaternion(const Vector3& Axis, const FLOAT theta)
{
	return Vector4(sin(theta/2) * Axis.X, sin(theta/2) * Axis.Y, sin(theta/2) * Axis.Z, cos(theta/2));
}

Vector4 Vector4::BaryCentric(const Vector4 &V1, const Vector4 &V2, const Vector4 &V3, const FLOAT &F, const FLOAT &G)
{
	return V1 + F * (V2 - V1) + G * (V3 - V1);
}

Vector4 Vector4::CatmullRom(const Vector4 &V1, const Vector4 &V2, const Vector4 &V3, const Vector4 &V4, const FLOAT &S)
{
	return 0.5 * ((2 * V2) + (-V1 + V3) * S + (2 * V1 -5 * V2 + 4 * V3 - V4) * (S * S) + (-V1 + 3 * V2 - 3 * V3 + V4) * (S * S * S));
}

#pragma endregion

#pragma region Matrix4

#pragma region Constructor

Matrix4::Matrix4(D3DXMATRIX& M)
{
	this->M = M;
}

Matrix4::Matrix4()
{
	this->M._11 = 0;
	this->M._21 = 0;
	this->M._31 = 0;
	this->M._41 = 0;
	this->M._12 = 0;
	this->M._22 = 0;
	this->M._32 = 0;
	this->M._42 = 0;
	this->M._13 = 0;
	this->M._23 = 0;
	this->M._33 = 0;
	this->M._34 = 0;
	this->M._14 = 0;
	this->M._24 = 0;
	this->M._34 = 0;
	this->M._44 = 0;
}

Matrix4::Matrix4(FLOAT m11, FLOAT m21, FLOAT m31, FLOAT m41, FLOAT m12, FLOAT m22, FLOAT m32, FLOAT m42, FLOAT m13, FLOAT m23, FLOAT m33, FLOAT m43, FLOAT m14, FLOAT m24, FLOAT m34, FLOAT m44)
{
	this->M._11 = m11;
	this->M._21 = m21;
	this->M._31 = m31;
	this->M._41 = m41;
	this->M._12 = m12;
	this->M._22 = m22;
	this->M._32 = m32;
	this->M._42 = m42;
	this->M._13 = m13;
	this->M._23 = m23;
	this->M._33 = m33;
	this->M._34 = m34;
	this->M._14 = m14;
	this->M._24 = m24;
	this->M._34 = m34;
	this->M._44 = m44;
}

#pragma endregion

#pragma region Operator

FLOAT* Matrix4::operator[](int i) const { return (FLOAT*)this->M.m[i]; }

Matrix4 Matrix4::operator*(const Matrix4& M) const 
{
	D3DXMATRIX ret;
	D3DXMatrixMultiply(&ret, &this->M, &M.M);
	return ret;
}

#pragma endregion

#pragma region Methods

#pragma region Value

#pragma region Determinant

FLOAT Matrix4::Determinant() const
{
	return D3DXMatrixDeterminant(&this->M);
}

#pragma endregion

#pragma region Decompose

void Matrix4::Decompose(Vector3& Scale, Vector4& Rotation, Vector3& Translation) const
{
	D3DXVECTOR3 scale;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 translation;
	D3DXMatrixDecompose(&scale, &rotation, &translation, &this->M);
	Scale.X = scale.x;
	Scale.Y = scale.y;
	Scale.Z = scale.z;
	Rotation.X = rotation.x;
	Rotation.Y = rotation.y;
	Rotation.Z = rotation.z;
	Rotation.W = rotation.w;
	Translation.X = translation.x;
	Translation.Y = translation.y;
	Translation.Z = translation.z;
}

#pragma endregion

#pragma region Identity

Matrix4 Matrix4::Identity()
{
	D3DXMATRIX O;
	D3DXMatrixIdentity(&O);
	return O;
}

#pragma endregion

#pragma region Reflect

Matrix4 Matrix4::Reflect(const Vector4& Plane)
{
	D3DXMATRIX O;
	D3DXMatrixReflect(&O, &(D3DXPLANE&)Plane);
	return O;
}

#pragma endregion

#pragma region Inverse

Matrix4 Matrix4::Inverse(const Matrix4& M)
{
	D3DXMATRIX O;
	FLOAT F = M.Determinant();
	D3DXMatrixInverse(&O, &F, &M.M);
	return O;
}

#pragma endregion

#pragma region Shadow

Matrix4 Matrix4::Shadow(const Vector4& Light, const Vector4& Plane)
{
	D3DXMATRIX O;
	D3DXMatrixShadow(&O, &(D3DXVECTOR4&)Light, &(D3DXPLANE&)Plane);
	return O;
}

#pragma endregion

#pragma region CreateRotationQuaternion

Matrix4 Matrix4::CreateRotationQuaternion(const Vector4& Quaternion)
{
	D3DXMATRIX O;
	D3DXMatrixRotationQuaternion(&O, &(const D3DXQUATERNION&)Quaternion);
	return O;
}

#pragma endregion

#pragma region CreateRotationAxis

Matrix4 Matrix4::CreateRotationAxis(const Vector3& Axis, FLOAT Angle)
{
	D3DXMATRIX O;
	D3DXMatrixRotationAxis(&O, &(const D3DXVECTOR3&)Axis, Angle);
	return O;
}

#pragma endregion

#pragma region CreateYawPitchRoll

Matrix4 Matrix4::CreateYawPitchRoll(const Vector3& Angles)
{
	D3DXMATRIX O;
	D3DXMatrixRotationYawPitchRoll(&O, Angles.X, Angles.Y, Angles.Z);
	return O;
}

#pragma endregion

#pragma region CreateRotationX

Matrix4 Matrix4::CreateRotationX(FLOAT Angle)
{
	D3DXMATRIX O;
	D3DXMatrixRotationX(&O, Angle);
	return O;
}

#pragma endregion

#pragma region CreateRotationY

Matrix4 Matrix4::CreateRotationY(FLOAT Angle)
{
	D3DXMATRIX O;
	D3DXMatrixRotationY(&O, Angle);
	return O;
}

#pragma endregion

#pragma region CreateRotationZ

Matrix4 Matrix4::CreateRotationZ(FLOAT Angle)
{
	D3DXMATRIX O;
	D3DXMatrixRotationZ(&O, Angle);
	return O;
}

#pragma endregion

#pragma region CreateTranslation

Matrix4 Matrix4::CreateTranslation(const Vector3& Translation)
{
	D3DXMATRIX O;
	D3DXMatrixTranslation(&O, Translation.X, Translation.Y, Translation.Z);
	return O;
}

#pragma endregion

#pragma region CreateTranspose

Matrix4 Matrix4::CreateTranspose(const Matrix4& M)
{
	D3DXMATRIX O;
	D3DXMatrixTranspose(&O, &M.M);
	return O;
}

#pragma endregion

#pragma region CreateMultiplyTranspose

Matrix4 Matrix4::CreateMultiplyTranspose(const Matrix4& M1, const Matrix4& M2)
{
	D3DXMATRIX O;
	D3DXMatrixMultiplyTranspose(&O, &M1.M, &M2.M);
	return O;
}

#pragma endregion

#pragma region CreateAffineTransformation

Matrix4 Matrix4::CreateAffineTransformation(FLOAT Scale, const Vector2& RotationCenter, FLOAT Rotation, const Vector2& Translation)
{
	D3DXMATRIX O;
	D3DXMatrixAffineTransformation2D(&O, Scale, &(const D3DXVECTOR2&)RotationCenter, Rotation, &(const D3DXVECTOR2&)Translation);
	return O;
}

#pragma endregion

#pragma region CreateAffineTransformation

Matrix4 Matrix4::CreateAffineTransformation(FLOAT Scale, const Vector3& RotationCenter, const Vector4& Rotation, const Vector3& Translation)
{
	D3DXMATRIX O;
	D3DXMatrixAffineTransformation(&O, Scale, &(const D3DXVECTOR3&)RotationCenter, &(const D3DXQUATERNION&)Rotation, &(const D3DXVECTOR3&)Translation);
	return O;
}

#pragma endregion

#pragma region CreateTransformation

Matrix4 Matrix4::CreateTransformation(const Vector2& ScalingCenter, FLOAT ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, FLOAT QuaternionRotation, const Vector2& Translation)
{
	D3DXMATRIX O;
	D3DXMatrixTransformation2D(&O, &(const D3DXVECTOR2&)ScalingCenter, ScalingRotation, &(const D3DXVECTOR2&)Scaling, &(const D3DXVECTOR2&)RotationCenter, QuaternionRotation, &(const D3DXVECTOR2&)Translation);
	return O;
}

#pragma endregion

#pragma region CreateTransformation

Matrix4 Matrix4::CreateTransformation(const Vector3& ScalingCenter, const Vector4& ScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Vector4& QuaternionRotation, const Vector3& Translation)
{
	D3DXMATRIX O;
	D3DXMatrixTransformation(&O, &(const D3DXVECTOR3&)ScalingCenter, &(const D3DXQUATERNION&)ScalingRotation, &(const D3DXVECTOR3&)Scaling, &(const D3DXVECTOR3&)RotationCenter, &(const D3DXQUATERNION&)QuaternionRotation, &(const D3DXVECTOR3&)Translation);
	return O;
}

#pragma endregion

#pragma region CreateScaling

Matrix4 Matrix4::CreateScaling(Vector3& Scales)
{
	D3DXMATRIX O;
	D3DXMatrixScaling(&O, Scales.X, Scales.Y, Scales.Z);
	return O;
}

#pragma endregion

#pragma region CreateLookAt

Matrix4 Matrix4::CreateLookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up)
{
	D3DXMATRIX O;
	D3DXMatrixLookAtLH(&O, &(const D3DXVECTOR3&)Eye, &(const D3DXVECTOR3&)At, &(const D3DXVECTOR3&)Up);
	return O;
}

#pragma endregion

#pragma region CreatePerspective

Matrix4 Matrix4::CreatePerspective(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar)
{
	D3DXMATRIX O;
	D3DXMatrixPerspectiveLH(&O, Width, Height, ZNear, ZFar);
	return O;
}

#pragma endregion

#pragma region CreatePerspectiveFieldOfView

Matrix4 Matrix4::CreatePerspectiveFieldOfView(FLOAT FOVY, FLOAT Aspect, FLOAT ZNear, FLOAT ZFar)
{
	D3DXMATRIX O;
	D3DXMatrixPerspectiveFovLH(&O, FOVY, Aspect, ZNear, ZFar);
	return O;
}

#pragma endregion

#pragma region CreatePerspectiveOffCenter

Matrix4 Matrix4::CreatePerspectiveOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar)
{
	D3DXMATRIX O;
	D3DXMatrixPerspectiveOffCenterLH(&O, Left, Right, Bottom, Top, ZNear, ZFar);
	return O;
}

#pragma endregion

#pragma region CreateOrthographic

Matrix4 Matrix4::CreateOrthographic(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar)
{
	D3DXMATRIX O;
	D3DXMatrixOrthoLH(&O, Width, Height, ZNear, ZFar);
	return O;
}

#pragma endregion

#pragma region CreateOrthographicOffCenter

Matrix4 Matrix4::CreateOrthographicOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar)
{
	D3DXMATRIX O;
	D3DXMatrixOrthoOffCenterLH(&O, Left, Right, Bottom, Top, ZNear, ZFar);
	return O;
}
#pragma endregion

#pragma endregion

#pragma region Reference

#pragma region Identity

void Matrix4::Identity(Matrix4& out)
{
	D3DXMatrixIdentity(&out.M);
}

#pragma endregion

#pragma region Reflect

void Matrix4::Reflect(const Vector4& Plane, Matrix4& out)
{
	D3DXMatrixReflect(&out.M, &(D3DXPLANE&)Plane);
}

#pragma endregion

#pragma region Inverse

void Matrix4::Inverse(const Matrix4& M, Matrix4& out)
{
	FLOAT F = M.Determinant();
	D3DXMatrixInverse(&out.M, &F, &M.M);
}

#pragma endregion

#pragma region Shadow

void Matrix4::Shadow(const Vector4& Light, const Vector4& Plane, Matrix4& out)
{
	D3DXMatrixShadow(&out.M, &(D3DXVECTOR4&)Light, &(D3DXPLANE&)Plane);
}

#pragma endregion

#pragma region Multiply

void Matrix4::Multiply(const Matrix4& M1, const Matrix4& M2, Matrix4& out)
{
	D3DXMatrixMultiply(&out.M, &M1.M, &M2.M);
}

#pragma endregion

#pragma region CreateRotationQuaternion

void Matrix4::CreateRotationQuaternion(const Vector4& Quaternion, Matrix4& out)
{
	D3DXMatrixRotationQuaternion(&out.M, &(const D3DXQUATERNION&)Quaternion);
}

#pragma endregion

#pragma region CreateRotationAxis

void Matrix4::CreateRotationAxis(const Vector3& Axis, FLOAT Angle, Matrix4& out)
{
	D3DXMatrixRotationAxis(&out.M, &(const D3DXVECTOR3&)Axis, Angle);
}

#pragma endregion

#pragma region CreateYawPitchRoll

void Matrix4::CreateYawPitchRoll(const Vector3& Angles, Matrix4& out)
{
	D3DXMatrixRotationYawPitchRoll(&out.M, Angles.X, Angles.Y, Angles.Z);
}

#pragma endregion

#pragma region CreateRotationX

void Matrix4::CreateRotationX(FLOAT Angle, Matrix4& out)
{
	D3DXMatrixRotationX(&out.M, Angle);
}

#pragma endregion

#pragma region CreateRotationY

void Matrix4::CreateRotationY(FLOAT Angle, Matrix4& out)
{
	D3DXMatrixRotationY(&out.M, Angle);
}

#pragma endregion

#pragma region CreateRotationZ

void Matrix4::CreateRotationZ(FLOAT Angle, Matrix4& out)
{
	D3DXMatrixRotationZ(&out.M, Angle);
}

#pragma endregion

#pragma region CreateTranslation

void Matrix4::CreateTranslation(const Vector3& Translation, Matrix4& out)
{
	D3DXMatrixTranslation(&out.M, Translation.X, Translation.Y, Translation.Z);
}

#pragma endregion

#pragma region CreateTranspose

void Matrix4::CreateTranspose(const Matrix4& M, Matrix4& out)
{
	D3DXMatrixTranspose(&out.M, &M.M);
}

#pragma endregion

#pragma region CreateMultiplyTranspose

void Matrix4::CreateMultiplyTranspose(const Matrix4& M1, const Matrix4& M2, Matrix4& out)
{
	D3DXMatrixMultiplyTranspose(&out.M, &M1.M, &M2.M);
}

#pragma endregion

#pragma region CreateAffineTransformation

void Matrix4::CreateAffineTransformation(FLOAT Scale, const Vector2& RotationCenter, FLOAT Rotation, const Vector2& Translation, Matrix4& out)
{
	D3DXMatrixAffineTransformation2D(&out.M, Scale, &(const D3DXVECTOR2&)RotationCenter, Rotation, &(const D3DXVECTOR2&)Translation);
}

#pragma endregion

#pragma region CreateAffineTransformation

void Matrix4::CreateAffineTransformation(FLOAT Scale, const Vector3& RotationCenter, const Vector4& Rotation, const Vector3& Translation, Matrix4& out)
{
	D3DXMatrixAffineTransformation(&out.M, Scale, &(const D3DXVECTOR3&)RotationCenter, &(const D3DXQUATERNION&)Rotation, &(const D3DXVECTOR3&)Translation);
}

#pragma endregion

#pragma region CreateTransformation

void Matrix4::CreateTransformation(const Vector2& ScalingCenter, FLOAT ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, FLOAT QuaternionRotation, const Vector2& Translation, Matrix4& out)
{
	D3DXMatrixTransformation2D(&out.M, &(const D3DXVECTOR2&)ScalingCenter, ScalingRotation, &(const D3DXVECTOR2&)Scaling, &(const D3DXVECTOR2&)RotationCenter, QuaternionRotation, &(const D3DXVECTOR2&)Translation);
}

#pragma endregion

#pragma region CreateTransformation

void Matrix4::CreateTransformation(const Vector3& ScalingCenter, const Vector4& ScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Vector4& QuaternionRotation, const Vector3& Translation, Matrix4& out)
{
	D3DXMatrixTransformation(&out.M, &(const D3DXVECTOR3&)ScalingCenter, &(const D3DXQUATERNION&)ScalingRotation, &(const D3DXVECTOR3&)Scaling, &(const D3DXVECTOR3&)RotationCenter, &(const D3DXQUATERNION&)QuaternionRotation, &(const D3DXVECTOR3&)Translation);
}

#pragma endregion

#pragma region CreateScaling

void Matrix4::CreateScaling(Vector3& Scales, Matrix4& out)
{
	D3DXMatrixScaling(&out.M, Scales.X, Scales.Y, Scales.Z);
}

#pragma endregion

#pragma region CreateLookAt

void Matrix4::CreateLookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up, Matrix4& out)
{
	D3DXMatrixLookAtLH(&out.M, &(const D3DXVECTOR3&)Eye, &(const D3DXVECTOR3&)At, &(const D3DXVECTOR3&)Up);
}

#pragma endregion

#pragma region CreatePerspective

void Matrix4::CreatePerspective(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar, Matrix4& out)
{
	D3DXMatrixPerspectiveLH(&out.M, Width, Height, ZNear, ZFar);
}

#pragma endregion

#pragma region CreatePerspectiveFieldOfView

void Matrix4::CreatePerspectiveFieldOfView(FLOAT FOVY, FLOAT Aspect, FLOAT ZNear, FLOAT ZFar, Matrix4& out)
{
	D3DXMatrixPerspectiveFovLH(&out.M, FOVY, Aspect, ZNear, ZFar);
}

#pragma endregion

#pragma region CreatePerspectiveOffCenter

void Matrix4::CreatePerspectiveOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar, Matrix4& out)
{
	D3DXMatrixPerspectiveOffCenterLH(&out.M, Left, Right, Bottom, Top, ZNear, ZFar);
}

#pragma endregion

#pragma region CreateOrthographic

void Matrix4::CreateOrthographic(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar, Matrix4& out)
{
	D3DXMatrixOrthoLH(&out.M, Width, Height, ZNear, ZFar);
}

#pragma endregion

#pragma region CreateOrthographicOffCenter

void Matrix4::CreateOrthographicOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar, Matrix4& out)
{
	D3DXMatrixOrthoOffCenterLH(&out.M, Left, Right, Bottom, Top, ZNear, ZFar);
}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Rectangle

#pragma region Constructor

Rectangle::Rectangle()
{
	L = 0;
	T = 0;
	R = 0;
	B = 0;
}

Rectangle::Rectangle(Vector2 Pos, long Width, long Height)
{
	L = Pos.X;
	T = Pos.Y;
	R = L + Width;
	B = T + Height;
}

Rectangle::Rectangle(long Left, long Top, long Right, long Bottom)
{
	L = Left;
	T = Top;
	R = Right;
	B = Bottom;
}

#pragma endregion

#pragma region Operators

Rectangle::operator const RECT()
{
	RECT tmp;
	tmp.left = L;
	tmp.right = R;
	tmp.top = T;
	tmp.bottom = B;
	return tmp;
}

Rectangle::operator const RECT*()
{
	return (const RECT*)this;
}

#pragma endregion

#pragma region Methods

#pragma region Width

long Rectangle::Width()
{
	return L - R;
}

#pragma endregion

#pragma region Height

long Rectangle::Height()
{
	return T - B;
}

#pragma endregion

#pragma region Inflate

void Rectangle::Inflate(int PushX, int PushY)
{
	L -= PushX;
	R += PushX;
	T -= PushY;
	B += PushY;
}

#pragma endregion

#pragma region Intersects

BOOL Rectangle::Intersects(Rectangle rect)
{
	return (this->R > rect.L || this->L < rect.R || this->T > rect.B || this->B < rect.T) ? 1 : 0;
}

#pragma endregion

#pragma region Contains

BOOL Rectangle::Contains(Rectangle rect)
{
	return (this->L < rect.L && this->R > rect.R && this->T < rect.T && this->B > rect.B) ? 1 : 0;
}

#pragma endregion

#pragma region Intersect

Rectangle Rectangle::Intersect(Rectangle R1, Rectangle R2)
{
	Rectangle tmp;
	tmp.L = R1.L > R2.L ? R1.L : R2.L;
	tmp.L = R1.T > R2.T ? R1.T : R2.T;
	tmp.L = R1.R < R2.R ? R1.R : R2.R;
	tmp.L = R1.B < R2.B ? R1.B : R2.B;
	return tmp;
}

#pragma endregion

#pragma region Union

Rectangle Rectangle::Union(Rectangle R1, Rectangle R2)
{
	Rectangle tmp;
	tmp.L = R1.L < R2.L ? R1.L : R2.L;
	tmp.L = R1.T < R2.T ? R1.T : R2.T;
	tmp.L = R1.R > R2.R ? R1.R : R2.R;
	tmp.L = R1.B > R2.B ? R1.B : R2.B;
	return tmp;
}

#pragma endregion

#pragma region Intersects

BOOL Rectangle::Intersects(Rectangle R1, Rectangle R2)
{
	return (R1.R > R2.L || R1.L < R2.R || R1.T > R2.B || R1.B < R2.T) ? 1 : 0;
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Graphics

#pragma region Color

#pragma region Members

	const Color Color::Red		= Color(255,   0,   0);
	const Color Color::Green		= Color(0, 255,   0);
	const Color Color::Blue		= Color(  0,   0, 255);

	// Secondary
	const Color Color::Cyan		= Color(  0, 255, 255);
	const Color Color::Magenta	= Color(255,   0, 255);
	const Color Color::Yellow		= Color(255, 255,   0);

	// Black & White
	const Color Color::Black		= Color(  0,   0,   0);		
	const Color Color::White		= Color(255, 255, 255); 
	const Color Color::Gray		= Color(128, 128, 128); 

	// Grayscale
	const Color Color::LightGray	= Color( 64,  64,  64);	
	const Color Color::MiddleGray	= Color(128, 128, 128); 
	const Color Color::DarkGray	= Color(192, 192, 192); 

	// Misc. 
	// (mostly from en.wikipedia.org/wiki/List_of_colors) 
	const Color Color::Amethyst	= Color(153, 102, 204);	
	const Color Color::AppleGreen	= Color(141, 182,   0);	
	const Color Color::Aquamarine	= Color(127, 255, 212);	
	const Color Color::ArmyGreen	= Color( 75,  83,  32);	
	const Color Color::Arsenic	= Color( 59,  68,  75);	

	const Color Color::BabyBlue	= Color(137, 207, 240);	
	const Color Color::BabyPink	= Color(244, 194, 194);	
	const Color Color::Banana		= Color(255, 209,  42);	
	const Color Color::Brass		= Color(181, 166,  66);	
	const Color Color::BrickRed	= Color(203,  65,  84);	
	const Color Color::Bronze		= Color(205, 127,  50);	
	const Color Color::Brown		= Color(204, 119,  34);		
	const Color Color::BubbleGum	= Color(252, 193, 204);	
	const Color Color::Burgundy	= Color(128,   0,  32);	
	const Color Color::BurntUmber	= Color(138,  51,  36);	
	const Color Color::Byzantine	= Color(189,  51, 164);	

	const Color Color::CamoGreen	= Color(120, 134, 107);	
	const Color Color::Cardinal	= Color(196,  30,  58);	
	const Color Color::Carnation	= Color(255, 166, 201);	
	const Color Color::Carrot		= Color(237, 145,  33);	
	const Color Color::Cerulean	= Color(  0, 123, 167);	
	const Color Color::Chartreuse	= Color(223, 255,   0);	
	const Color Color::Cinnamon	= Color(210, 105,  30);	
	const Color Color::Cobalt		= Color(  0,  71, 171);	
	const Color Color::Copper		= Color(184, 115,  51);	
	const Color Color::Coral		= Color(255, 127,  80);	
	const Color Color::CornFlower	= Color(100, 149, 237);	
	const Color Color::CottonCandy= Color(255, 188, 217);	
	const Color Color::Crimson	= Color(220,  20,  60);	

	const Color Color::Daffodil	= Color(255, 255,  49);	
	const Color Color::Dandelion	= Color(240, 225,  48);	
	const Color Color::Denim		= Color( 21,  96, 189);	
	const Color Color::DollarBill	= Color(133, 187, 101);	

	const Color Color::Ecru		= Color(194, 178, 128);	
	const Color Color::Eggplant	= Color( 97,  64,  81);	
	const Color Color::Eggshell	= Color(240, 234, 214);	
	const Color Color::EgyptianBlue	= Color( 16,  52, 166);	
	const Color Color::Emerald	= Color( 80, 200, 120);	

	const Color Color::Fallow		= Color(193, 154, 107);	
	const Color Color::FaluRed	= Color(128,  24,  24);	
	const Color Color::Fandango	= Color(181,  51, 137);	
	const Color Color::FernGreen	= Color( 79, 121,  66);	
	const Color Color::FireEngine	= Color(206,  22,  32);	
	const Color Color::FlameOrange= Color(226,  88,  34);	
	const Color Color::FlamingoPink= Color(252, 142, 172);	
	const Color Color::FrenchBleu	= Color( 49, 140, 231);	
	const Color Color::Fuschia	= Color(245,   0, 245);		
	const Color Color::Fulvous	= Color(220, 132,   0);	

	const Color Color::Gamboge	= Color(228, 155,  15);	
	const Color Color::Glaucous	= Color( 96, 130, 182);	
	const Color Color::Gold		= Color(212, 175,  55);	
	const Color Color::GoldenRod	= Color(218, 165,  32);	
	const Color Color::GrannySmith= Color(168, 228, 160);	
	const Color Color::Grullo		= Color(169, 154, 134);	
	const Color Color::Guppie		= Color(  0, 255, 127);	

	const Color Color::Hazel		= Color(218, 145,   0);	
	const Color Color::Heliotrope	= Color(223, 115, 255);	
	const Color Color::Hooloovoo	= Color(100, 149, 237);	
	const Color Color::HunterGreen= Color( 53,  94,  59);	

	const Color Color::Iceberg	= Color(113, 166, 210);	
	const Color Color::Icterine	= Color(252, 247,  94);	
	const Color Color::Indigo		= Color( 75,   0, 130);	
	const Color Color::Iris		= Color( 90,  79, 207);	
	const Color Color::Isabelline	= Color(244, 240, 236);	
	const Color Color::IslamGreen	= Color(  0, 144,   0);	
	const Color Color::Ivory		= Color(255, 255, 240);	

	const Color Color::Jade		= Color(  0, 168, 107);	
	const Color Color::Jasper		= Color(215,  59,  62);	
	const Color Color::Jam		= Color(165,  11,  94);	
	const Color Color::Jonquil	= Color(250, 218,  94);	
	const Color Color::JuneBud	= Color(189, 218,  87);	
	const Color Color::JungleGreen= Color( 41, 171, 135);	

	const Color Color::LapisLazuli= Color( 46,   0, 140);	
	const Color Color::Lava		= Color(207,  16,  32);	
	const Color Color::Lavender	= Color(181, 126, 220);	
	const Color Color::Lemon		= Color(255, 247,   0);	
	const Color Color::LemonChiffon= Color(255, 250, 205);	
	const Color Color::Lilac		= Color(200, 162, 200);	
	const Color Color::Lime		= Color( 30, 205,  30);	
	const Color Color::Liver		= Color( 83,  75,  79);	
	const Color Color::LustRed	= Color(230,  32,  32);	

	const Color Color::MagicMint	= Color(170, 240, 209);	
	const Color Color::Magnolia	= Color(248, 244, 255);	
	const Color Color::Mahogany	= Color(192,  64,   0);	
	const Color Color::Maize		= Color(251, 236,  94);	
	const Color Color::Malachite	= Color( 11, 218,  81);	
	const Color Color::Maroon		= Color(176,  48,  96);	
	const Color Color::Mauve		= Color(224, 176, 255);	
	const Color Color::MidnightBlue= Color( 25,  25, 112);	
	const Color Color::MidnightGreen= Color(  0,  73,  83);		
	const Color Color::Mint		= Color( 62, 180, 137);	
	const Color Color::Moonstone	= Color(115, 169, 194);	
	const Color Color::MountainMaj= Color(150, 120, 182);	
	const Color Color::MullBerry	= Color(197,  75, 140);	
	const Color Color::Mustard	= Color(255, 219,  88);	
	const Color Color::Myrtle		= Color( 33,  66,  30);	

	const Color Color::NapierGreen= Color( 42, 128,   0);	
	const Color Color::NavyBlue	= Color(  0,   0, 128);		

	const Color Color::Ochre		= Color(204, 119,  34);	
	const Color Color::Olive		= Color(128, 128,   0);	
	const Color Color::Olivine	= Color(154, 185, 115);	
	const Color Color::Onyx		= Color( 15,  15,  15);	
	const Color Color::Orange		= Color(255, 127,   0);	
	const Color Color::Orchid		= Color(218, 112, 214);	

	const Color Color::Peach		= Color(255, 229, 180);	
	const Color Color::Pear		= Color(209, 226,  49);	
	const Color Color::Pearl		= Color(230, 226,   0);	
	const Color Color::Peridot	= Color(230, 226,   0);	
	const Color Color::Periwinkle	= Color(204, 204, 255);	
	const Color Color::Perisimmon	= Color(236,  88,   0);	
	const Color Color::Pink		= Color(255, 192, 203);			

	const Color Color::Pistachio	= Color(147, 197, 114);	
	const Color Color::Platinum	= Color(229, 228, 226);	
	const Color Color::Plum		= Color(142,  69, 133);	
	const Color Color::PowderBlue	= Color(176, 224, 230);	
	const Color Color::Puce		= Color(204, 136, 153);			
	const Color Color::Pumpkin	= Color(255, 117,  24);	
	const Color Color::Purple		= Color(128,   0, 128);	

	const Color Color::Raspberry	= Color(227,  11,  92);
	const Color Color::RawUmber	= Color(130, 102,  68);	
	const Color Color::Razzmatazz	= Color(227,  37, 107);	
	const Color Color::Redwood	= Color(171,  78,  82);
	const Color Color::Regalia	= Color( 82,  45, 128);	
	const Color Color::Rose		= Color(255,   0, 127);	
	const Color Color::Rosewood	= Color(101,   0,  11);	
	const Color Color::RossoCorsa	= Color(212,   0,   0);		
	const Color Color::RoyalAzure	= Color(  0,  56, 168);	
	const Color Color::RoyalBlue	= Color(  0,  35, 102);	
	const Color Color::RoyalFuschia= Color(202,  44, 146);			
	const Color Color::RoyalPurple= Color(107,  63, 160);	
	const Color Color::Ruby		= Color(224,  17,  95);	
	const Color Color::Ruddy		= Color(255,   0,  40);	
	const Color Color::Rufous		= Color(168,  28,   7);			
	const Color Color::Russet		= Color(128,  70,  27);	
	const Color Color::Rust		= Color(183,  65,  14);	

	const Color Color::SafetyOrange= Color(255, 103,   0);	
	const Color Color::Saffron	= Color(244, 196,  48);	
	const Color Color::Salmon		= Color(255, 140, 105);	
	const Color Color::Sand		= Color(194, 178, 128);	
	const Color Color::Sangria	= Color(146,   0,  10);	
	const Color Color::SapGreen	= Color( 80, 125,  42);	
	const Color Color::Sapphire	= Color(  8,  37, 103);	
	const Color Color::Scarlet	= Color(255,  32,   0);	
	const Color Color::SchoolBus	= Color(255, 216,   0);	
	const Color Color::SeaGreen	= Color( 46, 139,  87);	
	const Color Color::Sepia		= Color(112,  66,  20);	
	const Color Color::Sherbert	= Color(247, 143, 167);	
	const Color Color::Sienna		= Color(136,  45,  23);	
	const Color Color::Silver		= Color(192, 192, 192);	
	const Color Color::Sinopia	= Color(203,  65,  11);	
	const Color Color::Skobeloff	= Color(  0, 122, 116);	
	const Color Color::SkyBlue	= Color(135, 206, 235);	
	const Color Color::SlateGrey	= Color(112, 128, 144);	
	const Color Color::SpringGreen= Color(  0, 255, 127);	
	const Color Color::SteelBlue	= Color( 70, 130, 180);	
	const Color Color::Straw		= Color(228, 217, 111);	

	const Color Color::Tan		= Color(210, 180, 140);	
	const Color Color::Tangelo	= Color(249,  77,   0);	
	const Color Color::Tangerine	= Color(242, 133,   0);	
	const Color Color::Taupe		= Color( 72,  60,  50);	
	const Color Color::Teal		= Color(  0, 128, 128);	
	const Color Color::TerraCotta	= Color(226, 114,  91);	
	const Color Color::Thistle	= Color(216, 191, 216);	
	const Color Color::TickleMePink= Color(252, 137, 172);	
	const Color Color::TiffanyBlue= Color( 10, 186, 181);	
	const Color Color::Tomato		= Color(255,  99,  71);	
	const Color Color::Tumbleweed	= Color(222, 170, 136);	
	const Color Color::Turquoise	= Color( 48, 213, 200);	
	const Color Color::TuscanRed	= Color(130,  53,  53);	

	const Color Color::Umber		= Color( 99,  81,  71);	
	const Color Color::Urobilin	= Color(225, 173,  33);	

	const Color Color::Vanilla	= Color(243, 229, 171);	
	const Color Color::Vermillion	= Color(227,  66,  52);	
	const Color Color::Violet		= Color(143,   0, 255);	
	const Color Color::Viridian	= Color( 64, 130, 109);	

	const Color Color::Wenge		= Color(100,  84,  82);	
	const Color Color::Wheat		= Color(245, 222, 179);	
	const Color Color::Wisteria	= Color(201, 160, 220);	

	const Color Color::Xanadu		= Color(115, 134, 120);	

	const Color Color::YellowGreen= Color(154, 205,  50);	

	const Color Color::Zaffre		= Color(  0,  20, 168);	

#pragma endregion

#pragma region Constructor

Color::Color()
{
	R = 0;
	G = 0;
	B = 0;
	A = 0;
}

Color::Color(byte V)
{
	R = V;
	G = V;
	B = V;
	A = 255;
}

Color::Color(byte R, byte G, byte B)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = 255;
}

Color::Color(byte R, byte G, byte B, byte A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

#pragma endregion

#pragma region Methods

ulong Color::ToDword() { D3DCOLOR_ARGB(this->A, this->R, this->G, this->B); }

ulong Color::ToDword(byte R, byte G, byte B) { D3DCOLOR_ARGB(0xFF, R, G, B); }
ulong Color::ToDword(byte R, byte G, byte B, byte A) { D3DCOLOR_ARGB(A, R, G, B); }

#pragma endregion

#pragma endregion

#pragma region VertexDeclaration

VertexDeclaration::VertexDeclaration(VertexElement first, ...)
{
	std::vector<D3DVERTEXELEMENT9> elements;
	elements.push_back(first);
	va_list list;
	va_start(list, first);

	for(;;)
	{
		VertexElement tmp = va_arg(list, VertexElement);
		elements.push_back(tmp);

		if(tmp.Stream == 0xFF) break;
	}

	va_end(list);
	
	Device::CreateVertexDeclaration(elements.data(), &vd);
}

#pragma endregion

#pragma region VertexTypes

#pragma region P

VertexDeclaration V::P::Declaration
	(
		VertexElement(0, 0, V::Format::Vector3, V::Method::Default, V::Usage::Position, 0),
		VertexElement(0xFF, 0, V::Format::UnUsed, 0, 0, 0)
	);

#pragma endregion

#pragma region PC

VertexDeclaration V::PC::Declaration
(
	VertexElement(0, 0, V::Format::Vector3, V::Method::Default, V::Usage::Position, 0),
	VertexElement(0, 12, V::Format::Color, V::Method::Default, V::Usage::Color, 0),
	VertexElement(0xFF, 0, V::Format::UnUsed, 0, 0, 0)
);

#pragma endregion

#pragma region PT

VertexDeclaration V::PT::Declaration
(
	VertexElement(0, 0, V::Format::Vector3, V::Method::Default, V::Usage::Position, 0),
	VertexElement(0, 12, V::Format::Vector2, V::Method::Default, V::Usage::TextureCoordinate, 0),
	VertexElement(0xFF, 0, V::Format::UnUsed, 0, 0, 0)
);

#pragma endregion

#pragma endregion

#pragma region VertexBuffer

#pragma region Constructor

VertexBuffer::VertexBuffer(uint SizeInBytes, uint BufferUsage)
{
	Device::device->CreateVertexBuffer(SizeInBytes, BufferUsage, 0, D3DPOOL_MANAGED, &this->data, 0);
}

#pragma endregion

#pragma region SetData

void VertexBuffer::SetData(const void* data, uint BytesToCopy)
{
	this->data->Lock(0, 0, (void**)&Device::pVoid, 0);
	memcpy(Device::pVoid, data, BytesToCopy);
	this->data->Unlock();
}

#pragma endregion

#pragma endregion

#pragma region IndexBuffer

#pragma region Constructor

IndexBuffer::IndexBuffer(uint SizeInBytes, uint BufferUsage, DFormat IndexFormat)
{
	Device::device->CreateIndexBuffer(SizeInBytes, BufferUsage, IndexFormat, D3DPOOL_MANAGED, &this->data, 0);
}

#pragma endregion

#pragma region SetData

void IndexBuffer::SetData(const void* data, uint BytesToCopy)
{
	this->data->Lock(0, 0, (void**)&Device::pVoid, 0);
	memcpy(Device::pVoid, data, BytesToCopy);
	this->data->Unlock();
}

#pragma endregion

#pragma endregion

#pragma region DeviceManager

#pragma region Members

#pragma region private

BOOL DeviceManager::isfullscreen = !1;

#pragma endregion

#pragma region public

const BOOL          &DeviceManager::IsFullScreen = isfullscreen; /* Start FullScreen/Get Currently FullScreen */

uint                DeviceManager::BackBufferWidth = Device::Width;
uint                DeviceManager::BackBufferHeight = Device::Height;
D3DFORMAT           DeviceManager::BackBufferFormat = D3DFMT_X8R8G8B8;
uint                DeviceManager::BackBufferCount;
D3DMULTISAMPLE_TYPE DeviceManager::MultiSampleType;
ulong               DeviceManager::MultiSampleQuality;
D3DSWAPEFFECT       DeviceManager::SwapEffect = D3DSWAPEFFECT_DISCARD;
BOOL                DeviceManager::EnableAutoDepthStencil = 1;
D3DFORMAT           DeviceManager::AutoDepthStencilFormat = D3DFMT_D16;
ulong               DeviceManager::Flags;
uint                DeviceManager::FullScreen_RefreshRateInHz;
bool                DeviceManager::VSync = 1;

#pragma endregion

#pragma endregion

#pragma region Methods

#pragma region InitializeDevice

void DeviceManager::IntializeDevice()
{
	if(Window::hWnd != 0)
	{
		DestroyWindow(Window::hWnd);
		Device::Release();
	}
	Window::SetupWindow();
	
	PresentParameters pp;

	ZeroMemory(&pp, sizeof(pp));
	pp.AutoDepthStencilFormat = AutoDepthStencilFormat;
	pp.BackBufferCount = BackBufferCount;
	pp.BackBufferFormat = BackBufferFormat;
	pp.BackBufferHeight = BackBufferHeight;
	pp.BackBufferWidth = BackBufferWidth;
	pp.EnableAutoDepthStencil = EnableAutoDepthStencil;
	pp.Flags = Flags;
	pp.FullScreen_RefreshRateInHz = FullScreen_RefreshRateInHz;
	pp.hDeviceWindow = Window::hWnd;
	pp.MultiSampleQuality = MultiSampleQuality;
	pp.MultiSampleType = MultiSampleType;
	pp.SwapEffect = SwapEffect;
	pp.Windowed = !IsFullScreen;

	if(VSync) pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; else pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	
	Device::d3d = Direct3DCreate9(D3D_SDK_VERSION);
	Device::d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &Device::device);
	
}

#pragma endregion

#pragma region ApplyChanges

void DeviceManager::ApplyChanges()
{
	Device::Content->OnLostDevice();
	if(DeviceManager::isfullscreen)
	{
		SetWindowLong(Window::hWnd, GWL_STYLE, WS_EX_TOPMOST | WS_POPUP);
		SetWindowPos(Window::hWnd, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		PresentParameters pp;

		ZeroMemory(&pp, sizeof(pp));
		pp.AutoDepthStencilFormat = AutoDepthStencilFormat;
		pp.BackBufferCount = BackBufferCount;
		pp.BackBufferFormat = BackBufferFormat;
		pp.BackBufferHeight = BackBufferHeight;
		pp.BackBufferWidth = BackBufferWidth;
		pp.EnableAutoDepthStencil = EnableAutoDepthStencil;
		pp.Flags = Flags;
		pp.FullScreen_RefreshRateInHz = FullScreen_RefreshRateInHz;
		pp.hDeviceWindow = Window::hWnd;
		pp.MultiSampleQuality = MultiSampleQuality;
		pp.MultiSampleType = MultiSampleType;
		pp.SwapEffect = SwapEffect;
		pp.Windowed = !IsFullScreen;

		if(VSync) pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; else pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		Device::device->Reset(&pp);
	}

	if(!DeviceManager::isfullscreen)
	{
		SetWindowLong(Window::hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(Window::hWnd, HWND_NOTOPMOST, 0, 0, 800, 600, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);


		PresentParameters pp;

		ZeroMemory(&pp, sizeof(pp));
		pp.AutoDepthStencilFormat = AutoDepthStencilFormat;
		pp.BackBufferCount = BackBufferCount;
		pp.BackBufferFormat = BackBufferFormat;
		pp.BackBufferHeight = BackBufferHeight;
		pp.BackBufferWidth = BackBufferWidth;
		pp.EnableAutoDepthStencil = EnableAutoDepthStencil;
		pp.Flags = Flags;
		pp.FullScreen_RefreshRateInHz = FullScreen_RefreshRateInHz;
		pp.hDeviceWindow = Window::hWnd;
		pp.MultiSampleQuality = MultiSampleQuality;
		pp.MultiSampleType = MultiSampleType;
		pp.SwapEffect = SwapEffect;
		pp.Windowed = !IsFullScreen;

		if(VSync) pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; else pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		Device::device->Reset(&pp);

	}
	Device::Content->OnResetDevice();
	DeviceManager::isfullscreen = !DeviceManager::isfullscreen;
}
#pragma endregion

#pragma region ToggleFullScreen

void DeviceManager::ToggleFullScreen()
{
	Device::Content->OnLostDevice();
	if(!DeviceManager::isfullscreen)
	{
		SetWindowLong(Window::hWnd, GWL_STYLE, WS_EX_TOPMOST | WS_POPUP);
		SetWindowPos(Window::hWnd, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		PresentParameters pp;

		ZeroMemory(&pp, sizeof(pp));
		pp.AutoDepthStencilFormat = AutoDepthStencilFormat;
		pp.BackBufferCount = BackBufferCount;
		pp.BackBufferFormat = BackBufferFormat;
		pp.BackBufferHeight = BackBufferHeight;
		pp.BackBufferWidth = BackBufferWidth;
		pp.EnableAutoDepthStencil = EnableAutoDepthStencil;
		pp.Flags = Flags;
		pp.FullScreen_RefreshRateInHz = FullScreen_RefreshRateInHz;
		pp.hDeviceWindow = Window::hWnd;
		pp.MultiSampleQuality = MultiSampleQuality;
		pp.MultiSampleType = MultiSampleType;
		pp.SwapEffect = SwapEffect;
		pp.Windowed = IsFullScreen;

		if(VSync) pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; else pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		Device::device->Reset(&pp);
	}

	if(DeviceManager::isfullscreen)
	{
		SetWindowLong(Window::hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(Window::hWnd, HWND_NOTOPMOST, 0, 0, 800, 600, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);


		PresentParameters pp;

		ZeroMemory(&pp, sizeof(pp));
		pp.AutoDepthStencilFormat = AutoDepthStencilFormat;
		pp.BackBufferCount = BackBufferCount;
		pp.BackBufferFormat = BackBufferFormat;
		pp.BackBufferHeight = BackBufferHeight;
		pp.BackBufferWidth = BackBufferWidth;
		pp.EnableAutoDepthStencil = EnableAutoDepthStencil;
		pp.Flags = Flags;
		pp.FullScreen_RefreshRateInHz = FullScreen_RefreshRateInHz;
		pp.hDeviceWindow = Window::hWnd;
		pp.MultiSampleQuality = MultiSampleQuality;
		pp.MultiSampleType = MultiSampleType;
		pp.SwapEffect = SwapEffect;
		pp.Windowed = IsFullScreen;

		if(VSync) pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; else pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		Device::device->Reset(&pp);

	}
	Device::Content->OnResetDevice();
	DeviceManager::isfullscreen = !DeviceManager::isfullscreen;
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region GraphicDevice

#pragma region Members

#pragma region private

LPDIRECT3D9 Device::d3d = Direct3DCreate9(D3D_SDK_VERSION);
LPDIRECT3DDEVICE9 Device::device;

void* Device::pVoid;

#pragma endregion

#pragma region public

int Device::Width = 800;
int Device::Height = 600;

VertexStreamCollection Device::Streams;
ContentManager* Device::Content;

#pragma endregion

#pragma endregion

#pragma region Methods

#pragma region private

#pragma region CreateVertexDeclaration

void Device::CreateVertexDeclaration(const D3DVERTEXELEMENT9* elements, LPDIRECT3DVERTEXDECLARATION9* vd)
{
	if(Device::device == 0)	
		DeviceManager::IntializeDevice();
	
	device->CreateVertexDeclaration(elements, vd);
}

#pragma endregion

#pragma endregion

#pragma region public 

#pragma region Scene

void Device::BeginScene()
{
	Device::device->BeginScene();
}

void Device::EndScene()
{
	Device::device->EndScene();
	Device::device->Present(0, 0, 0, 0);
}

#pragma endregion

#pragma region Clear

void Device::Clear(Color col)
{
	
}
void Device::Clear(ulong flags, Color col, float depth, ulong stencil)
{
	Device::device->Clear(0, 0, flags, col.ToDword(), depth, stencil);
}
void Device::Clear(ulong flags, Color col, float depth, ulong stencil, const D3DRECT* rects, ulong count)
{
	Device::device->Clear(count, rects, flags, col.ToDword(), depth, stencil);
}

#pragma endregion

#pragma region RenderTarget

#pragma endregion

#pragma region Release

void Device::Release()
{
	device != 0 ? device->Release() : 0;
	d3d != 0 ? d3d->Release() : 0;

	device = 0;
	d3d = 0;
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region RenderState

#pragma region Members
	
	Device::RenderState::RenderStateSetting Device::RenderState::ZENABLE                   = Device::RenderState::RenderStateSetting((RenderStateType)7);    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
	Device::RenderState::RenderStateSetting Device::RenderState::FILLMODE                  = Device::RenderState::RenderStateSetting((RenderStateType)8);    /* D3DFILLMODE */
	Device::RenderState::RenderStateSetting Device::RenderState::SHADEMODE                 = Device::RenderState::RenderStateSetting((RenderStateType)9);    /* D3DSHADEMODE */
	Device::RenderState::RenderStateSetting Device::RenderState::ZWRITEENABLE              = Device::RenderState::RenderStateSetting((RenderStateType)14);   /* TRUE to enable z writes */
	Device::RenderState::RenderStateSetting Device::RenderState::ALPHATESTENABLE           = Device::RenderState::RenderStateSetting((RenderStateType)15);   /* TRUE to enable alpha tests */
	Device::RenderState::RenderStateSetting Device::RenderState::LASTPIXEL                 = Device::RenderState::RenderStateSetting((RenderStateType)16);   /* TRUE for last-pixel on lines */
	Device::RenderState::RenderStateSetting Device::RenderState::SRCBLEND                  = Device::RenderState::RenderStateSetting((RenderStateType)19);   /* D3DBLEND */
	Device::RenderState::RenderStateSetting Device::RenderState::DESTBLEND                 = Device::RenderState::RenderStateSetting((RenderStateType)20);   /* D3DBLEND */
	Device::RenderState::RenderStateSetting Device::RenderState::CULLMODE                  = Device::RenderState::RenderStateSetting((RenderStateType)22);   /* D3DCULL */
	Device::RenderState::RenderStateSetting Device::RenderState::ZFUNC                     = Device::RenderState::RenderStateSetting((RenderStateType)23);   /* D3DCMPFUNC */
	Device::RenderState::RenderStateSetting Device::RenderState::ALPHAREF                  = Device::RenderState::RenderStateSetting((RenderStateType)24);   /* D3DFIXED */
	Device::RenderState::RenderStateSetting Device::RenderState::ALPHAFUNC                 = Device::RenderState::RenderStateSetting((RenderStateType)25);   /* D3DCMPFUNC */
	Device::RenderState::RenderStateSetting Device::RenderState::DITHERENABLE              = Device::RenderState::RenderStateSetting((RenderStateType)26);   /* TRUE to enable dithering */
	Device::RenderState::RenderStateSetting Device::RenderState::ALPHABLENDENABLE          = Device::RenderState::RenderStateSetting((RenderStateType)27);   /* TRUE to enable alpha blending */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGENABLE                 = Device::RenderState::RenderStateSetting((RenderStateType)28);   /* TRUE to enable fog blending */
	Device::RenderState::RenderStateSetting Device::RenderState::SPECULARENABLE            = Device::RenderState::RenderStateSetting((RenderStateType)29);   /* TRUE to enable specular */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGCOLOR                  = Device::RenderState::RenderStateSetting((RenderStateType)34);   /* D3DCOLOR */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGTABLEMODE              = Device::RenderState::RenderStateSetting((RenderStateType)35);   /* D3DFOGMODE */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGSTART                  = Device::RenderState::RenderStateSetting((RenderStateType)36);   /* Fog start (for both vertex and pixel fog) */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGEND                    = Device::RenderState::RenderStateSetting((RenderStateType)37);   /* Fog end      */
	Device::RenderState::RenderStateSetting Device::RenderState::FOGDENSITY                = Device::RenderState::RenderStateSetting((RenderStateType)38);   /* Fog density  */
	Device::RenderState::RenderStateSetting Device::RenderState::RANGEFOGENABLE            = Device::RenderState::RenderStateSetting((RenderStateType)48);   /* Enables range-based fog */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILENABLE             = Device::RenderState::RenderStateSetting((RenderStateType)52);   /* BOOL enable/disable stenciling */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILFAIL               = Device::RenderState::RenderStateSetting((RenderStateType)53);   /* D3DSTENCILOP to do if stencil test fails */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILZFAIL              = Device::RenderState::RenderStateSetting((RenderStateType)54);   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILPASS               = Device::RenderState::RenderStateSetting((RenderStateType)55);   /* D3DSTENCILOP to do if both stencil and Z tests pass */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILFUNC               = Device::RenderState::RenderStateSetting((RenderStateType)56);   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILREF                = Device::RenderState::RenderStateSetting((RenderStateType)57);   /* Reference value used in stencil test */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILMASK               = Device::RenderState::RenderStateSetting((RenderStateType)58);   /* Mask value used in stencil test */
	Device::RenderState::RenderStateSetting Device::RenderState::STENCILWRITEMASK          = Device::RenderState::RenderStateSetting((RenderStateType)59);   /* Write mask applied to values written to stencil buffer */
	Device::RenderState::RenderStateSetting Device::RenderState::TEXTUREFACTOR             = Device::RenderState::RenderStateSetting((RenderStateType)60);   /* D3DCOLOR used for multi-texture blend */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP0                     = Device::RenderState::RenderStateSetting((RenderStateType)128);  /* wrap for 1st texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP1                     = Device::RenderState::RenderStateSetting((RenderStateType)129);  /* wrap for 2nd texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP2                     = Device::RenderState::RenderStateSetting((RenderStateType)130);  /* wrap for 3rd texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP3                     = Device::RenderState::RenderStateSetting((RenderStateType)131);  /* wrap for 4th texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP4                     = Device::RenderState::RenderStateSetting((RenderStateType)132);  /* wrap for 5th texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP5                     = Device::RenderState::RenderStateSetting((RenderStateType)133);  /* wrap for 6th texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP6                     = Device::RenderState::RenderStateSetting((RenderStateType)134);  /* wrap for 7th texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP7                     = Device::RenderState::RenderStateSetting((RenderStateType)135);  /* wrap for 8th texture coord. set */
	Device::RenderState::RenderStateSetting Device::RenderState::CLIPPING                  = Device::RenderState::RenderStateSetting((RenderStateType)136);
	Device::RenderState::RenderStateSetting Device::RenderState::LIGHTING                  = Device::RenderState::RenderStateSetting((RenderStateType)137);
	Device::RenderState::RenderStateSetting Device::RenderState::AMBIENT                   = Device::RenderState::RenderStateSetting((RenderStateType)139);
	Device::RenderState::RenderStateSetting Device::RenderState::FOGVERTEXMODE             = Device::RenderState::RenderStateSetting((RenderStateType)140);
	Device::RenderState::RenderStateSetting Device::RenderState::COLORVERTEX               = Device::RenderState::RenderStateSetting((RenderStateType)141);
	Device::RenderState::RenderStateSetting Device::RenderState::LOCALVIEWER               = Device::RenderState::RenderStateSetting((RenderStateType)142);
	Device::RenderState::RenderStateSetting Device::RenderState::NORMALIZENORMALS          = Device::RenderState::RenderStateSetting((RenderStateType)143);
	Device::RenderState::RenderStateSetting Device::RenderState::DIFFUSEMATERIALSOURCE     = Device::RenderState::RenderStateSetting((RenderStateType)145);
	Device::RenderState::RenderStateSetting Device::RenderState::SPECULARMATERIALSOURCE    = Device::RenderState::RenderStateSetting((RenderStateType)146);
	Device::RenderState::RenderStateSetting Device::RenderState::AMBIENTMATERIALSOURCE     = Device::RenderState::RenderStateSetting((RenderStateType)147);
	Device::RenderState::RenderStateSetting Device::RenderState::EMISSIVEMATERIALSOURCE    = Device::RenderState::RenderStateSetting((RenderStateType)148);
	Device::RenderState::RenderStateSetting Device::RenderState::VERTEXBLEND               = Device::RenderState::RenderStateSetting((RenderStateType)151);
	Device::RenderState::RenderStateSetting Device::RenderState::CLIPPLANEENABLE           = Device::RenderState::RenderStateSetting((RenderStateType)152);
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSIZE                 = Device::RenderState::RenderStateSetting((RenderStateType)154);   /* float point size */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSIZE_MIN             = Device::RenderState::RenderStateSetting((RenderStateType)155);   /* float point size min threshold */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSPRITEENABLE         = Device::RenderState::RenderStateSetting((RenderStateType)156);   /* BOOL point texture coord control */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSCALEENABLE          = Device::RenderState::RenderStateSetting((RenderStateType)157);   /* BOOL point size scale enable */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSCALE_A              = Device::RenderState::RenderStateSetting((RenderStateType)158);   /* float point attenuation A value */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSCALE_B              = Device::RenderState::RenderStateSetting((RenderStateType)159);   /* float point attenuation B value */
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSCALE_C              = Device::RenderState::RenderStateSetting((RenderStateType)160);   /* float point attenuation C value */
	Device::RenderState::RenderStateSetting Device::RenderState::MULTISAMPLEANTIALIAS      = Device::RenderState::RenderStateSetting((RenderStateType)161);  // BOOL - set to do FSAA with multisample buffer
	Device::RenderState::RenderStateSetting Device::RenderState::MULTISAMPLEMASK           = Device::RenderState::RenderStateSetting((RenderStateType)162);  // DWORD - per-sample enable/disable
	Device::RenderState::RenderStateSetting Device::RenderState::PATCHEDGESTYLE            = Device::RenderState::RenderStateSetting((RenderStateType)163);  // Sets whether patch edges will use float style tessellation
	Device::RenderState::RenderStateSetting Device::RenderState::DEBUGMONITORTOKEN         = Device::RenderState::RenderStateSetting((RenderStateType)165);  // DEBUG ONLY - token to debug monitor
	Device::RenderState::RenderStateSetting Device::RenderState::POINTSIZE_MAX             = Device::RenderState::RenderStateSetting((RenderStateType)166);   /* float point size max threshold */
	Device::RenderState::RenderStateSetting Device::RenderState::INDEXEDVERTEXBLENDENABLE  = Device::RenderState::RenderStateSetting((RenderStateType)167);
	Device::RenderState::RenderStateSetting Device::RenderState::COLORWRITEENABLE          = Device::RenderState::RenderStateSetting((RenderStateType)168);  // per-channel write enable
	Device::RenderState::RenderStateSetting Device::RenderState::TWEENFACTOR               = Device::RenderState::RenderStateSetting((RenderStateType)170);   // float tween factor
	Device::RenderState::RenderStateSetting Device::RenderState::BLENDOP                   = Device::RenderState::RenderStateSetting((RenderStateType)171);   // D3DBLENDOP setting
	Device::RenderState::RenderStateSetting Device::RenderState::POSITIONDEGREE            = Device::RenderState::RenderStateSetting((RenderStateType)172);   // NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
	Device::RenderState::RenderStateSetting Device::RenderState::NORMALDEGREE              = Device::RenderState::RenderStateSetting((RenderStateType)173);   // NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
	Device::RenderState::RenderStateSetting Device::RenderState::SCISSORTESTENABLE         = Device::RenderState::RenderStateSetting((RenderStateType)174);
	Device::RenderState::RenderStateSetting Device::RenderState::SLOPESCALEDEPTHBIAS       = Device::RenderState::RenderStateSetting((RenderStateType)175);
	Device::RenderState::RenderStateSetting Device::RenderState::ANTIALIASEDLINEENABLE     = Device::RenderState::RenderStateSetting((RenderStateType)176);
	Device::RenderState::RenderStateSetting Device::RenderState::MINTESSELLATIONLEVEL      = Device::RenderState::RenderStateSetting((RenderStateType)178);
	Device::RenderState::RenderStateSetting Device::RenderState::MAXTESSELLATIONLEVEL      = Device::RenderState::RenderStateSetting((RenderStateType)179);
	Device::RenderState::RenderStateSetting Device::RenderState::ADAPTIVETESS_X            = Device::RenderState::RenderStateSetting((RenderStateType)180);
	Device::RenderState::RenderStateSetting Device::RenderState::ADAPTIVETESS_Y            = Device::RenderState::RenderStateSetting((RenderStateType)181);
	Device::RenderState::RenderStateSetting Device::RenderState::ADAPTIVETESS_Z            = Device::RenderState::RenderStateSetting((RenderStateType)182);
	Device::RenderState::RenderStateSetting Device::RenderState::ADAPTIVETESS_W            = Device::RenderState::RenderStateSetting((RenderStateType)183);
	Device::RenderState::RenderStateSetting Device::RenderState::ENABLEADAPTIVETESSELLATION= Device::RenderState::RenderStateSetting((RenderStateType)184);
	Device::RenderState::RenderStateSetting Device::RenderState::TWOSIDEDSTENCILMODE       = Device::RenderState::RenderStateSetting((RenderStateType)185);   /* BOOL enable/disable 2 sided stenciling */
	Device::RenderState::RenderStateSetting Device::RenderState::CCW_STENCILFAIL           = Device::RenderState::RenderStateSetting((RenderStateType)186);   /* D3DSTENCILOP to do if ccw stencil test fails */
	Device::RenderState::RenderStateSetting Device::RenderState::CCW_STENCILZFAIL          = Device::RenderState::RenderStateSetting((RenderStateType)187);   /* D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
	Device::RenderState::RenderStateSetting Device::RenderState::CCW_STENCILPASS           = Device::RenderState::RenderStateSetting((RenderStateType)188);   /* D3DSTENCILOP to do if both ccw stencil and Z tests pass */
	Device::RenderState::RenderStateSetting Device::RenderState::CCW_STENCILFUNC           = Device::RenderState::RenderStateSetting((RenderStateType)189);   /* D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
	Device::RenderState::RenderStateSetting Device::RenderState::COLORWRITEENABLE1         = Device::RenderState::RenderStateSetting((RenderStateType)190);   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
	Device::RenderState::RenderStateSetting Device::RenderState::COLORWRITEENABLE2         = Device::RenderState::RenderStateSetting((RenderStateType)191);   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
	Device::RenderState::RenderStateSetting Device::RenderState::COLORWRITEENABLE3         = Device::RenderState::RenderStateSetting((RenderStateType)192);   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
	Device::RenderState::RenderStateSetting Device::RenderState::BLENDFACTOR               = Device::RenderState::RenderStateSetting((RenderStateType)193);   /* D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
	Device::RenderState::RenderStateSetting Device::RenderState::SRGBWRITEENABLE           = Device::RenderState::RenderStateSetting((RenderStateType)194);   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
	Device::RenderState::RenderStateSetting Device::RenderState::DEPTHBIAS                 = Device::RenderState::RenderStateSetting((RenderStateType)195);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP8                     = Device::RenderState::RenderStateSetting((RenderStateType)198);   /* Additional wrap states for vs_3_0+ attributes with D3DDECLUSAGE_TEXCOORD */
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP9                     = Device::RenderState::RenderStateSetting((RenderStateType)199);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP10                    = Device::RenderState::RenderStateSetting((RenderStateType)200);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP11                    = Device::RenderState::RenderStateSetting((RenderStateType)201);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP12                    = Device::RenderState::RenderStateSetting((RenderStateType)202);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP13                    = Device::RenderState::RenderStateSetting((RenderStateType)203);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP14                    = Device::RenderState::RenderStateSetting((RenderStateType)204);
	Device::RenderState::RenderStateSetting Device::RenderState::WRAP15                    = Device::RenderState::RenderStateSetting((RenderStateType)205);
	Device::RenderState::RenderStateSetting Device::RenderState::SEPARATEALPHABLENDENABLE  = Device::RenderState::RenderStateSetting((RenderStateType)206);  /* TRUE to enable a separate blending function for the alpha channel */
	Device::RenderState::RenderStateSetting Device::RenderState::SRCBLENDALPHA             = Device::RenderState::RenderStateSetting((RenderStateType)207);  /* SRC blend factor for the alpha channel when GraphicsDevice::RenderState::RenderStateSetting GraphicsDevice::RenderState::SEPARATEDESTALPHAENABLE is TRUE */
	Device::RenderState::RenderStateSetting Device::RenderState::DESTBLENDALPHA            = Device::RenderState::RenderStateSetting((RenderStateType)208);  /* DST blend factor for the alpha channel when GraphicsDevice::RenderState::RenderStateSetting GraphicsDevice::RenderState::SEPARATEDESTALPHAENABLE is TRUE */
	Device::RenderState::RenderStateSetting Device::RenderState::BLENDOPALPHA              = Device::RenderState::RenderStateSetting((RenderStateType)209);  /* Blending operation for the alpha channel when GraphicsDevice::RenderState::RenderStateSetting GraphicsDevice::RenderState::SEPARATEDESTALPHAENABLE is TRUE */

	Device::RenderState::RenderStateSetting Device::RenderState::FORCE_DWORD               = Device::RenderState::RenderStateSetting((RenderStateType)0x7fffffff); /* force 32-bit size enum */

#pragma endregion

#pragma endregion

#pragma endregion
	
#pragma region VertexStream
	
#pragma region Constructor

VertexStream::VertexStream(UINT stream)
{
	this->stream = stream;
	this->buffer = 0;
	this->stream = 0;
	this->stride = 0;
}

#pragma endregion

#pragma region SetSource

void VertexStream::SetSource(VertexBuffer* Buffer, UINT OffsetInBytes, UINT VertexStride)
{
	this->buffer = Buffer;
	this->offset = OffsetInBytes;
	this->stride = VertexStride;
	if(this->buffer != 0) Device::device->SetStreamSource(stream, buffer->data, offset, stride);
	else Device::device->SetStreamSource(stream, 0, 0, 0);
}

#pragma endregion

#pragma region SetSourceFrequency

void VertexStream::SetSourceFrequency(UINT Frequency)
{
	Device::device->SetStreamSourceFreq(stream, Frequency);
}

#pragma endregion

#pragma region VertexBuffer

VertexBuffer* VertexStream::Buffer()
{
	return buffer;
}

#pragma endregion

#pragma region OffsetInBytes

UINT VertexStream::OffsetInBytes()
{
	return offset;
}

#pragma endregion

#pragma region VertexStride

UINT VertexStream::VertexStride()
{
	return stride;
}

#pragma endregion

#pragma endregion

#pragma region Content

#pragma region Effect
	
#pragma region IContent

#pragma region Lost

void Effect::Lost()	
{
	this->Data->OnLostDevice();
}

#pragma endregion

#pragma region Reset

void Effect::Reset()
{
	this->Data->OnResetDevice();
}

#pragma endregion

#pragma region Release

void Effect::Release()
{
	this->Data->Release();
	delete this;
}

#pragma endregion

#pragma region GetPath

std::wstring Effect::GetPath()
{
	return Path;
}

#pragma endregion

#pragma endregion

#pragma region Load

Effect* Effect::Load(std::wstring path)
{
	Effect* tmp = new Effect;
	tmp->Path = path;
	LPD3DXBUFFER error;
	D3DXHANDLE technique;
	D3DXCreateEffectFromFileW(Device::device, tmp->Path.c_str(), 0, 0, 0, 0, &tmp->Data, &error);
	if(error != 0) throw error->GetBufferPointer(); else tmp->Data->FindNextValidTechnique(0, &technique);
	return tmp;
}

#pragma endregion

#pragma region Begin

void Effect::Begin()
{
	this->Data->Begin(0, 0);
	this->Data->BeginPass(0);
}

#pragma endregion

#pragma region End

void Effect::End()
{
	this->Data->EndPass();
	this->Data->End();
}

#pragma endregion

#pragma endregion

#pragma region Texture2D

#pragma region IContent

#pragma region Lost

void Texture2D::Lost()	
{

}

#pragma endregion

#pragma region Reset

void Texture2D::Reset()
{
	
}

#pragma endregion

#pragma region Release

void Texture2D::Release()
{
	this->Data->Release();
	delete this;
}

#pragma endregion

#pragma region GetPath

std::wstring Texture2D::GetPath()
{
	return Path;
}

#pragma endregion

#pragma endregion

#pragma region Load

Texture2D* Texture2D::Load(std::wstring path)
{
	Texture2D* tmp = new Texture2D;
	tmp->Path = path;
	D3DXIMAGE_INFO i;
	D3DXCreateTextureFromFileExW(Device::device, tmp->Path.c_str(), 0, 0, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0xFFFF00FF, &i, 0, &tmp->Data);
	tmp->width = i.Width;
	tmp->height = i.Height;
	return tmp;
}

#pragma endregion

#pragma region Width

uint Texture2D::Width()
{
	return this->width;
}

#pragma endregion

#pragma region Height

uint Texture2D::Height()
{
	return this->height;
}

#pragma endregion

#pragma endregion

#pragma region Texture3D

#pragma region IContent

#pragma region Lost

void Texture3D::Lost()	
{

}

#pragma endregion

#pragma region Reset

void Texture3D::Reset()
{
	
}

#pragma endregion

#pragma region Release

void Texture3D::Release()
{
	this->Data->Release();
	delete this;
}

#pragma endregion

#pragma region GetPath

std::wstring Texture3D::GetPath()
{
	return Path;
}

#pragma endregion

#pragma endregion

#pragma region Load

Texture3D* Texture3D::Load(std::wstring path)
{
	Texture3D* tmp = new Texture3D;
	tmp->Path = path;
	D3DXIMAGE_INFO i;
	D3DXCreateVolumeTextureFromFileExW(Device::device, tmp->Path.c_str(), 0, 0, 0, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0xFFFF00FF, &i, 0, &tmp->Data);
	tmp->width = i.Width;
	tmp->height = i.Height;
	tmp->depth = i.Depth;
	return tmp;
}

#pragma endregion

#pragma region Width

uint Texture3D::Width()
{
	return this->width;
}

#pragma endregion

#pragma region Height

uint Texture3D::Height()
{
	return this->height;
}

#pragma endregion

#pragma region Depth

uint Texture3D::Depth()
{
	return this->depth;
}

#pragma endregion

#pragma endregion

#pragma region TextureCube

#pragma endregion

#pragma endregion

#pragma region ContentManager

#pragma region OnLostDevice

void ContentManager::OnLostDevice()
{
	for(uint i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Lost();
	}
}

#pragma endregion

#pragma region OnResetDevice

void ContentManager::OnResetDevice()
{
	for(uint i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Reset();
	}
}

#pragma endregion

#pragma region UnloadContent

void ContentManager::UnloadContent()
{
	for(uint i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Release();
	}
}

#pragma endregion

#pragma endregion

#pragma region RenderTarget2D

#pragma region Constructor


#pragma endregion

#pragma endregion

#pragma region RenderTargetCube

#pragma region Constructor

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Audio

#pragma endregion

#pragma region Input

#pragma region InitializeInput

void Input::Initialize()
{
	RAWINPUTDEVICE Device;

    Device.usUsage = 0x02;
    Device.usUsagePage = 0x01;
    Device.dwFlags = 0;
	Device.hwndTarget = 0;

    RegisterRawInputDevices(&Device, 1, sizeof(RAWINPUTDEVICE));
}

#pragma endregion

#pragma region Mouse

#pragma region Members

MouseState Mouse::Cur;
MouseState Mouse::Pre;

#pragma endregion

#pragma region Methods

void Mouse::Update()
{
	Pre = Cur;
	POINT p;
	GetCursorPos(&p);
	Cur.Position.X = (FLOAT)p.x;
	Cur.Position.Y = (FLOAT)p.y;
}

#pragma endregion

#pragma endregion

#pragma region KeyboardState

#pragma region KeyUp

bool KeyboardState::KeyUp(BYTE key)
{
	return !(StateData[key] & 0x80);
}

#pragma endregion

#pragma region KeyDown

bool KeyboardState::KeyDown(BYTE key)
{
	return StateData[key] & 0x80;
}

#pragma endregion

#pragma endregion

#pragma region Keyboard

#pragma region Members

KeyboardState Keyboard::Cur;
KeyboardState Keyboard::Pre;

#pragma endregion

#pragma region Methods

void Keyboard::Update()
{
    Pre = Cur;
	GetKeyState(0);
	GetKeyboardState(Cur.StateData);
	Cur.CapsLock = Cur.StateData[0x14] & 0x1;
	Cur.ScrLock = Cur.StateData[0x91] & 0x1;
	Cur.NumLock = Cur.StateData[0x90] & 0x1;
}

bool Keyboard::KeyPressed(BYTE Key)
{
	return Cur.KeyDown(Key) && Pre.KeyUp(Key);
}

#pragma endregion

#pragma endregion

#pragma region GamePads

#pragma region Members

GamePads GamePads::Pads[4];

#pragma endregion

#pragma region Methods

void GamePads::Update()
{
	uint connected;
	for(uint i = 0; i < 4; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		connected = XInputGetState(i, &state);

		if(connected == ERROR_SUCCESS)
		{
			if(Pads[i].Pre.PacketNumber != state.dwPacketNumber)
			{
				Pads[i].Cur.PacketNumber = state.dwPacketNumber;
				Pads[i].Pre = Pads[i].Cur;
				Pads[i].Cur.DPad.Up    = state.Gamepad.wButtons & 0x00000001;
				Pads[i].Cur.DPad.Down  = state.Gamepad.wButtons & 0x00000002;
				Pads[i].Cur.DPad.Left  = state.Gamepad.wButtons & 0x00000004;
				Pads[i].Cur.DPad.Right = state.Gamepad.wButtons & 0x00000008;

				Pads[i].Cur.Start = state.Gamepad.wButtons & 0x00000010;
				Pads[i].Cur.Back  = state.Gamepad.wButtons & 0x00000020;

				Pads[i].Cur.Left.Click  = state.Gamepad.wButtons & 0x00000040;
				Pads[i].Cur.Right.Click = state.Gamepad.wButtons & 0x00000080;

				Pads[i].Cur.Left.Bumper  = state.Gamepad.wButtons & 0x00000100;
				Pads[i].Cur.Right.Bumper = state.Gamepad.wButtons & 0x00000200;

				Pads[i].Cur.A = state.Gamepad.wButtons & 0x00001000;
				Pads[i].Cur.B = state.Gamepad.wButtons & 0x00002000;
				Pads[i].Cur.X = state.Gamepad.wButtons & 0x00004000;
				Pads[i].Cur.Y = state.Gamepad.wButtons & 0x00008000;

				
				Pads[i].Cur.Left.Thumb.X = state.Gamepad.sThumbLX / 32767.0f;
				Pads[i].Cur.Left.Thumb.Y = state.Gamepad.sThumbLY / 32767.0f;

				Pads[i].Cur.Right.Thumb.X = state.Gamepad.sThumbRX / 32767.0f;
				Pads[i].Cur.Right.Thumb.Y = state.Gamepad.sThumbRY / 32767.0f;

				if (Pads[i].Cur.Left.Trigger > 0)  Pads[i].Cur.Left.Trigger  = (state.Gamepad.bLeftTrigger  - 30)  / 225.0f; else Pads[i].Cur.Left.Trigger  = 0;
				if (Pads[i].Cur.Right.Trigger > 0) Pads[i].Cur.Right.Trigger = (state.Gamepad.bRightTrigger - 30) / 225.0f; else Pads[i].Cur.Right.Trigger = 0;

				XINPUT_VIBRATION tmp;
				tmp.wLeftMotorSpeed = (WORD)floor(Pads[i].Cur.Left.Motor * 32767);
				tmp.wRightMotorSpeed = (WORD)floor(Pads[i].Cur.Right.Motor * 32767);
				XInputSetState(i, &tmp);
			}
		}
		else
		{
			Pads[i].Pre = Pads[i].Cur;
			Pads[i].Cur.DPad.Up    = 0;
			Pads[i].Cur.DPad.Down  = 0;
			Pads[i].Cur.DPad.Left  = 0;
			Pads[i].Cur.DPad.Right = 0;

			Pads[i].Cur.Start = 0;
			Pads[i].Cur.Back  = 0;

			Pads[i].Cur.Left.Click  = 0;
			Pads[i].Cur.Right.Click = 0;

			Pads[i].Cur.Left.Bumper  = 0;
			Pads[i].Cur.Right.Bumper = 0;

			Pads[i].Cur.A = 0;
			Pads[i].Cur.B = 0;
			Pads[i].Cur.X = 0;
			Pads[i].Cur.Y = 0;

			Pads[i].Cur.Left.Thumb.X = 0.0f;
			Pads[i].Cur.Left.Thumb.Y = 0.0f;

			Pads[i].Cur.Right.Thumb.X = 0.0f;
			Pads[i].Cur.Right.Thumb.Y = 0.0f;

			Pads[i].Cur.Left.Trigger  = 0.0f;
			Pads[i].Cur.Right.Trigger = 0.0f;

			Pads[i].Cur.Left.Motor = 0.0f;
			Pads[i].Cur.Right.Motor = 0.0f;
		}
	}
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Multiplayer

#pragma endregion

}