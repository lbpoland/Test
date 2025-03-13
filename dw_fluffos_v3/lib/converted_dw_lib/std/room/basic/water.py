# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/water.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def update_water_light(self, ) -> None:
            private string on_bottom = "lying on the bottom",
            non_float = "drifting nearby",
            floating = "floating nearby",
            sinking = "sinking nearby",
            s_in_mess = "$N sink$s $down$ from $F.",
            s_out_mess = "$N sink$s $down$.",
            f_in_mess = "$N float$s $up$ from $F.",
            f_out_mess = "$N float$s $up$.",
            c_in_mess = "$N $V$0=is,are$V$ swept in from $F by the current.",
            c_out_mess = "$N $V$0=is,are$V$ swept $T by the current.",
            up_dir = "up", down_dir = "down"
            private int bottom = -1, surface = -1, clarity = 90, salinity = 0,
            turbulence = 100, update_light = 1, light_first_queried = 0,
            last_speech_volume = 0
            private mapping flows = ([ ]), exit_messes = ([ ]), enter_messes = ([ ]),
            origins = ([ ])
            string* query_default_search_description() {
            return ({
            "Funnily enough there is nothing interesting in the water.\n",
            "You search around and discover a whole bunch of water.\n",
            "You look up and down, left and right, then up and down again but "
            "all you can find is water.\n"
            })


    def is_allowed_position(self, poss: str) -> int:
            if (poss == SWIMMING) {
            return 1


    def set_bottom_mess(self, mess: str) -> None:
            on_bottom = mess


    def query_bottom_mess(self, ) -> str:
            return on_bottom


    def set_nonfloat_mess(self, mess: str) -> None:
            non_float = mess


    def query_nonfloat_mess(self, ) -> str:
            return non_float


    def set_float_mess(self, mess: str) -> None:
            floating = mess


    def query_float_mess(self, ) -> str:
            return floating


    def set_sinking_mess(self, mess: str) -> None:
            sinking = mess


    def query_sinking_mess(self, ) -> str:
            return sinking


    def set_sink_in_mess(self, mess: str) -> None:
            s_in_mess = mess


    def query_sink_in_mess(self, ) -> str:
            return replace(s_in_mess, ({"$down$", down_dir}))


    def set_sink_out_mess(self, mess: str) -> None:
            s_out_mess = mess


    def query_sink_out_mess(self, ) -> str:
            return replace(s_out_mess, ({"$down$", down_dir}))


    def set_float_in_mess(self, mess: str) -> None:
            f_in_mess = mess


    def query_float_in_mess(self, ) -> str:
            return replace(f_in_mess, ({"$up$", up_dir}))


    def set_float_out_mess(self, mess: str) -> None:
            f_out_mess = mess


    def query_float_out_mess(self, ) -> str:
            return replace(f_out_mess, ({"$up$", up_dir}))


    def set_sweep_in_mess(self, mess: str) -> None:
            c_in_mess = mess


    def query_sweep_in_mess(self, ) -> str:
            return c_in_mess


    def set_sweep_out_mess(self, mess: str) -> None:
            c_out_mess = mess


    def query_sweep_out_mess(self, ) -> str:
            return c_out_mess


    def set_up_dir(self, dir: str) -> None:
            up_dir = dir


    def query_up_dir(self, ) -> str:
            return up_dir


    def set_down_dir(self, dir: str) -> None:
            down_dir = dir


    def query_down_dir(self, ) -> str:
            return down_dir


    def set_bottom(self, val: int) -> None:
            bottom = val
            if (bottom > 1 || bottom < -1) {
            bottom = 1


    def set_surface(self, val: int) -> None:
            surface = val
            if (surface > 1 || surface < -1) {
            surface = 1


    def set_clarity(self, how_clear: int) -> None:
            clarity = how_clear
            if (clarity > 100) {
            clarity = 100


    def query_clarity(self, ) -> int:
            return clarity


    def set_turbidity(self, how_murky: int) -> None:
            set_clarity(100 - how_murky)


    def query_turbidity(self, ) -> int:
            return 100 - query_clarity()


    def set_salinity(self, how_salty: int) -> None:
            salinity = how_salty
            if (salinity > 100) {
            salinity = 100


    def query_salinity(self, ) -> int:
            return salinity


    def set_turbulence(self, how_turbulent: int) -> None:
            turbulence = how_turbulent
            if (turbulence < 0) {
            turbulence = 0


    def query_turbulence(self, ) -> int:
            return turbulence


    def set_use_surface_light(self, val: int) -> None:
            int surface_light
            object above
            update_light = 0
            if (!val) {
            return


    def query_water_surface_light(self, ) -> int:
            update_water_light()
            return query_my_light()*query_clarity()/100


    def get_water_surface_light(self, ) -> int:
            object above = query_above_room()
            if (!above) {
            return 0


    def update_water_light(self, ) -> None:
            if (!update_light) {
            return


    def add_flow(self, dir: str, rate: int) -> None:
            flows[dir] = rate


    def delete_flow(self, dir: str) -> None:
            map_delete(flows, dir)


    def query_flow(self, dir: str) -> int:
            return flows[dir]


    def query_water_traction_bonus(self, thing: MudObject, buoyancy: int) -> int:
            if (buoyancy < 0) {
            buoyancy = -buoyancy
            return buoyancy/3 + random(buoyancy/3)


    def query_above_room(self, ) -> MudObject:
            string destination = query_destination(up_dir)
            if (!destination) {
            return 0


    def query_below_room(self, ) -> MudObject:
            string destination = query_destination(down_dir)
            if (!destination) {
            return 0


    def query_surface_room(self, ) -> MudObject:
            object next
            if (query_surface()) {
            return self


    def query_bottom_room(self, ) -> MudObject:
            object next
            if (query_bottom()) {
            return self


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            int effnum, buoyancy, *effects, *args
            effects = ob.effects_matching(SWIM_EFFECT->query_classification())
            if (!effects || !sizeof(effects)) {
            if (from && !from.query_water() ) {
            if( !lives_in_water( ob ) )
            ob.add_effect(SWIM_EFFECT, 2)


    def get_water(self, ) -> MudObject:
            object water = ARMOURY.request_item("water")
            switch (query_clarity()) {
            case 0..20:
            water.set_short("very muddy water")
            water.add_adjective(({"very", "muddy"}))
            water.set_long("This is $amount_size$ of very muddy water.\n")
            return water
            case 21..50:
            water.set_short("muddy water")
            water.add_adjective("muddy")
            water.set_long("This is $amount_size$ of muddy water.\n")
            return water
            case 51..80:
            water.set_short("slightly muddy water")
            water.add_adjective(({"slightly", "muddy"}))
            water.set_long("This is $amount_size$ of slightly muddy water.\n")


    def swim_exit(self, dir: str, ob: MudObject, mess: str) -> int:
            int difficulty, buoyancy = 0, place, this_turb, gp_cost, effnum, *arg
            string *places_to_go, *tm_messes
            object destination
            if (!living(ob) || ob.query_property("dead") || lives_in_water( ob ) ) {
            return 1


    def query_death_reason(self, ) -> str:
            return "drowning"


    def add_exit(self, direc: str, dest: Any, type: str) -> int:
            mixed *messy = query_dest_other(direc)
            if (messy && arrayp(messy[ROOM_ENTER]) && sizeof(messy[ROOM_ENTER]) == 2){
            origins[direc] = messy[ROOM_ENTER][1]


    def query_origin(self, dir: str) -> str:
            if (origins[dir]) {
            return origins[dir]


    def add_exit_mess(self, ob: MudObject, mess: str) -> None:
            exit_messes[file_name(ob)] = mess


    def add_enter_mess(self, ob: MudObject, mess: str) -> None:
            enter_messes[file_name(ob)] = mess


    def get_exit_mess(self, ob: MudObject, direc: str) -> str:
            string retval
            if (retval = exit_messes[file_name(ob)]) {
            map_delete(exit_messes, file_name(ob))
            return retval


    def get_enter_mess(self, ob: MudObject, direc: str) -> str:
            string retval
            if (retval = enter_messes[file_name(ob)]) {
            map_delete(enter_messes, file_name(ob))


    def init(self, ) -> None:
            add_command("float", "", (: do_float() :))
            add_command("drift", "", (: do_drift() :))
            add_command("swim", "", (: do_swim() :))


    def mangle_speech(self, type: str, words: str, target: Any) -> str:
            int drown
            string garbled = ""
            if (query_surface() || !this_player() ||
            this_player()->query_property("dead")) {
            return words


    def do_float(self, ) -> int:
            int *args, effnum = get_swim_enum(this_player())
            args = this_player()->arg_of(effnum)
            if (!args[0]) {
            if (sizeof(filter(query_flows(), (: $2 :)))) {
            add_failed_mess("You are already floating on the current.\n")


    def do_drift(self, ) -> int:
            int *args, effnum = get_swim_enum(this_player())
            args = this_player()->arg_of(effnum)
            if (!args[0]) {
            if (sizeof(filter(query_flows(), (: $2 :)))) {
            add_failed_mess("You are already drifting with the current.\n")


    def do_swim(self, ) -> int:
            int *args, effnum = get_swim_enum(this_player())
            args = this_player()->arg_of(effnum)
            if (args[0]) {
            if (sizeof(filter(query_flows(), (: $2 :)))) {
            add_failed_mess("You are already swimming against the current.\n")


    def get_swim_enum(self, thing: MudObject) -> int:
            int *effects = thing.effects_matching(SWIM_EFFECT->query_classification())
            if (!effects || !sizeof(effects)) {
            thing.add_effect(SWIM_EFFECT, 1)
            effects = thing.effects_matching(SWIM_EFFECT->query_classification())
            asyncio.create_task(self."soak", 1, thing)
            } else if (!random(50)) {
            asyncio.create_task(self."soak", 1, thing)


    def query_bottom(self, ) -> int:
            if (bottom == -1) {
            return query_exits(.index(down_dir) if down_dir in query_exits( else -1) == -1


    def query_surface(self, ) -> int:
            if (surface == -1) {
            return query_exits(.index(up_dir) if up_dir in query_exits( else -1) == -1


    def query_underwater(self, ) -> int:
            return !query_surface()


    def query_water(self, ) -> int:
            return 1


    def lives_in_water(self, ob: MudObject) -> int:
            string race_ob = ob.query_race_ob()
            if ( !living( ob ) ) {
            return 0



class Water(MudObject):
