#ifndef DirectN_H
#define DirectN_H

#pragma region Header

#include <vector>
#include <string>

#include <windows.h>
#include <windowsx.h>

#include <d3dx9.h>
#include <XInput.h>
#include <XAudio2.h>

#pragma endregion

namespace DirectN
{

#pragma region typedef

typedef _D3DPRESENT_PARAMETERS_ PresentParameters;

typedef _D3DRENDERSTATETYPE RenderStateType;

typedef _D3DPRIMITIVETYPE DPrimitiveType;
typedef _D3DFORMAT        DFormat;

typedef WORD ushort;
typedef DWORD ulong;
typedef UINT uint;
typedef BYTE byte;

#pragma endregion

#pragma region Global

extern void CleanUp();

#pragma endregion

#pragma region Windows

#pragma region Window

class Window
{
	friend class DeviceManager;

	#pragma region private

	private:

	#pragma region Members

	static bool MLeft;
	static bool MRight;
	static bool MMiddle;
	static USHORT MWheel;

	#pragma endregion

	#pragma region Methods

	inline static void CreateFullScreen();
	inline static void CreateWindowed();

	#pragma endregion

	#pragma endregion

	#pragma region public

	public:

	#pragma region Members

	static HWND hWnd;

	#pragma endregion

	#pragma region Methods

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void SetupWindow();

	#pragma endregion

	#pragma endregion
};

#pragma endregion

#pragma region WindowClass

class WindowClass
{
	
	#pragma region public

	public:

	#pragma region Members

	static HINSTANCE hInstance;
	static HCURSOR hCursor;
	static LPCTSTR WindowName; /* Name for the WINDOW, not the Class. Classname is always "freshman". WindowName defaults to "freshman 2.0" */
	static HICON hIcon;
	static uint Style;

	static WNDPROC WindowProcFunction;

	#pragma endregion

	#pragma endregion
};

#pragma endregion

#pragma endregion

#pragma region Math

#pragma region Vector2

class Vector2
{
	public:
	
	FLOAT X;
	FLOAT Y;

	#pragma region Constructor

	Vector2()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
	}
	Vector2(FLOAT X, FLOAT Y)
	{
		this->X = X;
		this->Y = Y;
	}
	Vector2(FLOAT Val)
	{
		this->X = Val;
		this->Y = Val;
	}

	#pragma endregion

	#pragma region Operators

	operator const D3DXVECTOR2&() const;
	
	Vector2 operator+(const Vector2 &V) const;
	Vector2 operator-(const Vector2 &V) const;
	Vector2 operator*(const Vector2 &V) const;
	Vector2 operator/(const Vector2 &V) const;
	Vector2 operator%(const Vector2 &V) const;
	
	Vector2 operator+(const FLOAT &S) const;
	Vector2 operator-(const FLOAT &S) const;
	Vector2 operator*(const FLOAT &S) const;
	Vector2 operator/(const FLOAT &S) const;
	Vector2 operator%(const FLOAT &S) const;

	Vector2 operator+=(const Vector2 &V);
	Vector2 operator-=(const Vector2 &V);
	Vector2 operator*=(const Vector2 &V);
	Vector2 operator/=(const Vector2 &V);
	Vector2 operator%=(const Vector2 &V);

	Vector2 operator+=(const FLOAT &S);
	Vector2 operator-=(const FLOAT &S);
	Vector2 operator*=(const FLOAT &S);
	Vector2 operator/=(const FLOAT &S);
	Vector2 operator%=(const FLOAT &S);
	
	friend Vector2 operator+(const FLOAT &S, const Vector2 &V);
	friend Vector2 operator-(const FLOAT &S, const Vector2 &V);
	friend Vector2 operator*(const FLOAT &S, const Vector2 &V);
	friend Vector2 operator/(const FLOAT &S, const Vector2 &V);

	Vector2 operator=(const Vector2 &V);
	BOOL operator==(const Vector2 &V) const;
	BOOL operator!=(const Vector2 &V) const;

	Vector2 operator-() const;
	Vector2 operator~() const; //Normal
	FLOAT   operator!() const; //Length

	#pragma endregion

	#pragma region Methods

	static FLOAT Dot(const Vector2 &V1, const Vector2 &V2);
	static FLOAT CCW(const Vector2 &V1, const Vector2 &V2);
	static Vector2 Min(const Vector2 &V1, const Vector2 &V2);
	static Vector2 Max(const Vector2 &V1, const Vector2 &V2);
	static Vector2 Lerp(const Vector2 &V1, const Vector2 &V2, const FLOAT &S);
	static Vector2 BaryCentric(const Vector2 &V1, const Vector2 &V2, const Vector2 &V3, const FLOAT &F, const FLOAT &G);
	static Vector2 CatmullRom(const Vector2 &V1, const Vector2 &V2, const Vector2 &V3, const Vector2 &V4, const FLOAT &S);
	
	#pragma endregion
};

#pragma endregion

#pragma region Vector3

class Vector3
{
	public:

	FLOAT X;
	FLOAT Y;
	FLOAT Z;

	#pragma region Constructor

	Vector3()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}

	Vector3(FLOAT Val)
	{
		this->X = Val;
		this->Y = Val;
		this->Z = Val;
	}

	Vector3(FLOAT X, FLOAT Y, FLOAT Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	Vector3(Vector2 V, FLOAT F)
	{
		this->X = V.X;
		this->Y = V.Y;
		this->Z = F;
	}

	#pragma endregion
	
	#pragma region Operators

	operator const D3DXVECTOR3&() const { return *(const D3DXVECTOR3*)this; }
	
	Vector3 operator+(const Vector3 &V) const;
	Vector3 operator-(const Vector3 &V) const;
	Vector3 operator*(const Vector3 &V) const;
	Vector3 operator/(const Vector3 &V) const;
	Vector3 operator%(const Vector3 &V) const;
	
	Vector3 operator+(const FLOAT &S) const;
	Vector3 operator-(const FLOAT &S) const;
	Vector3 operator*(const FLOAT &S) const;
	Vector3 operator/(const FLOAT &S) const;
	Vector3 operator%(const FLOAT &S) const;

	Vector3 operator+=(const Vector3 &V);
	Vector3 operator-=(const Vector3 &V);
	Vector3 operator*=(const Vector3 &V);
	Vector3 operator/=(const Vector3 &V);
	Vector3 operator%=(const Vector3 &V);

	Vector3 operator+=(const FLOAT &S);
	Vector3 operator-=(const FLOAT &S);
	Vector3 operator*=(const FLOAT &S);
	Vector3 operator/=(const FLOAT &S);
	Vector3 operator%=(const FLOAT &S);
	
	friend Vector3 operator+(const FLOAT &S, const Vector3 &V);
	friend Vector3 operator-(const FLOAT &S, const Vector3 &V);
	friend Vector3 operator*(const FLOAT &S, const Vector3 &V);
	friend Vector3 operator/(const FLOAT &S, const Vector3 &V);

	Vector3 operator=(const Vector3 &V);
	BOOL operator==(const Vector3 &V) const;
	BOOL operator!=(const Vector3 &V) const;

	Vector3 operator-() const;
	Vector3 operator~() const; //Normal
	FLOAT   operator!() const; //Length

	#pragma endregion

	#pragma region Methods

	static FLOAT Dot(const Vector3 &V1, const Vector3 &V2);
	static Vector3 Min(const Vector3 &V1, const Vector3 &V2);
	static Vector3 Max(const Vector3 &V1, const Vector3 &V2);
	static Vector3 Cross(const Vector3 &V1, const Vector3 &V2);
	static Vector3 Lerp(const Vector3 &V1, const Vector3 &V2, const FLOAT &S);
	static Vector3 BaryCentric(const Vector3 &V1, const Vector3 &V2, const Vector3 &V3, const FLOAT &F, const FLOAT &G);
	static Vector3 CatmullRom(const Vector3 &V1, const Vector3 &V2, const Vector3 &V3, const Vector3 &V4, const FLOAT &S);

	#pragma endregion
};

#pragma endregion

#pragma region Vector4

class Vector4
{
	public:

	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	FLOAT W;

	#pragma region Constructor

	Vector4()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
		this->W = 0.0f;
	}

	Vector4(FLOAT Val)
	{
		this->X = Val;
		this->Y = Val;
		this->Z = Val;
	}

	Vector4(FLOAT X, FLOAT Y, FLOAT Z, FLOAT W)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->W = W;
	}

	Vector4(Vector2 V1, Vector2 V2)
	{
		this->X = V1.X;
		this->Y = V1.Y;
		this->Z = V2.X;
		this->W = V2.Y;
	}

	Vector4(Vector3 V, FLOAT F)
	{
		this->X = V.X;
		this->Y = V.Y;
		this->Z = V.Z;
		this->W = F;
	}

	#pragma endregion

	#pragma region Operators

	operator const D3DXVECTOR4&() const;
	operator const D3DXQUATERNION&() const;
	operator const D3DXPLANE&() const;
	
	Vector4 operator+(const Vector4 &V) const;
	Vector4 operator-(const Vector4 &V) const;
	Vector4 operator*(const Vector4 &V) const;
	Vector4 operator/(const Vector4 &V) const;
	Vector4 operator%(const Vector4 &V) const;
	
	Vector4 operator+(const FLOAT &S) const;
	Vector4 operator-(const FLOAT &S) const;
	Vector4 operator*(const FLOAT &S) const;
	Vector4 operator/(const FLOAT &S) const;
	Vector4 operator%(const FLOAT &S) const;

	Vector4 operator+=(const Vector4 &V);
	Vector4 operator-=(const Vector4 &V);
	Vector4 operator*=(const Vector4 &V);
	Vector4 operator/=(const Vector4 &V);
	Vector4 operator%=(const Vector4 &V);

	Vector4 operator+=(const FLOAT &S);
	Vector4 operator-=(const FLOAT &S);
	Vector4 operator*=(const FLOAT &S);
	Vector4 operator/=(const FLOAT &S);
	Vector4 operator%=(const FLOAT &S);
	
	friend Vector4 operator+(const FLOAT &S, const Vector4 &V);
	friend Vector4 operator-(const FLOAT &S, const Vector4 &V);
	friend Vector4 operator*(const FLOAT &S, const Vector4 &V);
	friend Vector4 operator/(const FLOAT &S, const Vector4 &V);

	Vector4 operator=(const Vector4 &V);
	BOOL operator==(const Vector4 &V) const;
	BOOL operator!=(const Vector4 &V) const;

	Vector4 operator-() const;
	Vector4 operator~() const; //Normal
	FLOAT   operator!() const; //Length

	#pragma endregion

	#pragma region Methods

	static FLOAT Dot(const Vector4 &V1, const Vector4 &V2);
	static Vector4 Min(const Vector4 &V1, const Vector4 &V2);
	static Vector4 Max(const Vector4 &V1, const Vector4 &V2);
	static Vector4 Lerp(const Vector4 &V1, const Vector4 &V2, const FLOAT &S);
	static Vector4 CreateQuaternion(const Vector3& Axis, const FLOAT theta);
	static Vector4 BaryCentric(const Vector4 &V1, const Vector4 &V2, const Vector4 &V3, const FLOAT &F, const FLOAT &G);
	static Vector4 CatmullRom(const Vector4 &V1, const Vector4 &V2, const Vector4 &V3, const Vector4 &V4, const FLOAT &S);

	#pragma endregion
};

