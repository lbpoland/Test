#include <situations.h>
#include "path.h"
inherit "/std/outside";
void setup() {
  add_property( "commented functions",
                ({  }) );
  add_property( "keywords",
                ({ "situation" }) );
  set_short("Exclusion and random words situations example room");
  set_light(100);
  set_long("This is a of situations example that is automated "
           "and makes use of random words and exclusion.  "
           "It is at a pier where one ship may dock at a time.  "
           "Exclusion means one situation (or set of them) "
           "prevents another from happenning at the same time "
           "and vice versa.  "
           "Random words mean that the text changes each time.  "
           "Just wait to experience the situations within a minute or so.  "
           "Please more here to see how it is done.\n"
           "%^CYAN%^Functions shown:%^RESET%^\n"
           "%^YELLOW%^add_situation,  automate_situation.%^RESET%^\n");
  add_exit( "back", LEARNING +"search", "path" );
  add_exit( "next", SIT+"sitroom5", "path" );
  add_exit( "exit", ENTRANCE, "path" );
  add_item( "pier", "There is small pier here." );
  add_situation( "boat1",
    new(class situation,
      start_mess: "A little fishing boat comes up to the pier.  "
         "It has the name \"#1\" painted on the side.\n"
         "A fisherman jumps off the boat and ties its painter to a post.",
      chats: ({"The little boat bobs up and down next to the pier.",
               "A fisherman hops off the little boat." }),
      chat_rate: ({ 20, 30 }),
      extra_look: "There is a little boat here.",
      add_items: ({ ({ ({ "#1","little boat" }),
        "There is little fishing boat tied up at the pier here.  "
        "The name \"#1\" is painted on the side."   }) }),
      end_mess: "The fishermen get back on board and "
         "the little boat moves on.",
      random_words: ({ ({ "Honey Toad", "Piker", "Bing" }) })
    )
  );
  add_situation( "boat2",
    new(class situation,
      start_mess: "A fat trading vessel comes up to the pier.  "
         "It has the name \"#1\" painted on the prow.\n"
         "A sailor jumps off and ties the vessel to a post.",
      chats: ({"The trading vessel thumps against the pier.",
               "A sailor comes ashore.",
               "#2 is unloaded from the vessel.",
               "#3 is loaded onto the vessel." }),
      chat_rate: ({ 10, 20 }),
      extra_look: "There is a trading vessel docked here.",
      add_items: ({ ({ ({ "#1","fat vessel","ship" }),
        "There is a trading vessel docked at the pier here.  "
          "The name \"#1\" is painted on the prow." }) }),
      end_mess: "The sailors get back on board and "
         "the trading vessel departs.",
      random_words: ({ ({ "Fat Cat", "Scumbag", "Cap Pig" }),
          ({ "A pair of slaves", "A bale of wool", "A bolt of cloth" }),
          ({ "A stock option", "A cage of frogs", "A wooden crate" }), })
    )
  );
  automate_situation( "boat2", 61, WHEN_ANY_TIME, 300, "boat" );
  automate_situation( "boat1", 50, WHEN_ANY_TIME, 200, "boat" );
}