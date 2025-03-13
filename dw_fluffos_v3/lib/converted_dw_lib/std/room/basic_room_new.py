# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic_room_new.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.aliases = []
            self.exits = []
            self.hidden_objects = []
            self._use_internal_objects = []
            self.door_control = ([ ])
            self.dest_other = []


    def __init__(self):
            self.aliases = []
            self.exits = []
            self.hidden_objects = []
            self._use_internal_objects = []
            self.door_control = ([ ])
            self.dest_other = []
            if ( find_object( "/obj/handlers/map" ) ) {
            catch( "/obj/handlers/map"->check_map( file_name( self ) ) )


    def query_is_room(self, ) -> int:
            {
            return 1


    def query_enchant(self, ) -> int:
            int enchant_level =  to_int( floor( 0.5 + dynamic_enchant *
            exp( -0.693 *
            ( time() - enchant_time ) /
            ENCHANT_HALF)) +
            background_enchant )
            if ( enchant_level > 5000 ) {
            return 5000


    def set_enchant(self, number: int) -> int:
            if (number < 0) {
            number = 0


    def add_enchant(self, number: int) -> int:
            dynamic_enchant = dynamic_enchant * exp( -0.693 *
            ( time() - enchant_time ) /
            ENCHANT_HALF ) + number
            enchant_time = time()
            return floor( 0.5 + dynamic_enchant ) + background_enchant


    def set_background_enchant(self, number: int) -> None:
            background_enchant = number


    def set_dynamic_enchant(self, number: Any) -> None:
            dynamic_enchant = number
            enchant_time = time()


    def query_background_enchant(self, ) -> int:
            return background_enchant


    def set_co_ord(self, new_co_ord: int) -> None:
            if ( !pointerp( new_co_ord ) ) {
            write( "Warning: Co-ordinate must be an array.\n" )
            return


    def calc_long_exit(self, ) -> None:
            int i, add
            string *words
            mixed tmp
            words = [})
            for ( i = 0; i < sizeof( dest_other ); i += 2 ) {
            tmp = dest_other[ i + 1 ][ ROOM_OBV ]
            if ( !tmp ) {
            continue


    def add_alias(self, names: Any, word: str) -> None:
            string name
            if ( !aliases ) {
            aliases = [})


    def remove_alias(self, names: Any, word: str) -> None:
            int i
            string name
            if ( !aliases ) {
            return


    def add_hidden_object(self, thing: MudObject) -> int:
            if ( hidden_objects .index( thing) if  thing in hidden_objects  else -1 != -1 ) {
            return 0


    def remove_hidden_object(self, thing: MudObject) -> int:
            int i
            i = hidden_objects .index( thing) if  thing in hidden_objects  else -1
            if ( i == -1 ) {
            return 0


    def add_use_internal_object(self, thing: MudObject) -> None:
            _use_internal_objects |= [thing]


    def remove_use_internal_object(self, thing: MudObject) -> None:
            _use_internal_objects -= [thing]


    def query_use_internal_objects(self, ) -> List[MudObject]:
            return _use_internal_objects


    def query_destination(self, exit: str) -> str:
            int i
            i = dest_other .index( exit) if  exit in dest_other  else -1
            if ( ( i < 0 ) && objectp( this_player() ) )
            i = member_array( (string)this_player()->reorient_rel( exit ),
            dest_other )
            if ( i < 0 )
            return ROOM_VOID
            return dest_other[ i + 1 ][ ROOM_DEST ]


    def query_dark_mess(self, ) -> str:
            mixed dark_mess
            if ( !stringp( dark_mess = query_property( "dark mess" ) ) ) {
            return "It's dark here, isn't it?"


    def set_dark_mess(self, word: str) -> None:
            add_property( "dark mess", word )


    def query_bright_mess(self, ) -> str:
            mixed bright_mess
            if ( !stringp( bright_mess = query_property( "bright mess" ) ) ) {
            return "It's too bright to see anything!"


    def query_room_size(self, ) -> Any:
            mixed room_size
            room_size = query_property( "room size" )
            if ( !room_size ) {
            return 10


    def set_room_size(self, number: Any) -> None:
            if ( intp( number ) ) {
            add_property( "room size", number )
            return


    def expand_alias(self, word: str) -> str:
            int i
            if ( !aliases || !sizeof( aliases ) ) {
            return word


    def calc_short_exit_string(self, ) -> str:
            int i, add
            string *words
            mixed tmp
            words = [})
            for ( i = 0; i < sizeof( dest_other ); i += 2 ) {
            tmp = dest_other[ i + 1 ][ ROOM_OBV ]
            if ( !tmp ) {
            continue


    def query_short_exit_string(self, ) -> str:
            string tmp
            if(short_exit) {
            return this_player()->colour_event("exits", "%^GREEN%^") +
            short_exit + "%^RESET%^"


    def enchant_string(self, ) -> str:
            string words
            words = (string)self.query_property( "octarine_mess" )
            if ( words ) {
            return words +"\n"


    def long(self, word: str, dark: int) -> str:
            string ret
            if ( !long_exit ) {
            calc_long_exit()


    def pretty_short(self, thing: MudObject) -> str:
            int dark
            if ( thing ) {
            dark = (int)thing.check_dark( (int)self.query_light() )


    def calc_co_ord(self, ) -> None:
            int i, j, k, shift, *delta, *other_co_ord
            string other
            for ( i = sizeof( dest_other ) - 2; ( i > -1 ) && !co_ord; i -= 2 ) {
            other = dest_other[ i + 1 ][ ROOM_DEST ]
            if ( !find_object( other ) ) {
            continue


    def calc_exits(self, ) -> None:
            int i, j
            string exit, word, *tmp_al
            exits = [})
            for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 ) {
            exit = dest_other[ i ]
            if ( exits .index( exit) if  exit in exits  else -1 == -1 ) {
            exits += [exit]
            word = SHORTEN[ exit ]
            if ( stringp( word ) ) {
            exits += [word]


    def init(self, ) -> None:
            object ob
            int i
            if(is_day != -1 && ((WEATHER_HANDLER.query_day() > 0) != is_day)) {
            is_day = (1 - is_day)
            if(variablelongs && strlen(variablelongs[is_day]))
            set_long(variablelongs[is_day])
            if(variableitems) {
            for(i=0; i<sizeof(variableitems[1-is_day]); i += 2)
            remove_item(variableitems[1-is_day][i])
            for(i=0; i<sizeof(variableitems[is_day]); i += 2)
            add_item(variableitems[is_day][i], variableitems[is_day][i+1])


    def add_zone(self, zone: str) -> None:
            string *zones
            zones = query_property( "room zone" )
            if ( !zones ) {
            zones = [zone]
            } else {
            zones += [zone]


    def set_zone(self, zone: str) -> None:
            add_zone(zone)


    def query_exit(self, direc: str) -> int:
            return ( dest_other .index( direc) if  direc in dest_other  else -1 != -1 )


    def add_exit(self, direc: str, dest: Any, type: str) -> int:
            mixed *stuff
            if ( !dest_other ) dest_other = [})
            if ( dest_other .index( direc) if  direc in dest_other  else -1 != -1 ) return 0
            if ( objectp( dest ) )
            dest = file_name( dest )
            if ( dest[ 0 .. 0 ] != "/" )
            dest = "/"+ dest
            stuff = [dest] + (mixed *)ROOM_HANDLER.query_exit_type( type, direc )
            dest_other += [direc, stuff]
            if ( ( stuff = (mixed *)ROOM_HANDLER->query_door_type( type, direc,
            dest ) ) ) {
            door_control[ direc ] = clone_object( DOOR_OBJECT )
            door_control[ direc ]->setup_door( direc, self, dest, stuff,
            type)
            hidden_objects += [door_control[ direc ]]
            door_control[ dest ] = direc


    def modify_exit(self, direc: Any, data: Any) -> int:
            int i, j, k
            if(pointerp(direc)) {
            for(k = 0; k < sizeof(direc); k++) {
            modify_exit(direc[k], data)


    def remove_exit(self, direc: str) -> int:
            int i
            if ( !dest_other ) {
            dest_other = [})
            return 0


    def query_door_open(self, direc: str) -> int:
            if ( !objectp( door_control[ direc ] ) ) {
            return -1


    def query_relative(self, direc: str) -> int:
            int i
            i = dest_other .index( direc) if  direc in dest_other  else -1
            if ( i == -1 ) {
            return 0


    def query_look(self, direc: str) -> str:
            int i
            i = dest_other .index( direc) if  direc in dest_other  else -1
            if ( i == -1 )
            return 0
            if ( !dest_other[ i + 1 ] )
            return 0
            return (string)evaluate(dest_other[ i + 1 ][ ROOM_LOOK ])


    def query_size(self, direc: str) -> int:
            int i
            if ( ( i = dest_other .index( direc) if  direc in dest_other  else -1 ) == -1 ) return 0
            if ( stringp( dest_other[ i + 1 ][ ROOM_SIZE ] ) )
            return (int)call_other( self, dest_other[ i + 1 ][ ROOM_SIZE ] )
            if ( pointerp( dest_other[ i + 1 ][ ROOM_SIZE ] ) )
            return (int)call_other( dest_other[ i + 1 ][ ROOM_SIZE ][ 0 ],
            dest_other[ i + 1 ][ ROOM_SIZE ][ 1 ] )
            return dest_other[ i + 1 ][ ROOM_SIZE ]


    def event_magic(self, channel: MudObject, amount: int, caster: MudObject) -> None:
            add_enchant( amount / 5 )


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if(interactive(ob))
            last_visited = time()


    def query_last_visited(self, ) -> int:
            varargs int add_item( mixed shorts, mixed desc, int no_plural ) {
            if (!desc) {
            printf("Error!  In %O add_item(%O, 0), not added.\n", file_name(),
            shorts)
            return 0


    def remove_item(self, word: str) -> int:
            if ( !item ) {
            return 1


    def modify_item(self, word: str, new_desc: Any) -> int:
            if ( !item ) {
            return 0


    def add_effect(self, eff: str, arg: Any) -> None:
            effects = clone_object( "/std/shadows/misc/effects" )
            effects.setup_shadow( self )
            effects.add_effect( eff, arg )


    def set_terrain(self, terrain_name: str) -> int:
            if ( terrain ) {
            return 0


    def set_wall(self, args: Any) -> None:
            if ( !wall ) {
            wall = clone_object( WALL_OBJECT )
            wall.setup_shadow( self )


    def set_default_position(self, stuff: Any) -> None:
            add_property(DEFAULT_POSITION_PROPERTY, stuff)


    def query_default_position(self, ) -> Any:
            return query_property(DEFAULT_POSITION_PROPERTY)


    def is_allowed_position(self, poss: str) -> int:
            switch (poss) {
            case SITTING :
            case STANDING :
            case KNEELING :
            case LYING :
            case MEDITATING :
            case CROUCHING :
            return 1
            default :
            return 0


    def dest_me(self, ) -> None:
            int in_armoury, in_void
            object thing, *things
            if ( file_name( self ) == ARMOURY )
            in_armoury = 1
            if ( file_name( self ) == ROOM_VOID )
            in_void = 1
            if ( !in_void ) {
            things = all_inventory( self )
            foreach( thing in things ) {
            if ( userp( thing ) ) {
            thing.move_with_look( ROOM_VOID, "$N fall$s into the void." )
            continue


    def set_keep_room_loaded(self, flag: int) -> None:
            add_property(ROOM_KEEP_PROP, flag)


    def query_keep_room_loaded(self, ) -> int:
            return query_property(ROOM_KEEP_PROP)


    def clean_up(self, parent: int) -> int:
            if (parent) {
            return 0


    def real_clean(self, ) -> int:
            object thing
            foreach ( thing in all_inventory( self ) ) {
            if ( thing.query_property( "player" ) ||
            (thing.query_property( "unique" ) &&
            last_visited > time() - 3600) ||
            thing.query_slave() ||
            thing.query_name() == "corpse") {
            return 0


    def tell_door(self, direc: str, message: str, thing: MudObject) -> None:
            if ( objectp( door_control[ direc ] ) )
            door_control[ direc ]->tell_door( message, thing )


    def query_door(self, dest: Any) -> str:
            int i
            string direc
            mixed bing
            if ( objectp( dest ) ) {
            dest = file_name( dest )


    def stop_room_chats(self, ) -> None:
            if ( chatter ) {
            chatter.dest_me()


    def set_chat_min_max(self, min: int, max: int) -> None:
            if (chatter) chatter.set_chat_min_max(min,max)


    def add_room_chats(self, new_chats: str) -> None:
            if (chatter) chatter.add_room_chats( new_chats )


    def remove_room_chats(self, dead_chats: str) -> None:
            if (chatter) chatter.remove_room_chats( dead_chats )


    def add_situation(self, label: Any, situation: Any) -> None:
            if (!sitchanger) {
            sitchanger = clone_object( SITUATION_CHANGER_OBJECT )
            sitchanger.set_room( self )


    def make_situation_seed(self, xval: int, yval: int) -> None:
            if (sitchanger) sitchanger.set_seed(xval,yval)


    def start_situation(self, label: int, do_start_mess: int) -> None:
            if (sitchanger)
            sitchanger.start_situation( label, do_start_mess )


    def end_situation(self, label: Any) -> None:
            if (sitchanger) sitchanger.end_situation( label )


    def shutdown_all_situations(self, ) -> None:
            if (sitchanger) sitchanger.shutdown_all_situations()


    def shutdown_situation(self, call: int, label: Any) -> None:
            if (sitchanger) sitchanger.shutdown_situation(call,label)


    def query_not_replaceable(self, ) -> int:
            return query_property(ROOM_NOT_REPLACE_PROGRAM_PROP)


    def set_not_replaceable(self, replace: int) -> None:
            add_property(ROOM_NOT_REPLACE_PROGRAM_PROP, replace)


    def stats(self, ) -> Any:
            int i
            mixed *stuff
            stuff = [})
            for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 )
            stuff += ({
            [dest_other[ i ], dest_other[ i + 1 ][ ROOM_DEST ]]
            })
            if ( co_ord )
            stuff += ({
            ["co-ord x", co_ord[ 0 ]],
            ["co-ord y", co_ord[ 1 ]],
            ["co-ord z", co_ord[ 2 ]]
            })
            return light::stats() + property::stats() + stuff + ({
            ["short", short( 0 )],
            ["enchantment", query_enchant()],
            ["background enchantment", background_enchant],
            ["dynamic enchantment", dynamic_enchant],
            ["enchantment time", enchant_time],
            ["theft handler", theft_handler],
            })


    def set_day_long(self, str: str) -> None:
            if(!variablelongs)
            variablelongs = allocate(2)
            variablelongs[DAY] = str
            if(is_day == -1)
            is_day = (WEATHER_HANDLER.query_day() > 0)
            if(is_day == DAY)
            set_long(str)


    def set_night_long(self, str: str) -> None:
            if(!variablelongs)
            variablelongs = allocate(2)
            variablelongs[NIGHT] = str
            if(is_day == -1)
            is_day = (WEATHER_HANDLER.query_day() > 0)
            if(is_day == NIGHT)
            set_long(str)


    def query_night_long(self, ) -> str:
            if(variablelongs && strlen(variablelongs[NIGHT]))
            return variablelongs[NIGHT]
            return self.query_long()


    def room_day_chat(self, args: Any) -> None:
            if(!variablechats)
            variablechats = allocate(2)
            variablechats[DAY] = args
            if(is_day == -1)
            is_day = (WEATHER_HANDLER.query_day() > 0)
            if(is_day == DAY)
            room_chat(args)


    def room_night_chat(self, args: Any) -> None:
            if(!variablechats)
            variablechats = allocate(2)
            variablechats[NIGHT] = args
            if(is_day == -1)
            is_day = (WEATHER_HANDLER.query_day() > 0)
            if(is_day == NIGHT)
            room_chat(args)


    def query_help_file_directory(self, ) -> str:
            return ROOM_HELP_FILE_DIR



class Basic_room_new(MudObject):

    aliases = '[]'

    exits = '[]'

    hidden_objects = '[]'

    _use_internal_objects = '[]'

    door_control = '([ ])'

    dest_other = '[]'
