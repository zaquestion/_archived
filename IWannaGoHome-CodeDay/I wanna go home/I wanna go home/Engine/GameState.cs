using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using System.Threading;
using Microsoft.Xna.Framework.Graphics;

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

        static GameState()
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
            if (!Screen.ContentLoaded) Screen.Initialize();
            if (!Screen.ContentLoaded) Screen.LoadContent();
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
            
            ContentLoaded = false;
            Updates = true;
            Draws = true;
        }

        public abstract void Initialize();
        public abstract void LoadContent();
        public abstract void UnloadContent();
        public abstract void Update(GameTime gameTime);
        public abstract void Draw(GameTime gameTime);
    }

    #endregion

    #region GameScreen

    public abstract class GameScreen : Screen
    {
        public List<Entity> Entities { get; set; }

        public bool[,] Mask { get; set; }
        public Texture2D[,] MaskTexs { get; set; }

        public override void Initialize()
        {
            Entities = new List<Entity>();
            
        }

        public override void LoadContent()
        {
            #region Fill Mask

            Color[] colarray = new Color[1280 * 720];

            for (int xi = 0; xi < Constants.NumSX; xi++)
            {
                for (int yi = 0; yi < Constants.NumSY; yi++)
                {
                    if (MaskTexs[xi, yi] != null)
                    {
                        MaskTexs[xi, yi].GetData<Color>(colarray);

                        #region Fill Mask With Chunk

                        for (int x = 0; x < 1280; x++)
                        {
                            for (int y = 0; y < 720; y++)
                            {
                                if (colarray[x + y * 1280].R == 0) 
                                    Mask[x + xi * 1280, y + yi * 720] = true; 
                                else Mask[x + xi * 1280, y + yi * 720] = false;
                            }
                        }

                        #endregion

                        //MaskTexs[xi, yi].Dispose();
                    }
                }
            }

            #endregion
        }

        public override void UnloadContent()
        {

        }

        public override void Update(GameTime gameTime)
        {
            
        }

        public override void Draw(GameTime gameTime)
        {

        }
    }

    #endregion

}
