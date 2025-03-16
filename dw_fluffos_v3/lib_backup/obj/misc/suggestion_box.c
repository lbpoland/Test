inherit "/std/object";
int do_fill();
string _savedir, _savefile;
void setup() {
  set_short( "suggestion box" );
  set_long( "This is a suggestion box.  It is sitting on a pole which puts"
	    " the box at a convienient height for writing.  It has a pile "
	    "of small papers on it on which you can write suggestions.  "
	    "There is a slot in the top for stuffing the suggestion in "
	    "when you're done.\n" );
  set_name( "box" );
  set_main_plural( "boxes" );
  set_read_mess( "\nPlease fill in a suggestion form", "common" );
  add_property( "there", "sitting in the middle of the floor" );
  set_weight( 1000 );
  reset_get();
}
void init() {
  add_command( "fill", "in a suggestion form", (: do_fill() :) );
}
void set_save_file ( string file ) {
  _savefile = file;
  return;
}
void set_save_dir ( string dir ) {
  _savedir = dir;
  return;
}
string query_save_file () {
  return _savefile;
}
string query_save_dir () {
  return _savedir;
}
int do_fill() {
  tell_object( this_player(), "Please fill in your suggestion below.\n" );
  this_player()->do_edit( 0, "end_suggestion", this_object() );
  add_succeeded_mess( ({"", "$N fill$s in a suggestion form and stuff$s "
			  "it in the box.\n" }) );
  return 1;
}
void end_suggestion( string text ) {
  string player, file;
  if( _savefile ) {
    file = _savefile;
  } else if( _savedir ) {
    player = previous_object()->query_name();
    file = sprintf( query_save_dir() + "/%s-%d.txt", player, time() );
  }
  debug_printf( "File: %s", file );
  if( !(unguarded( (: write_file, file, text :) ) ) ) {
    tell_object( previous_object(), "Sorry, your suggestion was not recorded."
		 "  Please use the 'bug object' command to bug report the "
		 "suggestion box.\n" );
    return;
  }
  tell_object( previous_object(), "You fill in a suggestion form and stuff "
	       "it in the box.\n" );
}