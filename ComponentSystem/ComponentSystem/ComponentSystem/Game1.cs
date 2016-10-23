using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Engine
{
    public class Game1 : Microsoft.Xna.Framework.Game
    {

        public static IServiceProvider IServiceProvider { get; set; }
        public static GraphicsDeviceManager Manager { get; set; }
        public static ContentManager ContentM { get; set; }

        public Manager M = new Manager();


        public Game1()
        {
            Manager = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            ContentM = Content;
        }

        protected override void Initialize()
        {
            Guid MahObject = Guid.NewGuid();
            M.AddObject(MahObject, new Limb(Content.Load<Texture2D>("head")));
            Position p = new Position();
            p.Pos = new Vector2(400, 300);
            M.GetObject(MahObject).Components.Add(p);

            M.Systems.Add("Render", new Render());

            base.Initialize();
        }

        protected override void LoadContent()
        {
        }

        protected override void UnloadContent()
        {

        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            foreach (var system in M.Systems) system.Value.Update(M.Objects);

            base.Draw(gameTime);
        }
    }

    #region Entry Point

    #if WINDOWS || XBOX

    static class Program
    {
        static void Main(string[] args)
        {
            using (Game1 game = new Game1())
            {
                game.Run();
            }
        }
    }

    #endif

    #endregion

}
