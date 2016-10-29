using System;
using System.Data;
using System.Diagnostics;

namespace Spells.Domain
{
    public class TimeHelper
    {
        private static Stopwatch watch;
        private static TimeSpan CurrentTime
        {
            get
            {
                return watch == null ? new TimeSpan(0, 0, 0, 0, 0) : watch.Elapsed;
            }
        }

        static public void Start()
        {
            if (watch == null)
                watch = new Stopwatch();

            watch.Start();
        }
        static public void Stop()
        {
            watch.Stop();
        }
        private TimeHelper()
        {

        }

        public static TimeSpan GetCurrentTime()
        {
            return CurrentTime;
        }
    }
}