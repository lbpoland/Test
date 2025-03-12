#include <money.h>
#include <vault.h>
inherit "/std/room";
#define TIME_LIMIT 500
#define LO laundryowner->the_short()
string location, laundry_room;
int visit_cost;
object laundryowner;
void set_location(string str) { location = str; }
void set_visit_cost(int i) { visit_cost = i; }
void set_laundryowner(object ob) { laundryowner = ob; }
void set_laundry_exit(string direc, mixed dest, string type) {
  laundry_room = dest;
  add_exit(direc, dest, type);
  modify_exit( direc, ({ "function", "check_customer" }) );
  modify_exit( direc, ({ "closed", 1}));
}
int check_customer( string verb, object thing, string special ) {
  string owner;
  object vroom;
  if(!laundryowner || environment(laundryowner) != this_object())
    return notify_fail("Since the owner of this laundry is missing "
      "you think twice before entering the laundry.\n");
  if( !interactive(thing) )
    return 0;
  owner = (string)thing->query_name();
  if ( !( vroom = find_object( laundry_room ) ) )  {
      laundry_room->load_me();
      vroom = find_object( laundry_room );
  }
  if(sizeof(filter_array(all_inventory(vroom),
                         (: userp( $1 ) :)))) {
    tell_object(thing, LO + " intercepts you.\n");
    tell_room( this_object(), LO + " intercepts "+
               (string)thing->the_short() +".\n",
               thing);
    laundryowner->do_command("say No more than one person at a time in "
      "laundry room.  It can be very dangerous!");
    laundryowner->do_command("emote taps his head implying madness.");
    return notify_fail( "" );
  }
  if(query_property(owner)) {
    remove_property(owner);
    tell_object(thing, LO + " opens the round door of the laundry and "
      "signalls you to enter.\n" );
    tell_room(this_object(), LO + " signalls "+
              (string)thing->the_short() +" to enter the laundry through "
                "the small round door of the laundry.\n", thing );
    call_out("check_idler", TIME_LIMIT, thing);
    return 1;
  }
  if ( (int)thing->query_value_in( location ) +
       (int)thing->query_value_in( "default" ) < visit_cost ) {
    tell_object( thing, LO + " intercepts you.\n" );
    tell_room( this_object(), LO + " intercepts "+
               (string)thing->the_short() +".\n",
               thing );
    laundryowner->do_command("say Well... I am but a poor man.  I cannot "
      "just let you use my fine, imp-powered laundry for nothing!\n" );
    laundryowner->do_command("emote sniffs.\n" );
    return notify_fail( "" );
  }
  thing->pay_money((mixed *)MONEY_HAND->create_money_array(visit_cost,
                                                           location),
                   location);
  tell_object( thing, "You pay " + LO + " who signals you to go through "
    "the small, round door of the laundry.\n" );
  tell_room( this_object(), (string)thing->the_short() +
             " pays " + LO + " who signals to "
             + (string)thing->query_objective() + " to move through "
             "a small, round door and enters the laundry.\n", thing );
   return 1;
}
void player_quitting(object who, object env) {
}