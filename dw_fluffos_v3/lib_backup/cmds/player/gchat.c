#include <language.h>
#include <player.h>
#include <drinks.h>
inherit "cmds/base";
inherit "cmds/speech";
#define TEAM_HANDLER "/obj/handlers/team"
#define TP this_player()
mixed cmd(string arg) {
  string word, cur_lang, group;
  object ob, *members, *earmuffed;
  return notify_fail( "This command is no longer used.  Please "
   "use \"group say\" instead.\n" );
  if( TP->check_earmuffs( "gchat" ) )
     return notify_fail( "You have gchat ear muffed.\n" );
  group = TEAM_HANDLER->query_group(this_player());
  if(!group)
    return notify_fail("You are not a member of any group.\n");
  if(!arg)
    return notify_fail("Syntax: gchat <message>\n");
  cur_lang = TP->query_current_language();
  if (!LANGUAGE_HAND->query_language_spoken(cur_lang))
    return notify_fail(capitalize(cur_lang)+" is not a spoken language.\n");
  if (!LANGUAGE_HAND->query_language_distance(cur_lang))
    return notify_fail(capitalize(cur_lang)+" is not able to spoken at a "
                       "distance.\n");
  word = query_word_type(arg, "");
  if (word != "")
    word = word + "ing";
  if (TP->query_volume(D_ALCOHOL))
    arg = drunk_speech(arg);
  if(function_exists("mangle_tell", environment(TP)))
    arg = environment(TP)->mangle_tell(arg, ob, 0);
  members = TEAM_HANDLER->query_members(group);
  members -= ({ this_player() });
  if ( !members ) {
    TEAM_HANDLER->leave_group( group, this_player() );
    TEAM_HANDLER->end_group( group );
    write( "Somehow your group has no members.  "
        "Your group has been ended.  "
        "I hope this is okay.\n" );
    return 1;
  }
  earmuffed = ({ });
  foreach( ob in members ) {
    if( ob->check_earmuffs( "gchat" ) ) {
      earmuffed += ({ ob });
      members -= ({ ob });
    }
  }
  if( sizeof( earmuffed ) ) {
    write( capitalize( query_multiple_short( earmuffed ) ) +
        ( sizeof( earmuffed ) > 1 ? " have":" has" )+
        " gchat ear muffed.\n");
  }
  if( !sizeof( members ) ) {
    return notify_fail( "It seems you are the only one listening to "
          "this channel.\n" );
  } else if(word != "asking") {
    if( word != "" )
      word = " "+ word;
    foreach(ob in members) {
      if ( ob && interactive( ob ) )
        ob->event_person_tell(TP, capitalize((string)TP->query_name())+
                              " tells "+ group + word +": ", arg,
                              cur_lang );
    }
    if(cur_lang != "common")
      word += " in "+cur_lang;
    my_mess("You tell "+ group + word +": ", arg);
    TP->add_tell_history( "You tell "+ group + word + ": ", arg );
  } else {
    foreach(ob in members) {
      if ( ob && interactive( ob ) )
        ob->event_person_tell(TP, capitalize((string)TP->query_name())+
                              " asks "+group+": ", arg, cur_lang );
    }
    if(cur_lang != "common")
      word = " in "+ cur_lang;
    else word = "";
    my_mess( "You ask "+ group + word +": ", arg);
    TP->add_tell_history( "You ask "+ group + word + ": ", arg );
  }
  TP->adjust_time_left(-5);
  return 1;
}