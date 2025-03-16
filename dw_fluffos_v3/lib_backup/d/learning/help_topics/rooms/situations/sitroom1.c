#include <situations.h>
#include "path.h"
inherit "/std/room";
void setup() {
  add_property( "commented functions",
                ({  }) );
  add_property( "keywords",
                ({ "situation" }) );
  set_short("Basic situation example room");
  set_light(100);
  set_long("This is a very simple situation example.  "
           "To start it \"press\" the button.  "
           "Please more here to see how it is done.\n"
           "%^CYAN%^Functions shown:%^RESET%^\n"
           "%^YELLOW%^add_situation,  change_situation.%^RESET%^\n");
  add_exit( "next", SIT+"sitroom2", "path" );
  add_exit( "back", LEARNING +"search", "path" );
  add_exit( "exit", ENTRANCE, "path" );
  add_item( "button", "There is a button on the wall you might \"press\".");
  add_situation( "frog",
    new(class situation,
        start_mess: "A little frog appears from nowhere.\n",
        extra_look: "There is a little frog here.",
        add_items: ({ ({ "frog", "The frog is small but happy." }) }),
        chat_rate: ({ 10, 30 }),
        chats: ({"The little frog hops on the spot.",
                 "The little frog says:  Ribbit." }) ,
        end_mess: "The little frog disappears into thin air."
    )
  );
}
int do_press()
{
  tell_object(this_player(),"You press the button.\n");
  tell_object(this_player(),"%^YELLOW%^You just started the frog situation.  "
              "It will go for 60 seconds.  It adds an add_item ( look frog ), "
              "an extra_look to the room ( look ) and some chats.%^RESET%^\n");
  change_situation( "frog", 60 );
  return 1;
}
void init()
{
  this_player()->add_command( "press", this_object(), "button" );
  ::init();
}