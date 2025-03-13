# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/watch.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("watch")
            add_adjective("demonic")
            add_alias("watch")
            set_main_plural("demonic watches")
            set_short("demonic watch")
            set_long("A small wrist attackable living quaters for a demon "+
            "the demon looks pretty harried about giveing out the "+
            "time all the time, and the pay is lousy..\n")
            set_value(20000)
            our_offset = 0
            their_offset = 8
            last_time = time()
            asyncio.create_task(self."check_alarm",60)
            alarms = [})


    def init(self, ) -> None:
            add_command("time", "")
            add_command("gmt", "<word'offset'>", (:self.set_gmt($4[0]):))
            add_command("use", "<direct:object>", (:self.use():))
            this_player()->add_command("read", self)


    def use(self, arg: str) -> int:
            if (!alarms)
            alarms = [})
            printf("%-=80s","You look into the watch and fiddle with several buttons, "+
            "Finally a light lights up in the top corner say you have "+
            "the security clearance to modify the settings.\n"+
            "You can \"set\" an alarm \"remove\" an alarm \"list\" the "+
            "set alarms. You can \"quit\" also.\n")
            write("What do you wish to do ? ")
            input_to("the_command")
            return 1


    def the_command(self, arg: str) -> int:
            string s1
            int i
            if (arg == "quit") {
            write("Thank you for using this wonderful watch.\n")
            return 1


    def query_auto_load(self, ) -> Any:
            mixed ret
            if (!alarms)
            alarms = [})
            ret = [their_offset, alarms]
            return ret


    def init_arg(self, arg: Any) -> None:
            their_offset = arg[0]
            alarms = arg[1]
            if (!alarms)
            alarms = [})


    def check_alarm(self, ) -> None:
            int the_time, offset, i
            int tmp
            the_time = time()
            offset = (the_time/(3600*24))*3600*24 - our_offset*3600
            for (i=0;i<sizeof(alarms);i+=4) {
            tmp = offset + (alarms[i+1]-our_offset+their_offset)*3600 + alarms[i+2]*60
            if (the_time>tmp && tmp>last_time) {
            alarm = 6
            alarm_name = alarms[i]
            if (alarms[i+3])
            alarm_write = explode(alarms[i+3],"\n")
            else
            alarm_write = ({
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            "Beep Beep Beep, Your "+alarms[i]+" alarm has gone off.\n",
            })
            offset_alarm = 0
            set_heart_beat(1)


    def heart_beat(self, ) -> None:
            if (our_player)
            our_player->event_say(self, "The watch goes: "+
            alarm_write[offset_alarm++]+"\n")
            if (offset_alarm>sizeof(alarm_write))
            set_heart_beat(0)


    def move(self, ob: MudObject) -> int:
            int i
            i = ::move(ob)
            our_player = environment()
            return i



class Watch(MudObject):
