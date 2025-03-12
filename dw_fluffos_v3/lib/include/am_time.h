#ifndef __AM_TIME_H
#define __AM_TIME_H
#define AM_TIME_HANDLER "/obj/handlers/am_time_handler"
#define AM_TIME_MONTH 0
#define AM_TIME_DAY_OF_MONTH 1
#define AM_TIME_DAY_OF_WEEK 2
#define AM_TIME_HOUR 3
#define AM_TIME_MINUTE 4
#define AM_TIME_YEAR 5
#define AM_TIME_PRIMUS 6
#define AM_TIME_OFFLE 1
#define AM_TIME_FEBURARY 2
#define AM_TIME_MARCH 3
#define AM_TIME_APRIL 4
#define AM_TIME_MAY 5
#define AM_TIME_JUNE 6
#define AM_TIME_GRUNE 7
#define AM_TIME_AUGUST 8
#define AM_TIME_SPUNE 9
#define AM_TIME_SEKTOBER 10
#define AM_TIME_EMBER 11
#define AM_TIME_DECEMBER 12
#define AM_TIME_ICK 13
#define AM_TIME_MONDAY 1
#define AM_TIME_TUESDAY 2
#define AM_TIME_WEDNESSDAY 3
#define AM_TIME_THURSDAY 4
#define AM_TIME_FRIDAY 5
#define AM_TIME_SATURDAY 6
#define AM_TIME_SUNDAY 7
#define AM_TIME_OCTEDAY 8
#define AM_DAYS_PER_HALF_YEAR 400
#define AM_SECONDS_PER_MINUTE 18
#define AM_MINUTES_PER_HOUR 60
#define AM_HOURS_PER_DAY 24
#define AM_DAYS_PER_WEEK 8
#define AM_MINUTES_PER_DAY (AM_MINUTES_PER_HOUR * AM_HOURS_PER_DAY)
#define AM_SECONDS_PER_DAY (AM_MINUTES_PER_DAY * AM_SECONDS_PER_MINUTE)
#define AM_SECONDS_PER_WEEK (AM_DAYS_PER_WEEK * AM_MINUTES_PER_DAY * AM_SECONDS_PER_MINUTE)
#define AM_SECONDS_PER_HALF_YEAR (AM_SECONDS_PER_DAY * AM_DAYS_PER_HALF_YEAR)
#define AM_SECONDS_PER_HOUR (AM_SECONDS_PER_MINUTE*AM_MINUTES_PER_HOUR)
#define AM_START_YEAR_DATE 1966
#define AM_TIME_FORMAT_NO_TIME 1
class am_time {
   int year;
   int primus;
   int minute;
   int hour;
   int month;
   int day_of_week;
   int day_of_month;
   int day_of_year;
}
#endif