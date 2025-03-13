# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/cutnpaste/kess.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            object chain
            set_name("kess")
            set_short("Kess of Sek")
            set_main_plural("Kesses of Sek")
            set_long( "This is Kess, an Archcardinal of Sek.  She is a young woman, "+
            "and beautiful in a twisted kind of way.  She seems fairly "+
            "innocuous until you notice her eyes and see the vicious look in "+
            "them.\n" )
            add_adjective(({"archcardinal", "of", "sek"}))
            add_alias(({"priestess", "archcardinal", "cardinal"}))
            add_property("determinate","")
            add_property("unique", 1)
            set_gender("female")
            set_race("human")
            set_class("priest")
            set_deity("sek")
            set_level(260)
            set_height(140)
            set_weight(1000)
            set_al(2000)
            adjust_str(2)
            adjust_con(2)
            adjust_wis(5)
            adjust_int(-6)
            adjust_dex(-3)
            add_skill_level( "faith.items.rod", 250, 0 )
            add_skill_level( "fighting.combat.melee.blunt", 200, 0 )
            add_skill_level( "fighting.combat.parry.held", 200, 0 )
            add_known_command("kick")
            add_spell( "paralysis", "/obj/rituals/paralysis",
            "cast_spell" )
            add_spell( "fear", "/obj/rituals/fear",
            "cast_spell" )
            add_spell("cure medium wounds", "/obj/rituals/curemedium",
            "cast_spell" )
            add_spell("calm", "/obj/rituals/calm",
            "cast_spell" )
            add_spell( "rage", "/obj/rituals/rage",
            "cast_spell" )
            set_join_fights( "Blood-lust glows in Kess' eyes as she dives "+
            "into the melee.\n" )
            set_join_fight_type(1)
            chain = ARMOURY.request_armour("chainmail", 100)
            chain.add_ac("magic", "magic", 60)
            chain.add_ac("fire", "fire" , 60)
            chain.add_ac("cold", "cold", 60)
            chain.move(self)
            chain.add_property("holy amulet", "sek")
            chain.add_property("sek", 1)
            ARMOURY.request_armour("blood red cloak", 100)->move(self)
            ARMOURY.request_armour("rope belt", 100)->move(self)
            ARMOURY.request_armour("soft leather shoes", 100)->move(self)
            rod = ARMOURY.request_weapon( "cleric rod", 100 )
            rod.whichone(6)
            rod.set_enchant(8)
            rod.move(self)
            clone_object("/obj/faith/sek_symbol.arm")->move(self)
            init_equip()
            ((object)ARMOURY.request_weapon("dagger", 100))->move(self)
            do_command("tactics response parry")
            do_command("tactics parry both")
            do_command("tactics attitude offensive")
            load_chat(20, ({2, ":smiles viciously.",
            1, "@glare $lname$",
            1, "@smirk",
            }))
            load_a_chat(20, ({1, "'Do you know who I am?",
            1, "'Die unbeliever!",
            1, "'You fight me, Sek will rip your heart out!"}) )
            set_virtual_move(1)
            set_move_after(30, 120)
            add_move_zone("Waterdeep")
            add_move_zone("sek")
            add_enter_commands("#get_heart")
            add_combat_action(100, "maintenance", ["maintain_self"] )
            add_combat_action(70, "fighting_stuff", ["fighting_stuff"] )
            add_combat_action(50, "reequip", ["reequip"])


    def reequip(self, thing1: MudObject, thing2: MudObject) -> None:
            if(self.query_holding()[0] != rod) {
            do_command( "get yellow rod" )
            do_command( "hold yellow rod" )


    def fighting_stuff(self, thing1: MudObject, thing2: MudObject) -> None:
            if(thing2 != self)
            return
            switch(random(6)) {
            case 5:
            do_command("cast rage on "+thing1.query_name())
            break
            case 4:
            do_command("cast fear on "+thing1.query_name())
            break
            case 3:
            do_command("cast paralysis on "+thing1.query_name())
            break
            case 2:
            do_command("use rod to cast dustdevil")
            break
            case 1:
            do_command("use rod to cast barrier")
            break
            default:
            do_command("concentrate on "+thing1.query_name())
            do_command("kick "+thing1.query_name())
            break


    def maintain_self(self, thing1: MudObject, thing2: MudObject) -> None:
            if ( thing2 != self )
            return
            if ( query_gp() < 200 )
            adjust_gp( 200 )
            if ( query_hp() < query_max_hp() / 4 )
            do_command( "use rod to cast sanctuary" )
            if ( query_hp() < query_max_hp() / 2 )
            do_command( "cast calm on "+thing1.query_name())
            if ( query_hp() < query_max_hp() )
            do_command( "cast cure medium wounds on kess" )


    def event_death(self, thing: MudObject) -> None:
            if(thing != self) {
            asyncio.create_task(self."get_heart", 3)


    def get_heart(self, ) -> None:
            object corpse
            if(find_match("corpse", environment()) != ({})) {
            do_command("hold dagger")
            do_command("get heart from corpse")
            do_command("eat heart")
            do_command("hold rod")


    def adjust_hp(self, hp: int, attacker: MudObject) -> int:
            ::adjust_hp(hp, attacker)
            if(hp < -300) {
            init_command("cast cure medium wounds on kess")
            if(!random(3))
            asyncio.create_task(self."eek", 0)


    def eek(self, ) -> None:
            do_command("lose all")
            run_away()



class Kess(MudObject):
