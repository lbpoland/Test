#include <map_handler.h>
mapping shorts = ([ ]), movezones = ([ ]), changetimes = ([ ])
#if !efun_defined(db_exec)
, clusters = ([ ]), map = ([ ])
#endif
;
#ifdef COORDS
mapping coords = ([ ]), sizes = ([ ]);
#endif
string directory;
nosave string loaded;
nosave int save;
void create() {
   seteuid( (string)master()->get_bb_uid() );
}
void save_dir() {
#ifdef HELPLOGTO
   tell_object( find_living( LOGTO ), "%^RED%^saving%^RESET%^ "+ loaded +"\n");
#endif
   if (sizeof(shorts) ||
       sizeof(movezones) ||
       sizeof(changetimes) ||
#ifdef COORDS
       sizeof(coords) ||
       sizeof(sizes) ||
#endif
#if !efun_defined(db_exec)
       sizeof(clusters) ||
       sizeof(map) ||
#endif
        0) {
      unguarded((: save_object, "/save/map/" + loaded :));
   } else {
      unguarded((: rm("/save/map/" + loaded) :));
   }
   save = 0;
}
void check_dir( string dir ) {
   string tmp_file;
   if ( dir == directory ) {
      return;
   }
   if ( save )  {
      save_dir();
   }
   tmp_file = replace_string( dir, "/", "_" );
   shorts = ([ ]);
   movezones = ([ ]);
   changetimes = ([ ]);
#if !efun_defined(db_exec)
   clusters = ([ ]);
   map = ([ ]);
#endif
#ifdef COORDS
   coords = ([ ]);
   sizes = ([ ]);
#endif
   if ( file_size( "/save/map/" + tmp_file + ".o" ) > 0 ) {
#ifdef HELPLOGTO
      tell_object( find_living( LOGTO ), "%^GREEN%^loading%^RESET%^ "+ tmp_file
                   +"\n");
#endif
      unguarded((: restore_object, "/save/map/" + tmp_file :));
   } else {
#ifdef HELPLOGTO
      tell_object( find_living( LOGTO ), "%^BLUE%^newmap%^RESET%^ "+ tmp_file +"\n");
#endif
      shorts = ([ ]);
      movezones = ([ ]);
      changetimes = ([ ]);
#if !efun_defined(db_exec)
      clusters = ([ ]);
      map = ([ ]);
#endif
#ifdef COORDS
      coords = ([ ]);
      sizes = ([ ]);
#endif
   }
   loaded = tmp_file;
   directory = dir;
}
#if !efun_defined(db_exec)
void change_map( string dir, string room, string *dd ) {
   check_dir( dir );
   map[ room ] = dd;
   save = 1;
}
mapping query_map( string dir ) {
   check_dir( dir );
   if ( !map )
     return ([ ]);
   return map;
}
#endif
void change_shorts( string dir, string room, string sh ) {
   check_dir( dir );
   shorts[ room ] = sh;
   save = 1;
}
mapping query_shorts( string dir ) {
   check_dir( dir );
   if ( !shorts ) {
     return ([ ]);
   }
   return shorts;
}
void change_movezones( string dir, string room, string *zones ) {
   check_dir( dir );
   movezones[ room ] = zones;
   save = 1;
}
mapping query_movezones( string dir ) {
   check_dir( dir );
   if ( !movezones )
     return ([ ]);
   return movezones;
}
#if !efun_defined(db_exec)
void change_clusters( string dir, string room, int cluster ){
  check_dir( dir );
  if(!clusters)
    clusters = ([]);
  clusters[ room ] = cluster;
  save = 1;
}
mapping query_clusters( string dir ){
  check_dir( dir );
  if( !clusters )
    return ([ ]);
  return clusters;
}
#endif
void change_changetimes( string dir, string room, int time ) {
   check_dir( dir );
   if ( !changetimes )
      changetimes = ([ ]);
   changetimes[ room ] = time;
   save = 1;
}
mapping query_changetimes( string dir ) {
   check_dir( dir );
   if ( !changetimes )
     return ([ ]);
   return changetimes;
}
#ifdef COORDS
void change_co_ords( string dir, string room, int *coord ) {
   check_dir( dir );
   if ( !coords )
      coords = ([ ]);
   coords[ room ] = coord;
   save = 1;
}
mapping query_co_ords( string dir ) {
   check_dir( dir );
   if ( !coords )
     return ([ ]);
   return coords;
}
void change_sizes( string dir, string room, int size ) {
   check_dir( dir );
   if ( !sizes )
      sizes = ([ ]);
   sizes[ room ] = size;
   save = 1;
}
mapping query_sizes( string dir ) {
   check_dir( dir );
   if ( !sizes )
     return ([ ]);
   return sizes;
}
#endif
void del( string dir, string room ) {
   check_dir( dir );
#if !efun_defined(db_exec)
   if (mapp(map)) {
     map_delete( map, room );
   } else {
     map = ([ ]);
   }
#endif
   if (mapp(shorts)) {
     map_delete( shorts, room );
   } else {
     shorts = ([ ]);
   }
   if (mapp(movezones)) {
     map_delete( movezones, room );
   } else {
     movezones = ([ ]);
   }
   if (mapp(changetimes)) {
     map_delete( changetimes, room );
   } else {
     changetimes = ([ ]);
   }
#if !efun_defined(db_exec)
   if (mapp(clusters)) {
     map_delete( clusters, room );
   } else {
     clusters = ([ ]);
   }
#endif
#ifdef COORDS
   if (mapp(coords)) {
     map_delete( coords, room );
   } else {
     coords = ([ ]);
   }
   if (mapp(sizes)) {
     map_delete( sizes, room );
   } else {
     sizes = ([ ]);
   }
#endif
   save = 1;
}