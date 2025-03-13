# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/player_housing.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_owner(self, ) -> str:
            class decoration {
            string short
            string covering


    def debug_log(self, fmt: str, args: Any) -> None:
            debug_printf(fmt + "\n", args ...)
            if(base_name(self) == "/d/cwc/Bes_Pelargic/Pong_Ping/roads/phoenix_avenue/housing/05entrycorridor") {
            log_file("HOUSING_DEBUG", "%s (%s): " + fmt + "\n",
            ctime(time())[4..18], base_name(self), args ...)


    def __init__(self):
            self.exits = ([ ])
            self.exit_shorts = ([ ])
            self.decorations = []
            self.tell_denied = []
            self.done_setup = 0


    def show_surface(self, direc: str) -> str:
            class decoration tmp
            int found
            string lstr, dstr
            mixed tmp2
            switch(direc) {
            case "left":
            case "right":
            case "forward":
            case "backward":
            tmp2 = this_player()->query_facing()
            direc = (string)this_player()->find_abs(direc, tmp2[0])
            break
            case "up":
            direc = "ceiling"
            break
            case "down":
            direc = "floor"
            break


    def show_corner(self, direc: str) -> str:
            string tmp
            tmp = desc_surface(direc)
            if(tmp == "") {
            tmp = "The " + direc + " corner is empty."


    def exit_long(self, ) -> str:
            string *direcs, lstr
            int i, j
            object door
            direcs = query_direc()
            if(!sizeof(direcs))
            return ""
            lstr = "  $C$"
            for(i=0; i<sizeof(direcs); i++) {
            update_short_cache(direcs[i])
            if(query_relative(direcs[i])) {
            j = REL_DIRS.index(this_player()->find_rel(direcs[i])) if this_player()->find_rel(direcs[i]) in REL_DIRS else -1
            lstr += REL_DIRS[j+2]
            if(exit_shorts[direcs[i]]) {
            if(query_door_control(direcs[i]))
            lstr += " " + query_door_control(direcs[i])->a_short() + " leads "
            "to " + exit_shorts[direcs[i]]->a_short
            else
            lstr += " an exit leads to " + exit_shorts[direcs[i]]->a_short
            } else {
            if(query_door_control(direcs[i]))
            lstr += " is " + query_door_control(direcs[i])->a_short()
            else
            lstr += " is an exit"


    def decoration_long(self, ) -> str:
            class decoration tmp
            string lstr, wstr, tmpstr, *tmparray, *names
            int i
            #ifdef 0
            if(decoration_desc != "")
            return decoration_desc
            #endif
            lstr = ""
            if(sizeof(decorations)) {
            coverings = ([ ])
            names = ["walls"]
            foreach ( tmp in decorations ) {
            if(!coverings[tmp->covering])
            coverings[tmp->covering] = [tmp->short]
            else
            coverings[tmp->covering] += [tmp->short]
            if(classp(tmp) && strsrch(tmp->short, "wall") == -1)
            names += [tmp->short]


    def query_long(self, ) -> str:
            string lstr, tmp
            if(base_long)
            lstr = "This is " + base_long + "."
            else
            lstr = ""
            tmp = decoration_long()
            if(tmp != "")
            lstr += tmp
            else
            lstr += "  "
            return (lstr + furniture_long() + exit_long() + "\n")


    def setup_exit(self, direc: str, relative: int) -> int:
            if(STANDARD_EXITS.index(direc) if direc in STANDARD_EXITS else -1 != -1 && relative)
            modify_exit(direc, ["relative", 1])
            modify_exit(direc, ["closed", 1])
            return 1


    def set_base_desc(self, desc: str) -> None:
            base_long = desc


    def query_base_desc(self, ) -> str:
            return base_long


    def set_quit_handler(self, filename: str) -> None:
            quit_location = filename


    def query_quit_handler(self, ) -> str:
            if(this_player() && !test_occupier(this_player()->query_name()) &&
            quit_location)
            return quit_location
            return base_name(self)


    def add_surface(self, short: str, covering: str) -> None:
            class decoration tmp
            string dir
            if(!surfaces)
            surfaces = [})
            surfaces += [short]
            if(!decorations)
            decorations = [})
            else {
            foreach(tmp in decorations)
            if(tmp->short == short) {
            add_item(tmp->short, (: show_surface($(tmp->short)) :))
            short = replace(short, ({" wall", ""}))
            foreach(dir in keys(ABS_FACING)) {
            if(ABS_FACING[short] &&
            ABS_FACING[dir] == (ABS_FACING[short] % 8 ) + 1) {
            add_item(dir+" corner", (: show_corner($(dir)) :))
            break


    def decorate_surface(self, short: str, covering: str) -> int:
            class decoration tmp
            foreach(tmp in decorations)
            if(tmp->short == short) {
            tmp->covering = covering
            event(self, "save")
            decoration_desc = ""
            return 1


    def query_decorations(self, ) -> None:
            printf("%O\n", decorations)


    def test_save(self, thing: MudObject) -> int:
            return thing.query_furniture() || thing.query_missing_item_receipt()


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            if(!placement::test_remove(thing, flag, dest))
            return 0
            return room_save::test_remove(thing, flag, dest)


    def init(self, ) -> None:
            placement::init()
            if(!allowed) {
            allowed = [})


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            #ifdef PLAYTESTING
            if(interactive(ob) &&
            (!ob.query_creator() &&
            !"/obj/handlers/playtesters"->query_playtester(ob.query_name())) &&
            ob.query_name() != "gumboot") {
            await ob.send("Sorry, this area is only open to playtesters.\n")
            ob.move(from)


    def allow_list(self, ) -> int:
            string *tmp
            if(owner && owner != "For Sale" && owner != "Under Offer") {
            tmp = [owner] + allowed
            } else {
            tmp = allowed


    def do_allow(self, player: MudObject, location: str) -> int:
            string pname
            string *rooms
            string room
            int failed
            if((query_owner() != this_player()->query_name()) &&
            !this_player()->query_creator()) {
            add_failed_mess("You are not allowed to control this room.\n", [}))
            return 0


    def do_deny(self, player: str, location: str) -> int:
            object ob
            string *rooms, room
            if(allowed.index(player) if player in allowed else -1 == -1) {
            add_failed_mess(player + " is not on the allow list.\n")
            return 0


    def update_doors(self, ) -> None:
            string exit
            object door_ob
            if(!done_setup)
            setup_doors()
            if(!exits)
            exits = ([ ])
            foreach(exit in query_exits()) {
            door_ob = query_door_control(exit)
            if(door_ob) {
            if(door_ob.query_key() == "generic_key") {
            #ifdef DEBUG
            if(exits[exit])
            debug_log("update_doors", "Door %s has generic_key, exit data "
            "has %s", exit, exits[exit]->key)
            else
            debug_log("update_doors", "Door %s has generic_key, no existing "
            "exit data.", exit)
            #endif


    def setup_doors(self, ) -> None:
            string exit
            object door
            string other, other_id
            #ifdef DEBUG2
            debug_log("Setup doors called.")
            #endif
            if(!self.query_exits()) {
            self.calc_exits()


    def query_owner(self, ) -> str:
            if(owner)
            return owner
            return HOUSING.query_owner(base_name(self))


    def add_allowed(self, pname: str) -> int:
            if(test_occupier(pname))
            return 0
            allowed += [pname]
            event(self, "save")
            return 0


    def remove_allowed(self, pname: str) -> int:
            if(!test_occupier(pname))
            return 0
            allowed -= [pname]
            event(self, "save")
            return 1


    def test_occupier(self, name: str) -> int:
            if(!owner)
            catch(owner = HOUSING.query_owner(base_name(self)))
            if(!owner || lower_case(owner) == "for sale" ||
            lower_case(owner) == "under offer")
            return 1
            if(PLAYER_HANDLER.test_creator(name))
            return 1
            if(!allowed)
            allowed = [})
            return (owner == name || (allowed.index(name) if name in allowed else -1 != -1))


    def ownership_change(self, old_owner: str, new_owner: str) -> int:
            if(old_owner != new_owner) {
            owner = new_owner
            allowed = [})
            return 1


    def is_allowed(self, name: str) -> int:
            if((query_owner() && (lower_case(name) == lower_case(query_owner()))) ||
            (query_allowed(.index(lower_case(name)) if lower_case(name) in query_allowed( else -1) != -1) ||
            PLAYER_HANDLER.test_creator(name)) {
            return 1


    def dest_me(self, ) -> None:
            #ifdef NOT_USED
            if (base_name(self) + ".c" != __FILE__)
            update_doors()
            #endif
            ::dest_me()


    def event_open(self, door: MudObject, opener: MudObject) -> None:
            #ifdef DEBUG2
            debug_log("door opened by %s [%d]", opener.query_name(), done_setup)
            #endif
            if(done_setup) {
            ::event_open(door, opener)
            update_doors()


    def event_close(self, door: MudObject, closer: MudObject) -> None:
            #ifdef DEBUG2
            debug_log("door closed by %s [%d]", closer.query_name(), done_setup)
            #endif
            if(done_setup) {
            ::event_close(door, closer)
            update_doors()


    def event_unlock(self, door: MudObject, unlocker: MudObject) -> None:
            #ifdef DEBUG2
            debug_log("door unlocked by %s [%d]",
            unlocker?unlocker.query_name():"noone", done_setup)
            #endif
            if(done_setup) {
            ::event_unlock(door, unlocker)
            update_doors()


    def event_lock(self, door: MudObject, locker: MudObject) -> None:
            #ifdef DEBUG2
            debug_log("door locked by %s [%d]", locker?locker.query_name():"noone",
            done_setup)
            #endif
            if(done_setup) {
            ::event_lock(door, locker)
            update_doors()



class Player_housing(MudObject):

    exits = '([ ])'

    exit_shorts = '([ ])'

    decorations = '[]'

    tell_denied = '[]'

    done_setup = 0
