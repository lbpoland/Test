# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/juicer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "juicer" )
            set_short( "juicer" )
            set_main_plural( "juicers" )
            set_long( "This is a device for extracting the juice or liquid from " +
            "objects.  It has a hole at the top for inserting things, " +
            "and a small bowl at the bottom to catch the juice.  You " +
            "could probably \"juice\" something and then \"pour\" " +
            "the juicer into another container.\n" )
            set_value( 4000 )
            set_weight( 100 )
            set_max_volume( 19200 )


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "juice", self, "%I 'in' %D" )


    def do_juice(self, things: MudObject) -> int:
            int i, amount, *weight_unit, percent
            string medium_short, *types, fn
            mapping amount_types
            if ( living( environment() ) ) {
            this_player()->add_failed_mess( self, "You have to put down "+
            "$D to use it.\n", [}) )
            return 0


    def juice_bit(self, ob: MudObject, fn: str) -> int:
            object juice_ob
            mixed *bit_data
            string *m, s
            int i
            juice_ob = clone_object("/obj/reagents/generic_liquid.ob")
            juice_ob.set_name("juice")
            if (s = ob.query_race_name())
            s = capitalize(s)
            bit_data = ob.query_bit_data()
            m = explode(bit_data[ BIT_NAME ], " ")
            for ( i = 0; i < sizeof(m); i++ )
            s += capitalize(m[i]?m[i]:"")
            juice_ob.set_medium_alias(s+"Juice")
            switch ( bit_data[ BIT_ALIAS ] ) {
            case "eye":
            juice_ob.add_adjective("eye")
            juice_ob.add_alias("ichor")
            juice_ob.set_short("clear liquid")
            juice_ob->set_long("This is a clear liquid, slightly tinged" +
            "with blood.\n")
            juice_ob.set_amount(10*(int)ob.query_weight() + 10)
            break
            default:
            juice_ob.set_short("liquid")
            juice_ob->set_long("This is a non-descript liquid.  It's probably " +
            "useless.\n")
            break



class Juicer(MudObject):