#pragma endregion

#pragma region Matrix4

class Matrix4
{	
	private:

	#pragma region Constructor

	Matrix4(D3DXMATRIX& M);

	#pragma endregion

	public:

	#pragma region Members

	D3DXMATRIX M;

	#pragma endregion

	#pragma region Constructor

	Matrix4();
	
	Matrix4(FLOAT m11, FLOAT m12, FLOAT m13, FLOAT m14, FLOAT m21, FLOAT m22, FLOAT m23, FLOAT m24, FLOAT m31, FLOAT m32, FLOAT m33, FLOAT m34, FLOAT m41, FLOAT m42, FLOAT m43, FLOAT m44);

	#pragma endregion

	#pragma region Operators
	
	FLOAT* operator[](int i) const;
	//operator const D3DXMATRIX() const;

	Matrix4 operator*(const Matrix4& M) const;
	Matrix4 operator*(FLOAT Ss) const;

	bool operator==(const Matrix4& M);
	bool operator!=(const Matrix4& M);

	#pragma endregion

	#pragma region Methods
	//Everything is left hand

	#pragma region Value

	FLOAT Determinant() const;
	void Decompose(Vector3& Scale, Vector4& Rotation, Vector3& Translation) const;

	static Matrix4 Identity();
	static Matrix4 Reflect(const Vector4& Plane);
	static Matrix4 Inverse(const Matrix4& M);
	static Matrix4 Shadow(const Vector4& Light, const Vector4& Plane);

	static Matrix4 CreateRotationQuaternion(const Vector4& Quaternion);
	static Matrix4 CreateRotationAxis(const Vector3& Axis, FLOAT Angle);
	static Matrix4 CreateYawPitchRoll(const Vector3& Angles);
	static Matrix4 CreateRotationX(FLOAT Angle);
	static Matrix4 CreateRotationY(FLOAT Angle);
	static Matrix4 CreateRotationZ(FLOAT Angle);
	
	static Matrix4 CreateTranspose(const Matrix4&M);
	static Matrix4 CreateTranslation(const Vector3& Translation);
	static Matrix4 CreateMultiplyTranspose(const Matrix4& M1, const Matrix4& M2);
	static Matrix4 CreateAffineTransformation(FLOAT Scale, const Vector2& RotationCenter, FLOAT Rotation, const Vector2& Translation);
	static Matrix4 CreateAffineTransformation(FLOAT Scale, const Vector3& RotationCenter, const Vector4& Qauternion, const Vector3& Translation);
	static Matrix4 CreateTransformation(const Vector2& ScalingCenter, FLOAT ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, FLOAT QuaternionRotation, const Vector2& Translation);
	static Matrix4 CreateTransformation(const Vector3& ScalingCenter, const Vector4& QuaternionScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Vector4& QuaternionRotation, const Vector3& Translation);

	static Matrix4 CreateScaling(Vector3& Scales);

	static Matrix4 CreateLookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up);

	static Matrix4 CreatePerspective(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar);
	static Matrix4 CreatePerspectiveFieldOfView(FLOAT FOVY, FLOAT Aspect, FLOAT ZNear, FLOAT ZFar);
	static Matrix4 CreatePerspectiveOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar);
	static Matrix4 CreateOrthographic(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar);
	static Matrix4 CreateOrthographicOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar);

	#pragma endregion

	#pragma region Reference

	static void Identity(Matrix4& out);
	static void Reflect(const Vector4& Plane, Matrix4& out);
	static void Inverse(const Matrix4& M, Matrix4& out);
	static void Shadow(const Vector4& Light, const Vector4& Plane, Matrix4& out);
	static void Multiply(const Matrix4& M1, const Matrix4& M2, Matrix4& out);

	static void CreateRotationQuaternion(const Vector4& Quaternion, Matrix4& out);
	static void CreateRotationAxis(const Vector3& Axis, FLOAT Angle, Matrix4& out);
	static void CreateYawPitchRoll(const Vector3& Rotations, Matrix4& out);
	static void CreateRotationX(FLOAT Rotation, Matrix4& out);
	static void CreateRotationY(FLOAT Rotation, Matrix4& out);
	static void CreateRotationZ(FLOAT Rotation, Matrix4& out);
	
	static void CreateTranspose(const Matrix4& M, Matrix4& out);
	static void CreateTranslation(const Vector3& Translation, Matrix4& out);
	static void CreateMultiplyTranspose(const Matrix4& M1, const Matrix4& M2, Matrix4& out);
	static void CreateAffineTransformation(FLOAT Scale, const Vector2& RotationCenter, FLOAT Rotation, const Vector2& Translation, Matrix4& out);
	static void CreateAffineTransformation(FLOAT Scale, const Vector3& RotationCenter, const Vector4& Qauternion, const Vector3& Translation, Matrix4& out);
	static void CreateTransformation(const Vector2& ScalingCenter, FLOAT ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, FLOAT QuaternionRotation, const Vector2& Translation, Matrix4& out);
	static void CreateTransformation(const Vector3& ScalingCenter, const Vector4& QuaternionScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Vector4& QuaternionRotation, const Vector3& Translation, Matrix4& out);

	static void CreateScaling(Vector3& Scales, Matrix4& out);

	static void CreateLookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up, Matrix4& out);

	static void CreatePerspective(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar, Matrix4& out);
	static void CreatePerspectiveFieldOfView(FLOAT FOVY, FLOAT Aspect, FLOAT ZNear, FLOAT ZFar, Matrix4& out);
	static void CreatePerspectiveOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar, Matrix4& out);
	static void CreateOrthographic(FLOAT Width, FLOAT Height, FLOAT ZNear, FLOAT ZFar, Matrix4& out);
	static void CreateOrthographicOffCenter(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT ZNear, FLOAT ZFar, Matrix4& out);

	#pragma endregion

	#pragma endregion
};

#pragma endregion

#pragma region Rectangle

class Rectangle
{
	public:
	
	#pragma region Members
	
	long L; 
	long T;
	long R;
	long B;

	#pragma endregion
	
	#pragma region Constructor
	
	Rectangle();
	Rectangle(Vector2 Pos, long Width, long Height);
	Rectangle(long Left, long Top, long Right, long Bottom);
	

	#pragma endregion

	#pragma region Operator

	operator const RECT(); 
	operator const RECT*(); 

	#pragma endregion
	
	#pragma region Methods

	long Width();
	long Height();
	void Inflate(int PushX, int PushY);
	BOOL Intersects(Rectangle rect);
	BOOL Contains(Rectangle rect);
		
	static Rectangle Intersect(Rectangle R1, Rectangle R2);
	static Rectangle Union(Rectangle R1, Rectangle R2);
	static BOOL Intersects(Rectangle R1, Rectangle R2);

	#pragma endregion
};

#pragma endregion

#pragma endregion

#pragma region Graphics

#pragma region Color

struct Color /* Color represented by 4 Bytes. Use Vector4 for floats */
{
	byte B, G, R, A;

	Color();
	Color(byte V);
	Color(byte R, byte G, byte B);
	Color(byte R, byte G, byte B, byte A);

	ulong ToDword();

	static ulong ToDword(byte R, byte G, byte B);
	static ulong ToDword(byte R, byte G, byte B, byte A);

	static const Color Red;
	static const Color Green;
	static const Color Blue;

	// Secondary
	static const Color Cyan;
	static const Color Magenta;
	static const Color Yellow;

	// Black & White
	static const Color Black;		
	static const Color White; 
	static const Color Gray; 

	// Grayscale
	static const Color LightGray;	
	static const Color MiddleGray; 
	static const Color DarkGray; 

	// Misc. 
	// (mostly from en.wikipedia.org/wiki/List_of_colors) 
	static const Color Amethyst;	
	static const Color AppleGreen;	
	static const Color Aquamarine;	
	static const Color ArmyGreen;	
	static const Color Arsenic;	

	static const Color BabyBlue;	
	static const Color BabyPink;	
	static const Color Banana;	
	static const Color Brass;	
	static const Color BrickRed;	
	static const Color Bronze;	
	static const Color Brown;		
	static const Color BubbleGum;	
	static const Color Burgundy;	
	static const Color BurntUmber;	
	static const Color Byzantine;	

	static const Color CamoGreen;	
	static const Color Cardinal;	
	static const Color Carnation;	
	static const Color Carrot;	
	static const Color Cerulean;	
	static const Color Chartreuse;	
	static const Color Cinnamon;	
	static const Color Cobalt;	
	static const Color Copper;	
	static const Color Coral;	
	static const Color CornFlower;	
	static const Color CottonCandy;	
	static const Color Crimson;	

	static const Color Daffodil;	
	static const Color Dandelion;	
	static const Color Denim;	
	static const Color DollarBill;	

	static const Color Ecru;	
	static const Color Eggplant;	
	static const Color Eggshell;	
	static const Color EgyptianBlue;	
	static const Color Emerald;	

	static const Color Fallow;	
	static const Color FaluRed;	
	static const Color Fandango;	
	static const Color FernGreen;	
	static const Color FireEngine;	
	static const Color FlameOrange;	
	static const Color FlamingoPink;	
	static const Color FrenchBleu;	
	static const Color Fuschia;		
	static const Color Fulvous;	

	static const Color Gamboge;	
	static const Color Glaucous;	
	static const Color Gold;	
	static const Color GoldenRod;	
	static const Color GrannySmith;	
	static const Color Grullo;	
	static const Color Guppie;	

	static const Color Hazel;	
	static const Color Heliotrope;	
	static const Color Hooloovoo;	
	static const Color HunterGreen;	

	static const Color Iceberg;	
	static const Color Icterine;	
	static const Color Indigo;	
	static const Color Iris;	
	static const Color Isabelline;	
	static const Color IslamGreen;	
	static const Color Ivory;	

	static const Color Jade;	
	static const Color Jasper;	
	static const Color Jam;	
	static const Color Jonquil;	
	static const Color JuneBud;	
	static const Color JungleGreen;	

	static const Color LapisLazuli;	
	static const Color Lava;	
	static const Color Lavender;	
	static const Color Lemon;	
	static const Color LemonChiffon;	
	static const Color Lilac;	
	static const Color Lime;	
	static const Color Liver;	
	static const Color LustRed;	

