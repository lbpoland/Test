#include <config.h>
#include <weather.h>
#include <move_failures.h>
#ifndef __DISTRIBUTION_LIB__
#include <special_day.h>
#endif
inherit  "/cmds/base";
#define TP this_player()
private string *_snow_creatures = ({
    "snowman",
    "snowwoman",
    "snowboy",
    "snowgirl",
    "snowbunny",
    "snowfrog",
    "snowball",
    "snowwomble",
    "snowangel",
    "snowcabbage",
    "snowwitch",
    "snowwizard",
    "snowwarrior",
    "snowthief",
    "snowpriest",
    "snowassassin",
    "snowfamily",
    "snowfox",
    "snowdwarf",
    "snowplayerkiller",
    "snowtroll"
});
private string _make_pattern_cache;
void create() {
    ::create();
    _snow_creatures = sort_array( _snow_creatures, 1 );
}
int is_snowing(object player, string str) {
  object env;
  int *co_ords;
  env = environment(player);
  if ((string)env->query_property("location") == "inside") {
    add_failed_mess("You must be outside to make a " + str + ".\n");
    return 0;
  }
  co_ords = (mixed *)env->query_co_ord();
  if (!WEATHER->query_snowing(env)) {
     add_failed_mess("You need snow to make a " + str + ".\n");
     return 0;
  }
  return 1;
}
mixed cmd(string str) {
  object ob;
  object env;
  env = environment(TP);
  switch (str) {
  case "snowball" :
    if (is_snowing(TP, str)) {
      ob = clone_object("/std/environ/snowball");
      if (ob->move(TP) != MOVE_OK) {
        add_succeeded_mess(({ "$N try to make a snowball, but you cannot "
                              "pick it up so it disintergrates in "
                              "disinterest.\n",
                              "$N tries to make a snowball, but they cannot "
                                "pick it up.\n" }));
      } else {
        add_succeeded_mess(({
          "$N $V a lovely big snowball.  Have fun with it ;)\n",
            "$N $V a lovely big snowball.\n" }));
      }
      return 1;
    }
    break;
#ifndef __DISTRIBUTION_LIB__
  case "cream pie":
    if (SPECIAL_DAY_HANDLER->query_special_day() == CREAM_PIE_DAY) {
      if (TP->query_property("made cream pie")) {
        add_failed_mess("You made a cream pie less than 30 seconds ago.  "
                        "Don't be greedy now.\n");
      } else {
        ob = clone_object("/obj/misc/cream_pie");
        if (ob->move(TP) != MOVE_OK) {
          add_succeeded_mess(({ "You try to magicaly conjure a cream pie up "
                                  "out of nowhere, but you cannot pick it up.\n",
                                  "$N tries to conjure up a cream pie, but "
                                  "just looks silly.\n" }));
          ob->dest_me();
          return 1;
        } else {
          TP->add_property("made cream pie", 1, 30);
          add_succeeded_mess("$N conjure$s up $I.\n", ({ ob }));
          return 1;
        }
      }
    } else {
       add_failed_mess("You can only create cream pies on cream pie day!\n");
    }
    break;
  default:
    if ( member_array( str, _snow_creatures ) > -1 ) {
        if (is_snowing(TP, str)) {
          ob = clone_object("/std/environ/snowman");
          ob->set_type(str);
          ob->move(env);
          add_succeeded_mess("$N $V a beautiful " + str + ".\n");
          return 1;
        }
    }
    break;
#endif
  }
  return 0;
}
mixed *query_patterns() {
    if ( !_make_pattern_cache ) {
        _make_pattern_cache = "{" + implode( _snow_creatures +
            ({ "cream pie" }), "|" ) + "}";
    }
   return ({ _make_pattern_cache, (: cmd($4[0]) :) });
}