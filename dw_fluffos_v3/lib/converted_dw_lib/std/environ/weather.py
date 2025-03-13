# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/environ/weather.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("weather")
            set_short("weather controller extrodinare")
            set_long("The weather controller, at least this one is always right!\n")
            cloudarr = [[0,0], [50,50], [-50,-50]]
            rainarr = [[0,0], [50,50], [-50,-50]]
            coldarr = [[0,0], [50,50], [-50,-50]]
            intensity = 100
            restore_object(FILE_NAME)
            asyncio.create_task(self."update_low",SPEED)
            move("bing")


    def query_moon_string(self, env: MudObject) -> str:
            int bing
            bing = timeofday - (DAY/4) -
            (distance((mixed *)env.query_co_ord(), [0, 0, 0,])/100)
            if (bing<0) bing += DAY
            if ((moonoff+(DAY/2)<bing) && (bing<DAY-moonoff))
            return 0
            return ["full moon",
            "waning three quarter moon",
            "waning half moon",
            "waning quarter moon",
            "waning cresent moon",
            "new moon",
            "waxing cresent moon",
            "waxing quarter moon",
            "waxing half moon",
            "waxing three quarter moon"][mooncycle]


    def distance(self, co_ord1: Any, co_ord2: Any) -> int:
            int off
            if (!pointerp(co_ord1) || !pointerp(co_ord2))
            return 0
            if (co_ord1[0]>co_ord2[0])
            off = co_ord1[0] - co_ord2[0]
            else
            off = co_ord2[0] - co_ord1[0]
            if (co_ord1[1]>co_ord2[1])
            off += co_ord1[1] - co_ord2[1]
            else
            off += co_ord2[1] - co_ord1[1]
            return off


    def query_day(self, env: MudObject) -> int:
            int bing, bit
            if (!env) {
            load_object(CONFIG_START_LOCATION)
            env = find_object(CONFIG_START_LOCATION)


    def query_darkness(self, env: MudObject) -> int:
            int bing, per, i
            per = -cloud_index(env)
            if (per <-100)
            per = -100
            if (per > 100)
            per = 100
            if ((i=query_day(env))) {
            i *= 20
            if (i>100)
            i = 100
            return 50+(per+100)*150*i/20000


    def weather_string(self, env: MudObject) -> str:
            return temperature_string(env)+" with "+cloud_string(env)+
            rain_string(env)


    def query_raining(self, env: MudObject) -> int:
            int cloud,rain
            if (temperature_index(env)/(100/7)<2) {
            cloud = cloud_index(env)
            if (cloud<=0)
            return 0
            rain = rain_index(env)
            if (cloud-rain<=0)
            return 0
            return cloud-rain


    def query_hailing(self, env: MudObject) -> int:
            int cloud, rain
            if (temperature_index(env)/(100/7)==2) {
            cloud = cloud_index(env)
            if (cloud <=0)
            return 0
            rain = rain_index(env)
            if (cloud-rain <=0)
            return 0
            return cloud-rain


    def query_snowing(self, env: MudObject) -> int:
            int cloud,rain
            if ((temperature_index(env)/(100/7))>=3) {
            cloud = cloud_index(env)
            if (cloud<=0)
            return 0
            rain = cloud_index(env)
            if (cloud-rain<=0)
            return 0
            return cloud-rain


    def rain_string(self, env: MudObject) -> str:
            int cloud, rain, temp
            string tempstr1,tempstr2
            cloud = cloud_index(env)
            rain = rain_index(env)
            if (cloud<=0) return ""
            if (cloud-rain<=0) return ""
            temp = temperature_index(env)/(100/7)
            if (temp>3) temp = 3
            if (temp<-3) temp = -3
            tempstr1 = ["very hot ",
            "hot ",
            "warm ",
            "nice ",
            "cold ",
            "",
            ""][temp+3]
            tempstr2 = [" rain",
            " rain",
            " rain",
            " rain",
            " rain",
            " hail",
            " snow"][temp+3]
            cloud = (cloud-rain) / 20
            if (cloud>5) cloud = 5
            return "\n"+capitalize(tempstr1 + ["very light",
            "light",
            "medium",
            "heavy",
            "very heavy"] [cloud]+tempstr2)


    def temperature_string(self, env: MudObject) -> str:
            int inten
            inten = temperature_index(env)
            inten /= 10
            if (inten>10)
            inten = 10
            if (inten<-10)
            inten = -10
            return ["Its one of those baking eggs on the pavement days",
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
            "Freezing cold"][inten+10]


    def cloud_string(self, env: MudObject) -> str:
            int off
            off = cloud_index(env) / 20
            if (off>5) off = 5
            if (off<-5) off = -5
            return ["a beatifully clear sky",
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
            })[off+5]


    def temperature_index(self, env: MudObject) -> int:
            int off,i
            mixed clim, *co_ord
            for (i=0;i<sizeof(coldarr);i++)
            off += (distance((mixed *)env.query_co_ord(), coldarr[i]) % (MAX_DIST*2))
            off = off / sizeof(coldarr)
            if ((clim = (mixed *)env.query_property("climate")))
            off += clim[C_TEMP]
            if (off>MAX_DIST) off = (MAX_DIST*2) - off
            off -= (MAX_DIST/2)
            off = 0 - off
            co_ord = (mixed *)env.query_co_ord()
            if (!co_ord)
            co_ord = [0, 0, 0]
            return (off + (timeofyear - (YEAR/2)) + (timeofday - (DAY/2)) + co_ord[2])


    def cloud_index(self, env: MudObject) -> int:
            int off
            mixed *clim
            int i
            for (i=0;i<sizeof(cloudarr);i++)
            off += (distance((mixed *)env.query_co_ord(), cloudarr[i]) % (MAX_DIST*2))
            off = off / sizeof(cloudarr)
            if ((clim = (mixed *)env.query_property("climate")))
            off += clim[C_CLOUD]
            if (off>MAX_DIST) off = (MAX_DIST*2) - off
            off -= (MAX_DIST/2)
            off = 0-off
            return (off + (timeofyear - (YEAR/2)))


    def rain_index(self, env: MudObject) -> int:
            int off
            mixed *clim
            int i
            for (i=0;i<sizeof(rainarr);i++)
            off += (distance((mixed *)env.query_co_ord(), rainarr[i]) % (MAX_DIST*2))
            off = off / sizeof(rainarr)
            if ((clim = (mixed *)env.query_property("climate")))
            off += clim[C_RAIN]
            if (off>MAX_DIST) off = (MAX_DIST*2) - off
            off -= MAX_DIST/2
            off = 0-off
            return off


    def update_low(self, ) -> None:
            int i
            timeofday++
            if (timeofday>DAY) {
            timeofday = 0
            timeofyear++
            mooncycle++
            if (mooncycle %2) {
            moonoff += 1
            moonoff = moonoff % (DAY/2)


    def dest_me(self, ) -> None:
            save_object(FILE_NAME)
            ::dest_me()



class Weather(MudObject):
