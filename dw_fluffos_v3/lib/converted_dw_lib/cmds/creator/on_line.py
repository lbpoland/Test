# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/on_line.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def idle_time(self, person: MudObject) -> str:
            int hours, mins, secs
            string s, m, h
            secs = query_idle(person)
            mins = secs / 60
            secs %= 60
            hours = mins / 60
            mins %= 60
            s = ("0"+secs)[<2..<1]
            m = ("0"+mins)[<2..<1]
            if ( !hours )  {
            return " (idle: "+m+":"+s+")"


    def cmd(self, show_idle: int) -> int:
            object *people, person
            string *cre, *invis, *director, *trustee, bing, obtyp
            cre = [})
            invis = [})
            director = [})
            trustee = [})
            people = filter_array( users(), (: $1.query_creator() :) )
            people = people - this_player()->query_ignoring( people )
            people = sort_array( people,
            (: strcmp( $1.query_name(), $2.query_name() ) :) )
            foreach( person in people )  {
            bing = person.query_cap_name()
            if ( show_idle && query_idle( person ) > 120 )  {
            bing += idle_time( person )



class On_line(MudObject):
