# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/modified_efuns.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def find_player(self, string) -> MudObject:
            #endif
            private nosave int _callouttime
            private nosave mapping _calloutfunc = ([])
            private nosave mapping _log_file_info = ([ ])
            private nosave int _log_file_flush_id
            private nosave mapping _loggers = ([ ])
            private nosave string _reset_eval_message="simul_efun updated"
            private nosave int _reset_eval_message_count=1
            private nosave int _in_reference_allowed
            #define DELAY_LOG_FLUSH 15
            varargs void say(string str, mixed avoid)
            {
            if (!pointerp(avoid)) {
            avoid = [this_player(), previous_object()] + [avoid]
            } else {
            avoid += [this_player(), previous_object()]


    def tell_object(self, ob: MudObject, str: str) -> None:
            if (objectp(ob)) {
            ob.do_efun_write( str )


    def find_living(self, word: str) -> MudObject:
            object thing
            if ( !word ) {
            return 0


    def find_player(self, word: str) -> MudObject:
            object thing
            if ( !word ) {
            return 0


    def user_event(self, from: Any, first: Any, args: Any) -> None:
            if ( stringp( from ) ) {
            call_other( efun::users(), "event_"+ from, previous_object(),
            first, args ... )
            } else {
            if ( objectp( from ) && stringp( first ) ) {
            call_other( efun::users(), "event_"+ first, from, args ... )


    def flush_log_files(self, ) -> None:
            string fname
            string data
            int size
            _log_file_flush_id = 0
            foreach (fname, data in _log_file_info) {
            size = file_size(LOG_NAME(fname))
            if (size > MAX_SIZE) {
            if ( file_size( LOG_NAME(fname) + ".5" ) >= 0 ) {
            unguarded((: rm, LOG_NAME(fname)+".5" :))


    def mud_name(self, ) -> str:
            return capitalize(MUD_NAME)


    def cat(self, file: str, start_line: int, number: int) -> None:
            string bing
            bing = read_file(file, start_line, number)
            if (bing) {
            printf("%s", bing[0..5000])


    def wizardp(self, arg: Any) -> int:
            if (!objectp(arg)) {
            return 0


    def exec(self, to: MudObject, from: MudObject) -> int:
            string s
            object prev
            if(!objectp(to) || !objectp(from))
            return 0
            if (file_name(previous_object())[0..12] == "/secure/login" ||
            file_name(previous_object())[0..13] == "/secure/nlogin") {
            return efun::exec(to, from)


    def query_verb(self, ) -> str:
            string verb
            #if efun_defined(query_verb)
            verb = efun::query_verb()
            #else
            verb = ""
            #endif
            if ( ( verb != "" ) || !objectp( this_player() ) ) {
            return verb


    def strcasecmp(self, str1: str, str2: str) -> int:
            return strcmp(lower_case(str1), lower_case(str2))


    def tail(self, fname: str) -> int:
            int offset = file_size(fname)
            string str
            if (offset < 0) {
            return 0


    def write(self, str: Any) -> None:
            if (!this_player()) {
            return


    def notify_fail(self, stuff: Any) -> int:
            if (!this_player())  {
            return 0


    def cap_words(self, words: str) -> str:
            return implode(map(explode(words, " "), (: capitalize :)), " ")


    def reset_eval_cost(self, ) -> None:
            int i
            string *funs, stack
            object *obs
            if(time() == eval_cost_time && previous_object() == eval_ob) {
            if(real_time() - eval_cost_real_time > 5) {
            stack = ""
            obs = call_stack(1)
            funs = call_stack(2)
            for(i=0; i<sizeof(obs); i++) {
            if(clonep(obs[i]))
            stack += base_name(obs[i]) + "#" + obs[i]->query_name()
            else
            stack += base_name(obs[i])
            stack += "->" + funs[i] + "()\n"


    def event(self, ob: Any, func: str, rest: Any) -> None:
            object origin = previous_object(), *bing
            string name = "event_" + func
            if(arrayp(ob)){
            ob = filter(ob, (:$1:))
            call_other(ob, name, origin, rest ...)
            return
            } else if(!objectp(ob)) {
            return


    def move_object(self, ob: Any) -> None:
            object tp, *obs, bing
            if(stringp(ob)) {
            ob = find_object(ob)


    def shutdown(self, bing: int) -> None:
            string thing = base_name(previous_object())
            if(thing != "/obj/shut" && thing != "/global/lord"){
            unguarded((:write_file, "/d/admin/log/SHUTDOWN.log",
            sprintf("value %d\n%s", bing, back_trace()):))


    def memory_summary(self, ) -> str:
            return "Not on this mud...\n"


    def debug_info(self, operation: int, ob: MudObject) -> str:
            string path
            if ( operation != 2 )
            return efun::debug_info( operation, ob )
            path = base_name( ob )
            path += ".c"
            if ( !master()->valid_read( path,
            this_player()->query_name(), "debug_info" ) ) {
            self->unguarded((:write_file, "/d/admin/log/DEBUG_INFO.log",
            sprintf( "%s: %s tried to debug %s.\n", ctime( time() ),
            this_player()->query_name(),
            base_name( ob ) ) :))
            return "You are not authorised to do that.\n"


    def input_to(self, fun: Any, flag: Any, args: Any) -> None:
            function f = function(string input, object ob, mixed fun, mixed args){
            int t = real_time()
            if(functionp(fun))
            evaluate(fun, input, args...)
            else
            evaluate(bind((:call_other, ob, fun, input, args ...:), ob))
            if((real_time() - t) > 1) {
            if(fun == "logon2")
            input = "******"
            self.log_file("GARBAGE", "input_to %O (%O) in %O, time: %d\n",
            fun, input,
            ob, real_time() - t)



class Modified_efuns(MudObject):
