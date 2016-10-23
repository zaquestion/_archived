using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace Engine
{
    public class Enemy : Entity
    {
        #region Members

        #endregion

        #region Constructor

        public Enemy(Texture2D[] texs, Vector2 Pos, Effect effect)
            : base(texs, Pos)
        {
            this.effect = effect;
            effect.Parameters["P"].SetValue(Matrix.CreateOrthographicOffCenter(0, 1280, 720, 0, 0, 1));
        }

        #endregion

        #region Methods

        public override void Update(GameTime Time)
        {

        }

        public override void Draw(GameTime Time, Camera2D cam, Vector2 Ppos)
        {
            effect.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(-15, -15, 0)) * Matrix.CreateScale(2) * Matrix.CreateTranslation(new Vector3(Pos, 0)) * cam.View);


            if (Vector2.Distance(Pos, Ppos) > 120)
                effect.Parameters["Texture"].SetValue(texs[0]);
            else
                effect.Parameters["Texture"].SetValue(texs[1]);


            effect.CurrentTechnique.Passes[0].Apply();

            Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, VerticesPT, 0, VerticesPT.Length, Indices, 0, 2);
        }

        #endregion
    }
}

