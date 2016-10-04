using System;

namespace Spells.Domain
{
    public static class TimeHelper
    {
        public static TimeSpan GetCurrentTime()
        {
            var timeNow = DateTime.Now;
            return new TimeSpan(0, timeNow.Hour, timeNow.Minute, timeNow.Second, timeNow.Millisecond);
        }
    }
}