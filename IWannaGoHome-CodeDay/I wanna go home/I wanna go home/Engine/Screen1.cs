using Microsoft.Xna.Framework;

namespace Engine
{
    public class Screen1 : Screen
    {
        #region Members

        #endregion

        #region Initialize

        public override void Initialize()
        {

        }

        #endregion

        #region Load Content

        public override void LoadContent()
        {
            ContentLoaded = true;
        }

        #endregion

        #region Unload Content

        public override void UnloadContent()
        {
            Content.Unload();
            ContentLoaded = false;
        }

        #endregion

        #region Update

        public override void Update(GameTime gameTime)
        {
            if (Updates)
            {

            }
        }

        #endregion

        #region Draw

        public override void Draw(GameTime gameTime)
        {
            if (Draws)
            {
                Game1.Manager.GraphicsDevice.Clear(Color.CornflowerBlue);
            }
        }

        #endregion
    }
}
