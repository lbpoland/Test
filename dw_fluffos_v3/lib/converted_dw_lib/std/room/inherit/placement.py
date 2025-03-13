# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/placement.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            if(!this_player() || !interactive(this_player()))
            return
            this_player()->add_command("place", self,
            "<indirect:object'furniture'> so it is <word'verb'> "
            "{"+implode(ABOUT_PREPOSITIONS+HANGING_PREPOSITIONS+WALL_PREPOSITIONS+CORNER_PREPOSITIONS, "|")+"} "
            "the <string:'location'> [wall|corner]")
            this_player()->add_command("place", self,
            "<indirect:object'furniture'> "
            "{"+implode(ABOUT_PREPOSITIONS+HANGING_PREPOSITIONS+WALL_PREPOSITIONS+CORNER_PREPOSITIONS, "|")+"} the <string'location'> [wall|corner]")
            this_player()->add_command("displace", self,
            "<indirect:object'furniture'>")
            this_player()->add_command("place", self,
            "help", (: do_help(0) :))
            this_player()->add_command("place", self,
            "help <indirect:object'furniture'>",
            (: do_help($1[0]) :))


    def set_wall_name(self, direction: str, name: str) -> None:
            int pos
            if (!_wall_names) {
            _wall_names = ([ ])


    def query_wall_name_pos(self, pos: int) -> str:
            if (!_wall_names) {
            _wall_names = ([ ])


    def query_wall_name(self, direction: str) -> str:
            int pos
            pos = get_pos_int(direction)
            return query_wall_name_pos(pos)


    def query_another(self, ob: MudObject) -> str:
            {
            object *obs
            string another
            obs = filter(have_described,
            (: $1.query_plural() == $(ob.query_plural()) :))
            switch(sizeof(obs))
            {
            case 0 :
            another = " a"
            break
            case 1 :
            another = " another"
            break
            default :
            another = " yet another"
            break


    def query_more(self, ob: MudObject) -> str:
            {
            object *obs
            string more
            obs = filter(have_described,
            (: $1.query_plural() == $(ob.query_plural()) :))
            switch(sizeof(obs))
            {
            case 0 :
            more = ""
            break
            default :
            more = " more"
            break


    def clutter_string(self, ob: MudObject) -> str:
            mixed *things
            string cluttered = ""
            if(ob.query_has_surface()) {
            things = ob.find_inv_match("all", ob)
            things = unique_array(things, (: $1.query_plural() :))
            switch(sizeof(things)) {
            case 1 :
            if(sizeof(things[0]) == 1)
            cluttered = " is"
            else
            cluttered = " are"
            cluttered += " " + query_multiple_short(things[0])
            break
            default :
            break


    def query_multiple_furniture_short(self, obs: MudObject) -> str:
            object *party
            mixed *things
            string str
            string *strs
            strs = [})
            things = unique_array(obs, (: $1.query_plural() :))
            foreach(party in things)
            {
            switch(sizeof(party))
            {
            case 0 :
            break
            case 1 :
            str = query_another(party[0])[1..]
            str += " " + party[0]->query_short()
            break
            default :
            str = query_num(sizeof(party))
            str += query_more(party[0])
            str += " " + party[0]->query_plural()
            break


    def is_wall_hanging(self, pos: int) -> int:
            {
            if(orientation)
            {
            if([13, 15, 17, 19].index(pos) if pos in [13, 15, 17, 19] else -1 != -1)
            {
            return 1


    def is_in_centre(self, pos: int) -> int:
            {
            if(pos == 1)
            {
            return 1


    def query_max_space_around(self, pos: int) -> int:
            {
            if(is_in_corner(pos))
            {
            return 2


    def do_help(self, ob: MudObject) -> int:
            string str
            string *bits
            if(ob && !ob.query_furniture())
            return this_player()->add_failed_mess(self,
            "$I is not a piece of furniture.\n",
            [ob])
            str = "The place command requires a furniture object, an optional verb, "
            "a preposition and a location.  "
            if(!ob) {
            str += "Which verbs are available depends on the furniture.  Hanging "
            "furniture can use " + query_multiple_short(HANGING_VERBS) + ".  "
            } else {
            if(ob.query_allowed_room_verbs())
            bits = filter(keys(ob.query_allowed_room_verbs()), (: $1 != "" :))
            switch(sizeof(bits)) {
            case 0:
            str += "The " + ob.the_short() + " has no verbs.\n"
            break
            case 1:
            str += "The verb for " + ob.the_short() + " is " +
            query_multiple_short(bits) + ".\n"
            break
            default:
            str += "The verbs available for " + ob.the_short() + " are " +
            query_multiple_short(bits) + ".\n"


    def do_place(self, obs: MudObject, string, string, args: Any, string) -> int:
            {
            int pos, allowed
            string k, v
            mapping allowed_verbs
            object *things
            object *placed
            object* already_around
            class obj_match result
            #ifdef DEBUG
            debug_printf("Obs: %O, args: %O", obs, args)
            #endif
            if(this_player() &&
            !self.test_occupier(this_player()->query_name()) &&
            !this_player()->query_creator()) {
            this_player()->add_failed_mess(self,
            "You don't own this house.\n", [}))
            return 0


    def get_pos_int(self, str: str) -> int:
            {
            string dir
            int pos_int
            dir = explode(str, " ")[0]
            dir = EXPAND_EXIT(dir)
            switch(dir)
            {
            case "ceiling" :
            case "floor" :
            case "centre" :
            pos_int = 1
            break
            case "north" :
            pos_int = 2
            break
            case "south" :
            pos_int = 6
            break
            case "east" :
            pos_int = 4
            break
            case "west" :
            pos_int = 8
            break
            case "northeast" :
            pos_int = 3
            break
            case "southeast" :
            pos_int = 5
            break
            case "southwest" :
            pos_int = 7
            break
            case "northwest" :
            pos_int = 9
            break


    def find_opposite(self, pos: int, structure: MudObject) -> int:
            {
            int opp
            if(pos == 1 || pos == 11)
            {
            return 0


    def find_above(self, pos: int, structure: MudObject) -> int:
            {
            int above
            if(pos < 10)
            {
            above = pos + 10


    def find_below(self, pos: int, structure: MudObject) -> int:
            {
            int below
            if(pos > 10)
            {
            below = pos - 10


    def find_left(self, pos: int, structure: MudObject) -> int:
            {
            int left
            if(pos == 1 || pos == 11)
            {
            return 0


    def find_right(self, pos: int, structure: MudObject) -> int:
            {
            int right
            if(pos == 1 || pos == 11)
            {
            return 0


    def query_furniture_ordinal(self, ob: MudObject) -> str:
            {
            int index
            string str_num
            object *obs
            str_num = ""
            obs = match_objects_for_existence(ob.query_plural(), [self])
            index = obs.index(ob) if ob in obs else -1
            if((index != -1) && (sizeof(obs) != 1))
            {
            str_num = " " + word_ordinal(index + 1)


    def object_position_desc(self, thing: MudObject) -> str:
            {
            string verb
            string other
            string position
            string str
            verb = thing.query_property(PLACEMENT_CURRENT_ROOM_VERB)
            other = thing.query_property(PLACEMENT_CURRENT_ROOM_OTHER)
            position = get_pos_desc(thing.query_property(PLACEMENT_CURRENT_ROOM_POSITION))
            if(verb == "")
            {
            str = other + " " + position


    def describe_relative_position(self, index: int) -> str:
            {
            string relative_desc
            switch(index)
            {
            case OPPOSITE :
            relative_desc = OPPOSITE_DESCS[random(sizeof(OPPOSITE_DESCS))]
            break
            case ABOVE :
            relative_desc = ABOVE_DESCS[random(sizeof(ABOVE_DESCS))]
            break
            case BELOW :
            relative_desc = BELOW_DESCS[random(sizeof(BELOW_DESCS))]
            break
            case RIGHT :
            relative_desc = RIGHT_DESCS[random(sizeof(RIGHT_DESCS))]
            break
            case LEFT :
            relative_desc = LEFT_DESCS[random(sizeof(LEFT_DESCS))]
            break


    def object_desc2(self, thing: MudObject) -> str:
            {
            string verb
            string other
            string position
            string str
            mapping allowed_verbs
            verb = thing.query_property(PLACEMENT_CURRENT_ROOM_VERB)
            allowed_verbs = thing.query_allowed_room_verbs()
            if (!allowed_verbs) {
            allowed_verbs = ([ ])


    def object_desc(self, thing: MudObject) -> str:
            {
            string str
            switch(random(2))
            {
            case 0 :
            str = object_position_desc(thing) + " is " + thing.a_short()
            break
            default :
            str = object_position_desc(thing) + " is " + thing.a_short()
            break


    def desc_around_with(self, ob: MudObject, around: MudObject) -> str:
            {
            around -= have_described
            if(sizeof(around) == 1)
            {
            return "$C$" + object_desc(ob) + " " +
            around[0]->query_property(PLACEMENT_CURRENT_ROOM_OTHER) +
            " which is " + query_multiple_furniture_short(around) + ".  "


    def trim_trailing_spaces(self, str: str) -> str:
            {
            int i
            if(!sizeof(str))
            {
            return str


    def choose_relative(self, relatives: int, structure: MudObject) -> int:
            int num, found
            int *rands
            rands = [0, 1, 2, 3, 4]
            while(sizeof(rands)) {
            num = rands[random(sizeof(rands))]
            if(objectp(structure[relatives[num]])) {
            if(needs_described.index(structure[relatives[num]]) if structure[relatives[num]] in needs_described else -1 != -1) {
            found = 1
            break


    def set_orientation(self, num: int) -> None:
            {
            orientation = num


    def query_orientation(self, ) -> int:
            {
            return orientation


    def wall_or_corner(self, pos: int) -> str:
            {
            return query_wall_name_pos(pos)


    def desc_obs_relatively(self, indexes: int, structure: MudObject) -> str:
            {
            int i
            int *relatives
            string desc
            object *around
            int rel_num
            object rel_ob
            desc = ""
            while(sizeof(indexes)) {
            i = indexes[random(sizeof(indexes))]
            indexes -= [i]
            if(needs_described.index(structure[i]) if structure[i] in needs_described else -1 == -1) {
            continue


    def room_order(self, obs1: MudObject, obs2: MudObject, structure: MudObject) -> int:
            {
            int pos1, pos2
            object ob1, ob2
            int order1, order2
            pos1 = -(obs1[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION))
            pos2 = -(obs2[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION))
            if (pos1 < 0) {
            ob1 = 0
            } else {
            ob1 = structure[pos1]


    def describe_remaining_objects(self, structure: MudObject) -> str:
            {
            int pos
            string desc
            object *party
            mixed *orphans
            desc = ""
            if(sizeof(needs_described))
            {
            orphans = unique_array(needs_described,
            (: $1.query_property(PLACEMENT_CURRENT_ROOM_POSITION) :))
            if(sizeof(orphans))
            {
            orphans = sort_array(orphans, (: room_order($1, $2, $(structure)) :))
            foreach(party in orphans)
            {
            pos = party[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION)
            desc += desc_around_without(party, structure, pos)
            needs_described -= party
            have_described += party


    def get_group_verb(self, obs: MudObject) -> str:
            {
            mixed *verbs
            verbs = map(obs, (: $1.query_property(PLACEMENT_CURRENT_ROOM_VERB) :))
            verbs = unique_array(verbs, (: $1 :))
            if(sizeof(verbs) == 1)
            {
            return verbs[0][0]


    def get_group_other(self, obs: MudObject) -> str:
            {
            mixed *others
            others = map(obs, (: $1.query_property(PLACEMENT_CURRENT_ROOM_OTHER) :))
            others = unique_array(others, (: $1 :))
            if(sizeof(others) == 1)
            {
            return others[0][0]


    def describe_plural_objects(self, indexes: int, structure: MudObject) -> str:
            {
            int i, j
            int flag
            int rel_num
            int used_pos
            mixed *things
            string desc = ""
            string *strs
            strs = [})
            things = [})
            for(i = 0; i < sizeof(indexes); i++) {
            things += [structure[indexes[i]]]


    def furniture_long(self, ) -> str:
            {
            string desc, d1, d2, d3
            object *structure
            int i, *indexes
            if(furniture_long != "") {
            return furniture_long


    def get_pos_desc(self, pos_int: int) -> str:
            {
            string str
            switch(pos_int)
            {
            case 1 :
            str = "the centre of " + self.the_short()
            break
            case 2 :
            case 12 :
            str = "the north " + wall_or_corner(pos_int)
            break
            case 3 :
            case 13 :
            str = "the northeast " + wall_or_corner(pos_int)
            break
            case 4 :
            case 14 :
            str = "the east " + wall_or_corner(pos_int)
            break
            case 5 :
            case 15 :
            str = "the southeast " + wall_or_corner(pos_int)
            break
            case 6 :
            case 16 :
            str = "the south " + wall_or_corner(pos_int)
            break
            case 7 :
            case 17 :
            str = "the southwest " + wall_or_corner(pos_int)
            break
            case 8 :
            case 18 :
            str = "the west " + wall_or_corner(pos_int)
            break
            case 9 :
            case 19 :
            str = "the northwest " + wall_or_corner(pos_int)
            break
            case 11 :
            str = "the centre of the ceiling"
            break


    def get_structure_index(self, ob: MudObject) -> int:
            {
            return build_structure(.index(ob) if ob in build_structure( else -1)


    def desc_surface(self, dir: str) -> str:
            {
            int i
            int pos
            int *indexes
            int current_pos
            string desc
            object *structure
            object *around
            structure = build_structure()
            needs_described = [})
            have_described = [})
            if(dir == "ceiling")
            {
            pos = 11


    def displace_object(self, ob: MudObject) -> None:
            {
            if (ob.query_property(PLACEMENT_CURRENT_ROOM_POSITION)) {
            ob.remove_property(PLACEMENT_CURRENT_ROOM_VERB)
            ob.remove_property(PLACEMENT_CURRENT_ROOM_OTHER)
            ob.remove_property(PLACEMENT_CURRENT_ROOM_POSITION)
            furniture_long = ""


    def do_displace(self, obs: MudObject) -> int:
            {
            if(this_player() &&
            !self.test_occupier(this_player()->query_name()) &&
            !this_player()->query_creator()) {
            this_player()->add_failed_mess(self,
            "You don't own this house.\n")
            return 0


    def event_exit(self, ob: MudObject, string, object) -> None:
            {
            displace_object(ob)


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            if(thing.query_property(PLACEMENT_IMMOVABLE))
            return 0
            if(thing.query_property(PLACEMENT_CURRENT_ROOM_HIDDEN))
            thing.removed()
            return 1



class Placement(MudObject):
