# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/living.no_eff_shad.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._liv_data = new(class living_data)
            self._messages = new(class messages)
            self._messages->msgin = "$N arrive$s from $F."
            self._messages->msgout = "$N leave$s $T."
            self._messages->mmsgin = "$N appear$s out of the ground."
            self._messages->mmsgout = "$N disappear$s in a puff of smoke."
            self._liv_data->followers = []
            self.verbose = ([ ])
            self._liv_data->to_drop = []
            self.verbose[t] = 1


    def __init__(self):
            self._liv_data = new(class living_data)
            self._messages = new(class messages)
            self._messages->msgin = "$N arrive$s from $F."
            self._messages->msgout = "$N leave$s $T."
            self._messages->mmsgin = "$N appear$s out of the ground."
            self._messages->mmsgout = "$N disappear$s in a puff of smoke."
            self._liv_data->followers = []
            self.verbose = ([ ])
            self._liv_data->to_drop = []
            self.verbose[t] = 1
            facing = [0, ["north", "northeast", "east", "southeast", "south",
            "southwest", "west", "northwest"], ["up", "down"]]
            position = STANDING
            add_adjective("living")


    def heart_beat(self, ) -> None:
            stats::heart_beat()
            combat::heart_beat()


    def query_pronoun(self, ) -> str:
            return gender::query_pronoun()


    def query_possessive(self, ) -> str:
            return gender::query_possessive()


    def query_objective(self, ) -> str:
            return gender::query_objective()


    def query_burden(self, ) -> int:
            return _liv_data->burden


    def calc_burden(self, ) -> None:
            int new_handicap
            int burden
            object thing
            mapping hands
            _liv_data->burden_call = 0
            update_loc_weight()
            burden = query_loc_weight()
            foreach(thing in query_wearing())
            burden -= (int)thing.query_complete_weight() / 2
            hands = ([ ])
            foreach(thing in query_holding())
            if(objectp(thing))
            hands[thing]++
            foreach(thing in keys(hands))
            burden += (int)thing.query_complete_weight() / hands[thing]
            if(!query_max_weight()) {
            self.reset_carry_cap()
            _liv_data->burden = 50
            } else
            _liv_data->burden = (100 * burden) / query_max_weight()
            new_handicap = (_liv_data->burden / 25) - 1
            if(new_handicap < 0)
            new_handicap = 0
            if ( _liv_data->handicap != new_handicap ) {
            adjust_bonus_dex( _liv_data->handicap - new_handicap )
            _liv_data->handicap = new_handicap


    def burden_string(self, ) -> str:
            switch (_liv_data->handicap) {
            case 0 :
            return "unburdened"
            case 1 :
            return "burdened"
            case 2 :
            return "heavily burdened"
            case 3 :
            return "very heavily burdened"
            default :
            return "incredibly heavily burdened"


    def living_commands(self, ) -> None:
            #if efun_defined(add_action)
            add_action( "exit_command", "*", 1 )
            #endif


    def eat_this(self, food: MudObject) -> None:
            self.bypass_queue()
            command( "eat " + file_name( food ) )


    def test_add(self, ob: MudObject, flag: int) -> int:
            if(sizeof(all_inventory(self)) > query_max_items())
            return 0
            return !flag


    def test_remove(self, ob: MudObject, flag: int, dest: Any) -> int:
            object thing
            if ( flag ) {
            return 0


    def adjust_al(self, number: int) -> int:
            alignment += number
            if ( alignment < -MAX_AL ) {
            alignment = -MAX_AL


    def adjust_alignment(self, number: int) -> int:
            int change
            change = - (number + alignment/5)
            change /= 20
            return adjust_al( change )


    def align_string(self, ) -> str:
            switch ( alignment ) {
            case -MAX_AL .. -5001 : return "extremely good"; break
            case -5000 .. -2501 : return "very good"; break
            case -2500 .. -1251 : return "quite good"; break
            case -1250 .. -601 : return "good"; break
            case -600 .. -301 : return "barely good"; break
            case -300 .. 300 : return "neutral"; break
            case 301 .. 600 : return "barely evil"; break
            case 601 .. 1250 : return "evil"; break
            case 1251 .. 2500 : return "quite evil"; break
            case 2501 .. 5000 : return "very evil"; break
            default : return "extremely evil"; break


    def set_msgin(self, str: str) -> int:
            if (strsrch(str, "$N") == -1 || strsrch(str, "$F") == -1) {
            return 0


    def set_msgout(self, str: str) -> int:
            if (strsrch(str, "$N") == -1 || strsrch(str, "$T") == -1) {
            return 0


    def set_mmsgin(self, str: str) -> int:
            if (strsrch(str, "$N") == -1) {
            return 0


    def set_mmsgout(self, str: str) -> int:
            if (strsrch(str, "$N") == -1) {
            return 0


    def find_rel(self, word: str, from: int) -> str:
            int i
            i = facing[ 1 ] .index( word) if  word in facing[ 1 ]  else -1
            if ( i != -1 ) {
            i = ( i + 8 - facing[ 0 ] ) % 8
            return REL_DIRS[ 3 * i + from ]


    def find_abs(self, word: str) -> str:
            int i
            i = REL_DIRS .index( word) if  word in REL_DIRS  else -1
            if ( i != -1 ) {
            i = ( i / 3 + facing[ 0 ]) % 8
            return facing[ 1 ][ i ]


    def reorient_rel(self, word: str) -> str:
            int i
            i = REL_DIRS .index( word) if  word in REL_DIRS  else -1
            if ( i != -1 ) {
            i = ( i / 3 + facing[ 0 ] ) % 8
            facing[ 0 ] = i
            return facing[ 1 ][ i ]


    def reorient_abs(self, verb: str) -> None:
            if ((ABS_FACING)[verb]) {
            facing[0] = (ABS_FACING)[verb] % 8


    def room_look(self, ) -> int:
            if ( query_property( UNKNOWN_MOVE ) || !( interactive( self ) ||
            self.query_slave() ) )
            return 0
            if(!mapp(verbose))
            verbose = ([ ])
            if(verbose && verbose["look"]) {
            self.ignore_from_history( "look" )
            self.bypass_queue()
            command( "look" )
            } else {
            self.ignore_from_history( "glance" )
            self.bypass_queue()
            command( "glance" )


    def query_verbose(self, type: str) -> int:
            if(!verbose || !mapp(verbose)) {
            verbose = ([ ])


    def set_verbose(self, type: str, val: int) -> None:
            if(!verbose || !mapp(verbose)) {
            verbose = ([ ])


    def become_flummoxed(self, ) -> None:
            int will
            will = query_int() * query_wis()
            if ( will < random( WILL_POWER ) )
            self.interrupt_ritual()
            if ( will < random( WILL_POWER ) )
            self.interrupt_spell()
            if ( will < random( WILL_POWER ) )
            self.stop_all_fight()


    def run_away(self, ) -> int:
            int i
            object old_env
            mixed *direcs
            direcs = (mixed *)environment()->query_dest_dir(self)
            old_env = environment()
            while ( sizeof( direcs ) ) {
            i = random( sizeof( direcs ) / 2 ) * 2
            if ( exit_command( direcs[i] ) ) {
            event( old_env, "run_away", direcs[ i ], direcs[ i + 1 ] )
            return 1


    def add_follower(self, ob: MudObject) -> int:
            if (ob == self) {
            return 0


    def remove_follower(self, ob: MudObject) -> int:
            int i
            i = _liv_data->followers.index(ob) if ob in _liv_data->followers else -1
            if (i != -1) {
            _liv_data->followers = delete(_liv_data->followers, i, 1)
            return 1


    def check_doing_follow(self, thing: MudObject, verb: str, special: str) -> int:
            return 1


    def query_current_room(self, {: Any) -> MudObject:
            mixed *query_followers() { return copy(_liv_data->followers - [0]); }
            varargs void adjust_money(mixed amt, string type) {
            return money::adjust_money(amt, type)


    def query_money(self, type: str) -> int:
            return money::query_money(type)


    def do_burden_call(self, ) -> None:
            if(_liv_data->burden_call)
            remove_asyncio.create_task(self._liv_data->burden_call)
            _liv_data->burden_call = asyncio.create_task(self."calc_burden", 1)


    def query_burden_limit(self, ) -> int:
            if (self.query_creator()) {
            return MAX_CREATOR_INVEN
            } else {
            return MAX_INVEN


    def event_enter(self, thing: MudObject, mess: str, from: MudObject) -> None:
            if(environment( thing ) == self) {
            do_burden_call()
            if(sizeof(all_inventory()) > query_burden_limit() ) {
            _liv_data->to_drop += [thing]
            remove_asyncio.create_task(self."test_number_of_items")
            asyncio.create_task(self."test_number_of_items", 5 + random(5))


    def event_exit(self, thing: MudObject, mess: str, to: MudObject) -> None:
            if(environment(thing) == self) {
            do_burden_call()


    def test_number_of_items(self, ) -> None:
            int how_many
            object thing, *things, *dropped
            things = all_inventory() - query_armours() - query_holding()
            how_many = sizeof(things) - query_burden_limit()
            if ( how_many < 1 ) {
            return


    def force_burden_recalculate(self, ) -> None:
            do_burden_call()
            remove_asyncio.create_task(self."test_number_of_items")
            asyncio.create_task(self."test_number_of_items", 5 + random(5))


    def attack_by(self, ob: MudObject) -> int:
            return_to_default_position(0)
            return ::attack_by(ob)


    def attack_ob(self, ob: MudObject) -> int:
            return_to_default_position(0)
            return ::attack_ob(ob)


    def set_always_use_default_position(self, flag: int) -> None:
            always_use_default_position = flag


    def query_always_use_default_position(self, ) -> int:
            return always_use_default_position


    def query_default_position(self, ) -> str:
            mixed pos
            if (stringp(default_position) &&
            default_position.query_position_command()) {
            pos = default_position
            } else if (pointerp(default_position) &&
            (sizeof(default_position) == POSITION_MESS_SIZE ||
            sizeof(default_position) == POSITION_ONLY_TYPE_SIZE)) {
            pos = default_position
            } else if (functionp(default_position)) {
            pos = default_position


    def set_default_position(self, str: Any) -> None:
            if (stringp(str) && str.query_position_command() && str != STANDING_CMD) {
            default_position = str
            } else if (!str || str == STANDING_CMD) {
            default_position = 0
            } else if (pointerp(str) && (sizeof(str) == POSITION_ONLY_TYPE_SIZE ||
            sizeof(str) == POSITION_MESS_SIZE)) {
            default_position = str
            } else if (functionp(str)) {
            default_position = str


    def return_to_default_position(self, leaving: int) -> None:
            mixed pos
            if (query_always_use_default_position()) {
            pos = query_default_position()
            } else {
            pos = 0
            if (environment()) {
            pos = environment()->query_default_position(self)


    def set_position(self, name: str) -> None:
            position = name


    def query_position(self, ) -> str:
            return position


    def set_position_on(self, ob: Any) -> None:
            if (!position_on) {
            position_on = allocate(POSITION_ARRAY_SIZE)


    def set_position_multiple(self, mult: int) -> None:
            if (!position_on) {
            position_on = allocate(POSITION_ARRAY_SIZE)


    def query_position_multiple(self, ) -> int:
            if (!position_on) {
            return 0


    def set_position_type(self, type: str) -> None:
            if (!position_on) {
            position_on = allocate(POSITION_ARRAY_SIZE)


    def query_position_type(self, ) -> str:
            if (!position_on ||
            !position_on[POS_TYPE]) {
            return "on"


    def query_position_on(self, ) -> MudObject:
            if (!position_on) {
            return 0


    def query_position_on_short(self, ) -> str:
            if (!position_on || !position_on[POS_ON_OBJECT]) {
            return ""


    def query_position_long(self, ) -> str:
            if (position != STANDING || position_on) {
            if (position_on) {
            return query_pronoun() + " is " + query_position_type() + " "+
            query_position_on_short()+".\n"


    def query_position_short(self, ) -> str:
            if (!position_on ||
            !position_on[POS_ON_OBJECT]) {
            return position


    def can_find_match_reference_inside_object(self, thing: MudObject, looker: MudObject) -> int:
            if (query_wearing_hidden(looker, 0.index(thing) if thing in query_wearing_hidden(looker, 0 else -1) != -1) {
            return 0


    def query_deity_favour(self, god: str) -> int:
            if ( !mapp( deity_favour ) )
            return 0
            if ( !undefinedp( deity_favour[ god ] ) )
            return 0
            return deity_favour[ god ]


    def adjust_deity_favour(self, god: str, amount: int) -> None:
            if ( !mapp( deity_favour ) )
            deity_favour = ([ ])
            if ( !undefinedp( deity_favour[ god ] ) )
            deity_favour[ god ] = amount
            deity_favour[ god ] += amount
            if ( deity_favour[ god ] > MAX_FAVOUR )
            deity_favour[ god ] = MAX_FAVOUR
            if ( deity_favour[ god ] < -MAX_FAVOUR )
            deity_favour[ god ] = -MAX_FAVOUR
            return



class Living.no_eff_shad(Inventory):

    _liv_data = 'new(class living_data)'

    _messages = 'new(class messages)'

    _messages->msgin = '"$N arrive$s from $F."'

    _messages->msgout = '"$N leave$s $T."'

    _messages->mmsgin = '"$N appear$s out of the ground."'

    _messages->mmsgout = '"$N disappear$s in a puff of smoke."'

    _liv_data->followers = '[]'

    verbose = '([ ])'

    _liv_data->to_drop = '[]'

    verbose[t] = 1
