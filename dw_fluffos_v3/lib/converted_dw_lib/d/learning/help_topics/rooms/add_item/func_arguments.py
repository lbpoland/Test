# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/func_arguments.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about the arguments of the function" )
            set_light( 100 )
            add_property( "determinate", "the " )
            set_long( "This is a room telling about the arguments passed to the "
            "do_<verb>() function.  Go east for examples of using the "
            "arguments, west for something else:).\n"
            "Here goes:\n"
            "  int do_<verb>( string command, object *indir, string dir_match,\n"
            "                 string indir_match, mixed *args, string pattern );\n"
            "$I$12=command     is a string, it is the name of the verb "
            "used.$I$0=\n"
            "$I$12=indir       is an array of objects.  If any indirect "
            "objects are requested for, then they will be in this array."
            "$I$0=\n"
            "$I$12=dir_match   is a string, it is the name of the direct "
            "object.$I$0=\n"
            "$I$12=indir_match is a string, it is the name of the indirect "
            "object.$I$0=\n"
            "$I$12=args        is a mixed array of strings and numbers.  For "
            "each <> thingie you have in the pattern, it has a member.  So "
            "if you have <direct:object>, it has the name of the direct "
            "object, if you have <number> then it will have a number also, "
            "if <indirect:object>, the indirect object's name, and so on.  "
            "They are in the same order as in the pattern.$I$0=\n"
            "$I$12=pattern     is a string containing the pattern. It is "
            "useful to know which pattern has been caught since multiple "
            "patterns are allowed per function.$I$0=\n\n"
            "All do_<verb> functions in the learning domain will write their "
            "arguments, to help you figure out how to use them.\n"
            "A pool you can jump into is here.\n" )
            add_item( "large pool", ({
            "long", "It looks like you can jump into it.",
            "jump", [self, "do_jump", "[into|in] <direct:object>"]
            }) )
            add_exit( "east", PATH +"args_integer", "path" )
            add_exit( "west", PATH +"verb_patterns", "path" )
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )



class Func_arguments(Room):
