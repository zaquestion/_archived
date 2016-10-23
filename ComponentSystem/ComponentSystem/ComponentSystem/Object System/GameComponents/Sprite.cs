using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Engine 
{
    public struct Sprite :  Component
    {
        public Texture2D Texture { get; set; }

        string Component.ID { get { return "Sprite"; } set { } }
    }
}
