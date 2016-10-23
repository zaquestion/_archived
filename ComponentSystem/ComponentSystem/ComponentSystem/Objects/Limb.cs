using Microsoft.Xna.Framework;
using System.Collections.Generic;
using Microsoft.Xna.Framework.Graphics;
using System;

namespace Engine
{
    public class Limb : Object
    {
        #region Members

        public List<Component> Components { get; set; }

        #endregion

        #region Constructor

        public Limb(Texture2D Tex)
        {
            Components = new List<Component>();

            Sprite sprite = new Sprite();
            sprite.Texture = Tex;
            Components.Add(sprite);

            Primitive<V.PT> primitive = new Primitive<V.PT>();
            primitive.Type = PrimitiveType.TriangleList;
            primitive.Vertices = new V.PT[] 
            {
                new V.PT(Vector3.Zero, Vector2.Zero),
                new V.PT(new Vector3(Tex.Width, 0, 0), new Vector2(1, 0)),
                new V.PT(new Vector3(Tex.Width, Tex.Height, 0), new Vector2(1, 1)),
                new V.PT(new Vector3(0, Tex.Height, 0), new Vector2(0, 1))
            };
            primitive.Indices = new int[] { 0, 1, 2, 2, 3, 0 };
            primitive.Count = 2;
            Components.Add(primitive);
        }

        #endregion

        #region Methods

        #endregion
    }
}

