inherit "/obj/weapon";
string *patterns = ({
  "with <direct:object> in <string>",
  "with <direct:object> in <indirect:object>",
  "with <direct:object>",
  "[in] <string> with <direct:object>",
  "[in] <indirect:object> with <direct:object>"
});
void init(){
  this_player()->add_command("dig", this_object(), patterns);
}
int do_dig( object *things, string dir_match, string
            indir_match, mixed *args, string pattern) {
  object *obj, indir;
  string indir_s;
  if (!objectp(environment(this_player()))) {
    return 0;
  }
  obj=this_player()->query_holding();
  if(member_array(this_object(), obj) == -1){
    this_player()->add_failed_mess(this_object(), "You must hold the $D to "
                                   "dig with it.\n", ({}));
    return 0;
  }
  if (pattern == patterns[4]) {
    if (!objectp(indir = things[0])) {
      return 0;
    }
    indir_s = args[0];
  } else if (pattern == patterns[3]) {
    indir_s = args[0];
    indir = 0;
  } else if (pattern == patterns[2]) {
    indir_s = 0;
    indir = 0;
  } else if (pattern == patterns[1]) {
    if (!objectp(indir = things[0])) {
      return 0;
    }
    indir_s = args[1];
  } else if (pattern == patterns[0]) {
    indir_s = args[1];
    indir = 0;
  } else {
    return 0;
  }
  return environment(this_player())->dig(indir, indir_s);
}
mapping query_static_auto_load() {
   if ( explode( file_name( this_object() ), "#" )[ 0 ] == "/obj/shovel" )
      return int_query_static_auto_load();
   return ([ ]);
}