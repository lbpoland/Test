# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.follow_speed = 3
            self.doing_story = ['({ })', '({ })']
            self.chat_string = ['0', '({ })']
            self.achat_string = ['0', '({ })']
            self.move_zones = []
            self._spell_actions = ([ ])
            self._combat_actions = []
            self.enter_commands = []
            self.known_commands = []
            self._queued_commands = []
            self.following_route = []
            self.always_return_to_default_position = 5


    def __init__(self):
            self.follow_speed = 3
            self.doing_story = ['({ })', '({ })']
            self.chat_string = ['0', '({ })']
            self.achat_string = ['0', '({ })']
            self.move_zones = []
            self._spell_actions = ([ ])
            self._combat_actions = []
            self.enter_commands = []
            self.known_commands = []
            self._queued_commands = []
            self.following_route = []
            self.always_return_to_default_position = 5
            }, 60)


    def setup_nationality(self, nationality: str, region: str) -> None:
            set_nationality(nationality)
            set_nationality_region(region)
            if (!load_object(nationality)) {
            debug_printf("Bad nationality, %O\n", nationality)
            } else {
            if (!nationality.query_region_description(region)) {
            debug_printf("Bad region %O in nationality, %O\n", region,
            nationality)


    def dest_me(self, ) -> None:
            living::dest_me()


    def soul_commqz(self, str: str) -> int:
            string verb, bit
            if (sscanf(str, "%s %s", verb, bit) == 2)
            return (int)SOUL_OBJECT.soul_command(verb, bit)
            return (int)SOUL_OBJECT.soul_command(str, "")


    def query_cap_name(self, ) -> str:
            return cap_name


    def soul_com_force(self, str: str) -> int:
            if (file_name(previous_object()) != SOUL_OBJECT)
            return 0
            command(str)
            return 1


    def set_name(self, n: str) -> None:
            if (query_name() && query_name() != "object")
            return
            ::set_name(n)
            cap_name = capitalize(query_name())
            add_plural(pluralize(query_name()))
            set_short( query_name() )
            set_long("You see nothing special.\n")
            set_living_name(n)


    def long(self, str: str, dark: int) -> str:
            string s
            if (dark < -1) {
            s = "You can only make out a rough shape in the glare.\n"
            } else if (dark > 1) {
            s = "You can only make out a rough shape in the gloom.\n"
            } else {
            s = query_long()


    def set_race(self, str: str) -> int:
            race = str
            return 1


    def set_class(self, str: str) -> int:
            class = str


    def set_guild(self, str: str) -> int:
            class = str


    def set_profession(self, str: str) -> int:
            class = str


    def do_command(self, words: str) -> int:
            if ( self.query_property( PASSED_OUT_PROP ) ) {
            return -1


    def delete_queued_commands(self, ) -> None:
            _queued_commands = [})


    def delay_command(self, words: str, interval: int) -> int:
            if ( self.query_property( PASSED_OUT_PROP ) ) {
            return -1


    def init(self, ) -> None:
            set_heart_beat( 1 )
            if (environment() && aggressive && this_player() &&
            file_name( environment() )[1..4] != "room" &&
            !environment()->no_attack() &&
            this_player()->query_visible(self))
            start_attack(this_player())


    def start_attack(self, who: MudObject) -> None:
            if(!who || !aggressive ) {
            return


    def adjust_gp(self, number: int) -> int:
            set_heart_beat( 1 )
            return ::adjust_gp( number )


    def check_anyone_here(self, ) -> int:
            object thing
            if ( !environment() ) {
            return 0


    def run_away(self, ) -> int:
            if ( query_property( "run away" ) == -1 ) {
            return 0


    def expand_string(self, in_str: str, on: MudObject) -> str:
            string *str, ret
            int i, add_dollar
            object liv, *obs, ob
            in_str = "/global/events"->convert_message( in_str )
            str = explode(in_str, "$")
            ret = ""
            for ( i = 0; i < sizeof( str ); i++ ) {
            if ( i % 2 == 0 ) {
            if (add_dollar) {
            ret += "$"


    def expand_mon_string(self, str: Any) -> None:
            string *args
            if ( functionp( str ) ) {
            evaluate( str, self )
            } else {
            if( !stringp( str ) && environment( self ) ) {
            tell_room(environment(self),
            "%^RED%^"+ self.the_short()+
            " says: please bugreport me, I have a bad load_chat.%^RESET%^\n",
            [}) )


    def query_ok_turn_off_heart_beat(self, ) -> int:
            return 1


    def heart_beat(self, ) -> None:
            int i, j
            if(base_name(environment()) == "/room/rubbish") {
            set_heart_beat(0)
            return


    def clean_up(self, parent: int) -> int:
            if(query_property("unique") || check_anyone_here())
            return 1
            if(parent) {
            log_file("CLEANUP", "%s %s cleaned up.\n", ctime(time()),
            file_name(self))


    def rand_num(self, no: int, type: int) -> int:
            int i, val
            for (i=0;i<no;i++)
            val = random(type)+1
            return val


    def set_random_stats(self, no: int, type: int) -> None:
            set_str(rand_num(no, type))
            set_dex(rand_num(no, type))
            set_int(rand_num(no, type))
            set_con(rand_num(no, type))
            set_wis(rand_num(no, type))


    def basic_setup(self, race: str, guild: str, level: int) -> None:
            {
            self.set_race(race)
            self.set_class(class)
            self.set_level(level)


    def give_money(self, base: int, rand: int, type: str) -> int:
            if (!type)
            type = "copper"
            return adjust_money(base+random(rand), type)


    def load_chat(self, chance: int, c_s: Any) -> None:
            int i
            chat_string = [0, [})]
            for (i=0;i<sizeof(c_s);i+=2) {
            chat_string[1] += [c_s[i], c_s[i+1]]
            chat_string[0] += c_s[i]


    def add_chat_string(self, weight: Any, chat: Any) -> None:
            int i
            if (pointerp(weight)) {
            for (i=0;i<sizeof(weight);i+=2) {
            add_chat_string(weight[i], weight[i+1])


    def remove_chat_string(self, chat: Any) -> None:
            int i
            if (pointerp(chat)) {
            for (i=0;i<sizeof(chat);i++) {
            remove_chat_string(chat[i])


    def load_a_chat(self, chance: int, c_s: Any) -> None:
            int i
            achat_string = [0, [})]
            for (i=0;i<sizeof(c_s);i+=2) {
            achat_string[1] += [c_s[i], c_s[i+1]]
            achat_string[0] += c_s[i]


    def add_achat_string(self, weight: Any, chat: Any) -> None:
            int i
            if (pointerp(weight))
            for (i=0;i<sizeof(weight);i+=2)
            add_achat_string(weight[i], weight[i+1])
            else
            if (achat_string[1].index(chat) if chat in achat_string[1] else -1 == -1) {
            achat_string[1] += [chat]
            achat_string[0] += weight


    def remove_achat_string(self, chat: Any) -> None:
            int i
            if (pointerp(chat))
            for (i=0;i<sizeof(chat);i++)
            remove_achat_string(chat[i])
            else
            if ((i = achat_string[1].index(chat) if chat in achat_string[1] else -1) != -1) {
            achat_string[0] -= achat_string[1][i-1]
            achat_string[1] = delete(achat_string[1], i-1, 1)


    def add_move_zone(self, zone: Any) -> None:
            int i
            if (pointerp(zone))
            for (i=0;i<sizeof(zone);i++)
            add_move_zone(zone[i])
            else if (move_zones.index(zone) if zone in move_zones else -1 != -1)
            return
            else
            move_zones += [zone]


    def set_move_zones(self, zones: str) -> None:
            int i
            for (i=0;i<sizeof(zones);i++)
            add_move_zone(zones[i])


    def remove_move_zone(self, zone: Any) -> None:
            int i
            if (pointerp(zone))
            for (i=0;i<sizeof(zone);i++)
            remove_move_zone(zone[i])
            else {
            if ((i=move_zones.index(zone) if zone in move_zones else -1) == -1)
            return
            move_zones = delete(move_zones, i, 1)


    def set_move_after(self, after: int, rand: int) -> None:
            _move_after = [after, rand]
            if (after != 0 && rand != 0) {
            do_move_after(0)


    def query_move_after(self, ) -> Any:
            return copy( _move_after )


    def add_enter_commands(self, str: Any) -> int:
            if (stringp(str)) {
            enter_commands += [str]
            } else if (pointerp(str)) {
            enter_commands += str
            } else if (functionp(str)) {
            enter_commands += [str]


    def reset_enter_commands(self, {: Any) -> None:
            varargs int move( mixed dest, string messin, string messout ) {
            int result
            object before
            before = environment()
            result = living::move( dest, messin, messout )
            if ( result == MOVE_OK ) {
            me_moveing( before )
            if ( virtual_move )
            true_location = file_name( environment() )


    def room_look(self, ) -> None:
            int i
            ::room_look()
            for ( i = 0; i < sizeof( enter_commands ); i++ ) {
            if ( functionp( enter_commands[ i ] ) ) {
            asyncio.create_task(self. enter_commands[ i ], 2 * i + 1, self )
            continue


    def do_move_after(self, running_away: int) -> None:
            if (sizeof(following_route)) {
            do_route_move()
            } else {
            WANDER_HANDLER.move_after( running_away )


    def event_fight_in_progress(self, me: MudObject, him: MudObject) -> None:
            mixed action
            int i
            if(sizeof(self.query_attacker_list())) {
            for(i=0; i<sizeof(_combat_actions); i+= 3) {
            if(_combat_actions[i] > random(100)) {
            action = _combat_actions[i+2]
            if(stringp(action))
            self.do_command(action)
            else if(functionp(action))
            evaluate(action, me, him)
            else if(pointerp(action) && sizeof(action) == 1 && stringp(action[0]))
            call_other(self, action[0], me, him)
            else if(pointerp(action) && sizeof(action) == 2)
            call_other(action[0], action[1], self, me, him)


    def event_exit(self, me: MudObject, mess: str, to: MudObject) -> None:
            mixed *bing
            int i, j, k
            string *zones, fname
            object *attacker_list, ob
            events::event_exit( me, mess, to )
            living::event_exit( me, mess, to )
            if (!_move_after || sizeof(following_route))
            return
            if ( !to || !me.query_visible(self))
            return
            attacker_list = self.query_attacker_list()
            if(attacker_list && sizeof(attacker_list)) {
            if (attacker_list.index(me) if me in attacker_list else -1 == -1)
            return
            attacker_list -= [me]
            foreach(ob in attacker_list) {
            if(ob && environment(ob) == environment())
            return


    def do_follow_move(self, dir: str) -> None:
            if (sizeof(following_route))
            return
            self.adjust_action_defecit((ACTIONS_PER_HB / (COMBAT_SPEED + 1)))
            do_command(dir)


    def add_combat_action(self, chance: int, name: str, action: Any) -> None:
            int i
            i = _combat_actions .index( name) if  name in _combat_actions  else -1
            if ( i == -1 ) {
            _combat_actions += [chance, name, action]
            } else {
            _combat_actions[ i - 1 ] = chance
            _combat_actions[ i + 1 ] = action


    def remove_combat_action(self, name: str) -> int:
            int i
            i = _combat_actions .index( name) if  name in _combat_actions  else -1
            if ( i == -1 )
            return 0
            _combat_actions = delete( _combat_actions, i - 1, 3 )
            return 1


    def combat_actions_call_back(self, player: MudObject, target: MudObject) -> None:
            int i
            object thing
            object *things
            mixed *actions
            if ( !player || !target ) {
            return


    def remove_spell_action(self, name: str) -> int:
            string spell
            mapping bits
            int ret
            foreach (spell, bits in _spell_actions) {
            if (bits[name]) {
            map_delete(bits, name)
            ret = 1


    def set_aggressive(self, a: int) -> None:
            aggressive = a
            if (a && !join_fight_mess) {
            join_fight_mess = self.one_short()+" joins in the fight.\n"


    def query_level(self, ) -> int:
            if (!class_ob) return 1
            return (int)class_ob.query_level(self)


    def query_death_xp(self, ) -> int:
            int amount
            if ( query_property( "dead" ) || query_property( "unique" ) ) {
            return 0


    def event_enter(self, dest: MudObject, mess: str, from: MudObject) -> None:
            if( environment( self ) &&
            file_name( environment( self ) )[ 1 .. 4 ] == "room" )
            return
            if(check_anyone_here() && (moves > 2)){
            moves = 0
            do_move_after(0)


    def real_room(self, check_room: str) -> None:
            if ( check_room == true_location ) {
            move_object( true_location )


    def set_virtual_move(self, number: int) -> None:
            if(virtual_move && !number && file_name(environment()) == "/room/virtual"){
            object ob = load_object(true_location)
            if(ob)
            move(ob)


    def set_true_location(self, word: str) -> None:
            if(word == "/room/virtual"){
            if(true_location)
            return
            word = file_name(environment())
            if(word == "/room/virtual"){
            move("/room/rubbish")
            true_location = "/room/rubbish"


    def cleaning_room(self, ) -> int:
            if ( virtual_move ) {
            true_location = file_name( environment() )
            "/room/virtual"->force_load()
            move_object( "/room/virtual" )
            return 1


    def do_move(self, move: str) -> None:
            if (1 || check_anyone_here()) {
            moves = 0


    def get_next_route_direction(self, ) -> str:
            string direc
            if (!sizeof(following_route)) {
            return 0


    def do_route_move(self, ) -> None:
            if (!sizeof(following_route)) {
            return


    def identify(self, thing: MudObject, places: MudObject) -> str:
            do_command( "'Please bug me!  I'm using identify()!" )
            return file_name( thing )


    def add_language(self, str: str) -> None:
            ::add_language(str)
            added_language = 1


    def set_cannot_change_position(self, flag: int) -> None:
            cannot_change_position = flag


    def query_cannot_change_position(self, ) -> int:
            return cannot_change_position


    def set_position(self, new_pos: str) -> None:
            if (always_return_to_default_position) {
            if (new_pos != query_position() &&
            this_player() != self) {
            asyncio.create_task(self."return_to_default_position",
            always_return_to_default_position, 0)


    def set_always_return_to_default_position(self, tim: int) -> None:
            always_return_to_default_position = tim


    def query_always_return_to_default_position(self, ) -> int:
            return always_return_to_default_position


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ )
            return int_query_static_auto_load()
            return ([ ])


    def init_static_arg(self, args: Any) -> None:
            if (args["::"])
            ::init_static_arg(args["::"])
            if (!undefinedp(args["cap name"]))
            cap_name = args["cap name"]
            if (!undefinedp(args["race"]))
            race = args["race"]
            if (!undefinedp(args["class"]))
            class = args["class"]


    def init_dynamic_arg(self, args: Any, ob: MudObject) -> None:
            if (args["::"])
            ::init_static_arg(args["::"])
            if (!undefinedp(args["chat string"]))
            chat_string = args["chat string"]
            if (!undefinedp(args["achat string"]))
            achat_string = args["achat string"]
            if (!undefinedp(args["combat actions"]))
            _combat_actions = args["combat actions"]
            if (!undefinedp(args["move after"]))
            _move_after = args["move after"]
            if (!undefinedp(args["throw out"]))
            throw_out = args["throw out"]
            if (!undefinedp(args["chat chance"]))
            chat_chance = args["chat chance"]
            if (!undefinedp(args["achat chance"]))
            achat_chance = args["achat chance"]
            if (!undefinedp(args["aggressive"]))
            aggressive = args["aggressive"]
            if (!undefinedp(args["join fight type"]))
            join_fight_type = args["join fight type"]
            if (!undefinedp(args["join fight mess"]))
            join_fight_mess = args["join fight mess"]
            if (!undefinedp(args["follow speed"]))
            follow_speed = args["follow speed"]
            if (!undefinedp(args["virtual move"]))
            virtual_move = args["virtual move"]
            if (!undefinedp(args["moves"]))
            moves = args["moves"]
            if (!undefinedp(args["true location"]))
            true_location = args["true location"]
            if (!undefinedp(args["enter commands"]))
            enter_commands = args["enter commands"]
            if (!undefinedp(args["move zones"]))
            move_zones = args["move zones"]
            if (!undefinedp(args["doing story"]))
            doing_story = args["doing story"]
            if (!undefinedp(args["last attacked"]))
            last_attacked = args["last attacked"]
            if (!undefinedp(args["following route"]))
            following_route = args["following route"]
            if (!undefinedp(args["added language"]))
            added_language = args["added language"]
            if (!undefinedp(args["cannot change position"]))
            cannot_change_position = args["cannot change position"]
            if (!undefinedp(args["always return to default position"]))
            always_return_to_default_position =
            args["always return to default position"]
            if (!undefinedp(args["level"]))
            set_level(args["level"])


    def attack_permission(self, ob1: MudObject, ob2: MudObject, stringy: str) -> int:
            #if !efun_defined(add_action)
            protected mixed _process_input(string str) {
            object ob = this_player()
            if(str == "")
            return 0
            _notify_fail(0)
            efun::set_this_player(self)
            if(!self.drunk_check(str))
            if(!self.exit_command(str))
            if(!self.cmdAll(str))
            if(!self.new_parser(str))
            if(!self.lower_check(str)){
            efun::set_this_player(ob)
            return 0


    def drunk_check(self, str: str) -> int:
            if(cmd_func){
            object owner = function_owner(cmd_func)
            if(owner && owner == environment(this_player())){
            int res = evaluate(cmd_func, str)
            if(res)
            return res
            } else cmd_func = 0


    def command_override(self, func: Any) -> None:
            if(!functionp(func))
            error("command_override needs a function!")
            cmd_func = func


    def event_hide_invis(self, hider: MudObject, adding: int, type: str, quiet: int) -> None:
            if ( aggressive &&
            !adding &&
            environment() &&
            file_name( environment() )[1..4] != "room" )
            {
            start_attack(hider)



class Monster(MudObject):

    follow_speed = 3

    doing_story = "['({ })', '({ })']"

    chat_string = "['0', '({ })']"

    achat_string = "['0', '({ })']"

    move_zones = '[]'

    _spell_actions = '([ ])'

    _combat_actions = '[]'

    enter_commands = '[]'

    known_commands = '[]'

    _queued_commands = '[]'

    following_route = '[]'

    always_return_to_default_position = 5
