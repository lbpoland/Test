#include <bits_controller.h>
#include <drinks.h>
#include <weapon.h>
#include <move_failures.h>
#include <playtesters.h>
inherit "/obj/cont_medium";
inherit "/std/basic/virtual_update";
#define DEFAULT_DECAY 7200
#define STATE_CHANGE ("/obj/handlers/state_change")
private int _liquid;
private int _dried, _cured;
private int _bites_gone;
private int _weight_per_bite;
private int _in_pieces;
private int _decay_level;
private int _decay_speed;
private int _splashable;
private int _applicable;
private int _external_pk_check;
private float _divisor = to_float(DEFAULT_DECAY) / to_float(6 * TIME_OUT);
private mixed _eat_mess;
private string _eat_object;
private string _eat_func;
private string _piece_desc;
private string _piece_short;
private string _piece_plural;
private string _piece_substance;
private mixed _eat_piece_mess;
private mixed _eat_amt_mess;
private mixed _eat_last_mess;
private mapping _eat_effects = ([ ]);
private mapping _external_effects = ([ ]);
varargs int do_cut(int num);
varargs int do_eat(int no_mess);
int do_mince();
void set_decay_speed(int decay);
int check_for_container();
void create()
{
   do_setup++;
   ::create();
   do_setup--;
   reset_continuous();
   _eat_effects = ([ ]);
   set_decay_speed(DEFAULT_DECAY);
   add_help_file("food");
   if (!do_setup) {
      this_object()->setup();
   }
}
int query_liquid()
{
   return _liquid;
}
int query_edible()
{
   return !_liquid;
}
void set_liquid()
{
   set_continuous();
   _liquid = 1;
   if (environment()) {
      environment()->calc_liquid();
   }
   set_decay_speed(0);
}
void reset_liquid()
{
   reset_continuous();
   _liquid = 0;
   if (environment())
      environment()->calc_liquid();
   set_decay_speed(DEFAULT_DECAY);
   _divisor = to_float(DEFAULT_DECAY) / to_float(6 * TIME_OUT);
}
int query_food_object()
{
   return 1;
}
void init()
{
   if (query_continuous()) {
      add_command("rub", "<direct:object> <preposition> <indirect:living>");
      add_command("apply", "<direct:object> <preposition> <indirect:living>");
   }
   if (_liquid) {
      add_command("drink", "<direct:object>");
      add_command("quaff", "<direct:object>");
      add_command("splash",
                  "<direct:object> <preposition> <indirect:living>");
   } else {
      add_command("eat", "<direct:object>", (: do_eat(0) :));
      add_command("cut",
                  "<direct:object> into <number'number, eg: 3'> pieces",
                  (: do_cut($4[1]) :));
      add_command("cut", "<direct:object>", (: do_cut() :));
      add_command("slice", "<direct:object>", (: do_cut() :));
      add_command("mince", "<direct:object>", (: do_mince() :));
   }
}
int query_decays()
{
   return _decay_speed != 0;
}
int query_bites_gone()
{
   return _bites_gone;
}
int query_weight_per_bite()
{
   return _weight_per_bite;
}
string query_eat_object()
{
   return _eat_object;
}
string query_eat_func()
{
   return _eat_func;
}
string query_eat_mess()
{
   return _eat_mess;
}
string query_piece_description()
{
   return _piece_desc;
}
int query_in_pieces()
{
   return _in_pieces;
}
int query_decay_speed()
{
   return _decay_speed;
}
int query_decay_level() {
   return _decay_level;
}
void set_bites_gone(int number)
{
   _bites_gone = number;
}
void set_weight_per_bite(int number)
{
   _weight_per_bite = number;
}
void set_eat_object(string word)
{
   _eat_object = word;
}
void set_eat_func(string word)
{
   _eat_func = word;
}
void set_eat_mess(mixed word)
{
   _eat_mess = word;
}
void setup_eat_piece_messages(mixed piece,
                              mixed amt,
                              mixed last) {
   _eat_piece_mess = piece;
   _eat_amt_mess = amt;
   _eat_last_mess = last;
}
void set_piece_description(string word) {
   _piece_desc = word;
}
void set_piece_short(string short) {
   _piece_short = short;
}
void set_piece_plural(string plural) {
   _piece_plural = plural;
}
void set_piece_substance(string substance) {
   _piece_substance = substance;
}
void set_in_pieces(int number) {
   int p;
   _in_pieces = p;
}
void set_decay_level(int level) {
   _decay_level = level;
}
void set_decay_speed(int decay) {
   float tmp;
   if(decay != _decay_speed && !_dried && !_cured) {
      BITS_CONTROLLER->remove_bit(this_object());
      _decay_speed = decay;
      if (decay && !_dried && !_cured) {
         tmp = _divisor;
         _divisor = to_float(decay) / to_float(6 * TIME_OUT);
         _decay_level = to_int(_decay_level * _divisor / tmp);
         BITS_CONTROLLER->add_bit(this_object());
      }
   }
}
void do_decay() {
  if(_dried || _cured) {
    BITS_CONTROLLER->remove_bit(this_object());
    return;
  }
  if ( environment() && environment()->query_property( "no decay" ) )
    return;
  _decay_level++;
  if (_decay_level > (2 * _divisor) -1 ) {
    remove_adjective( "fresh" );
  }
  if (_decay_level > 6 * _divisor) {
    tell_room(environment(this_object()),
              capitalize(the_short()) + " crumbles to dust.\n");
    move("/room/rubbish");
  }
}
int query_weight() {
  if (query_liquid())
    return 0;
  return ::query_weight() - _bites_gone * _weight_per_bite;
}
string query_short_rotten_adjective() {
    string ret;
    ret = "";
    switch (to_int(_decay_level / _divisor)) {
    case 2:
      ret = "slightly rotten ";
      break;
    case 3:
      ret = "half rotten ";
      break;
    case 4:
      ret = "mostly rotten ";
      break;
    case 5:
      ret = "almost rotten ";
      break;
    case 6:
      ret = "rotten ";
      break;
    }
    return ret;
}
string short(int dark) {
  string ret;
  ret = ::short(dark);
  if (_decay_speed) {
     ret = query_short_rotten_adjective() + ret;
  }
  return ret;
}
string query_long_eat_level() {
   int twelfths;
   string ret;
    twelfths = (_bites_gone * _weight_per_bite * 12) / ::query_weight();
    switch (twelfths) {
        case 0..1:
            ret = "It has just been nibbled on.\n";
        break;
        case 2:
            ret = "It is about one sixth gone.\n";
        break;
        case 3:
            ret = "It is about one quarter gone.\n";
        break;
        case 4:
            ret = "It is about one third gone.\n";
        break;
        case 5:
            ret = "It is just under half gone.\n";
        break;
        case 6:
            ret = "It is about half gone.\n";
        break;
        case 7:
            ret = "It is just over half gone.\n";
        break;
        case 8:
            ret = "It is about two thirds gone.\n";
        break;
        case 9:
            ret = "It is about three quarters gone.\n";
        break;
        case 10:
            ret = "It is about five sixths gone.\n";
        break;
        case 11:
            ret = "It is almost all gone.\n";
        break;
        default:
            ret = "Schroedinger's cat has been at it.\n";
        break;
    }
    return ret;
}
string query_long_decay_level() {
    string ret;
    ret = "";
    switch (to_int(_decay_level / _divisor)) {
    case 0..1:
      if(query_collective() && query_amount() > 1)
        ret += "They look nice and fresh.\n";
      else
       ret += "It looks nice and fresh.\n";
      break;
    case 2:
      if(query_collective() && query_amount() > 1)
        ret += "They look a bit rotten.\n";
      else
        ret += "It looks a bit rotten.\n";
      break;
    case 3:
      if(query_collective() && query_amount() > 1)
        ret += "They are half rotten.\n";
      else
        ret += "It is half rotten.\n";
      break;
    case 4:
      if(query_collective() && query_amount() > 1)
        ret += "They are mostly rotten.\n";
      else
        ret += "It is mostly rotten.\n";
      break;
    case 5:
      if(query_collective() && query_amount() > 1)
        ret += "They are almost completely rotten.\n";
      else
        ret += "It is almost completely rotten.\n";
       break;
    case 6:
      if(query_collective() && query_amount() > 1)
        ret += "They are completely rotten.\n";
      else
        ret += "It is completely rotten.\n";
      break;
    }
    return ret;
}
string long(string words, int dark) {
   string ret;
   ret =::long(words, dark);
   if (_liquid) {
      return ret;
   }
   if (_weight_per_bite && _bites_gone) {
       ret += query_long_eat_level();
   }
   if (_decay_speed) {
       ret += query_long_decay_level();
   }
   else {
       if(_dried) {
           if(query_collective() && query_amount() > 1) {
              ret += "They are all dry and shrivelled up.\n";
           }
           else {
              ret += "It is all dry and shrivelled up.\n";
           }
        }
        else {
            if(_cured) {
                if(query_collective() && query_amount() > 1) {
                    ret += "They seem to have been pickled.\n";
                }
                else {
                    ret += "It seems to have been pickled.\n";
                }
            }
        }
   }
   return ret;
}
void setup_eat(string ob, string func) {
   _eat_object = ob;
   _eat_func = func;
}
mapping query_eat_effects() {
   if (undefinedp(_eat_effects)) {
      _eat_effects = ([ ]);
   }
   return copy( _eat_effects );
}
void set_eat_effects(mapping map) {
   if (mapp(map)) {
      _eat_effects = map;
   }
}
int add_eat_effect(mixed word,
                   int number)
{
   if (undefinedp(_eat_effects)) {
      _eat_effects = ([ ]);
   }
   if (mapp(word)) {
      int num;
      string name;
      foreach(name, number in word) {
         num += add_eat_effect(name, number);
      }
      return num;
   }
   if (_eat_effects[word]) {
      _eat_effects[word] += number;
   } else {
      _eat_effects[word] = number;
   }
   return _eat_effects[word];
}
void remove_eat_effect(string word)
{
   if (!undefinedp(_eat_effects[word])) {
      _eat_effects = m_delete(_eat_effects, word);
   }
}
void set_external_pk_check()
{
   _external_pk_check = 1;
}
void unset_external_pk_check()
{
   _external_pk_check = 0;
}
mapping query_external_effects()
{
   if (undefinedp(_external_effects))
      _external_effects = ([ ]);
   return _external_effects + ([ ]);
}
void set_external_effects(mapping map)
{
   _external_effects = map;
}
int add_external_effect(string word,
                        int number)
{
   if (undefinedp(_external_effects))
      _external_effects = ([ ]);
   if (_external_effects[word])
      _external_effects[word] += number;
   else
      _external_effects[word] = number;
   return _external_effects[word];
}
void remove_external_effect(string word)
{
   if (!undefinedp(_external_effects[word])) {
      _external_effects = m_delete(_external_effects, word);
   }
}
void set_splashable()
{
   _splashable = 1;
}
void unset_splashable()
{
   _splashable = 0;
}
int query_splashable(object splasher,
                     object splashee)
{
   if (splasher == splashee || !_external_pk_check) {
      return (_splashable && _liquid);
   }
   return (_splashable && _liquid && !(pk_check(splasher, splashee)));
}
void set_applicable()
{
   _applicable = 1;
}
void unset_applicable()
{
   _applicable = 0;
}
int query_applicable(object applier,
                     object appliee)
{
   if (applier == appliee || !_external_pk_check) {
      return _applicable;
   }
   return (_applicable && !(pk_check(applier, appliee)));
}
void being_joined_by(object thing)
{
   int i,
     that,
     this;
   string *words;
   mapping new_effects;
   that = (int) thing->query_amount();
   this = query_amount();
   if (!(this + that))
      return;
   if (thing->query_splashable(0, 0) && !_splashable)
      set_splashable();
   if (thing->query_applicable(0, 0) && !_applicable)
      set_applicable();
   if (thing->query_external_pk_check() && !_external_pk_check)
      set_external_pk_check();
   new_effects = (mapping) thing->query_eat_effects();
   words = m_indices(_eat_effects);
   for (i = 0; i < sizeof(words); i++) {
      if (new_effects[words[i]]) {
         new_effects[words[i]] *= that;
         new_effects[words[i]] += this * _eat_effects[words[i]];
      } else {
         new_effects[words[i]] = this * _eat_effects[words[i]];
      }
   }
   words = m_indices(new_effects);
   for (i = 0; i < sizeof(words); i++) {
      new_effects[words[i]] /= this + that;
   }
   _eat_effects = new_effects;
   new_effects = (mapping) thing->query_external_effects();
   words = m_indices(_external_effects);
   for (i = 0; i < sizeof(words); i++) {
      if (_external_effects[words[i]]) {
         new_effects[words[i]] *= that;
         new_effects[words[i]] += this * _external_effects[words[i]];
      } else {
         new_effects[words[i]] = this * _external_effects[words[i]];
      }
   }
   words = m_indices(new_effects);
   for (i = 0; i < sizeof(words); i++) {
      new_effects[words[i]] /= this + that;
   }
   _external_effects = new_effects;
}
varargs void consume(object consumer, int amount, string type) {
  int i, denominator, numerator, wholes;
  string *words;
  switch (type) {
  case "splash":
  case "apply":
  case "external":
    words = m_indices(_external_effects);
    break;
  default:
    words = m_indices(_eat_effects);
    break;
  }
  if (!amount && query_continuous()) {
    amount = query_amount();
  }
  if (amount) {
    if (query_continuous() && (amount > query_amount()))
      amount = query_amount();
    numerator = amount * query_weight_unit()[0];
    denominator = query_weight_unit()[1];
    if (type != "apply" && type != "splash" && type != "external") {
      if (_liquid) {
        consumer->adjust_volume(D_DRINK, (50 * numerator) / denominator);
      } else {
        consumer->adjust_volume(D_FOOD, (50 * numerator) / denominator);
      }
    }
    if (!this_object()->query_property("playtester") ||
        PLAYTESTER_HAND->query_playtester(consumer->query_name()) ||
        consumer->query_creator()) {
      for (i = 0; i < sizeof(words); i++) {
        switch (type) {
        case "splash":
        case "apply":
        case "external":
          numerator = _external_effects[words[i]] * amount *
            query_weight_unit()[0];
          break;
        default:
          numerator = _eat_effects[words[i]] * amount *
            query_weight_unit()[0];
          break;
        }
        wholes = numerator / denominator;
        numerator %= denominator;
        if (random(denominator) < numerator) {
          wholes++;
        }
        consumer->add_effect(words[i], wholes);
      }
    }
    adjust_amount(-amount);
  } else {
    if (_weight_per_bite) {
      _bites_gone++;
      if (type != "apply" && type != "splash" && type != "external") {
        consumer->adjust_volume(D_FOOD, 50 * _weight_per_bite);
      }
      if (!this_object()->query_property("playtester") ||
          PLAYTESTER_HAND->query_playtester(consumer->query_name()) ||
          consumer->query_creator()) {
        for (i = 0; i < sizeof(words); i++) {
          switch (type) {
          case "splash":
          case "apply":
          case "external":
            this_player()->add_effect(words[i],
                                      _external_effects[words[i]] *
                                      _weight_per_bite);
            break;
          default:
            this_player()->add_effect(words[i], _eat_effects[words[i]] *
                                      _weight_per_bite);
            break;
          }
        }
      }
    } else {
      consumer->adjust_volume(D_FOOD, 50 * weight);
      if (!this_object()->query_property("playtester") ||
          PLAYTESTER_HAND->query_playtester(consumer->query_name()) ||
          consumer->query_creator()) {
        for (i = 0; i < sizeof(words); i++) {
          switch (type) {
          case "apply":
          case "splash":
          case "external":
            consumer->add_effect(words[i],
                                 _external_effects[words[i]] * weight);
            break;
          default:
            consumer->add_effect(words[i],
                                 _eat_effects[words[i]] * weight);
            break;
          }
        }
      }
    }
  }
  if (type != "apply" && type != "splash" && type != "external") {
    if (_eat_func) {
      if (_eat_object) {
        call_other(_eat_object, _eat_func, this_object(), consumer);
      } else {
        call_other(this_object(), _eat_func, this_object(), consumer);
      }
    }
  }
}
varargs int do_eat(int no_mess) {
   int ret;
   if ((weight <= 0) && !query_continuous()) {
      if (_eat_mess && !no_mess) {
         add_succeeded_mess(_eat_mess, ({ }));
      }
      move("/room/rubbish");
      return 1;
   }
   if ((weight <= (_bites_gone + 1) * _weight_per_bite) || !_weight_per_bite) {
      if (!no_mess) {
         if (!query_continuous()) {
            if (_weight_per_bite) {
               if (_eat_last_mess) {
                  add_succeeded_mess(_eat_last_mess, ({ }));
               } else {
                  add_succeeded_mess("$N $V the last of $D.\n", ({ }));
               }
            } else if (_eat_mess) {
               add_succeeded_mess(_eat_mess, ({ }));
            }
         } else {
            if (_eat_amt_mess) {
               add_succeeded_mess(replace_string(_eat_amt_mess, "$amt$",
                                                 amount_size() ), ({ }));
            } else {
               add_succeeded_mess("$N $V " + amount_size() + " of $D.\n",
                                  ({ }));
            }
         }
      }
      ret = 2;
      move("/room/rubbish");
   } else {
      if (!no_mess) {
         if (_eat_piece_mess) {
            add_succeeded_mess(_eat_piece_mess, ({ }));
         } else {
            add_succeeded_mess("$N $V a piece of $D.\n", ({ }));
         }
      }
      ret = 1;
   }
   consume(this_player(), 0);
   return ret;
}
int check_sharp(object weapon)
{
   mixed *data;
   int i;
   if (!weapon) {
      return 0;
   }
   data = weapon->query_attack_data();
   for (i = W_TYPE; i < sizeof(data); i += W_ARRAY_SIZE) {
      if (data[i] == "sharp") {
         return 1;
      }
   }
   return 0;
}
varargs int do_cut(int num_pieces) {
  object bing, *obs, with;
  string name, *exploded_short;
  int i, j, k, size_of_each, gone;
  int portion_of_whole;
  int portion_of_parent;
  string temp_short, temp_plural;
  mixed rabbit;
  if (query_liquid()) {
    add_failed_mess("You cannot $V $D.\n");
    return -1;
  }
  obs = this_player()->query_holding();
  for (i = 0; i < sizeof(obs); i++) {
    if (check_sharp(obs[i])) {
      if (!with || (with && with->query_weight() > obs[i]->query_weight())) {
        with = obs[i];
      }
    }
  }
  if (!with) {
    add_failed_mess("You have to be holding a sharp object to $V $D.\n");
    return -1;
  }
  if (undefinedp(num_pieces))
    num_pieces = 2;
  if (query_continuous())
    return (do_mince());
  if (num_pieces <= 1 || !_weight_per_bite) {
    add_failed_mess("$D cannot be cut up.\n");
    return -1;
  } else if (num_pieces >
             ((query_weight() / _weight_per_bite) - _bites_gone)) {
    if (num_pieces == 2 || ((query_weight() / _weight_per_bite) -
                            _bites_gone) < 2) {
      add_failed_mess("$D cannot be cut up.\n");
    } else
      add_failed_mess("You can't $V $D into that many pieces.\n");
    return -1;
  }
  name = file_name(this_object());
  sscanf(name, "%s#%*d", name);
  size_of_each = (query_weight() - _weight_per_bite * _bites_gone) /
    num_pieces;
  gone = (::query_weight() - size_of_each) / _weight_per_bite;
  for (i = 0; i < num_pieces; i++) {
    bing = clone_object(name);
    bing->init_static_arg(query_static_auto_load());
    bing->init_dynamic_arg(query_dynamic_auto_load());
    bing->set_weight(size_of_each);
    bing->set_value(0);
    bing->add_property("whole:weight", query_property("whole:weight")
                       || query_weight());
    bing->add_property("whole:short", query_property("whole:short")
                       || this_player()->convert_message(a_short()));
    portion_of_whole = bing->query_property("whole:weight") / size_of_each;
    portion_of_parent = query_weight() / size_of_each;
    if (!_in_pieces) {
      if (_piece_desc) {
        bing->set_long(_piece_desc);
        if (!_in_pieces) {
          if (!_piece_short) {
            if (portion_of_whole == 1)
              temp_short = "piece";
            else if (portion_of_whole == 2)
              temp_short = "half";
            else if (portion_of_whole == 4)
              temp_short = "quarter";
            else
              temp_short = word_ordinal(portion_of_whole);
          }
          if (!_piece_plural) {
            if (_piece_short)
              _piece_plural = _piece_short + "s";
            else {
              if (temp_short == "half")
                temp_plural = "halves";
              else
                temp_plural = temp_short + "s";
            }
          }
          if (_piece_substance)
            rabbit = _piece_substance;
          else
            rabbit = bing->query_property("whole:short");
          bing->set_short((_piece_short || temp_short) +
                          " of " + rabbit);
          bing->set_main_plural((_piece_plural || temp_plural) +
                                " of " + rabbit);
        }
      }
    } else {
      bing->set_bites_gone(gone);
    }
    bing->add_alias(_piece_short || temp_short);
    bing->add_plural(_piece_plural || temp_plural);
    exploded_short = explode(bing->query_short(), " ");
    j = sizeof(exploded_short);
    bing->set_name(exploded_short[j - 1]);
    for (k = 0; k < sizeof(exploded_short) - 1; k++) {
      bing->add_adjective(exploded_short[k]);
    }
    bing->set_in_pieces(1);
    if (bing->move(environment((this_object())))!= MOVE_OK ) {
      bing->move(environment(this_player()));
    }
  }
  move("/room/rubbish");
  if (with->query_weight() < 20) {
    add_succeeded_mess(({ sprintf("$N $V $D into %s pieces with %s%s.\n",
                                  query_num(num_pieces), with->poss_short(),
                                  (num_pieces * size_of_each) <
                                  query_weight()?
                                  ", carelessly dribbling a bit while you do "
                                  "so" : ""),
                            sprintf("$N $V $D into %s pieces with %s.\n",
                                    query_num(num_pieces),
                                    with->poss_short()) }));
  } else {
    add_succeeded_mess(({sprintf("$N stand back and hack $D into %s pieces "
                                 "with %s%s.\n", query_num(num_pieces),
                                 with->poss_short(),
                                 (num_pieces * size_of_each) < query_weight()?
                                 ", carelessly obliterating a bit when you do "
                                 "so" : ""),
                           sprintf("$N stands back and hacks $D into %s "
                                   "pieces with %s.\n",
                                   query_num(num_pieces),
                                   with->poss_short()) }));
  }
  return 1;
}
varargs int do_mince()
{
   object *obs,
     with,
     transformed;
   int i,
     rem_pieces;
   if (query_liquid()) {
      add_failed_mess("You cannot $V $D.\n");
      return -1;
   }
   obs = this_player()->query_holding();
   for (i = 0; i < sizeof(obs); i++) {
      if (check_sharp(obs[i])) {
         if (!with || (with && with->query_weight() > obs[i]->query_weight())) {
            with = obs[i];
         }
      }
   }
   if (!with) {
      add_failed_mess("You have to be holding a sharp object to $V " "$D.\n");
      return -1;
   }
   transformed = STATE_CHANGE->transform(this_object(), "slice");
   if (!objectp(transformed)) {
      if (query_continuous()) {
         add_failed_mess("$D cannot be cut up any further.\n");
         return -1;
      }
      if (_weight_per_bite) {
         rem_pieces = (query_weight() / _weight_per_bite) - _bites_gone;
         return (do_cut(rem_pieces));
      }
      return -1;
   }
   this_object()->move("/room/rubbish");
   if (transformed->move(this_player()) != MOVE_OK) {
      call_out("tell_object", 0, this_player(), "You drop " +
               transformed->the_short() + ".\n");
      call_out("tell_room", 0, environment(this_player()),
               this_player()->the_short() + " drops " +
               transformed->the_short() + ".\n");
      transformed->move(environment(this_player()));
   }
   add_succeeded_mess("$N $V $D with " + with->the_short() +
                      " into $I.\n", ({ transformed }));
   return 1;
}
int do_drink()
{
   if (!check_for_container()) {
      add_failed_mess("You go to try and $V $D, but it suddenly "
                      "remembers what happens when it is not in a "
                      "container and drains away to dust.\n");
      move("/room/rubbish");
      return 0;
   }
   this_player()->add_succeeded_mess(this_object(), "$N $V " +
                                     amount_size() + " of $D.\n", ({ }));
   consume(this_player(), 0);
   return 1;
}
int do_quaff()
{
   if (!check_for_container()) {
      add_failed_mess("You go to try and $V $D, but it suddenly "
                      "remembers what happens when it is not in a "
                      "container and drains away to dust.\n");
      move("/room/rubbish");
      return 0;
   }
   this_player()->add_succeeded_mess(this_object(), "$N $V " +
                                     amount_size() +
                                     " of $D spilling most of "
                                     "it of course.\n", ({ }));
   consume(this_player(), query_amount() * 6 / 10, "splash");
   consume(this_player(), query_amount() * 4 / 10);
   return 1;
}
int do_apply(object * things)
{
   if (sizeof(things) > 1) {
      add_failed_mess("You must $V $D to one person alone.\n", ({ }));
      return 0;
   }
   if (!_applicable) {
      add_failed_mess("You cannot $V $D to anybody.\n");
      return 0;
   }
   if (_external_pk_check && pk_check(this_player(), things[0])) {
      add_failed_mess("You feel it would be wrong to rub $D on $I.\n",
                      things);
      return 0;
   }
   this_player()->add_succeeded_mess(this_object(), "$N $V " +
                                     amount_size() + " of $D to $I.\n",
                                     ({ things[0] }));
   consume(things[0], 0, "apply");
   return 1;
}
int do_rub(object * things)
{
   if (sizeof(things) > 1) {
      add_failed_mess("You must $V $D on one person alone.\n", ({ }));
      return 0;
   }
   if (!_applicable) {
      add_failed_mess("You cannot $V $D on anybody.\n");
      return 0;
   }
   if (_external_pk_check && pk_check(this_player(), things[0])) {
      add_failed_mess("You feel it would be wrong to rub $D on $I.\n",
                      things);
      return 0;
   }
   this_player()->add_succeeded_mess(this_object(), "$N $V " +
                                     amount_size() + " of $D on $I.\n",
                                     ({ things[0] }));
   consume(things[0], 0, "apply");
   return 1;
}
int do_splash(object * things)
{
   if (sizeof(things) > 1) {
      add_failed_mess("You must $V $D on one person alone.\n", ({ }));
      return 0;
   }
   if (!_splashable || !_liquid) {
      add_failed_mess("You cannot $V $D on anybody.\n", ({ }));
      return 0;
   }
   if (_external_pk_check && pk_check(this_player(), things[0])) {
      add_failed_mess("You feel it would be wrong to splash $D on $I.\n",
                      things);
      return 0;
   }
   this_player()->add_succeeded_mess(this_object(), "$N $V " +
                                     amount_size() + " of $D on $I.\n",
                                     ({ things[0] }));
   consume(things[0], 0, "splash");
   return 1;
}
mapping int_query_static_auto_load() {
   return ([ "::" : ::int_query_static_auto_load(),
             "liquid" : _liquid,
             "weight_per_bite" : _weight_per_bite,
             "eat_object" : _eat_object,
             "eat_func" : _eat_func,
             "eat_mess" : _eat_mess,
             "splashable" : _splashable,
             "applicable" : _applicable,
             "external_pk_check" : _external_pk_check ]);
}
mapping query_static_auto_load()
{
   if ((explode(file_name(this_object()), "#")[0] != "/obj/food")
       && !query_continuous()) {
      return 0;
   }
   return int_query_static_auto_load();
}
void init_static_arg(mapping map)
{
   if (!mapp(map)) {
      return;
   }
   if (map["::"]) {
      ::init_static_arg(map["::"]);
   }
   _liquid = map["liquid"];
   _weight_per_bite = map["weight_per_bite"];
   _eat_object = map["eat_object"];
   _eat_func = map["eat_func"];
   _eat_mess = map["eat_mess"];
   _splashable = map["splashable"];
   _applicable = map["applicable"];
   _external_pk_check = map["external_pk_check"];
}
mapping query_dynamic_auto_load()
{
   return ([ "::" : ::query_dynamic_auto_load(),
             "bites_gone" : _bites_gone,
             "eat_effects" : _eat_effects,
             "external_effects" : _external_effects,
             "in pieces" : _in_pieces,
             "piece desc" : _piece_desc,
             "piece short" : _piece_short,
             "piece plural" : _piece_plural,
             "piece substance" : _piece_substance,
             "decay speed" : _decay_speed,
             "decay level" : _decay_level,
             "dried" : _dried,
             "cured" : _cured,
             "divisor" : _divisor, ]);
}
void init_dynamic_arg(mapping map, object)
{
   if (!mapp(map)) {
      return;
   }
   if (map["::"]) {
      ::init_dynamic_arg(map["::"]);
   }
   _bites_gone = map["bites_gone"];
   if (undefinedp(_eat_effects)) {
      _eat_effects = ([ ]);
   } else {
      if (mapp(map["eat_effects"])) {
         _eat_effects = map["eat_effects"];
      }
   }
   if (undefinedp(_external_effects)) {
      _external_effects = ([ ]);
   } else {
      _external_effects = map["external_effects"];
   }
   _in_pieces = map["in pieces"];
   _piece_desc = map["piece desc"];
   _piece_short = map["piece short"];
   _piece_plural = map["piece plural"];
   _piece_substance = map["piece substance"];
   if (_in_pieces && _piece_desc) {
      set_long(_piece_desc);
   }
   set_decay_speed(map["decay speed"]);
   _decay_level = map["decay level"];
   _divisor = map["divisor"];
   _dried = map["dried"];
   _cured = map["cured"];
   init_virtual_object();
}
mixed *stats()
{
   int i;
   string *words;
   mixed *args;
   args =::stats() + ({ ({ "liquid", _liquid }),
                        ({ "bites gone", _bites_gone }),
                        ({ "weight per bite", _weight_per_bite }),
                        ({ "eat object", _eat_object }),
                        ({ "eat function", _eat_func }),
                        ({ "eat message", _eat_mess }),
                        ({ "in pieces", _in_pieces }),
                        ({ "decay speed", _decay_speed }),
                        ({ "decay level", _decay_level }),
                        ({ "dried", _dried }),
                        ({ "cured", _cured }) });
   words = m_indices(_eat_effects);
   for (i = 0; i < sizeof(words); i++) {
      args += ({ ({ "eat effect#" + i, words[i] + " (" +
                    _eat_effects[words[i]] + ")" }) });
   }
   args += ({ ({ "applicable", _applicable }) });
   args += ({ ({ "splashable", _splashable }) });
   if (_splashable && !_liquid) {
      args += ({ ({ "***not splashable***", "because not a liquid" }) });
   }
   args += ({ ({ "external_pk_check", _external_pk_check }) });
   if (_external_effects) {
      words = keys(_external_effects);
      for (i = 0; i < sizeof(words); i++) {
         args += ({ ({ "external effect#" + i, words[i] + " (" +
                       _external_effects[words[i]] + ")" }) });
      }
   }
   return args;
}
int check_for_container()
{
   if (query_liquid()) {
      if (!environment()->query_max_volume() || living(environment())) {
         return 0;
      }
   }
   return 1;
}
private void move_check_for_container()
{
   if (!check_for_container()) {
      tell_room(environment(),
                the_short() + " dribbles all over the place and disappears "
                "into the dust.\n");
      if(move("/room/rubbish") != MOVE_OK) {
        debug_printf("Oops, failed to move us to the rubbish room.\n");
      }
   }
}
varargs int move(mixed dest, string mess1, string mess2) {
   int ret;
   ret =::move(dest, mess1, mess2);
   if (ret == MOVE_OK && dest != "/room/rubbish" && query_liquid()) {
      move_check_for_container();
   }
   return ret;
}
int query_rotten() {
    if ( _divisor ) {
        return to_int( _decay_level / _divisor ) > 1;
    }
    return 0;
}
string *query_adjectives() {
  if( query_rotten() ) {
    return ::query_adjectives() + ({ "rotten" });
  }
  return ::query_adjectives();
}
float query_decay_divisor() { return _divisor; }
int do_cure() {
  if(_dried || _liquid || _cured)
    return 0;
  _decay_speed = 0;
  _decay_level = 0;
  BITS_CONTROLLER->remove_bit(this_object());
  set_main_plural( "cured " + query_plural() );
  set_short( "cured " + query_short());
  add_adjective("cured");
  remove_adjective("fresh");
  _cured = 1;
  if( query_collective() ) {
    merge();
  }
  return 1;
}
int query_cured() { return _cured; }
int do_dry() {
  int new_weight;
  if(_dried || _liquid || _cured)
    return 0;
  _decay_speed = 0;
  _decay_level = 0;
  BITS_CONTROLLER->remove_bit( this_object() );
  set_main_plural("dried " + query_plural(0));
  set_short( "dried " + query_short());
  add_adjective("dried");
  remove_adjective("fresh");
  new_weight = ::query_weight() / 10;
  if ( new_weight ) {
    set_weight( new_weight );
  }
  else {
    set_weight( 1 );
  }
  if( query_collective() ) {
    merge();
  }
  _dried = 1;
  return 1;
}
int query_dried() { return _dried; }
int merge_criteria(object ob) {
  return ::merge_criteria(ob) &&
    _decay_speed == ob->query_decay_speed() &&
    _bites_gone == ob->query_bites_gone() &&
    ((to_int(_decay_level / _divisor) < 2 &&
     to_int(ob->query_decay_level() / ob->query_decay_divisor()) < 2) ||
     to_int(_decay_level / _divisor) ==
     to_int(ob->query_decay_level() / ob->query_decay_divisor()));
}