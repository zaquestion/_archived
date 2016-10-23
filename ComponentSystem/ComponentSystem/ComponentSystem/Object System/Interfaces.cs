using System;
using System.Collections.Generic;

namespace Engine
{
    public class Manager //Player, Drawing, Enemy
    {
        public Dictionary<Guid, Object> Objects { get; set; }
        public Dictionary<string, System> Systems { get; set; }

        public Manager()
        {
            Objects = new Dictionary<Guid, Object>();
            Systems = new Dictionary<string, System>();
        }

        public void AddObject(Guid Guid, Object Object)
        {
            Objects.Add(Guid, Object);
        }

        public Object GetObject(Guid Guid)
        {
            return Objects[Guid];
        }
    }

    public interface System //PuppetSkeleton, Input, Shading, Rendering
    {
        void Update(Dictionary<Guid, Object> Objects);
    }

    public interface Object //Limb, Primitive
    {
        List<Component> Components { get; set; }
    }

    public interface Component //Tex, Pos, Origin
    {
        string ID { get; set; }
    }
}

