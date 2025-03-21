#include "/cmds/guild-race/masters/marry.h"
#define RING "/obj/misc/wedding_ring.c"
#define LOG "/w/olorin/responselog"
#define MAXLOG 8000
object player, marry1, marry2, ring1, ring2;
int found, response_index;
string asking, askingwho, *words, *yes_array, *no_array;
mapping local_prop, yes_response, no_response;
void do_accept();
void do_refuse();
void create() {
   yes_response = ([ "say":({ "yes", "yep", "sure", "ok",
                     ({ "will" , "i" }), ({ "do" , "i" }) }),
                     "soul":({ "nod" , "ack", }) ]);
   no_response = ([ "say":({ "no", "nope", ({ "won't", "i" }),
                          ({ "don't", "i" }), ({ "can't", "i" }),
                    "cannot" }),
                    "soul":({ ({ "shake" , "head" }), "panic", "puke" }) ]);
   local_prop = ([ MARRYPROP : 1, ]);
}
object add_marry_shadow( object p, object m1, object m2 ) {
   player = p;
   marry1 = m1;
   marry2 = m2;
   askingwho = (string)marry1->query_name();
   asking = ASKFIRST;
   tell_object( player, "Now you should ask " +
         (string) marry1->query_short() + " whether " +
         (string) marry1->query_pronoun() + " will marry " +
         (string) marry2->query_short() + "\n");
   return shadow( p, 1 );
}
string remove_read_marks(string str) {
   int index, size;
   string result;
   string temp;
   index = 0;
   size = strlen(str);
   result = "";
   while (index < size) {
      temp = str[index..index];
      if (((temp >= "a") && (temp <= "z")) ||
    (temp == " ") || (temp == "'")) result += temp;
      else result += " ";
      index++;
   }
  return result;
}
void check_response( string resptype, string mess ) {
   if ( mess && strlen( mess ) ) {
      mess = lower_case( mess );
      mess = remove_read_marks(mess);
      words = explode( mess, " " );
      yes_array = yes_response[ resptype ];
      no_array = no_response[ resptype ];
      response_index = sizeof( yes_array );
      while ( response_index-- ) {
   if ( !stringp( yes_array[ response_index ] ) ) {
      if ( ( member_array( yes_array[ response_index ][ 0 ],
         words ) != -1 ) &&
     ( member_array( yes_array[ response_index ][ 1 ],
         words ) != -1 ) ) {
         do_accept();
         return;
      }
   } else {
      if ( member_array( yes_array[ response_index ], words ) != -1 ) {
             do_accept();
         return;
      }
   }
      }
      response_index = sizeof( no_array );
      while ( response_index-- ) {
   if ( !stringp( no_array[ response_index ] ) ) {
      if ( ( member_array( no_array[ response_index ][ 0 ],
         words ) != -1 ) &&
     ( member_array( no_array[ response_index ][ 1 ],
         words ) != -1 ) ) {
         do_refuse();
         return;
      }
   } else {
      if ( member_array( no_array[ response_index ], words ) != -1 ) {
         do_refuse();
         return;
      }
   }
      }
#ifdef LOG
      if ( file_size( LOG ) <= MAXLOG)
  unguarded((: write_file, LOG ,
             "MARRY response: "+resptype+": '"+mess+"'\n" :));
#endif
   }
}
void event_person_say( object ob, string start, string mess, string lang ) {
   if ( ob->query_name() == askingwho ) {
      check_response("say", mess);
   }
   player->event_person_say( ob, start, mess, lang );
   return;
}
void event_person_tell(object ob, string start, string mess, string lang) {
   if ( ob->query_name() == askingwho ) {
      check_response("say", mess);
   }
   player->event_person_tell( ob, start, mess, lang );
   return;
}
void event_soul(object ob, string mess, object *avoid, string verb,
                string last, mixed at) {
   if ( sizeof( avoid ) &&
       avoid[0]->query_name() == askingwho ) {
      check_response( "soul", mess );
   }
   response_index = sizeof( avoid );
   while ( response_index-- ) {
      if ( avoid[ response_index ] == player ) {
   return;
      }
   }
   tell_object( player, mess );
   return;
}
void do_accept() {
   if ( asking == ASKFIRST ) {
      asking = ASKSECOND;
      askingwho = (string) marry2->query_name();
      tell_object( player, (string) marry1->query_pronoun() +
      " accepted. Now you should ask " +
      (string) marry2->query_short() + " whether " +
      (string) marry2->query_pronoun() + " will marry " +
      (string) marry1->query_short() + "\n" );
      tell_object( marry1, "You accepted.\n" );
   } else if ( asking == ASKSECOND ) {
      asking = DONEASK;
      askingwho = "*NoOne*";
      tell_object( player, (string) marry2->query_pronoun() +
      " accepted. Now you can ask if there are any objections or" +
      " you can finalize the wedding with 'marry them'.\n" );
      tell_object( marry2, "You accepted.\n" );
   } else {
      tell_object( player, "Something is wrong here, please tell Olorin " +
      "what you where doing.\n" );
#ifdef LOG
     unguarded((: write_file, LOG ,
                "marry_error "+
     "in accept:" + asking + ";" + askingwho + "(" +
     (string) marry1->query_short() + " to " +
     (string) marry2->query_short() + ")" :));
#endif
      call_out( "remove_propose_shadow", 0 );
   }
}
void do_refuse() {
   if ( asking == ASKFIRST ) {
      tell_object( player, (string) marry1->query_pronoun() +
      " wimpied out.\n" );
      tell_object( marry1, "You refused, the marriage is off.\n" );
   } else if ( asking == ASKSECOND ) {
      tell_object( player , (string) marry2->query_pronoun() +
      " wimpied out.\nYou'd better try to console " +
      (string) marry1->query_short() + "\n" );
      tell_object( marry2, "You refused, how will you explain that to "+
      (string) marry1->query_short() + ".\n" );
   } else {
      tell_object( player, "Something is wrong here, please tell Olorin " +
      "what you where doing.\n" );
#ifdef LOG
      unguarded((: write_file, LOG ,
                 "marry_error"+
     "in refuse:" + asking + ";" + askingwho + "(" +
     (string) marry1->query_short() + " to " +
     (string) marry2->query_short() + ")" :));
#endif
   }
   call_out( "remove_marry_shadow", 0 );
}
mixed query_property( string str ) {
   if ( str == MARRYPROP ) {
      return 1;
   } else {
      return player->query_property( str );
   }
}
int do_wedding() {
   if ( environment( player ) == environment( marry1 ) ) {
      if ( environment( player ) == environment( marry2 ) ) {
   marry1->add_property( "spouse", marry2->query_name() );
   marry2->add_property( "spouse", marry1->query_name() );
   ring1 = clone_object( RING );
   ring1->set_owner( marry1->query_short() );
   ring1->set_giver( marry2->query_short() );
   ring1->move( marry1 );
   ring2 = clone_object( RING );
   ring2->set_owner( marry2->query_short() );
   ring2->set_giver( marry1->query_short() );
   ring2->move( marry2 );
   tell_object( player, "They are now married, you'd better tell them.\n" );
   call_out( "remove_marry_shadow", 0 );
   return 1;
      } else {
   tell_object( player, marry2->query_short() +
         " seems to have wandered off.\n" +
         "Perhaps you should try to console " +
         (string) marry1->query_short() + "\n" );
      }
   } else {
      tell_object( player, marry2->query_short() +
      " seems to have wandered off.\n" +
      "Perhaps you should try to console " +
      (string) marry2->query_short()+"\n" );
   }
   call_out( "remove_marry_shadow", 0 );
   return 0;
}
int abort_wedding() {
   call_out( "remove_marry_shadow", 0 );
   return 0;
}
void remove_marry_shadow() {
   destruct( this_object() );
   return;
}