	static const Color MagicMint;	
	static const Color Magnolia;	
	static const Color Mahogany;	
	static const Color Maize;	
	static const Color Malachite;	
	static const Color Maroon;	
	static const Color Mauve;	
	static const Color MidnightBlue;	
	static const Color MidnightGreen;		
	static const Color Mint;	
	static const Color Moonstone;	
	static const Color MountainMaj;	
	static const Color MullBerry;	
	static const Color Mustard;	
	static const Color Myrtle;	

	static const Color NapierGreen;	
	static const Color NavyBlue;		

	static const Color Ochre;	
	static const Color Olive;	
	static const Color Olivine;	
	static const Color Onyx;	
	static const Color Orange;	
	static const Color Orchid;	

	static const Color Peach;	
	static const Color Pear;	
	static const Color Pearl;	
	static const Color Peridot;	
	static const Color Periwinkle;	
	static const Color Perisimmon;	
	static const Color Pink;			

	static const Color Pistachio;	
	static const Color Platinum;	
	static const Color Plum;	
	static const Color PowderBlue;	
	static const Color Puce;			
	static const Color Pumpkin;	
	static const Color Purple;	

	static const Color Raspberry;
	static const Color RawUmber;	
	static const Color Razzmatazz;	
	static const Color Redwood;
	static const Color Regalia;	
	static const Color Rose;	
	static const Color Rosewood;	
	static const Color RossoCorsa;		
	static const Color RoyalAzure;	
	static const Color RoyalBlue;	
	static const Color RoyalFuschia;			
	static const Color RoyalPurple;	
	static const Color Ruby;	
	static const Color Ruddy;	
	static const Color Rufous;			
	static const Color Russet;	
	static const Color Rust;	

	static const Color SafetyOrange;	
	static const Color Saffron;	
	static const Color Salmon;	
	static const Color Sand;	
	static const Color Sangria;	
	static const Color SapGreen;	
	static const Color Sapphire;	
	static const Color Scarlet;	
	static const Color SchoolBus;	
	static const Color SeaGreen;	
	static const Color Sepia;	
	static const Color Sherbert;	
	static const Color Sienna;	
	static const Color Silver;	
	static const Color Sinopia;	
	static const Color Skobeloff;	
	static const Color SkyBlue;	
	static const Color SlateGrey;	
	static const Color SpringGreen;	
	static const Color SteelBlue;	
	static const Color Straw;	

	static const Color Tan;	
	static const Color Tangelo;	
	static const Color Tangerine;	
	static const Color Taupe;	
	static const Color Teal;	
	static const Color TerraCotta;	
	static const Color Thistle;	
	static const Color TickleMePink;	
	static const Color TiffanyBlue;	
	static const Color Tomato;	
	static const Color Tumbleweed;	
	static const Color Turquoise;	
	static const Color TuscanRed;	

	static const Color Umber;	
	static const Color Urobilin;	

	static const Color Vanilla;	
	static const Color Vermillion;	
	static const Color Violet;	
	static const Color Viridian;	

	static const Color Wenge;	
	static const Color Wheat;	
	static const Color Wisteria;	

	static const Color Xanadu;	

	static const Color YellowGreen;	

	static const Color Zaffre;	
};

#pragma endregion

#pragma region PrimitiveType

struct PrimitiveType
{
	static const D3DPRIMITIVETYPE PointList     = (D3DPRIMITIVETYPE)1;
	static const D3DPRIMITIVETYPE LineList      = (D3DPRIMITIVETYPE)2;
	static const D3DPRIMITIVETYPE LineStrip     = (D3DPRIMITIVETYPE)3;
	static const D3DPRIMITIVETYPE TriangleList  = (D3DPRIMITIVETYPE)4;
	static const D3DPRIMITIVETYPE TriangleStrip = (D3DPRIMITIVETYPE)5;
	static const D3DPRIMITIVETYPE TriangleFan   = (D3DPRIMITIVETYPE)6;
};

#pragma endregion

#pragma region VertexElement

class VertexElement
{
	public:
	ushort Stream;
	ushort Offset; 
	byte Format;
	byte Method;
	byte Usage;
	byte UsageIndex;

	VertexElement(ushort Stream, ushort Offset, byte Format, byte Method, byte Usage, byte UsageIndex)
	{
		this->Stream = Stream;
		this->Offset = Offset;
		this->Format = Format;
		this->Method = Method;
		this->Usage = Usage;
		this->UsageIndex = UsageIndex;
	}

	operator D3DVERTEXELEMENT9() const
	{
		return *(const D3DVERTEXELEMENT9*)this;
	}
};

#pragma endregion

#pragma region VertexDeclaration

class VertexDeclaration
{
	friend class Device;
	private:
	LPDIRECT3DVERTEXDECLARATION9 vd;
	public:
	
	VertexDeclaration(VertexElement first, ...);
};

#pragma endregion

#pragma region VertexTypes

class IVertexType {	};

class V
{
	public:

	#pragma region Format

	struct Format
	{
		static const D3DDECLTYPE Single                  = (D3DDECLTYPE)0;
 		static const D3DDECLTYPE Vector2                 = (D3DDECLTYPE)1;
		static const D3DDECLTYPE Vector3                 = (D3DDECLTYPE)2;
 		static const D3DDECLTYPE Vector4                 = (D3DDECLTYPE)3;
  		static const D3DDECLTYPE Color                   = (D3DDECLTYPE)4;
  		static const D3DDECLTYPE Byte4                   = (D3DDECLTYPE)5;
  		static const D3DDECLTYPE Short2                  = (D3DDECLTYPE)6;
  		static const D3DDECLTYPE Short4                  = (D3DDECLTYPE)7;
  		static const D3DDECLTYPE RGBA32                  = (D3DDECLTYPE)8;
  		static const D3DDECLTYPE NormalizedShort2        = (D3DDECLTYPE)9;
  		static const D3DDECLTYPE NormalizedShort4        = (D3DDECLTYPE)10;
  		static const D3DDECLTYPE RG32                    = (D3DDECLTYPE)11;
  		static const D3DDECLTYPE RGBA64                  = (D3DDECLTYPE)12;
  		static const D3DDECLTYPE UInt101010              = (D3DDECLTYPE)13;
  		static const D3DDECLTYPE Normalized101010        = (D3DDECLTYPE)14;
  		static const D3DDECLTYPE HalfVector2             = (D3DDECLTYPE)15;
  		static const D3DDECLTYPE HalfVector4             = (D3DDECLTYPE)16;
		static const D3DDECLTYPE UnUsed                  = (D3DDECLTYPE)17;
	};

	#pragma endregion

	#pragma region Method

	struct Method
	{
		static const D3DDECLMETHOD Default            = (D3DDECLMETHOD)0;
		static const D3DDECLMETHOD PartialU           = (D3DDECLMETHOD)1;
		static const D3DDECLMETHOD PartialV           = (D3DDECLMETHOD)2;
		static const D3DDECLMETHOD CrossUV            = (D3DDECLMETHOD)3;
		static const D3DDECLMETHOD UV                 = (D3DDECLMETHOD)4;
		static const D3DDECLMETHOD LookUp             = (D3DDECLMETHOD)5;
		static const D3DDECLMETHOD LookUpPreSampled   = (D3DDECLMETHOD)6;
	};

	#pragma endregion

	#pragma region Usage

	struct Usage
	{
		static const D3DDECLUSAGE Position           = (D3DDECLUSAGE)0;
		static const D3DDECLUSAGE BlendWeight        = (D3DDECLUSAGE)1;
		static const D3DDECLUSAGE BlendIndices       = (D3DDECLUSAGE)2;
		static const D3DDECLUSAGE Normal             = (D3DDECLUSAGE)3;
		static const D3DDECLUSAGE PointSize          = (D3DDECLUSAGE)4;
		static const D3DDECLUSAGE TextureCoordinate  = (D3DDECLUSAGE)5;
		static const D3DDECLUSAGE Tangent            = (D3DDECLUSAGE)6;
		static const D3DDECLUSAGE Binormal           = (D3DDECLUSAGE)7;
		static const D3DDECLUSAGE TessellateFactor   = (D3DDECLUSAGE)8;
		static const D3DDECLUSAGE Color              = (D3DDECLUSAGE)10;
		static const D3DDECLUSAGE Fog                = (D3DDECLUSAGE)11;
		static const D3DDECLUSAGE Depth              = (D3DDECLUSAGE)12;
		static const D3DDECLUSAGE Sample             = (D3DDECLUSAGE)13;
	};

	#pragma endregion

	#pragma region P

	class P : IVertexType
	{
		public:
		Vector3 Pos;

		
		P(Vector3 Pos) 
		{
			this->Pos = Pos;
		}

		static VertexDeclaration Declaration;
	};

	#pragma endregion

	#pragma region PC

	class PC : IVertexType
	{
		public:
		Vector3 Pos;
		Color Col;
		
		

		PC(Vector3 Pos, Color Vol) 
		{
			this->Pos = Pos;
			this->Col = Col;
		}

		static VertexDeclaration Declaration;
	};

	#pragma endregion

	#pragma region PT

	class PT : IVertexType
	{
		public:
		Vector3 Pos;
		Vector2 Tex;
		
		

		PT(Vector3 Pos, Vector2 Tex)
		{
			this->Pos = Pos;
			this->Tex = Tex;
		}

		static VertexDeclaration Declaration;
	};

	#pragma endregion
};

#pragma endregion

#pragma region BufferUsage

struct BufferUsage
{
	static const uint None      = 0x00000000L;
	static const uint Point     = 0x00000008L;
	static const uint WriteOnly = 0x00000040L;
};

#pragma endregion

#pragma region VertexBuffer

class VertexBuffer
{
	friend class Device;
	public:
	IDirect3DVertexBuffer9* data;

	VertexBuffer(uint SizeInBytes, uint BufferUsage);

	void SetData(const void* data, uint BytesToCopy);
};

#pragma endregion

#pragma region IndexFormat

struct IndexFormat
{
	static const _D3DFORMAT Word = (_D3DFORMAT)101;
	static const _D3DFORMAT DWord = (_D3DFORMAT)102;
};

#pragma endregion

#pragma region IndexBuffer

class IndexBuffer
{
	public:
	IDirect3DIndexBuffer9* data;

	IndexBuffer(uint SizeInBytes, uint BufferUsage, DFormat IndexFormat);

	void SetData(const void* data, uint BytesToCopy);
};

#pragma endregion

#pragma region DeviceManager

class DeviceManager
{
	friend class Window;
	friend class Device;

	#pragma region private

	private:

	#pragma region Members

	static BOOL isfullscreen;

	#pragma endregion

	#pragma endregion

	#pragma region public

	public:

	#pragma region Members

	static const BOOL          &IsFullScreen; /* Start windowed/Get Currently Windowed */

