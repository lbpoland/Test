# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/accept.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_surrender(self, player: MudObject) -> Any:
            object *victims
            victims = this_player()->query_surrenderers()
            if (!victims  ||  victims.index(player) if player in victims else -1 == -1) {
            add_failed_mess("Sorry, but $I has not offered to surrender to you.\n",
            [player] )
            return 0


    def do_club(self, club_name: str, players: MudObject) -> Any:
            object ob
            string club
            int ok
            foreach (ob in players) {
            club = this_player()->query_respond_command(CLUB_RESPOND_TYPE, ob)
            if (club) {
            if (lower_case(club) == lower_case(club_name)) {
            if (CLUB_HANDLER->is_member_of(club_name,
            this_player()->query_name())) {
            add_failed_mess("You are already a member of '" +
            CLUB_HANDLER.query_club_name(club_name) +
            "'.\n")
            } else {
            CLUB_HANDLER->add_member(club_name,
            this_player()->query_name())
            add_succeeded_mess("$N join$s '" +
            CLUB_HANDLER.query_club_name(club_name) +
            "' with an invite from $I.\n",
            [ob] )
            ob.remove_respond_command(CLUB_RESPOND_TYPE, ob)
            ok++
            all_inventory(this_player())->event_joined_club(this_player(),
            club_name)



class Accept(MudObject):
