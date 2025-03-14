#define RESTORE_PATH "/save/cpi_indices/"
#define STOCK_EXCHANGE find_object( "/d/am/am/gomerchants" )
inherit "/std/object";
string material_name;
mapping prices;
void setup() {
  set_name( "board" );
  set_short( "price board" );
  set_long( "This is a large board with many small, wooden flaps attached "+
            "to it.  Painted onto the flaps are numbers and letters, and "+
            "the display is occasionally changed by means of a small imp "+
            "that seems to live inside somewhere.  The board lists the "+
            "purchasing prices of almost everything from gold and silk "+
            "to beef and chicken livers at various places where the "+
            "Merchants' Guild does business.\n" );
  add_adjective( "price" );
  set_main_plural( "price boards" );
  add_plural( "boards" );
  reset_get();
}
int look_up(string);
void init() {
  add_command("find", "<word'thing'>", (:look_up($4[0]):));
}
void imp_effect( string phrase ) {
  tell_room( STOCK_EXCHANGE, "A tiny door opens in the board, a warty imp "+
            "climbs out, clambers across the surface and "+ phrase +
            ".  The imp scowls a bit for the look of the thing, and then "+
            "disappears back inside the board.\n" );
}
void init_data( string word ) {
  material_name = word;
  prices = ([ ]);
}
int get_data_file( string word ) {
  if ( material_name != word ) {
    if ( file_size( RESTORE_PATH + word +".o" ) > 0 )
      unguarded((: restore_object, RESTORE_PATH + word :));
    else {
      init_data( word );
      return 0;
    }
  }
  return 1;
}
void save_data_file( string word ) {
  unguarded((: save_object, RESTORE_PATH + word :));
}
int query_price( string word1, string word2 ) {
   if ( !stringp( word1 ) )
      return 0;
   get_data_file( word1 );
   if ( !prices )
      return 0;
   return prices[ word2 ];
}
int add_price( string word1, string word2, int number ) {
  get_data_file( word1 );
  if ( prices[word2] != 0 ) return 0;
  prices += ([ word2 : number ]);
  imp_effect( "adds the price of "+ word1 +" in "+ word2 +" to the lists" );
  save_data_file( material_name );
  return 1;
}
int modify_price( string word1, string word2, int number ) {
  get_data_file( word1 );
  if ( prices[word2] == 0 ) return 0;
  prices[word2] = number;
  imp_effect( "updates the price of "+ word1 +" in "+ word2 );
  save_data_file( material_name );
  return 1;
}
int remove_price( string word1, string word2 ) {
  get_data_file( word1 );
  if ( prices[word2] == 0 ) return 0;
  prices = m_delete( prices, word2 );
  imp_effect( "removes the price of "+ word1 +" in "+ word2 +
              " from the lists" );
  save_data_file( material_name );
  return 1;
}
int look_up( string word ) {
  int i;
  get_data_file( word );
  if ( !m_sizeof( prices ) ) {
    notify_fail( "You can't find any prices for "+ word +" on the board.\n" );
    return 0;
  }
  if ( m_sizeof( prices ) == 1 ) {
    write( "The only price on the board for "+ word +" is "+
              m_values( prices )[0] +" in "+ m_indices( prices )[0] +".\n" );
  } else {
    write( "You find the following price list for "+ word +":\n\n" );
    for ( i = 1; i < m_sizeof( prices ); i++ ) {
      printf( "%6-s %7d %4|s %40-s \n", "", m_values( prices )[i], "in",
                m_indices( prices )[i] +"," );
    }
    printf( "%6-s %7d %4|s %40-s \n", "  and ", m_values( prices )[0], "in",
              m_indices( prices )[0] +"." );
  }
  return 1;
}
string *query_available_datatypes()
{
  return get_dir(RESTORE_PATH);
}