# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/terrain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "terrain-maker room" )
            add_property( "determinate", "the " )
            set_light( 100 )
            set_long( "This room is quite bare, save a notice that has been "
            "taped on the door but its walls have been painted with "
            "scenes of deserts and forests, oceans and mountains, caves and "
            "swamps, and all manner of other types of terrain.\n"
            "Use \"help room\" to list the room's commands.\n" )
            add_exit( "northwest", ROOM +"development", "door" )
            add_sign("The large notice has furled corners and has been taped "
            "and re-taped to the door.\n",
            "Due to the incomprehensible help in this room, this \n"
            "notice was put up to help with the confusion.\n"
            "\n"
            "1.  To get information on a certain terrain, you\n"
            "    need to select that terrain by typing \n"
            "    \"terrain <terrain_name>\".\n"
            "\n"
            "2.  To remove floating or fixed locations within the terrain,\n"
            "    type \"list floating\" or \"list fixed\".\n"
            "\n"
            "    remove floating <path of terrain> <all 6 co ordinates> <level>\n"
            "\n"
            "    remove fixed <path of room>\n"
            "\n"
            "3.  To add a floating location, same as above, only use add.\n"
            "    For both removing and adding, no commas and no .c at the end\n"
            "    of path names.  When removing/adding fixed locations, all\n"
            "    locations must be done one by one.\n", 0, "notice")


    def reset(self, ) -> None:
            if ( !generator ) {
            generator = clone_object( "/obj/handlers/terrain_things/dungeon_maker" )
            generator.move( self )


    def init(self, ) -> None:
            ::init()
            add_command("help", "room", (: do_help() :) )
            add_command("terrain", "<string>", (: do_terrain($4[0]) :) )
            add_command("list", "fixed", (: do_list("fixed") :) )
            add_command("list", "floating", (: do_list("floating") :) )
            add_command("member", "", (: do_member(0,0) :) )
            add_command("member", "fixed <string>",
            (: do_member("fixed", $4[0]) :) )
            add_command("member", "floating <string>",
            (: do_member("floating", $4[0]) :) )
            add_command("add",
            "fixed <word'file'> <number'x'> <number'y'> <number'z'>",
            (: do_add(0, $4[0], $4[1], $4[2], $4[3], 0, 0, 0, 0) :) )
            add_command("add",
            "floating <word'file'> <number'x1'> <number'y1'> <number'z1'> "
            "<number'x2'> <number'y2'> <number'z2'> <number'level'>",
            (: do_add(1, $4[0], $4[1], $4[2], $4[3],
            $4[4], $4[5], $4[6],
            $4[7]) :) )
            add_command("add",
            "floating <word'file'> <number'x'> <number'y'> <number'z'> "
            "<number'level'>",
            (: do_add(2, $4[0], $4[1], $4[2], $4[3],
            0, 0, 0,
            $4[4]) :) )
            add_command("remove",
            "fixed <word'file'>",
            (: do_remove(0, $4[0], 0, 0, 0, 0, 0, 0) :) )
            add_command("remove",
            "floating <word'file'> <number'x1'> <number'y1'> <number'z1'> "
            "<number'x2'> <number'y2'> <number'z2'>",
            (: do_remove(1, $4[0], $4[1], $4[2], $4[3],
            $4[4], $4[5], $4[6]) :) )
            add_command("remove",
            "floating <word'file'> <number'x'> <number'y'> <number'z'>",
            (: do_remove(2, $4[0], $4[1], $4[2], $4[3],
            0, 0, 0 ) :) )
            add_command("clear", "", (: do_clear() :) )


    def do_help(self, ) -> int:
            write( "Available commands are:\n\n"+
            "     terrain  -  set terrain name\n"+
            "     list     -  list locations in current terrain\n"+
            "     member   -  find locations matching coordinates\n"+
            "     add      -  add a new location\n"+
            "     remove   -  remove an old location\n"+
            "     clear    -  clear all clones and connections\n" )
            return 1


    def do_terrain(self, name: str) -> int:
            if ( !name ) {
            if ( stringp( terrain_name ) )
            write( "Terrain name is "+ terrain_name +".\n" )
            else
            write( "There is no terrain name set.\n" )
            return 1


    def do_list(self, word: str) -> int:
            int i, size
            string list
            mapping locations
            mixed indeces, values
            if ( ( word != "fixed" ) && ( word != "floating" ) ) {
            write( "List what? Options are \"fixed\" and \"floating\".\n" )
            return 1


    def do_member(self, type: str, parameters: str) -> int:
            int i, size, *co_ords
            string list, location
            mixed *locations
            if (!type || !parameters) {
            write( "Syntax: member <fixed|floating> <coord1> ...\n" )
            return 1


    def do_clear(self, ) -> int:
            if ( !terrain_name ) {
            write( "There is no current terrain name.\n" )
            return 1



class Terrain(MudObject):
