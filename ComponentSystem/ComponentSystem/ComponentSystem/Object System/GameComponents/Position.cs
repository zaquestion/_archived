using Microsoft.Xna.Framework;

namespace Engine 
{
    public struct Position : Component
    {
        public Vector2 Pos { get; set; }

        string Component.ID { get { return "Position"; } set {} }
    }
}