	static uint                BackBufferWidth;
	static uint                BackBufferHeight;
	static D3DFORMAT           BackBufferFormat;
	static uint                BackBufferCount;
	static D3DMULTISAMPLE_TYPE MultiSampleType;
	static ulong               MultiSampleQuality;
	static D3DSWAPEFFECT       SwapEffect;
	static BOOL                EnableAutoDepthStencil;
	static D3DFORMAT           AutoDepthStencilFormat;
	static ulong               Flags;
	static uint                FullScreen_RefreshRateInHz;
	static bool                VSync;

	#pragma endregion

	#pragma region Methods

	static void IntializeDevice();
	static void ApplyChanges();
	static void ToggleFullScreen();

	#pragma endregion

	#pragma endregion
};

#pragma endregion

#pragma region GraphicsDevice

class VertexStreamCollection;
class RenderTargetCube;
class RenderTarget2D;
class ContentManager;

class Device
{
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class DeviceManager;
	friend class VertexDeclaration;

	#pragma region private

	private:

	#pragma region Members

	static LPDIRECT3D9 d3d;
	public: static LPDIRECT3DDEVICE9 device;

	private:

	static void* pVoid;

	#pragma endregion

	#pragma region Methods

	static void CreateVertexDeclaration(const D3DVERTEXELEMENT9* element, LPDIRECT3DVERTEXDECLARATION9* vd);

	#pragma endregion

	#pragma endregion

	#pragma region public

	public:

	#pragma region Members

	static int Width;
	static int Height;
	
	static VertexStreamCollection Streams;
	static ContentManager* Content;

	#pragma endregion

	#pragma region Methods

	#pragma region Prototypes

	static void BeginScene();
	static void EndScene();

	static void Clear(Color col);
	static void Clear(ulong flags, Color col, float depth, ulong stencil);
	static void Clear(ulong flags, Color col, float depth, ulong stencil, const D3DRECT* rects, ulong count);



	static void Release();

	#pragma endregion

	#pragma region TemplateFunctions

	#pragma region DrawPrimitive

	template <typename T> static void DrawPrimitive(DPrimitiveType type, uint StartVertex, uint PrimitiveCount)
	{
		device->SetVertexDeclaration(T::Declaration.vd);
		device->DrawPrimitive(type, StartVertex, PrimitiveCount);
	}

	#pragma endregion

	#pragma region DrawUserPrimitive

	template <typename T> 
	static void DrawUserPrimitive (DPrimitiveType ptype, T Vertices[], int PrimitiveCount)
	{
		device->SetVertexDeclaration(T::Declaration.vd);
		device->DrawPrimitiveUP(ptype, PrimitiveCount, Vertices, sizeof(T));
		Device::Streams[0].SetSource(0, 0, 0);
	}
	#pragma endregion

	#pragma region DrawIndexedPrimitive

	template <typename T> static void DrawIndexedPrimitive(DPrimitiveType type, INT BaseVertexIndex, uint MinIndex, uint NumVertices, uint StartIndex, uint PrimitiveCount)
	{
		device->SetVertexDeclaration(T::Declaration.vd);
		device->DrawIndexedPrimitive(type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
	}

	#pragma endregion

	#pragma region DrawUserIndexedPrimitive

	template <typename T> 
	static void DrawUserIndexedPrimitive (DPrimitiveType ptype, T Vertices[], short VOffset, int numVertices, short Indices[], int IOffset, int numIndices, int PrimitiveCount)
	{
		device->SetVertexDeclaration(T::Declaration.vd);
		device->DrawIndexedPrimitiveUP(ptype, 0, numVertices, PrimitiveCount, Indices, IndexFormat::Word, Vertices, sizeof(T));
		Device::Streams[0].SetSource(0, 0, 0);
	}
	template <typename T> 
	static void DrawUserIndexedPrimitive (DPrimitiveType ptype, T Vertices[], short VOffset, int numVertices, int Indices[], int IOffset, int numIndices, int PrimitiveCount)
	{
		device->SetVertexDeclaration(T::Declaration.vd);
		device->DrawIndexedPrimitiveUP(ptype, 0, numVertices, PrimitiveCount, Indices, IndexFormat::DWord, Vertices, sizeof(T));
		Device::Streams[0].SetSource(0, 0, 0);
	}

	#pragma endregion

	#pragma endregion

	#pragma endregion

	#pragma endregion
	

	#pragma region RenderState

	class RenderState
	{

		#pragma region private

		private:

		#pragma region RenderStateSetting

		struct RenderStateSetting
		{

			private: 

			RenderStateType setting;
		
			public:

			RenderStateSetting(RenderStateType t)
			{ 
				setting = t;
			}

			operator const ulong() const 
			{ 
				ulong temp; 
				Device::device->GetRenderState(setting, &temp); 
				return temp; 
			}

			RenderStateSetting& operator=(int source)
			{
				Device::device->SetRenderState(setting, source);
				return *this;
			}

			bool operator==(ulong source)
			{
				ulong temp;
				Device::device->GetRenderState(setting, &temp);
				return temp == source;
			}
		};

		#pragma endregion

		#pragma endregion

		#pragma region public

		public:

		#pragma region Members

		static RenderStateSetting   ZENABLE;    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
		static RenderStateSetting	FILLMODE;    /* D3DFILLMODE */
		static RenderStateSetting	SHADEMODE;   /* D3DSHADEMODE */
		static RenderStateSetting	ZWRITEENABLE;   /* TRUE to enable z writes */
		static RenderStateSetting	ALPHATESTENABLE;   /* TRUE to enable alpha tests */
		static RenderStateSetting	LASTPIXEL;   /* TRUE for last-pixel on lines */
		static RenderStateSetting	SRCBLEND;   /* D3DBLEND */
		static RenderStateSetting	DESTBLEND;   /* D3DBLEND */
		static RenderStateSetting	CULLMODE;   /* D3DCULL */
		static RenderStateSetting	ZFUNC;   /* D3DCMPFUNC */
		static RenderStateSetting	ALPHAREF;   /* D3DFIXED */
		static RenderStateSetting	ALPHAFUNC;   /* D3DCMPFUNC */
		static RenderStateSetting	DITHERENABLE;   /* TRUE to enable dithering */
		static RenderStateSetting	ALPHABLENDENABLE;   /* TRUE to enable alpha blending */
		static RenderStateSetting	FOGENABLE;   /* TRUE to enable fog blending */
		static RenderStateSetting	SPECULARENABLE;   /* TRUE to enable specular */
		static RenderStateSetting	FOGCOLOR;   /* D3DCOLOR */
		static RenderStateSetting	FOGTABLEMODE;   /* D3DFOGMODE */
		static RenderStateSetting	FOGSTART;   /* Fog start (for both vertex and pixel fog) */
		static RenderStateSetting	FOGEND;   /* Fog end      */
		static RenderStateSetting	FOGDENSITY;   /* Fog density  */
		static RenderStateSetting	RANGEFOGENABLE;   /* Enables range-based fog */
		static RenderStateSetting	STENCILENABLE;   /* BOOL enable/disable stenciling */
		static RenderStateSetting	STENCILFAIL;   /* D3DSTENCILOP to do if stencil test fails */
		static RenderStateSetting	STENCILZFAIL;   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
		static RenderStateSetting	STENCILPASS;   /* D3DSTENCILOP to do if both stencil and Z tests pass */
		static RenderStateSetting	STENCILFUNC;   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		static RenderStateSetting	STENCILREF;   /* Reference value used in stencil test */
		static RenderStateSetting	STENCILMASK;   /* Mask value used in stencil test */
		static RenderStateSetting	STENCILWRITEMASK;   /* Write mask applied to values written to stencil buffer */
		static RenderStateSetting	TEXTUREFACTOR;   /* D3DCOLOR used for multi-texture blend */
		static RenderStateSetting	WRAP0;  /* wrap for 1st texture coord. set */
		static RenderStateSetting	WRAP1;  /* wrap for 2nd texture coord. set */
		static RenderStateSetting	WRAP2;  /* wrap for 3rd texture coord. set */
		static RenderStateSetting	WRAP3;  /* wrap for 4th texture coord. set */
		static RenderStateSetting	WRAP4;  /* wrap for 5th texture coord. set */
		static RenderStateSetting	WRAP5;  /* wrap for 6th texture coord. set */
		static RenderStateSetting	WRAP6;  /* wrap for 7th texture coord. set */
		static RenderStateSetting	WRAP7;  /* wrap for 8th texture coord. set */
		static RenderStateSetting	CLIPPING;
		static RenderStateSetting	LIGHTING;
		static RenderStateSetting	AMBIENT;
		static RenderStateSetting	FOGVERTEXMODE;
		static RenderStateSetting	COLORVERTEX;
		static RenderStateSetting	LOCALVIEWER;
		static RenderStateSetting	NORMALIZENORMALS;
		static RenderStateSetting	DIFFUSEMATERIALSOURCE;
		static RenderStateSetting	SPECULARMATERIALSOURCE;
		static RenderStateSetting	AMBIENTMATERIALSOURCE;
		static RenderStateSetting	EMISSIVEMATERIALSOURCE;
		static RenderStateSetting	VERTEXBLEND;
		static RenderStateSetting	CLIPPLANEENABLE;
		static RenderStateSetting	POINTSIZE;   /* float point size */
		static RenderStateSetting	POINTSIZE_MIN;   /* float point size min threshold */
		static RenderStateSetting	POINTSPRITEENABLE;   /* BOOL point texture coord control */
		static RenderStateSetting	POINTSCALEENABLE;   /* BOOL point size scale enable */
		static RenderStateSetting	POINTSCALE_A;   /* float point attenuation A value */
		static RenderStateSetting	POINTSCALE_B;   /* float point attenuation B value */
		static RenderStateSetting	POINTSCALE_C;   /* float point attenuation C value */
		static RenderStateSetting	MULTISAMPLEANTIALIAS;  // BOOL - set to do FSAA with multisample buffer
		static RenderStateSetting	MULTISAMPLEMASK;  // DWORD - per-sample enable/disable
		static RenderStateSetting	PATCHEDGESTYLE;  // Sets whether patch edges will use float style tessellation
		static RenderStateSetting	DEBUGMONITORTOKEN;  // DEBUG ONLY - token to debug monitor
		static RenderStateSetting	POINTSIZE_MAX;   /* float point size max threshold */
		static RenderStateSetting	INDEXEDVERTEXBLENDENABLE;
		static RenderStateSetting	COLORWRITEENABLE;  // per-channel write enable
		static RenderStateSetting	TWEENFACTOR;   // float tween factor
		static RenderStateSetting	BLENDOP;   // D3DBLENDOP setting
		static RenderStateSetting	POSITIONDEGREE;   // NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
		static RenderStateSetting	NORMALDEGREE;   // NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
		static RenderStateSetting	SCISSORTESTENABLE;
		static RenderStateSetting	SLOPESCALEDEPTHBIAS;
		static RenderStateSetting	ANTIALIASEDLINEENABLE;
		static RenderStateSetting	MINTESSELLATIONLEVEL;
		static RenderStateSetting	MAXTESSELLATIONLEVEL;
		static RenderStateSetting	ADAPTIVETESS_X;
		static RenderStateSetting	ADAPTIVETESS_Y;
		static RenderStateSetting	ADAPTIVETESS_Z;
		static RenderStateSetting	ADAPTIVETESS_W;
		static RenderStateSetting	ENABLEADAPTIVETESSELLATION;
		static RenderStateSetting	TWOSIDEDSTENCILMODE;   /* BOOL enable/disable 2 sided stenciling */
		static RenderStateSetting	CCW_STENCILFAIL;   /* D3DSTENCILOP to do if ccw stencil test fails */
		static RenderStateSetting	CCW_STENCILZFAIL;   /* D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
		static RenderStateSetting	CCW_STENCILPASS;   /* D3DSTENCILOP to do if both ccw stencil and Z tests pass */
		static RenderStateSetting	CCW_STENCILFUNC;   /* D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		static RenderStateSetting	COLORWRITEENABLE1;   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		static RenderStateSetting	COLORWRITEENABLE2;   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		static RenderStateSetting	COLORWRITEENABLE3;   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		static RenderStateSetting	BLENDFACTOR;   /* D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
		static RenderStateSetting	SRGBWRITEENABLE;   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
		static RenderStateSetting	DEPTHBIAS;
		static RenderStateSetting	WRAP8;   /* Additional wrap states for vs_3_0+ attributes with D3DDECLUSAGE_TEXCOORD */
		static RenderStateSetting	WRAP9;
		static RenderStateSetting	WRAP10;
		static RenderStateSetting	WRAP11;
		static RenderStateSetting	WRAP12;
		static RenderStateSetting	WRAP13;
		static RenderStateSetting	WRAP14;
		static RenderStateSetting	WRAP15;
		static RenderStateSetting	SEPARATEALPHABLENDENABLE;  /* TRUE to enable a separate blending function for the alpha channel */
		static RenderStateSetting	SRCBLENDALPHA;  /* SRC blend factor for the alpha channel when SEPARATEDESTALPHAENABLE is TRUE */
		static RenderStateSetting	DESTBLENDALPHA;  /* DST blend factor for the alpha channel when SEPARATEDESTALPHAENABLE is TRUE */
		static RenderStateSetting	BLENDOPALPHA;  /* Blending operation for the alpha channel when SEPARATEDESTALPHAENABLE is TRUE */

		static RenderStateSetting	FORCE_DWORD; /* force 32-bit size enum */

		#pragma endregion

		#pragma endregion
	};

	#pragma endregion
};

#pragma endregion

#pragma region VertexStream

class VertexStream
{
	private:
	VertexBuffer* buffer;
	UINT stream;
	UINT offset;
	UINT stride;
	public:
	VertexStream(UINT stream);

