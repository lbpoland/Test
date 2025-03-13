# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/dummy.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def query_trainer(self, ) -> MudObject:
            return trainer


    def reset_trainer(self, ) -> MudObject:
            trainer = 0


    def set_trainer(self, thing: MudObject) -> MudObject:
            return trainer = thing


    def query_trainee(self, ) -> MudObject:
            return trainee


    def reset_trainee(self, ) -> MudObject:
            trainee = 0


    def set_trainee(self, thing: MudObject) -> MudObject:
            return trainee = thing


    def query_skill_bonus(self, words: str) -> int:
            return 10


    def setup(self, ) -> None:
            set_name( "dummy" )
            add_adjective( ["wood", "wooden", "training"] )
            set_short( "training dummy" )
            set_long( "A fighters dummy.  It is looking pretty donned in Faerûn from having "+
            "all the stuffing knocked out of it all day.\n")
            basic_setup( "human", "warrior", 10 )
            set_gender( 0 )
            add_property( "run away", -1 )
            set_dex(6)
            set_str(6)
            set_con(18)
            set_int(6)
            set_wis(6)
            remove_ac( "sharp" )
            remove_ac( "pierce" )
            remove_ac( "blunt" )
            remove_ac( "unarmed" )
            add_skill_level( "other.health", 1000 )
            add_combat_action( 100, "spin_arm", (: spin_arm :) )
            ARMOURY.request_item( "dirty rags", 30 )->move( self )


    def attack_this_time(self, ) -> int:
            return 0


    def init(self, ) -> None:
            if( this_player() ) {
            this_player()->add_command( "kill", self, "{dummy}",
            (: assault_dummy() :) )
            this_player()->add_command( "attack", self, "{dummy}",
            (: assault_dummy() :) )


    def assault_dummy(self, ) -> int:
            object *weapons, weapon
            int i
            if( trainer.query_fighting() ) {
            write( "You beat at and tear up " + self.the_short() +
            " for a while until you get bored.\n" )
            say( this_player()->query_short() + " hacks at " +
            self.the_short() + " for a while.\n", this_player() )


    def attack_by(self, ob: MudObject) -> int:
            if(!sizeof(query_specials()))
            asyncio.create_task(self."attack_dummy", 0)
            return ::attack_by(ob)


    def spin_arm(self, newbie: MudObject, dumdum: MudObject) -> None:
            int diff, which, failed
            if( environment( newbie ) != environment( self ) )
            return
            switch( ( ( class tactics )newbie.query_tactics() )->attitude ) {
            case "offensive":
            diff = DIFF + MOD
            break
            case "defensive":
            diff = DIFF - MOD
            break
            default:
            diff = DIFF


    def tell_misc(self, newbie: MudObject) -> None:
            int which
            if(!sizeof(misc) || random(5))
            return
            which = random(sizeof(misc))
            trainer.do_command("say " + misc[which])
            misc -= [misc[which]]


    def failed_attack(self, newbie: MudObject) -> None:
            string attitude
            if(told_attack)
            return
            attitude = (newbie.query_tactics())->attitude
            if(attitude != "offensive" && attitude != "insane") {
            told_attack = 1
            trainer->do_command( "say You can improve your chances of hitting your "
            "opponent by setting your tactics to a more "
            "offensive attitude.")


    def failed_defense(self, newbie: MudObject) -> None:
            string attitude
            if(told_parry)
            return
            attitude = (newbie.query_tactics())->attitude
            if(attitude != "defensive" && attitude != "wimp") {
            told_parry = 1
            trainer->do_command( "say You can improve your chances of defending by "
            "setting your tactics to a more defensive "
            "attitude." )


    def adjust_hp(self, ) -> None:
            return self.query_max_hp()



class Dummy(MudObject):
