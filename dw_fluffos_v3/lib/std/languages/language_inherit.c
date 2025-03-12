#include <fixed_random.h>
#include <tasks.h>
#include <living.h>
private string _long;
private string _name;
private string _start_text_bit;
void setup();
void create() {
  setup();
}
void set_long(string str) {
   _long = str;
}
string query_long() {
   return _long;
}
void set_name(string str) {
   _name = str;
}
string query_name() {
   return _name;
}
void setup() {
}
void set_start_text_bit(string str) {_start_text_bit = str; }
string do_garble(string word, string type) {
  string ret;
  int i;
  ret = "";
  for (i=0;i<strlen(word);i++)
    if (word[i] != ' ')
      ret += "*";
    else
      ret += " ";
  return ret;
}
void check_level_increase(object player, int difficulty, int level,
                          string skill, string mess) {
   int chance;
   if(query_verb() == "shout" || player->query_property("dead") ||
      player->query_property(PASSED_OUT) ||
      (userp(player) && !interactive(player)))
     return;
   if(player->query_current_language() !=
      lower_case(this_object()->query_name()))
     return;
   if (player->query_property("last message:" + skill) == mess ||
       player->query_property("dead")) {
      return ;
   }
   if(player->query_specific_gp("other") < difficulty) {
     return;
   } else {
     player->adjust_gp(-(difficulty*2));
   }
   player->add_property("last message:" + skill, mess, 360);
   if (difficulty <= level && level < 100) {
        chance = 800 + ((level - 40) * (level - 40)) / 20;
      chance -= level - difficulty;
      if (random(1000) > chance) {
        if(player->add_skill_level(skill, 1)) {
          tell_object(player, "%^YELLOW%^You feel like the " +
                      capitalize(_name) +
                      " language is less confusing.%^RESET%^\n");
        }
      }
   }
}
string garble_message(string mess, object player, object speaker,
                      string type, string skill, int no_increase) {
  int i, level, num;
  int max_difficulty, diff, difference;
  string *bits;
  int something_garbled;
  level = player->query_skill(skill);
  if (level > 100) {
    player->add_skill_level(skill, 100 - level, 1);
  }
  num = speaker->query_skill(skill);
  if (num > 100) {
    speaker->add_skill_level(skill, 100 - num, 1);
  }
  difference = speaker->query_skill(skill) - player->query_skill(skill);
  if (num < level)
    level = num;
  if (level >= 100) {
    return mess;
  }
  if (level == 0) {
    max_difficulty = 0;
  } else {
    max_difficulty = 1000;
  }
  RANDOM_OBJ->set_seed(crc32(mess));
  bits = explode(mess, " ");
  for (i=0;i<sizeof(bits);i++) {
    if (strlen(mess)) {
      if (level > 0) {
         num = (int)RANDOM_OBJ->random(100);
         if (strlen(mess) < 8) {
           diff = (level*100) / (strlen(mess)*10);
           if (num >= (level*100 / strlen(mess)*10)) {
             if (max_difficulty > diff)
               max_difficulty = diff;
             if (interactive(player)) {
               bits[i] = do_garble(bits[i], type);
               something_garbled = 1;
             } else {
               bits[i] = "";
             }
           }
         } else {
           diff = (level*100) / 90;
           if (num >= diff) {
             max_difficulty = level*100 / 100;
             if (interactive(player)) {
               bits[i] = do_garble(bits[i], type);
               something_garbled = 1;
             } else {
               bits[i] = "";
             }
           }
         }
      } else {
         if (interactive(player)) {
           bits[i] = do_garble(bits[i], type);
           something_garbled = 1;
         } else {
           bits[i] = "";
         }
      }
    }
  }
  if (something_garbled && (difference > -10) && !no_increase) {
    check_level_increase(player, max_difficulty, level, skill, mess);
  }
  return implode(bits, " ");
}
mixed garble_say(string start, string mess, object player,
                 object from, string type, string skill, int no_increase) {
  return ({ start, garble_message(mess, player, from, "speech", skill,
                                  no_increase) });
}
string garble_text( mixed text, object thing, object player, string skill) {
  string bing;
  if (stringp(text)) {
    if (player->query_default_language() != query_name()) {
      return _start_text_bit +
        garble_message(text, player, player, "text", skill, 0);
    } else {
      return garble_message(text, player, player, "text", skill, 0);
    }
  }
  if ( pointerp( text ) ) {
    if ( ( bing = (string)text[ 0 ]->garble_text( text, thing, player ) ) ) {
      if (player->query_default_language() != query_name()) {
        return _start_text_bit + bing;
      } else {
        return bing;
      }
    }
  }
  return "You cannot read the spidery writing.\n";
}
void dest_me() {
  destruct(this_object());
}