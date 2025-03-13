# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/cabbage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "cabbage" )
            set_short( "cabbage" )
            set_long( "A small cute looking cabbage.\n" )
            set_race( "cabbage" )
            set_level( 1 )
            add_respond_to_with( [["@hug", "@snuggle", "@cuddle", "@nestle",
            "@snuffle", "@smooch", "@fondle", "@huggle", "@squeeze", "@wuffle"
            "@hop", "@lick", "@snog", "@fluff", "@nuzzle"], "you"],
            "#respond_nice")
            add_respond_to_with( [["@skick", "@spunch", "@sburn", "@jump",],
            "you"], "#respond_nasty")
            #ifndef __DISTRIBUTION_LIB__
            if (SPECIAL_DAY_HANDLER.query_special_day() == CABBAGE_DAY) {
            add_property( "player", 1 )
            set_get()


    def init(self, ) -> None:
            ::init()
            this_player()->add_command("eat", self, "<direct:object'cabbage'>" )
            asyncio.create_task(self. "check_env", 3 )


    def set_owner(self, thing: MudObject) -> None:
            if (!objectp( thing ) )
            return
            set_long( (: long_desc :) )
            owner = thing
            owner_name  = owner.query_name()
            owner_short = owner.query_short()
            language = owner.query_default_language()
            add_language( language )
            set_language( language )
            load_chat(30, ({
            1, "@roll up",
            1, "@purr",
            1, ":$V$0=ruffles its,ruffle their$V$ fronds.",
            1, ":$V$0=looks,look$V$ green.",
            3, "#soul_owner",
            1, "@roll over",
            1, "#check_env"] )
            check_env()


    def long_desc(self, ) -> str:
            if ( owner && environment( owner ) == environment() ) {
            return "This small, cute-looking cabbage stares adoringly at "
            + owner.the_short() + ".\n"


    def respond_nice(self, souler: MudObject) -> None:
            if ( !souler.query_visible(self) )
            return
            if ( owner && souler == owner) {
            do_command("nestle " + souler.query_name() )
            } else {
            do_command("peer curiously " + souler.query_name() )


    def respond_nasty(self, souler: MudObject) -> None:
            if ( !souler.query_visible(self) )
            return
            if ( owner && souler == owner) {
            do_command("gasp")
            do_command("cry")
            } else {
            do_command( "sburn " + souler.query_name() + " dreams")


    def do_eat(self, ) -> int:
            if ( this_player() != owner || eaten) {
            this_player()->add_failed_mess( self, "You cannot eat this "
            "cabbage!\n" )
            return -1


    def zap_cabbage(self, ) -> None:
            if ( environment() ) {
            all_inventory()->move( environment() )


    def attack_by(self, ob: MudObject) -> int:
            if( ( !query_owner() || ob == query_owner() ) &&
            base_name( previous_object() ) == LANCE )
            asyncio.create_task(self. "coleslaw", 2 )
            ob.stop_fight(self)
            await ob.send("The cabbage is a terrible pacifist.\n")


    def attack_ob(self, ob: MudObject) -> int:
            ob.stop_fight(self)
            await ob.send("The cabbage is a terrible pacifist.\n")


    def adjust_hp(self, number: int, attacker: MudObject) -> int:
            return 0


    def soul_owner(self, ) -> None:
            string *souls = ["snuggle ", "nestle ", "stare dreamily ", "snuffle "]
            if(!owner)
            return
            if ( environment() != environment( owner ) ) {
            do_command( "sniffle sadly" )
            return


    def check_env(self, ) -> None:
            object my_env, owner_env, *caterpillars
            if ( !owner_name )
            return
            my_env = environment()
            if ( !my_env ) {
            return


    def query_owner(self, ) -> MudObject:
            return owner


    def query_theft_command(self, ) -> int:
            return -1


    def coleslaw(self, ) -> None:
            object ob
            tell_room( environment(), the_short() + " explodes in a shower of "
            "fronds.\n" )
            ob = ARMOURY.request_object("coleslaw", 100)
            if (ob) {
            ob.move( environment() )



class Cabbage(MudObject):
