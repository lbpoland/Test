#include <armoury.h>
#include <position.h>
#include <room.h>
#include <tasks.h>
#define ANCHOR_PROP "anchor"
#define GILLS_PROP "gills"
#define FLOATING_PROP "floating"
#define LIVES_IN_WATER_PROP "lives in water"
#define SWIMMING_SKILL "other.movement.swimming"
#define OBJECT_WET_EFFECT "/std/effects/object/wet"
#define LIVING_WET_EFFECT "/std/effects/other/wetness"
#define SWIM_EFFECT "/std/effects/other/water_effect"
mixed query_property(string);
varargs mixed *query_dest_other(string);
varargs int add_property(string, mixed, int);
int modify_exit(mixed, mixed*);
string query_destination(string);
string *query_exits();
int set_water_light(int);
int query_my_light();
varargs string *query_dest_dir(object);
int lives_in_water( object ob );
varargs void soak(object, int);
object get_water();
int water_override(string);
int do_float();
int do_drift();
int do_swim();
int get_swim_enum(object);
int query_bottom();
int query_surface();
string get_exit_mess(object, string);
string get_enter_mess(object, string);
object query_above_room();
void update_water_light();
private string on_bottom = "lying on the bottom",
        non_float = "drifting nearby",
        floating = "floating nearby",
        sinking = "sinking nearby",
        s_in_mess = "$N sink$s $down$ from $F.",
        s_out_mess = "$N sink$s $down$.",
        f_in_mess = "$N float$s $up$ from $F.",
        f_out_mess = "$N float$s $up$.",
        c_in_mess = "$N $V$0=is,are$V$ swept in from $F by the current.",
        c_out_mess = "$N $V$0=is,are$V$ swept $T by the current.",
        up_dir = "up", down_dir = "down";
private int bottom = -1, surface = -1, clarity = 90, salinity = 0,
        turbulence = 100, update_light = 1, light_first_queried = 0,
        last_speech_volume = 0;
private mapping flows = ([ ]), exit_messes = ([ ]), enter_messes = ([ ]),
        origins = ([ ]);
