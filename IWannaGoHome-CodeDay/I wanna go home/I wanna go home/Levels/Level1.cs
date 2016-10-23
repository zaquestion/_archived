using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using Microsoft.Xna.Framework.Audio;

namespace Engine
{
    public class Level1 : GameScreen
    {
        #region Members

        V.PT[] nVerticesPT { get; set; }
        V.PT[] VerticesPT { get; set; }
        int[] Indices { get; set; }

        Effect VPT { get; set; }

        Camera2D cam { get; set; }

        Texture2D[,] Texs { get; set; }
        Texture2D[] SomeTexs { get; set; }

        Texture2D start { get; set; }

        Texture2D end { get; set; }

        SoundEffect sfx;

        #endregion

        #region Initialize

        public override void Initialize()
        {
       
            base.Initialize();
        }

        #endregion

        bool starting = true;
        bool ending = false;
        #region Load Content

        public override void LoadContent()
        {
            Entities.Add(new Player(new Texture2D[] { Content.Load<Texture2D>("Entities\\Player\\playerfront"), Content.Load<Texture2D>("Entities\\Player\\1"), Content.Load<Texture2D>("Entities\\Player\\2") }, new Vector2(200, 200), Content.Load<Effect>("Effects\\vpt")));
            Entities.Add(new Enemy(new Texture2D[] { Content.Load<Texture2D>("Entities\\littlegirl\\littlegirlfront"), Content.Load<Texture2D>("Entities\\littlegirl\\littlegirlfront_creepy") }, new Vector2(600, 400), Content.Load<Effect>("Effects\\vpt")));
            Entities.Add(new Enemy(new Texture2D[] { Content.Load<Texture2D>("Entities\\bunny\\bunnyfront"), Content.Load<Texture2D>("Entities\\bunny\\bunnyfront_creepy") }, new Vector2(1400, 400), Content.Load<Effect>("Effects\\vpt")));
            Entities.Add(new Enemy(new Texture2D[] { Content.Load<Texture2D>("Entities\\jelly\\jellyfront"), Content.Load<Texture2D>("Entities\\jelly\\jellyfront_creepy") }, new Vector2(1000, 400), Content.Load<Effect>("Effects\\vpt")));

            cam = new Camera2D(Entities[0].Pos);
            VPT = Content.Load<Effect>("Effects\\vpt");
            VPT.Parameters["P"].SetValue(Matrix.CreateOrthographicOffCenter(0, 1280, 720, 0, 0, 1));

            sfx = Content.Load<SoundEffect>("song");
            SoundEffectInstance sfxi = sfx.CreateInstance();
            sfxi.IsLooped = true;
            sfxi.Play();

            start = Content.Load<Texture2D>("start");
            end = Content.Load<Texture2D>("end");

            

            SomeTexs = new Texture2D[4];
            for (int i = 0; i < 4; i++)
                SomeTexs[i] = Content.Load<Texture2D>("characterpoint" + (i + 1));

            //load base.texs here
            #region Base Info

            base.Mask = new bool[1280 * Constants.NumSX, 720 * Constants.NumSY];
            base.MaskTexs = new Texture2D[Constants.NumSX, Constants.NumSY];

            Texs = new Texture2D[Constants.NumSX, Constants.NumSY];
            

            for (int xi = 0; xi < Constants.NumSX; xi++)
            {
                for (int yi = 0; yi < Constants.NumSY; yi++)
                {
                    //MaskTexs[xi, yi] = Content.Load<Texture2D>(".//Level1/xi + "," + yi);
                    Texs[xi, yi] = Content.Load<Texture2D>("Level\\Tex\\background_0" + (xi + yi * 3 + 1));
                }
            }

           // try
            //{
                for (int xi = 0; xi < Constants.NumSX; xi++)
                {
                    for (int yi = 0; yi < Constants.NumSY; yi++)
                    {
                        //MaskTexs[xi, yi] = Content.Load<Texture2D>(".//Level1/xi + "," + yi);
                        MaskTexs[xi, yi] = Content.Load<Texture2D>("Level\\Masks\\background_0" + (xi + yi * 3 + 1) + "mask");
                    }
                }
           // }

            base.LoadContent();

            #endregion

            #region Drawing crap

            VerticesPT = new V.PT[]
            {
                new V.PT(new Vector3(0, 0, 0), new Vector2(0, 0)),
                new V.PT(new Vector3(1280, 0, 0), new Vector2(1,0)),
                new V.PT(new Vector3(1280, 720, 0), new Vector2(1,1)),
                new V.PT(new Vector3(0,720,0), new Vector2(0,1))
            };
            nVerticesPT = new V.PT[]
            {
                new V.PT(new Vector3(0, 0, 0), new Vector2(0, 0)),
                new V.PT(new Vector3(SomeTexs[0].Width, 0, 0), new Vector2(1,0)),
                new V.PT(new Vector3(SomeTexs[0].Width, SomeTexs[0].Height, 0), new Vector2(1,1)),
                new V.PT(new Vector3(0,SomeTexs[0].Height,0), new Vector2(0,1))
            };

            Indices = new int[] { 0, 1, 2, 2, 3, 0 };

            #endregion

            ContentLoaded = true;
        }

