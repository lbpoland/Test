#define SAVE_FILE "/save/philosophies"
#define SAVE_DIR "/save/philosophies/"
#define PHILOSOPHY_TYPE 0
#define PHILOSOPHY_BONUS 1
#define PHILOSOPHY_NEEDED 2
#define PHILOSOPHY_EFFECT 3
#define PHILOSOPHY_ARGUMENTS 4
nosave string current_person, current_philosophies;
mapping philosophies;
void create() {
  seteuid( (string)"/secure/master"->
           creator_file( file_name( this_object() ) ) );
   philosophies = ([ ]);
   if ( file_size( SAVE_FILE +".o" ) > 0 )
      unguarded( (: restore_object, SAVE_FILE :) );
}
void save_me() { unguarded( (: save_object, SAVE_FILE :) ); }
mapping query_philosophies() { return philosophies; }
string *query_philosophy_names() { return keys( philosophies ); }
int query_philosophy( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return 1;
}
void add_philosophy( string name, string type, int bonus, string needed,
      string effect ) {
   philosophies[ name ] = ({ type, bonus, needed, effect, ([ ]) });
   save_me();
}
void remove_philosophy( string name ) {
   if ( !philosophies[ name ] ) {
      return;
   }
   map_delete( philosophies, name );
   save_me();
}
string query_philosophy_type( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return philosophies[ name ][ PHILOSOPHY_TYPE ];
}
int query_philosophy_bonus( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return philosophies[ name ][ PHILOSOPHY_BONUS ];
}
string query_philosophy_needed( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return philosophies[ name ][ PHILOSOPHY_NEEDED ];
}
string query_philosophy_effect( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return philosophies[ name ][ PHILOSOPHY_EFFECT ];
}
mapping query_philosophy_all_arguments( string name ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return copy( philosophies[ name ][ PHILOSOPHY_ARGUMENTS ] );
}
mixed query_philosophy_argument( string name, string argument ) {
   if ( !philosophies[ name ] ) {
      return 0;
   }
   return philosophies[ name ][ PHILOSOPHY_ARGUMENTS ][ argument ];
}
void add_philosophy_argument( string name, string argument, mixed args ) {
   if ( !philosophies[ name ] ) {
      return;
   }
   if ( !undefinedp( philosophies[ name ][ PHILOSOPHY_ARGUMENTS ][ argument ] ) ) {
      return;
   }
   philosophies[ name ][ PHILOSOPHY_ARGUMENTS ][ argument ] = args;
   save_me();
}
void remove_philosophy_argument( string name, string argument ) {
   if ( !philosophies[ name ] ) {
      return;
   }
   if ( undefinedp( philosophies[ name ][ PHILOSOPHY_ARGUMENTS ][ argument ] ) ) {
      return;
   }
   map_delete( philosophies[ name ][ PHILOSOPHY_ARGUMENTS ], argument );
   save_me();
}
string *query_all_known( string person ) {
   string *oldstuff, *newstuff = ({}), key;
  if ( person != current_person ) {
     if(unguarded((: file_length, SAVE_DIR + person[0..0]+"/"+person :)) < 1) {
       current_philosophies = "";
     } else {
       current_philosophies = unguarded((:read_file,
         SAVE_DIR+person[0..0]+"/"+person:));
     }
  }
  oldstuff = explode(current_philosophies, "\n");
  foreach ( key in oldstuff ) {
     if ( member_array( key, newstuff ) == -1 ) {
          newstuff += ({ key });
      }
  }
  current_person = person;
  return newstuff;
}
int query_known( string person, string argument ) {
  if(person != current_person) {
    current_philosophies = "";
    if( unguarded( (: file_length,
		    SAVE_DIR + person[0..0]+"/"+person :) ) < 1 ) {
      current_person = person;
      return 0;
    }
    current_person = person;
    current_philosophies =
      unguarded( (: read_file, SAVE_DIR +  person[0..0]+"/"+person :) );
  }
  return (member_array(argument,explode(current_philosophies ,"\n")) != -1);
}
void add_known( string person, string argument ) {
   string *oldstuff, *newstuff = ({}), key;
   if ( !query_known( person, argument ) ) {
      if( !current_philosophies ) {
         current_philosophies = "";
      }
      current_philosophies += argument +"\n";
   }
   current_person = person;
   oldstuff = explode(current_philosophies, "\n");
   foreach ( key in oldstuff ) {
     if ( member_array( key, newstuff ) == -1 ) {
       newstuff += ({ key });
     }
   }
   unguarded( (: write_file, SAVE_DIR +  person[0..0]+"/"+person,
      current_philosophies, 1 :));
}
int remove_known( string person, string argument ) {
   string *oldstuff, *newstuff = ({}), key;
   if ( !this_player()->query_lord() &&
      this_player()->query_name() != "ringo" ) {
      tell_object(this_player(), "Lords only...\n");
      return 1;
   }
   oldstuff = query_all_known( person );
   current_person = person;
   current_philosophies = "";
   foreach ( key in oldstuff ) {
      if ( member_array( key, newstuff ) == -1 &&
        key != argument ) {
          newstuff += ({ key });
          current_philosophies += sprintf( "%s\n", key );
       }
   }
   unguarded( (: write_file, SAVE_DIR +  person[0..0]+"/"+person,
      current_philosophies, 1 :));
}
int reset_known( string person ) {
   if ( !this_player()->query_lord() &&
      this_player()->query_name() != "ringo" ) {
      tell_object(this_player(), "Lords only...\n");
      return 1;
   }
   current_person = person;
   current_philosophies = "";
   unguarded( (: write_file, SAVE_DIR +  person[0..0]+"/"+person,
      current_philosophies, 1 :));
}