	void SetSource(VertexBuffer* Buffer, UINT OffsetInBytes, UINT VertexStride);
	void SetSourceFrequency(UINT Frequency);
	VertexBuffer* Buffer();
	UINT OffsetInBytes();
	UINT VertexStride();
};

#pragma endregion

#pragma region VertexStreamCollection

class VertexStreamCollection
{
	private:
	std::vector<VertexStream> streams;
	public:
	VertexStream& operator[](uint i) 
	{
		if(i + 1 > streams.size())
		{
			for(uint k = streams.size(); k < i + 1; k++)
				streams.push_back(VertexStream(k));
		}
		return streams[i];
	}
};

#pragma endregion

#pragma region Content

#pragma region IContent

class IContent
{
	friend class Device;
	public:
	virtual void Lost() = 0;
	virtual void Reset() = 0;
	virtual void Release() = 0;
	virtual std::wstring GetPath() = 0;
};

#pragma endregion

#pragma region Effect

class Effect : public IContent
{
	public:
	ID3DXEffect* Data;
	std::wstring Path;

	virtual void Lost();
	virtual void Reset();
	virtual void Release();
	virtual std::wstring GetPath();

	static Effect* Load(std::wstring path);

	void Begin();
	void End();

	#pragma region SetValue

	template<typename T>
	void SetValue(std::string Parameter, const IContent* value)
	{
		this->Data->SetValue(Parameter.c_str(), &((T*)value)->Data, sizeof(*(((T*)value)->Data)));
	}

	template<typename T>
	void SetValue(std::string Parameter, const T& value)
	{
		this->Data->SetValue(Parameter.c_str(), &value, sizeof(T));
	}

	#pragma endregion

	#pragma region GetValue

	template<typename T>
	T GetValue(std::string Parameter)
	{
		LPVOID value;
		this->Data->GetValue(Parameter.c_str(), value, sizeof(T));
		return *(T*)value;
	}

	#pragma endregion
};

#pragma endregion

#pragma region Texture2D

class Texture2D : public IContent
{
	private:
	uint width;
	uint height;

	public:
	IDirect3DTexture9* Data;
	std::wstring Path;

	Texture2D() { Data = nullptr; }
	Texture2D(int Width, int Height, bool MipMap, DFormat SurfaceFormat) { Device::device->CreateTexture(Width, Height, MipMap, D3DX_DEFAULT, SurfaceFormat, D3DPOOL_MANAGED, &Data, 0); } 
	
	virtual void Lost();
	virtual void Reset();
	virtual void Release();
	virtual std::wstring GetPath();

	static Texture2D* Load(std::wstring path);

	uint Width();
	uint Height();
	
	template<typename T>
	void GetData(T* outData)
	{
		D3DLOCKED_RECT R;
		int size = width * height;
		Data->LockRect(0, &R, 0, D3DLOCK_DISCARD);
		for(int i = 0; i < size; i++) 
		{
			outData[i] = *((T*)(R.pBits) + i);
		}
		Data->UnlockRect(0);
	}

	template<typename T>
	void SetData(T* inData)
	{
		D3DLOCKED_RECT R;
		int size = width * height;
		Data->LockRect(0, &R, 0, D3DLOCK_DISCARD);
		for(int i = 0; i < size; i++) *((T*)(R.pBits) + i) = outData[i];
		Data->UnlockRect(0);
	}
};

#pragma endregion

#pragma region Texture3D

class Texture3D : public IContent
{
	private:
	uint width;
	uint height;
	uint depth;

	public:
	IDirect3DVolumeTexture9* Data;
	std::wstring Path;

	Texture3D() { Data = 0; }

	virtual void Lost();
	virtual void Reset();
	virtual void Release();
	virtual std::wstring GetPath();
	
	static int Size();
	static Texture3D* Load(std::wstring path);

	uint Width();
	uint Height();
	uint Depth();

	template<typename T>
	void GetData(T* outData)
	{
		D3DLOCKED_BOX B;
		int size = width * height * depth;
		Data->LockBox(0, &B, 0, D3DLOCK_DISCARD);
		for(int i = 0; i < size; i++) outData[i] = *((T)(B.pBits )+ i)
		Data->UnlockBox(0);
	}

	template<typename T>
	void SetData(T* outData)
	{
		D3DLOCKED_BOX B;
		int size = width * height * depth;
		Data->LockBox(0, &B, 0, D3DLOCK_DISCARD);
		for(int i = 0; i < size; i++) *((T)(B.pBits )+ i) = outData[i];
		Data->UnlockBox(0);
	}
};

#pragma endregion

#pragma region TextureCube

class TextureCube : public IContent
{
	private:
	uint width;
	uint height;

	public:
	IDirect3DCubeTexture9* Data;
	std::wstring Path;

	TextureCube() { Data = 0; }

	virtual void Lost();
	virtual void Reset();
	virtual void Release();
	virtual std::wstring GetPath();
	
	static int Size();
	static TextureCube* Load(std::wstring path);

	uint Width();
	uint Height();
};

#pragma endregion

#pragma endregion

#pragma region ContentManager

class ContentManager
{
	public:

	std::vector<IContent*> objects;
	std::wstring RootContentDirectory;

	ContentManager(std::wstring RootContentDirectory)
	{
		this->RootContentDirectory = RootContentDirectory;
		Device::Content = this;
	}

	template <typename T>
	T* Load(std::wstring path)
	{
		for(uint i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetPath() == this->RootContentDirectory + path)
			{
				return (T*)objects[i];
			}
		}

		objects.push_back(T::Load(this->RootContentDirectory + path));
		return (T*)objects.back();
	}
	
	void OnLostDevice();
	void OnResetDevice();
	void UnloadContent();
};

#pragma endregion

#pragma region SurfaceFormat

struct SurfaceFormat
{
	public:
	static const D3DFORMAT UNKNOWN              = (D3DFORMAT)0;

    static const D3DFORMAT R8G8B8               = (D3DFORMAT)20;
    static const D3DFORMAT A8R8G8B8             = (D3DFORMAT)21;
    static const D3DFORMAT X8R8G8B8             = (D3DFORMAT)22;
    static const D3DFORMAT R5G6B5               = (D3DFORMAT)23;
    static const D3DFORMAT X1R5G5B5             = (D3DFORMAT)24;
    static const D3DFORMAT A1R5G5B5             = (D3DFORMAT)25;
    static const D3DFORMAT A4R4G4B4             = (D3DFORMAT)26;
    static const D3DFORMAT R3G3B2               = (D3DFORMAT)27;
    static const D3DFORMAT A8                   = (D3DFORMAT)28;
    static const D3DFORMAT A8R3G3B2             = (D3DFORMAT)29;
    static const D3DFORMAT X4R4G4B4             = (D3DFORMAT)30;
    static const D3DFORMAT A2B10G10R10          = (D3DFORMAT)31;
    static const D3DFORMAT A8B8G8R8             = (D3DFORMAT)32;
    static const D3DFORMAT X8B8G8R8             = (D3DFORMAT)33;
    static const D3DFORMAT G16R16               = (D3DFORMAT)34;
    static const D3DFORMAT A2R10G10B10          = (D3DFORMAT)35;
    static const D3DFORMAT A16B16G16R16         = (D3DFORMAT)36;

    static const D3DFORMAT A8P8                 = (D3DFORMAT)40;
    static const D3DFORMAT P8                   = (D3DFORMAT)41;

    static const D3DFORMAT L8                   = (D3DFORMAT)50;
    static const D3DFORMAT A8L8                 = (D3DFORMAT)51;
    static const D3DFORMAT A4L4                 = (D3DFORMAT)52;

    static const D3DFORMAT V8U8                 = (D3DFORMAT)60;
    static const D3DFORMAT L6V5U5               = (D3DFORMAT)61;
    static const D3DFORMAT X8L8V8U8             = (D3DFORMAT)62;
    static const D3DFORMAT Q8W8V8U8             = (D3DFORMAT)63;
    static const D3DFORMAT V16U16               = (D3DFORMAT)64;
    static const D3DFORMAT A2W10V10U10          = (D3DFORMAT)67;

