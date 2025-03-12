inherit "/std/basic/virtual_quit_control";
#include <playerinfo.h>
#include <config.h>
#define MULTIPLAYER "/obj/handlers/multiplayer"
private int  *saved_co_ords;
private string last_pos;
private string *starts;
protected void inform_entered_game();
int query_creator();
string query_name();
string query_cap_name();
string the_short();
varargs int move(string pos, string messin, string messout);
string query_nationality_start_location();
void create() {
   starts = ({ });
}
int *query_saved_co_ords() { return saved_co_ords; }
protected void set_last_pos(string pos) {
  if(pos[0..4] != "/room")
    last_pos = pos;
}
string query_last_pos() {
   return last_pos;
}
string query_start_pos() {
   string start_pos;
   if ( !sizeof( starts ) ) {
      start_pos = query_nationality_start_location();
   } else {
      start_pos = starts[ 0 ];
   }
   if ( !find_object( start_pos ) ) {
      if ( catch( call_other( start_pos, "??" ) ) ) {
         start_pos = query_nationality_start_location();
      }
   }
   return start_pos;
}
string *query_starts() {
   return starts;
}
void reset_starts() { starts = ({ }); }
void add_start( string start_file, string start_desc ) {
   if ( !starts ) {
      starts = ({ });
   }
   if ( member_array( start_file, starts ) != -1 ) {
      return;
   }
   starts += ({ start_file, start_desc });
}
void remove_start( string start_file ) {
   int i;
   if ( !starts ) {
      return;
   }
   i = member_array( start_file, starts );
   if ( i == -1 ) {
      return;
   }
   starts = delete( starts, i, 2 );
}
void set_start_location( string start_file ) {
  int i;
  if ( !starts) {
    return ;
  }
  i = member_array(start_file, starts);
  if (i <= 0) {
    return ;
  }
  starts = starts[i..i + 1] + starts[0..i - 1] + starts[i + 2..];
}
protected void move_to_start_pos() {
   if (!last_pos || catch(call_other(last_pos, "??"))) {
      last_pos = query_start_pos();
      saved_co_ords = 0;
   }
   move(last_pos);
   if ( !last_pos->query_co_ord() && !last_pos->query_property( "no map" ) &&
         saved_co_ords && !query_creator() ) {
      last_pos->set_co_ord( saved_co_ords );
   }
   inform_entered_game();
}
private function query_extra_login_stuff(string start) {
   string ip_str;
   object *obs;
   object mph;
   string alert;
   int num;
   string *dups;
   switch (this_object()->query_invis()) {
      case 3 :
         start += " (trustee invisible)";
         break;
      case 2 :
         start += " (director invisible)";
         break;
      case 1 :
         start += " (invisible)";
         break;
   }
   mph = load_object(MULTIPLAYER);
   obs = filter(users() - ({ this_object() }),
                (: query_ip_number($1) == query_ip_number(this_object()) &&
                   !$1->query_login_ob() :));
   if (sizeof(obs) &&
       sizeof((dups = mph->check_allowed(this_object(), obs)))) {
      ip_str = " (" + query_ip_name(this_object()) + ")";
      ip_str += " Duplicate: " + query_multiple_short(dups);
   }
   if (!catch(num = PLAYERINFO_HANDLER->query_alerts_for(query_name()))) {
      if (num > 0) {
         alert = " %^BOLD%^%^RED%^" + num + " alert";
         if (num > 1) {
            alert += "s";
         }
         alert += "%^RESET%^";
      }
   }
   if (ip_str) {
      if (!alert) {
         alert = "";
      }
      return (: $(start) +
                       ($1->query_creator()?$(ip_str) + $(alert):"") :);
   } else {
      if (alert) {
         return (: $(start) + ($1->query_creator()?$(alert):"") :);
      } else {
         return (: $(start) :);
      }
   }
}
protected void inform_entered_game() {
   string logon_str;
   if ("/d/liaison/master"->query_member( query_name() ) ) {
      logon_str = query_cap_name() + " enters "
           "" + mud_name() + " %^YELLOW%^(Liaison)";
   } else {
      logon_str = query_cap_name() + " enters " +
           ( this_object()->query_property( "guest" ) ? "as a guest of " : "" ) +"" + mud_name() + ""+
           ( this_object()->query_property( "new player!" ) ? " (new player)" : "" );
   }
   user_event( this_object(), "inform",
               query_extra_login_stuff(logon_str),
               "logon", this_object());
   say(the_short()+" enters the game.\n", 0);
   last_pos->enter(this_object());
}
void inform_reconnect_game() {
   user_event( "inform",
         query_extra_login_stuff(query_cap_name() +
         " reconnects"), "link-death", this_object() );
}
void check_last_pos() {
   last_pos = find_start_pos(this_object(), environment());
   saved_co_ords = find_start_coord(this_object(), environment());
}