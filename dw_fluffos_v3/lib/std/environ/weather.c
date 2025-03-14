#include <config.h>
inherit "std/object";
#include "climate.h"
#define FILE_NAME "/save/environ/weather"
#define HOME "/obj/handlers/weather_room"
#define MAX_DIST 100
#define YEAR 60
#define DAY 60
#define SPEED 40
mixed *coldarr,
      *cloudarr,
      *rainarr;
int timeofyear,
    mooncycle,
    moonoff,
    timeofday,
    intensity;
int distance(mixed *co_ord1,mixed *co_ord);
int cloud_index(object env);
int rain_index(object env);
int temperature_index(object env);
string cloud_string(object env);
string rain_string(object env);
string temperature_string(object env);
void setup() {
  set_name("weather");
  set_short("weather controller extrodinare");
  set_long("The weather controller, at least this one is always right!\n");
  cloudarr = ({ ({ 0,0 }), ({ 50,50 }), ({ -50,-50 }) });
  rainarr = ({ ({ 0,0 }), ({ 50,50 }), ({ -50,-50 }) });
  coldarr = ({ ({ 0,0 }), ({ 50,50 }), ({ -50,-50 }) });
  intensity = 100;
  restore_object(FILE_NAME);
  call_out("update_low",SPEED);
  move("bing");
}
move(arg) {
  ::move(HOME);
}
mixed *query_cold() { return coldarr; }
mixed *query_rain() { return rainarr; }
mixed *query_cloud() { return cloudarr; }
int query_moon() { return mooncycle; }
string query_moon_string(object env) {
  int bing;
  bing = timeofday - (DAY/4) -
         (distance((mixed *)env->query_co_ord(), ({ 0, 0, 0, }))/100);
  if (bing<0) bing += DAY;
  if ((moonoff+(DAY/2)<bing) && (bing<DAY-moonoff))
    return 0;
  return ({ "full moon",
            "waning three quarter moon",
            "waning half moon",
            "waning quarter moon",
            "waning cresent moon",
            "new moon",
            "waxing cresent moon",
            "waxing quarter moon",
            "waxing half moon",
            "waxing three quarter moon" })[mooncycle];
}
int distance(mixed *co_ord1, mixed *co_ord2) {
  int off;
  if (!pointerp(co_ord1) || !pointerp(co_ord2))
    return 0;
  if (co_ord1[0]>co_ord2[0])
    off = co_ord1[0] - co_ord2[0];
  else
    off = co_ord2[0] - co_ord1[0];
  if (co_ord1[1]>co_ord2[1])
    off += co_ord1[1] - co_ord2[1];
  else
    off += co_ord2[1] - co_ord1[1];
  return off;
}
int query_season() { return timeofyear/15; }
int query_time_of_year() { return timeofyear; }
int query_time_of_day() { return timeofday; }
int query_day(object env) {
  int bing, bit;
  if (!env) {
    load_object(CONFIG_START_LOCATION);
    env = find_object(CONFIG_START_LOCATION);
  }
  bing = timeofday - (DAY/4) -
         (distance((mixed *)env->query_co_ord(), ({ 0, 0, 0, }))/100);
  if (bing<0) bing += DAY;
  bit = (DAY/2)-(timeofyear-(YEAR/2))/(YEAR/10);
  if (bing>bit)
    return 0;
  if (bit < 10)
    return bit;
  return -(bing - bit);
}
int query_darkness(object env) {
  int bing, per, i;
  per = -cloud_index(env);
  if (per <-100)
    per = -100;
  if (per > 100)
    per = 100;
  if ((i=query_day(env))) {
    i *= 20;
    if (i>100)
      i = 100;
    return 50+(per+100)*150*i/20000;
  }
  bing = timeofday - (DAY/4) -
         (distance((mixed *)env->query_co_ord(), ({ 0, 0, 0, }))/100);
  if (bing<0) bing += DAY;
  if ((moonoff+(DAY/2)<bing) && (bing<DAY-moonoff))
    return 15+(per+100)*30/200;
  if (timeofday<0) timeofday += DAY;
  i = mooncycle -5;
  if (i<0)
    i = -i;
  return 30+(per+100)*14*i/200;
}
string weather_string(object env) {
  return temperature_string(env)+" with "+cloud_string(env)+
         rain_string(env);
}
int query_raining(object env) {
  int cloud,rain;
  if (temperature_index(env)/(100/7)<2) {
    cloud = cloud_index(env);
    if (cloud<=0)
      return 0;
    rain = rain_index(env);
    if (cloud-rain<=0)
      return 0;
    return cloud-rain;
  }
  return 0;
}
int query_hailing(object env) {
  int cloud, rain;
  if (temperature_index(env)/(100/7)==2) {
    cloud = cloud_index(env);
    if (cloud <=0)
      return 0;
    rain = rain_index(env);
    if (cloud-rain <=0)
      return 0;
    return cloud-rain;
  }
  return 0;
}
int query_snowing(object env) {
  int cloud,rain;
  if ((temperature_index(env)/(100/7))>=3) {
    cloud = cloud_index(env);
    if (cloud<=0)
      return 0;
    rain = cloud_index(env);
    if (cloud-rain<=0)
      return 0;
    return cloud-rain;
  }
  return 0;
}
string rain_string(object env) {
  int cloud, rain, temp;
  string tempstr1,tempstr2;
  cloud = cloud_index(env);
  rain = rain_index(env);
  if (cloud<=0) return "";
  if (cloud-rain<=0) return "";
  temp = temperature_index(env)/(100/7);
  if (temp>3) temp = 3;
  if (temp<-3) temp = -3;
  tempstr1 = ({ "very hot ",
                "hot ",
                "warm ",
                "nice ",
                "cold ",
                "",
                "" })[temp+3];
  tempstr2 = ({ " rain",
                " rain",
                " rain",
                " rain",
                " rain",
                " hail",
                " snow" })[temp+3];
  cloud = (cloud-rain) / 20;
  if (cloud>5) cloud = 5;
  return "\n"+capitalize(tempstr1 + ({ "very light",
                      "light",
                      "medium",
                      "heavy",
                      "very heavy" }) [cloud]+tempstr2);
}
string temperature_string(object env) {
  int inten;
  inten = temperature_index(env);
  inten /= 10;
  if (inten>10)
    inten = 10;
  if (inten<-10)
    inten = -10;
  return ({ "Its one of those baking eggs on the pavement days",
            "So hot that the sun feels like its right next door",
            "Damn hot",
            "Very hot",
            "Hot",
            "Hot",
            "Reasonably hot",
            "Very warm",
            "Warm",
            "Pleasantly warm",
            "Average temerature",
            "A little chilly",
            "A slight nip in the air",
            "Chilly",
            "Very chilly",
            "Cold",
            "Cold",
            "Very cold",
            "Damn cold",
            "Incredibly cold",
            "Freezing cold" })[inten+10];
}
string cloud_string(object env) {
  int off;
  off = cloud_index(env) / 20;
  if (off>5) off = 5;
  if (off<-5) off = -5;
  return ({ "a beatifully clear sky",
            "a few high level sirius clouds",
            "scattered puffy clouds",
            "very thin complete cloud cover",
            "light cloud cover",
            "medium cloud cover",
            "dense cloud cover",
            "packed cloud cover",
            "packed cloud cover",
            "heavy black clouds",
            "thick heavy clouds",
         })[off+5];
}
int temperature_index(object env) {
  int off,i;
  mixed clim, *co_ord;
  for (i=0;i<sizeof(coldarr);i++)
    off += (distance((mixed *)env->query_co_ord(), coldarr[i]) % (MAX_DIST*2));
  off = off / sizeof(coldarr);
  if ((clim = (mixed *)env->query_property("climate")))
    off += clim[C_TEMP];
  if (off>MAX_DIST) off = (MAX_DIST*2) - off;
  off -= (MAX_DIST/2);
  off = 0 - off;
  co_ord = (mixed *)env->query_co_ord();
  if (!co_ord)
    co_ord = ({ 0, 0, 0 });
  return (off + (timeofyear - (YEAR/2)) + (timeofday - (DAY/2)) + co_ord[2]);
}
int cloud_index(object env) {
  int off;
  mixed *clim;
  int i;
  for (i=0;i<sizeof(cloudarr);i++)
    off += (distance((mixed *)env->query_co_ord(), cloudarr[i]) % (MAX_DIST*2));
  off = off / sizeof(cloudarr);
  if ((clim = (mixed *)env->query_property("climate")))
    off += clim[C_CLOUD];
  if (off>MAX_DIST) off = (MAX_DIST*2) - off;
  off -= (MAX_DIST/2);
  off = 0-off;
  return (off + (timeofyear - (YEAR/2)));
}
int rain_index(object env) {
  int off;
  mixed *clim;
  int i;
  for (i=0;i<sizeof(rainarr);i++)
    off += (distance((mixed *)env->query_co_ord(), rainarr[i]) % (MAX_DIST*2));
  off = off / sizeof(rainarr);
  if ((clim = (mixed *)env->query_property("climate")))
    off += clim[C_RAIN];
  if (off>MAX_DIST) off = (MAX_DIST*2) - off;
  off -= MAX_DIST/2;
  off = 0-off;
  return off;
}
void update_low() {
  int i;
  timeofday++;
  if (timeofday>DAY) {
    timeofday = 0;
    timeofyear++;
    mooncycle++;
    if (mooncycle %2) {
      moonoff += 1;
      moonoff = moonoff % (DAY/2);
    }
    timeofyear = timeofyear % YEAR;
    mooncycle = mooncycle % 10;
    save_object(FILE_NAME);
  }
  for (i=0;i<sizeof(rainarr);i++) {
    rainarr[i][0] += random(3)-1;
    rainarr[i][0] = rainarr[i][0] % (MAX_DIST*2);
    rainarr[i][1] += random(3)-1;
    rainarr[i][1] = rainarr[i][1] % (MAX_DIST*2);
  }
  for (i=0;i<sizeof(cloudarr);i++) {
    cloudarr[i][0] += random(3)-1;
    cloudarr[i][0] = cloudarr[i][0] % (MAX_DIST*2);
    cloudarr[i][1] += random(3)-1;
    cloudarr[i][1] = cloudarr[i][1] % (MAX_DIST*2);
  }
  for (i=0;i<sizeof(coldarr);i++) {
    coldarr[i][0] += random(3)-1;
    coldarr[i][0] = coldarr[i][0] % (MAX_DIST*2);
    coldarr[i][1] += random(3)-1;
    coldarr[i][1] = coldarr[i][1] % (MAX_DIST*2);
  }
  intensity += random(3)-1;
  if (intensity<50)
    intensity=50;
  if (intensity>300)
    intensity=300;
  call_out("update_low",SPEED);
}
void dest_me() {
  save_object(FILE_NAME);
  ::dest_me();
}