#include <config.h>
inherit "/std/room/basic_room";
int squish(string cmd);
void setup() {
  set_co_ord(({0,0,-1000}));
  set_light(100);
  set_short("Discworld departure lounge");
  set_long("This is a small room seemingly attached to the underside of the "
           "disc.  Clear walls all around give you a truly mind-twisting "
           "view of Great A'Tuin and the accompanying elephants.  Lined "
           "up next to little doorways are an assortment of demonic "
           "creatures about to set off to other realities all over "
           "the universe.  You will shortly be getting on one to return "
           "to your normal reality.\n");
  add_item("disc", "You can see the underside of the disc.  It seems to "
           "be made of ... well ... something black and smushy.\n");
  add_item("great a'tuin", "A big turtle.  Like real big.\n");
  add_item("elephant", "Like an elephant only bigger.\n");
  add_item(({ "door", "doorway" }), "Little round hatches from which "
           "assorted demonic creatures launch themselves out on journeys "
           "to other worlds.\n");
  add_item("other world", "They are a bit too far away to see.\n");
  add_item("reality", "But who is to say what is real anyway?\n");
  add_item(({"creature", "demonic creature"}),
           "Well, there is a large bird with glowing "
           "red feet, a 6 foot tall spider with ivy growing up its legs, "
           "a chimera and other assorted sillinesses.\n");
  add_property( "no teleport", 1 );
  set_keep_room_loaded(1);
}
void init() {
  ::init();
  if (!this_player()) {
    return;
  }
  this_player()->command_override((: squish :));
}
int squish(string cmd) {
  if (cmd == "quit" ||
      cmd == "quit2" ||
      cmd == "save" ||
      cmd == "godmother" ||
      cmd == "su") {
    write( "Fat chance, bozo.\n" );
    return 1;
  } else {
    return 0;
  }
}
void event_enter(object ob, string message, object from) {
  if(!from && interactive(ob)) {
    write("%^CYAN%^Greco says: You shouldn't be in here.%^RESET%^\n"
          "Greco throws you back to the Mended Drum.\n");
    ob->move(CONFIG_START_LOCATION);
  }
}
int test_add( object thing, int flag ) {
  if(base_name(thing) != "/global/player" &&
     base_name(thing) != "/global/creator" &&
     base_name(thing) != "/global/lord") {
    call_out( "destroy_thing", 60, thing );
  }
  return 1;
}
void destroy_thing(object thing) {
  if(!thing) {
    return;
  }
    if ( environment( thing ) != this_object() ) {
        return;
    }
  thing->move("/room/rubbish");
}