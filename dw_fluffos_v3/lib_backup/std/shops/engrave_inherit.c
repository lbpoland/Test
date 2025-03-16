#include <money.h>
#include <shops/engrave.h>
void set_engrave_language(string str);
protected int do_engrave( object *things, string message);
mixed query_property(string name);
private string _lingo = "general";
void create() {
   this_object()->add_help_file("engrave");
}
void engrave_init() {
   add_command( "engrave", "<string> on <indirect:object>",
                (: do_engrave($1, $4[0]) :));
}
protected int engrave_living(object *obs) {
   return 0;
}
protected int engrave_wrong_items(object *obs) {
   return 0;
}
protected int engrave_no_money(object *obs, int cost) {
   return 0;
}
int engrave_objects(object *obs, int cost) {
   return 0;
}
protected int do_engrave( object *things, string message) {
   int cost;
   string coststring;
   string place;
   object *liv;
   object *engravable;
   liv = filter(things, (: living($1) :));
   if (sizeof(liv) && !engrave_living(liv)) {
      add_failed_mess("Cannot engrave messages on $I, they are living things.\n", liv);
   }
   things -= liv;
   if (!sizeof(things)) {
      return 0;
   }
   engravable = filter(things,
                       (: ($1->query_property( "shop type" ) == "jewellers" ||
                         $1->query_property( ENGRAVE_PROP ) == 1 ||
                           $1->query_property( "shop type" ) == "armoury") &&
                          $1->query_short() != "holy blade of Soyin" :) );
   if (!sizeof(engravable)) {
      if (!engrave_wrong_items(things - engravable)) {
         add_failed_mess("Cannot engrave messages on $I.\n",
                         things - engravable);
      }
      return 0;
   }
   place = query_property("place");
   if (!place) {
      place = "default";
   }
   coststring = replace_string(message, " ", "");
   cost = (strlen(coststring) * 80) * sizeof(engravable);
   if ( (int) this_player()->query_value_in( place ) < cost ) {
      if (!engrave_no_money(engravable, cost)) {
         add_failed_mess("Not enough money to engrave $I, you need " +
                         MONEY_HAND->money_value_string(cost, place) + ".\n",
                         engravable);
      }
      return 0;
   }
   if ( engrave_objects( engravable, cost ) ) {
      this_player()->pay_money( ( mixed *)MONEY_HAND->create_money_array( cost,
                                place ), place );
      add_succeeded_mess( ({ "You have the message \"" + message +
                            "\" engraved into $I for " +
                            MONEY_HAND->money_value_string(cost, place)
                            + ".\n", "$N gets $I engraved with a message.\n" }),
                            engravable);
      engravable->add_read_mess( message,
                 "neatly engraved letters", _lingo, 1);
      return 1;
   }
   else return 0;
}
void init() {
  engrave_init();
}
void set_engrave_language(string lang) {
  _lingo = lang;
}