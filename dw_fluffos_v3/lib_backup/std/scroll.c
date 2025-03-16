inherit "/std/object";
int num_pages, open_page;
mixed *pages;
void create() {
  num_pages = 1;
  open_page = 1;
  pages = ({ ({ 0, 0, 0 }) });
  ::create();
}
void init() {
  add_command("scroll", "<word'forward|backward'>", (:this_object()->do_scroll($4[0]):));
}
void set_read_mess( string mess, string lang, int size ) {
  pages[ open_page ] = ({ mess, lang, size });
  ::set_read_mess( mess, lang, size );
}
void add_read_mess( string mess, string type, string lang, string size ) {
  pages[ open_page ] = ({ mess, lang, size });
  ::set_read_mess( mess, lang, size );
}
int query_num_pages() { return num_pages; }
void set_num_pages( int number ) { num_pages = number; }
int query_open_page() { return open_page; }
void set_open_page( int number ) {
  int size;
  string mess, lang;
  mixed *text;
  if ( ( number < 0 ) || ( number > num_pages ) )
    open_page = 1;
  else
    open_page = number;
  text = pages[ open_page ];
  if ( !text || ( sizeof( text ) < 3 ) )
    text = ({ 0, 0, 0 });
  mess = text[ 0 ];
  lang = text[ 1 ];
  size = text[ 2 ];
  ::set_read_mess( mess, lang, size );
}
int do_scroll( string word ) {
  if ( ( word != "forward" ) && ( word != "backward" ) ) {
    notify_fail( "Syntax: scroll forward|backward\n" );
    return 0;
  }
  if ( word == "forward" ) {
    if ( open_page == num_pages ) {
      notify_fail( "The scroll is already rolled forward to the last "+
          "section.\n" );
      return 0;
    }
    set_open_page( ++open_page );
    write( "You roll the scroll forward to the next section.\n" );
    say( (string)this_player()->one_short() +" rolls the "+ short( 0 ) +
        " forward.\n" );
    return 1;
  }
  if ( open_page == 1 ) {
    notify_fail( "The scroll is already open at the first section.\n" );
    return 0;
  }
  set_open_page( --open_page );
  write( "You roll the scroll backward to the previous section.\n" );
  say( (string)this_player()->one_short() +" rolls the "+ short( 0 ) +
      " backward.\n" );
  return 1;
}
mixed *stats() {
  return ::stats() + ({
    ({ "pages", num_pages }),
    ({ "open at", open_page })
  });
}
mapping query_auto_dynamic_load() {
  return ([
    "::": ::query_dynamic_auto_load(),
    "open_page": open_page
  ]);
}
mapping int_query_static_auto_load() {
  return ([
    "::": ::int_query_static_auto_load(),
    "num_pages": num_pages,
    "pages": pages
  ]);
}
mixed query_static_auto_load() {
  if ( ( file_name( this_object() ) )[ 0 .. 10 ] != "/std/scroll" )
    return 0;
  return int_query_static_auto_load();
}
void init_dynamic_arg( mapping args ) {
  ::init_dynamic_arg( args[ "::" ] );
  open_page = args[ "open_page" ];
}
void init_static_arg( mapping args ) {
  if ( args[ "::" ] ) ::init_static_arg( args[ "::" ] );
  if ( args[ "num_pages" ] ) num_pages = args[ "num_pages" ];
  if ( args[ "pages" ] ) pages = args[ "pages" ];
}