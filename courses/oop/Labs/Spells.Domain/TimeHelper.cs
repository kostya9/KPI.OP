using System;

namespace Spells.Domain
{
    public class TimeHelper
    {
        private TimeHelper()
        {

        }
        public static TimeSpan GetCurrentTime()
        {
            var timeNow = DateTime.Now;
            return new TimeSpan(0, timeNow.Hour, timeNow.Minute, timeNow.Second, timeNow.Millisecond);
        }
    }
}