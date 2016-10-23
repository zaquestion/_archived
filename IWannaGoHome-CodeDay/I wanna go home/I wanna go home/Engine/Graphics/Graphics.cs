using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Engine
{
    #region Graphics

    public static class Graphics
    {
        public static GraphicsDeviceManager Manager { get { return Game1.Manager; } }
        public static GraphicsDevice Device { get { return Game1.Manager.GraphicsDevice; } }

        public static int Width { get { return Device.Viewport.Width; } }
        public static int Height { get { return Device.Viewport.Height; } }
    }

    #endregion

    #region Camera

    #region Base

    public class Camera
    {
        #region Members

        public Matrix View;
        public Matrix Proj;
        public Vector3 Pos;

        #endregion

        #region Constructor

        public Camera()
        {

        }

        #endregion 

        #region Update

        public virtual void Update() { }

        #endregion
    }

    #endregion

    #region Camera2D

    public class Camera2D : Camera
    {
        #region Members

        public float Scl;

        Vector3 Cnt;

        #endregion

        #region Constructor

        public Camera2D(Vector2 Pos)
        {
            this.Scl = 1;
            this.Pos = new Vector3(Pos, 0);
            this.Cnt = new Vector3(1280 / 2, 720 / 2, 0.0f);
            this.View = Matrix.CreateTranslation(Cnt - this.Pos);
            this.Proj = Matrix.CreateOrthographicOffCenter(0, 1280, 720, 0, 0, 1);
        }

        #endregion

        #region Update

        public override void Update()
        {
            View = Matrix.CreateTranslation((Cnt - Pos));
        }

        #endregion
    }

    #endregion

    #endregion

    #region Vertex

    public struct V
    {
        #region Formats

        #region Position

        public struct P : IVertexType
        {
            public Vector3 Pos;

            VertexDeclaration IVertexType.VertexDeclaration { get { return VertexDeclaration; } }

            public P(Vector3 Pos)
            {
                this.Pos = Pos;
            }

            public static readonly VertexDeclaration VertexDeclaration = new VertexDeclaration
            (
                new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0)
            );
        }

        #endregion

        #region Position Color

        public struct PC : IVertexType
        {
            public Vector3 Pos;
            public Vector4 Col;

            VertexDeclaration IVertexType.VertexDeclaration { get { return VertexDeclaration; } }

            public PC(Vector3 Pos, Vector4 Col)
            {
                this.Pos = Pos;
                this.Col = Col;
            }

            public static readonly VertexDeclaration VertexDeclaration = new VertexDeclaration
            (
            new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector4, VertexElementUsage.Color, 0)
            );

            public static PC[] CreateRectangle(float Width, float Height, Color Color)
            {
                return new PC[]
                {
                    new PC(new Vector3(-0.5f * Width, -0.5f * Height, 0), Color.ToVector4()),
                    new PC(new Vector3(0.5f * Width, -0.5f * Height, 0), Color.ToVector4()),
                    new PC(new Vector3(-0.5f * Width, 0.5f * Height, 0), Color.ToVector4()),
                    new PC(new Vector3(0.5f * Width, 0.5f * Height, 0), Color.ToVector4()),
                };
            }
        }

        #endregion

        #region Position Texture

        public struct PT : IVertexType
        {
            public Vector3 Pos;
            public Vector2 Tex;

            VertexDeclaration IVertexType.VertexDeclaration { get { return VertexDeclaration; } }

            public PT(Vector3 Pos, Vector2 Tex)
            {
                this.Pos = Pos;
                this.Tex = Tex;
            }

            public static readonly VertexDeclaration VertexDeclaration = new VertexDeclaration
            (
            new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector2, VertexElementUsage.TextureCoordinate, 0)
            );
            public static PT[] CreateRectangle(float Width, float Height)
            {
                return new PT[]
                {
                    new PT(new Vector3(-0.5f * Width, -0.5f * Height, 0), new Vector2(-0.5f, -0.5f)),
                    new PT(new Vector3(0.5f * Width, -0.5f * Height, 0), new Vector2(0.5f, -0.5f)),
                    new PT(new Vector3(-0.5f * Width, 0.5f * Height, 0), new Vector2(-0.5f, 0.5f)),
                    new PT(new Vector3(0.5f * Width, 0.5f * Height, 0), new Vector2(0.5f, 0.5f)),
                };
            }
        }

        #endregion

        #region Position Color Texture

        public struct PCT : IVertexType
        {
            public Vector3 Pos;
            public Vector4 Col;
            public Vector2 Tex;

            VertexDeclaration IVertexType.VertexDeclaration { get { return VertexDeclaration; } }

            public PCT(Vector3 Pos, Vector4 Col, Vector2 Tex)
            {
                this.Pos = Pos;
                this.Col = Col;
                this.Tex = Tex;
            }

            public static readonly VertexDeclaration VertexDeclaration = new VertexDeclaration
            (
            new VertexElement(00, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector4, VertexElementUsage.Color, 0),
            new VertexElement(28, VertexElementFormat.Vector2, VertexElementUsage.TextureCoordinate, 0)
            );
        }

        #endregion

        #region Position Color Normal Texture

        public struct PNT : IVertexType
        {
            public Vector3 Pos;
            public Vector3 Nml;
            public Vector2 Tex;

            VertexDeclaration IVertexType.VertexDeclaration { get { return VertexDeclaration; } }

            public PNT(Vector3 Pos, Vector3 Nml, Vector2 Tex)
            {
                this.Pos = Pos;
                this.Nml = Nml;
                this.Tex = Tex;
            }

            public static readonly VertexDeclaration VertexDeclaration = new VertexDeclaration
            (
            new VertexElement(00, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector3, VertexElementUsage.Normal, 0),
            new VertexElement(24, VertexElementFormat.Vector2, VertexElementUsage.TextureCoordinate, 0)
            );
        }

        #endregion

        #endregion
    }

    #endregion
}
