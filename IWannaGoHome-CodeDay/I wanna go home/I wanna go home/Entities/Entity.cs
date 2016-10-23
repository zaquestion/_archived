using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace Engine
{
    public abstract class Entity
    {
        #region Members

        public V.PT[] VerticesPT { get; set; }
        public int[] Indices { get; set; }
        public Effect effect { get; set; }

        public Texture2D[] texs { get; set; }

        public Vector2 Pos;



        #endregion

        #region Constructor

        public Entity(Texture2D[] texs, Vector2 Pos)
        {
            this.VerticesPT = new V.PT[] 
            { 
                new V.PT(new Vector3(0, 0, 0), new Vector2(0, 0)),
                new V.PT(new Vector3(texs[0].Width, 0, 0), new Vector2(1, 0)),
                new V.PT(new Vector3(texs[0].Width, texs[0].Height, 0), new Vector2(1, 1)),
                new V.PT(new Vector3(0, texs[0].Height, 0), new Vector2(0, 1))
            };

            this.Indices = new int[] { 0, 1, 2, 2, 3, 0 };
            this.Pos = Pos;

            this.texs = texs;
        }

        #endregion

        #region Methods

        public abstract void Update(GameTime Time);
        public abstract void Draw(GameTime Time, Camera2D cam, Vector2 Ppos);

        public void DoColisions(bool[,] Mask, Camera2D cam)
        {
            int x = (int)Pos.X;
            int y = (int)Pos.Y;

            if (Mask[x, y])
            {

                for (int i = 0; i < 50; i++)
                {
                    int l = x - i;
                    int r = x + i;
                    int u = y - i;
                    int d = y + i;

                    if (l > 0)
                    {
                        if (!Mask[l, y]) { Pos.X = l; break; }
                        if (r < Constants.NumSX * 1280)
                        {
                            if (!Mask[r, y]) { Pos.X = r; break; }
                        }
                    }

                    if (u > 0)
                    {
                        if (!Mask[x, u]) { Pos.Y = u; break; }
                        if (d < Constants.NumSY * 720)
                        {
                            if (!Mask[x, d]) { Pos.Y = d; break; }
                        }
                    }
                }
            }
        }

        #endregion
    }
}

