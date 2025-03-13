# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/object/talker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            mixed args
            object where
            string channel
            where = environment(player)
            #ifdef DEBUG
            tell_creator("taffyd", "%O, %O, %O.\n", player, this_player(), where)
            #endif
            if( !where )
            return
            if (!living(where)) {
            player.init()
            return


    def query_player(self, ) -> MudObject:
            if(player && environment(player) && living(environment(player)))
            return environment(player)
            return 0


    def do_talker_control(self, args: Any, pattern: str) -> int:
            class talker_args t_args
            int position
            string full_name
            #ifdef DEBUG
            tell_creator("taffyd", "Args to talker control is %O. Pattern is %O.\n",
            args, pattern)
            #endif
            t_args = arg()
            switch (pattern) {
            case ON_PATTERN:
            return handle_status_command(args[0], t_args)
            case VERBOSE_PATTERN:
            return handle_verbose_command(args[0], t_args)
            case CHANNEL_PATTERN:
            if ( !t_args->status ) {
            await this_player().send("The eyes are asleep.\n")
            return 1


    def handle_history_command(self, channel: str, talker_args: Any) -> int:
            mixed *history
            string result
            if (!args->status) {
            await this_player().send("The eyes are asleep.\n")
            return 1


    def query_colour_status(self, talker_args: Any) -> str:
            if ( !mapp( args->colour ) ) {
            return "off"


    def set_colour_status(self, talker_args: Any, status: str) -> int:
            if ( !args->colour ) {
            args->colour = DEFAULT_COLOUR_SETTINGS
            } else {
            if ( stringp( args->colour ) ) {
            args->colour = DEFAULT_COLOUR_WITH( args->colour )


    def set_channel_colour(self, talker_args: Any, channel: str, colour: str) -> int:
            if ( !channel || !colour )
            return 0
            if ( !mapp( args->colour ) ) {
            args->colour = DEFAULT_COLOUR_WITH(colour)


    def handle_colour_toggle_command(self, talker_args: Any) -> int:
            if ( query_colour_status( args ) == "on" ) {
            return handle_colour_on_off_command( "off", args )


    def handle_colour_on_off_command(self, str_status: str, talker_args: Any) -> int:
            string status
            status = query_colour_status( args )
            switch( str_status ) {
            case "on":
            if ( status == "on" ) {
            add_failed_mess( "Talker colours for $D are already on!\n" )
            return -1


    def handle_status_command(self, mode: str, talker_args: Any) -> int:
            switch (mode) {
            case "on" :
            if ( args->status ) {
            tell_object(this_player(),  "The eyes are already alert "
            "and listening to your every word.\n")
            } else {
            tell_object(this_player(), "The eyes open and light up "
            "eagerly, then dim to a dull glow.\n")
            args->status = 1


    def handle_verbose_command(self, mode: str, talker_args: Any) -> int:
            if (!args->status) {
            await this_player().send("The eyes are asleep.\n")
            return 1


    def receive(self, channel: str, sender: str, text: str, receivers: MudObject) -> None:
            class talker_args args
            string *ignoring
            object where
            string colour
            string txt
            if(!player || !environment(player) )
            return
            where = environment(player)
            args = arg()
            if (args && !classp(args))
            return
            if (!args || !args->status || !living(where) || !interactive(where))
            return
            if(map(args->channels, (: lower_case($1.index(channel) if channel in map(args->channels, (: lower_case($1 else -1 :)) ) == -1) {
            return


    def do_chat(self, message: str, pattern: str, verb: str) -> int:
            class talker_args args
            object *things, *receivers
            string sender
            #ifdef DEBUG
            tell_creator("taffyd", "Message is %s, pattern is %s, verb is "
            "%s.\n", message, pattern, verb)
            #endif
            #ifdef EMOTE_ENABLED
            if ( verb[ <1 ] == ':' ) {
            verb = verb[0..<2]


    def remove_effect_shadow(self, i: int) -> None:
            if ( i == id ) {
            if ( player && environment( player ) ) {
            environment( player )->remove_object( player, 1 )
            init()


    def handle_colour_list(self, colour_args: Any, talker_args: Any) -> int:
            string channel
            if (!mapp(args->colour) || query_colour_status( args ) == "off" ) {
            add_failed_mess( "You currently have talker colours disabled.  Use "
            "\"talker colour on\" to turn them on.\n" )
            return 0


    def handle_echo_command(self, mode: str, talker_args: Any) -> int:
            int current
            current = args->local_echo
            if ( current ) {
            if ( mode == "on" ) {
            add_failed_mess( "Talker echo is already on for $D!\n" )
            return -1



class Talker(MudObject):
