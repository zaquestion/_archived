using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Engine
{
    public class Game1 : Game
    {
        #region Members

        public static IServiceProvider IServiceProvider { get; set; }
        public static GraphicsDeviceManager Manager { get; set; }

        #endregion

        #region Constructer

        public Game1()
        {
            Manager = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            Manager.PreferredBackBufferWidth = 1280;
            Manager.PreferredBackBufferHeight = 720;
            Manager.SynchronizeWithVerticalRetrace = true;
            IsFixedTimeStep = true;
            IsMouseVisible = true;
        }

        #endregion

        #region Initialize

        protected override void Initialize()
        {
            IServiceProvider = Content.ServiceProvider;
            base.Initialize();
        }

        #endregion

        #region Load Content

        protected override void LoadContent()
        {
            GameState.AddScreen(new LoadingScreen(new Level1()));
        }

        #endregion

        #region Unload Content

        protected override void UnloadContent()
        {
            Content.Unload();
        }

        #endregion

        #region Update

        protected override void Update(GameTime gameTime)
        {
            Input.Update();
            if (Input.Keyboard.Current.KeyDown(Keys.Escape))
                this.Exit();

            GameState.Update(gameTime);

            base.Update(gameTime);
        }

        #endregion

        #region Draw

        protected override void Draw(GameTime gameTime)
        {
            GameState.Draw(gameTime);

            base.Draw(gameTime);
        }

        #endregion
    }

    #region Entry Point

#if WINDOWS || XBOX
    static class EntryPoint
    {
        static void Main()
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

