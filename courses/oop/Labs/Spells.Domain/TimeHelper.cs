using System;
using System.Data;
using System.Diagnostics;

namespace Spells.Domain
{
    public class TimeHelper
    {
        private static Stopwatch _watch;
        private static TimeSpan CurrentTime => _watch?.Elapsed ?? new TimeSpan(0, 0, 0, 0, 0);

        public static void Start()
        {
            if (_watch == null)
                _watch = new Stopwatch();

            _watch.Start();
        }
        public static void Stop()
        {
            _watch.Stop();
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