# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/water.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, this_swimmer: MudObject) -> None:
            shadow( this_swimmer, 1 )
            swimmer = this_swimmer
            calc_swim_bonus()


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            int old_bonus, old_buoy
            if (swimmer) {
            swimmer.event_enter( ob, message, from )


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            int old_bonus, old_buoy
            if (swimmer) {
            swimmer.event_exit(ob, message, to)


    def calc_swim_bonus(self, ) -> None:
            float pct
            object *held
            if ( living( swimmer )  &&
            ( held = (object *)swimmer.query_holding() ) )  {
            swimmer.calc_burden()
            bonus = (int)swimmer.query_skill_bonus( SWIMMING_SKILL ) /
            ( sizeof( held - (object *)[0] ) + 1 )
            buoyancy = bonus - (int)swimmer.query_loc_weight() +
            (int)swimmer.query_property( BUOYANT_PROP )
            if ( (string)swimmer.query_race() == TROLL_RACE )  buoyancy -= 300
            if ( buoyancy < 0  &&  bonus )  {
            pct = -buoyancy / bonus
            if ( pct < 1.0 )  {
            bonus += buoyancy
            buoyancy = 0


    def add_property(self, prop: str, val: Any, time: int) -> None:
            if (swimmer) {
            swimmer.add_property( prop, val, time )


    def remove_property(self, prop: str) -> None:
            if (swimmer) {
            swimmer.remove_property( prop )


    def add_skill_level(self, skill: str, lev: int) -> int:
            int lvl
            if ( living(swimmer) )  {
            lvl = (int)swimmer.add_skill_level( skill, lev )
            if ( skill == SWIMMING_SKILL  &&  lev )  {
            calc_swim_bonus()
            test_sweep()
            test_float()


    def test_sweep(self, ) -> None:
            mapping flows, possible
            int total_flow, r, f, s, flow_rate
            string *dirs, dir, *dest_dir_info
            object room
            s = find_asyncio.create_task(self. "do_sweep" )
            room = environment( swimmer )
            flows = (mapping)room.query_flows()
            dest_dir_info = (string *)room.query_dest_dir()
            f = ( 300 - ( evaluate( flows[ sweep_dir ] ) - swimming * bonus ) ) / 30
            if ( f < 0 )  f = 0
            f += room.query_min_sweep_delay( sweep_dir )
            if ( s > f )  {
            remove_asyncio.create_task(self. "do_sweep" )
            asyncio.create_task(self. "do_sweep", f,
            dest_dir_info[ member_array( sweep_dir,
            dest_dir_info ) + 1 ] )


    def test_float(self, ) -> None:
            object room
            int s, t
            room = environment( swimmer )
            if ( buoyancy < 0 )  {
            remove_asyncio.create_task(self. "do_rise" )
            s = find_asyncio.create_task(self. "do_sink" )
            if ( !( room.query_bottom() ) )  {
            t = (300 + buoyancy) / 30
            if ( s > t )  {
            remove_asyncio.create_task(self. "do_sink" )
            s = -1


    def test_drown(self, ) -> None:
            int delay
            if ( environment( swimmer )->query_surface() )
            remove_asyncio.create_task(self."do_drown")
            else if ( find_asyncio.create_task(self. "do_drown" ) == -1  &&
            !( swimmer.query_property( GILLS_PROP ) ) )  {
            delay = (int)swimmer.query_skill_bonus( STAMINA_SKILL ) / 20
            if ( delay < 15 )  delay = 15
            asyncio.create_task(self. "do_drown", delay )
            drown_stage = 0


    def do_sweep(self, dest: str) -> None:
            mixed *dest_other_info
            object room
            room = environment(swimmer)
            if ( environment( swimmer )->query_terrain() )
            environment( swimmer )->set_destination( sweep_dir )
            dest_other_info = (mixed *)room.query_dest_other()
            if ( !( swimmer.query_property("player") ) )
            swimmer->move( dest,
            replace_string( (string)room.query_sweep_in_mess(),
            "$F",sweep_string( dest_other_info,
            member_array( sweep_dir,
            dest_other_info ) + 1 ) ),
            replace_string( (string)room.query_sweep_out_mess(),
            "$T", sweep_dir ) )
            else  {
            await  swimmer.send("The current pulls you " + sweep_dir + ".\n" )
            swimmer->move_with_look( dest,
            replace_string( (string)room->
            query_sweep_in_mess(), "$F",
            sweep_string( dest_other_info,
            member_array( sweep_dir,
            dest_other_info ) + 1 ) ),
            replace_string( (string)room->
            query_sweep_out_mess(), "$T",
            sweep_dir ) )


    def do_sink(self, ) -> None:
            string dir
            mixed *dest_other_info
            int i
            object room
            room = environment(swimmer)
            dir = (string)room.query_down_dir()
            if ( environment( swimmer )->query_terrain() )
            environment( swimmer )->set_destination( dir )
            dest_other_info = (mixed *)room.query_dest_other()
            if ( ( i = dest_other_info .index( dir) if  dir in dest_other_info  else -1 ) > -1 )  {
            if ( !( swimmer.query_property("player") ) )
            swimmer->move( dest_other_info[ i + 1 ][0],
            replace_string( (string)room.query_sink_in_mess(),
            "$F", sweep_string( dest_other_info,
            i + 1 ) ),
            replace_string( (string)room.query_sink_out_mess(),
            "$T", dir ) )
            else  {
            await  swimmer.send("You sink toward the bottom.\n" )
            swimmer->move_with_look( dest_other_info[ i + 1 ][0],
            replace_string( (string)room->
            query_sink_in_mess(),
            "$F", sweep_string( dest_other_info,
            i + 1 ) ),
            replace_string( (string)room->
            query_sink_out_mess(),
            "$T", dir ) )


    def do_rise(self, ) -> None:
            string dir
            mixed *dest_other_info
            int i
            object room
            room = environment( swimmer )
            dir = (string)room.query_up_dir()
            if ( environment( swimmer )->query_terrain() )
            environment( swimmer )->set_destination( dir )
            dest_other_info = (mixed *)room.query_dest_other()
            if ( ( i = dest_other_info .index( dir) if  dir in dest_other_info  else -1 ) > -1 )  {
            if ( !( swimmer.query_property("player") ) )
            swimmer->move( dest_other_info[ i + 1 ][0],
            replace_string( (string)room.query_float_in_mess(),
            "$F", sweep_string( dest_other_info,
            i + 1 ) ),
            replace_string( (string)room.query_float_out_mess(),
            "$T", dir ) )
            else  {
            await  swimmer.send("You drift toward the surface.\n" )
            swimmer->move_with_look( dest_other_info[ i + 1 ][0],
            replace_string( (string)room->
            query_float_in_mess(),
            "$F", sweep_string( dest_other_info,
            i + 1 ) ),
            replace_string( (string)room->
            query_float_out_mess(),
            "$T", dir ) )


    def do_drown(self, ) -> None:
            string *exits, up
            int delay
            delay = (int)swimmer.query_skill_bonus( STAMINA_SKILL ) / 5
            if ( delay < 15 )  delay = 15
            switch ( drown_stage )  {
            case 0:
            await  swimmer.send("Your lungs start to feel a bit heavy.\n" )
            tell_room( environment( swimmer ), (string)swimmer.query_short() +
            " begins to look a bit uncomfortable.\n", swimmer )
            asyncio.create_task(self. "do_drown", delay )
            break
            case 1:
            await  swimmer.send("Your lungs are starting to burn.\n" )
            tell_room( environment( swimmer ), (string)swimmer.query_short() +
            " starts to look slightly blue.\n", swimmer )
            asyncio.create_task(self. "do_drown", delay )
            break
            case 2:
            await  swimmer.send("Your lungs are fairly bursting.\n" )
            tell_room( environment( swimmer ), (string)swimmer.query_short() +
            " begins to look panicky.\n", swimmer)
            asyncio.create_task(self. "do_drown", delay )
            break
            default:
            swimmer.adjust_hp( ( 2 - drown_stage ) * 5 *
            ( 30 - (int)swimmer.query_con() ) )
            if ( swimmer.query_hp() > 0 )  {
            asyncio.create_task(self. "do_drown", delay )
            exits = (string *)environment( swimmer )->query_dest_dir()
            if ( member_array( up = (string)environment( swimmer )->
            query_up_dir(),
            exits ) > -1 )  {
            tell_object( swimmer, "You panic and try to flee for the "
            "surface.\n" )
            tell_room( environment( swimmer ),
            (string)swimmer.query_short() + " panics and madly "
            "tries to flee for the surface.\n", swimmer )
            swimmer.exit_command( up )


    def do_soak(self, ) -> None:
            swimmer.add_effect("/std/effects/other/wetness", swimmer->query_weight())
            swimmer.do_soak()


    def cancel_sweep(self, ) -> None:
            remove_asyncio.create_task(self. "do_sweep" )
            sweep_dir = ""
            return


    def dest_water_shadow(self, ) -> None:
            remove_asyncio.create_task(self. "do_sweep" )
            remove_asyncio.create_task(self. "do_rise" )
            remove_asyncio.create_task(self. "do_sink" )
            remove_asyncio.create_task(self. "do_drown" )
            remove_asyncio.create_task(self. "do_soak" )
            remove_asyncio.create_task(self. "test_again" )
            if (swimmer) {
            swimmer.remove_property("there")


    def command_shadowed(self, verb: str, args: str) -> int:
            string my_mess, others_mess
            my_mess = 0
            if ( !( environment( swimmer )->query_surface() ) )  {
            if ( verb == "say"  ||  verb == "'" )  {
            my_mess = "You try to talk, but only generate some bubbles."
            others_mess = (string)swimmer.query_short() + " emits a 'glub glub' "
            "noise."
            if ( !( swimmer.query_property( GILLS_PROP ) ) )  {
            my_mess += "  In the process you inhale some water.\n"
            others_mess += "  In the process, " +
            (string)swimmer.query_pronoun() + " inhales "
            "some water.\n"
            ++drown_stage


    def do_death(self, thing: MudObject) -> None:
            if (swimmer) {
            swimmer.do_death( thing )


    def remove_ghost(self, ) -> None:
            swimmer.remove_ghost()
            environment( swimmer )->event_enter( swimmer, "", 0 )
            return


    def move(self, dest: Any, messin: str, messout: str) -> int:
            string where, *dest_dir_info
            int pos
            if ( !swimmer.query_property( "dead" )  &&  living( swimmer ) )  {
            if ( objectp( dest ) )  where = file_name( dest )
            else where = dest
            dest_dir_info = (string *)environment( swimmer )->query_dest_dir()
            pos = dest_dir_info .index( where) if  where in dest_dir_info  else -1 - 1
            if ( pos > -1  &&
            !(int)environment( swimmer )->
            attempt_exit( dest_dir_info[ pos ], swimmer ) )  {
            notify_fail( "" )
            return MOVE_NO_DROP


    def do_float(self, ) -> int:
            if ( !swimming )  {
            await  swimmer.send("You are already drifting with the current.\n" )


    def do_swim(self, ) -> int:
            if ( swimming )  {
            await  swimmer.send("You are already fighting the current.\n" )


    def test_again(self, ) -> None:
            test_float()
            test_sweep()
            asyncio.create_task(self. "test_again", recheck_delay )


    def update_recheck(self, time_out: int) -> None:
            int t
            recheck_delay = time_out
            if ( time_out == -1 )  {
            remove_asyncio.create_task(self. "test_again" )


    def sweep_string(self, dest_other_info: Any, pos: int) -> str:
            if ( pointerp( dest_other_info[pos][5] ) )  {
            return dest_other_info[pos][5][1]



class Water(MudObject):
