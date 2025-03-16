#include <situations.h>
#include "path.h"
inherit "/std/outside";
void setup() {
  add_property( "commented functions",
                ({  }) );
  add_property( "keywords",
                ({ "situation" }) );
  set_short("Situation with a background state example room");
  set_light(100);
  set_long("This is a situations example that is automated "
           "and makes use of a background situation.  "
           "This means that when the automated manager has not "
           "fired up the labelled automated situations you specified "
           "there is another situation that goes by default the rest "
           "of the time.  It is marked in the list by having -1 "
           "for its duration.  "
           "Please more here to see how it is done.\n"
           "%^CYAN%^Functions shown:%^RESET%^\n"
           "%^YELLOW%^add_situation,  automate_situation.%^RESET%^\n");
  add_exit( "back", LEARNING +"search", "path" );
  add_exit( "exit", ENTRANCE, "path" );
  add_situation( "tramp_sleeping",
    new(class situation,
      chats: ({"The tramp snores." }),
      chat_rate: ({ 60,120 }),
      extra_look: "There is a tramp sleeping here.",
      add_items: ({ ({ "tramp",
        "There is dusty and fairly dirty tramp curled up and sleeping "
        "at one side of the road."   }) })
    )
  );
  add_situation( "tramp_awake",
    new(class situation,
      start_mess: "The tramp leaps to his feet, instantly alert.",
      chats: ({"The tramp produces some brightly coloured balls and juggles "
                 "them.",
               "The tramp does a handstand.",
               "The tramp leaps into the air and touches his toes.",
               "The tramp does a little dance.",
               "Dust billows from the frenetic tramp's clothes."
             }),
      chat_rate: ({ 20,30 }),
      extra_look: "There is a tramp bouncing around here.",
      add_items: ({ ({ "tramp",
        "The dusty tramp is bright eyed and very awake."  }) }),
      end_mess: "The tramp flops to the ground and slowly curls into a ball."
    )
  );
  automate_situation( ({ "tramp_sleeping", "tramp_awake" }),
                      ({ -1, 61 }) , WHEN_ANY_TIME, 300 );
}