    static const D3DFORMAT UYVY                 = (D3DFORMAT)MAKEFOURCC('U', 'Y', 'V', 'Y');
    static const D3DFORMAT R8G8_B8G8            = (D3DFORMAT)MAKEFOURCC('R', 'G', 'B', 'G');
    static const D3DFORMAT YUY2                 = (D3DFORMAT)MAKEFOURCC('Y', 'U', 'Y', '2');
    static const D3DFORMAT G8R8_G8B8            = (D3DFORMAT)MAKEFOURCC('G', 'R', 'G', 'B');
    static const D3DFORMAT DXT1                 = (D3DFORMAT)MAKEFOURCC('D', 'X', 'T', '1');
    static const D3DFORMAT DXT2                 = (D3DFORMAT)MAKEFOURCC('D', 'X', 'T', '2');
    static const D3DFORMAT DXT3                 = (D3DFORMAT)MAKEFOURCC('D', 'X', 'T', '3');
    static const D3DFORMAT DXT4                 = (D3DFORMAT)MAKEFOURCC('D', 'X', 'T', '4');
    static const D3DFORMAT DXT5                 = (D3DFORMAT)MAKEFOURCC('D', 'X', 'T', '5');

    static const D3DFORMAT D16_LOCKABLE         = (D3DFORMAT)70;
    static const D3DFORMAT D32                  = (D3DFORMAT)71;
    static const D3DFORMAT D15S1                = (D3DFORMAT)73;
    static const D3DFORMAT D24S8                = (D3DFORMAT)75;
    static const D3DFORMAT D24X8                = (D3DFORMAT)77;
    static const D3DFORMAT D24X4S4              = (D3DFORMAT)79;
    static const D3DFORMAT D16                  = (D3DFORMAT)80;

    static const D3DFORMAT D32F_LOCKABLE        = (D3DFORMAT)82;
    static const D3DFORMAT D24FS8               = (D3DFORMAT)83;

	#if !defined(D3D_DISABLE_9EX)

    static const D3DFORMAT D32_LOCKABLE         = (D3DFORMAT)84;
    static const D3DFORMAT S8_LOCKABLE          = (D3DFORMAT)85;

	#endif // !D3D_DISABLE_9EX

    static const D3DFORMAT L16                  = (D3DFORMAT)81;

    static const D3DFORMAT VERTEXDATA           = (D3DFORMAT)100;
    static const D3DFORMAT INDEX16              = (D3DFORMAT)101;
    static const D3DFORMAT INDEX32              = (D3DFORMAT)102;

    static const D3DFORMAT Q16W16V16U16         = (D3DFORMAT)110;

    static const D3DFORMAT MULTI2_ARGB8         = (D3DFORMAT)MAKEFOURCC('M', 'E', 'T', '1');

    static const D3DFORMAT R16F                 = (D3DFORMAT)111;
    static const D3DFORMAT G16R16F              = (D3DFORMAT)112;
    static const D3DFORMAT A16B16G16R16F        = (D3DFORMAT)113;

    static const D3DFORMAT R32F                 = (D3DFORMAT)114;
    static const D3DFORMAT G32R32F              = (D3DFORMAT)115;
    static const D3DFORMAT A32B32G32R32F        = (D3DFORMAT)116;

    static const D3DFORMAT CxV8U8               = (D3DFORMAT)117;

	#if !defined(D3D_DISABLE_9EX)

    static const D3DFORMAT A1                   = (D3DFORMAT)118;
    static const D3DFORMAT A2B10G10R10_XR_BIAS  = (D3DFORMAT)119;
    static const D3DFORMAT BINARYBUFFER         = (D3DFORMAT)199;

	#endif // !D3D_DISABLE_9EX
};

#pragma endregion

#pragma region RenderTarget2D

class RenderTarget2D : Texture2D
{
	private:
	
	IDirect3DSurface9* Data;

	public:

	int Width;
	int Height;

	RenderTarget2D(int Width, int Height, bool MipMap, DFormat SurfaceFormat);
};

#pragma endregion

#pragma region RenderTargetCube

class RenderTargetCube : TextureCube
{

};

#pragma endregion

#pragma endregion

#pragma region Audio

#pragma endregion

#pragma region Input

#pragma region Initialize

class Input
{
	friend class LMotor;
	friend class RMotor;
	public:
	static void Initialize();
};

#pragma endregion

#pragma region MouseState

class MouseState
{
	public:
	bool Left;
	bool Right;
	bool Middle;
	USHORT Wheel;

	Vector2 Position;
	Vector2 Velocity;
};

#pragma endregion

#pragma region Mouse

class Mouse
{
	public:
	static MouseState Cur;
	static MouseState Pre;

	static void Update();
};

#pragma endregion

#pragma region KeyboardState

#pragma region Keys

struct Keys
{
	static const BYTE Backspace    = 0x08;
	static const BYTE Tab          = 0x09;
	static const BYTE Enter        = 0x0D;
	static const BYTE Shift        = 0x10;  //Either Shift key 
	static const BYTE Control      = 0x11;  //Either Control Key
	static const BYTE Alt          = 0x12;
	static const BYTE Pause        = 0x13;
	static const BYTE Esc          = 0x1B;
	static const BYTE Space        = 0x20;
	static const BYTE PgUp         = 0x21;
	static const BYTE pgDn         = 0x22;
	static const BYTE End          = 0x23;
	static const BYTE Home         = 0x24;
	static const BYTE Left         = 0x25;
	static const BYTE Up           = 0x26;
	static const BYTE Right        = 0x27;
	static const BYTE Down         = 0x28;
	static const BYTE Select       = 0x29;
	static const BYTE Print        = 0x2A;
	static const BYTE Execute      = 0x2B;
	static const BYTE PrtSc        = 0x2C;
	static const BYTE Ins          = 0x2D;
	static const BYTE Del          = 0x2E;
	static const BYTE Help         = 0x2F;
	static const BYTE D0           = 0x30;
	static const BYTE D1           = 0x31;
	static const BYTE D2           = 0x32;
	static const BYTE D3           = 0x33;
	static const BYTE D4           = 0x34;
	static const BYTE D5           = 0x35;
	static const BYTE D6           = 0x36;
	static const BYTE D7           = 0x37;
	static const BYTE D8           = 0x38;
	static const BYTE D9           = 0x39;
	static const BYTE A            = 0x41;
	static const BYTE B            = 0x42;
	static const BYTE C            = 0x43;
	static const BYTE D            = 0x44;
	static const BYTE E            = 0x45;
	static const BYTE F            = 0x46;
	static const BYTE G            = 0x47;
	static const BYTE H            = 0x48;
	static const BYTE I            = 0x49;
	static const BYTE J            = 0x4A;
	static const BYTE K            = 0x4B;
	static const BYTE L            = 0x4C;
	static const BYTE M            = 0x4D;
	static const BYTE N            = 0x4E;
	static const BYTE O            = 0x4F;
	static const BYTE P            = 0x50;
	static const BYTE Q            = 0x51;
	static const BYTE R            = 0x52;
	static const BYTE S            = 0x53;
	static const BYTE T            = 0x54;
	static const BYTE U            = 0x55;
	static const BYTE V            = 0x56;
	static const BYTE W            = 0x57;
	static const BYTE X            = 0x58;
	static const BYTE Y            = 0x59;
	static const BYTE Z            = 0x5A;
	static const BYTE LWindows     = 0x5B;
	static const BYTE RWindows     = 0x5C;
	static const BYTE App          = 0x5D;
	static const BYTE Sleep        = 0x5F;
	static const BYTE Num0         = 0x60;
	static const BYTE Num1         = 0x61;
	static const BYTE Num2         = 0x62;
	static const BYTE Num3         = 0x63;
	static const BYTE Num4         = 0x64;
	static const BYTE Num5         = 0x65;
	static const BYTE Num6         = 0x66;
	static const BYTE Num7         = 0x67;
	static const BYTE Num8         = 0x68;
	static const BYTE Num9         = 0x69;
	static const BYTE Multiply     = 0x6A;
	static const BYTE Add          = 0x6B;
	static const BYTE Separator    = 0x6C;
	static const BYTE Subtract     = 0x6D;
	static const BYTE Decimal      = 0x6E;
	static const BYTE Divide       = 0x6F;
	static const BYTE F1           = 0x70;
	static const BYTE F2           = 0x71;
	static const BYTE F3           = 0x72;
	static const BYTE F4           = 0x73;
	static const BYTE F5           = 0x74;
	static const BYTE F6           = 0x75;
	static const BYTE F7           = 0x76;
	static const BYTE F8           = 0x77;
	static const BYTE F9           = 0x78;
	static const BYTE F10          = 0x79;
	static const BYTE F11          = 0x7A;
	static const BYTE F12          = 0x7B;
	static const BYTE F13          = 0x7C;
	static const BYTE F14          = 0x7D;
	static const BYTE F15          = 0x7E;
	static const BYTE F16          = 0x7F;
	static const BYTE F17          = 0x80;
	static const BYTE F18          = 0x81;
	static const BYTE F19          = 0x82;
	static const BYTE F20          = 0x83;
	static const BYTE F21          = 0x84;
	static const BYTE F22          = 0x85;
	static const BYTE F23          = 0x86;
	static const BYTE F24          = 0x87;
	static const BYTE LShift       = 0xA0;
	static const BYTE RShift       = 0xA1;
	static const BYTE LControl     = 0xA2;
	static const BYTE RControl     = 0xA3;
	static const BYTE BrowseBack   = 0xA6;
	static const BYTE BrowseForward = 0xA7;
	static const BYTE BrowseRefresh = 0xA8;
	static const BYTE BrowseStop    = 0xA9;
	static const BYTE BrowseSearch  = 0xAA;
	static const BYTE BrowseFav     = 0xAB;
	static const BYTE BrowseHome    = 0xAC;
	static const BYTE VolumeMute    = 0xAD;
	static const BYTE VolumeDown    = 0xAE;
	static const BYTE VolumeUp      = 0xAF;
	static const BYTE NextTrack     = 0xB0;
	static const BYTE PrevTrack     = 0xB1;
	static const BYTE StopTrack     = 0xB2;
	static const BYTE PlayPause     = 0xB3;
	static const BYTE StartMedia    = 0xB5;
	static const BYTE SemiColon     = 0xBA;
	static const BYTE Plus          = 0xBB;
	static const BYTE Comma         = 0xBC;
	static const BYTE Minus         = 0xBD;
	static const BYTE Period        = 0xBE;
	static const BYTE ForeSlash     = 0xBF;
	static const BYTE Tild          = 0xC0;
	static const BYTE OpenBracket   = 0xDB;
	static const BYTE BackSlash     = 0xDC;
	static const BYTE CloseBracket  = 0xDD;
	static const BYTE Qoute         = 0xDE;
	static const BYTE Play          = 0xFA;
	static const BYTE Zoom          = 0xFB;
	static const BYTE Clear         = 0xFE;
};

