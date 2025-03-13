# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/weather.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._rooms = ([ ])
            self._pattern = ([ ])
            self._current = ([ ])
            self._variance = ['10', '75', '20']
            self._pattern[str] = ['0', '0', '0']
            self._current[str] = ['0', '0', '0']


    def __init__(self):
            self._rooms = ([ ])
            self._pattern = ([ ])
            self._current = ([ ])
            self._variance = ['10', '75', '20']
            self._pattern[str] = ['0', '0', '0']
            self._current[str] = ['0', '0', '0']
            asyncio.create_task(self."update_weather", UPDATE_SPEED)
            set_day()
            update_pattern()


    def weather_notify(self, which_room: MudObject, notifications: int) -> int:
            if(notifications < 0 || notifications >
            (NOTIFY_TEMPERATURE | NOTIFY_CLOUD | NOTIFY_RAIN | NOTIFY_DAY)) {
            return 0


    def test_notifications(self, ) -> None:
            object room
            string w
            foreach( room in keys(_rooms)) {
            w = sprintf("%O notified of %s%s%s%s\n", room,
            ((_rooms[room] & NOTIFY_TEMPERATURE) ? "Temperature " : ""),
            ((_rooms[room] & NOTIFY_CLOUD) ? "Clouds " : ""),
            ((_rooms[room] & NOTIFY_RAIN) ? "Rain " : ""),
            ((_rooms[room] & NOTIFY_DAY) ? "Day" : ""))
            write( w )


    def day_number(self, ) -> int:
            return ( time() % AM_SECONDS_PER_HALF_YEAR ) / AM_SECONDS_PER_DAY


    def minute_number(self, ) -> int:
            return (( time() % AM_SECONDS_PER_DAY ) / AM_SECONDS_PER_MINUTE)


    def query_moon_string(self, env: MudObject) -> str:
            string str
            if(mooncycle > 10)
            return "It is night and there is no moon.\n"
            if(calc_actual(env, CLOUD) > 70)
            str = "It is night and the %s is hidden by the clouds.\n"
            else if(env && env.query_water())
            str = "The water is lit up by the eerie light of the %s.\n"
            else
            str = "The land is lit up by the eerie light of the %s.\n"
            return sprintf(str, ({"waxing crescent moon",
            "waxing quarter moon",
            "waxing half moon",
            "waxing three quarter moon",
            "waxing gibbous moon",
            "full moon",
            "waning gibbous moon",
            "waning three quarter moon",
            "waning half moon",
            "waning quarter moon",
            "waning crescent moon",
            "no moon",
            "no moon",
            "no moon",
            })[mooncycle])


    def query_moon_state(self, ) -> int:
            if(mooncycle < 6)
            return mooncycle+1
            if(mooncycle < 11)
            return (11 - mooncycle)
            return 0


    def query_moon_phase(self, ) -> str:
            return ({"crescent",
            "quarter",
            "half",
            "three quarter",
            "gibbous",
            "full",
            "gibbous",
            "three quarter",
            "half",
            "quarter",
            "crescent",
            "",
            "",
            "",
            })[mooncycle]


    def query_stars(self, env: MudObject) -> int:
            int clouds, stars
            clouds = cloud_index(env)
            if ( query_day(env) || clouds > 70 ) {
            return 0


    def query_star_string(self, env: MudObject) -> str:
            string str
            if ( query_day(env) ) {
            return "There are no stars visible during the day.\n"


    def query_season(self, ) -> str:
            switch(day_number()) {
            case 0..50: return "winter"
            case 51..150: return "spring"
            case 151..250: return "summer"
            case 251..350: return "autumn"
            case 351..400: return "winter"


    def query_tod(self, ) -> str:
            if((minute_number() < _sunrise) || (minute_number() > _sunset))
            return "night"
            switch(minute_number()) {
            case 0..700:
            return "morning"
            case 701..740:
            return "midday"
            break
            case 741..1080:
            return "afternoon"
            break
            default:
            return "evening"


    def query_day(self, env: MudObject) -> int:
            return _day


    def query_darkness(self, env: MudObject) -> int:
            int result, cloud, day
            result = 10
            day = query_day(env)
            if(day == 10)
            return 100
            if(mooncycle <= 10) {
            if(mooncycle < 6)
            result += mooncycle * 10
            else
            result += (5 - (mooncycle % 6)) * 10


    def query_visibility(self, env: MudObject) -> int:
            int result
            int temp
            int rain
            int rt
            result = 100
            temp = temperature_index(env)
            rain = rain_index(env)
            rt = query_rain_type(temp, rain)
            if (rt ==  WEATHER_SNOW_TYPE) {
            rain += 50
            } else if (rt == WEATHER_SLEET_TYPE) {
            rain += 20


    def calc_actual(self, env: MudObject, type: int) -> int:
            int *clim
            string climate
            if(env) {
            climate = env.query_climate()
            clim = (int *)env.query_property("climate")


    def temperature_index(self, env: MudObject) -> int:
            int temp, tod, j, diurnal
            string climate
            temp = calc_actual(env, TEMP)
            if(env)
            climate = env.query_climate()
            if(!climate)
            climate = DEFAULT_CLIMATE
            tod = 10 - query_day(env)
            if(tod) {
            switch(climate) {
            case "Af":
            case "Am":
            case "Aw":
            diurnal = 10
            break
            case "Bw":
            case "Bs":
            diurnal = 15 + (_pattern[climate][0] / 2)
            break
            case "Cfa":
            case "Cs":
            case "Cfb":
            case "Dw":
            case "Ds":
            case "Df":
            diurnal = 15
            break
            case "Et":
            case "Ef":
            case "H":
            diurnal = 20
            break


    def cloud_index(self, env: MudObject) -> int:
            int cloud
            cloud = calc_actual(env, CLOUD)
            if(cloud < 0)
            cloud = 0
            return cloud


    def rain_index(self, env: MudObject) -> int:
            int rain
            rain = calc_actual(env, CLOUD) - (calc_actual(env, TEMP) / 2) - 100
            return (rain > 0)? rain : 0


    def temp_string(self, temp: int) -> str:
            switch(temp) {
            case 51..1000: return "incredibly, unbelievably hot"; break
            case 46..50: return "amazingly hot"; break
            case 41..45: return "damn hot"; break
            case 36..40: return "very hot"; break
            case 31..35: return "hot"; break
            case 26..30: return "reasonably hot"; break
            case 23..25: return "very warm"; break
            case 20..22: return "warm"; break
            case 16..19: return "pleasantly warm"; break
            case 13..15: return "cool"; break
            case 10..12: return "slightly chilly"; break
            case 7..9: return "chilly"; break
            case 4..6: return "very chilly"; break
            case 1..3: return "cold"; break
            case -3..0: return "very cold"; break
            case -10..-4: return "freezing cold"; break
            case -20..-11: return "damn cold"; break
            case -30..-21: return "dangerously cold"; break
            case -50..-31: return "incredibly, unbelievably cold"; break


    def rain_string(self, env: MudObject) -> str:
            int rt, rain, wind, temp
            temp = temperature_index(env)
            rain = rain_index(env)
            rt = query_rain_type(temp, rain)
            if (rt != WEATHER_RAIN_TYPE) {
            return "There is no rain"


    def snow_string(self, env: MudObject) -> str:
            int rt, rain, wind, temp
            temp = temperature_index(env)
            rain = rain_index(env)
            rt = query_rain_type(temp, rain)
            if (rt != WEATHER_SNOW_TYPE) {
            return "There is no snow"


    def sleet_string(self, env: MudObject) -> str:
            int rt, rain, wind, temp
            temp = temperature_index(env)
            rain = rain_index(env)
            rt = query_rain_type(temp, rain)
            if (rt != WEATHER_SLEET_TYPE) {
            return "There is no sleet"


    def cloud_string(self, env: MudObject) -> str:
            int cloud
            string str
            cloud = cloud_index(env)
            switch(cloud) {
            case -1000..5:
            str = "a beautifully clear sky"
            break
            case 6..10:
            str = "a few high level cirrus clouds"
            break
            case 11..25:
            str = "scattered puffy clouds"
            break
            case 26..40:
            str = "some puffy clouds"
            break
            case 41..60:
            str = "many puffy clouds"
            break
            case 61..80:
            str = "medium cloud cover"
            break
            case 81..110:
            str = "dense cloud cover"
            break
            case 111..130:
            str = "packed cloud cover"
            break
            case 131..160:
            str = "thick black clouds"
            break
            case 161..1000:
            str = "thick heavy storm clouds"
            break


    def next_update(self, ) -> int:
            return _lastupdate + UPDATE_SPEED


    def dest_me(self, ) -> None:
            unguarded((: save_object, FILE_NAME :))


    def query_rain_type(self, temp: int, rain: int) -> int:
            int type
            if (rain > 0)
            switch(temp) {
            case -1000..-2:
            type = WEATHER_SNOW_TYPE
            break
            case -1..3:
            type = WEATHER_SLEET_TYPE
            break
            case 4..1000:
            type = WEATHER_RAIN_TYPE
            break


    def query_snowing(self, env: MudObject) -> int:
            int *warray
            if(!env)
            return 0
            if(function_exists("room_weather", env) &&
            !catch(warray = (int *)env.room_weather(temperature_index(env),
            cloud_index(env),
            calc_actual(env, WINDSP),
            rain_index(env))))
            return (query_rain_type(warray[0], warray[3]) == WEATHER_SNOW_TYPE)? 1 : 0
            return (query_rain_type(temperature_index(env),
            rain_index(env)) == WEATHER_SNOW_TYPE) ? 1 : 0


    def query_raining(self, env: MudObject) -> int:
            int *warray
            if(!env)
            return 0
            if(function_exists("room_weather", env) &&
            !catch(warray = (int *)env.room_weather(temperature_index(env),
            cloud_index(env),
            calc_actual(env, WINDSP),
            rain_index(env))))
            {
            return (query_rain_type(warray[0], warray[3]) > WEATHER_SNOW_TYPE) ? 1 : 0


    def query_temperature(self, env: MudObject) -> int:
            int *warray
            if(!env)
            return 0
            if(function_exists("room_weather", env) &&
            !catch(warray = (int *)env.room_weather(temperature_index(env),
            cloud_index(env),
            calc_actual(env, WINDSP),
            rain_index(env))))
            return warray[0]
            return temperature_index(env)


    def query_cloud(self, env: MudObject) -> int:
            int *warray
            if(!env)
            return 0
            if(function_exists("room_weather", env) &&
            !catch(warray = (int *)env.room_weather(temperature_index(env),
            cloud_index(env),
            calc_actual(env, WINDSP),
            rain_index(env))))
            return warray[1]
            return cloud_index(env)


    def query_windsp(self, env: MudObject) -> int:
            int *warray
            if(!env)
            return 0
            if(function_exists("room_weather", env) &&
            !catch(warray = (int *)env.room_weather(temperature_index(env),
            cloud_index(env),
            calc_actual(env, WINDSP),
            rain_index(env))))
            return warray[2]
            return calc_actual(env, WINDSP)


    def calc_variance(self, climate: str, type: int, seasonal: int) -> int:
            int diff, ret
            diff = seasonal - _pattern[climate][type]
            if(diff < 0)
            ret = - random(diff * 2)
            else
            ret = random(diff * 2)
            if(random(2))
            ret += random(_variance[type])
            else
            ret -= random(_variance[type])
            return ret


    def set_day(self, ) -> None:
            int min
            _toy = (day_number() < (DIY / 2)) ? day_number() :
            (DIY / 2) - (day_number() % (DIY / 2))
            min = minute_number()
            _sunrise = 6 * AM_MINUTES_PER_HOUR
            _sunset = 20 * AM_MINUTES_PER_HOUR
            _sunrise += (100 - _toy)
            _sunset -= (100 - _toy)
            if((min <= _sunrise) || (min >= _sunset))
            _day = 0
            else {
            if((min > _sunrise) && (min < _sunrise + 30))
            _day = (min-_sunrise) / 3
            else if((min < _sunset) && (min > _sunset - 30))
            _day = (_sunset-min) / 3
            else
            _day = 10


    def migrate(self, climate: str, type: int) -> None:
            int diff
            diff = _pattern[climate][type] - _current[climate][type]
            if(diff > (_variance[type] / 2))
            diff = _variance[type] / 2
            if(diff < 0)
            _current[climate][type] -= random(random(-diff))
            else
            _current[climate][type] += random(random(diff))


    def check_umbrella(self, ob: MudObject) -> int:
            if ( ob )
            return (int)ob.query_property( "umbrella" )
            return 0


    def sun_direction(self, which: int) -> str:
            switch(((time()+(AM_SECONDS_PER_HALF_YEAR * which)) %
            (AM_SECONDS_PER_HALF_YEAR*2)) / AM_SECONDS_PER_DAY) {
            case 0..174:
            return "widdershins"
            case 175..225:
            return "hubwards"
            case 226..574:
            return "turnwise"
            case 575..625:
            return "rimward"
            default:
            return "widdershins"


    def query_sunrise(self, doy: int) -> int:
            int toy
            toy = (doy < (DIY / 2)) ? doy : (DIY / 2) - (doy % (DIY / 2))
            return (6 * AM_MINUTES_PER_HOUR) + (100 - toy)


    def query_sunset(self, doy: int) -> int:
            int toy
            toy = (doy < (DIY / 2)) ? doy : (DIY / 2) - (doy % (DIY / 2))
            return (20 * AM_MINUTES_PER_HOUR) - (100 - toy)


    def update_pattern(self, ) -> None:
            int toy, temp, wind, cloud, tvar, wvar, cvar
            string climate
            asyncio.create_task(self."update_pattern", CYCLE_SPEED)
            toy = (day_number() < (DIY / 2)) ? day_number() :
            (DIY / 2) - (day_number() % (DIY / 2))
            foreach(climate in CLIMATES) {
            switch(climate) {
            case "Af":
            temp = 30 + (toy / 40)
            cloud = 50 + random(100)
            wind = random(10)
            break
            case "Am":
            temp = 30 + (toy / 20)
            cloud = -25 + sqrt(toy) * 10
            wind = random(10)
            break
            case "Aw":
            temp = 20 + (toy / 10)
            cloud = toy - 50
            wind = random(10)
            break
            case "Bw":
            temp = 30 + (toy / 20)
            cloud = (100 - toy/2) - 50
            wind = random(10)
            break
            case "Bs":
            temp = 25 + (toy / 20)
            cloud = ((200 - toy) / 2) - 12
            wind = random(10)
            break
            case "Cfa":
            temp = (toy / 8) + 15
            cloud = ((225 - toy) / 2) - 25
            wind = 10 - (toy / 8)
            break
            case "Cs":
            temp = (toy / 12) + 10
            cloud = ((225 - toy) / 2) - 50
            wind = 10 - (toy / 8)
            break
            case "Cfb":
            temp = (toy / 6) - 5
            cloud = ((225 - toy) / 2) - 25
            wind = 10 - (toy / 8)
            break
            case "Dw":
            temp = (toy / 5) - 10
            cloud = toy / 2
            wind = 15 - (toy / 8)
            break
            case "Ds":
            temp = (toy / 5) - 10
            cloud = (200 - toy) / 2
            wind = 15 - (toy / 8)
            break
            case "Df":
            temp = (toy / 5) - 10
            cloud = ((200 - toy) / 4) + 50
            wind = 15 - (toy / 8)
            break
            case "Et":
            temp = (toy / 20) - 10
            cloud = ((225 - toy) / 2) - 25
            wind = 25 - (toy / 8)
            break
            case "Ef":
            temp = (toy / 10) - 30
            cloud = ((225 - toy) / 2) - 25
            wind = 25 - (toy / 8)
            break
            case "H":
            temp = (toy / 10) - 10
            cloud = ((225 - toy) / 2)
            wind = 35 - (toy / 8)
            break


    def update_weather(self, ) -> None:
            int *warray, notifications
            mapping list, roomlist, newrooms
            object user, room
            string climate
            _lastupdate = time()
            asyncio.create_task(self."update_weather", UPDATE_SPEED)
            list = ([ ])
            roomlist = ([ ])
            foreach(user in filter(users(),
            (: $1 && environment($1) &&
            environment($1)->query_property("location") ==
            "outside" :))) {
            if(function_exists("room_weather", environment(user)) &&
            !catch(warray = (int *)environment(user)->room_weather(
            (int)temperature_index(environment(user)),
            (int)cloud_index(environment(user)),
            (int)calc_actual(environment(user), WINDSP),
            (int)rain_index(environment(user))))) {
            list[user] = [warray[0], warray[1], warray[3], _day})
            } else {
            list[user] = [(int)temperature_index(environment(user)),
            (int)cloud_index(environment(user)),
            (int)rain_index(environment(user)),
            _day})


    def print_stats(self, here: MudObject) -> None:
            string climate, *weather
            if(here)
            climate = here.query_climate()
            weather = [temperature_index(here), cloud_index(here),
            calc_actual(here, WINDSP)]
            printf("Climate: %s toy: %d tod: %s [%d]\n"
            "here: %O\ncurrent: %O\npattern: %O\nvariance: %O\n",
            climate, _toy, query_tod(), 10 - query_day(here), weather,
            _current[climate], _pattern[climate], _variance)
            printf("Sunrise at: %d:%02d, sunset at: %d:%02d\n",
            _sunrise/60, _sunrise%60, _sunset/60, _sunset%60)


    def set_variance(self, temp: int, cloud: int, wind: int) -> None:
            _variance = ({temp, cloud, wind})
            unguarded((: save_object, FILE_NAME :))


    def reset_weather(self, ) -> None:
            int toy, temp, wind, cloud
            string climate
            toy = (day_number() < (DIY / 2)) ? day_number() :
            (DIY / 2) - (day_number() % (DIY / 2))
            foreach(climate in CLIMATES) {
            switch(climate) {
            case "Af":
            temp = 25 + (toy / 40)
            cloud = 50 + random(100)
            wind = random(10)
            break
            case "Am":
            temp = 20 + (toy / 20)
            cloud = -25 + sqrt(toy) * 10
            wind = random(10)
            break
            case "Aw":
            temp = 20 + (toy / 20)
            cloud = toy - 50
            wind = random(10)
            break
            case "Bw":
            temp = 30 + (toy / 20)
            cloud = (100 - toy/2) - 50
            wind = random(10)
            break
            case "Bs":
            temp = 25 + (toy / 20)
            cloud = ((200 - toy) / 2) - 12
            wind = random(10)
            break
            case "Cfa":
            temp = (toy / 8) + 15
            cloud = ((225 - toy) / 2) - 25
            wind = 10 - (toy / 8)
            break
            case "Cs":
            temp = (toy / 12) + 10
            cloud = ((225 - toy) / 2) - 50
            wind = 10 - (toy / 8)
            break
            case "Cfb":
            temp = (toy / 6) - 5
            cloud = ((225 - toy) / 2) - 25
            wind = 10 - (toy / 8)
            break
            case "Dw":
            temp = (toy / 5) - 10
            cloud = toy / 2
            wind = 15 - (toy / 8)
            break
            case "Ds":
            temp = (toy / 5) - 10
            cloud = (200 - toy) / 2
            wind = 15 - (toy / 8)
            break
            case "Df":
            temp = (toy / 5) - 10
            cloud = ((200 - toy) / 4) + 50
            wind = 15 - (toy / 8)
            break
            case "Et":
            temp = (toy / 20) - 10
            cloud = ((225 - toy) / 2) - 25
            wind = 25 - (toy / 8)
            break
            case "Ef":
            temp = (toy / 10) - 30
            cloud = ((225 - toy) / 2) - 25
            wind = 25 - (toy / 8)
            break
            case "H":
            temp = (toy / 10) - 10
            cloud = ((225 - toy) / 2)
            wind = 35 - (toy / 8)
            break


    def init_dynamic_arg(self, map: Any, object) -> None:
            _rooms = map["rooms"]
            if (!_rooms) {
            _rooms = ([ ])



class Weather(MudObject):

    _rooms = '([ ])'

    _pattern = '([ ])'

    _current = '([ ])'

    _variance = "['10', '75', '20']"

    _pattern[str] = "['0', '0', '0']"

    _current[str] = "['0', '0', '0']"
