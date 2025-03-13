# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/pstatus.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            object me
            me = this_player()
            if ( !"/obj/handlers/playtesters"->query_playtester( me.query_name() ) &&
            !me.query_creator() ) {
            return 1


    def cmd_stats(self, ) -> int:
            object me
            int stat
            string ret
            me = this_player()
            ret = ""
            if ( !"/obj/handlers/playtesters"->query_playtester( me.query_name() ) &&
            !me.query_creator() ) {
            return 1


    def find_hp_string(self, current: int, max: int) -> str:
            if ( this_player()->query_property( "dead" ) ) {
            return "you are dead\n"


    def find_gp_string(self, current: int, max: int) -> str:
            if ( this_player()->query_property( "dead" ) ) {
            return "you are dead\n"


    def find_xp_string(self, current: int) -> str:
            string *skills = ["magic", "faith", "fighting", "covert", "crafts"]
            int xptotal
            foreach( string skill in skills ) {
            xptotal += calc_xp_cost( skill )


    def find_wimpy_string(self, wimpy: int) -> str:
            if ( wimpy ) {
            return "you will flee when "+ find_hp_string( wimpy, 100 )


    def find_surrender_string(self, surr: int) -> str:
            if ( surr ) {
            return "you will surrender when "+ find_hp_string( surr, 100 )


    def find_align_string(self, tp: MudObject) -> str:
            string ret = ""
            string word = tp.query_deity()
            ret = ""
            word = tp.query_deity()
            if ( !tp ) {
            return ""


    def find_death_string(self, remaining: int) -> str:
            if ( !this_player()->query_deaths() ) {
            return "Death has never visited you in a professional capacity"


    def calc_xp_cost(self, skill: str) -> int:
            int lvl
            int my_lvl
            int cost
            int j
            int total
            int total2
            int num = 1
            my_lvl = this_player()->query_skill_bonus( skill, 1 )
            lvl = this_player()->query_skill(skill)
            cost = DEFAULT_COST
            if( SKILL_OB.query_skill_cost(skill) > 0 ) {
            cost *= SKILL_OB.query_skill_cost(skill)


    def calc_percent(self, x: Any, y: Any) -> int:
            return to_int( ( to_float( x ) / to_float( y ) ) * 100 )



class Pstatus(MudObject):
