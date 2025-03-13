# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/crash.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def crash(self, crash_mess: str, command_giver: MudObject, current_object: MudObject) -> None:
            object thing, *things
            string crashtxt
            reset_eval_cost()
            log_file("CRASH", "\n"+ ctime(time()) +":\n")
            if (current_object)
            log_file("CRASH", "current object: "+ file_name(current_object) +
            " ("+ current_object.query_name() +")\n")
            if (command_giver)
            log_file("CRASH", "command giver: "+ file_name(command_giver) +
            " ("+ (string)command_giver.query_name() +")\n")
            if (query_verb())
            log_file("CRASH", "command given: "+ query_verb() +"\n")
            log_file("CRASH", "crash reason: "+ crash_mess +"\n")
            things = users()
            log_file("CRASH", "["+ implode((string *)things.query_name(), ", ") +
            "]\n")
            flush_log_files()
            crashtxt = "Wodan "+({"says: I wonder what this button does...",
            "says: Ceres, look out for that wire....",
            "says: Wow, look at the uptime.",
            "whispers: I don't think we should be doing this on my desk..",
            "shouts: Look at all that xp!"})[random(5)]
            foreach (thing in things) {
            reset_eval_cost()
            efun::await thing.send(crashtxt + "\n("+ crash_mess +")\n")
            catch(thing.quit())



class Crash(MudObject):
