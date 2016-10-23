using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace Engine
{
    #region Sound

    public static class Sound
    {
        private static List<ProximitySFX> pSFXs = new List<ProximitySFX>();

        #region Update

        public static void Update(Vector2 pos)
        {
            #region Update Proximity SFX

            foreach (ProximitySFX sfx in pSFXs)
            {
                sfx.Instance.Volume = sfx.MaxVol * (50 / (Vector2.Distance(sfx.Pos, pos) + 50));
                if (sfx.Instance.Volume > 0.009 && sfx.Instance.State != SoundState.Playing)
                {
                    sfx.Instance.Play();
                }
                if (sfx.Instance.Volume < 0.009) sfx.Instance.Stop();
            }

            #endregion
        }

        #endregion

        #region Methods

        #region Clean Up

        public static void cleanUp()
        {
            pSFXs.Clear();
        }

        #endregion

        #region Add Proximity SFX

        public static void AddProximitySFX(ProximitySFX sfx)
        {
            pSFXs.Add(sfx);
        }

        #endregion

        #endregion
    }

    #endregion

    #region Proximity SFX

    public class ProximitySFX
    {
        #region Members

        public SoundEffectInstance Instance { get; set; }
        public float MaxVol { get; set; }
        public Vector2 Pos { get; set; }

        #endregion

        #region Constructer

        public ProximitySFX(SoundEffect SFX, Vector2 Pos, float MaxVol)
        {
            this.Instance = SFX.CreateInstance();
            this.Instance.IsLooped = true;
            this.MaxVol = MaxVol;
            this.Pos = Pos;
        }

        #endregion
    }

    #endregion
}
