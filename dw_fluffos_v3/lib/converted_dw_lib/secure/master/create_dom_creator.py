# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/create_dom_creator.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def create_domain(self, name: str, lord: str) -> int:
            string file
            object *interactives
            if (!( master()->high_programmer(previous_object(-1)) &&
            sizeof((interactives = filter(previous_object(-1),
            (: interactive($1) :))) ))) {
            write("Cheat!\n")
            return 0


    def employ_creator(self, name: str) -> int:
            object *interactives
            string fname
            if (!( master()->query_lord(previous_object(-1)) &&
            sizeof((interactives = filter(previous_object(-1),
            (: interactive($1) :))))))
            return 0
            if (!PLAYER_HANDLER.test_user(name)) {
            write("User does not exist.\n")
            return 1


    def dismiss_creator(self, str: str) -> int:
            string name
            string reason
            string fname
            string save_file
            object *interactives
            if (!( master()->query_lord(previous_object(-1)) &&
            sizeof((interactives = filter(previous_object(-1),
            (: interactive($1) :))))))
            return 0
            if (sscanf(str, "%s %s", name, reason) != 2) {
            notify_fail("You need to give a reason!\n")
            return 0


    def eligible_creator(self, player: MudObject) -> int:
            int age, level
            string age_str, reasoning
            reasoning =
            "  You do not have a *right* to create here.  In order to enhance your\n"
            "chances to be employed, you should demonstrate by your actions that you\n"
            "are worthy.\n"
            "  If our Creators find lots of your bug, typo, and idea reports in their\n"
            "directories, then your chances are improved.  If you have been a trouble-\n"
            "maker here, your chances are very slim.  Harrassing the Lords for a\n"
            "position will not help your chances either.\n"
            "  Having access to a MUD's file system is a great responsibility.  It\n"
            "cannot be given out to strangers who have not demonstrated their trust-\n"
            "worthiness.  After investing a fair amount of your time and energy in\n"
            "playing at FaerûnWorld, you are less likely to try to hurt it.  This is\n"
            "why we cannot give out instant creatorships unless we know you from\n"
            "elsewhere.  Please try to be understanding about our policy.\n\n"
            age   = - ( (int) player.query_time_on() )
            level = (int)player.query_level()
            if ( ( level >= 150 ) && ( age > 432000 ) ) {
            write("  You have achieved the *minimum* requirements necessary to apply "
            "for a\n"
            "creatorship at " + mud_name() + ".  You must now pass a review of the Lords "
            "to be\naccepted.\n"+ reasoning )
            return 1



class Create_dom_creator(MudObject):
