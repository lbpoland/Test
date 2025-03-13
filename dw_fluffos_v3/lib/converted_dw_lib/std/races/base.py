# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.sight = ['5', '20', '200', '300']
            self.stats = allocate( 5 )
            self.desc = "a small non-descript thing"
            self.inedible = []
            self.unrottable = []
            self.pluckable = []
            self.acs = []
            self.attacks = []
            self.bits = []


    def query_dark(self, light: int) -> int:
            if ( light < sight[ 0 ] ) {
            return -2


    def query_desc(self, thing: MudObject) -> str:
            return capitalize( (string)thing.query_pronoun() ) +" is "+ desc +".\n"


    def set_desc(self, words: str) -> None:
            string *query_limbs() {
            if ( !limbs ) {
            self.find_limbs()


    def find_limbs(self, ) -> None:
            int i
            string limb
            limbs = [})
            for ( i = 0; i < sizeof( bits ); i += 3 ) {
            if ( sscanf( bits[ i ], "%s hand", limb ) == 1 ) {
            limbs += [bits[ i ]]


    def add_ac(self, ac_name: str, ac_type: str, ac_amount: Any) -> None:
            acs += [ac_name, ac_type, ac_amount]


    def add_attack(self, attack_name: str, attack_chance: int, attack_data: int) -> None:
            attacks += [attack_name, attack_chance, attack_data]


    def add_bit(self, bit_short: str, bit_name: str, bit_array: Any) -> None:
            int i
            i = bits .index( bit_short) if  bit_short in bits  else -1
            if ( !( i % 3 ) ) {
            bits[ i ] = bit_short
            bits[ i + 1 ] = bit_name
            bits[ i + 2 ] = bit_array
            return


    def remove_bit(self, word: str) -> None:
            int i
            i = bits .index( word) if  word in bits  else -1
            if ( ( i == -1 ) || ( i % 3 ) ) {
            return


    def modifier(self, number: int) -> int:
            return ( number * ( roll_MdN( 20, 21 ) - 220 ) ) / 2000


    def start_player(self, thing: MudObject) -> None:
            if ( !thing.query_base_weight() ) {
            thing.set_base_weight( 1 + weight + modifier( weight ) )


    def query_number_worn(self, type: str) -> int:
            switch ( type ) {
            case "armband" :
            return 2
            case "badge" :
            return 15
            case "bracelet" :
            return 4
            case "earring" :
            return 2
            case "garter" :
            return 2
            case "shoulder" :
            return 2
            case "necklace" :
            return 5
            case "ring" :
            return 8
            case "sash" :
            return 2
            case "shirt" :
            return 2
            case "belt scabbard" :
            return 2
            case "small scabbard" :
            return 2
            case "bandaid" :
            return 5
            default :
            return 1


    def set_level(self, thing: MudObject, level: int) -> None:
            int i
            if ( !thing ) {
            return


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int i, number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number )
            for ( i = sizeof( attacks ) - 3; i > -1; i -= 3 ) {
            thing.remove_attack( attacks[ i ] )
            thing->add_attack( attacks[ i ], attacks[ i + 1 ],
            calc_attack( attacks[ i + 2 ], number ), A_TYPES[ attacks[ i ] ],
            "unarmed", "unarmed_"+ attacks[ i ] )


    def query_eat(self, bit: str) -> int:
            if (inedible.index( bit) if  bit in inedible else -1 == -1) {
            return 1


    def query_unrottable(self, bit: str) -> int:
            if (unrottable.index( bit) if  bit in unrottable else -1 == -1) {
            return 0


    def query_pluckable(self, bit: str) -> int:
            if (pluckable.index( bit) if  bit in pluckable else -1 == -1) {
            return 0


    def map_target_zone(self, zone: str) -> str:
            switch(zone) {
            case "abdomen":
            return "stomach"
            case "hands":
            case "arms":
            return (random(2) ? "left " : "right ") + "front leg"
            case "feet":
            case "legs":
            return (random(2) ? "left " : "right ") + "rear leg"
            default:
            return zone


    def map_armour_zone(self, zone: str) -> str:
            switch(zone) {
            case "thorax":
            case "body":
            case "breast":
            case "trunk":
            return "chest"
            case "tail":
            return "back"
            case "stomach":
            return "abdomen"
            case "left arm":
            case "right arm":
            case "left front leg":
            case "right front leg":
            case "left petral fin":
            case "right petral fin":
            case "left wing":
            case "right wing":
            case "branches":
            return "arms"
            case "left hand":
            case "right hand":
            case "left middle leg":
            case "right middle leg":
            case "left front paw":
            case "right front paw":
            return "hands"
            case "left leg":
            case "right leg":
            case "left back leg":
            case "right back leg":
            case "left rear leg":
            case "right rear leg":
            case "dorsal fin":
            return "legs"
            case "left foot":
            case "right foot":
            case "left rear paw":
            case "left rear paw":
            case "left rear foot":
            case "left rear foot":
            case "left claw":
            case "right claw":
            case "root":
            return "feet"
            default:
            return zone



class Base(MudObject):

    sight = "['5', '20', '200', '300']"

    stats = 'allocate( 5 )'

    desc = '"a small non-descript thing"'

    inedible = '[]'

    unrottable = '[]'

    pluckable = '[]'

    acs = '[]'

    attacks = '[]'

    bits = '[]'
