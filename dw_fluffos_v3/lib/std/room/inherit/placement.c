#include <obj_parser.h>
#include <dirs.h>
#include <room/placement.h>
#define PLAYTESTING
#define MAX_PLACED 10
#define PLACEMENT_CURRENT_ROOM_HIDDEN "current room hidden"
#define OPPOSITE 0
#define ABOVE    1
#define BELOW    2
#define RIGHT    3
#define LEFT     4
#define OPPOSITE_DESCS ({ \
  "opposite which", \
  "facing which", \
})
#define ABOVE_DESCS ({ \
  "above which", \
  "over which", \
})
#define BELOW_DESCS ({ \
  "under which", \
  "below which", \
})
#define RIGHT_DESCS ({ \
  "to the right of which", \
})
#define LEFT_DESCS ({ \
  "to the left of which", \
})
#define HANGING_VERBS ({ \
  "hanging", \
  "suspended", \
  "dangling", \
})
#define HANGING_PREPOSITIONS ({ \
  "from", \
  "on", \
})
#define WALL_PREPOSITIONS ({ \
  "beside", \
  "against", \
})
#define CORNER_PREPOSITIONS ({ \
  "in", \
})
#define ABOUT_PREPOSITIONS ({ \
  "near", \
  "at", \
})
string get_pos_desc(int pos_int);
int do_place(object *obs, string, string, mixed *args, string);
int do_help(object *);
int get_pos_int(string str);
string extra_look(object);
string object_position_desc(object thing);
string object_desc(object thing);
string object_desc2(object thing);
object *build_structure();
int find_opposite(int pos, object *structure);
int find_above(int pos, object *structure);
int find_below(int pos, object *structure);
int find_left(int pos, object *structure);
int find_right(int pos, object *structure);
int get_structure_index(object ob);
varargs int is_beside_wall(int pos, int flag);
varargs int is_in_corner(int pos, int flag);
nosave object *needs_described;
nosave object *have_described;
nosave int orientation;
nosave mapping _wall_names;
nosave string furniture_long = "";
void init() {
 if(!this_player() || !interactive(this_player()))
     return;
  this_player()->add_command("place", this_object(),
    "<indirect:object'furniture'> so it is <word'verb'> "
    "{"+implode(ABOUT_PREPOSITIONS+HANGING_PREPOSITIONS+WALL_PREPOSITIONS+CORNER_PREPOSITIONS, "|")+"} "
    "the <string:'location'> [wall|corner]");
  this_player()->add_command("place", this_object(),
    "<indirect:object'furniture'> "
    "{"+implode(ABOUT_PREPOSITIONS+HANGING_PREPOSITIONS+WALL_PREPOSITIONS+CORNER_PREPOSITIONS, "|")+"} the <string'location'> [wall|corner]");
  this_player()->add_command("displace", this_object(),
    "<indirect:object'furniture'>");
  this_player()->add_command("place", this_object(),
                             "help", (: do_help(0) :));
  this_player()->add_command("place", this_object(),
                             "help <indirect:object'furniture'>",
                             (: do_help($1[0]) :));
}
void set_wall_name(string direction, string name) {
   int pos;
   if (!_wall_names) {
      _wall_names = ([ ]);
   }
   pos = get_pos_int(direction);
   _wall_names[pos] = name;
}
string query_wall_name_pos(int pos) {
   if (!_wall_names) {
      _wall_names = ([ ]);
   }
   if (_wall_names[pos]) {
      return _wall_names[pos];
   }
   if(!orientation)
   {
      if(pos % 2)
      {
         return "corner";
      }
      return "wall";
   }
   if(pos % 2)
   {
      return "wall";
   }
   return "corner";
}
string query_wall_name(string direction) {
   int pos;
   pos = get_pos_int(direction);
   return query_wall_name_pos(pos);
}
string query_another(object ob)
{
  object *obs;
  string another;
  obs = filter(have_described,
    (: $1->query_plural() == $(ob->query_plural()) :));
  switch(sizeof(obs))
  {
    case 0 :
      another = " a";
      break;
    case 1 :
      another = " another";
      break;
    default :
      another = " yet another";
      break;
  }
  return another;
}
string query_more(object ob)
{
  object *obs;
  string more;
  obs = filter(have_described,
    (: $1->query_plural() == $(ob->query_plural()) :));
  switch(sizeof(obs))
  {
    case 0 :
      more = "";
      break;
    default :
      more = " more";
      break;
  }
  return more;
}
string clutter_string(object ob) {
  mixed *things;
  string cluttered = "";
  if(ob->query_has_surface()) {
    things = ob->find_inv_match("all", ob);
    things = unique_array(things, (: $1->query_plural() :));
    switch(sizeof(things)) {
      case 1 :
        if(sizeof(things[0]) == 1)
          cluttered = " is";
        else
          cluttered = " are";
        cluttered += " " + query_multiple_short(things[0]);
        break;
      default :
        break;
    }
  }
  return cluttered;
}
string query_multiple_furniture_short(object *obs) {
  object *group;
  mixed *things;
  string str;
  string *strs;
  strs = ({ });
  things = unique_array(obs, (: $1->query_plural() :));
  foreach(group in things)
  {
    switch(sizeof(group))
    {
      case 0 :
        break;
      case 1 :
        str = query_another(group[0])[1..];
        str += " " + group[0]->query_short();
        break;
      default :
        str = query_num(sizeof(group));
        str += query_more(group[0]);
        str += " " + group[0]->query_plural();
        break;
    }
    strs += ({ str });
  }
  return query_multiple_short(strs);
}
varargs int is_in_corner(int pos, int flag)
{
  if(orientation && !flag)
    return is_beside_wall(pos, 1);
  if(member_array(pos, ({ 3, 5, 7, 9 })) != -1)
    return 1;
  return 0;
}
varargs int is_beside_wall(int pos, int flag)
{
  if(orientation && !flag)
  {
    return is_in_corner(pos, 1);
  }
  if(member_array(pos, ({ 2, 4, 6, 8 })) != -1)
  {
    return 1;
  }
  return 0;
}
int is_wall_hanging(int pos)
{
  if(orientation)
  {
    if(member_array(pos, ({ 13, 15, 17, 19 })) != -1)
    {
      return 1;
    }
    return 0;
  }
  if(member_array(pos, ({ 12, 14, 16, 18 })) != -1)
  {
    return 1;
  }
  return 0;
}
int is_in_centre(int pos)
{
  if(pos == 1)
  {
    return 1;
  }
  return 0;
}
int query_max_space_around(int pos)
{
  if(is_in_corner(pos))
  {
    return 2;
  }
  if(is_beside_wall(pos))
  {
    return 3;
  }
  if(is_in_centre(pos))
  {
    return 4;
  }
  return 0;
}
int do_help(object ob) {
  string str;
  string *bits;
  if(ob && !ob->query_furniture())
    return this_player()->add_failed_mess(this_object(),
                                          "$I is not a piece of furniture.\n",
                                          ({ ob }));
  str = "The place command requires a furniture object, an optional verb, "
    "a preposition and a location.  ";
  if(!ob) {
    str += "Which verbs are available depends on the furniture.  Hanging "
      "furniture can use " + query_multiple_short(HANGING_VERBS) + ".  ";
  } else {
    if(ob->query_allowed_room_verbs())
      bits = filter(keys(ob->query_allowed_room_verbs()), (: $1 != "" :));
    switch(sizeof(bits)) {
    case 0:
      str += "The " + ob->the_short() + " has no verbs.\n";
      break;
    case 1:
      str += "The verb for " + ob->the_short() + " is " +
        query_multiple_short(bits) + ".\n";
      break;
    default:
      str += "The verbs available for " + ob->the_short() + " are " +
        query_multiple_short(bits) + ".\n";
    }
  }
  str += "The prepositions for hanging things are " +
    query_multiple_short(HANGING_PREPOSITIONS) + ", while items may be "
    "placed " + query_multiple_short(WALL_PREPOSITIONS) + " walls, " +
    query_multiple_short(CORNER_PREPOSITIONS) + " corners, or " +
    query_multiple_short(ABOUT_PREPOSITIONS) + " other objects.  "
    "The " + query_multiple_short(({"ceiling", "floor", "centre", "north",
                                      "south", "east", "west", "northeast",
                                      "southeast", "northwest", "southwest"}))+
    " may be used as locations.\n";
  write(str);
  return 1;
}
int do_place(object *obs, string, string, mixed *args, string)
{
  int pos, allowed;
  string k, v;
  mapping allowed_verbs;
  object *things;
  object *placed;
  object* already_around;
  class obj_match result;
#ifdef DEBUG
  debug_printf("Obs: %O, args: %O", obs, args);
#endif
  if(this_player() &&
     !this_object()->test_occupier(this_player()->query_name()) &&
     !this_player()->query_creator()) {
    this_player()->add_failed_mess(this_object(),
                                   "You don't own this house.\n", ({ }));
    return 0;
  }
  if(sizeof(obs) > 1) {
    this_player()->add_failed_mess(this_object(),
      "You may only place one object at a time.\n", ({ }));
    return 0;
  }
  if(!obs[0]->query_furniture()) {
    this_player()->add_failed_mess(this_object(),
      "$I is not suitable furniture.\n", ({ obs[0] }));
    return 0;
  }
  placed = filter(all_inventory(this_object()),
    (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) :));
  if(!obs[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION))
  {
    if(sizeof(placed) >= MAX_PLACED)
    {
      if(this_player())
         this_player()->add_failed_mess(this_object(),
                                        "$C$"+this_object()->the_short() +
                                        " is too cluttered to place anything "
                                        "else.\n", ({ }));
      return 0;
    }
  }
  if(obs[0]->query_property(PLACEMENT_IMMOVABLE)) {
    this_player()->add_failed_mess(this_object(),
                                   "Try as you might you cannot move $I.\n",
                                   ({ obs[0] }));
    return 0;
  }
  if(member_array(args[1], HANGING_PREPOSITIONS + WALL_PREPOSITIONS
    + CORNER_PREPOSITIONS + ABOUT_PREPOSITIONS) != -1)
  {
    args[2] = replace_string(args[2], "ern ", " ");
    if((member_array(EXPAND_EXIT(args[2]), ({"north", "south", "east",
      "west", "northeast", "southeast", "southwest", "northwest",
      "centre"})) != -1) || sizeof(match_objects_for_existence(args[2],
      ({ this_object() }) )))
    {
      int i;
      string *new_args;
      new_args = ({ });
      new_args += ({ args[0] });
      new_args += ({ "" });
      for(i = 1; i < sizeof(args); i++)
      {
        new_args += ({ args[i] });
      }
      args = new_args;
    }
  }
  allowed_verbs = obs[0]->query_allowed_room_verbs();
  if(allowed_verbs)
  {
    allowed_verbs += ([ "" : "" ]);
    foreach(k, v in allowed_verbs)
    {
      if(k == args[1] || v == args[1])
      {
        allowed = 1;
        break;
      }
    }
  }
  if(!allowed)
  {
    string *verb_keys;
    string extra = "";
    if(allowed_verbs)
    {
      verb_keys = keys(allowed_verbs);
      verb_keys -= ({ "" });
      verb_keys = map(verb_keys, (: ("\"" + $1 + "\"") :));
      extra = "  You may only place $I " +
        query_multiple_short(verb_keys) + ".";
    }
    if(this_player())
      this_player()->add_failed_mess(this_object(),
      "You can't place $I with that verb."
      + extra + "\n", ({ obs[0] }));
    return 0;
  }
  if(sizeof(args) == 3)
  {
    string *shrapnel;
    shrapnel = explode(args[2], " ");
    args -= ({ args[2] });
    args += shrapnel;
  }
  if(args[1] != "")
  {
    args[1] = " " + args[1];
  }
  pos = get_pos_int(args[3]);
  if(args[3] == "floor" && args[2] == "on")
    args[2] = "in";
  if(member_array(args[2], ABOUT_PREPOSITIONS) != -1)
  {
    if(!pos)
    {
      result = (class obj_match)match_objects_in_environments(args[3], ({ this_object() }));
      if (result->result != OBJ_PARSER_SUCCESS) {
         if(this_player()) {
            add_failed_mess( match_objects_failed_mess( result ));
         }
         return 0;
      }
      things = result->objects;
      pos = things[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
      if(pos < -1)
      {
        if(this_player())
        this_player()->add_failed_mess(this_object(),
          "$I is placed around another piece of "
          "furniture.\n", ({ things[0]->the_short() }));
        return 0;
      }
      if(pos == get_structure_index(obs[0]))
      {
        if(this_player()) {
          if(sizeof(args) >= 4)
            this_player()->add_failed_mess(this_object(),
                   "You can't place $I " + args[2] + " the " + args[3] + ".\n",
                                           ({ obs[0] }));
          else
            this_player()->add_failed_mess(this_object(),
                   "You can't place $I " + args[2] + " itself.\n", ({ obs[0] }));
        }
        return 0;
      }
      if(pos > 9)
      {
        if(this_player())
        this_player()->add_failed_mess(this_object(),
          "You can't place $I " + args[2] + " " +
          things[0]->the_short() + ".\n", ({ obs[0] }));
        return 0;
      }
      if(pos == -1)
      {
        if(this_player())
        this_player()->add_failed_mess(this_object(),
          "$I isn't placed.\n", ({ things[0] }));
        return 0;
      }
    }
    already_around = filter(all_inventory(this_object()),
      (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) == -($(pos)) :));
    if(sizeof(already_around) > query_max_space_around(pos))
    {
      if(this_player())
      this_player()->add_failed_mess(this_object(),
        "There isn't enough room to place " + obs[0]->the_short()
        + " there.\n", ({ }));
      return 0;
    }
    pos = -(pos);
  }
  if(pos > 0)
  {
    object *already_there;
    if(member_array(args[1][1..], HANGING_VERBS) != -1)
    {
      if(is_in_corner(pos))
      {
        if(this_player())
        this_player()->add_failed_mess(this_object(),
          "You may not place $I" + args[1] + " in a "
          "corner.\n", ({ obs[0] }));
        return 0;
      }
      pos += 10;
    }
    already_there = filter(all_inventory(this_object()),
      (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) == $(pos) :));
    if((sizeof(already_there)) && (already_there[0] != obs[0]))
    {
      if(this_player())
      this_player()->add_failed_mess(this_object(),
        "$I is already"
        + already_there[0]->query_property(PLACEMENT_CURRENT_ROOM_VERB) + " "
        + already_there[0]->query_property(PLACEMENT_CURRENT_ROOM_OTHER) + " "
        + get_pos_desc(pos) + ".\n", ({ already_there[0] }));
      return 0;
    }
  }
  if(is_wall_hanging(pos))
  {
    if(member_array(args[2], HANGING_PREPOSITIONS) == -1)
    {
      string *preps;
      string extra = "";
      preps = HANGING_PREPOSITIONS;
      preps = map(preps, (: ("\"" + $1 + "\"") :));
      extra = "  You may only use " + query_multiple_short(preps) +
        " as prepositions.";
#ifdef PLAYTESTING
      extra += "  Mail suggestions for more to Gototh.";
#endif
      if(this_player())
      this_player()->add_failed_mess(this_object(),
        "You may not place $I"+ args[1] + " \"" + args[2] + "\" "
        + get_pos_desc(pos) + "." + extra + "\n", ({ obs[0] }));
      return 0;
    }
  }
  if(is_beside_wall(pos))
  {
    if(member_array(args[2], WALL_PREPOSITIONS) == -1)
    {
      string *preps;
      string extra = "";
      preps = WALL_PREPOSITIONS;
      preps = map(preps, (: ("\"" + $1 + "\"") :));
      extra = "  You may only use " + query_multiple_short(preps) +
        " as prepositions.";
#ifdef PLAYTESTING
      extra += "  Mail suggestions for more to Gototh.";
#endif
      if(this_player())
      this_player()->add_failed_mess(this_object(),
        "You may not place $I"+ args[1] + " \"" + args[2] + "\" "
        + get_pos_desc(pos) + "." + extra + "\n", ({ obs[0] }));
      return 0;
    }
  }
  if(is_in_corner(pos))
  {
    if(member_array(args[2], CORNER_PREPOSITIONS) == -1)
    {
      string *preps;
      string extra = "";
      preps = CORNER_PREPOSITIONS;
      preps = map(preps, (: ("\"" + $1 + "\"") :));
      extra = "  You may only use " + query_multiple_short(preps) +
        " as a preposition.";
#ifdef PLAYTESTING
      extra += "  Mail suggestions for more to Gototh.";
#endif
      if(this_player())
      this_player()->add_failed_mess(this_object(),
        "You may not place $I"+ args[1] + " \"" + args[2] + "\" "
        + get_pos_desc(pos) + "." + extra + "\n", ({ obs[0] }));
      return 0;
    }
  }
  if(!pos)
  {
    if(this_player())
       this_player()->add_failed_mess(this_object(),
      "You may not place $I"+ args[1] + " " + args[2] + " the \""
      + args[3] + "\".\n", ({ obs[0] }));
    return 0;
  }
  obs[0]->add_property(PLACEMENT_CURRENT_ROOM_VERB, args[1]);
  obs[0]->add_property(PLACEMENT_CURRENT_ROOM_OTHER, args[2]);
  obs[0]->add_property(PLACEMENT_CURRENT_ROOM_POSITION, pos);
  if(environment(obs[0]) != this_object())
  {
    obs[0]->move(this_object());
  }
  if(pos > 0)
  {
    if(this_player())
      this_player()->add_succeeded_mess(this_object(),
      "$N $V $I so that it is" + args[1] + " " + args[2]
      + " " + get_pos_desc(pos) + ".\n", ({ obs[0] }));
  }
  else
  {
    if(sizeof(things))
    {
      if(this_player())
        this_player()->add_succeeded_mess(this_object(),
        "$N $V $I so that it is" + args[1] + " " + args[2] +
        " " + things[0]->the_short() + ".\n", ({ obs[0] }));
    }
    else
    {
      pos = -(pos);
      if(this_player())
      this_player()->add_succeeded_mess(this_object(),
        "$N $V $I so that it is" + args[1] + " " + args[2] +
        " " + get_pos_desc(pos) + ".\n", ({ obs[0] }));
    }
  }
  event(this_object(), "save", this_object());
  furniture_long = "";
  return 1;
}
int get_pos_int(string str)
{
  string dir;
  int pos_int;
  dir = explode(str, " ")[0];
  dir = EXPAND_EXIT(dir);
  switch(dir)
  {
    case "ceiling" :
    case "floor" :
    case "centre" :
      pos_int = 1;
      break;
    case "north" :
      pos_int = 2;
      break;
    case "south" :
      pos_int = 6;
      break;
    case "east" :
      pos_int = 4;
      break;
    case "west" :
      pos_int = 8;
      break;
    case "northeast" :
      pos_int = 3;
      break;
    case "southeast" :
      pos_int = 5;
      break;
    case "southwest" :
      pos_int = 7;
      break;
    case "northwest" :
      pos_int = 9;
      break;
  }
  return pos_int;
}
int find_opposite(int pos, object *structure)
{
  int opp;
  if(pos == 1 || pos == 11)
  {
    return 0;
  }
  if((pos > 5 && pos < 10) || (pos > 11 && pos > 15))
  {
    opp = pos - 4;
  }
  else
  {
    opp = pos + 4;
  }
  return opp;
}
int find_above(int pos, object *structure)
{
  int above;
  if(pos < 10)
  {
    above = pos + 10;
  }
  return above;
}
int find_below(int pos, object *structure)
{
  int below;
  if(pos > 10)
  {
    below = pos - 10;
  }
  return below;
}
int find_left(int pos, object *structure)
{
  int left;
  if(pos == 1 || pos == 11)
  {
    return 0;
  }
  left = pos - 1;
  if(left == 1)
  {
    left = 9;
  }
  if(left == 11)
  {
    left = 19;
  }
  return left;
}
int find_right(int pos, object *structure)
{
  int right;
  if(pos == 1 || pos == 11)
  {
    return 0;
  }
  right = pos + 1;
  if(right == 10)
  {
    right = 2;
  }
  if(right == 20)
  {
    right = 12;
  }
  return right;
}
string query_furniture_ordinal(object ob)
{
  int index;
  string str_num;
  object *obs;
  str_num = "";
  obs = match_objects_for_existence(ob->query_plural(), ({ this_object() }));
  index = member_array(ob, obs);
  if((index != -1) && (sizeof(obs) != 1))
  {
    str_num = " " + word_ordinal(index + 1);
  }
  if((index != -1) && (sizeof(obs) != 1))
  {
    str_num = " " + word_ordinal(index + 1);
  }
  return str_num;
}
string object_position_desc(object thing)
{
  string verb;
  string other;
  string position;
  string str;
  verb = thing->query_property(PLACEMENT_CURRENT_ROOM_VERB);
  other = thing->query_property(PLACEMENT_CURRENT_ROOM_OTHER);
  position = get_pos_desc(thing->query_property(PLACEMENT_CURRENT_ROOM_POSITION));
  if(verb == "")
  {
    str = other + " " + position;
  }
  else
  {
    str = verb[1..] + " " + other + " " + position;
  }
  return str;
}
string describe_relative_position(int index)
{
  string relative_desc;
  switch(index)
  {
    case OPPOSITE :
      relative_desc = OPPOSITE_DESCS[random(sizeof(OPPOSITE_DESCS))];
      break;
    case ABOVE :
      relative_desc = ABOVE_DESCS[random(sizeof(ABOVE_DESCS))];
      break;
    case BELOW :
      relative_desc = BELOW_DESCS[random(sizeof(BELOW_DESCS))];
      break;
    case RIGHT :
      relative_desc = RIGHT_DESCS[random(sizeof(RIGHT_DESCS))];
      break;
    case LEFT :
      relative_desc = LEFT_DESCS[random(sizeof(LEFT_DESCS))];
      break;
  }
  return relative_desc;
}
string object_desc2(object thing)
{
  string verb;
  string other;
  string position;
  string str;
  mapping allowed_verbs;
  verb = thing->query_property(PLACEMENT_CURRENT_ROOM_VERB);
  allowed_verbs = thing->query_allowed_room_verbs();
  if (!allowed_verbs) {
     allowed_verbs = ([ ]);
  }
  verb = allowed_verbs[verb[1..]];
  if(!verb || verb == "")
  {
    verb = "is";
  }
  other = thing->query_property(PLACEMENT_CURRENT_ROOM_OTHER);
  position = get_pos_desc(thing->query_property(PLACEMENT_CURRENT_ROOM_POSITION));
  str = verb + " " + thing->a_short();
  return str;
}
string object_desc(object thing)
{
  string str;
  switch(random(2))
  {
    case 0 :
      str = object_position_desc(thing) + " is " + thing->a_short();
      break;
    default :
      str = object_position_desc(thing) + " is " + thing->a_short();
      break;
  }
  return str;
}
int *find_relative_indexes(int index, mixed structure)
{
  int *relatives;
  relatives = allocate(5);
  relatives[OPPOSITE] = find_opposite(index, structure);
  relatives[ABOVE] = find_above(index, structure);
  relatives[BELOW] = find_below(index, structure);
  relatives[RIGHT] = find_right(index, structure);
  relatives[LEFT] = find_left(index, structure);
  return relatives;
}
string desc_around_with(object ob, object *around)
{
  around -= have_described;
  if(sizeof(around) == 1)
  {
    return "$C$" + object_desc(ob) + " " +
      around[0]->query_property(PLACEMENT_CURRENT_ROOM_OTHER) +
      " which is " + query_multiple_furniture_short(around) + ".  ";
  }
  return "$C$" + object_desc(ob) + " around which are " +
    query_multiple_furniture_short(around) + ".  ";
}
string desc_around_without(object *around, object *structure,
  int location)
{
  if(location < 0)
  {
    location = -(location);
  }
  if(!structure[location])
  {
    if(sizeof(around) == 1)
    {
      return "$C$" + around[0]->query_property(PLACEMENT_CURRENT_ROOM_OTHER)
        + " " + get_pos_desc(location) + " is" +
        query_another(around[0]) + " " + around[0]->query_short() +
        ".  ";
    }
    else
    {
      return "Around " + get_pos_desc(location) +
        " are " + query_multiple_furniture_short(around) + ".  ";
    }
  }
  else
  {
    if(sizeof(around) == 1)
    {
      return "$C$" + around[0]->query_property(PLACEMENT_CURRENT_ROOM_OTHER) +
        " the" + query_furniture_ordinal(structure[location]) + " " +
        structure[location]->query_short() + " is" +
        query_another(around[0]) + " " +
        around[0]->query_short() + ".  ";
    }
    else
    {
      return "Around " + structure[location]->the_short() +
        " are " + query_multiple_furniture_short(around) + ".  ";
    }
  }
}
string trim_trailing_spaces(string str)
{
  int i;
  if(!sizeof(str))
  {
    return str;
  }
  for(i = (sizeof(str)) - 1; str[i] == ' '; i--);
  return str[0..i];
}
int choose_relative(int *relatives, object *structure) {
  int num, found;
  int *rands;
  rands = ({ 0, 1, 2, 3, 4 });
  while(sizeof(rands)) {
    num = rands[random(sizeof(rands))];
    if(objectp(structure[relatives[num]])) {
      if(member_array(structure[relatives[num]], needs_described) != -1) {
        found = 1;
        break;
      }
    }
    rands -= ({ num });
  }
  if(found)
    return num;
  return -1;
}
object *get_around(object ob) {
  object *around;
  around = filter(all_inventory(this_object()),
    (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) &&
       $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) ==
       -($(ob->query_property(PLACEMENT_CURRENT_ROOM_POSITION))) :));
  return around;
}
void set_orientation(int num)
{
  orientation = num;
}
int query_orientation()
{
  return orientation;
}
string wall_or_corner(int pos)
{
   return query_wall_name_pos(pos);
}
string desc_obs_relatively(int *indexes, object *structure)
{
  int i;
  int *relatives;
  string desc;
  object *around;
  int rel_num;
  object rel_ob;
  desc = "";
  while(sizeof(indexes)) {
    i = indexes[random(sizeof(indexes))];
    indexes -= ({ i });
    if(member_array(structure[i], needs_described) == -1) {
      continue;
    }
    needs_described -= ({ structure[i] });
    have_described += ({ structure[i] });
    relatives = find_relative_indexes(i, structure);
    rel_num = choose_relative(relatives, structure);
    if(rel_num == -1)
      rel_ob = 0;
    else
      rel_ob = structure[relatives[rel_num]];
    around = get_around(structure[i]);
    if(!rel_ob) {
      if(sizeof(around)) {
        desc += desc_around_with(structure[i], around);
        needs_described -= around;
        have_described += around;
        continue;
      } else {
        if(clutter_string(structure[i]) == "") {
          desc += "$C$" + object_desc(structure[i]) + ".  ";
        } else {
          desc += "$C$" + object_desc(structure[i]) +
            " upon which" + clutter_string(structure[i]) + ".  ";
        }
        continue;
      }
    }
    needs_described -= ({ rel_ob });
    have_described += ({ rel_ob });
    indexes -= ({ relatives[rel_num] });
    desc += "$C$" + object_desc(structure[i]) + " " +
      describe_relative_position(rel_num) + " " +
      object_desc2(rel_ob) + ".  ";
    if(clutter_string(structure[i]) != "") {
      desc += "On " + structure[i]->the_short() +
        clutter_string(structure[i]);
      if(clutter_string(rel_ob) != "") {
        desc += " while on " + rel_ob->the_short() +
          clutter_string(rel_ob) + ".  ";
      } else {
        desc += ".  ";
      }
    } else if(clutter_string(rel_ob) != "") {
      desc += "On " + rel_ob->the_short() +
        clutter_string(rel_ob) + ".  ";
    }
    if(sizeof(around)) {
      desc += desc_around_without(around, structure, i);
      needs_described -= around;
      have_described += around;
      continue;
    }
    around = get_around(rel_ob);
    if(sizeof(around)) {
      desc += desc_around_without(around, structure, relatives[rel_num]);
      needs_described -= around;
      have_described += around;
      continue;
    }
  }
  return desc;
}
int room_order(object *obs1, object *obs2, object *structure)
{
  int pos1, pos2;
  object ob1, ob2;
  int order1, order2;
  pos1 = -(obs1[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION));
  pos2 = -(obs2[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION));
  if (pos1 < 0) {
     ob1 = 0;
  } else {
     ob1 = structure[pos1];
  }
  if (pos2 < 0) {
     ob2 = 0;
  } else {
     ob2 = structure[pos2];
  }
  if(!ob1 || !ob2)
  {
    return 0;
  }
  if(ob1->query_plural() != ob2->query_plural())
  {
    return 0;
  }
  order1 = member_array(ob1, match_objects_for_existence(ob1->query_plural(),
    ({ this_object() })));
  order2 = member_array(ob2, match_objects_for_existence(ob2->query_plural(),
    ({ this_object() })));
  if(order1 > order2)
  {
    return 1;
  }
  return -1;
}
string describe_remaining_objects(object *structure)
{
  int pos;
  string desc;
  object *group;
  mixed *orphans;
  desc = "";
  if(sizeof(needs_described))
  {
    orphans = unique_array(needs_described,
      (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) :));
    if(sizeof(orphans))
    {
      orphans = sort_array(orphans, (: room_order($1, $2, $(structure)) :));
      foreach(group in orphans)
      {
        pos = group[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
        desc += desc_around_without(group, structure, pos);
        needs_described -= group;
        have_described += group;
      }
    }
  }
  return desc;
}
string get_group_verb(object *obs)
{
  mixed *verbs;
  verbs = map(obs, (: $1->query_property(PLACEMENT_CURRENT_ROOM_VERB) :));
  verbs = unique_array(verbs, (: $1 :));
  if(sizeof(verbs) == 1)
  {
    return verbs[0][0];
  }
  return "";
}
string get_group_other(object *obs)
{
  mixed *others;
  others = map(obs, (: $1->query_property(PLACEMENT_CURRENT_ROOM_OTHER) :));
  others = unique_array(others, (: $1 :));
  if(sizeof(others) == 1)
  {
    return others[0][0];
  }
  return others[random(sizeof(others))][0];
}
string describe_plural_objects(int *indexes, object *structure)
{
  int i, j;
  int flag;
  int rel_num;
  int used_pos;
  mixed *things;
  string desc = "";
  string *strs;
  strs = ({ });
  things = ({ });
  for(i = 0; i < sizeof(indexes); i++) {
    things += ({ structure[indexes[i]] });
  }
  things = unique_array(things, (: $1->query_plural() :));
  things = filter(things, (: sizeof($1) > 1 :) );
  if(sizeof(things) > 0) {
    for(i = 0; i < sizeof(things); i++) {
      needs_described -= things[i];
      have_described += things[i];
      if(sizeof(things[i]) == 4) {
        int they_are = 1;
        int *rel_nums;
        int num;
        rel_nums = map(things[i],
          (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) :));
#ifdef DEBUG
        debug_printf("rel_nums: %O", rel_nums);
#endif
        foreach(num in rel_nums)
          if(is_in_corner(num))
            they_are = 0;
        if(they_are) {
          desc += "$C$" + things[i][0]->query_plural() + " are" +
            get_group_verb(things[i]) + " " +
            get_group_other(things[i]) + " each " +
            wall_or_corner(rel_nums[0]) + ".  ";
#ifdef DEBUG
          debug_printf("4 corner: %s\n", desc);
#endif
          continue;
        }
        they_are = 1;
        foreach(num in rel_nums)
        {
          if(is_beside_wall(num))
          {
            they_are = 0;
          }
        }
        if(they_are)
        {
          desc += "$C$" + things[i][0]->query_plural() + " are" +
            get_group_verb(things[i]) + " " +
            get_group_other(things[i]) + " each " +
            wall_or_corner(3) + ".  ";
          continue;
        }
      }
      if(sizeof(things[i]) == 3)
      {
        int *rel_nums;
        rel_nums = map(things[i],
          (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) :));
        rel_nums = sort_array(rel_nums, 1);
        if(rel_nums[2] == 9)
        {
          rel_nums -= ({ 9 });
          rel_nums = ({ 1 }) + rel_nums;
        }
        if(is_beside_wall(rel_nums[1]) &&
          rel_nums[0] == rel_nums[1] - 1 &&
          rel_nums[2] == rel_nums[1] + 1)
        {
          desc += "$C$" + query_multiple_short(things[i]) +
            " are" + get_group_verb(things[i]) + " beside each other " +
            structure[rel_nums[1]]->query_property(PLACEMENT_CURRENT_ROOM_OTHER)
            + " the " + get_pos_desc(rel_nums[1]) + ".  ";
          continue;
        }
      }
      if(sizeof(things[i]) == 2)
      {
        rel_num = member_array(get_structure_index(things[i][1]),
          find_relative_indexes(get_structure_index(things[i][0]),
          structure));
        if(rel_num != -1)
        {
          desc += "$C$" + query_multiple_short(things[i]);
          switch(rel_num)
          {
            case OPPOSITE :
              desc += " face each other across the room.  ";
              continue;
              break;
            case RIGHT :
            case LEFT :
              desc += " are" + get_group_verb(things[i]) +
                " beside each other ";
              break;
            default :
              break;
          }
          if(!orientation)
          {
            if(get_structure_index(things[i][0]) & 1)
            {
              used_pos =
                things[i][1]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
            }
            else
            {
              used_pos =
                things[i][0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
            }
          }
          else
          {
            if(get_structure_index(things[i][0]) & 1)
            {
              used_pos =
                things[i][0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
            }
            else
            {
              used_pos =
                things[i][1]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
            }
          }
          desc +=
            structure[used_pos]->query_property(PLACEMENT_CURRENT_ROOM_OTHER) +
            " the " + get_pos_desc(used_pos) + ".  ";
          continue;
        }
      }
      desc += "$C$" + query_num(sizeof(things[i]), 4) + " "
        + things[i][0]->query_plural() + " are positioned "
        "around the room.  ";
#ifdef DEBUG
      debug_printf("2 items: %s\n", desc);
#endif
      if(sizeof(things[i]) > 4)
      {
        flag = 1;
      }
      else
      {
        desc += "They are ";
      }
      for(j = 0; j < sizeof(things[i]); j++)
      {
        if(!flag)
        {
          strs += ({ object_position_desc(things[i][j]) });
        }
        indexes -=
          ({ things[i][j]->query_property(PLACEMENT_CURRENT_ROOM_POSITION) });
      }
      if(!flag)
      {
        desc += query_multiple_short(strs)+".  ";
#ifdef DEBUG
        debug_printf("position: %s [%s]\n",
                     query_multiple_short(strs), desc);
#endif
        strs = ({ });
      }
    }
  }
  return desc;
}
string furniture_long()
{
  string desc, d1, d2, d3;
  object *structure;
  int i, *indexes;
  if(furniture_long != "") {
    return furniture_long;
  }
  structure = build_structure();
  indexes = ({ });
  for(i = 0; i < sizeof(structure); i++)
  {
    if(objectp(structure[i]))
    {
      indexes += ({ i });
    }
  }
  needs_described = filter(all_inventory(this_object()),
    (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) :));
  have_described = ({ });
  d1 = describe_plural_objects(indexes, structure);
  d2 = desc_obs_relatively(indexes, structure);
  d3 = describe_remaining_objects(structure);
