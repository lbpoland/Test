inherit "/obj/baggage";
private mapping details;
private nosave string _save_file;
private object _loading;
private nosave int _can_recurse;
varargs void do_load( object thing ) {
   if ( _save_file ) {
      all_inventory( this_object() ) -> dest_me();
      if ( file_size( _save_file + ".o" ) > 0 ) {
         unguarded((: restore_object, _save_file :));
         if ( thing ) {
            set_player( thing );
         }
         if ( sizeof( details ) ) {
            init_dynamic_arg( details, 0 );
         }
      }
   }
}
void create() {
   _save_file = "";
   details = ([ ]);
   _can_recurse = 0;
   ::create();
}
protected int handle_restore_inventory(object ob) {
   _loading = ob;
   return ::handle_restore_inventory(ob);
}
string query_long_details(string arg, int dark, object looker) {
   string ret;
   ret = ::query_long_details(arg, dark, looker);
   if (query_auto_loading()) {
      return ret + the_short() + " contents is still being generated.\n";
   }
   return ret;
}
int test_remove( object thing, int flag, mixed dest ) {
   if (!query_auto_loading()) {
      remove_call_out( "do_save" );
      if ( find_call_out( "do_save" ) == -1 ) {
         call_out( "do_save", 1 );
      }
      return ::test_remove( thing, flag, dest );
   } else if (_loading == thing) {
      return ::test_remove( thing, flag, dest );
   } else {
      return 0;
   }
}
int test_add( object ob, int flag) {
   if (!query_auto_loading()) {
      remove_call_out( "do_save" );
      if ( find_call_out( "do_save" ) == -1 ) {
         call_out( "do_save", 1 );
      }
      return 1;
   } else if (_loading == ob) {
      return ::test_add( ob, flag );
   } else {
      return 0;
   }
}
void do_save() {
   if ( _save_file && _save_file != "" &&
        !query_auto_loading()) {
      details = ([ ]);
      details = query_dynamic_auto_load();
      unguarded((: save_object, _save_file :));
   }
}
void check_euid() {
   if ( previous_object() ) {
      seteuid( geteuid( previous_object() ) );
   }
}
varargs void set_save_file( string file, object thing ) {
   _save_file = file;
   call_out( "do_load", 0, thing );
}
string query_save_file() {
   return _save_file;
}
void set_can_recurse(int recurse_flag) { _can_recurse = recurse_flag; }
int query_can_recurse() { return _can_recurse; }
int can_find_match_recurse_into(object looker) {
   if (query_closed()) {
      return 0;
   }
   if (!_can_recurse)
      return ::can_find_match_recurse_into(looker);
   return 1;
}