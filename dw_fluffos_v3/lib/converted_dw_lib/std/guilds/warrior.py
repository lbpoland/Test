# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/guilds/warrior.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("warriors")
            set_short("Warriors' Guild")
            set_long("The Warriors' Guild.\n\n"
            "The Warriors' Guild is for the brave and "
            "heroic.  As a member you can expect to "
            "recieve a sound background in beating, "
            "bashing, slicing, and dicing a variety of "
            "opponents up with a wide selection of "
            "weapons.  The evaluation of arms and armour "
            "will also be covered in detail.  Join this "
            "class if you wish to journey to interesting "
            "places, meet interesting people, and give "
            "them a sound thrashing.\n")
            set_gp_skill("fighting.points")
            set_start_pos("/d/dist/pumpkin/squash/squash5")
            set_skills([ "fighting.points",
            "fighting.combat.melee.sharp",
            "fighting.combat.melee.pierce",
            "fighting.combat.melee.blunt",
            "fighting.combat.melee.unarmed",
            "fighting.combat.range.thrown",
            "fighting.combat.range.fired",
            "fighting.combat.parry.melee",
            "fighting.combat.parry.range",
            "fighting.combat.dodging.melee",
            "fighting.combat.dodging.range",
            "fighting.combat.special.weapon",
            "fighting.combat.special.unarmed",
            "other.evaluating.weapons",
            "other.evaluating.armour" ])


    def query_skill_cost(self, skill: str) -> int:
            string *bits
            if(skills.index(skill) if skill in skills else -1 != -1)
            return 3
            bits = explode(skill, ".")
            switch(bits[0]) {
            case "faith" :
            return 15
            case "fighting" :
            return 5
            case "magic" :
            return 50
            default :
            return 10


    def query_skill_max_level(self, skill: str) -> int:
            string *bits
            if(skills.index(skill) if skill in skills else -1 != -1)
            return 300
            bits = explode(skill, ".")
            switch (bits[0]) {
            case "faith" :
            return 25
            case "fighting" :
            return 50
            case "magic" :
            return 5
            case "other" :
            return 25
            default :
            return 10


    def query_title(self, player: MudObject) -> str:
            int lvl, female
            female = (int)player.query_gender() == 2
            lvl = query_level( player )
            switch( lvl ) {
            case 0..15: return "the Novice Fighter"
            case 16..30: return "the Apprentice Fighter"
            case 31..45: return "the Skillful Fighter"
            default: return "the Grave of All Hope"


    def query_warrior(self, player: str) -> int:
            if( PLAYER_HANDLER.test_class( player ) == "/std/classs/warrior" ) {
            return 1


    def query_warrior_ob(self, player: MudObject) -> int:
            if( player.query_class_ob() == "/std/classs/warrior" ) {
            return 1



class Warrior(MudObject):
