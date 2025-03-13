# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/playtester/check.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def pt_protected(self, ) -> str:
            varargs int cmd(string check, string name) {
            object ob = environment (this_player())
            int min, max
            mixed *chats
            mixed *chatsd, *chatsn
            string day, night
            string ret = ""
            int count
            mixed *args, *args1
            if (ob->query_property ("restrict check")) {
            this_player()->add_failed_mess (self, "The use of the check "
            "command in this room has been restricted.\n", [}))
            return 0


    def do_check_quota(self, ) -> int:
            string* bits
            string shortdate
            int* spam
            int reports
            int age
            int curage
            mapping spamtoo
            bits = explode( ctime( time() ), " " ) - [""]
            shortdate = bits[ 1 ] + " " + bits[ 4 ]
            spamtoo = PLAYTESTER_HAND->
            query_bugs( this_player()->query_name() )
            if ( mapp( spamtoo ) ) {
            spam = spamtoo[ shortdate ]
            if ( arrayp( spam ) ) {
            reports = spam[ 0 ]
            age = spam[ 1 ]
            curage = PLAYTESTER_HAND.get_age_uncached(this_player()->query_name())
            age += curage - spam[2]
            await  this_player().send("This month (" + shortdate + "), you "
            "have made " + reports + " report" +
            ( ( reports == 1 ) ? "" : "s" ) +  " in " +
            time_string( age ) + " online.\n" )
            return 1
            } else {
            tell_object( this_player(), "You cannot check your playtester "
            "quota.\n" )
            return 1


    def cmd_chats(self, obs: Any) -> int:
            mixed* chats
            string ret
            int i
            object ob
            ret = ""
            foreach (ob in obs) {
            ret += "$I$0=%^YELLOW%^$C$" + ob.the_short() + "%^RESET%^:\n"
            chats = ob.query_chat_string()
            if (sizeof(chats)) {
            ret += "$I$0=   %^BOLD%^Chats:%^RESET%^ (Chance: " + chats[0] + ")\n"
            chats = chats[1]
            for (i = 0; i < sizeof(chats); i += 2) {
            if (stringp(chats[i + 1])) {
            ret += "$I$6=   (Weight " + chats[i] + "): " + chats[i + 1] + "\n"
            } else if (arrayp(chats[i + 1])) {
            ret += "$I$6=   (Weight " + chats[i] + ") Story:\n "
            foreach (string story in chats[i + 1]) {
            ret += story + "\n"


    def pt_protected(self, ) -> str:
            object *obs = filter (users(), (: $1.query_playtester() :))
            string ret = ""
            obs = filter (obs, (: $1.query_pt_protection() :))
            if (!sizeof(obs)) {
            tell_object (this_player(), "No-one is currently using PT Protection.\n")



class Check(MudObject):
