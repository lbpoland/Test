# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/crowd/am_crippled_beggar.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def initial_chats(self, ) -> None:
            load_chat( 15, ({
            1, "'Money for the crippled.",
            1, "'Please give me some money.",
            1, ":pulls on your leg.",
            1, ":rattles "+query_possessive()+" tin.",
            1, ":mutters something about a "+spouse+" and 7 children.",
            1, ":looks at you with big brown eyes.",
            1, "'Who will help me?",
            1, ":hobbles around pathetically.",
            1, "#do_gossip_say:Did you know $name$ said $mess$?",
            1, "@open door",
            }) )


    def fix_gender(self, gender: int) -> None:
            set_gender( gender )
            set_long( "This is a crippled beggar.  "
            "One of "+query_possessive()+
            " legs has wasted so that it ressembles a gnarled branch.\n" )
            spouse = (query_gender()==1) ? "wife" : "husband"


    def setup(self, ) -> None:
            set_name("beggar")
            set_short( "crippled beggar" )
            set_main_plural( "crippled beggars" )
            add_adjective("crippled")
            add_alias("beggar")
            set_race("human")
            set_level( 3 + random( 10 ) )
            set_wimpy( 80 )
            set_al( HOSPITAL.pick_al() / 10 )
            fix_gender(1+random(2))
            add_move_zone("docks")
            add_move_zone("underdocks")
            start_money = 3 + random( 300 )
            adjust_money( start_money, "Waterdeep pence" )
            initial_chats()
            add_effect( "/std/effects/npc/gossip", 5 )
            add_effect( "/std/effects/npc/given", [self, "given_thing"])


    def done_everything(self, ) -> None:
            going = 0


    def at_pub(self, ) -> None:
            mixed *stuff
            string dest
            stuff = environment()->query_menu_items()
            if (!stuff) {
            dest = PUBS[random(sizeof(PUBS))]
            add_effect( "/std/effects/npc/goto_destination",
            [dest, [self, "at_pub"], 20] )
            } else {
            add_effect( "/std/effects/npc/drink_silly",
            [self, "done_drinking"] )


    def hassle_opposite_gender(self, ) -> None:
            object *things
            string action
            things=filter(all_inventory(environment()),
            (: $1.query_gender()==3-($2.query_gender()) :), self )
            if (sizeof(things)) {
            action=[":leers at TARGET.",
            ":pats TARGET on the bum.",
            "say How's it going sweetheart?",
            ":grins at TARGET.",
            ":wolf whistles at TARGET."][random(5)]
            do_command(replace(action,"TARGET",
            things[random(sizeof(things))]->the_short() ))
            return


    def done_drinking(self, ) -> None:
            load_chat( 60, ({
            1, "'You rich prats never give me any respect.",
            1, "'Give me some money for booze.",
            5, "#hassle_opposite_gender",
            1, ":ponders "+query_possessive()+" empty tin.",
            1, ":chuckles something about a "+spouse+" and 7 children.",
            1, ":grins toothily at you.",
            1, "@burp",
            1, "#do_gossip_say:Do you even care that $name$ said $mess$?"
            }) )
            asyncio.create_task(self. function() { self.initial_chats()
            self->add_effect( "/std/effects/npc/goto_destination",
            [from, [self, "done_everything"], 5] ); },
            random(300)+300 )


    def given_thing(self, player: MudObject, ob: MudObject, mess: str) -> None:
            string dest
            if (ob.id(MONEY_ALIAS)) {
            if (!going) {
            if(ob.query_value_in("Waterdeep") > 300) {
            this_player()->adjust_al( -5 )


    def loot_coins(self, ) -> None:
            asyncio.create_task(self. (: do_command(":looks around nervously.") :), 2 )
            asyncio.create_task(self. (: do_command("get coins from corpse") :), 5+random(10) )



class Am_crippled_beggar(MudObject):
