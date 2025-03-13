# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/chars/dog.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            colour = ["light brown", "black", "grey", "mottled", "white", "patched",
            "dark brown", "black and white", "fluorescent yellow"][ random( 9 ) ]
            set_name("dog")
            set_race("dog")
            set_gender(1 + random(2))
            set_level( 1 + random( 1 + random( 3 ) ) )
            add_adjective("hairy")
            add_adjective(explode(colour, " "))


    def set_type(self, type: str) -> None:
            set_short( type +" "+ colour +" dog" )
            set_main_plural( type +" "+ colour +" dogs" )
            add_adjective( type )
            if ( type == "small" ) {
            set_long("The small "+colour+" dog is very hairy.  It looks a "
            "bit sad and lost in the streets of Pumpkin.  "
            "You are sure it would prefer a cat flap and a nice "
            "hot meal every night, or is that you?\n")
            } else {
            add_skill_level( "fighting", random( 10 + random( 30 ) ) )
            add_skill_level( "other.health", random( 10 + random( 30 ) ) )
            set_main_plural("large "+colour+" dogs")
            add_adjective("large")
            set_long("The large "+colour+" dog confidently walks the streets, "
            "insolently not moving aside for the warriors and heroes "
            "stalking the streets.\n")


    def bark_at_hidden(self, per: MudObject) -> None:
            mapping hide_invis
            if (per) {
            hide_invis = per.query_hide_invis()
            if (environment(per) == environment() &&
            hide_invis["hiding"]) {
            do_command("bark loudly")
            if (!random(4))
            do_command("bark loudly at "+
            per.query_name())
            else
            do_command("bark loudly")
            asyncio.create_task(self."bark_at_hidden", 2, per)


    def check_for_hidden(self, ) -> None:
            object *obs, mine
            int i
            mapping hide_invis
            function fun
            mine = query_property("following")
            obs = all_inventory(environment(self))
            for (i=0;i<sizeof(obs);i++) {
            hide_invis = query_hide_invis()
            if (living(obs[i]) && hide_invis["hiding"] &&
            obs[i] != mine && obs[i]->query_visible(self)) {
            asyncio.create_task(self."bark_at_hidden", 0, obs[i])
            break


    def test_rabid_attack(self, ) -> None:
            int i
            object *obs
            obs = filter_array(all_inventory(environment()),
            (: living($1) && $1 != $2 &&
            (!$1.query_property("player") ||
            $1.query_level() > 5) :),
            self)
            if (sizeof(obs))
            attack_ob(obs[0])


    def test_urinate(self, ) -> None:
            object *obs, *liv, blue, mine
            int i
            liv = [})
            mine = query_property("following")
            obs = all_inventory(environment())
            check_for_hidden()
            for (i=0;i<sizeof(obs);i++) {
            if (living(obs[i]) && obs[i] != mine &&
            obs[i] != self) {
            liv += obs[i..i]


    def i_like_them(self, them: MudObject) -> None:
            if(!them || environment() != environment(them))
            return
            asyncio.create_task(self."i_like_them", 60+random(240), them)
            if (query_property("excited")) {
            do_command("bounce excit")
            } else switch (random(5)) {
            case 0 :
            do_command("nuzzle "+them.query_name())
            break
            case 1 :
            do_command("stare pitifully at "+them.query_name())
            break
            case 2 :
            do_command("smile "+them.query_name())
            break
            case 3 :
            do_command("eye "+them.query_name())
            break
            case 4 :
            do_command("drool "+them.query_name())
            break


    def pat_me(self, per: MudObject) -> None:
            object ob
            ob = query_property("following")
            if (objectp(ob) &&
            environment(ob) == environment()) {
            init_command("nuzzle "+per.query_name())
            } else if (environment() == environment(per) &&
            (query_property("monster type") == "small dog" ||
            !random(5))) {
            init_command("follow "+per.query_name())
            init_command("protect "+per.query_name())
            add_property("following", per)
            asyncio.create_task(self."i_like_them", 60+random(240), per)
            } else {
            init_command("ignore "+per.query_name())


    def periodic_excited(self, ) -> None:
            if (query_property("excited")) {
            if (query_property("excited") > 1) {
            switch (random(4)) {
            case 0 :
            do_command("growl")
            break
            case 1 :
            do_command("bark")
            break
            case 2 :
            do_command("caper")
            break
            case 3 :
            do_command("bounce excit")
            break


    def sic_em(self, per: MudObject, mess: str) -> None:
            string *bing
            object mine
            object *obs
            int lvl
            bing = explode(replace(mess, "!", ""), " ")
            mine = query_property("following")
            if (bing[0] == "get" && per == mine) {
            obs = match_objects_for_existence(bing[1], environment())
            obs = filter_array(obs, (: living($1) :))
            if ( sizeof( obs ) ) {
            lvl = query_property( "excited" )
            add_property( "excited", lvl+1 )
            asyncio.create_task(self. function( object npc ) {
            int lvl
            lvl = npc.query_property("excited")
            if (lvl > 0)
            npc.add_property("excited", lvl - 1)
            else
            npc.remove_property("excited")
            }, 120, self)
            if (!lvl) {
            asyncio.create_task(self."periodic_excited", 10+random(10))



class Dog(MudObject):
