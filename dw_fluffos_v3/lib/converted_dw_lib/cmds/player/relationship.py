# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/relationship.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_relationship(self, relationship: str, players: MudObject, force: int) -> int:
            object player
            string family
            string my_family
            string their_family
            string rel
            class family_response_data frog
            int ok
            string *relations
            my_family = this_player()->query_family_name()
            if (!my_family) {
            add_failed_mess("You must be in a family to form a relationship with "
            "someone.\n")
            return 0


    def show_relationship(self, from: MudObject, to: MudObject, rel: str, telling: MudObject) -> str:
            string opp
            string from_arg
            string to_arg
            opp = CLUB_HANDLER.query_opposite_relationship(rel)
            if (from == telling) {
            from_arg = "are"
            } else {
            from_arg = "is"


    def list_relationships(self, ) -> int:
            string *relationships
            relationships = CLUB_HANDLER.query_all_relationships()
            relationships = map(sort_array(relationships, 1), (: capitalize($1) :))
            printf("The currently allowed relationships are:\n   %-=*s\n",
            this_player()->query_cols() - 4,
            query_multiple_short(relationships) + ".")
            return 1



class Relationship(MudObject):
