# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/shopkeeper.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):


    def attack_by(self, baddie: MudObject) -> None:
            {
            if (_office == "") return
            self.stop_fight(baddie)
            baddie.stop_fight(self)
            do_command("'Why are you attacking me, "+ baddie.query_cap_name()+ "?")
            do_command("'I'm not staying here for this!")
            do_command(_office.query_channel()+ "@ is being attacked by "+
            baddie.query_cap_name()+ ".")
            asyncio.create_task(self."shuffle_to", NPC_DELAY, _office, (: end_shift() :))
            _office.event_death(self, 0, baddie, 0, 0)
            #ifdef DEBUG
            tell_creator(CREATOR,  "Attacked by %s.\n", baddie.query_short())
            #endif


    def do_buy(self, stuff: str) -> int:
            {
            #ifdef DEBUG
            tell_creator(CREATOR,  "In do_buy()\n")
            #endif
            if (outside_hours(TRUE)) return 1
            say_to_room(this_player(), "say", "I would like to buy "+ stuff +
            ", please.\n%^RESET%^")
            if (query_busy())
            init_command(":seems busy at the moment.", NPC_DELAY)
            else
            {
            set_busy(this_player())
            asyncio.create_task(self.(: sell_something($(stuff)) :), NPC_DELAY)


    def do_browse(self, item: str) -> int:
            {
            #ifdef DEBUG
            tell_creator(CREATOR,  "In do_browse()\n")
            #endif
            if (outside_hours(TRUE)) return 1
            say_to_room(this_player(), "ask", "How much do "+ item +" cost?\n")
            if (query_busy())
            init_command(":seems busy at the moment.", NPC_DELAY)
            else
            {
            set_busy(this_player())
            asyncio.create_task(self.(: how_much($(item)) :), NPC_DELAY)


    def do_list(self, args: Any) -> int:
            {
            #ifdef DEBUG
            tell_creator(CREATOR,  "In do_list()\n")
            #endif
            if (outside_hours(TRUE)) return 1
            if (!sizeof(args) || !args[0] || args[0] == "")
            {
            say_to_room( this_player(), "ask", "What items do you buy and sell?\n")
            if (query_busy())
            init_command(":seems busy at the moment.", NPC_DELAY)
            else
            {
            set_busy(this_player())
            asyncio.create_task(self.(: what_items() :), NPC_DELAY)


    def do_sell(self, obs: MudObject) -> int:
            {
            #ifdef DEBUG
            tell_creator(CREATOR,  "In do_sell()\n" )
            #endif
            if (outside_hours(TRUE)) return 1
            say_to_room(this_player(), "say", "I would like to sell " +
            query_multiple_short(obs, "the")+ ", please.\n%^RESET%^")
            if (query_busy())
            init_command(":seems busy at the moment.", NPC_DELAY)
            else
            {
            set_busy(this_player())
            asyncio.create_task(self.(: buy_something($(obs)) :), NPC_DELAY)


    def event_person_say(self, thing: MudObject, start: str, mess: str, lang: str) -> None:
            {
            string words
            #ifdef DEBUG
            tell_creator(CREATOR,  "In event_person_say()\n" )
            #endif
            if (outside_hours(TRUE)) return
            if (!mess || (mess == "")) return
            mess = lower_case(mess)
            if (query_busy()) return
            set_busy(thing)
            if (sscanf(mess, "%*s buy %s, please.", words) == 2)
            {
            asyncio.create_task(self.(: sell_something($(words)) :), NPC_DELAY)
            return


    def init(self, ) -> None:
            {
            object tp = this_player()
            #ifdef DEBUG
            tell_creator(CREATOR,  "In init()\n" )
            #endif
            if (environment(self) == find_object("/room/rubbish")) return
            #ifdef DEBUG
            tell_creator(CREATOR,  "Not in /room/rubbish\n")
            #endif
            ::init()
            tp.add_command("buy", self, "<string'item(s)'>",
            (: do_buy($4[0]) :))
            tp->add_command("sell", self, "<indirect:object:me>",
            (: do_sell($1) :))
            tp.add_command("list", self, ({"", "<string'item(s)'>"}),
            (: do_list($4) :))
            tp.add_command("browse", self, "<string'item(s)'>",
            (: do_browse($4[0]) :))
            outside_hours(TRUE)


    def query_office(self, {: Any) -> str:
            private void say_to_room(object me, string t, string message)
            {
            await me.send("You "+ t+ ": "+ message)
            foreach(object player in all_inventory(environment(self)))
            if (interactive(player) && player != me)
            await player.send(player.colour_event("say", "%^CYAN%^")+
            me.query_short()+ " "+ t + "s: "+ message)


    def set_failed(self, failed: int) -> None:
            protected void set_office(string path)
            {
            mapping values
            string new_key
            _office = path
            _place = _office.query_place()
            _smallest_in = MONEY_HAND.smallest_in( _place )
            _smallest_value_in = MONEY_HAND.smallest_value_in(_place)
            _smallest_plural_in = MONEY_HAND.query_plural_for(_smallest_in)
            values = MONEY_HAND.query_mapped_values_in(_place)
            foreach(string key in keys(values))
            {
            new_key = MONEY_HAND.query_aliases_for(key)[0]
            _values_sing += ([new_key:values[key]])
            new_key = MONEY_HAND.query_details_for(key)[5]
            _values_plural += ([new_key:values[key]])


    def shuffle_to(self, location: str, next_action: Any) -> None:
            {
            string direc = environment()->directions_to(location)
            if (!direc)
            {
            if (environment() == find_object("/room/rubbish")) return
            if (environment() == _shop_front.query_outside())
            {
            move(_shop_front, "$N enter$s the shop.",
            "$N enter$s _shop_front.query_short().")


    def start_shift(self, ) -> None:
            {
            #ifdef DEBUG
            tell_creator(CREATOR,  "In start_shift()\n" )
            #endif
            if (outside_hours(FALSE)) return
            set_busy(self)
            move(_office, "$N arrive$s for " + query_possessive()+ " shift.")
            if (_office.query_employee(query_name()) & CLOCKED_IN)
            do_command("clock out")
            do_command("claim badge")
            do_command("wear badge")
            do_command("clock in")
            do_command(_office.query_channel()+ "@ is clocking in.")
            asyncio.create_task(self."shuffle_to", NPC_DELAY, _shop_front, 0)



class Shopkeeper(MudObject):
