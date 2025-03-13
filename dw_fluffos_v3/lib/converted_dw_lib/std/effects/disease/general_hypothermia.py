# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/general_hypothermia.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, temperature: int, id: int) -> int:
            if(temperature + calc_personal_temp(player) < COMFORTABLE) {
            await player.send("You feel a bit chilly.\n")
            player.submit_ee( "shiver", [20, 20], EE_CONTINUOUS )
            player.submit_ee( "stat_adjusts", [240, 240], EE_CONTINUOUS )
            player.add_extra_look( self )
            } else {
            player.submit_ee(0, 0, EE_REMOVE )


    def restart(self, player: MudObject) -> None:
            player.add_extra_look( self )


    def end(self, player: MudObject) -> None:
            await  player.send("You don't feel cold anymore.\n" )
            player.remove_extra_look( self )


    def shiver(self, player: MudObject, temperature: int, id: int) -> None:
            int *enums, pwet, personal
            int room_temp, min
            if (!environment(player))
            return
            room_temp = WEATHER.temperature_index(environment(player))
            personal = calc_personal_temp(player)
            if(room_temp + personal > COMFORTABLE)
            temperature += (room_temp + personal - COMFORTABLE)
            min = 100 * (personal + room_temp - COMFORTABLE)
            if(min > COMFORTABLE)
            min = personal + room_temp - COMFORTABLE
            if(temperature < min)
            temperature = min
            if(temperature >= COMFORTABLE)
            player.submit_ee(0, 0, EE_REMOVE )
            if ( temperature < DEATH ) {
            player.dest_hide_shadow()
            await  player.send("The cold is just too much for you.\n" )
            tell_room( environment( player ), "Frost riming "+
            (string)player.query_possessive() +" skin in a thick crust, "+
            (string)player.the_short() +" expires.\n", player )
            player.do_death()
            return


    def calc_personal_temp(self, player: MudObject) -> int:
            object where
            string item, zone, type, *types, *zones
            int count
            zones = [})
            where = environment(player)
            count = 0
            if(where.query_property("location") == "inside")
            count += 20
            count += where.query_property("warmth")
            foreach(item in player.query_wearing()) {
            types = item.query_type()
            if(!arrayp(types))
            types = [item.query_type()]
            foreach(type in types) {
            foreach(zone in CLOTHING_HANDLER.query_zone_names(type)) {
            if(zones.index(zone) if zone in zones else -1 == -1)
            zones += [zone]
            if(item.query_property("warmth"))
            count += item.query_property("warmth")
            else
            count ++


    def stat_adjusts(self, player: MudObject, temperature: int, id: int) -> None:
            if(WEATHER.temperature_index(environment(player)) > 0 ||
            temperature > -100)
            return
            switch(player.query_race()) {
            case "troll":
            tell_object( player, "You feel a tingling between your ears and "+
            "new and strangely clever thoughts race along the "+
            "superconducting neural pathways of your brain.\n" )
            player.adjust_int( 1 )
            break
            default:
            tell_object( player, "You feel your strength being drained by the "+
            "freezing temperatures.\n" )
            player.adjust_tmp_str( -1 )
            player.adjust_tmp_con( -1 )
            break


    def extra_look(self, player: MudObject) -> str:
            string desc
            int temperature
            int *enums
            enums = (int *)player.effects_matching( "disease.hypothermia" )
            if ( !sizeof( enums ) )
            return ""
            temperature = (int)player.arg_of(enums[0])
            switch(temperature/5) {
            case -5 .. 100 :
            desc = "looks a bit cold.\n"
            break
            case -10 .. -6 :
            desc = "looks rather cold.\n"
            break
            case -30 .. -11 :
            desc = "looks very cold.\n"
            break
            case -80 .. -31 :
            desc = "appears to be suffering from extreme hypothermia.\n"
            break
            case -100 .. -81 :
            desc = "looks close to death from hypothermia.\n"
            break
            default :
            return ""



class General_hypothermia(MudObject):