#pragma endregion

class KeyboardState
{
	friend class Keyboard;

	#pragma region private

	private:

	BYTE StateData[256];

	#pragma endregion

	#pragma region public

	public:

	#pragma region Members

	bool CapsLock;
	bool NumLock;
	bool ScrLock;

	#pragma endregion

	#pragma region Constructor

	KeyboardState()
	{	}

	#pragma endregion

	#pragma region KeyUp

	bool KeyUp(BYTE key);                      //Use the Structure Keys 

	#pragma endregion

	#pragma region KeyDown

	bool KeyDown(BYTE key);                    //Use the Structure Keys 

	#pragma endregion

	#pragma endregion
};

#pragma endregion

#pragma region Keyboard

class Keyboard
{
	friend class KeyboardState;

	public:

	#pragma region Members

	static KeyboardState Cur;
	static KeyboardState Pre;

	#pragma endregion

	#pragma region Methods

	static void Update();
	static bool KeyPressed(BYTE key);

	#pragma endregion
};

#pragma endregion

#pragma region GamePadState

#pragma region LeftState

struct LeftState
{
	Vector2 Thumb;
	FLOAT Trigger;
	FLOAT Motor;
	bool Bumper;
	bool Click;
};

#pragma endregion

#pragma region RightState

struct RightState
{
	Vector2 Thumb;
	FLOAT Trigger;
	FLOAT Motor;
	bool Bumper;
	bool Click;
};

#pragma endregion

#pragma region DPadState

struct DPadState
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

#pragma endregion

class GamePadState
{
	friend class GamePads;
	private:
	uint PacketNumber;
	public:
	LeftState Left;
	RightState Right;
	DPadState DPad;

	bool A;
	bool X;
	bool Y;
	bool B;

	bool Back;
	bool Start;
};

#pragma endregion

#pragma region GamePads

class GamePads
{
	friend class GamePadState;
	public:
	static GamePads Pads[4];

	GamePadState Cur;
	GamePadState Pre;

	static void Update();
};

#pragma endregion

#pragma endregion

#pragma region Multiplayer

#pragma endregion

#pragma region Inlines

#pragma region Vector2

#pragma region Operator

D3DXINLINE Vector2::operator const D3DXVECTOR2&() const { return *(D3DXVECTOR2*)this; }

D3DXINLINE Vector2 Vector2::operator+(const Vector2 &V) const { return Vector2(this->X + V.X, this->Y + V.Y); }
D3DXINLINE Vector2 Vector2::operator-(const Vector2 &V) const { return Vector2(this->X - V.X, this->Y - V.Y); }
D3DXINLINE Vector2 Vector2::operator*(const Vector2 &V) const { return Vector2(this->X * V.X, this->Y * V.Y); }
D3DXINLINE Vector2 Vector2::operator/(const Vector2 &V) const { return Vector2(this->X / V.X, this->Y / V.Y); }
D3DXINLINE Vector2 Vector2::operator%(const Vector2 &V) const { return Vector2(fmod(this->X, V.X), fmod(this->Y, V.Y)); }
	
D3DXINLINE Vector2 Vector2::operator+(const FLOAT &S) const { return Vector2(this->X + S, this->Y + S); }
D3DXINLINE Vector2 Vector2::operator-(const FLOAT &S) const { return Vector2(this->X - S, this->Y - S); }
D3DXINLINE Vector2 Vector2::operator*(const FLOAT &S) const { return Vector2(this->X * S, this->Y * S); }
D3DXINLINE Vector2 Vector2::operator/(const FLOAT &S) const { return Vector2(this->X / S, this->Y / S); }
D3DXINLINE Vector2 Vector2::operator%(const FLOAT &S) const { return Vector2(fmod(this->X, S), fmod(this->Y, S)); }

D3DXINLINE Vector2 Vector2::operator+=(const Vector2 &V) { this->X += V.X; this->Y += V.Y; return *this; }
D3DXINLINE Vector2 Vector2::operator-=(const Vector2 &V) { this->X -= V.X; this->Y -= V.Y; return *this; }
D3DXINLINE Vector2 Vector2::operator*=(const Vector2 &V) { this->X *= V.X; this->Y *= V.Y; return *this; }
D3DXINLINE Vector2 Vector2::operator/=(const Vector2 &V) { this->X /= V.X; this->Y /= V.Y; return *this; }
D3DXINLINE Vector2 Vector2::operator%=(const Vector2 &V) { this->X = fmod(this->X, V.X); this->Y = fmod(this->Y, V.Y); return *this; }

D3DXINLINE Vector2 Vector2::operator+=(const FLOAT &S) { this->X += S; this->Y += S; return *this; }
D3DXINLINE Vector2 Vector2::operator-=(const FLOAT &S) { this->X -= S; this->Y -= S; return *this; }
D3DXINLINE Vector2 Vector2::operator*=(const FLOAT &S) { this->X *= S; this->Y *= S; return *this; }
D3DXINLINE Vector2 Vector2::operator/=(const FLOAT &S) { this->X /= S; this->Y /= S; return *this; }
D3DXINLINE Vector2 Vector2::operator%=(const FLOAT &S) { this->X = fmod(this->X, S); this->Y = fmod(this->Y, S); return *this; }
	
D3DXINLINE Vector2 operator+(const FLOAT &S, const Vector2 &V) { return Vector2(S + V.X, S + V.Y); }
D3DXINLINE Vector2 operator-(const FLOAT &S, const Vector2 &V) { return Vector2(S - V.X, S - V.Y); }
D3DXINLINE Vector2 operator*(const FLOAT &S, const Vector2 &V) { return Vector2(S * V.X, S * V.Y); }
D3DXINLINE Vector2 operator/(const FLOAT &S, const Vector2 &V) { return Vector2(S / V.X, S / V.Y); }

D3DXINLINE Vector2 Vector2::operator=(const Vector2 &V) { this->X = V.X; this->Y = V.Y; return *this; }
D3DXINLINE BOOL Vector2::operator==(const Vector2 &V) const { return (this->X == V.X && this->Y == V.Y); }
D3DXINLINE BOOL Vector2::operator!=(const Vector2 &V) const { return (this->X != V.X && this->Y != V.Y); }
	
D3DXINLINE Vector2 Vector2::operator-() const { return Vector2(-this->X, -this->Y); }
D3DXINLINE Vector2 Vector2::operator~() const { FLOAT tmp = !(*this); return Vector2(this->X / tmp, this->Y / tmp); }
D3DXINLINE FLOAT   Vector2::operator!() const { return sqrtf(this->X * this->X + this->Y * this->Y); }

#pragma endregion 

#pragma region Methods

D3DXINLINE Vector2 Vector2::Lerp(const Vector2 &V1, const Vector2 &V2, const FLOAT &S)
{
	return Vector2(V1.X + S * (V2.X - V1.X), V1.Y + S * (V2.Y - V1.Y));
}
	
D3DXINLINE FLOAT Vector2::Dot(const Vector2 &V1, const Vector2 &V2)
{
	return V1.X * V2.X + V1.Y * V2.Y;
}

D3DXINLINE FLOAT Vector2::CCW(const Vector2 &V1, const Vector2 &V2)
{
	return V1.X * V2.Y - V2.X * V1.Y;
}

D3DXINLINE Vector2 Vector2::Min(const Vector2 &V1, const Vector2 &V2)
{
	return Vector2((V1.X < V2.X ? V1.X : V2.X), (V1.Y < V2.Y ? V1.Y : V2.Y));
}

D3DXINLINE Vector2 Vector2::Max(const Vector2 &V1, const Vector2 &V2)
{
	return Vector2((V1.X > V2.X ? V1.X : V2.X), (V1.Y > V2.Y ? V1.Y : V2.Y));
}

#pragma endregion

#pragma endregion

#pragma region Vector3

#pragma region Operators

//D3DXINLINE Vector3::operator const D3DXVECTOR3&() const { return *(const D3DXVECTOR3*)this; }

D3DXINLINE Vector3 Vector3::operator+(const Vector3 &V) const { return Vector3(this->X + V.X, this->Y + V.Y, this->Z + V.Z); }
D3DXINLINE Vector3 Vector3::operator-(const Vector3 &V) const { return Vector3(this->X - V.X, this->Y - V.Y, this->Z - V.Z); }
D3DXINLINE Vector3 Vector3::operator*(const Vector3 &V) const { return Vector3(this->X * V.X, this->Y * V.Y, this->Z * V.Z); }
D3DXINLINE Vector3 Vector3::operator/(const Vector3 &V) const { return Vector3(this->X / V.X, this->Y / V.Y, this->Z / V.Z); }
D3DXINLINE Vector3 Vector3::operator%(const Vector3 &V) const { return Vector3(fmod(this->X, V.X), fmod(this->Y, V.Y), fmod(this->Z, V.Z)); }
	
D3DXINLINE Vector3 Vector3::operator+(const FLOAT &S) const { return Vector3(this->X + S, this->Y + S, this->Z + S); }
D3DXINLINE Vector3 Vector3::operator-(const FLOAT &S) const { return Vector3(this->X - S, this->Y - S, this->Z - S); }
D3DXINLINE Vector3 Vector3::operator*(const FLOAT &S) const { return Vector3(this->X * S, this->Y * S, this->Z * S); }
D3DXINLINE Vector3 Vector3::operator/(const FLOAT &S) const { return Vector3(this->X / S, this->Y / S, this->Z / S); }
D3DXINLINE Vector3 Vector3::operator%(const FLOAT &S) const { return Vector3(fmod(this->X, S), fmod(this->Y, S), fmod(this->Z, S)); }

D3DXINLINE Vector3 Vector3::operator+=(const Vector3 &V) { this->X += V.X; this->Y += V.Y; this->Z += V.Z; return *this; }
D3DXINLINE Vector3 Vector3::operator-=(const Vector3 &V) { this->X -= V.X; this->Y -= V.Y; this->Z -= V.Z; return *this; }
D3DXINLINE Vector3 Vector3::operator*=(const Vector3 &V) { this->X *= V.X; this->Y *= V.Y; this->Z *= V.Z; return *this; }
D3DXINLINE Vector3 Vector3::operator/=(const Vector3 &V) { this->X /= V.X; this->Y /= V.Y; this->Z /= V.Z; return *this; }
D3DXINLINE Vector3 Vector3::operator%=(const Vector3 &V) { this->X = fmod(this->X, V.X); this->Y = fmod(this->Y, V.Y); this->Z = fmod(this->Z, V.Z); return *this; }

