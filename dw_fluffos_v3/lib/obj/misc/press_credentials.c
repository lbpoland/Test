inherit "/obj/clothing";
private string _owner = "someone";
private string _paper;
void set_owner_stuff();
void update_stuff();
void setup() {
   add_property("press credentials",1);
   set_name( "badge" );
   set_short( "press credentials badge" );
   add_adjective( ({ "press", "credentials" }) );
   add_alias( "badge" );
   add_property( "nosteal", 1 );
   add_alias( "credentials" );
   set_type( "badge" );
   setup_clothing( 1000 );
   set_weight( 1 );
   reset_drop();
   set_wear_remove_func(base_name(this_object()), "wear_badge");
}
void init() {
   if( _owner == "someone" ) {
      update_stuff();
   }
   if( this_player()->query_name() == lower_case(_owner) ) {
      add_command( "show", "<direct:object:me'credentials'>");
   }
}
void wear_badge(object ob, object player) {
   if (!ob) {
      if (player) {
         player->remove_title("newspaper");
      }
   } else if (_paper) {
      player->set_title("newspaper", "Reporter for " + _paper);
   }
}
void set_owner_stuff() {
   set_long( "This is a small badge with a hand-drawn picture of " +
     _owner + " on it, underneath the logo of " + _paper + ".  "
     "Emblazoned along the bottom are the words \"Official Reporter\".\n");
   if (query_worn_by()) {
      query_worn_by()->set_title("newspaper", "Reporter for " + _paper);
   }
}
int do_show() {
   add_succeeded_mess( ({ "With a practiced flick of your wrist, you display "
     "your press credentials to the room.\n", "With a practiced flick of $p "
     "wrist, $N whips out $p press credentials for " + _paper +
     " and shows them to "
     "everybody.\n" }) );
   return 1;
}
void set_paper_name(string paper) {
   _paper = paper;
}
string query_paper_name() {
   return _paper;
}
void update_stuff() {
   object ob;
   ob = environment();
   if( ob && living( ob ) ) {
      _owner = ob->query_cap_name();
   }
   set_owner_stuff();
}
mapping query_dynamic_auto_load() {
   return ([
     "::" : ::query_dynamic_auto_load(),
     "cred owner" : _owner,
     "paper" : _paper
   ]);
}
void init_dynamic_arg( mapping map ) {
   _paper = map["paper"];
   _owner = map["cred owner"];
   ::init_dynamic_arg( map[ "::" ] );
   set_owner_stuff();
}