string* query_default_search_description() {
   return ({
       "Funnily enough there is nothing interesting in the water.\n",
       "You search around and discover a whole bunch of water.\n",
       "You look up and down, left and right, then up and down again but "
       "all you can find is water.\n"
           });
}
mixed *query_default_position(object ob) {
  return ({SWIMMING, "%^BOLD%^You start to swim.%^RESET%^\n",
           "$C$"+ob->one_short()+" "
           "$V$0=starts,start$V$ to swim.\n"});
}
int is_allowed_position(string poss) {
  if (poss == SWIMMING) {
    return 1;
  }
  return 0;
}
void set_bottom_mess(string mess) {
  on_bottom = mess;
}
string query_bottom_mess() {
  return on_bottom;
}
void set_nonfloat_mess(string mess) {
   non_float = mess;
}
string query_nonfloat_mess() {
  return non_float;
}
void set_float_mess(string mess) {
  floating = mess;
}
string query_float_mess() {
  return floating;
}
void set_sinking_mess(string mess) {
  sinking = mess;
}
string query_sinking_mess() {
  return sinking;
}
void set_sink_in_mess(string mess) {
  s_in_mess = mess;
}
string query_sink_in_mess() {
  return replace(s_in_mess, ({"$down$", down_dir}));
}
void set_sink_out_mess(string mess) {
  s_out_mess = mess;
}
string query_sink_out_mess() {
  return replace(s_out_mess, ({"$down$", down_dir}));;
}
void set_float_in_mess(string mess) {
  f_in_mess = mess;
}
string query_float_in_mess() {
  return replace(f_in_mess, ({"$up$", up_dir}));
}
void set_float_out_mess(string mess) {
  f_out_mess = mess;
}
string query_float_out_mess() {
  return replace(f_out_mess, ({"$up$", up_dir}));
}
void set_sweep_in_mess(string mess) {
  c_in_mess = mess;
}
string query_sweep_in_mess() {
  return c_in_mess;
}
void set_sweep_out_mess(string mess) {
  c_out_mess = mess;
}
string query_sweep_out_mess() {
  return c_out_mess;
}
void set_up_dir(string dir) {
  up_dir = dir;
}
string query_up_dir() {
  return up_dir;
}
void set_down_dir(string dir) {
  down_dir = dir;
}
string query_down_dir() {
  return down_dir;
}
void set_bottom(int val) {
  bottom = val;
  if (bottom > 1 || bottom < -1) {
    bottom = 1;
  }
}
void set_surface(int val) {
  surface = val;
  if (surface > 1 || surface < -1) {
    surface = 1;
  }
}
void set_clarity(int how_clear) {
  clarity = how_clear;
  if (clarity > 100) {
    clarity = 100;
  }
  else if (clarity < 0) {
    clarity = 0;
  }
  if (!query_property("dark mess")) {
    if (clarity < 20) {
      add_property("dark mess", "The water here is very murky.");
    }
    else if (clarity < 50) {
      add_property("dark mess", "The water here is quite murky.");
    }
    else if (clarity < 80) {
      add_property("dark mess", "The water here is slightly murky.");
    }
  }
}
int query_clarity() {
  return clarity;
}
void set_turbidity(int how_murky) {
  set_clarity(100 - how_murky);
}
int query_turbidity() {
  return 100 - query_clarity();
}
void set_salinity(int how_salty) {
  salinity = how_salty;
  if (salinity > 100) {
    salinity = 100;
  }
  else if (salinity < 0) {
    salinity = 0;
  }
}
int query_salinity() {
  return salinity;
}
void set_turbulence(int how_turbulent) {
  turbulence = how_turbulent;
  if (turbulence < 0) {
    turbulence = 0;
  }
}
int query_turbulence() {
  return turbulence;
}
void set_use_surface_light(int val) {
  int surface_light;
  object above;
  update_light = 0;
  if (!val) {
    return;
  }
  above = query_above_room();
  if (!above) {
    set_water_light(0);
    return;
  }
  if (function_exists("query_day_light", above) ||
           above->water_surface_light_varies()) {
    update_light = 1;
    return;
  }
  if (function_exists("query_water_surface_light", above)) {
    surface_light = above->query_water_surface_light();
  }
  else {
    surface_light = above->query_my_light();
  }
  set_water_light(surface_light);
}
int query_water_surface_light() {
  update_water_light();
  return query_my_light()*query_clarity()/100;
}
int get_water_surface_light() {
  object above = query_above_room();
  if (!above) {
    return 0;
  }
  if (function_exists("query_water_surface_light", above)) {
    return above->query_water_surface_light();
  }
  return above->query_my_light();
}
void update_water_light() {
  if (!update_light) {
    return;
  }
  if (!light_first_queried) {
    set_use_surface_light(1);
    light_first_queried = 1;
    update_water_light();
    return;
  }
  set_water_light(get_water_surface_light());
}
void add_flow(string dir, int rate) {
  flows[dir] = rate;
}
void delete_flow(string dir) {
  map_delete(flows, dir);
}
mapping query_flows() {
  return copy(flows);
}
int query_flow(string dir) {
  return flows[dir];
}
int query_water_traction_bonus(object thing, int buoyancy) {
  if (buoyancy < 0) {
    buoyancy = -buoyancy;
    return buoyancy/3 + random(buoyancy/3);
  }
  return 0;
}
object query_above_room() {
  string destination = query_destination(up_dir);
  if (!destination) {
    return 0;
  }
  return load_object(destination);
}
object query_below_room() {
  string destination = query_destination(down_dir);
  if (!destination) {
    return 0;
  }
  return load_object(destination);
}
object query_surface_room() {
  object next;
  if (query_surface()) {
    return this_object();
  }
  next = query_above_room();
  if (next && next->query_water()) {
    return next->query_surface_room();
  }
  return 0;
}
object query_bottom_room() {
  object next;
  if (query_bottom()) {
    return this_object();
  }
  next = query_below_room();
  if (next && next->query_water()) {
    return next->query_bottom_room();
  }
  return 0;
}
void event_enter(object ob, string mess, object from)  {
  int effnum, buoyancy, *effects, *args;
  effects = ob->effects_matching(SWIM_EFFECT->query_classification());
  if (!effects || !sizeof(effects)) {
    if (from && !from->query_water() ) {
      if( !lives_in_water( ob ) )
        ob->add_effect(SWIM_EFFECT, 2);
    }
  }
  if ( !lives_in_water( ob ) ) {
      effnum = get_swim_enum(ob);
      args = ob->arg_of(effnum);
      if (living(ob) && query_surface() && !ob->query_property("dead") && from &&
               from->query_water() && !from->query_surface()) {
        if (args[1] < 150 || ob->query_property(GILLS_PROP)) {
          tell_object(ob, "You break the surface.\n");
        }
        else {
          tell_object(ob, "You break the surface and take a deep breath.\n");
        }
        if (args[1] != 0) {
          ob->set_arg_of(effnum, ({args[0], 0}));
        }
      }
  }
  if (!living(ob)) {
    buoyancy = SWIM_EFFECT->calc_buoyancy(ob);
    if (buoyancy < 0 && query_bottom()) {
      ob->add_property("there", on_bottom);
    }
    else if (buoyancy >= 0 && (buoyancy > ob->query_property(ANCHOR_PROP)
           || query_surface())) {
      ob->add_property("there", floating);
    }
    else if (buoyancy < 0 && buoyancy < -ob->query_property(ANCHOR_PROP)) {
      ob->add_property("there", sinking);
    }
    else {
      ob->add_property("there", non_float);
    }
  } else {
    ob->return_to_default_position();
  }
}
varargs void soak(object ob, int ignore_location) {
  int wetness = 0, *effects;
  object env, water, *things;
  env = ob;
  if (!ignore_location) {
    while (env && env = environment(env)) {
      if (env == this_object()) {
        break;
      }
      if ((env->query_closed() && env->query_waterproof()) ||
           env->query_dry_cargo()) {
        env = 0;
        break;
      }
    }
  }
  if (!env) {
    return;
  }
  if (ob->query_property(FLOATING_PROP) && query_surface()) {
    return;
  }
  if (living(ob)) {
    if (ob->query_property("dead") || lives_in_water( ob ) ) {
      return;
    }
    effects = ob->effects_matching(LIVING_WET_EFFECT->query_classification());
    if (effects && sizeof(effects)) {
      wetness = ob->arg_of(effects[0]);
    }
    wetness = ob->query_weight() - wetness;
    if (wetness > 0) {
      ob->add_effect(LIVING_WET_EFFECT, wetness);
    }
  }
  else if (ob->id("towel")) {
    effects = ob->effects_matching(OBJECT_WET_EFFECT->query_classification());
    if (effects && sizeof(effects)) {
      wetness = ob->arg_of(effects[0]);
    }
    wetness = 200*ob->query_weight() - wetness;
    if (wetness > 0) {
      ob->add_effect(OBJECT_WET_EFFECT, wetness);
    }
  }
  if (ob->query_max_volume() && !ob->query_closed() &&
           ob->query_max_volume() - ob->query_volume() > 0) {
    water = get_water();
    water->set_amount(ob->query_max_volume() - ob->query_volume());
    water->move(ob);
  }
  if (!(ob->query_closed() && ob->query_waterproof()) &&
           !ob->query_dry_cargo()) {
    things = all_inventory(ob);
    if (things && sizeof(things)) {
      map(things, (: soak($1, 1) :));
    }
  }
}
object get_water() {
  object water = ARMOURY->request_item("water");
  switch (query_clarity()) {
  case 0..20:
    water->set_short("very muddy water");
    water->add_adjective(({"very", "muddy"}));
    water->set_long("This is $amount_size$ of very muddy water.\n");
    return water;
  case 21..50:
    water->set_short("muddy water");
    water->add_adjective("muddy");
    water->set_long("This is $amount_size$ of muddy water.\n");
    return water;
  case 51..80:
    water->set_short("slightly muddy water");
    water->add_adjective(({"slightly", "muddy"}));
    water->set_long("This is $amount_size$ of slightly muddy water.\n");
  }
  switch (query_salinity()) {
  case 51..100:
    water->set_short("brine");
    water->add_alias("brine");
    water->set_long("This is $amount_size$ of very salty water.\n");
    return water;
  case 11..50:
    water->set_short("salty water");
    water->add_adjective("salty");
    water->set_long("This is $amount_size$ of salty water.\n");
  }
  return water;
}
int swim_exit(string dir, object ob, string mess) {
  int difficulty, buoyancy = 0, place, this_turb, gp_cost, effnum, *arg;
  string *places_to_go, *tm_messes;
  object destination;
  if (!living(ob) || ob->query_property("dead") || lives_in_water( ob ) ) {
    return 1;
  }
  effnum = get_swim_enum(ob);
  arg = ob->arg_of(effnum);
  if (-2 == arg[0]) {
    return 1;
  }
  difficulty = -flows[dir];
  buoyancy = SWIM_EFFECT->calc_buoyancy(ob);
  if (ob->query_weight()) {
    buoyancy /= ob->query_weight();
  }
  places_to_go = query_dest_dir();
  place = member_array(dir, places_to_go);
  if (-1 == place || !(destination = load_object(places_to_go[place+1]))) {
    return 0;
  }
  if (dir == up_dir) {
    difficulty -= buoyancy + 50;
  } else if (dir == down_dir) {
    difficulty += buoyancy - 50;
  } else if (buoyancy < 0) {
    difficulty -= buoyancy/5;
  } else {
    difficulty += buoyancy/5;
  }
  if (query_bottom() && (!destination->query_water() ||
           destination->query_bottom())) {
    difficulty -= query_water_traction_bonus(ob, buoyancy);
  }
  this_turb = random(query_turbulence());
  difficulty += this_turb;
  if (arg[0] == -1) {
    difficulty -= 50;
  }
  if (!destination->query_water()) {
    difficulty -= 50;
  }
  difficulty *= SWIM_EFFECT->swim_difficulty(ob);
  difficulty /= 100;
  if (difficulty <= 0) {
    return 1;
  }
  if (arg[0] != -1) {
    gp_cost = difficulty/20;
    if (gp_cost > 50) {
      gp_cost = 50;
    }
    else if (gp_cost < 1) {
      gp_cost = 1;
    }
    if (ob->query_specific_gp("other") < gp_cost) {
      tell_object(ob, "You're too "+({"fatigued", "tired", "weary",
           "exhausted"})[random(4)]+" to swim "+dir+" at the moment.\n");
      notify_fail("");
      return 0;
    }
  }
  ob->adjust_gp(-gp_cost);
  switch (TASKER->perform_task(ob, SWIMMING_SKILL, difficulty,
           TM_CONTINUOUS)) {
  case AWARD:
    tm_messes = ({"You move more surely as you glide through the water.",
                  "You discover a more efficient stroke.",
                  "You find a better way to streamline your body.",
                  "You find a more efficient swimming rhythm.",
                  "You begin to move more confidently through the water."});
    tell_object(ob, "%^YELLOW%^"+tm_messes[random(sizeof(tm_messes))]+
           "%^RESET%^\n");
  case SUCCEED:
    return 1;
  }
  notify_fail("");
  if (dir == up_dir && buoyancy < -50) {
    tell_object(ob, "You struggle to leave "+up_dir+" but, with the load "
           "you're carrying, you can't make any headway.\n");
    tell_room(this_object(), "$C$"+ob->one_short()+" "
           "$V$0=struggles,struggle$V$ to leave "+up_dir+", but can't make "
           "any headway.\n", ob);
    return 0;
  }
  if (dir == down_dir && buoyancy > 50) {
    tell_object(ob, "You struggle to leave "+down_dir+" but, with your "
           "buoyancy, you can't make any headway.\n");
    tell_room(this_object(), "$C$"+ob->one_short()+" "
           "$V$0=struggles,struggle$V$ to leave "+down_dir+", but can't make "
           "any headway.\n", ob);
    return 0;
  }
  if (flows[dir] < 0) {
    tell_object(ob, "You struggle to leave "+dir+", but you can't make any "
           "headway against the current.\n");
    tell_room(this_object(), "$C$"+ob->one_short()+" "
           "$V$0=struggles,struggle$V$ to leave "+dir+", but can't make any "
           "headway against the current.\n", ob);
    return 0;
  }
  if (this_turb > 0) {
    tell_object(ob, "You struggle to leave "+dir+", but you can't make any "
           "headway in the turbulent waters.\n");
    tell_room(this_object(), "$C$"+ob->one_short()+" "
           "$V$0=struggles,struggle$V$ to leave "+dir+", but can't make any "
           "headway.\n", ob);
    return 0;
  }
  tell_object(ob, "You struggle to leave "+dir+", but you can't make any "
           "headway.\n");
  tell_room(this_object(), "$C$"+ob->one_short()+" $V$0=struggles,struggle$V$ "
           "to leave "+dir+", but can't make any headway.\n", ob);
  return 0;
}
string query_death_reason() {
  return "drowning";
}
int add_exit(string direc, mixed dest, string type) {
    mixed *messy = query_dest_other(direc);
    if (messy && arrayp(messy[ROOM_ENTER]) && sizeof(messy[ROOM_ENTER]) == 2){
        origins[direc] = messy[ROOM_ENTER][1];
    }
    modify_exit(direc, ({"function", "swim_exit",
                       "exit mess", (: get_exit_mess($1, $(direc)) :),
                       "enter mess", (: get_enter_mess($1, $(direc)) :)}));
    if( direc == "down" ) {
        add_property("no burial", 1);
    }
}
string query_origin(string dir) {
  if (origins[dir]) {
    return origins[dir];
  }
  return "elsewhere";
}
void add_exit_mess(object ob, string mess) {
  exit_messes[file_name(ob)] = mess;
}
void add_enter_mess(object ob, string mess) {
  enter_messes[file_name(ob)] = mess;
}
string get_exit_mess(object ob, string direc) {
  string retval;
  if (retval = exit_messes[file_name(ob)]) {
    map_delete(exit_messes, file_name(ob));
    return retval;
  }
  return "$N $V$0=swims,swim$V$ $T.";
}
string get_enter_mess(object ob, string direc) {
  string retval;
  if (retval = enter_messes[file_name(ob)]) {
    map_delete(enter_messes, file_name(ob));
  }
  else if (direc == up_dir) {
    retval = "$N $V$0=swims,swim$V$ up from $F.";
  }
  else if (direc == down_dir) {
    retval = "$N $V$0=swims,swim$V$ down from $F.";
  }
  else {
    retval = "$N $V$0=swims,swim$V$ in from $F.";
  }
  retval = replace(retval, "$F", query_origin(direc));
  return retval;
}
void init()  {
  add_command("float", "", (: do_float() :));
  add_command("drift", "", (: do_drift() :));
  add_command("swim", "", (: do_swim() :));
}
string mangle_speech(string type, string words, mixed target) {
  int drown;
  string garbled = "";
  if (query_surface() || !this_player() ||
           this_player()->query_property("dead")) {
    return words;
  }
  switch (type) {
  case "whisper":
    drown = 20 + random(20);
    break;
  case "lsay":
  case "mock":
    drown = 80 + random(80);
    break;
  case "shout":
    drown = 120 + random(120);
    break;
  default:
    drown = 40 + random(40);
  }
  for (int inc = (strlen(words) / 10) + 1;inc > 0;--inc) {
    garbled += ({"blub", "glub", "gloog", "arrrble"})[random(4)]+" ... ";
  }
  if (drown > 70) {
    garbled = garbled[0..(strlen(garbled) - 6)]+"!";
  } else {
    garbled = garbled[0..(strlen(garbled) - 2)];
  }
  garbled = capitalize(garbled);
  last_speech_volume = drown;
  return garbled;
}
void event_person_say(object ob, string start, string mess, string lang,
           string accent) {
  int effnum, *args;
  if (!ob || ob->query_property("dead") || ob->query_property(GILLS_PROP) ||
      lives_in_water( ob ) || environment(ob) != this_object() || query_surface()) {
    last_speech_volume = 0;
    return;
  }
  if (!last_speech_volume) {
    last_speech_volume = 40 + random(40);
  }
  effnum = get_swim_enum(ob);
  args = ob->arg_of(effnum);
  args[1] += last_speech_volume;
  ob->set_arg_of(effnum, args);
  ob->adjust_tmp_con(-random((last_speech_volume / 50) + 1));
  switch (last_speech_volume) {
  case 0..30:
    tell_object(ob, "You inhale a bit of water.\n");
    break;
  case 31..80:
    tell_object(ob, "You inhale some water.\n");
    break;
  case 81..150:
    tell_object(ob, "You inhale a fair amount of water.\n");
    break;
  default:
    tell_object(ob, "You inhale about a lungful of water.\n");
  }
  last_speech_volume = 0;
}
int do_float()  {
  int *args, effnum = get_swim_enum(this_player());
  args = this_player()->arg_of(effnum);
  if (!args[0]) {
    if (sizeof(filter(query_flows(), (: $2 :)))) {
      add_failed_mess("You are already floating on the current.\n");
    }
    else {
      add_failed_mess("You are already floating freely.\n");
    }
    return 0;
  }
  this_player()->set_arg_of(effnum, ({0, args[1]}));
  if (sizeof(filter(query_flows(), (: $2 :)))) {
    add_succeeded_mess(({"You begin to float freely on the current.\n", ""}));
  }
  else {
    add_succeeded_mess(({"You begin to float freely.\n", ""}));
  }
  return 1;
}
int do_drift()  {
  int *args, effnum = get_swim_enum(this_player());
  args = this_player()->arg_of(effnum);
  if (!args[0]) {
    if (sizeof(filter(query_flows(), (: $2 :)))) {
      add_failed_mess("You are already drifting with the current.\n");
    }
    else {
      add_failed_mess("You are already drifting freely.\n");
    }
    return 0;
  }
  this_player()->set_arg_of(effnum, ({0, args[1]}));
  if (sizeof(filter(query_flows(), (: $2 :)))) {
    add_succeeded_mess(({"You begin to drift freely with the current.\n",
           ""}));
  }
  else {
    add_succeeded_mess(({"You begin to drift freely.\n", ""}));
  }
  return 1;
}
int do_swim()  {
  int *args, effnum = get_swim_enum(this_player());
  args = this_player()->arg_of(effnum);
  if (args[0]) {
    if (sizeof(filter(query_flows(), (: $2 :)))) {
      add_failed_mess("You are already swimming against the current.\n");
    }
    else {
      add_failed_mess("You are already swimming.\n");
    }
    return 0;
  }
  this_player()->set_arg_of(effnum, ({1, args[1]}));
  if (sizeof(filter(query_flows(), (: $2 :)))) {
    add_succeeded_mess(({"You begin to swim against the current.\n", ""}));
  }
  else {
    add_succeeded_mess(({"You begin to swim.\n", ""}));
  }
  return 1;
}
int get_swim_enum(object thing) {
  int *effects = thing->effects_matching(SWIM_EFFECT->query_classification());
  if (!effects || !sizeof(effects)) {
    thing->add_effect(SWIM_EFFECT, 1);
    effects = thing->effects_matching(SWIM_EFFECT->query_classification());
    call_out("soak", 1, thing);
  } else if (!random(50)) {
    call_out("soak", 1, thing);
  }
  return effects[0];
}
int query_bottom()  {
  if (bottom == -1) {
    return member_array(down_dir, query_exits()) == -1;
  }
  return bottom;
}
int query_surface() {
    if (surface == -1) {
        return member_array(up_dir, query_exits()) == -1;
    }
    return surface;
}
int query_underwater() {
  return !query_surface();
}
int query_water()  {
  return 1;
}
int lives_in_water( object ob ) {
  string race_ob = ob->query_race_ob();
  if ( !living( ob ) ) {
    return 0;
  }
  if(ob->query_property(LIVES_IN_WATER_PROP) ||
     ob->lives_in_water() ||
     (race_ob && race_ob->lives_in_water()))
    return 1;
  return 0;
}
string query_terrain_map_colour() { return "%^CYAN%^"; }