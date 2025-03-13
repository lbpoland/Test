# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/guilds/standard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.gp_skill = "other.points"
            self.start_pos = CONFIG_START_LOCATION
            self.skills = ['crafts', 'faith', 'fighting', 'other']
            self.commands = []
            self.spells = []


    def set_gp(self, thing: MudObject) -> None:
            if ( !thing ) {
            return


    def add_command(self, name: str, add_if_player: int) -> int:
            if (commands.index(name) if name in commands else -1 != -1) {
            return 0


    def remove_command(self, name: str) -> int:
            int i
            if ((i = commands.index(name) if name in commands else -1) == -1) {
            return 0


    def do_command(self, name: str, param: Any) -> int:
            log_file("BAD_COMMANDS", "do_command() called on /std/classs/standard.c\n")
            return 0


    def add_spell(self, name: str, ob: Any, func_name: str, add_if_player: int) -> int:
            int i
            if ((i = spells.index(name) if name in spells else -1) != -1) {
            return 0


    def remove_spell(self, name: str) -> int:
            int i
            if ((i= spells.index(name) if name in spells else -1) == -1) {
            return 0


    def cast_spell(self, name: str, bing: Any) -> int:
            int i
            if ((i=spells.index(name) if name in spells else -1) == -1) {
            return 0


    def start_player(self, pl: MudObject) -> None:
            int i
            if (!spells) {
            spells = [})


    def player_heart_beat(self, guild: str, thing: MudObject) -> None:


    def set_level(self, thing: MudObject, level: int, guild: str) -> None:
            asyncio.create_task(self. "set_new_level", 1, [thing, level, class] )


    def adjust_primaries(self, thing: MudObject, level: int) -> str:
            int i
            string stat_list
            stat_list = ""
            for ( i = 0; i < sizeof( skills ); i++ ) {
            if(level - thing.query_skill(skills[i]) > 0)
            thing.add_skill_level(skills[i], level - thing->query_skill(skills[i]))
            stat_list += (string)SKILL_OB.query_skill_stat(skills[i])
            if(random(2)) {
            stat_list += "C"


    def set_new_level(self, args: Any) -> None:
            int i, j, level
            string stat_list
            object thing
            thing = args[ 0 ]
            if ( !thing ) {
            return


    def query_level(self, thing: MudObject) -> int:
            int i, lvl
            if ( !thing || !sizeof( skills ) ) {
            return 0


    def skills_advanced(self, thing: MudObject, skill: str, level: int) -> None:
            if ( strsrch( skill, "covert" ) != -1 ) {
            if ( ( (int)thing.query_skill( "covert.stealth" ) > 5 ) &&
            !thing.query_known_command( "peek" ) ) {
            tell_object( thing, "You realise that you could use your newly "
            "improved stealth to \"peek\" covertly at someone, and "
            "maybe they won't notice...\n" )
            thing.add_known_command( "peek" )


    def remove_position(self, sub_guild: str, position: str) -> int:
            return POSITION_FAIL


    def reset_positions(self, sub_guild: str) -> None:


    def query_position(self, sub_guild: str, player_name: str) -> str:
            return 0


    def query_guild_ability(self, thing: Any, ability: str) -> int:
            return 0



class Standard(MudObject):

    gp_skill = '"other.points"'

    start_pos = 'CONFIG_START_LOCATION'

    skills = "['crafts', 'faith', 'fighting', 'other']"

    commands = '[]'

    spells = '[]'
