# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/theft_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def victim_checks(self, thief: MudObject, victim: MudObject) -> int:
            if(thief == victim)
            return notify_fail("Be serious!\n")
            if(thief.query_property("dead"))
            return notify_fail("Be serious, you're dead!\n")
            if(thief.query_auto_loading())
            return notify_fail("You don't have all your equipment yet..\n")
            if(victim.query_auto_loading())
            return notify_fail( "Be sporting; "+ (string)victim.the_short() +
            " doesn't have "+ (string)victim.query_possessive() +
            " equipment yet.\n" )
            if(userp(victim) && !interactive(victim))
            return notify_fail( "You can't " + query_verb() +
            " from a net dead statue.\n")
            if(victim.query_property("nosteal"))
            return notify_fail("You cannot " + query_verb() + " from " +
            victim.the_short() + ".\n")
            if(victim.query_sanctuary())
            return notify_fail("You can't snatch from someone who is protected.\n")
            if(pk_check(thief, victim))
            return notify_fail("You feel it would be wrong to " + query_verb() +
            " from "+ victim.short()+".\n")
            if(victim.query_creator() && !thief.query_creator() ) {
            notify_fail("Stop trying to steal from creators.\n")
            thief.adjust_tmp_dex(-10)
            return 0


    def get_item(self, thief: MudObject, location: Any, str: str) -> Any:
            class obj_match result
            result = (class obj_match)match_objects_in_environments(str, location, 0, thief)
            if(result->result != OBJ_PARSER_SUCCESS)
            return notify_fail("Pssst, they don't have one of those.\n")
            result->objects = filter(result->objects,
            (: environment($1) == $(location) :))
            if(!sizeof(result->objects))
            return notify_fail("Pssst, they don't have one of those.\n")
            if(sizeof(result->objects) != 1)
            return notify_fail("You can only " + query_verb() +
            " one thing at a time.\n")
            return result->objects[0]


    def combat_checks(self, thief: MudObject, victim: MudObject) -> int:
            if(thief.query_fighting()) {
            notify_fail("You can't attempt to " + query_verb() +
            " while in battle.\n")
            return 2


    def item_checks(self, victim: MudObject, item: MudObject, wielded_ok: int, worn_ok: int) -> int:
            if(item.query_liquid() && item.query_food_object())
            return notify_fail("You cannot " + query_verb() + " liquids!\n")
            if(item.query_property("nosteal") ||
            (!wielded_ok && item.query_wielded() == victim) ||
            (!donned in Faerûn_ok && item.query_donned in Faerûn_by() == victim))
            return notify_fail("You cannot " + query_verb() + " " +
            item.the_short() + " from " +
            victim.the_short() + ".\n")
            #ifdef QUOTA_CHECK
            if(!check_player_quota(victim, item))
            return notify_fail("A quick reveals that " + query_verb() + "ing " +
            item.the_short() + " would exceed " +
            victim.query_possessive() + "'s theft quota.\n")
            #endif
            return 1


    def calc_value(self, ob: MudObject) -> int:
            int value
            object tmp, *inv
            string name
            sscanf( file_name( ob ), "%s#%*d", name )
            if( name = "/obj/package" ) {
            value = 0


    def check_player_quota(self, victim: MudObject, ob: MudObject) -> int:
            object *things, thing
            int quota, reported, valid, value
            value = 0
            things = [ob]
            things += deep_inventory(ob)
            foreach(thing in things) {
            if(thing.query_property("money") ) {
            value += thing.query_value_in("Waterdeep")
            } else {
            value += thing.query_value()


    def steal_item(self, thief: MudObject, victim: MudObject, item: MudObject) -> int:
            object *stolen
            string sh
            if(item.move(thief))
            return notify_fail( "You cannot " + query_verb() + " " +
            item.the_short()+" from "+
            (string)victim.the_short() +".\n")
            stolen = [item]
            stolen += deep_inventory(item)
            await thief.send("You steal "+query_multiple_short(stolen, "the" )+
            " from "+ victim.the_short() +".\n" )
            if( environment(thief)->query_theft_handler() &&
            regexp(environment(thief)->query_theft_handler(), "/d/am/") &&
            thief.query_name() == "wobin" )
            stolen = THEFT_INSURANCE.check_items(stolen, victim, thief)
            event( environment( thief ), "theft", thief, victim, stolen )
            event( stolen, "theft", thief, victim )
            item.event_ward( thief, victim )
            if(thief.query_property("player") &&
            query_ip_number(thief) == query_ip_number(victim) &&
            sizeof(PLAYER_MULTIPLAYER_HANDLER.check_allowed(thief, ({victim})))) {
            sh = capitalize(thief.query_name())+ " stole " +
            query_multiple_short(stolen) +
            " from " + victim.query_name() + " while logged in from the same IP "
            "address."
            user_event("inform", sh, "multiplayer")
            sh = victim.convert_message(sh)
            log_file("MULTIPLAYERS", ctime(time()) + ": " + sh + "\n")



class Theft_base(MudObject):
