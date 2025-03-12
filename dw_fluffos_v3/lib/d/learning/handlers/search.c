#include <learning.h>
#define SAVE SAVEPATH +"search"
mapping rooms,
        objects,
        keywords,
        functions;
string *directories;
nosave string word;
void create() {
   seteuid( (string)master()->get_bb_uid() );
   unguarded( (: restore_object, SAVE :) );
}
mixed get_keywords( string *words ) {
   string *found_words, *found_rooms, *found_objects, key, *value;
   if( sizeof( words ) ) {
      found_objects = keys( keywords );
      foreach( word in words ) {
         if( objects[ word ] ) {
            found_objects = filter_array( found_objects,
                (: member_array( $1, objects[ word ] ) != -1 :) );
         } else {
            found_objects = ({ });
         }
      }
      found_rooms = keys( keywords );
      foreach( word in words ) {
         if( rooms[ word ] ) {
            found_rooms = filter_array( found_rooms,
                (: member_array( $1, rooms[ word ] ) != -1 :) );
         } else {
            found_rooms = ({ });
         }
      }
      found_words = ({ });
      foreach( word in found_rooms ) {
         found_words -= keywords[ word ];
         found_words += keywords[ word ];
      }
      foreach( word in found_objects ) {
         found_words -= keywords[ word ];
         found_words += keywords[ word ];
      }
      found_words -= words;
   } else {
      found_rooms = ({ });
      foreach( key, value in rooms ) {
         found_rooms -= value;
         found_rooms += value;
      }
      found_objects = ({ });
      foreach( key, value in objects ) {
         found_objects -= value;
         found_objects += value;
      }
      found_words = keys( rooms );
      found_words -= keys( objects );
      found_words += keys( objects );
   }
   return ({ found_words, found_rooms, found_objects });
}
void update_info_for( string file ) {
   string *words, word;
   object obj;
   if( !catch( file->force_load() ) ) {
      obj = find_object( file );
      words = obj->query_property( "commented functions" );
      if( words ) {
         functions[ file ] = words;
      }
      words = obj->query_property( "keywords" );
      if( words ) {
         keywords[ file ] = words;
         if( function_exists( "add_exit", obj ) ) {
            foreach ( word in words ) {
               if( rooms[ word ] ) {
                  rooms[ word ] -= ({ file });
                  rooms[ word ] += ({ file });
               } else {
                  rooms[ word ] = ({ file });
               }
            }
         } else {
            foreach ( word in words ) {
               if( objects[ word ] ) {
                  objects[ word ] -= ({ file });
                  objects[ word ] += ({ file });
               } else {
                  objects[ word ] = ({ file });
               }
            }
         }
      }
      if( !directories ) {
         unguarded( (: save_object, SAVE :) );
      }
   }
}
void update_search( string room ) {
   object *obs;
   int i;
   obs = all_inventory( find_object( room ) );
   i = sizeof( obs );
   while( i--  ) {
      if ( userp( obs[ i ] ) ) {
         obs[ i ]->move( "/room/void" );
      } else {
         obs = delete( obs, i, 1 );
      }
   }
   room->dest_me();
   room->force_load();
   obs->move( room );
}
void collect_one() {
   string dir, file, *funcs;
   mixed dirs, file_info;
   dir = directories[ 0 ];
   dirs = get_dir( dir, -1 );
   if( dirs ) {
      foreach ( file_info in dirs ) {
         if( file_info[ 1 ] == -2 ) {
            if( file_info[ 0 ] != "old" ) {
               directories = directories + ({ dir + file_info[ 0 ] +"/" });
            }
         } else {
            if( ( sizeof( file_info[ 0 ] ) > 2 ) &&
                ( file_info[ 0 ][ <2 .. <1 ] == ".c" ) ) {
               update_info_for( dir + file_info[ 0 ][ 0 .. <3 ] );
            }
         }
      }
   }
   directories = directories[ 1 .. <1 ];
   if( find_call_out( "collect_one" ) == -1 && sizeof( directories ) ) {
      call_out( "collect_one", 3 );
   } else if( !sizeof( directories ) ) {
      tell_object( find_living( "olorin" ), "Collect finished.\n" );
      directories = 0;
      unguarded( (: save_object, SAVE :) );
      update_search( LEARNING +"search" );
      update_search( LEARNING +"functions" );
   }
}
void collect() {
   rooms=([ ]);
   objects=([ ]);
   functions=([ ]);
   keywords=([ ]);
   directories=({ "/d/learning/" });
   collect_one();
}
int query_collecting() {
   if( directories ) {
      return 1;
   } else {
      return 0;
   }
}
string find_room( string *words ) {
   object thing, *things;
   string word_mark;
   if( !sizeof( words ) )
     return LEARNING +"search";
   word_mark = implode( sort_array( words, 1 ), ", " );
   things = children( SEARCH_ROOM ) - ({ find_object( SEARCH_ROOM ) });
   foreach ( thing in things ) {
      if ( (string)thing->query_marker() == word_mark )
        return file_name( thing );
   }
   thing = clone_object( SEARCH_ROOM );
   thing->set_marker( word_mark, words );
   return file_name( thing );
}
string find_function_room( string word ) {
   object thing, *things;
   if( !word )
     return LEARNING +"functions";
   things = children( FUNCTION_ROOM ) - ({ find_object( FUNCTION_ROOM ) });
   foreach ( thing in things ) {
      if ( (string)thing->query_marker() == word )
        return file_name( thing );
   }
   thing = clone_object( FUNCTION_ROOM );
   thing->set_marker( word );
   return file_name( thing );
}
string *query_functions() {
   string *functions_found, key, *value;
   functions_found = ({ });
   foreach ( key, value in functions ) {
      functions_found -= value;
      functions_found += value;
   }
   return sort_array( functions_found, 1 );
}
string *query_rooms_with_function( string word ) {
   string *rooms_found, key, *value;
   rooms_found = ({ });
   foreach ( key, value in functions ) {
      if ( member_array( word, value ) != -1 )
        rooms_found += ({ key });
   }
   return uniq_array(rooms_found);
}