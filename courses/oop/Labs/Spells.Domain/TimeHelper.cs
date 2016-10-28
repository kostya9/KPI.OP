using System;
using System.Data;

namespace Spells.Domain
{
    public class TimeHelper
    {
        private static int updates  = 0;
        private TimeHelper()
        {

        }

        public static void Update(SpellsContainer c,
            EventArgs args)
        {
            updates += 1;
        }

        public static TimeSpan GetCurrentTime()
        {
            var timeNow = DateTime.Now;
            return new TimeSpan(0, timeNow.Hour, timeNow.Minute, timeNow.Second, timeNow.Millisecond);
        }
    }
}