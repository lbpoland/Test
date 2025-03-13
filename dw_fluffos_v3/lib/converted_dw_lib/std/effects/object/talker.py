# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/talker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_indefinite(self, ) -> int:
            protected class talker_args new_talker_args() {
            return new(class talker_args, status : 1, channels : ["one"],
            verbose : 1, local_echo : 0, colour : 0 )


    def restart(self, thing: MudObject, args: Any, id: int) -> None:
            if (!classp(args)) {
            thing.set_arg_of(thing->sid_to_enum(id), new_talker_args())
            tell_object( environment( thing ), "Your talker quivers "
            "uncontrollably and starts to jump around.  You will have "
            "to re-add your talker channels and reconfigure your talker.\n" )


    def end(self, thing: MudObject, args: Any, id: int) -> None:
            if ( environment( thing ) )
            tell_object( environment( thing ), "The pair of glittering eyes in "+
            (string)thing.the_short() +" close and fade away forever.\n" )
            thing.remove_extra_look( self )
            thing.remove_alias( "talker" )
            thing.remove_plural( "talkers" )


    def extra_look(self, thing: MudObject) -> str:
            int *enums
            mixed args
            enums = (int *)thing.effects_matching( "magic.talker" )
            if ( !sizeof( enums ) ) {
            return ""


    def channels(self, ) -> str:
            return sprintf( "%#-*s\n", (int)this_player()->query_cols(),
            implode( all_channels( this_player() ), "\n" ) )


    def find_actual_talker(self, thing: MudObject) -> MudObject:
            object talker
            while ( thing ) {
            talker = thing
            thing = query_shadowing( thing )


    def list(self, word: str, brief: int) -> str:
            int space
            int *enums
            string sender
            string table
            object thing
            object *ok
            object *things
            object holder
            class talker_args args
            table = ""
            space = (int)this_player()->query_cols() - 20
            things = children( SHADOWS + "talker" ) -
            [find_object( SHADOWS + "talker" )]
            things = filter( map( things, (: find_actual_talker( $1 ) :) ),
            (: $1 && environment($1) && living(environment($1)) &&
            (!userp($1) || interactive($1)) :) )
            things = uniq_array(things)
            things = sort_array( things,
            (: strcmp( environment($1)->query_name(),
            environment($2)->query_name() ) :) )
            ok = [})
            foreach( thing in things ) {
            holder = environment( thing )
            if (userp(holder)) {
            sender = capitalize( holder.query_cap_name() )
            } else {
            sender = capitalize( holder.query_name() )


    def normalise_name(self, channel: str) -> str:
            int position
            mixed *details
            string *lower_names
            string lower_channel
            lower_channel = lower_case( channel )
            lower_names = map( valid_channels, (: lower_case($1) :) )
            position = lower_names .index( lower_channel) if  lower_channel in lower_names  else -1
            if ( position == -1 ) {
            details = HELP_CMD->find_match_in_array( lower_channel,
            lower_names )
            if ( details[ 1 ] > 70 ) {
            return valid_channels[ details[ 0 ] ]


    def reset(self, ) -> None:
            _channel_cache = ([ ])


    def clear_cache(self, person: str) -> None:
            if (_channel_cache) {
            map_delete(_channel_cache, person)



class Talker(MudObject):