D3DXINLINE Vector3 Vector3::operator+=(const FLOAT &S) { this->X += S; this->Y += S; this->Z += S; return *this; }
D3DXINLINE Vector3 Vector3::operator-=(const FLOAT &S) { this->X -= S; this->Y -= S; this->Z -= S; return *this; }
D3DXINLINE Vector3 Vector3::operator*=(const FLOAT &S) { this->X *= S; this->Y *= S; this->Z *= S; return *this; }
D3DXINLINE Vector3 Vector3::operator/=(const FLOAT &S) { this->X /= S; this->Y /= S; this->Z /= S; return *this; }
D3DXINLINE Vector3 Vector3::operator%=(const FLOAT &S) { this->X = fmod(this->X, S); this->Y = fmod(this->Y, S); this->Z = fmod(this->Z, S); return *this; }
	
D3DXINLINE Vector3 operator+(const FLOAT &S, const Vector3 &V) { return Vector3(S + V.X, S + V.Y, S + V.Z); }
D3DXINLINE Vector3 operator-(const FLOAT &S, const Vector3 &V) { return Vector3(S - V.X, S - V.Y, S - V.Z); }
D3DXINLINE Vector3 operator*(const FLOAT &S, const Vector3 &V) { return Vector3(S * V.X, S * V.Y, S * V.Z); }
D3DXINLINE Vector3 operator/(const FLOAT &S, const Vector3 &V) { return Vector3(S / V.X, S / V.Y, S / V.Z); }

D3DXINLINE Vector3 Vector3::operator=(const Vector3 &V) { this->X = V.X; this->Y = V.Y; this->Z = V.Z; return *this; }
D3DXINLINE BOOL Vector3::operator==(const Vector3 &V) const { return (this->X == V.X && this->Y == V.Y && this->Z == V.Z); }
D3DXINLINE BOOL Vector3::operator!=(const Vector3 &V) const { return (this->X != V.X && this->Y != V.Y && this->Z == V.Z); }
	
D3DXINLINE Vector3 Vector3::operator-() const { return Vector3(-this->X, -this->Y, -this->Z); }
D3DXINLINE Vector3 Vector3::operator~() const { FLOAT tmp = !(*this); return Vector3(this->X / tmp, this->Y / tmp, this->Z / tmp); }
D3DXINLINE FLOAT   Vector3::operator!() const { return sqrtf(this->X * this->X + this->Y * this->Y + this->Z * this->Z); }

#pragma endregion

#pragma region Methods

D3DXINLINE Vector3 Vector3::Lerp(const Vector3 &V1, const Vector3 &V2, const FLOAT &S)
{
	return Vector3(V1.X + S * (V2.X - V1.X), V1.Y + S * (V2.Y - V1.Y), V1.Z + S * (V2.Z - V1.Z));
}
	
D3DXINLINE FLOAT Vector3::Dot(const Vector3 &V1, const Vector3 &V2)
{
	return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

D3DXINLINE Vector3 Vector3::Cross(const Vector3 &V1, const Vector3 &V2)
{
	return Vector3(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

D3DXINLINE Vector3 Vector3::Min(const Vector3 &V1, const Vector3 &V2)
{
	return Vector3((V1.X < V2.X ? V1.X : V2.X), (V1.Y < V2.Y ? V1.Y : V2.Y), (V1.Z < V2.Z ? V1.Z : V2.Z));
}

D3DXINLINE Vector3 Vector3::Max(const Vector3 &V1, const Vector3 &V2)
{
	return Vector3((V1.X > V2.X ? V1.X : V2.X), (V1.Y > V2.Y ? V1.Y : V2.Y), (V1.Z > V2.Z ? V1.Z : V2.Z));
}

#pragma endregion

#pragma endregion

#pragma region Vector4

#pragma region Operators

D3DXINLINE Vector4::operator const D3DXVECTOR4&() const { return *(D3DXVECTOR4*)this; }
D3DXINLINE Vector4::operator const D3DXQUATERNION&() const { return *(D3DXQUATERNION*)this; }
D3DXINLINE Vector4::operator const D3DXPLANE&() const { return *(D3DXPLANE*)this; }

D3DXINLINE Vector4 Vector4::operator+(const Vector4 &V) const { return Vector4(this->X + V.X, this->Y + V.Y, this->Z + V.Z, this->W + V.W); }
D3DXINLINE Vector4 Vector4::operator-(const Vector4 &V) const { return Vector4(this->X - V.X, this->Y - V.Y, this->Z - V.Z, this->Z + V.W); }
D3DXINLINE Vector4 Vector4::operator*(const Vector4 &V) const { return Vector4(this->X * V.X, this->Y * V.Y, this->Z * V.Z, this->W + V.W); }
D3DXINLINE Vector4 Vector4::operator/(const Vector4 &V) const { return Vector4(this->X / V.X, this->Y / V.Y, this->Z / V.Z, this->W + V.W); }
D3DXINLINE Vector4 Vector4::operator%(const Vector4 &V) const { return Vector4(fmod(this->X, V.X), fmod(this->Y, V.Y), fmod(this->Z, V.Z), fmod(this->W, V.W)); }
	
D3DXINLINE Vector4 Vector4::operator+(const FLOAT &S) const { return Vector4(this->X + S, this->Y + S, this->Z + S, this->W + S); }
D3DXINLINE Vector4 Vector4::operator-(const FLOAT &S) const { return Vector4(this->X - S, this->Y - S, this->Z - S, this->W + S); }
D3DXINLINE Vector4 Vector4::operator*(const FLOAT &S) const { return Vector4(this->X * S, this->Y * S, this->Z * S, this->W + S); }
D3DXINLINE Vector4 Vector4::operator/(const FLOAT &S) const { return Vector4(this->X / S, this->Y / S, this->Z / S, this->W + S); }
D3DXINLINE Vector4 Vector4::operator%(const FLOAT &S) const { return Vector4(fmod(this->X, S), fmod(this->Y, S), fmod(this->Z, S), fmod(this->W, S)); }

D3DXINLINE Vector4 Vector4::operator+=(const Vector4 &V) { this->X += V.X; this->Y += V.Y; this->Z += V.Z; this->W += V.W; return *this; }
D3DXINLINE Vector4 Vector4::operator-=(const Vector4 &V) { this->X -= V.X; this->Y -= V.Y; this->Z -= V.Z; this->W += V.W; return *this; }
D3DXINLINE Vector4 Vector4::operator*=(const Vector4 &V) { this->X *= V.X; this->Y *= V.Y; this->Z *= V.Z; this->W += V.W; return *this; }
D3DXINLINE Vector4 Vector4::operator/=(const Vector4 &V) { this->X /= V.X; this->Y /= V.Y; this->Z /= V.Z; this->W += V.W; return *this; }
D3DXINLINE Vector4 Vector4::operator%=(const Vector4 &V) { this->X = fmod(this->X, V.X); this->Y = fmod(this->Y, V.Y); this->Z = fmod(this->Z, V.Z); this->W = fmod(this->W, V.W); return *this; }

D3DXINLINE Vector4 Vector4::operator+=(const FLOAT &S) { this->X += S; this->Y += S; this->Z += S; this->W += S; return *this; }
D3DXINLINE Vector4 Vector4::operator-=(const FLOAT &S) { this->X -= S; this->Y -= S; this->Z -= S; this->W += S; return *this; }
D3DXINLINE Vector4 Vector4::operator*=(const FLOAT &S) { this->X *= S; this->Y *= S; this->Z *= S; this->W += S; return *this; }
D3DXINLINE Vector4 Vector4::operator/=(const FLOAT &S) { this->X /= S; this->Y /= S; this->Z /= S; this->W += S; return *this; }
D3DXINLINE Vector4 Vector4::operator%=(const FLOAT &S) { this->X = fmod(this->X, S); this->Y = fmod(this->Y, S); this->Z = fmod(this->Z, S); this->W = fmod(this->W, S); return *this; }
	
D3DXINLINE Vector4 operator+(const FLOAT &S, const Vector4 &V) { return Vector4(S + V.X, S + V.Y, S + V.Z, S + V.W); }
D3DXINLINE Vector4 operator-(const FLOAT &S, const Vector4 &V) { return Vector4(S - V.X, S - V.Y, S - V.Z, S + V.W); }
D3DXINLINE Vector4 operator*(const FLOAT &S, const Vector4 &V) { return Vector4(S * V.X, S * V.Y, S * V.Z, S + V.W); }
D3DXINLINE Vector4 operator/(const FLOAT &S, const Vector4 &V) { return Vector4(S / V.X, S / V.Y, S / V.Z, S + V.W); }

D3DXINLINE Vector4 Vector4::operator=(const Vector4 &V) { this->X = V.X; this->Y = V.Y; this->Z = V.Z; this->W = V.W; return *this; }
D3DXINLINE BOOL Vector4::operator==(const Vector4 &V) const { return (this->X == V.X && this->Y == V.Y && this->Z == V.Z && this->W == V.W); }
D3DXINLINE BOOL Vector4::operator!=(const Vector4 &V) const { return (this->X != V.X && this->Y != V.Y && this->Z != V.Z && this->W != V.W); }
	
D3DXINLINE Vector4 Vector4::operator-() const { return Vector4(-this->X, -this->Y, -this->Z, -this->W); }
D3DXINLINE Vector4 Vector4::operator~() const { FLOAT tmp = !(*this); return Vector4(this->X / tmp, this->Y / tmp, this->Z / tmp, this->W / tmp); }
D3DXINLINE FLOAT   Vector4::operator!() const { return sqrtf(this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W); }

#pragma endregion

#pragma region Methods

D3DXINLINE Vector4 Vector4::Lerp(const Vector4 &V1, const Vector4 &V2, const FLOAT &S)
{
	return Vector4(V1.X + S * (V2.X - V1.X), V1.Y + S * (V2.Y - V1.Y), V1.Z + S * (V2.Z - V1.Z), V1.W + S * (V2.W - V1.W));
}
	
D3DXINLINE FLOAT Vector4::Dot(const Vector4 &V1, const Vector4 &V2)
{
	return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z + V1.W * V2.W;
}

D3DXINLINE Vector4 Vector4::Min(const Vector4 &V1, const Vector4 &V2)
{
	return Vector4((V1.X < V2.X ? V1.X : V2.X), (V1.Y < V2.Y ? V1.Y : V2.Y), (V1.Z < V2.Z ? V1.Z : V2.Z), (V1.W < V2.W ? V1.W : V2.W));
}

D3DXINLINE Vector4 Vector4::Max(const Vector4 &V1, const Vector4 &V2)
{
	return Vector4((V1.X > V2.X ? V1.X : V2.X), (V1.Y > V2.Y ? V1.Y : V2.Y), (V1.Z > V2.Z ? V1.Z : V2.Z), (V1.W > V2.W ? V1.W : V2.W));
}


#pragma endregion

#pragma endregion

#pragma endregion

}

#endif