using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using System.Collections.Generic;
using Microsoft.Xna.Framework.Graphics;

namespace Engine
{
    public class Render : System
    {
        Effect VPT = Game1.ContentM.Load<Effect>("vpt");

        #region Constructor

        public Render()
        {
            VPT.Parameters["P"].SetValue(Matrix.CreateOrthographicOffCenter(0, Graphics.Width, Graphics.Height, 0, 0, 1));
        }

        #endregion

        #region Update

        void System.Update(Dictionary<Guid, Object> Objects)
        {
            foreach (var Object in Objects)
            {
                Sprite Sprite;
                Primitive<V.PT> PrimitivePT;
                Position Pos;

                foreach (var Component in Object.Value.Components)
                {
                    if (Component.ID == "Sprite") Sprite = (Sprite)Component; else break;
                    
                    if (typeof(Primitive<V.PT>) == Component) PrimitivePT = (Primitive<V.PT>)Component; else break;

                    if (Component.ID == "Position") Pos = (Position)Component; else break;

                }

                VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(Pos.Pos, 0)));
                VPT.Parameters["Texture"].SetValue(Sprite.Texture);
                
                Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitivePT.Type, PrimitivePT.Vertices, 0, PrimitivePT.Vertices.Length, PrimitivePT.Indices, 0, PrimitivePT.Count);
            }
        }

        #endregion
    }
}