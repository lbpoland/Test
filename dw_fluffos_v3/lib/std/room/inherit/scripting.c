#include <expressions.h>
#include "nroff.h";
inherit "/std/basic/expressions";
#define SCRIPTING_WAIT_COMMAND  1
#define SCRIPTING_COMMAND       2
#define SCRIPTING_EXPRESSION    3
#define SCRIPTING_GOTO          4
#define SCRIPTING_TRIGGER_EVENT 5
class script_data {
   int type;
   string actor;
   string str;
   class parse_node* expr;
   int number;
}
class script {
   string* valid_actors;
   class script_data* data;
   int priority;
}
class running_script {
   class script script;
   int position;
   object who;
   string who_name;
   string who_short;
   int run_priority;
}
private mapping _script_data;
private nosave int _callout_tag;
private nosave class running_script* _running_scripts;
object find_npc( string what );
int is_allowed( string name );
void event_save( object ob );
class script query_script( string name ){
   return _script_data[name];
}
private void add_running_script(class running_script script) {
   if (!sizeof(_running_scripts)) {
      _running_scripts += ({ script });
      return ;
   }
}
void trigger_script( string event, object who, int override ){
   int i;
   class script this_script;
   class running_script running;
   this_script = query_script( event );
   if (!this_script || !objectp(who)) {
      return;
   }
   running = new(class running_script);
   running->script = this_script;
   running->who = who;
   running->position = 0;
   running->who_name = who->query_name();
   running->who_short = who->the_short();
   if (undefinedp(override)) {
      running->run_priority = this_script->priority;
   } else {
      running->run_priority = override;
   }
   add_running_script(running);
}
void repeat_loop() {
   object npc;
   class script_data data;
   string str;
   class parse_node node;
   if (!sizeof( _running_scripts ) ) {
      return;
   }
   if (_running_scripts[0]->position >= sizeof(_running_scripts[0]->script)) {
      _running_scripts = _running_scripts[1..];
      if (!sizeof( _running_scripts ) ) {
         return;
      }
   }
   data = _running_scripts[0]->script->data[_running_scripts[0]->position];
   _running_scripts[0]->position++;
   _callout_tag = call_out( "repeat_loop", 2);
   switch ( data->type) {
   case SCRIPTING_WAIT_COMMAND :
      remove_call_out(_callout_tag);
      _callout_tag = call_out( "repeat_loop",  data->number);
      return;
   case SCRIPTING_COMMAND :
      npc = find_npc( data->actor );
      if( !npc ){
         repeat_loop();
         return;
      }
      npc->do_command( data->str );
      break;
   case SCRIPTING_EXPRESSION :
      node = evaluate_expresion(data->expr);
      if (node->type == EXPRESSION_TYPE_STRING) {
         npc = find_npc( data->actor );
         if (!npc) {
            repeat_loop();
            return ;
         }
         npc->do_command( data-> str );
      }
      break;
   case SCRIPTING_GOTO :
      _running_script[0]->position = data->number;
      break;
   case SCRIPTING_TRIGGER_EVENT :
      trigger_script(data->name, _running_script[0]->npc,
                     _running_script[0]->run_priority | PRIORITY_FRONT);
      break;
   }
   call_out("repeat_loop");
}
void set_script(string name, class script script) {
   _script_data[name] = script;
   event_save(this_object());
}
void set_script_data(string name, class script_data* data) {
   if (_script_data[name]) {
      _script_data[name]->data = data;
      event_save(this_object());
   }
}
void set_script_actors(string name, string* actors) {
   if (_script_data[name]) {
      _script_data[name]->actors = actors;
      event_save(this_object());
   }
}
int set_script_data_location(string name, int pos, class script_data data) {
   if (_script_data[name] &&
       pos >= 0 && pos < sizeof(_script_data[name]->data)) {
      _script_data[name]->data[pos] = data;
      event_save(this_object());
      return 1;
   }
   return 0;
}
int delete_script_data_location(string name, int pos) {
   if (_script_data[name] &&
       pos >= 0 && pos < sizeof(_script_data[name]->data)) {
      _script_data[name]->data = _script_data[name]->data[0..pos-1] +
                                 _script_data[name]->data[pos+1..];
      event_save(this_object());
      return 1;
   }
   return 0;
}
int insert_script_data_before(string name, int pos, class script_data data) {
   if (_script_data[name]) {
      _script_data[name]->data = _script_data[name]->data[0..pos-1] +
                                 ({ data }) +
                                 _script_data[name]->data[pos..];
      event_save(this_object());
      return 1;
   }
   return 0;
}
void menu_prompt(string name, class* script) {
   tell_object( this_player(), "Enter the name of the person who should "
      "perform an action ( or another command such as \"wait\" ).\n" );
   print_commands();
   input_to( "menu_input", 0, name, script );
}
private int query_pos_from_string(string str) {
   if (bits[2] == "begining") {
      return 0;
   } else if (bits[2] == "end") {
      return sizeof(script->data);
   } else {
      pos = to_int(bits[2]);
   }
   if (pos < 0 || pos > sizeof(script->data)) {
      return -1;
   }
   return pos;
}
void menu_input( string input, string name, class script script ){
   string* bits;
   bits = explode(lower_case(input), " ");
   switch (lower_case(bits[0])) {
   case "h" :
   case "help" :
      show_help();
      break;
   case "s" :
   case "save" :
      set_script(name, script);
      break;
   case "q" :
   case "quit" :
      write("Are you sure you want to quit and "
         "lose the current script?\n" );
      input_to( "check_quit", 0, name, script );
      return ;
   case "l" :
   case "list" :
      write(query_script_string(script));
      break;
   case "a" :
   case "add" :
      if (sizeof(bits) != 3) {
         write("Syntax: add <person> <pos|end|begining>\n");
      } else if (lower_case(bits[1]) != "wait" &&
                 member_array(bits[1], script->actors) == -1) {
         write("The actor must be one of " +
               query_multiple_short(script->actors)  + " not " +
               bits[1] + ".\n");
      } else {
         pos = query_pos_from_string(bits[2]);
         if (pos != -1) {
            write("Which command do you want to execute for " + bits[1] +
                  "?\n: ");
            input_to("enter_command", 0, name, script, bits[1], pos);
         } else {
            write("The position must be in the range 0.." +
                  sizeof(script->data) + " or 'begining' or 'end'.\n");
         }
      }
      break;
   case "d" :
   case "delete" :
      if (sizeof(bits) != 2) {
         write("Syntax: delete <pos|end|begining>\n");
      } else {
         pos = query_pos_from_string(bits[2]);
         if (pos != -1) {
         } else {
            write("The position must be in the range 0.." +
                  sizeof(script->data) + " or 'begining' or 'end'.\n");
         }
      }
      break;
   default :
      write("Invalid command " + bits[1] + ".\n");
   }
   menu_prompt(name, script);
}
protected void enter_command( string input, string name, class script script ) {
   if( _temp_script->script[sizeof( _temp_script->script ) - 1] == "wait" ){
      if( !to_int(input) ){
         tell_object( this_player(), "%^BOLD%^For the wait command you "
            "must enter a whole value for the number of seconds "
            "to wait%^RESET%^.\n" );
         prompt_command();
         return;
      }
   }
   _temp_script->script = _temp_script->script + ({input});
   tell_object( this_player(), "Enter the name of the person who should "
      "perform an action ( or another command such as \"wait\" ).\n" );
   print_commands();
   input_to( "input_name" );
}
void print_commands(){
   tell_object( this_player(), "Command [ h for help ]:\n" );
}
void show_help(){
   string str;
   str = unguarded((: NROFF_HAND->cat_file("/doc/room/scripting_nroff", 1) :));
   if(!str){
     unguarded((: NROFF_HAND->create_nroff(PATH +"scripting_online_help",
        PATH +"scripting_nroff") :));
     str = unguarded((:NROFF_HAND->cat_file(PATH +"scripting_nroff", 0):));
   }
   write(str);
}
void query_quit( string input, string func ){
   if( (input == "y") || (input == "yes") || (input == "Y") ){
      write("Okay, quitting.\n" );
   }else{
      write("%^BOLD%^You did not enter \"y\" "
         "or \"yes\" so you are not being quitted.%^RESET%^\n" );
      call_other( this_object(), func );
   }
}
void set_script(string name, class scripting* script) {
   write("Saving current script and exiting.\n" );
   _scripts[name] = script;
   event_save( this_object() );
}
string query_script_string( class scripting* script ){
   int i;
   string str;
   if( _temp_script->tag == "" ) {
      return;
   }
   str = "\nScript name \""+ _temp_script->tag + ":\n\n";
   for( i = 0; i < sizeof(_temp_script->script); i++ ){
      str += _temp_script->script[i]->name +"  :  ";
      str += _temp_script->script[i]->action +"\n";
   }
   str += "\n";
   return str;
}
void query_delete( string input, int num ){
   if( (input == "y") || (input == "yes") || (input == "Y") ){
      tell_object( this_player(), "Okay, removing script.\n" );
      if( sizeof(_script_data) == 1 ){
         _script_data = ({});
      }else if( sizeof(_script_data) == 2 ){
         _script_data = ({_script_data[!num]});
      }else{
         if( !num ){
            _script_data = _script_data[1..];
         }else{
            _script_data = _script_data[0..(num - 1)] +
               _script_data[(num + 1)..];
         }
      }
      event_save( this_object() );
   }else{
      tell_object( this_player(), "%^BOLD%^You did not enter \"y\" or "
         "\"yes\" so the script will not be deleted.%^RESET%^\n" );
   }
   _temp_script->tag = "";
   _temp_script->script = ({});
}
int get_index( mixed input ){
   int i;
   if( to_int( input ) ){
      i = to_int( input );
      if( i > sizeof(_script_data) ){
         tell_object( this_player(), "Invalid option, quitting.\n" );
         return -1;
      }else{
         return i - 1;
      }
   }else{
      for( i = 0; i < sizeof(_script_data); i++ ){
         if( _script_data[i]->tag == input ) return i;
      }
      tell_object( this_player(), "Invalid option, quitting.\n" );
      return -1;
   }
}
void edit_script( string input, int which ){
   string *comm, command, text;
   int line, i;
   if( input == "" ){
      input_to( "edit_script", 0, which );
      tell_object( this_player(), "Command [ R(eplace), D(elete), "
         "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
      return;
   }
   command = "";
   line = -1;
   text = "";
   comm = explode( input, " " );
   if( sizeof(comm) ) command = comm[0];
   if( sizeof(comm) > 1) line = to_int(comm[1]) - 1;
   if( sizeof(comm) > 2){
      comm = comm[2..];
      text = implode(comm, " ");
   }
   switch (command){
      case "s" :
      case "S" :
         tell_object( this_player(), "Done editing script.\n" );
         _script_data[which]->script = _temp_script->script;
         return;
      case "q" :
      case "Q" :
         tell_object( this_player(), "Quitting without saving changes.\n");
         return;
      case "v" :
      case "V" :
         for( i = 0; i < sizeof(_temp_script->script); i++ )
            tell_object(this_player(),(i+1) +"  "+
               _temp_script->script[i] +"\n");
            input_to( "edit_script", 0, which );
            tell_object( this_player(), "Command [ R(eplace), D(elete), "
               "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
            return;
      case "d" :
      case "D" :
         if( (line < 0) || ((line +1) > sizeof(_temp_script->script)) ){
            tell_object( this_player(), "For this command you need to "
               "enter a valid line number.\n" );
            input_to( "edit_script", 0, which );
            tell_object( this_player(), "Command [ R(eplace), D(elete), "
               "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n");
            return;
         }
         if( sizeof(_temp_script->script) == 1 ){
            _temp_script->script = ({});
         }else if( sizeof(_temp_script->script) == 2 ){
            _temp_script->script = ({_temp_script->script[!line]});
         }else{
            _temp_script->script = _temp_script->script[0..(line-1)] +
                _temp_script->script[line+1..];
         }
         tell_object( this_player(), "Line "+ (line+1) +" deleted.  "
            "Please note that the line numbers for the rest of the "
            "script may have been effected by this change.\n" );
         input_to( "edit_script", 0, which );
         tell_object( this_player(), "Command [ R(eplace), D(elete), "
            "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
         return;
      case "r" :
      case "R" :
         if( (line < 0) || ((line +1) > sizeof(_temp_script->script)) ){
            tell_object( this_player(), "For this command you need to "
               "enter a valid line number.\n" );
            input_to( "edit_script", 0, which );
            tell_object( this_player(), "Command [ R(eplace), D(elete), "
               "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
            return;
         }
         tell_object( this_player(), "Replacing line "+ (line+1) +" with \""+
            text +"\".\n" );
         _temp_script->script[line] = text;
         input_to( "edit_script", 0, which );
         tell_object( this_player(), "Command [ R(eplace), D(elete), "
            "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
         return;
      case "i" :
      case "I" :
         if( (line < 0) || ((line +1) > sizeof(_temp_script->script)) ){
            tell_object( this_player(), "For this command you need to "
               "enter a valid line number.\n" );
            input_to( "edit_script", 0, which );
            tell_object( this_player(), "Command [ R(eplace), D(elete), "
               "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
            return;
         }
         tell_object( this_player(), "Inserting \""+ text +"\" at line "+
            (line+1) +".  Please note that the line numbers for the rest "
            "of the script may have been effected by this change.\n" );
         if( !line ){
            _temp_script->script = ({text}) + _temp_script->script;
         }else{
            _temp_script->script = _temp_script->script[0..(line-1)] +
               ({text}) + _temp_script->script[line..];
         }
         input_to( "edit_script", 0, which );
         tell_object( this_player(), "Command [ R(eplace), D(elete), "
            "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
         return;
      default :
         tell_object( this_player(),"%^BOLD%^Unknown command.\n%^RESET%^");
         input_to( "edit_script", 0, which );
         tell_object( this_player(), "Command [ R(eplace), D(elete), "
            "I(nsert), V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
         return;
   }
}
int do_add_script( string input ){
   if( input == "" ){
      tell_object( this_player(),
         "You must enter a name for the script.\n" );
      add_succeeded_mess( "" );
      return 1;
   }
   if( return_script( input ) != ({}) ){
      tell_object( this_player(), "%^BOLD%^There is already a script for \""+
         input +"\", if you wish to keep the existing version then quit "
         "now and start over, if you continue the new version will "
         "replace the old one.%^RESET%^\n" );
   }else{
      tell_object( this_player(), "This script will be known as \""+
         input +"\".\n" );
   }
   _temp_script = new(class fancy_hat, tag : input, script : ({}) );
    tell_object( this_player(), "Enter the name of the person who should "
      "perform an action, or another command such as \"wait\". eg\n\n"
      "  \"mike\"\n"
      "  \"thug1\"\n"
      "  \"wait\"\n" );
   print_commands();
   input_to( "input_name" );
   add_succeeded_mess( "$N begin$s to write a new script.\n" );
   return 1;
}
int do_list_scripts(){
   int i;
   if( !sizeof(_script_data) ){
      this_player()->add_failed_mess( this_object(),
         "No scripts found.\n" );
      return 0;
   }
   tell_object(this_player(), sizeof(_script_data) +" scripts found:\n\n");
   for( i = 0; i < sizeof(_script_data); i++ )
      tell_object( this_player(), (i +1) +"  "+ _script_data[i]->tag +"\n");
   add_succeeded_mess( "" );
   return 1;
}
int do_view_script( mixed input ){
   int num;
   num = get_index( input );
   if( num == -1 ){
      add_succeeded_mess( "" );
      return 1;
   }
   if( undefinedp( _temp_script ) ){
      _temp_script = new( class fancy_hat,
      tag : _script_data[num]->tag, script : _script_data[num]->script );
   }else{
      _temp_script->tag = _script_data[num]->tag;
      _temp_script->script = _script_data[num]->script;
   }
   view_script(1);
   add_succeeded_mess( "" );
   return 1;
}
int do_test_script( mixed input ){
   int num;
   num = get_index( input );
   if( num == -1 ){
      add_succeeded_mess( "" );
      return 1;
   }
   tell_object( this_player(), "Triggering event \""+
      _script_data[num]->tag +"\".\n" );
   trigger_thingy( _script_data[num]->tag, file_name( this_player()) );
   add_succeeded_mess( "" );
   return 1;
}
int do_delete_script( mixed input ){
   int num;
   num = get_index( input );
   if( num == -1 ){
      add_succeeded_mess( "" );
      return 1;
   }
   if( undefinedp( _temp_script ) ){
      _temp_script = new( class fancy_hat,
      tag : _script_data[num]->tag, script : _script_data[num]->script );
   }else{
      _temp_script->tag = _script_data[num]->tag;
      _temp_script->script = _script_data[num]->script;
   }
   tell_object( this_player(), "Are you sure that you want to "
      "permanently remove the script \""+ _temp_script->tag +"\"?\n" );
   input_to( "query_delete", 0, num );
   add_succeeded_mess( "" );
   return 1;
}
int do_edit_script( mixed input ){
   int num, i;
   num = get_index( input );
   if( num == -1 ){
      add_succeeded_mess( "" );
      return 1;
   }
   if( undefinedp( _temp_script ) ){
      _temp_script = new( class fancy_hat,
      tag : _script_data[num]->tag, script : _script_data[num]->script );
   }else{
      _temp_script->tag = _script_data[num]->tag;
      _temp_script->script = _script_data[num]->script;
   }
   tell_object( this_player(), "Editing script \""+ _temp_script->tag +
      "\".\n\nThis is a complete listing of the script:\n" );
   for( i = 0; i < sizeof(_temp_script->script); i++ ){
      tell_object(this_player(),(i+1) +"  "+ _temp_script->script[i] +"\n");
   }
   tell_object( this_player(), "Command [ R(eplace), D(elete), I(nsert), "
      "V(iew), S(ave), Q(uit) ]:\nEg \"R 13 rabbit\".\n" );
   input_to( "edit_script", 0, num );
   add_succeeded_mess( "" );
   return 1;
}
void init(){
   if( !is_allowed( this_player()->query_name() ) ) {
      return;
   }
   add_command( "add",
      "script <string'name'>", (: do_add_script( $4[0] ) :) );
   add_command( "list", "scripts",
      (: do_list_scripts() :) );
   add_command( "view",
      "script <string'name'>", (: do_view_script( $4[0] ) :) );
   add_command( "view",
      "script <number>", (: do_view_script( $4[0] ) :) );
   add_command( "test",
      "script <string'name'>", (: do_test_script( $4[0] ) :) );
   add_command( "test", this_object(),
      "script <number>", (: do_test_script( $4[0] ) :) );
   add_command( "delete",
      "script <string'name'>", (: do_delete_script( $4[0] ) :) );
   add_command( "delete",
      "script <number>", (: do_delete_script( $4[0] ) :) );
   add_command( "edit",
      "script <string'name'>", (: do_edit_script( $4[0] ) :) );
   add_command( "edit",
      "script <number>", (: do_edit_script( $4[0] ) :) );
}