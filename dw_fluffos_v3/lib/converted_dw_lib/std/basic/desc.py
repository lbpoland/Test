# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/desc.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_short(self, words: Any) -> None:
            if (functionp(words)) {
            if (!short_d)
            plural_d = (: pluralize(evaluate(short_d)) :)
            } else {
            if ( !short_d && words && ( words != "" ) )
            plural_d = pluralize( words )


    def query_short(self, ) -> Any:
            if ( functionp( short_d ) )  {
            return evaluate(short_d)


    def query_short_desc(self, ) -> str:
            string tmp
            if(!short_desc) {
            short_desc = ""
            if(self.query_str() > 16)
            short_desc += "strapping "
            else if(self.query_dex() > 16)
            short_desc += "nimble "
            else if(self.query_int() > 16)
            short_desc += "studious "
            else if(self.query_wis() > 16)
            short_desc += "pious "
            short_desc += "young "
            switch(self.query_class_ob()) {
            case "/std/classs/warrior":
            short_desc += (self.query_gender() == 2? "female " : "male ") +
            "warrior"
            break
            case "/std/classs/thief":
            tmp = "/std/classs/thief"->query_class_data()
            if(tmp)
            short_desc += (self.query_gender() == 2? "female ": "male ")+
            tmp
            else
            short_desc += (self.query_gender() == 2? "female ": "male ")+
            "thief"
            break
            case "/std/classs/wizard":
            short_desc += (self.query_gender() == 2? "female " : "male ") +
            "wizard"
            break
            case "/std/classs/witch":
            short_desc += "witch"
            break
            case "/std/classs/assassin":
            short_desc += (self.query_gender() == 2? "female " : "male ") +
            "assassin"
            break
            default:
            short_desc += (self.query_gender() == 2? "lass" : "lad")


    def query_plural_desc(self, ) -> str:
            return pluralize( query_short_desc() )


    def query_long_details(self, arg: str, dark: int, looker: MudObject) -> str:
            return 0


    def long(self, str: str, dark: int) -> str:
            if (!long_d)
            return "You see nothing particularly interesting.\n"
            if (functionp(long_d))
            return (string)evaluate(long_d)
            return long_d


    def query_determinate(self, thing: MudObject) -> str:
            if(query_visible(thing)) {
            #ifdef USE_ROLE_PLAYING_SHORTS
            if(interactive(self) &&
            thing.query_role_playing() &&
            !thing.is_friend(self->query_name()))
            return "a "
            #endif
            return (string)self.query_property( "determinate" )



class Desc(MudObject):
