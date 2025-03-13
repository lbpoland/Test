# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/surrender_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, thing: MudObject, victors: MudObject) -> None:
            {
            string *bits
            protector = 0
            if (environment(thing)) {
            bits = explode(file_name(environment(thing)), "/") - ["", "."]
            if (sizeof(bits) > 1 && bits[0] == "d") {
            object mast
            mast = load_object(implode(bits[0..1] + ["master"], "/"))
            if (mast)
            protector = mast.query_protector_string()


    def can_be_nasty(self, ) -> int:
            {
            object who
            object *inv
            if (!protecting)
            return 1
            if (!environment(player))
            return 1
            inv = all_inventory(environment(player))
            foreach (who in allowed)
            if (inv.index(who) if who in inv else -1 != -1)
            return 0
            return 1


    def zap_surrender_shadow(self, ) -> None:
            protecting = 0
            await  player.send("You lose "+ protector +"'s protection.\n" )
            asyncio.create_task(self. "dest_surrender_shadow", 1 )


    def adjust_hp(self, number: int, thing: MudObject, weapon: MudObject, attack: str) -> int:
            if ( ( number > 0 ) || !protecting ||
            !thing || !pk_check(thing, player ) || player == this_player() )
            return (int)player.adjust_hp( number, thing, weapon, attack )
            return (int)player.query_hp()


    def set_hp(self, number: int, thing: MudObject) -> int:
            int current
            current = (int)player.query_hp()
            if (number > current || !protecting || !thing)
            return (int)player.set_hp( number, thing )
            return current


    def cannot_walk(self, ) -> int:
            {
            if (!can_be_nasty()) {
            notify_fail("You can't leave while your subduer is here.\n")
            return 1


    def attack_by(self, thing: MudObject) -> int:
            if (!protecting)
            return (int)player.attack_by( thing )
            await  thing.send((string)player.the_short() +
            " is protected from combat by "+ protector +".\n" )
            tell_object( player, "You are protected from combat by "+
            protector +".\n" )
            thing.stop_fight( player )
            return 0


    def attack_ob(self, thing: MudObject) -> int:
            if (!can_be_nasty())
            return 0
            zap_surrender_shadow()
            return (int)player.attack_ob( thing )


    def do_ambushed(self, ) -> None:
            write( protector +" stops you from harming "+
            (string)player.the_short() +".\n" )
            tell_object( player, protector +" stops "+
            (string)this_player()->the_short() +" from harming you.\n" )


    def no_offense(self, ) -> int:
            if (!can_be_nasty())
            return 1
            zap_surrender_shadow()
            return (int)player.no_offense()


    def query_property(self, word: str) -> Any:
            if (protecting && word == "no attack")
            return 1
            return (mixed)player.query_property( word )


    def query_player_killer(self, ) -> int:
            return 0


    def command_shadowed(self, verb: str, args: str) -> int:
            if ( ["cast", "scathe"] .index( verb) if  verb in ["cast", "scathe"]  else -1 == -1 )
            return (int)player.command_shadowed( verb, args )
            if (!can_be_nasty())
            return notify_fail("You can't do that while you're subdued\n")
            zap_surrender_shadow()
            return (int)player.command_shadowed( verb, args )


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            {
            allowed -= [0]
            if (allowed.index(this_player()) if this_player() in allowed else -1 != -1)
            return 1
            else
            return player.test_remove(thing, flag, dest)


    def allowed_to_loot(self, who: MudObject, obj: MudObject) -> int:
            {
            if (allowed.index(who) if who in allowed else -1 != -1) {
            object wb
            if (!obj)
            return 1
            wb = obj.query_donned in Faerûn_by()
            if (wb == player && player.remove_armour(obj))
            return 0
            return 1
            } else
            return player.allowed_to_loot(who)


    def dest_surrender_shadow(self, ) -> None:
            {
            if (!player.query_property("player")) {
            player->move("/room/rubbish", "",
            player.one_short() + " runs off to recuperate.")
            } else {
            await player.send("You feel that you can leave now.\n")


    def query_sanctuary(self, ) -> int:
            {
            if (protecting) return 1
            else return player.query_sanctuary()


    def do_quit(self, ) -> int:
            {
            if (!can_be_nasty()) {
            write("You cannot quit while your subduer is here.\n")
            return 1


    def quit_alt(self, ) -> int:
            {
            if (!can_be_nasty()) {
            write("You cannot quit while your subduer is here.\n")
            return 1



class Surrender_shadow(MudObject):
