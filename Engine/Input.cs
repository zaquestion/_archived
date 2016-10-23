using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Engine
{
    public static class Input
    {
        #region Members
        //----------------------------------------------------------------------------------------------------//

        public static List<GamePad> Pads { get; set; }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Construct
        //----------------------------------------------------------------------------------------------------//

        static Input()
        {
            Mouse.Initialize();
            Keyboard.Initialize();

            Pads = new List<GamePad>();
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Update
        //----------------------------------------------------------------------------------------------------//

        public static void Update()
        {
            Mouse.Update();
            Keyboard.Update();
            foreach (GamePad pad in Pads) pad.Update();
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Mouse
        //----------------------------------------------------------------------------------------------------//

        public static class Mouse
        {
            #region Members
            //----------------------------------------------------------------------------------------------------//

            public static MouseState2 Current { get; set; }
            public static MouseState2 Previous { get; set; }

            public static int Limit { get; set; }
            public static List<MouseState2> States { get; set; }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Initialize
            //----------------------------------------------------------------------------------------------------//

            public static void Initialize()
            {
                Current = new MouseState2(Microsoft.Xna.Framework.Input.Mouse.GetState());
                Previous = Current;

                Limit = 10;
                States = new List<MouseState2>(Limit);
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Update
            //----------------------------------------------------------------------------------------------------//

            public static void Update()
            {
                Previous = Current;
                Current = new MouseState2(Microsoft.Xna.Framework.Input.Mouse.GetState());

                States.Insert(0, Current);
                while (States.Count > Limit) States.RemoveAt(States.Count - 1);
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion


            
        }

        //----------------------------------------------------------------------------------------------------//
        #endregion

        #region Keyboard
        //----------------------------------------------------------------------------------------------------//

        public static class Keyboard
        {
            #region Members
            //----------------------------------------------------------------------------------------------------//

            public static KeyboardState2 Current { get; set; }
            public static KeyboardState2 Previous { get; set; }

            public static int Limit { get; set; }
            public static List<KeyboardState2> States { get; set; }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Initialize
            //----------------------------------------------------------------------------------------------------//

            public static void Initialize()
            {
                Current = new KeyboardState2(Microsoft.Xna.Framework.Input.Keyboard.GetState());
                Previous = Current;

                Limit = 10;
                States = new List<KeyboardState2>(Limit);
            }

            //----------------------------------------------------------------------------------------------------//
            #endregion

            #region Update
            //----------------------------------------------------------------------------------------------------//

            public static void Update()
            {
                Previous = Current;
                Current = new KeyboardState2(Microsoft.Xna.Framework.Input.Keyboard.GetState());

                States.Insert(0, Current);
                while (States.Count > Limit) States.RemoveAt(States.Count - 1);
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

        //----------------------------------------------------------------------------------------------------//
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

            #region ButtonPressed
            public bool buttonPressed(Buttons button)
            {
                return Current.ButtonDown(button) && Previous.ButtonUp(button);
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

    #region GamepadState2

    public class GamePadState2
    {
        #region Members

        private GamePadState State;

        public Vector2 ThumbLeft { get { return State.ThumbSticks.Left; } }
        public Vector2 ThumbRight { get { return State.ThumbSticks.Right; } }
        public float TriggerLeft { get { return State.Triggers.Left; } }
        public float TriggerRight { get { return State.Triggers.Right; } }

        #endregion

        #region Constructer
        
        public GamePadState2(GamePadState State)
        {
            this.State = State;
        }

        #endregion

        #region ButtonUp

        public bool ButtonUp(Buttons button)
        {
            return State.IsButtonUp(button);
        }

        #endregion

        #region ButtonDown

        public bool ButtonDown(Buttons button)
        {
            return State.IsButtonDown(button);
        }

        #endregion

        


    }

    #endregion
} 