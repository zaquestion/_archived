using Microsoft.Xna.Framework;
using System.Threading;

namespace Engine
{
    public class LoadingScreen : Screen
    {
        #region Members

        public Screen ToLoad;
        public Thread LoadingThread;

        #endregion

        #region Constructor

        public LoadingScreen(Screen ToLoad)
        {
            this.ToLoad = ToLoad;
            ToLoad.Initialize();
            LoadingThread = new Thread(new ThreadStart(ToLoad.LoadContent));
        }

        #endregion

        #region Initialize

        public override void Initialize()
        {
            
        }

        #endregion

        #region LoadContent

        public override void LoadContent()
        {
            LoadingThread.Start();
            ContentLoaded = true;
        }

        #endregion

        #region Unload

        public override void UnloadContent()
        {
            Content.Unload();
        }

        #endregion

        #region Update

        public override void Update(GameTime gameTime)
        {
            #region Exit

            if (ToLoad.ContentLoaded)
            {
                GameState.AddScreen(ToLoad);
                GameState.RemoveScreen(this);
            }

            #endregion
        }

        #endregion

        #region Draw

        public override void Draw(GameTime gameTime)
        {
            Graphics.Device.Clear(Color.Black);
        }

        #endregion
    }
}
