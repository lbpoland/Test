#include <map_handler.h>
#include <config.h>
inherit "/obj/handlers/inherit/distance_handler";
mapping shorts = ([ ]);
mapping movezoness = ([ ]);
mapping changetimes = ([ ]);
#if !efun_defined(db_exec)
mapping clusters = ([ ]);
mapping map = ([ ]);
#else
int db, loop = 0;
#include <db.h>
#endif
mapping forced_rooms = ([ ]);
#ifdef COORDS
mapping coords = ([ ]);
mapping sizes = ([ ]);
#endif
int load = 0, time, stopped;
string *cache = ({ }), *queue = ({ });
int check_next_call_out;
mapping stats = ([]);
private void do_room1( string room );
private void check_next();
private void check_map2( string );
void create() {
   seteuid( (string)"secure/master"->get_root_uid() );
   "/room/void"->force_load();
   check_next_call_out = call_out( (: check_next :), SKEWTIME );
#if efun_defined(db_exec)
   db = db_connect("localhost","discworld",CONFIG_DB_USER);
#endif
}
protected void update_cache( string directory, int load ) {
   if ( !shorts[ directory ] || load ) {
      cache = ( cache - ({ directory }) ) + ({ directory });
      if ( sizeof( cache ) > CACHESIZE ) {
         map_delete( shorts, cache[ 0 ] );
         map_delete( movezoness, cache[ 0 ] );
         map_delete( changetimes, cache[ 0 ] );
#if !efun_defined(db_exec)
         map_delete( clusters, cache[ 0 ] );
         map_delete( map, cache[ 0 ] );
#endif
#ifdef COORDS
         map_delete( coords, cache[ 0 ] );
         map_delete( sizes, cache[ 0 ] );
#endif
         cache -= ({ cache[ 0 ] });
         LOG( sprintf( "%%^RED%%^uncaching %s%%^RESET%%^\n", cache[ 0 ] ) );
      }
      shorts[ directory ] = MH->query_shorts( directory );
      movezoness[ directory ] = MH->query_movezones( directory );
      changetimes[ directory ] = MH->query_changetimes( directory );
#if !efun_defined(db_exec)
      clusters[ directory ] = MH->query_clusters( directory );
      map[ directory ] = MH->query_map( directory );
#endif
#ifdef COORDS
      coords[ directory ] = MH->query_co_ords( directory );
      sizes[ directory ] = MH->query_sizes( directory );
#endif
   }
}
void clear_cache() {
   shorts = ([ ]);
   movezoness = ([ ]);
   changetimes = ([ ]);
#if !efun_defined(db_exec)
   clusters = ([ ]);
   map = ([ ]);
#endif
#ifdef COORDS
   coords = ([ ]);
   sizes = ([ ]);
#endif
   cache = ({ });
}
#if !efun_defined(db_exec)
mapping query_map( string dir ) {
   if ( !map[ dir ] ) {
     update_cache( dir, 1 );
   }
   stats["map"]++;
   return map[ dir ];
}
void change_map( string dir, string room, string *dd ) {
   MH->change_map( dir, room, dd );
   map[ dir ][ room ] = dd;
}
#endif
mapping query_shorts( string dir ) {
   if ( !shorts[ dir ] ) {
      update_cache( dir, 1 );
   }
   stats["shorts"]++;
   return shorts[ dir ];
}
void change_shorts( string dir, string room, string sh ) {
   MH->change_shorts( dir, room, sh );
   shorts[ dir ][ room ] = sh;
}
mapping query_movezones( string dir ) {
   if ( !movezoness[ dir ] ) {
      update_cache( dir, 1 );
   }
   stats["movezones"]++;
   return movezoness[ dir ];
}
void change_movezones( string dir, string room, string *zones ) {
   MH->change_movezones( dir, room, zones );
   movezoness[ dir ][ room ] = zones;
}
mapping query_changetimes( string dir ) {
   if ( !changetimes[ dir ] ) {
      update_cache( dir, 1 );
   }
   stats["changetimes"]++;
   return changetimes[ dir ];
}
void change_changetimes( string dir, string room, int time ) {
   MH->change_changetimes( dir, room, time );
   changetimes[ dir ][ room ] = time;
}
#if !efun_defined(db_exec)
mapping query_clusters( string dir ) {
  if ( !clusters[ dir ] ) {
    update_cache( dir, 1 );
  }
  return clusters[ dir ];
}
void change_clusters( string dir, string room, int cluster ) {
   MH->change_clusters( dir, room, cluster );
   if(clusters[ dir ])
     clusters[ dir ][ room ] = cluster;
}
#endif
#ifdef COORDS
mapping query_co_ords( string dir ) {
   if ( !coords[ dir ] )
      update_cache( dir, 1 );
   stats["co_ords"]++;
   return coords[ dir ];
}
void change_co_ords( string dir, string room, int *coord ) {
   MH->change_co_ords( dir, room, coord );
   coords[ dir ][ room ] = coord;
}
mapping query_sizes( string dir ) {
   if ( !sizes[ dir ] )
      update_cache( dir, 1 );
   stats["sizes"]++;
   return sizes[ dir ];
}
void change_sizes( string dir, string room, int *size ) {
   MH->change_sizes( dir, room, size );
   sizes[ dir ][ room ] = size;
}
#endif
void del( string dir, string room ) {
   MH->del( dir, room );
   update_cache( dir, 1 );
}
#if !efun_defined(db_exec)
int query_cluster( string room ) {
  string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
  string troom = explode( room, "/" )[ <1 ];
  if ( troom[ <2.. ] == ".c" ) {
    troom = troom[ 0..<3];
  }
  if( !clusters[ directory ] ) {
    update_cache( directory, 1 );
  }
  if( !clusters[ directory ] ) {
    clusters[ directory ] = ([]);
  }
  return query_clusters( directory )[ troom ];
}
void set_cluster( string room, int cluster ) {
  string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
  string troom = explode( room, "/" )[ <1 ];
  if ( troom[ <2.. ] == ".c" ) {
    troom = troom[ 0..<3];
  }
  change_clusters( directory, troom, cluster);
}
#endif
string *query_dest_dir( string room ) {
#if !efun_defined(db_exec)
  string directory, troom;
#else
  mixed rows;
  string *ret;
  int i = 0;
#endif
  stats["dest_dir"]++;
  if(!room || room == "/" || room == "" || strsrch(room, "/") == -1)
    return ({ });
#if !efun_defined(db_exec)
  directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
  troom = explode( room, "/" )[ <1 ];
  if ( troom[ <2.. ] == ".c" ) {
    troom = troom[ 0..<3];
  }
  if( !query_map( directory )[ troom ] ) {
    check_map2( room );
  }
  return query_map( directory )[ troom ];
#else
  if ( room[ <2.. ] == ".c" ) {
    room = room[ 0..<3];
  }
  if(loop == time())
    return ({});
  loop = time();
  rows = db_exec(db, "select exit, dest from roomexit where id = '%s'", db_escape(room));
  if(stringp(rows)||!rows){
    forced_rooms[ room ] = 1;
    check_map2( room );
    rows = db_exec(db, "select exit, dest from roomexit where id = '%s'", db_escape(room));
    if(stringp(rows)){
      loop = 0;
      return ({ });
    }
  }
  ret = allocate(rows * 2);
  for(i=0; i<rows; i++){
    string *row;
    row = db_fetch(db, i + 1);
    ret[i*2] = row[0];
    ret[i*2+1] = row[1];
  }
  loop = 0;
  return ret;
#endif
}
string *qdd( string room ) {
   return query_dest_dir( room );
}
string query_destination( string exit, string room ) {
   int i;
   string *dest_dir;
   stats["destination"]++;
   if( !room || room == "") {
      room = file_name( environment( previous_object() ) );
      if( !room ) return "/room/void";
   }
   dest_dir = query_dest_dir( room );
   i = member_array( exit, dest_dir );
   if( i < 0 ) return "/room/void";
   return dest_dir[ i + 1 ];
}
string qdes( string exit, string room ) {
   return query_destination( exit, room );
}
string *qdir( string room ) {
   int i;
   string *qddir, *dir=({});
   stats["qdir"]++;
   if( !room || room == "") {
      room = file_name( environment( previous_object() ) );
      if( !room ) return ({ "/room/void" });
   }
   qddir = query_dest_dir( room );
   for( i = sizeof( qddir ) - 2;i > -1;i -= 2)
     dir += ({ qddir[ i ]} );
   return dir;
}
string *query_cache() { return cache; }
string *query_queue() { return queue; }
void set_stopped( int s ) { stopped = s; }
int compare_arrays( mixed *ar1, mixed *ar2 ) {
   int i;
   if ( !ar1 && !ar2 ) return 0;
   if ( sizeof( ar1 ) != sizeof( ar2 ) ) return 1;
   i = sizeof( ar1 );
   while ( i-- ) {
      if ( ar1[ i ] != ar2[ i ] ) {
         return 1;
      }
   }
   return 0;
}
varargs void queue_room( string room, int force, string reason ) {
   queue -= ({ room });
   queue += ({ room });
   forced_rooms[ room ] = force;
#ifdef LOGTO
   if ( !reason ) reason = "";
   LOG( sprintf( "%%^RED%%^Queueing %s(%i) %s.%%^RESET%%^\n",
                room, sizeof( queue ), reason ) );
#else
   reason = reason;
#endif
}
void do_room( string room ) {
   call_out( (: do_room1 :), 1, room );
}
private void do_room1( string room ) {
   mixed tmp;
   int changetime;
   string directory = implode( explode( room, "/" )[ 0 .. <2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" )
      troom = troom[ 0 .. <3 ];
   if ( directory[ 0 ] == 'w' ) {
      LOG( sprintf( "%%^BLUE%%^Skipping %s,%%^RESET%%^ in /w/.\n", room ) );
      return;
   }
   if ( directory[ 0 .. 2 ] == "std" ) {
      LOG( sprintf( "%%^BLUE%%^Skipping %s,%%^RESET%%^ in /std/.\n", room ) );
      return;
   }
   tmp = stat( room +".c" );
   if( !pointerp( tmp ) || sizeof( tmp ) < 2 ) {
      tmp = stat( room );
      if( !pointerp( tmp ) || sizeof( tmp ) < 2 )
         return;
   }
   tmp = find_object( room );
   if ( tmp ) {
      if( tmp->query_property( "no map" ) ) {
         LOG( sprintf( "%%^BLUE%%^Skipping %s%%^RESET%%^, it asked me to.\n",
                      tmp->a_short() ) );
         return;
      }
#ifdef COORDS
      tmp->calc_co_ord();
      if ( sizeof( tmp->query_co_ord() ) >
          sizeof( query_co_ords( directory )[ troom ] ) ) {
         queue_room( room, 1, "new co_ordinates");
         return;
      }
#endif
   }
   tmp = stat( room +".c" );
   if ( query_changetimes( directory )[ troom ] ==
       ( changetime = tmp[ TIME ] ) ) {
      return;
   }
   queue -= ({ room });
   queue += ({ room });
   LOG( sprintf( "%%^RED%%^Queueing %s(%i).%%^RESET%%^\n",
                room, sizeof( queue ) ) );
}
private void check_next() {
   string room;
   if ( sizeof( queue ) && !stopped ) {
        check_next_call_out = call_out( (: check_next :), SKEWTIME );
      room = queue[ 0 ];
      queue -= ({ room });
      check_map2( room );
   } else {
      check_next_call_out = call_out( (: check_next :), 60 );
   }
}
private void check_short( object room_obj, string room_short, string room ) {
   string tmp_short, bad_short;
   if(!room_short)
     return;
   tmp_short = lower_case(room_short);
   bad_short = 0;
   if ( tmp_short[ 0 .. 4 ] == "an a " ||
       tmp_short[ 0 .. 5 ] == "an an " ||
       tmp_short[ 0 .. 5 ] == "the the " ||
       tmp_short[ 0 .. 5 ] == "a the " ) {
      bad_short = "strange or missing determinate";
   } else {
      if(!sizeof(tmp_short))
         bad_short = "no short";
      else if ( tmp_short[ <1 ] == '.' ) {
         bad_short = "period in short";
      } else {
         if ( !(tmp_short = (string)room_obj->query_property( "determinate" ) ) ) {
            tmp_short = (string)room_obj->query_short();
            if ( tmp_short )
            if ( tmp_short[ 0 .. 0 ] != lower_case( tmp_short[ 0 .. 0 ] ) )
               bad_short = "suspicious capitalisation";
         } else {
            if ( tmp_short != "" ) {
               if ( tmp_short[ <1 ] != ' ' ) {
                  bad_short = "missing space in determinate";
               } else {
                  if ( tmp_short[ 0 .. 0 ] != lower_case( tmp_short[ 0 .. 0 ] ) ) {
                     bad_short = "suspicious capitalisation in determinate";
                  }
               }
            }
         }
      }
   }
   if ( bad_short ) {
      log_file( "STRANGE_SHORT","%s, %s (%s)\n",
               room_short, bad_short, room );
      LOG( sprintf( "%%^RED%%^%s.%%^RESET%%^\n", bad_short ) );
   }
}
void check_map( string room ) {
   do_room( room );
}
private void check_map2( string room ) {
   mixed tmp;
   int i, changetime, do_update;
   string *dest_dir, *tmpdest_dir, room_short, *movezones;
#ifdef COORDS
   int *coord;
   mixed size;
#endif
   object room_obj;
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   if ( directory[ 0 ] == 'w' ) {
      LOG( sprintf( "%%^BLUE%%^Skipping %s,%%^RESET%%^ in /w/.\n", room ) );
      return;
   }
   if ( directory[ 0 .. 2 ] == "std" ) {
      LOG( sprintf( "%%^BLUE%%^Skipping %s,%%^RESET%%^ in /std/.\n", room ) );
      return;
   }
   do_update = forced_rooms[ room ];
   tmp = stat( room +".c" );
   if( !pointerp( tmp ) || sizeof( tmp ) < 2 )
      return;
#ifdef COORDS
   if ( room_obj = find_object( room ) ) {
      room_obj->calc_co_ord();
      if ( ( sizeof( room_obj->query_co_ord() ) >
            sizeof( query_co_ords( directory )[ troom ] ) ) ||
          compare_arrays( room_obj->query_co_ord(),
                         query_co_ords( directory )[ troom ] ) ) {
         do_update = 1;
      }
   }
#endif
   if ( !do_update &&
       ( query_changetimes( directory )[ troom ] ==
        ( changetime = tmp[ TIME ] ) ) ) {
      return;
   }
   if ( !find_object( room ) )
      catch( room->force_load() );
   room_obj = find_object( room );
   queue -= ({ room });
   map_delete( forced_rooms, room );
   update_cache( directory, 0 );
   if( !room_obj ) {
      if( shorts[ directory ][ troom ] ) {
         dest_dir = query_dest_dir(room);
         for(i = 1; i < sizeof( dest_dir ); i += 2 )
            check_map( dest_dir[ i ] );
#if !efun_defined(db_exec)
         map_delete( map[ directory ], troom );
#endif
         map_delete( shorts[ directory ], troom );
         map_delete( movezoness[ directory ], troom );
         map_delete( changetimes[ directory ], troom );
#ifdef COORDS
         map_delete( coords[ directory ], troom );
         map_delete( sizes[ directory ], troom );
#endif
         del( directory, room );
         LOG( sprintf( "%%^RED%%^Removing %s,%%^RESET%%^.\n", room ) );
      }
      return;
   }
   if ( room_obj->query_property( "no map" ) ) {
      LOG( sprintf( "%%^BLUE%%^Skipping %s,%%^RESET%%^ it asked me to.\n",
                   room ) );
      return;
   }
   room_short = (string)"/global/events"->convert_message(
         (string)room_obj->a_short() );
   if ( shorts[ directory ][ troom ] != room_short )
      do_update = 1;
   LOG( sprintf( "%%^YELLOW%%^Updating %s%%^RESET%%^. (%s)\n",
                room_short, troom ) );
#ifdef LOG_SHORTS
   check_short( room_obj, room_short, room );
#endif
   movezones = room_obj->query_zones();
   if ( !pointerp( movezones ) ) movezones = ({ });
   if ( movezoness[ directory ][ troom ] != movezones )
      do_update = 1;
#ifdef COORDS
   room_obj->calc_co_ord();
   coord = room_obj->query_co_ord();
   if ( !coord ) room_obj->calc_co_ord();
   coord = room_obj->query_co_ord();
   if ( !coords[ directory ] ) coords[ directory ] = ([ ]);
   if ( compare_arrays( coords[ directory ][ troom ], coord ) )
      do_update = 1;
   size = room_obj->query_room_size_array();
   if ( !sizes[ directory ] ) sizes[ directory ] = ([ ]);
   if ( sizes[ directory ][ troom ] != size )
      do_update = 1;
#endif
   if ( changetimes[ directory ][ troom ] != changetime )
      do_update = 1;
   if ( do_update ) {
      change_changetimes( directory, troom, changetime );
      change_movezones( directory, troom, movezones );
      change_shorts( directory, troom, room_short );
#ifdef COORDS
      if ( sizeof( coord ) == 3 )
         change_co_ords( directory, troom, coord );
      change_sizes( directory, troom, size );
#endif
      update_cache( directory, 1 );
   }
   dest_dir = room_obj->query_dest_dir();
   if( !dest_dir ) {
      dest_dir = ({ });
   } else {
      string exit;
      if( room_obj->query_blockage() ) {
        exit = room_obj->query_direction();
        if( !exit )
          for( i = 1; i < sizeof( dest_dir ); i += 2 )
            if( dest_dir[ i ]->query_blockage() ) {
              exit = dest_dir[ i - 1 ];
              break;
            }
      }
      if(!exit)
         exit = "";
      tmpdest_dir = ({ });
      for ( i = 1; i < sizeof( dest_dir ); i += 2 ) {
         mixed tmp2;
         catch(load_object(dest_dir[i]));
         if ( objectp( find_object( dest_dir[ i ] ) ) &&
                          !clonep( find_object( dest_dir[ i ] ) ) &&
              exit != dest_dir[i - 1] &&
              dest_dir[i - 1][0..5] != "enter " &&
              dest_dir[i][1] != 'w' &&
              dest_dir[i][1..3] != "std" &&
              dest_dir[i][1..4] != "room" &&
                     (catch(tmp2 = dest_dir[i]->query_property( "no map" )), !tmp2)) {
            tmpdest_dir += ({ dest_dir[ i - 1 ], dest_dir[ i ] });
         }
      }
      dest_dir = tmpdest_dir;
   }
   if ( compare_arrays( query_dest_dir(room), dest_dir ) ) {
#if !efun_defined(db_exec)
      map[ directory ][ troom ] = dest_dir;
#else
      db_exec(db, "delete from roomexit where id = '%s'", db_escape(room));
      for(i=0; i<sizeof(dest_dir)/2; i++){
        db_exec(db, "insert into roomexit values ('%s', '%s', '%s')",
                db_escape(room), db_escape(dest_dir[i*2]),
                db_escape(dest_dir[i*2+1]));
      }
#endif
      for( i = 1; i < sizeof( dest_dir );i += 2 ) {
         if ( dest_dir[ i ][ <2.. ] == ".c" ) {
#ifdef LOG_EXITS
            log_file("BAD_EXIT","from %s, %s to %s\n",
                     directory +"/"+ troom, dest_dir[ i-1 ], dest_dir[ i ] );
#endif
            dest_dir[ i ] = dest_dir[ i ][ 0..<3 ];
         }
      }
#if !efun_defined(db_exec)
      change_map( directory, troom, dest_dir );
#endif
#ifdef PARANOID
      update_cache( directory, 1 );
#endif
      for( i = 1; i < sizeof( dest_dir ); i += 2 ) {
         do_room( dest_dir[ i ] );
      }
#ifdef PARANOID
      return;
#endif
   }
#ifdef PARANOID
   update_cache( directory, 1 );
#endif
}
string query_short( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["short"]++;
   if ( strsrch( room, "#" ) != -1 ) {
      if ( find_object( room ) ) {
         return (string)"/global/events"->convert_message(
                     (string)room->a_short() );
      } else {
         return "The map_handler was called on a non-existent clone";
      }
   }
   if ( !shorts[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !shorts[ directory ] ) {
      shorts[ directory ] = ([ ]);
   }
   if ( shorts[ directory ][ troom ] ) {
     return shorts[ directory ][ troom ];
   }
   if ( !catch( load_object(room) ) ) {
     return (string)"/global/events"->convert_message(
                            (string)room->a_short() );
   }
   return "Oops!";
}
string static_query_short( string room ) {
   string directory, troom;
   if(!stringp(room))
     return "";
   directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["static short"]++;
   if ( !shorts[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !shorts[ directory ] ) {
      shorts[ directory ] = ([ ]);
   }
   if ( shorts[ directory ][ troom ] ) {
     return shorts[ directory ][ troom ];
   }
   return 0;
}
string *query_zones( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   object roomob;
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["zones"]++;
   if ( strsrch( room, "#" ) != -1 ) {
      if ( find_object( room ) ) {
         return (string *)room->query_movezones();
      } else {
         return ({ });
      }
   }
   if ( !movezoness[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !movezoness[ directory ] ) {
      movezoness[ directory ] = ([ ]);
   }
   if ( movezoness[ directory ][ troom ] ) {
     return movezoness[ directory ][ troom ];
   }
   if ( !catch( roomob = load_object(room) ) ) {
     if(roomob)
       return roomob->query_movezones();
   }
   return ({ "Oops!" });
}
#ifdef COORDS
void set_co_ord( string room, int *coord ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   if ( !coords[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !coords[ directory ] ) {
      coords[ directory ] = ([ ]);
   }
   MH->change_co_ords( directory, troom, coord );
   coords[ directory ][ troom ] = coord;
}
int *query_co_ord( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["co_ord"]++;
   LOG( sprintf( "%%^BLUE%%^query_co_ord(%s)%%^RESET%%^\n", room ) );
   if ( strsrch( room, "#" ) != -1 ) {
      if ( find_object( room ) ) {
         return room->query_co_ord();
      } else {
         return 0;
      }
   }
   if ( !coords[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !coords[ directory ] ) {
      coords[ directory ] = ([ ]);
   }
   if ( coords[ directory ][ troom ] ) {
     return coords[ directory ][ troom ];
   }
   if ( !catch( load_object(room ) ) ) {
     return room->query_co_ord();
   }
   return 0;
}
int *static_query_co_ord( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["static co_ord"]++;
   if ( strsrch( room, "#" ) != -1 ) {
      if ( find_object( room ) ) {
         return room->query_co_ord();
      } else {
         return 0;
      }
   }
   if ( !coords[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !coords[ directory ] ) {
      coords[ directory ] = ([ ]);
   }
   if ( coords[ directory ][ troom ] ) {
     return coords[ directory ][ troom ];
   }
   return 0;
}
int *query_room_size( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   stats["room_size"]++;
   if ( strsrch( room, "#" ) != -1 ) {
      if ( find_object( room ) ) {
         return room->query_room_size_array();
      } else {
         return 0;
      }
   }
   if ( !sizes[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !sizes[ directory ] ) {
      sizes[ directory ] = ([ ]);
   }
   if ( sizes[ directory ][ troom ] ) {
     return sizes[ directory ][ troom ];
   }
   if (!catch(room->force_load())) {
      return room->query_room_size_array();
   }
   return 0;
}
#endif
int test_room( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   if ( strsrch( room, "#" ) != -1 )  {
      return 1;
   }
   if ( !shorts[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !shorts[ directory ] ) {
      shorts[ directory ] = ([ ]);
   }
   if ( shorts[ directory ][ troom ] ) {
     return 1;
   }
   if ( !catch( load_object(room) ) ) {
     return 1;
   }
   return 0;
}
int query_known( string room ) {
   string directory = implode( explode( room, "/" )[ 0..<2 ], "/" );
   string troom = explode( room, "/" )[ <1 ];
   if ( troom[ <2.. ] == ".c" ) {
     troom = troom[ 0..<3];
   }
   if ( !shorts[ directory ] ) {
      update_cache( directory, 1 );
   }
   if ( !shorts[ directory ] ) {
      shorts[ directory ] = ([ ]);
   }
   return !undefinedp(shorts[ directory ][troom]);
}
void check_save_files() {
   string *files, file, room, *tmp;
   files = unguarded((: get_dir, "/save/map/" :));
   files = map( files, (: replace( $1, ({ "_", "/", ".o", ""}) ) :) );
   foreach( file in files ) {
      printf( "%s\n", file );
      tmp = keys( MH->query_map( file ) );
      reset_eval_cost();
      foreach( room in tmp ) {
         if( file_size( file +"/"+ room + ".c" ) < 0 ) {
            printf( "%s no longer exists.\n", file + "/" + room );
            MH->del( file, room );
         }
      }
   }
   cache = ({ });
}
mapping query_dynamic_auto_load() {
   mapping tmp;
   tmp = ([ "shorts" : shorts,
            "movezoness" : movezoness,
            "changetimes" : changetimes,
#if !efun_defined(db_exec)
            "clusters" : clusters,
            "map" : map,
#endif
#ifdef COORDS
            "coords" : coords,
            "sizes" : sizes,
#endif
            "cache" : cache,
            "queue" : queue,
          ]);
   return tmp;
}
void init_dynamic_arg(mapping maps) {
   if (maps["shorts"])
      shorts = maps["shorts"];
   if (maps["movezoness"])
      movezoness = maps["movezoness"];
   if (maps["changetimes"])
      changetimes = maps["changetimes"];
#if !efun_defined(db_exec)
   if (maps["clusters"])
      clusters = maps["clusters"];
   if (maps["map"])
     map = maps["map"];
#endif
#ifdef COORDS
   if (maps["coords"])
      coords = maps["coords"];
   if (maps["sizes"])
      sizes = maps["sizes"];
#endif
   if (maps["cache"])
      cache = maps["cache"];
   if (maps["queue"])
      queue = maps["queue"];
}
mixed *stats() {
   return ({
      ({ "queue size", sizeof( queue ) }),
      ({ "cache size", sizeof( cache ) }),
      ({ "next check", find_call_out( check_next_call_out ) }),
        }) + map(keys(stats), (:({$1, $(stats)[$1]}):));
}