# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/wallpaper.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "wallpaper" )
            set_short( "roll of wallpaper" )
            set_main_plural( "rolls of wallpaper")
            add_adjective( ["roll", "of"}))
            add_plural_adjective("rolls")
            add_alias(({"paper"}))
            set_long( "This is a large roll of wallpaper, probably enough to "
            "cover a single wall completely.\n")
            set_value( 480 )
            set_weight( 10 )


    def make_roll(self, design: str) -> None:
            _design = design
            set_short( "roll of " + _design + " wallpaper" )
            set_main_plural( "rolls of " + _design + " wallpaper")
            add_adjective( [_design])
            set_long( "This is a large roll of " + _design + " wallpaper.  It "
            "looks like there's just enough of it to cover a single wall "
            "completely.  If you had some wallpaper glue you could probably "
            "paste it to the wall.\n")


    def init(self, ) -> None:
            this_player()->add_command("paste", self,
            "<direct:object> to <indirect:object:here'cardinal direction'> using <indirect:object'pot'>", (: do_paper( $4[1], $1[1][0] ) :))


    def query_paper_mess(self, ) -> str:
            if( _design ) {
            return _design + " wallpaper"


    def init_static_arg(self, args: Any) -> None:
            if (args["::"])
            ::init_static_arg(args["::"])
            if(!undefinedp(args["design"]))
            _design = args["design"]
            if(_design)
            make_roll(_design)



class Wallpaper(MudObject):
