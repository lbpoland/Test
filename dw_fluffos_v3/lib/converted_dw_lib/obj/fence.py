# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fence.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def query_cont(self, ) -> MudObject:
            return cont


    def __init__(self):
            self.cont = clone_object( "/std/container" )


    def init(self, ) -> None:
            ::init()
            this_player()->add_command( "fence", self,
            "<indirect:object:me> to <direct:object>" )


    def dest_me(self, ) -> None:
            if( cont )
            cont.dest_me()
            ::dest_me()


    def reset(self, ) -> None:
            object ob
            if( this_offer )
            return
            foreach( ob in all_inventory( cont ) )
            ob.dest_me()


    def check_cont(self, ) -> None:
            if ( !cont )
            cont = clone_object( "/std/container" )


    def set_fence_type(self, str: str) -> None:
            fence_type = str


    def query_cost(self, thing: MudObject, buyer: MudObject) -> int:
            return (int)thing.query_value_at( self )


    def cost_string(self, thing: MudObject, place: str, buyer: MudObject) -> str:
            return (string)MONEY_HAND.money_value_string( query_cost( thing, buyer ),
            place )


    def query_item_type(self, ob: MudObject) -> str:
            if( ob.query_plurals(.index( "weapons") if  "weapons" in ob.query_plurals( else -1) != -1 )
            return "weapons"
            if( ob.query_plurals(.index( "jewellery") if  "jewellery" in ob.query_plurals( else -1) != -1 ||
            ob.query_property( "shop type" ) == "jewellers" )
            return "jewellery"
            if( ob.query_plurals(.index( "armours") if  "armours" in ob.query_plurals( else -1) != -1 )
            return "armour"
            if( ob.query_plurals(.index( "clothes") if  "clothes" in ob.query_plurals( else -1) != -1 )
            return "armour"
            if( ob.query_plurals(.index( "gems") if  "gems" in ob.query_plurals( else -1) != -1 )
            return "gems"
            return ""


    def judge_value(self, ob: MudObject, type: str) -> int:
            int value, variance, skill
            value = query_cost( ob, self )
            if( type != "" )
            skill = query_skill_bonus( SKILL + "." + type )
            else
            skill = query_skill_bonus( SKILL )
            if( !skill )
            skill = 1
            variance = value / sqrt( skill )
            value += random( variance ) - random( variance )
            return value


    def calc_place(self, ) -> str:
            string place
            place = environment()->query_property( "place" )
            if( !place || ( place == "" ) )
            place = "Waterdeep"
            return place


    def cost_str(self, amt: int) -> str:
            return MONEY_HAND->money_string( MONEY_HAND->create_money_array( amt,
            calc_place() ) )


    def scaled_value(self, n: int) -> int:
            int *fish, i, tot
            fish = PAY_RATES
            if( n < fish[0] ) {
            return n


    def do_yes(self, person: MudObject) -> None:
            object money, *selling, ob
            mixed *m_array
            string zone
            if( !this_offer || person != this_offer->who )
            return
            whisper( person, "You've got a deal." )
            selling = [})
            foreach( ob in this_offer->objects ) {
            ob.add_property( "fenced", (string)person.query_name() )
            selling += [ob]


    def do_no(self, player: MudObject) -> None:
            string zone
            object customer, thing
            int returned, burdened
            if( !this_offer || player != this_offer->who )
            return
            whisper( player, "Ok, have it your own way then." )
            customer = this_offer->who
            burdened = 0
            returned = 0
            foreach( thing in this_offer->objects ) {
            if( !thing ) {
            whisper( customer, "Seems thare is a hole in my sack!" )
            continue


    def whisper(self, ob: MudObject, message: str) -> None:
            do_command( "whisper " + message + " to " + ob.query_name() )


    def busy(self, ) -> int:
            if( this_offer )
            return 1
            return 0


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            object customer, thing
            int returned, burdened
            if( this_offer &&
            ob == this_offer->who ) {
            whisper( ob, "Since you're leaving, I'll give your stuff back." )
            customer = this_offer->who
            burdened = 0
            returned = 0
            foreach( thing in this_offer->objects ) {
            if( !thing ) {
            whisper( customer, "Seems thare is a hole in my sack!" )
            continue


    def attack_by(self, ob: MudObject) -> int:
            int burdened, returned
            object customer, thing
            if( this_offer &&
            this_offer->who &&
            environment( this_offer->who ) == environment( self ) &&
            this_offer->offer_time > time() - 60 ) {
            do_command( "say Hey! I'm trying to do business here!" )
            whisper( this_offer->who, "Hey, you'd better take these." )
            customer = this_offer->who
            burdened = 0
            returned = 0
            foreach( thing in this_offer->objects ) {
            if( !thing ) {
            whisper( customer, "Seems thare is a hole in my sack!" )
            continue


    def give_back(self, ) -> None:
            int burdened, returned
            object customer, thing
            customer = this_offer->who
            burdened = 0
            returned = 0
            foreach( thing in this_offer->objects ) {
            if( !thing ) {
            whisper( customer, "Seems thare is a hole in my sack!" )
            continue


    def query_current_offer(self, ) -> str:
            string str
            str = "\nCustomer: " + ( this_offer->who )->short()  + "\n"
            str += "Amount: " + this_offer->amount + "\n"
            str += "Offer time: " + this_offer->offer_time + "\n"
            str += "Objects: " + query_multiple_short( this_offer->objects )
            return str



class Fence(MudObject):

    cont = 'clone_object( "/std/container" )'
