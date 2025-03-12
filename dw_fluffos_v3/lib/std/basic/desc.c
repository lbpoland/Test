inherit "/std/basic/hide_invis";
nosave mixed short_d;
nosave mixed plural_d;
nosave mixed long_d;
private nosave string short_desc;
void set_short(mixed words) {
  if (functionp(words)) {
    if (!short_d)
      plural_d = (: pluralize(evaluate(short_d)) :);
  } else {
     if ( !short_d && words && ( words != "" ) )
        plural_d = pluralize( words );
  }
   short_d = words;
}
void set_long(mixed str) { long_d = str; }
void set_main_plural(mixed str) { plural_d = str; }
mixed query_main_plural() { return plural_d; }
mixed query_short() {
   if ( functionp( short_d ) )  {
      return evaluate(short_d);
   }
   else return short_d;
}
string query_short_desc() {
  string tmp;
  if(!short_desc) {
    short_desc = "";
    if(this_object()->query_str() > 16)
      short_desc += "strapping ";
    else if(this_object()->query_dex() > 16)
      short_desc += "nimble ";
    else if(this_object()->query_int() > 16)
      short_desc += "studious ";
    else if(this_object()->query_wis() > 16)
      short_desc += "pious ";
    short_desc += "young ";
    switch(this_object()->query_guild_ob()) {
    case "/std/guilds/warrior":
      short_desc += (this_object()->query_gender() == 2? "female " : "male ") +
        "warrior";
      break;
    case "/std/guilds/thief":
      tmp = "/std/guilds/thief"->query_guild_data();
      if(tmp)
        short_desc += (this_object()->query_gender() == 2? "female ": "male ")+
          tmp;
      else
        short_desc += (this_object()->query_gender() == 2? "female ": "male ")+
          "thief";
      break;
    case "/std/guilds/wizard":
      short_desc += (this_object()->query_gender() == 2? "female " : "male ") +
        "wizard";
      break;
    case "/std/guilds/witch":
      short_desc += "witch";
      break;
    case "/std/guilds/assassin":
      short_desc += (this_object()->query_gender() == 2? "female " : "male ") +
        "assassin";
      break;
    default:
      short_desc += (this_object()->query_gender() == 2? "lass" : "lad");
    }
  }
  return short_desc;
}
string query_plural_desc() {
    return pluralize( query_short_desc() );
}
varargs mixed query_long(string str, int dark) {
  if (functionp(long_d))
    return evaluate(long_d);
  return long_d;
}
string query_long_details(string arg, int dark, object looker) {
   return 0;
}
varargs string short(int dark) {
  if (functionp(short_d))
    return (string)evaluate(short_d);
  return short_d;
}
string long(string str, int dark) {
  if (!long_d)
    return "You see nothing particularly interesting.\n";
  if (functionp(long_d))
    return (string)evaluate(long_d);
  return long_d;
}
varargs string query_plural( int dark ) {
  if (!plural_d)
    if (!short( dark ))
      return 0;
    else
      return pluralize(short( dark ));
  if (functionp(plural_d))
    return (string)evaluate(plural_d);
  return plural_d;
}
string query_determinate(object thing) {
  if(query_visible(thing)) {
#ifdef USE_ROLE_PLAYING_SHORTS
    if(interactive(this_object()) &&
      thing->query_role_playing() &&
       !thing->is_friend(this_object()->query_name()))
      return "a ";
#endif
    return (string)this_object()->query_property( "determinate" );
  }
  return "";
}
varargs string pretty_short( object thing ) {
   int dark, verbose;
   if ( objectp( thing ) ) {
      dark = (int)thing->check_dark( (int)this_object()->query_light() );
      if(userp(thing))
        verbose = thing->query_verbose("names");
   }
   return (string)this_object()->short( dark, verbose );
}
varargs string pretty_plural( object thing ) {
   int dark;
   if ( objectp( thing ) )
      dark = (int)thing->check_dark( (int)this_object()->query_light() );
   return (string)this_object()->query_plural( dark );
}
varargs string a_short( int flag ) {
   if ( this_object() == this_player() && !flag )
      this_object()->remove_hide_invis( "hiding" );
   return "$a_short:"+ file_name( this_object() ) +"$";
}
varargs string one_short( int flag ) {
   if ( this_object() == this_player() && !flag )
      this_object()->remove_hide_invis( "hiding" );
   return "$one_short:"+ file_name( this_object() ) +"$";
}
varargs string poss_short( int flag ) {
   if ( this_object() == this_player() && !flag )
      this_object()->remove_hide_invis( "hiding" );
   return "$poss_short:"+ file_name( this_object() ) +"$";
}
varargs string the_poss_short( int flag ) {
   if ( this_object() == this_player() && !flag )
      this_object()->remove_hide_invis( "hiding" );
   return "$the_poss_short:"+ file_name( this_object() ) +"$";
}
varargs string the_short( int flag ) {
   if ( this_object() == this_player() && !flag )
      this_object()->remove_hide_invis( "hiding" );
   return "$the_short:"+ file_name( this_object() ) +"$";
}