#ifdef DEBUG
  debug_printf("1: %s\n2:%s\n3:%s\n",d1, d2, d3);
#endif
  desc = d1 + d2 + d3;
  if(desc == "")
    desc = "$C$" + this_object()->the_short() + "$C$" + " is completely empty.";
  furniture_long = trim_trailing_spaces(desc);
  return furniture_long;
}
string get_pos_desc(int pos_int)
{
  string str;
  switch(pos_int)
  {
    case 1 :
      str = "the centre of " + this_object()->the_short();
      break;
    case 2 :
    case 12 :
      str = "the north " + wall_or_corner(pos_int);
      break;
    case 3 :
    case 13 :
      str = "the northeast " + wall_or_corner(pos_int);
      break;
    case 4 :
    case 14 :
      str = "the east " + wall_or_corner(pos_int);
      break;
    case 5 :
    case 15 :
      str = "the southeast " + wall_or_corner(pos_int);
      break;
    case 6 :
    case 16 :
      str = "the south " + wall_or_corner(pos_int);
      break;
    case 7 :
    case 17 :
      str = "the southwest " + wall_or_corner(pos_int);
      break;
    case 8 :
    case 18 :
      str = "the west " + wall_or_corner(pos_int);
      break;
    case 9 :
    case 19 :
      str = "the northwest " + wall_or_corner(pos_int);
      break;
    case 11 :
      str = "the centre of the ceiling";
      break;
  }
  return str;
}
object *build_structure()
{
  int i;
  object *positions, *obs, *dummies;
  positions = allocate(20);
  obs = all_inventory(this_object());
  for(i = 1; i < sizeof(positions); i++)
  {
    dummies = filter(obs,
      (: $1->query_property(PLACEMENT_CURRENT_ROOM_POSITION) == $(i) :));
    if(sizeof(dummies))
    {
      positions[i] = dummies[0];
    }
  }
  return positions;
}
int get_structure_index(object ob)
{
  return member_array(ob, build_structure());
}
string desc_surface(string dir)
{
  int i;
  int pos;
  int *indexes;
  int current_pos;
  string desc;
  object *structure;
  object *around;
  structure = build_structure();
  needs_described = ({ });
  have_described = ({ });
  if(dir == "ceiling")
  {
    pos = 11;
  }
  else
  {
    pos = get_pos_int(dir);
  }
  desc = "";
  indexes = ({ });
  for(i = 1; i < sizeof(structure); i++)
  {
    if(!objectp(structure[i]))
    {
      continue;
    }
    current_pos = structure[i]->query_property(PLACEMENT_CURRENT_ROOM_POSITION);
    if(current_pos != pos)
    {
      if(pos != 1 && pos != 11)
      {
        if((current_pos != pos + 10) && (current_pos != pos - 10))
        {
          structure[i] = 0;
        }
        else
        {
          needs_described += ({ structure[i] });
          indexes += ({ i });
        }
      }
    }
    else
    {
      needs_described += ({ structure[i] });
      around = get_around(structure[i]);
      if(around)
      {
        needs_described += around;
      }
      indexes += ({ i });
    }
  }
  desc += desc_obs_relatively(indexes, structure);
  return desc;
}
void displace_object(object ob)
{
  if (ob->query_property(PLACEMENT_CURRENT_ROOM_POSITION)) {
    ob->remove_property(PLACEMENT_CURRENT_ROOM_VERB);
    ob->remove_property(PLACEMENT_CURRENT_ROOM_OTHER);
    ob->remove_property(PLACEMENT_CURRENT_ROOM_POSITION);
    furniture_long = "";
  }
}
int do_displace(object *obs)
{
  if(this_player() &&
     !this_object()->test_occupier(this_player()->query_name()) &&
     !this_player()->query_creator()) {
    this_player()->add_failed_mess(this_object(),
                                   "You don't own this house.\n");
    return 0;
  }
  if(sizeof(obs) > 1)
  {
    this_player()->add_succeeded_mess(this_object(),
      "You may only displace one thing at a time.\n", ({ }));
    return 1;
  }
  if(!obs[0]->query_property(PLACEMENT_CURRENT_ROOM_POSITION))
  {
    this_player()->add_failed_mess(this_object(),
      "$C$" + obs[0]->the_short() + " is not placed.\n", ({ }));
    return 0;
  }
  if(obs[0]->query_property(PLACEMENT_IMMOVABLE)) {
    this_player()->add_failed_mess(this_object(),
                                   "Try as you might you cannot move $I.\n",
                                   ({ obs[0] }));
    return 0;
  }
  displace_object(obs[0]);
  this_player()->add_succeeded_mess(this_object(),
    "$N drag$s " + obs[0]->a_short() + " out of position.\n", ({ }));
  furniture_long = "";
  return 1;
}
void event_exit(object ob, string, object)
{
  displace_object(ob);
}
int test_remove(object thing, int flag, mixed dest) {
  if(thing->query_property(PLACEMENT_IMMOVABLE))
    return 0;
  if(thing->query_property(PLACEMENT_CURRENT_ROOM_HIDDEN))
    thing->removed();
  return 1;
}