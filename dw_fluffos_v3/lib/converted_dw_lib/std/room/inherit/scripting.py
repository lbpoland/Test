# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/scripting.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def event_save(self, ob: MudObject) -> None:
            class script query_script( string name ){
            return _script_data[name]


    def trigger_script(self, event: str, who: MudObject, override: int) -> None:
            int i
            class script this_script
            class running_script running
            this_script = query_script( event )
            if (!this_script || !objectp(who)) {
            return


    def repeat_loop(self, ) -> None:
            object npc
            class script_data data
            string str
            class parse_node node
            if (!sizeof( _running_scripts ) ) {
            return


    def set_script(self, name: str, script: Any) -> None:
            _script_data[name] = script
            event_save(self)


    def set_script_data(self, name: str, script_data: Any) -> None:
            if (_script_data[name]) {
            _script_data[name]->data = data
            event_save(self)


    def set_script_actors(self, name: str, actors: Any) -> None:
            if (_script_data[name]) {
            _script_data[name]->actors = actors
            event_save(self)


    def set_script_data_location(self, name: str, pos: int, script_data: Any) -> int:
            if (_script_data[name] &&
            pos >= 0 && pos < sizeof(_script_data[name]->data)) {
            _script_data[name]->data[pos] = data
            event_save(self)
            return 1


    def delete_script_data_location(self, name: str, pos: int) -> int:
            if (_script_data[name] &&
            pos >= 0 && pos < sizeof(_script_data[name]->data)) {
            _script_data[name]->data = _script_data[name]->data[0..pos-1] +
            _script_data[name]->data[pos+1..]
            event_save(self)
            return 1


    def insert_script_data_before(self, name: str, pos: int, script_data: Any) -> int:
            if (_script_data[name]) {
            _script_data[name]->data = _script_data[name]->data[0..pos-1] +
            [data] +
            _script_data[name]->data[pos..]
            event_save(self)
            return 1


    def menu_prompt(self, name: str, script: Any) -> None:
            tell_object( this_player(), "Enter the name of the person who should "
            "perform an action ( or another command such as \"wait\" ).\n" )
            print_commands()
            input_to( "menu_input", 0, name, script )


    def menu_input(self, input: str, name: str, script: Any) -> None:
            string* bits
            bits = explode(lower_case(input), " ")
            switch (lower_case(bits[0])) {
            case "h" :
            case "help" :
            show_help()
            break
            case "s" :
            case "save" :
            set_script(name, script)
            break
            case "q" :
            case "quit" :
            write("Are you sure you want to quit and "
            "lose the current script?\n" )
            input_to( "check_quit", 0, name, script )
            return
            case "l" :
            case "list" :
            write(query_script_string(script))
            break
            case "a" :
            case "add" :
            if (sizeof(bits) != 3) {
            write("Syntax: add <person> <pos|end|begining>\n")
            } else if (lower_case(bits[1]) != "wait" &&
            script->actors.index(bits[1]) if bits[1] in script->actors else -1 == -1) {
            write("The actor must be one of " +
            query_multiple_short(script->actors)  + " not " +
            bits[1] + ".\n")
            } else {
            pos = query_pos_from_string(bits[2])
            if (pos != -1) {
            write("Which command do you want to execute for " + bits[1] +
            "?\n: ")
            input_to("enter_command", 0, name, script, bits[1], pos)
            } else {
            write("The position must be in the range 0.." +
            sizeof(script->data) + " or 'begining' or 'end'.\n")


    def print_commands(self, ) -> None:
            await  this_player().send("Command [ h for help ]:\n" )


    def show_help(self, ) -> None:
            string str
            str = unguarded((: NROFF_HAND.cat_file("/doc/room/scripting_nroff", 1) :))
            if(!str){
            unguarded((: NROFF_HAND->create_nroff(PATH +"scripting_online_help",
            PATH +"scripting_nroff") :))
            str = unguarded((:NROFF_HAND.cat_file(PATH +"scripting_nroff", 0):))


    def query_quit(self, input: str, func: str) -> None:
            if( (input == "y") || (input == "yes") || (input == "Y") ){
            write("Okay, quitting.\n" )
            }else{
            write("%^BOLD%^You did not enter \"y\" "
            "or \"yes\" so you are not being quitted.%^RESET%^\n" )
            call_other( self, func )


    def set_script(self, name: str, scripting: Any) -> None:
            write("Saving current script and exiting.\n" )
            _scripts[name] = script
            event_save( self )


    def query_script_string(self, scripting: Any) -> str:
            int i
            string str
            if( _temp_script->tag == "" ) {
            return


    def query_delete(self, input: str, num: int) -> None:
            if( (input == "y") || (input == "yes") || (input == "Y") ){
            await  this_player().send("Okay, removing script.\n" )
            if( sizeof(_script_data) == 1 ){
            _script_data = ({})
            }else if( sizeof(_script_data) == 2 ){
            _script_data = ({_script_data[!num]})
            }else{
            if( !num ){
            _script_data = _script_data[1..]
            }else{
            _script_data = _script_data[0..(num - 1)] +
            _script_data[(num + 1)..]


    def get_index(self, input: Any) -> int:
            int i
            if( to_int( input ) ){
            i = to_int( input )
            if( i > sizeof(_script_data) ){
            await  this_player().send("Invalid option, quitting.\n" )
            return -1
            }else{
            return i - 1


    def edit_script(self, input: str, which: int) -> None:
            string *comm, command, text
            int line, i
            if( input == "" ){
            input_to( "edit_script", 0, which )
            await  this_player().send("Command [ R(eplace), D(elete), "
            "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" )
            return


    def do_add_script(self, input: str) -> int:
            if( input == "" ){
            tell_object( this_player(),
            "You must enter a name for the script.\n" )
            add_succeeded_mess( "" )
            return 1


    def do_list_scripts(self, ) -> int:
            int i
            if( !sizeof(_script_data) ){
            this_player()->add_failed_mess( self,
            "No scripts found.\n" )
            return 0


    def do_view_script(self, input: Any) -> int:
            int num
            num = get_index( input )
            if( num == -1 ){
            add_succeeded_mess( "" )
            return 1


    def do_test_script(self, input: Any) -> int:
            int num
            num = get_index( input )
            if( num == -1 ){
            add_succeeded_mess( "" )
            return 1


    def do_delete_script(self, input: Any) -> int:
            int num
            num = get_index( input )
            if( num == -1 ){
            add_succeeded_mess( "" )
            return 1


    def do_edit_script(self, input: Any) -> int:
            int num, i
            num = get_index( input )
            if( num == -1 ){
            add_succeeded_mess( "" )
            return 1


    def init(self, ) -> None:
            if( !is_allowed( this_player()->query_name() ) ) {
            return



class Scripting(MudObject):
