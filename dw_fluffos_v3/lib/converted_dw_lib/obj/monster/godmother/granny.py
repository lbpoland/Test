# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/godmother/granny.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            start_time = time()
            set_name( "godmother" )
            set_short( "fairy godmother" )
            add_adjective( "fairy" )
            set_long( "This fairy godmother isn't quite what you expected.  She is "
            "tall and forbidding; not in the slightest bit cuddly or smiley.  She "
            "looks slightly uncomfortable and is currently glaring at her wand, "
            "which appears to be malfunctioning.  If you cross her, you might find "
            "yourself turned into a wombat or worse.\n" )
            set_race( "human" )
            set_class( "witch" )
            set_level( 300 )
            set_gender( 2 )
            set_language("general")
            set_response_mon_understand_anything(1)
            add_property( "anchor", 1)
            ARMOURY.request_item("hobnailed boots", 100)->move( self )
            ARMOURY.request_item("antique black dress", 100)->move( self )
            ARMOURY.request_item("witchs pointy hat", 100)->move( self )
            ARMOURY.request_item("black witches cloak", 100)->move( self )
            init_equip()
            add_respond_to_with(["yes"], "#yes_response")
            add_respond_to_with(["@nod"], "#yes_response")
            add_respond_to_with(["no"], "#no_response")
            add_respond_to_with(["@shake"], "#no_response")
            add_respond_to_with(["@think", "somewhere", "safe"], "#think_safe")
            add_respond_to_with(["@think", "safe"], "#think_safe")
            add_respond_to_with(["@think", "safety"], "#think_safe")
            add_respond_to_with(["@womble"], "#think_mended_drum")


    def do_panic(self, pl: MudObject) -> None:
            string home
            string nationality
            nationality = pl.query_nationality()
            if ( !nationality ) {
            queue_command( "say Oops.. you haven't got a nationality, I can't "
            "send you home!")
            finish_up()
            return


    def yes_response(self, ob: MudObject) -> None:
            if (ob != lost)
            return
            queue_command( "say Right then.  Close your eyes and concentrate." )
            queue_command( "say Think of somewhere safe." )
            prodded = 0
            asyncio.create_task(self."check_think", 30)


    def no_response(self, ob: MudObject) -> None:
            if (ob != lost)
            return
            queue_command( "say So why did you call me up then?", 1 )
            queue_command( "roll eyes "+lost.query_name() )
            queue_command( "pinch "+lost.query_name()+" cheek" )
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def think_safe(self, ob: MudObject) -> None:
            if (ob != lost)
            return
            queue_command( "say Now the world will just rearrange itself "
            "to suit you." )
            PANIC_HANDLER.finish_panic(lost, PANIC_OK)
            lost = 0


    def check_think(self, ) -> None:
            if(!lost)
            return
            if (prodded < 3 ) {
            queue_command( "say Come on, I haven't got all day.  Just think of "
            "safety." )
            queue_command( "tap" )
            prodded ++
            asyncio.create_task(self."check_think", 60)
            } else {
            queue_command( "say Young people of today..." )
            queue_command( "mutter no manners" )
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if (ob == lost) {
            queue_command("hrmph")
            queue_command("tell "+lost.query_name()+" Thats right!  Just walk "
            "out on me.")
            queue_command("glare "+lost.query_name() )
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def event_fight_in_progress(self, attacker: MudObject, attackee: MudObject) -> None:
            if (attackee == self) {
            attacker.adjust_tmp_str(-4)
            attacker.adjust_tmp_con(-4)
            attacker.adjust_tmp_dex(-4)
            attacker.adjust_tmp_int(-4)
            attacker.adjust_tmp_wis(-4)
            queue_command( "say What is this travesty!  Attacking your fairy "
            "godmother, Well I never." )
            queue_command( "say "+attacker.one_short()+" I here by curse you!" )
            queue_command( "say Don't expect me to help you again." )
            queue_command( "glare "+attacker.query_name() )
            attacker.add_property("attacked godmother", time())
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def hurry_up(self, ) -> None:
            if (!lost) {
            queue_command( "blink" )
            queue_command( "say Where'd that bugger go?  Oh well.")
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def finish_up(self, ) -> None:
            if (lost) {
            queue_command( "say Well.  You took too long.  What a complete "
            "waste of time." )
            queue_command( "glare " + lost.query_name() )
            lost = 0


    def event_dest(self, ob: MudObject) -> None:
            if (ob == lost) {
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def dest_me(self, ) -> None:
            if (lost) {
            PANIC_HANDLER.finish_panic(lost, PANIC_NOT_OK)
            lost = 0


    def unambushable(self, ) -> int:
            return 1



class Granny(MudObject):
