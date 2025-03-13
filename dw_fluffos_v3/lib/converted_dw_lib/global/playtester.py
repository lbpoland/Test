# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/playtester.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_pt_area(self, ob: MudObject) -> int:
            string *file
            if (strsrch (base_name (ob), "_pt") != -1) {
            return 1


    def __init__(self):
            self._pt_data = new(class playtester_data)


    def move_player_to_start(self, bong: str, new_pl: int, c_name: str, ident: str, go_invis: int) -> None:
            if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
            !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
            return 0
            #ifndef NEW_DRIVER
            #endif
            ::move_player_to_start(bong, new_pl, c_name, ident, go_invis)
            AddSearchPath([DIR_PLAYTESTER_CMDS])
            if (PLAYTESTER_HAND.query_senior_playtester(query_name())) {
            AddSearchPath([DIR_SENIOR_PLAYTESTER_CMDS])


    def query_object_type(self, object) -> str:
            if (PLAYTESTER_HAND.query_pt_exec(query_name())) {
            return "E"


    def query_pt_protection(self, ) -> int:
            if (_pt_data->room_protection) {
            return 2


    def enable_pt_protection(self, ) -> int:
            if (_pt_data->room_protection != 1) {
            log_file (PROTECTION_LOG, "%s: %s had room PT "
            "protection enabled by %s.\n", ctime(time()), this_player()->query_name(),
            base_name (environment (this_player())))
            tell_object (this_player(), "%^BOLD%^You have had your playtester "
            "protection enabled by an external source.  It will last until switched "
            "off by another external source.\n%^RESET%^")
            _pt_data->room_protection = 1
            return 1


    def disable_pt_protection(self, ) -> int:
            if (_pt_data->room_protection == 1) {
            log_file (PROTECTION_LOG, "%s: %s had room PT "
            "protection disabled by %s.\n", ctime(time()), this_player()->query_name(),
            base_name (environment (this_player())))
            tell_object (this_player(), "%^BOLD%^The playtester protection enabled "
            "by an external source has been switched off.\n%^RESET%^")
            _pt_data->room_protection = 0
            return 1


    def enable_personal_pt_protection(self, ) -> int:
            if (query_pt_protection()) {
            return 0


    def disable_personal_pt_protection(self, ) -> int:
            if (query_pt_protection() != 1) {
            return 0


    def pt_set_hp(self, hp: int) -> None:
            _pt_data->hp = hp


    def pt_query_hp(self, ) -> int:
            return _pt_data->hp


    def pt_make_corpse(self, ) -> MudObject:
            object corpse
            corpse = clone_object( "/obj/corpse" )
            corpse.set_owner( 0, self )
            corpse.set_ownership( query_name() )
            corpse.set_race_name( query_race() )
            if ( !query_race_ob() ) {
            corpse.set_race_ob( "/std/races/unknown" )
            } else {
            corpse.set_race_ob( query_race_ob() )


    def pt_do_death(self, ) -> MudObject:
            object corpse, flowers
            DEATH.death_informer( self, 0, _pt_data->log_file, 1 )
            tell_object( self,
            "The Death of Playtesters sneaks up behind you and taps "
            "you on the shoulder.\n"
            "%^CYAN%^The Death of Playtesters says: MY, WE'VE BEEN A BIT "
            "CARELESS, HAVEN'T WE?%^RESET%^\n"
            "The Death of Playtesters coughs.\n"
            "%^CYAN%^The Death of Playtesters says: Sorry about the Voice.  "
            "We have to do that, you know.  Well, you should really be dead "
            "now, but the Playtesters' Union renegotiated the whole death deal "
            "with the powers that be.%^RESET%^\n" )
            call_out ("pt_set_hp", 0, query_max_hp())
            corpse = pt_make_corpse()
            corpse.move( environment( ) )
            flowers = clone_object( "/std/object" )
            flowers.set_name( "flowers" )
            flowers.set_short( "bunch of flowers" )
            flowers.add_alias( "bunch" )
            flowers.add_adjective( ["bunch", "of"] )
            flowers.set_main_plural( "bunches of flowers" )
            flowers.add_plural( ["bunches", "bunches of flowers"] )
            flowers.set_long( "This is a small bunch of nice flowers.\n" )
            flowers.set_weight( 5 + random( 10 ) )
            flowers.set_value( 0 )
            flowers.set_read_mess( "Rest In Peas", "common" )
            flowers.move( corpse )
            return corpse


    def set_pt_log_file(self, str: str) -> None:
            _pt_data->log_file = str


    def query_pt_log_file(self, ) -> str:
            return _pt_data->log_file


    def enable_death_log(self, ) -> None:
            _pt_data->log_death = 1


    def disable_death_log(self, ) -> None:
            _pt_data->log_death = 0


    def query_log_death(self, ) -> int:
            return _pt_data->log_death


    def enable_damage_log(self, ) -> None:
            _pt_data->log_damage = 1


    def disable_damage_log(self, ) -> None:
            _pt_data->log_damage = 0


    def query_log_damage(self, ) -> int:
            return _pt_data->log_damage


    def do_death(self, thing: MudObject) -> MudObject:
            if( query_pt_protection() || query_in_pt_arena())
            return pt_do_death()
            else
            return ::do_death( thing )


    def query_hp(self, ) -> int:
            if( query_pt_protection() )
            return pt_query_hp()
            else
            return ::query_hp()


    def extra_score(self, ) -> str:
            return ::extra_score() +
            "Your playtester protection is "+
            ( query_pt_protection() ? "on" : "off" ) +".\n"


    def query_in_pt_arena(self, ) -> int:
            if (!environment(self)) {
            return 0


    def advancement_restriction(self, ) -> int:
            if (query_pt_protection()) {
            return 1


    def event_move_object(self, from: Any, to: Any) -> None:
            ::event_move_object (from, to)
            if (query_pt_protection()) {
            if (query_pt_area(from) && !query_pt_area (to)) {
            _pt_data->protection_counter = MAX_COUNTER
            if (_pt_data->turn_off) {
            remove_asyncio.create_task(self._pt_data->turn_off)


    def query_player_killer(self, ) -> int:
            if (query_in_pt_arena()) {
            return 1


    def query_contractable(self, ) -> int:
            return ::query_player_killer()



class Playtester(MudObject):

    _pt_data = 'new(class playtester_data)'
