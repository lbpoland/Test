# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/food.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._eat_effects = ([ ])


    def __init__(self):
            self._eat_effects = ([ ])


    def query_liquid(self, ) -> int:
            {
            return _liquid


    def query_edible(self, ) -> int:
            {
            return !_liquid


    def set_liquid(self, ) -> None:
            {
            set_continuous()
            _liquid = 1
            if (environment()) {
            environment()->calc_liquid()


    def reset_liquid(self, ) -> None:
            {
            reset_continuous()
            _liquid = 0
            if (environment())
            environment()->calc_liquid()
            set_decay_speed(DEFAULT_DECAY)
            _divisor = to_float(DEFAULT_DECAY) / to_float(6 * TIME_OUT)


    def query_food_object(self, ) -> int:
            {
            return 1


    def init(self, ) -> None:
            {
            if (query_continuous()) {
            add_command("rub", "<direct:object> <preposition> <indirect:living>")
            add_command("apply", "<direct:object> <preposition> <indirect:living>")


    def query_decays(self, ) -> int:
            {
            return _decay_speed != 0


    def query_bites_gone(self, ) -> int:
            {
            return _bites_gone


    def query_weight_per_bite(self, ) -> int:
            {
            return _weight_per_bite


    def query_eat_object(self, ) -> str:
            {
            return _eat_object


    def query_eat_func(self, ) -> str:
            {
            return _eat_func


    def query_eat_mess(self, ) -> str:
            {
            return _eat_mess


    def query_piece_description(self, ) -> str:
            {
            return _piece_desc


    def query_in_pieces(self, ) -> int:
            {
            return _in_pieces


    def query_decay_speed(self, ) -> int:
            {
            return _decay_speed


    def query_decay_level(self, ) -> int:
            return _decay_level


    def set_bites_gone(self, number: int) -> None:
            {
            _bites_gone = number


    def set_weight_per_bite(self, number: int) -> None:
            {
            _weight_per_bite = number


    def set_eat_object(self, word: str) -> None:
            {
            _eat_object = word


    def set_eat_func(self, word: str) -> None:
            {
            _eat_func = word


    def set_eat_mess(self, word: Any) -> None:
            {
            _eat_mess = word


    def set_piece_description(self, word: str) -> None:
            _piece_desc = word


    def set_piece_short(self, short: str) -> None:
            _piece_short = short


    def set_piece_plural(self, plural: str) -> None:
            _piece_plural = plural


    def set_piece_substance(self, substance: str) -> None:
            _piece_substance = substance


    def set_in_pieces(self, number: int) -> None:
            int p
            _in_pieces = p


    def set_decay_level(self, level: int) -> None:
            _decay_level = level


    def set_decay_speed(self, decay: int) -> None:
            float tmp
            if(decay != _decay_speed && !_dried && !_cured) {
            BITS_CONTROLLER.remove_bit(self)
            _decay_speed = decay
            if (decay && !_dried && !_cured) {
            tmp = _divisor
            _divisor = to_float(decay) / to_float(6 * TIME_OUT)
            _decay_level = to_int(_decay_level * _divisor / tmp)
            BITS_CONTROLLER.add_bit(self)


    def do_decay(self, ) -> None:
            if(_dried || _cured) {
            BITS_CONTROLLER.remove_bit(self)
            return


    def query_weight(self, ) -> int:
            if (query_liquid())
            return 0
            return ::query_weight() - _bites_gone * _weight_per_bite


    def query_short_rotten_adjective(self, ) -> str:
            string ret
            ret = ""
            switch (to_int(_decay_level / _divisor)) {
            case 2:
            ret = "slightly rotten "
            break
            case 3:
            ret = "half rotten "
            break
            case 4:
            ret = "mostly rotten "
            break
            case 5:
            ret = "almost rotten "
            break
            case 6:
            ret = "rotten "
            break


    def short(self, dark: int) -> str:
            string ret
            ret = ::short(dark)
            if (_decay_speed) {
            ret = query_short_rotten_adjective() + ret


    def query_long_eat_level(self, ) -> str:
            int twelfths
            string ret
            twelfths = (_bites_gone * _weight_per_bite * 12) / ::query_weight()
            switch (twelfths) {
            case 0..1:
            ret = "It has just been nibbled on.\n"
            break
            case 2:
            ret = "It is about one sixth gone.\n"
            break
            case 3:
            ret = "It is about one quarter gone.\n"
            break
            case 4:
            ret = "It is about one third gone.\n"
            break
            case 5:
            ret = "It is just under half gone.\n"
            break
            case 6:
            ret = "It is about half gone.\n"
            break
            case 7:
            ret = "It is just over half gone.\n"
            break
            case 8:
            ret = "It is about two thirds gone.\n"
            break
            case 9:
            ret = "It is about three quarters gone.\n"
            break
            case 10:
            ret = "It is about five sixths gone.\n"
            break
            case 11:
            ret = "It is almost all gone.\n"
            break
            default:
            ret = "Schroedinger's cat has been at it.\n"
            break


    def query_long_decay_level(self, ) -> str:
            string ret
            ret = ""
            switch (to_int(_decay_level / _divisor)) {
            case 0..1:
            if(query_collective() && query_amount() > 1)
            ret += "They look nice and fresh.\n"
            else
            ret += "It looks nice and fresh.\n"
            break
            case 2:
            if(query_collective() && query_amount() > 1)
            ret += "They look a bit rotten.\n"
            else
            ret += "It looks a bit rotten.\n"
            break
            case 3:
            if(query_collective() && query_amount() > 1)
            ret += "They are half rotten.\n"
            else
            ret += "It is half rotten.\n"
            break
            case 4:
            if(query_collective() && query_amount() > 1)
            ret += "They are mostly rotten.\n"
            else
            ret += "It is mostly rotten.\n"
            break
            case 5:
            if(query_collective() && query_amount() > 1)
            ret += "They are almost completely rotten.\n"
            else
            ret += "It is almost completely rotten.\n"
            break
            case 6:
            if(query_collective() && query_amount() > 1)
            ret += "They are completely rotten.\n"
            else
            ret += "It is completely rotten.\n"
            break


    def long(self, words: str, dark: int) -> str:
            string ret
            ret =::long(words, dark)
            if (_liquid) {
            return ret


    def setup_eat(self, ob: str, func: str) -> None:
            _eat_object = ob
            _eat_func = func


    def set_eat_effects(self, map: Any) -> None:
            if (mapp(map)) {
            _eat_effects = map


    def remove_eat_effect(self, word: str) -> None:
            {
            if (!undefinedp(_eat_effects[word])) {
            _eat_effects = m_delete(_eat_effects, word)


    def set_external_pk_check(self, ) -> None:
            {
            _external_pk_check = 1


    def unset_external_pk_check(self, ) -> None:
            {
            _external_pk_check = 0


    def set_external_effects(self, map: Any) -> None:
            {
            _external_effects = map


    def remove_external_effect(self, word: str) -> None:
            {
            if (!undefinedp(_external_effects[word])) {
            _external_effects = m_delete(_external_effects, word)


    def set_splashable(self, ) -> None:
            {
            _splashable = 1


    def unset_splashable(self, ) -> None:
            {
            _splashable = 0


    def set_applicable(self, ) -> None:
            {
            _applicable = 1


    def unset_applicable(self, ) -> None:
            {
            _applicable = 0


    def being_joined_by(self, thing: MudObject) -> None:
            {
            int i,
            that,
            this
            string *words
            mapping new_effects
            that = (int) thing.query_amount()
            this = query_amount()
            if (!(this + that))
            return
            if (thing.query_splashable(0, 0) && !_splashable)
            set_splashable()
            if (thing.query_applicable(0, 0) && !_applicable)
            set_applicable()
            if (thing.query_external_pk_check() && !_external_pk_check)
            set_external_pk_check()
            new_effects = (mapping) thing.query_eat_effects()
            words = m_indices(_eat_effects)
            for (i = 0; i < sizeof(words); i++) {
            if (new_effects[words[i]]) {
            new_effects[words[i]] *= that
            new_effects[words[i]] += this * _eat_effects[words[i]]
            } else {
            new_effects[words[i]] = this * _eat_effects[words[i]]


    def check_sharp(self, weapon: MudObject) -> int:
            {
            mixed *data
            int i
            if (!weapon) {
            return 0


    def do_drink(self, ) -> int:
            {
            if (!check_for_container()) {
            add_failed_mess("You go to try and $V $D, but it suddenly "
            "remembers what happens when it is not in a "
            "container and drains away to dust.\n")
            move("/room/rubbish")
            return 0


    def do_quaff(self, ) -> int:
            {
            if (!check_for_container()) {
            add_failed_mess("You go to try and $V $D, but it suddenly "
            "remembers what happens when it is not in a "
            "container and drains away to dust.\n")
            move("/room/rubbish")
            return 0


    def do_apply(self, : MudObject) -> int:
            {
            if (sizeof(things) > 1) {
            add_failed_mess("You must $V $D to one person alone.\n", [}))
            return 0


    def do_rub(self, : MudObject) -> int:
            {
            if (sizeof(things) > 1) {
            add_failed_mess("You must $V $D on one person alone.\n", [}))
            return 0


    def do_splash(self, : MudObject) -> int:
            {
            if (sizeof(things) > 1) {
            add_failed_mess("You must $V $D on one person alone.\n", [}))
            return 0


    def init_static_arg(self, map: Any) -> None:
            {
            if (!mapp(map)) {
            return


    def init_dynamic_arg(self, map: Any, object) -> None:
            {
            if (!mapp(map)) {
            return


    def check_for_container(self, ) -> int:
            {
            if (query_liquid()) {
            if (!environment()->query_max_volume() || living(environment())) {
            return 0


    def query_rotten(self, ) -> int:
            if ( _divisor ) {
            return to_int( _decay_level / _divisor ) > 1


    def do_cure(self, ) -> int:
            if(_dried || _liquid || _cured)
            return 0
            _decay_speed = 0
            _decay_level = 0
            BITS_CONTROLLER.remove_bit(self)
            set_main_plural( "cured " + query_plural() )
            set_short( "cured " + query_short())
            add_adjective("cured")
            remove_adjective("fresh")
            _cured = 1
            if( query_collective() ) {
            merge()


    def do_dry(self, ) -> int:
            int new_weight
            if(_dried || _liquid || _cured)
            return 0
            _decay_speed = 0
            _decay_level = 0
            BITS_CONTROLLER.remove_bit( self )
            set_main_plural("dried " + query_plural(0))
            set_short( "dried " + query_short())
            add_adjective("dried")
            remove_adjective("fresh")
            new_weight = ::query_weight() / 10
            if ( new_weight ) {
            set_weight( new_weight )


    def merge_criteria(self, ob: MudObject) -> int:
            return ::merge_criteria(ob) &&
            _decay_speed == ob.query_decay_speed() &&
            _bites_gone == ob.query_bites_gone() &&
            ((to_int(_decay_level / _divisor) < 2 &&
            to_int(ob.query_decay_level() / ob.query_decay_divisor()) < 2) ||
            to_int(_decay_level / _divisor) ==
            to_int(ob.query_decay_level() / ob.query_decay_divisor()))



class Food(MudObject):

    _eat_effects = '([ ])'
