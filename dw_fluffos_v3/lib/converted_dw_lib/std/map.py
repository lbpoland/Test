# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/map.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._locations = ([ ])


    def extra_look(self, ) -> str:
            return "Marked on the map are " +
            query_multiple_short(_features.query_base_description() +
            keys(_locations)) + "."


    def filter_features(self, feature: str) -> int:
            #ifdef DEBUG
            debug_printf("%s %d %d", feature,
            feature.query_max_range() / TERRAIN_MAP_ONE_MILE,
            _detail / TERRAIN_MAP_ONE_MILE)
            #endif
            return (!feature.query_max_range() ||
            feature.query_max_range() >= _detail)


    def setup_map(self, x1: int, y1: int, x2: int, y2: int, detail: int) -> None:
            _area = [x1, y1, x2, y2]
            _detail = detail
            _features = WORLD_MAP.query_features_in_region(x1, y1, x2, y2)
            _features = filter(_features, "filter_features", self)


    def set_map(self, area: str) -> None:
            int width, height, detail, x1, y1, x2, y2
            switch(area) {
            case "sur":
            width = (TERRAIN_MAP_ONE_MILE * 300)
            height = (TERRAIN_MAP_ONE_MILE * 200)
            x1 = -150575040 - width
            y1 = -2173248 - height
            x2 = -150575040 + width
            y2 = -2173248 + height
            detail = (TERRAIN_MAP_ONE_MILE * 50)
            break
            case "world":
            x1 = TERRAIN_MAP_WORLD_LOW_X / 10
            y1 = TERRAIN_MAP_WORLD_LOW_Y / 10
            x2 = TERRAIN_MAP_WORLD_HIGH_X / 10
            y2 = TERRAIN_MAP_WORLD_HIGH_Y / 10
            detail = (TERRAIN_MAP_ONE_MILE * 200)
            break


    def recalc_coords(self, ) -> None:
            int accuracy
            if(!_co_ords || this_player() != _pl || environment(this_player()) != _env) {
            _pl = this_player()
            _env = environment(_pl)
            _co_ords = _env.query_co_ord()
            accuracy = 500 - _pl.query_skill_bonus("other.direction")
            if(accuracy < 1)
            accuracy = 1
            _fudge = TERRAIN_MAP_ONE_MILE * accuracy
            _co_ords[0] += -(_fudge/2) + random(_fudge)
            _co_ords[1] += -(_fudge/2) + random(_fudge)
            _co_ords[2] += -(_fudge/2) + random(_fudge)


    def do_consult(self, find: str) -> int:
            string feature, *res
            object ob
            mapping direcs
            if(this_player()->check_dark(environment(this_player())->query_light()))
            return notify_fail("Sorry the light levels are not conducive to "
            "reading a map.\n")
            recalc_coords()
            if(_co_ords[0] < _area[0] || _co_ords[1] < _area[1] ||
            _co_ords[0] > _area[2] || _co_ords[1] > _area[3])
            return notify_fail("Sorry, you do not appear to be anywhere on this "
            "map.\n")
            res = [})
            foreach(feature in _features) {
            ob = feature.query_region_ob()
            if(ob) {
            #ifdef DEBUG
            debug_printf("%O max range %d", feature,
            feature.query_max_range()/TERRAIN_MAP_ONE_MILE)
            #endif
            direcs = ob->query_feature_desc_from(_co_ords[0], _co_ords[1],
            _co_ords[2], 1)
            if(direcs) {
            if(find == "" || strsrch(lower_case(feature.query_base_description()),
            lower_case(find)) != -1)
            res += [feature.calc_map_feature_desc(direcs, _fudge)]


    def do_add(self, location: str) -> int:
            if(keys(_locations.index(lower_case(location)) if lower_case(location) in keys(_locations else -1) != -1)
            return notify_fail("A location with the name " + location +
            " already exists on this map.\n")
            _locations[lower_case(location)] = _co_ords
            this_player()->add_succeeded_mess(self, "$N $V a new location "
            "to $D.\n")
            return 1


    def init(self, ) -> None:
            this_player()->add_command("consult", self, "<direct:object>",
            (: do_consult("") :))
            this_player()->add_command("find", self,
            "<string'place'> on <direct:object>",
            (: do_consult($4[0]) :))
            this_player()->add_command("add", self,
            "<string'description'> to <direct:object>",
            (: do_add($4[0]) :))


    def query_static_auto_load(self, ) -> Any:
            if((file_name(self))[0..7] != "/std/map" )
            return 0
            return int_query_static_auto_load()


    def init_static_arg(self, args: Any) -> None:
            if(args["::"])
            ::init_static_arg(args["::"])
            if(args["features"])
            _features = args["features"]
            if(args["detail"])
            _detail = args["detail"]
            if(args["area"])
            _area = args["area"]



class Map(MudObject):

    _locations = '([ ])'
