using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;

namespace Engine
{
    #region GameState

    public static class GameState
    {
        #region Members

        private static List<Screen> Screens { get; set; }
        private static List<Screen> ToUpdate { get; set; }

        #endregion

        #region Initialize

        public static void Initialize()
        {
            Screens = new List<Screen>();
            ToUpdate = new List<Screen>();
        }

        #endregion

        #region Update

        public static void Update(GameTime gameTime)
        {
            ToUpdate.Clear();
            foreach (Screen screen in Screens) ToUpdate.Add(screen);
            foreach (Screen screen in ToUpdate) screen.Update(gameTime);
        }

        #endregion

        #region Draw

        public static void Draw(GameTime gameTime)
        {
            foreach (Screen screen in ToUpdate) screen.Draw(gameTime);
        }

        #endregion

        #region Methods

        #region AddScreen

        public static void AddScreen(Screen Screen)
        {
            Screens.Add(Screen);
            if (!Screen.ContentLoaded)
                Screen.LoadContent();
        }

        #endregion

        #region RemoveScreen

        public static void RemoveScreen(Screen Screen)
        {
            if (Screen.ContentLoaded)
                Screen.UnloadContent();
            Screens.Remove(Screen);
        }

        #endregion

        #endregion
    }

    #endregion

    #region Screen

    public abstract class Screen
    {
        #region Members

        public ContentManager Content { get; set; }
        public bool ContentLoaded { get; set; }
        public bool Updates { get; set; }
        public bool Draws { get; set; }

        #endregion

        public Screen()
        {
            Content = new ContentManager(Game1.IServiceProvider, "Content");
            Graphics.Content = Content;
            ContentLoaded = false;
            Updates = true;
            Draws = true;
            Initialize();
        }

        public abstract void Initialize();
        public abstract void LoadContent();
        public abstract void UnloadContent();
        public abstract void Update(GameTime gameTime);
        public abstract void Draw(GameTime gameTime);
    }

    #endregion
}
