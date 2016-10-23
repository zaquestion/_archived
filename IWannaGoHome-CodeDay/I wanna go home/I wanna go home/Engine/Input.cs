using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Engine
{
    public static class Input
    {
        #region Members

        public static GamePad[] Pads { get; set; }

        #endregion

        #region Construct
        //----------------------------------------------------------------------------------------------------//

        static Input()
        {
            Mouse.Initialize();
            Keyboard.Initialize();

            Pads = new GamePad[4];
            Pads[0] = new GamePad(PlayerIndex.One);
            Pads[1] = new GamePad(PlayerIndex.Two);
            Pads[2] = new GamePad(PlayerIndex.Three);
            Pads[3] = new GamePad(PlayerIndex.Four);
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Update

        public static void Update()
        {
            Mouse.Update();
            Keyboard.Update();
            if(Microsoft.Xna.Framework.Input.GamePad.GetState(PlayerIndex.One).IsConnected) Pads[0].Update();
            if (Microsoft.Xna.Framework.Input.GamePad.GetState(PlayerIndex.Two).IsConnected) Pads[1].Update();
            if (Microsoft.Xna.Framework.Input.GamePad.GetState(PlayerIndex.Three).IsConnected) Pads[2].Update();
            if (Microsoft.Xna.Framework.Input.GamePad.GetState(PlayerIndex.Four).IsConnected) Pads[3].Update();
        }

        #endregion

        #region Mouse

        public static class Mouse
        {
            #region Members
            //----------------------------------------------------------------------------------------------------//

            public static MouseState2 Current { get; set; }
            public static MouseState2 Previous { get; set; }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Initialize
            //----------------------------------------------------------------------------------------------------//

            public static void Initialize()
            {
                Current = new MouseState2(Microsoft.Xna.Framework.Input.Mouse.GetState());
                Previous = Current;
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Update
            //----------------------------------------------------------------------------------------------------//

            public static void Update()
            {
                Previous = Current;
                Current = new MouseState2(Microsoft.Xna.Framework.Input.Mouse.GetState());
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion
        }

        #endregion

        #region Keyboard

        public static class Keyboard
        {
            #region Members
            //----------------------------------------------------------------------------------------------------//

            public static KeyboardState2 Current { get; set; }
            public static KeyboardState2 Previous { get; set; }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Initialize
            //----------------------------------------------------------------------------------------------------//

            public static void Initialize()
            {
                Current = new KeyboardState2(Microsoft.Xna.Framework.Input.Keyboard.GetState());
                Previous = Current;
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Update
            //----------------------------------------------------------------------------------------------------//

            public static void Update()
            {
                Previous = Current;
                Current = new KeyboardState2(Microsoft.Xna.Framework.Input.Keyboard.GetState());
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region KeyPressed
            //----------------------------------------------------------------------------------------------------//

            public static bool KeyPressed(Keys Key)
            {
                return Current.KeyDown(Key) && Previous.KeyUp(Key);
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion
        }

        #endregion

        #region GamePad

        public class GamePad
        {
            #region Members

            public GamePadState2 Current { get; set; }
            public GamePadState2 Previous { get; set; }
            private PlayerIndex index;


            #endregion

            #region Initialize

            public GamePad(PlayerIndex index)
            {
                this.index = index;
                Current = new GamePadState2(Microsoft.Xna.Framework.Input.GamePad.GetState(index));
                Previous = Current;
            }

            #endregion

            #region Update

            public void Update()
            {
                Previous = Current;
                Current = new GamePadState2(Microsoft.Xna.Framework.Input.GamePad.GetState(index));

            }

            #endregion
        }

        #endregion
    }


    #region MouseState2
    //----------------------------------------------------------------------------------------------------//

    public class MouseState2
    {
        #region Members
        //----------------------------------------------------------------------------------------------------//

        private MouseState state;

        public float X { get { return state.X; } }
        public float Y { get { return state.Y; } }

        public Vector2 Position { get { return new Vector2(state.X, state.Y); } }

        public bool Left { get { return state.LeftButton == ButtonState.Pressed; } }
        public bool Right { get { return state.RightButton == ButtonState.Pressed; } }
        public bool Middle { get { return state.MiddleButton == ButtonState.Pressed; } }

        public int Wheel { get { return state.ScrollWheelValue; } }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Constructor
        //----------------------------------------------------------------------------------------------------//

        public MouseState2(MouseState state)
        {
            this.state = state;
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion
    }

    //----------------------------------------------------------------------------------------------------//
    #endregion

    #region KeyboardState2
    //----------------------------------------------------------------------------------------------------//

    public class KeyboardState2
    {
        #region Members
        //----------------------------------------------------------------------------------------------------//

        private KeyboardState state;

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Constructor
        //----------------------------------------------------------------------------------------------------//

        public KeyboardState2(KeyboardState state)
        {
            this.state = state;
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region KeyUp
        //----------------------------------------------------------------------------------------------------//

        public bool KeyUp(Keys key)
        {
            return state.IsKeyUp(key);
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region KeyDown
        //----------------------------------------------------------------------------------------------------//

        public bool KeyDown(Keys key)
        {
            return state.IsKeyDown(key);
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion
    }

    //----------------------------------------------------------------------------------------------------//
    #endregion

    #region GamePadState2

    public class GamePadState2
    {
        #region Members

        private GamePadState State;

        public bool Connected { get { return State.IsConnected; } }

        public Vector2 LeftThumb { get { return State.ThumbSticks.Left; } }
        public Vector2 RightThumb { get { return State.ThumbSticks.Right; } }
       
        public float LeftTrigger { get { return State.Triggers.Left; } }
        public float RightTrigger { get { return State.Triggers.Right; } }

        public bool LeftBumper { get { return State.Buttons.LeftShoulder == ButtonState.Pressed; } }
        public bool LeftClick { get { return State.Buttons.LeftStick == ButtonState.Pressed; } }

        public bool RightBumper { get { return State.Buttons.RightShoulder == ButtonState.Pressed; } }
        public bool RightClick { get { return State.Buttons.RightStick == ButtonState.Pressed; } }

        public bool A { get { return State.Buttons.A == ButtonState.Pressed; } }
        public bool X { get { return State.Buttons.X == ButtonState.Pressed; } }
        public bool Y { get { return State.Buttons.Y == ButtonState.Pressed; } }
        public bool B { get { return State.Buttons.B == ButtonState.Pressed; } }

        public bool Start { get { return State.Buttons.Start == ButtonState.Pressed; } }
        public bool Back { get { return State.Buttons.Back == ButtonState.Pressed; } }

        #endregion

        #region Constructer
        
        public GamePadState2(GamePadState State)
        {
            this.State = State;
        }

        #endregion
    }

    #endregion
} 