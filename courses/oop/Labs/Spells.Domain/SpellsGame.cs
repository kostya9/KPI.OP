using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Spells.Domain
{
    public class SpellsGame : IDisposable
    {
        public SpellsContainer SpellsContainer { get; }
        private readonly MissleMover _missleMover;
        public WallStore WallStore { get; }
        private Collider _collider;
        private bool disposed = false;

        public event SpellCooldownZeroHandler SpellCooldownZero
        {
            add { SpellsContainer.SpellCooldownZero += value; }
            remove { SpellsContainer.SpellCooldownZero -= value; }
        }

        public event MissleMovedHandler MissleMoved
        {
            add { _missleMover.MissleMoved += value; }
            remove { _missleMover.MissleMoved -= value; }
        }

        public SpellsGame(ValidatePosition validater)
        {
            SpellsContainer = new SpellsContainer();
            _missleMover = new MissleMover(validater);
            WallStore = new WallStore();
            _collider = new Collider(_missleMover, WallStore);

            SpellsContainer.SpellCasted += (s,
                e) => _missleMover.AddMissle(e.Missle);
        }

        public SpellsGame(ValidatePosition validater,
            string settingsFile) : this(validater)
        {
            SettingsModel settings;
            try
            {
                using (var reader = new StreamReader(File.OpenRead(settingsFile)))
                {
                    settings = JsonConvert.DeserializeObject<SettingsModel>(reader.ReadToEnd());
                }
            }
            catch
            {
                return;
            }

            foreach (var wall in settings.WallModels)
            {
                var block = new WallBlock();
                for (int i = 0; i < wall.Quantity; i++)
                {
                    block.Add(new Wall(wall.MaxHealth));
                }
                this.WallStore.AddWallBlock(wall.Position, block);
            }

            foreach (var spellModel in settings.SpellModels)
            {
                ICastable spell;
                switch (spellModel.SpellClass)
                {
                        case Spells.FireBall:
                    {
                        spell = new FireBall();
                    }
                        break;
                        case Spells.HealingBall:
                    {
                        spell = new HealingBall();
                    }
                        break;
                        case Spells.SpinningFireBall:
                    {
                        spell = new SpinningFireBall();
                    }
                        break;
                    default:
                    {
                        spell = new FireBall();
                    }
                        break;
                }
                SpellsContainer.AddSpell(spell, spellModel.Position);
            }

        }



        public void Update()
        {
            SpellsContainer.CheckSpellCooldowns();
            _missleMover.Move(WallStore);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;

            if (disposing)
            {
                this.WallStore.Dispose();
            }

            this.disposed = true;
        }

        ~SpellsGame()
        {
            this.Dispose(false);
        }

    }
}
