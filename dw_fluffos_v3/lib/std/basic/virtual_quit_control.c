protected string find_start_pos(object player, object place) {
   mixed quit_env;
   string last_pos, name;
   mixed test_char;
   if ( place ) {
      quit_env = place->query_quit_handler( player );
      if (arrayp(quit_env)) {
         last_pos = quit_env[0];
      } else {
         last_pos = (string)quit_env;
      }
      if ( last_pos ) {
         last_pos->player_quitting( player, place );
      } else {
         last_pos = file_name( place );
      }
   } else {
      last_pos = player->query_start_pos();
   }
   if (last_pos && last_pos[ 0 .. 2 ] == "/w/" && last_pos != "/w/common.c") {
      test_char = player->query_property( "test character" );
      if ( !stringp( test_char ) ) {
          name = player->query_name();
      }
      else {
          name = test_char;
      }
      if (!sscanf(last_pos, "/w/"+ name +"%*s") ) {
         if (!player->query_creator() ||
              !last_pos->query_valid_save( player->query_name() )) {
            last_pos = player->query_start_pos();
         }
      }
   }
   return last_pos;
}
protected int * find_start_coord(object player, object place) {
   mixed quit_env;
   string last_pos, name;
   mixed test_char;
   if ( place ) {
      quit_env = place->query_quit_handler();
      if (arrayp(quit_env)) {
         return quit_env[1];
      } else {
         last_pos = (string)quit_env;
      }
      if ( !last_pos ) {
         last_pos = file_name( place );
      }
   } else {
      last_pos = player->query_start_pos();
   }
   if (last_pos[ 0 .. 2 ] == "/w/" && last_pos != "/w/common.c") {
      test_char = player->query_property( "test character" );
      if ( !stringp( test_char ) ) {
          name = player->query_name();
      }
      else {
          name = test_char;
      }
      if (!sscanf(last_pos, "/w/"+ name +"%*s") ) {
         if( !( player->query_creator() ||
                player->query_property( "test character" ) ) ||
              !last_pos->query_valid_save( player->query_name() )) {
            last_pos = player->query_start_pos();
         }
      }
   }
   return last_pos->query_co_ord();
}