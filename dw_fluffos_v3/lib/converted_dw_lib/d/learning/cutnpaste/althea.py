# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/cutnpaste/althea.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("althea")
            set_short("Althea of Pishe")
            set_main_plural("Altheas of Pishe")
            set_long("This is Althea, an Archcardinal of Pishe.  She is a beautiful, "
            "middle-aged woman with a kind face.  She almost seems to glow "
            "with a gentle power.\n")
            add_adjective(({"arch", "cardinal", "of", "pishe"}))
            add_alias(({"priestess", "archcardinal", "cardinal"}))
            add_property("determinate","")
            add_property("unique", 1)
            set_gender("female")
            set_race("human")
            set_class("priest")
            set_deity("pishe")
            set_level(400)
            set_height(140)
            set_weight(1000)
            set_al(-2000 - random(501))
            set_con(15)
            set_dex(13)
            set_int(12)
            set_str(15)
            set_wis(20)
            add_skill_level("fighting", 300, 0)
            add_skill_level("fighting.combat.melee.blunt", 150, 0)
            add_skill_level("faith", 200)
            add_skill_level("faith.rituals.misc.area", 300)
            add_skill_level("other.perception", 400, 0)
            add_skill_level("other.health", 200, 0)
            add_known_command("strike")
            add_known_command("crush")
            add_spell("cure light wounds", "/obj/rituals/curelight", "cast_spell")
            add_spell("cure serious wounds", "/obj/rituals/cureserious", "cast_spell")
            add_spell("cure critical wounds", "/obj/rituals/curecritical", "cast_spell")
            add_spell("minor shield", "/obj/rituals/minorshield", "cast_spell")
            add_spell("dust devil", "/obj/rituals/dustdevil", "cast_spell")
            add_combat_action(100, "maintenance", (: maintain_self :))
            add_combat_action(70, "fighting_stuff", (: fighting_stuff :))
            add_combat_action(50, "ritual_stuff", (: ritual_stuff :))
            ARMOURY.request_item("white cotton tunic", 100)->move(self)
            ARMOURY.request_item("rope belt", 100)->move(self)
            ARMOURY.request_item("soft leather shoes", 100)->move(self)
            clone_object("/obj/faith/pishe_symbol.ob")->move(self)
            do_command("tactics response parry")
            do_command("tactics attitude defensive")
            load_chat(20, [2, ":smiles kindly.",
            1, "'May the countenance of Pishe rain upon you.",
            2, ":smiles serenely."])
            load_a_chat(20, [1, "'Do you know who I am?",
            1, "'May the power of Pishe strike you down.",
            1, "'Die unbeliever!",
            1, "'You fight me, you fight Pishe herself",
            1, "'Pishe! Aid your loyal servant!"])
            set_virtual_move(1)
            set_move_after(30, 120)
            add_move_zone("Waterdeep")
            add_move_zone("Temple")
            set_wimpy(10)
            add_respond_to_with(["@say",
            [["heal", "healing"], "please"]], (: do_heal :))
            add_respond_to_with(["@say",
            ["please", "heal", "me"]], (: do_heal :))
            add_respond_to_with(["@smile", "althea"], "smile $hname$")
            add_respond_to_with([["@bow", "@curtsey"], "althea"],
            "curtsey $hname$")
            add_enter_commands((: check_injured :))
            flail = ARMOURY.request_item("cleric rod", 100)
            flail.set_enchant(flail->query_max_enchant() / 2)
            flail.whichone(7)
            flail.move(self)
            asyncio.create_task(self.(: init_equip :), 2)
            move("/d/classs/priests/Waterdeep/small-gods/old/PriestGardenStatue", "$N walk$s into the "
            "room, smiling serenely.")


    def maintain_self(self, thing1: MudObject, thing2: MudObject) -> None:
            if (thing2 != self)
            return
            if (query_holding(.index(flail) if flail in query_holding( else -1) == -1) {
            queue_command("get flail")
            queue_command("hold flail")


    def fighting_stuff(self, thing1: MudObject, thing2: MudObject) -> None:
            if (thing2 != self)
            return
            if ( random( 10 ) )
            return
            do_command("concentrate " + thing1.query_name())
            do_command("tactics attitude offensive" )
            do_command("crush "+ thing1.query_name() + " with flail")


    def ritual_stuff(self, thing1: MudObject, thing2: MudObject) -> None:
            if (thing2 != self)
            return
            switch (random(6)) {
            case 0..1:
            do_command( "cast minor shield on althea" )
            break
            case 2 .. 4 :
            do_command("cast dust devil on althea")
            do_command("cast dust devil on althea")
            do_command("cast dust devil on althea")
            break
            case 5 :
            do_command("use flail to cast fear on " + thing1.query_name())
            break


    def do_heal(self, victim: MudObject) -> None:
            if (query_attacker_list(.index(victim) if victim in query_attacker_list( else -1) != -1) {
            do_command("say I'm not going to heal you!")
            return


    def check_injured(self, ) -> None:
            object *people, person
            people = filter(all_inventory(environment()), (: living($1) &&
            ($1.query_hp() < ($1.query_max_hp() / 2)) &&
            $1.query_al() < -300 :))
            people -= [self]
            if (!sizeof(people))
            return
            person = people[random(sizeof(people))]
            do_command("say Oh my, " + person.short()+ " you don't look so good.")
            do_command("say Allow me to heal you.")
            asyncio.create_task(self.(: do_heal($1) :), 1, person)


    def event_fight_in_progress(self, attacker: MudObject, victim: MudObject) -> None:
            if ( attacker != self && victim.query_name() == "dickens" ) {
            if ( !dickens_warned ) {
            do_command( "say Fear not, Dickens, Pishe"
            " shall protect you!" )
            dickens_warned = 1
            do_command( "protect dickens" )
            attack_ob( attacker )


    def adjust_hp(self, hp: int, attacker: MudObject) -> int:
            int result
            result = ::adjust_hp(hp, attacker)
            if(hp < -1500)
            asyncio.create_task(self."eek", 0)
            return result


    def eek(self, ) -> None:
            init_command("use flail to cast sanctuary", 1)
            init_command("cast cure critical wounds on althea", 2)
            run_away()


    def check_fumble(self, ob: MudObject) -> None:
            if ( environment( ob ) == environment() ) {
            do_command( "say Whoops, I must have dropped my precious flail!" )
            do_command( "get " + file_name( ob ) )
            do_command( "hold " + file_name( ob ) )


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            ::event_enter( ob, mess, from )
            if ( environment( ob ) == environment() &&
            ob.id( "flail" ) && ob.query_cloned_by() == "althea" ) {
            asyncio.create_task(self. (: check_fumble :), 1, ob )



class Althea(MudObject):
