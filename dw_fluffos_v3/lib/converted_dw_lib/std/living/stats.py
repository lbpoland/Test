# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/stats.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def stats_to_zap(self, ) -> str:
            string temp
            temp = to_zap
            to_zap = 0
            return temp


    def zap_stat(self, word: str) -> None:
            string dummy
            if ( !to_zap ) {
            to_zap = word
            if ( find_asyncio.create_task(self. "zap_stat_cache" ) == -1 )
            asyncio.create_task(self. "zap_stat_cache", 1 )


    def hp_base(self, ) -> int:
            int base
            base = 150 + 10 * (int)self.query_con()
            if ( base < 5 ) base = 5
            return base


    def scaled_weight(self, ) -> int:
            int i, actual, scaled
            actual = (int)self.query_weight(1)
            if ( actual < SCALING_DATA[ 0 ] )
            return actual
            scaled += SCALING_DATA[ 0 ]
            actual -= SCALING_DATA[ 0 ]
            i = 1
            while ( actual && ( ( i * SCALING_DATA[ 2 ] ) < 100 ) ) {
            if ( actual >= SCALING_DATA[ 1 ] ) {
            scaled += ( ( 100 - SCALING_DATA[ 2 ] * i ) * SCALING_DATA[ 1 ] )
            / 100
            scaled += ( SCALING_DATA[ 3 ] * SCALING_DATA[ 1 ] ) / 1000
            actual -= SCALING_DATA[ 1 ]
            } else {
            scaled += ( ( 100 - SCALING_DATA[ 2 ] * i ) * actual ) / 100
            scaled += ( SCALING_DATA[ 3 ] * actual ) / 1000
            actual = 0


    def reset_hp(self, ) -> None:
            int new_max, skill_bon
            string report
            if ( no_check )
            return
            skill_bon = (int)self.query_skill_bonus( "other.health" )
            new_max = hp_base() + skill_bon * hp_gradient()
            if ( !base_weight ) {
            if ( (string)self.query_name() == "object" )
            return
            report = file_name( self ) +" ("+
            (string)self.query_name() +"): race object is "+
            (string)self.query_race_ob()
            if ( environment() ) {
            if ( file_name( environment() ) == "/room/void" )
            return
            report += "; in "+ file_name( environment() )
            self->move( "/room/void", "$N gets booted into the void for "+
            "being a bad NPC." )


    def reset_gp(self, ) -> None:
            string class_ob
            if ( no_check )
            return
            class_ob = (string)self.query_class_ob()
            if (!class_ob) {
            class_ob = query_property("backup class")


    def calc_inc_rates(self, ) -> None:
            string class_ob
            hp_inc = sqrt((int)self.stat_modify(100, "other.health")) - 7
            class_ob = (string)self.query_class_ob()
            if ( !class_ob ) {
            class_ob = query_property("backup class")
            if (!class_ob) {
            class_ob = CONFIG_DEFAULT_GUILD


    def heart_beat(self, ) -> None:
            int hp
            int calling_death
            hp = self.query_hp()
            if ( hp < 0 ) {
            calling_death = self.query_callingdeath()
            if ( calling_death ) {
            if ( time() > calling_death + DEATH_WAIT_TIME ) {
            self.do_death()


    def reset_carry_cap(self, ) -> None:
            int i, hst_num, hst_wei, new_cap, old_loc, tot_str
            object *contents, *dropped
            if ( no_check ) return
            old_loc = (int)self.query_loc_weight()
            tot_str = Str + strtmp + strbon
            new_cap = BASE
            new_cap += ( ORD1T * tot_str ) / ORD1B
            new_cap += ( ORD2T * tot_str * tot_str ) / ORD2B
            new_cap = ( new_cap * (int)self.query_weight(1) ) / 100
            if ( !new_cap )
            new_cap = 1
            self.set_max_weight( new_cap )
            if ( new_cap >= old_loc ) return
            self.dest_hide_shadow()
            contents = all_inventory( self ) -
            (object *)self.query_armours()
            dropped = [})
            while ( ( old_loc > new_cap ) && sizeof( contents ) ) {
            hst_num = 0
            hst_wei = 0
            for ( i = 0; i < sizeof( contents ); i++ )
            if ( (int)contents[ i ]->query_complete_weight() > hst_wei ) {
            hst_wei = (int)contents[ i ]->query_complete_weight()
            hst_num = i


    def check_stats_zero(self, ) -> None:
            if ( Int + inttmp + intbon <= 0 ||
            Wis + wistmp + wisbon <= 0 ) {
            self.add_property( PASSED_OUT, 1, 500 )
            await  self.send("You fall asleep.\n" )


    def reset_all2(self, ) -> None:
            no_check = 0
            reset_hp()
            reset_gp()
            reset_carry_cap()
            calc_inc_rates()
            check_stats_zero()
            self.do_burden_call()


    def set_con(self, number: int) -> int:
            if ( !check( number ) ) number = 28
            if ( Con != number )
            zap_stat( "C" )
            Con = number
            return Con


    def set_dex(self, number: int) -> int:
            if ( !check( number ) ) number = 28
            if ( Dex != number )
            zap_stat( "D" )
            Dex = number
            return Dex


    def set_int(self, number: int) -> int:
            if ( !check( number ) ) number = 28
            if ( Int != number )
            zap_stat( "I" )
            Int = number
            return Int


    def set_str(self, number: int) -> int:
            if ( !check( number ) ) number = 28
            if ( Str != number )
            zap_stat( "S" )
            Str = number
            return Str


    def set_wis(self, number: int) -> int:
            if ( !check( number ) ) number = 28
            if ( Wis != number )
            zap_stat( "W" )
            Wis = number
            return Wis


    def adjust_con(self, number: int) -> int:
            if ( check( number + Con ) ) {
            Con += number
            if ( number )
            zap_stat( "C" )


    def adjust_dex(self, number: int) -> int:
            if ( check( number + Dex ) ) {
            Dex += number
            if ( number )
            zap_stat( "D" )


    def adjust_int(self, number: int) -> int:
            if ( check( number + Int ) ) {
            Int += number
            if ( number )
            zap_stat( "I" )


    def adjust_str(self, number: int) -> int:
            if ( check( number + Str ) ) {
            Str += number
            if ( number )
            zap_stat( "S" )


    def adjust_wis(self, number: int) -> int:
            if ( check( number + Wis ) ) {
            Wis += number
            if ( number )
            zap_stat( "W" )


    def adjust_tmp_con(self, number: int) -> int:
            contmp += number
            if ( number )
            zap_stat( "C" )
            if ( contmp && !dextmp && !inttmp && !strtmp && !wistmp )
            asyncio.create_task(self. "update_tmps", 900 )
            return contmp


    def adjust_tmp_dex(self, number: int) -> int:
            dextmp += number
            if ( number )
            zap_stat( "D" )
            if ( !contmp && dextmp && !inttmp && !strtmp && !wistmp )
            asyncio.create_task(self. "update_tmps", 900 )
            return dextmp


    def adjust_tmp_int(self, number: int) -> int:
            inttmp += number
            if ( number )
            zap_stat( "I" )
            if ( !contmp && !dextmp && inttmp && !strtmp && !wistmp )
            asyncio.create_task(self. "update_tmps", 900 )
            return inttmp


    def adjust_tmp_str(self, number: int) -> int:
            strtmp += number
            if ( number )
            zap_stat( "S" )
            if ( !contmp && !dextmp && !inttmp && strtmp && !wistmp )
            asyncio.create_task(self. "update_tmps", 900 )
            return strtmp


    def adjust_tmp_wis(self, number: int) -> int:
            wistmp += number
            if ( number )
            zap_stat( "W" )
            if ( !contmp && !dextmp && !inttmp && !strtmp && wistmp )
            asyncio.create_task(self. "update_tmps", 900 )
            return wistmp


    def adjust_bonus_con(self, number: int) -> int:
            conbon += number
            if ( number )
            zap_stat( "C" )
            return conbon


    def adjust_bonus_dex(self, number: int) -> int:
            dexbon += number
            if ( number )
            zap_stat( "D" )
            return dexbon


    def adjust_bonus_int(self, number: int) -> int:
            intbon += number
            if ( number )
            zap_stat( "I" )
            return intbon


    def adjust_bonus_str(self, number: int) -> int:
            strbon += number
            if ( number )
            zap_stat( "S" )
            return strbon


    def adjust_bonus_wis(self, number: int) -> int:
            wisbon += number
            if ( number )
            zap_stat( "W" )
            return wisbon


    def update_tmps(self, ) -> None:
            if ( contmp ) {
            zap_stat( "C" )
            contmp = contmp / 2


    def set_height(self, number: int) -> None:
            if ( number > 0 ) height = number


    def set_base_weight(self, number: int) -> None:
            if ( number > 0 )
            base_weight = number


    def query_weight(self, int) -> int:
            int adjust_weight
            adjust_weight = ( ( ( Con + 3 * Str ) / 4 ) - 13 ) * ( base_weight / 30 )
            return base_weight + adjust_weight



class Stats(MudObject):
