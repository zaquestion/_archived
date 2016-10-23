using Microsoft.Xna.Framework.Graphics;

namespace Engine 
{
    public struct Primitive<T> : Component where T : IVertexType
    {
        public PrimitiveType Type { get; set; }
        public T[] Vertices { get; set; }
        public int[] Indices { get; set; }
        public int Count { get; set; }

        string Component.ID { get { return "Primitive" + typeof(T).ToString(); } set { } }
    }
}