        #endregion

        #region Unload Content

        public override void UnloadContent()
        {
             
            ContentLoaded = false;
        }

        #endregion

        #region Update

        public override void Update(GameTime gameTime)
        {
            if (Updates)
            {
                #region Update Crap
                cam.Pos = new Vector3(Entities[0].Pos, 0);
                if (cam.Pos.X < 1280 / 2) cam.Pos.X = 1280 / 2;
                if (cam.Pos.X > 1280 * Constants.NumSX - (1280 / 2)) cam.Pos.X = 1280 * Constants.NumSX - (1280 / 2);
                if (cam.Pos.Y < 720 / 2) cam.Pos.Y = 720 / 2; //remember to change based on world width
                if (cam.Pos.Y > 720 * Constants.NumSY - (720 / 2)) cam.Pos.Y = 720 * Constants.NumSY - (720 / 2);
                cam.Update();
                foreach (Entity E in Entities)
                {
                    E.Update(gameTime);
                    E.DoColisions(Mask, cam);
                }
                #endregion
                if (Input.Keyboard.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Space)) starting = false;
                if (Input.Keyboard.KeyPressed(Microsoft.Xna.Framework.Input.Keys.G)) ending = true;
            }
        }

        #endregion 

        #region Draw

        public override void Draw(GameTime gameTime)
        {
            if (Draws)
            {
                Game1.Manager.GraphicsDevice.Clear(Color.CornflowerBlue);

                #region DrawBackground

                int x = (int)Math.Floor(Entities[0].Pos.X / 1280);
                int y = (int)Math.Floor(Entities[0].Pos.Y / 720);

                int Right, Down;
                //lawl show kevin this
                if (Entities[0].Pos.X > x * 1280 + 1280 / 2) Right = 1; else if (x != 0) Right = -1; else Right = 1;
                if (Entities[0].Pos.X > Constants.NumSX * 1280 - 1280 / 2) Right = -1;
                if (Entities[0].Pos.Y > y * 720 + 720 / 2) Down = 1; else if (y != 0) Down = -1; else Down = 1;
                if (Entities[0].Pos.Y > Constants.NumSY * 720 - 720 / 2) Down = -1;

                #region Quad1

                VPT.Parameters["Texture"].SetValue(Texs[x, y]);
                VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(1280 * x, 720 * y, 0) * cam.View);

                VPT.CurrentTechnique.Passes[0].Apply();

                Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, VerticesPT, 0, VerticesPT.Length, Indices, 0, 2);

                #endregion

                #region Quad2

                VPT.Parameters["Texture"].SetValue(Texs[x + Right, y]);
                VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(1280 * (x + Right), 720 * y, 0)) * cam.View);

                VPT.CurrentTechnique.Passes[0].Apply();

                Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, VerticesPT, 0, VerticesPT.Length, Indices, 0, 2);

                #endregion

                #region Quad3

                VPT.Parameters["Texture"].SetValue(Texs[x + Right, y + Down]);
                VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(1280 * (x + Right), 720 * (y + Down), 0)) * cam.View);

                VPT.CurrentTechnique.Passes[0].Apply();

                Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, VerticesPT, 0, VerticesPT.Length, Indices, 0, 2);

                #endregion

                #region Quad4

                VPT.Parameters["Texture"].SetValue(Texs[x, y + Down]);
                VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(x * 1280, 720 * (y + Down), 0)) * cam.View);

                VPT.CurrentTechnique.Passes[0].Apply();

                Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, VerticesPT, 0, VerticesPT.Length, Indices, 0, 2);

                #endregion

                #endregion


                foreach (Entity E in Entities) E.Draw(gameTime, cam, Entities[0].Pos);

                #region Dialog

                if (Entities[0].Pos.X < 500 && Entities[0].Pos.Y < 720)
                {

                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(SomeTexs[0]);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
                }

                if (Entities[0].Pos.X < 1000 && Entities[0].Pos.Y < 720 && Entities[0].Pos.X > 500)
                {

                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(SomeTexs[1]);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
                }

                if (Entities[0].Pos.X < 1500 && Entities[0].Pos.Y < 720 && Entities[0].Pos.X > 1000)
                {

                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(SomeTexs[2]);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
                }

                if (Entities[0].Pos.X < 500 && Entities[0].Pos.Y < 4 * 720 && Entities[0].Pos.X > 0 && Entities[0].Pos.Y > 3 * 720)
                {

                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(SomeTexs[3]);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
                }
                #endregion

                if (starting)
                {
                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(start);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
           
                }

                if (ending)
                {
                    VPT.Parameters["W"].SetValue(Matrix.CreateTranslation(new Vector3(0, 0, 0)));
                    VPT.Parameters["Texture"].SetValue(end);

                    VPT.CurrentTechnique.Passes[0].Apply();

                    Graphics.Device.DrawUserIndexedPrimitives<V.PT>(PrimitiveType.TriangleList, nVerticesPT, 0, nVerticesPT.Length, Indices, 0, 2);
           
       
                }

            }
        }

        #endregion
    }
}
