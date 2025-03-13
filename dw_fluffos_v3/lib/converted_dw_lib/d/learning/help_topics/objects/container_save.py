# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/objects/container_save.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("room of shelf and wardrobe examples")
            add_property( "determinate", "the " )
            set_long( "This room gives some simple examples of how to make shelves, "
            "wardrobes and such that'll save the content for you.\n"
            "To make a shelf, which is characterized by having a surface "
            "you can put things on, you make a clone of /obj/surf_save, "
            "configure it like all cloned objects, and call set_save_file( "
            "file_name ) do tell what file should be used to save the "
            "objects that are put on it.  If the savefile isn't in /save/ "
            "you should call check_euid() on the shelf before calling "
            "set_save_file().\n"
            "Making a wardrobe, you do the same, except you that it is "
            "/obj/cont_save you should clone.\n"
            "Note that since these are fixed parts of the room, and not "
            "something that is put here, I clone them directly in reset() "
            "instead of doing a asyncio.create_task(self.) to a function that makes them.\n" )
            set_light( 100 )
            add_exit( "back", LEARNING +"search", "path" )
            add_exit( "exit", ENTRANCE, "path" )
            add_property( "commented functions",
            ["check_euid", "set_save_file"] )
            add_property( "keywords",
            ["shelf", "wardrobe", "save"] )


    def reset(self, ) -> None:
            if (!shelf) {
            shelf = clone_object("/obj/surf_save")
            shelf.set_name( "shelf" )
            shelf.set_short( "oaken shelf" )
            shelf.add_adjective( "wooden" )
            shelf.add_adjective( "oak" )
            shelf.add_adjective( "oaken" )
            shelf.add_property( "there", "hanging from the wall" )
            shelf->set_long( "This shelf is made from oak and "
            "varnished to bring out the glow.\n" )
            shelf.set_weight( 2000 )
            shelf.set_max_weight( 2000 )
            shelf.reset_get()
            shelf.check_euid()
            shelf.set_save_file( SAVEPATH+"/oak_shelf" )
            shelf.move( self )



class Container_save(Room):
