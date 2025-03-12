#include <am_time.h>
string query_num(int num);
#if !efun_defined(query_multiple_short)
varargs string query_multiple_short( mixed *args, string type,
                                     int no_dollars, int quiet,
                                     int dark );
#endif
string ordinal( int number ) {
   if ( ( number % 100 > 10 ) && ( number % 100 < 14 ) )
      return number +"th";
   if ( number % 10 == 1 )
      return number +"st";
   if ( number % 10 == 2 )
      return number +"nd";
   if ( number % 10 == 3 )
      return number +"rd";
   return number +"th";
}
varargs string amtime( int number, int format ) {
   return AM_TIME_HANDLER->query_am_time(number, format);
}
#include <am_time.h>
varargs string query_time_string (int t, int max_elements, int am_time,
                                  int use_words) {
  string *toret = ({ }), tmp_string;
  int year, day, hour, minute, tmp_int;
  if (am_time) {
    year = AM_SECONDS_PER_HALF_YEAR * 2;
    day = AM_SECONDS_PER_DAY;
    hour = AM_SECONDS_PER_HOUR;
    minute = AM_SECONDS_PER_MINUTE;
  }
  else {
    year = 60 * 60 * 24 * 365;
    day = 60 * 60 * 24;
    hour = 60 * 60;
    minute = 60;
  }
  if (t >= year) {
    toret = ({ toret ..., sprintf ("%d %s", (t / year),
      (t >= year * 2 ? "years" : "year")) });
    t %= year;
    year = -1;
  }
  if (t >= day) {
    toret = ({ toret ..., sprintf ("%d %s", (t / day),
      (t >= day * 2 ? "days" : "day")) });
    t %= day;
    day = -1;
  }
  else if (year == -1) {
    toret = ({ toret ..., "0 days" });
  }
  if (t >= hour) {
    toret = ({ toret ..., sprintf ("%d %s", (t / hour),
      (t >= hour * 2 ? "hours" : "hour")) });
    t %= hour;
  }
  else if (day == -1) {
    toret = ({ toret ..., "0 hours" });
  }
  if (t >= minute) {
    toret = ({ toret ..., sprintf ("%d %s", (t / minute),
      (t >= minute * 2 ? "minutes" : "minute")) });
    t %= minute;
  }
  else if (hour == -1) {
    toret = ({ toret ..., "0 minutes" });
  }
  if (t > 0) {
    toret = ({ toret ..., sprintf ("%d %s", t,
      (t > 1 ? "seconds" : "second")) });
  }
  if (!max_elements) {
    max_elements = 2;
  }
  if (max_elements > 0) {
    toret = toret[0..(max_elements - 1)];
  }
  for (int x = 0; x < sizeof (toret); ++x) {
    sscanf (toret[x], "%d %s", tmp_int, tmp_string);
    if (tmp_int == 0) {
      toret -= ({ toret[x] });
    }
    else if (use_words) {
      toret[x] = query_num (tmp_int) + " " + tmp_string;
    }
  }
  if (!toret || !sizeof (toret)) {
    return "no time at all";
  }
  return query_multiple_short (toret);
}