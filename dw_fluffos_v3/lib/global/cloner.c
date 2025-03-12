#define SAVE_FILE "/save/cloner"
#define SAVE_FILE_DELAY 15
#define LIFE_TIME 7257600
inherit "/std/object";
mapping changes;
mapping illegal;
private nosave int _save_file_call_out;
mapping query_changes() {
   return changes;
}
void save_file() {
   _save_file_call_out = 0;
   unguarded((: save_object, SAVE_FILE:));
}
void load_file() {
   if (file_size(SAVE_FILE + ".o") > 0)
      unguarded((: restore_object, SAVE_FILE:));
}
void setup() {
   changes = ([]);
   illegal = ([]);
   load_file();
   _save_file_call_out = 0;
}
object clone( string word ) {
   string new_file;
   object thing;
   if ( changes[ word ] && new_file = changes[ word ][ 0 ] )
      word = new_file;
   catch( thing = clone_object( word ) );
   return thing;
}
string other_file( string word ) {
   if ( changes[ word ] )
      return changes[ word ][ 0 ];
   return word;
}
int add_mapping( string from, string to ) {
  string obj_name;
  if(from[<2..] == ".c")
    from = from[0..<3];
  if(to[<2..] == ".c")
    to = to[0..<3];
  if((file_size(to) < 1) && (file_size(to+".c") < 1)) {
    write("Destination file does not exist\n");
    return 0;
  }
  changes[from] = ({to, time()});
  if ( !_save_file_call_out ) {
        _save_file_call_out = call_out( (: save_file :), SAVE_FILE_DELAY );
  }
  if ( !this_player() ) {
      obj_name = file_name( previous_object() );
  }
  else {
      obj_name = this_player()->query_cap_name();
  }
  write("Mapping of "+from+" to "+to+" added.\n");
  log_file("CLONER", "Mapping of "+from+" to "+to+" added by "+
           obj_name +" at "+ctime(time())+".\n");
  remove_call_out("clean_up");
  call_out("clean_up", 120 + random(500));
  return 1;
}
int remove_mapping( string from ) {
   string obj_name;
   if ( changes && changes[ from ] ) {
      map_delete( changes, from );
      save_file();
      write( "Mapping of " + from + " removed.\n" );
      if ( !this_player() ) {
          obj_name = file_name( previous_object() );
      }
      else {
          obj_name = this_player()->query_cap_name();
      }
      log_file( "CLONER", "Mapping of " + from + " removed by " +
          obj_name + " at " + ctime( time() ) + ".\n" );
      return 1;
   }
   write("No mapping found for " + from + ".\n");
   return 0;
}
string list_mappings( string str ) {
   string from, retval;
   retval = "";
   foreach(from in keys(changes)) {
      if (!str ||
          strsrch(from, str) != -1 ||
          strsrch(changes[from][0], str) != -1)
         retval += from + " -> " + changes[from][0] + "\n";
   }
   return retval;
}
int add_illegal(string basename, string short, string replacement) {
  if(!illegal)
    illegal = ([ ]);
  if(illegal[basename + ":" + short])
    return 0;
  if((file_size(replacement) < 1) && (file_size(replacement+".c") < 1))
    return 0;
  illegal[basename + ":" + short] = replacement;
  save_file();
  return 1;
}
int remove_illegal(string basename, string short) {
  if(!illegal)
    return 0;
  if(!illegal[basename+":"+short])
    return 0;
  map_delete(illegal, basename+":"+short);
  save_file();
  return 1;
}
mapping query_illegal() {
  return illegal;
}
string illegal_thing(string basename, string short) {
  if(!illegal)
    return 0;
  return illegal[basename + ":" + short];
}
void clean_up() {
   string from;
   mixed  *to;
   foreach(from, to in changes)
      if ((to[1] < time() - LIFE_TIME) ||
          ((file_size(to[0]) < 1) && (file_size(to[0] + ".c") < 1)))
         map_delete(changes, from);
   save_file();
}