#include <skills.h>
#include <language.h>
#define SKILL_BONUS 0
private mapping _stat_bonus;
private mixed *_skills;
private mapping _reg_skills;
private mapping _skill_tree;
private mapping _immediate_children;
private mapping _only_leaf;
private mapping _not_allowed_to_teach;
private mapping _only_show_if_non_zero;
private mapping _no_bonus;
private mapping _ignore_bits;
private mapping flatten(mixed *arr, string bit);
mixed *add_skill_rec(mixed *skill, string *path);
mixed *del_skill_rec(mixed *skill, string *path);
int query_skill_cost_int(string str);
void create() {
  string *languages, *lang_tree;
  int i;
  mixed *rabbit;
  string skill_written;
  string skill_spoken;
  string *skill_bits;
  _skills = STD_SKILLS;
  _skill_tree = ([ ]);
  _immediate_children = ([ ]);
  _not_allowed_to_teach = ([ ]);
  _only_show_if_non_zero = ([ ]);
  _no_bonus = ([ ]);
  lang_tree = ({ });
  languages = LANGUAGE_HAND->query_languages();
  for (i=0;i<sizeof(languages);i++) {
     rabbit = ({ });
     if (LANGUAGE_HAND->query_language_spoken(languages[i])) {
        rabbit += ({ SPOKEN_SKILL, 0, 0, ({ }), });
     }
     if (LANGUAGE_HAND->query_language_written(languages[i]) ||
         LANGUAGE_HAND->query_language_magic(languages[i])) {
        rabbit += ({ WRITTEN_SKILL, 0, 0, ({ }) });
     }
     skill_written = LANGUAGE_HAND->query_language_written_skill(languages[i]);
     skill_spoken = LANGUAGE_HAND->query_language_spoken_skill(languages[i]);
     languages[i] = replace(languages[i], " ", "_");
     lang_tree += ({ languages[i], 0, 0, rabbit });
     _not_allowed_to_teach[LANGUAGE_SKILL_START + languages[i]] = 1;
     _not_allowed_to_teach[skill_spoken] = 1;
     _not_allowed_to_teach[skill_written] = 1;
     _only_show_if_non_zero[skill_spoken] = 1;
     _only_show_if_non_zero[skill_written] = 1;
     _no_bonus[skill_spoken] = 1;
     _no_bonus[skill_written] = 1;
  }
  skill_bits = explode(LANGUAGE_SKILL_START, ".");
  _not_allowed_to_teach["other.language"] = 1;
  i = member_array(skill_bits[0], _skills);
  if (i != -1) {
     _skills[i+SKILL_BIT] += ({ skill_bits[1], 0, 0, lang_tree });
  }
  _only_leaf = ([ "other" : 1 ]);
  _ignore_bits = ([ "crafts" : 1 ]);
  _reg_skills = flatten( _skills, "" );
  _stat_bonus = ([
"covert"                            : ({ "DDDII" }),
  "covert.stealth"                  : ({ "DDDIS" }),
  "covert.hiding"                   : ({ "DDIIS" }),
  "covert.lockpick"                 : ({ "DDDDI" }),
  "covert.manipulation"             : ({ "DDISS" }),
  "covert.casing"                   : ({ "DIIWW" }),
  "covert.items"                    : ({ "DIIII" }),
  "covert.points"                   : ({ "DDIIC" }),
"crafts"                            : ({ "DDIIW" }),
  "crafts.smithing"                 : ({ "DDIIS" }),
  "crafts.mining"                   : ({ "DIISS" }),
  "crafts.hunting"                  : ({ "DDIII" }),
  "crafts.carpentry"                : ({ "DDIIS" }),
  "crafts.pottery"                  : ({ "DDDII" }),
  "crafts.materials"                : ({ "DDIIS" }),
  "crafts.husbandry"                : ({ "IIIWW" }),
  "crafts.culinary"                 : ({ "DDIII" }),
  "crafts.arts"                     : ({ "DIIII" }),
  "crafts.music"                    : ({ "DIIII" }),
  "crafts.points"                   : ({ "DDIIW" }),
"faith"                             : ({ "ISWWW" }),
  "faith.rituals.offensive"         : ({ "ISSWW" }),
  "faith.rituals.defensive"         : ({ "IDDWW" }),
  "faith.rituals.curing"            : ({ "ICCWW" }),
  "faith.rituals.misc"              : ({ "IIWWW" }),
  "faith.items"                     : ({ "IIDWW" }),
  "faith.points"                    : ({ "IICWW" }),
"fighting"                          : ({ "DDSSI" }),
  "fighting.combat.melee"           : ({ "DSSSW" }),
  "fighting.combat.melee.sharp"     : ({ "DDSSS" }),
  "fighting.combat.melee.pierce"    : ({ "DDDSS" }),
  "fighting.combat.melee.blunt"     : ({ "DSSSS" }),
  "fighting.combat.melee.unarmed"   : ({ "DDDSW" }),
  "fighting.combat.range"           : ({ "DDDSS" }),
  "fighting.combat.parry"           : ({ "DDSSW" }),
  "fighting.combat.dodging"         : ({ "DDDSW" }),
  "fighting.combat.special.weapon"  : ({ "SDIII" }),
  "fighting.combat.special.unarmed" : ({ "DDIII" }),
  "fighting.combat.special.tactics" : ({ "WWIII" }),
  "fighting.points"                 : ({ "DSSCC" }),
"magic"                             : ({ "IIIDW" }),
  "magic.spells"                    : ({ "IIDWW" }),
  "magic.spells.offensive"          : ({ "WSSII" }),
  "magic.spells.defensive"          : ({ "WCCII" }),
  "magic.spells.misc"               : ({ "WDDII" }),
  "magic.spells.special"            : ({ "WWWII" }),
  "magic.methods.elemental"         : ({ "IICCC" }),
  "magic.methods.mental"            : ({ "IIIII" }),
  "magic.methods.spiritual"         : ({ "IIWWW" }),
  "magic.methods.physical"          : ({ "IIDDD" }),
  "magic.items"                     : ({ "IIDWW" }),
  "magic.items.held"                : ({ "IIDWW" }),
  "magic.points"                    : ({ "IISWW" }),
"other"                             : ({ "DDISS" }),
   "other.trading"                  : ({ "IIIIW" }),
   "other.movement"                 : ({ "CCDDS" }),
   "other.acrobatics"               : ({ "CDDSS" }),
   "other.evaluating"               : ({ "IIIIW" }),
   "other.perception"               : ({ "IIWWW" }),
   "other.direction"                : ({ "DDIIW" }),
   "other.health"                   : ({ "CCCCS" }),
   "other.points"                   : ({ "CDISW" }),
   "other.language"                 : ({ "IIIWW" }),
   "other.culture"                  : ({ "IIIWW" }),
  ]);
}
mapping query_reg_skills() { return _reg_skills; }
mixed *query_skills() { return _skills; }
string *query_skill_path(string skill) {
   if (skill[0] == '.') {
      skill = skill[1..1090];
   }
   if (!_reg_skills[skill]) {
      return 0;
   }
   return explode(skill, ".");
}
string *query_skill_tree(string skill) {
   return _skill_tree[skill];
}
string query_skill_stat(string skill) {
   int i;
   string *bit, s;
   bit = explode(skill, ".");
   i = sizeof(bit);
   while (i >= 0) {
      s = implode(bit[0..i], ".");
      if (_stat_bonus[s])
         return _stat_bonus[s][SKILL_BONUS];
      else
         i--;
   }
   return "";
}
private int add_stat_bonus(string skill, string bonus) {
   if (_stat_bonus[skill]) {
      return 0;
   }
   _stat_bonus[skill] = ({ bonus });
   return 1;
}
private int remove_stat_bonus(string skill) {
   if (!_stat_bonus[skill]) {
      return 0;
   }
   _stat_bonus = m_delete(_stat_bonus, skill);
   return 1;
}
string *query_children(mixed *arr, string path) {
   string *ret;
   int i;
   ret = ({ });
   for (i = 0; i < sizeof(arr); i += SKILL_ARR_SIZE) {
      ret += ({ path+arr[i] }) +
           query_children(arr[i+SKILL_BIT], path+arr[i]+".");
   }
   return ret;
}
string *query_immediate_children(string skill) {
   return _immediate_children[skill];
}
string *query_all_children(string skill) {
   if (_reg_skills[skill]) {
      return _reg_skills[skill][0];
   }
   return 0;
}
private string *query_imm_children(mixed *arr, string path) {
   string *ret;
   int i;
   ret = ({ });
   for (i = 0; i < sizeof(arr); i+= SKILL_ARR_SIZE) {
      ret += ({ path+arr[i] });
   }
   return ret;
}
private string *create_skill_tree(string skill) {
   string *ret, *bits;
   int i;
   ret = ({ });
   bits = explode(skill, ".");
   if (_only_leaf[bits[0]]) {
      return ({ skill });
   }
   for (i = sizeof(bits) - 1; i >= 0; i--) {
      ret += ({ implode(bits[0..i], ".") });
   }
   return ret;
}
private mapping flatten(mixed *arr, string bit) {
   int i;
   mapping ret;
   if (!bit) {
      bit = "";
   }
   ret = ([ ]);
   for (i = 0; i < sizeof(arr); i += SKILL_ARR_SIZE) {
      reset_eval_cost();
      if (sizeof(arr[i+SKILL_BIT]) == 0) {
         ret[(bit+arr[i])] = ({ ({ bit+arr[i] }), 1 });
      } else {
         ret[bit + arr[i]] = ({ query_children(arr[i+SKILL_BIT], bit+arr[i]+".") +
                              ({ bit + arr[i] }),
                              query_skill_cost_int(bit+arr[i]) });
         ret += flatten(arr[i+SKILL_BIT], bit+arr[i]+".");
      }
      _skill_tree[(bit+arr[i])] = create_skill_tree(bit+arr[i]);
      _immediate_children[(bit+arr[i])] = query_imm_children(arr[i+SKILL_BIT],bit+arr[i]+".");
   }
   return ret;
}
private int query_skill_cost_rec(mixed *arr) {
   int i, tmp;
   if (!sizeof(arr)) {
      return 1;
   }
   for (i=0;i<sizeof(arr);i+=SKILL_ARR_SIZE) {
      tmp += query_skill_cost_rec(arr[i+SKILL_BIT]);
   }
   return tmp;
}
private int query_skill_cost_int(string str) {
   int i;
   mixed *arr;
   string *path;
   path = explode(str, ".");
   arr = _skills;
   while (sizeof(path)) {
      i = member_array(path[0], arr);
      if (i == -1) {
         return -1;
      } else {
         path = path[1..sizeof(path)];
         arr = arr[i+SKILL_BIT];
      }
   }
   return query_skill_cost_rec(arr);
}
string *query_related_skills(string skill) {
   if (_reg_skills[skill]) {
      return _reg_skills[skill][0];
   }
   return 0;
}
int query_skill_cost(string skill) {
   if (_reg_skills[skill]) {
      return _reg_skills[skill][1];
   }
   return -1;
}
string query_skill(string *bits) {
   mixed *arr;
   int i;
   string path, s1;
   if( !bits || !sizeof(bits) ) {
      return 0;
   }
   path = "";
   arr = _skills;
   for (i = 0; i < sizeof(arr); i += SKILL_ARR_SIZE) {
      if (sscanf(arr[i], bits[0]+"%s", s1) == 1) {
         path += "."+arr[i];
         arr = arr[i+SKILL_BIT];
         i = -SKILL_ARR_SIZE;
         bits = bits[1..sizeof(bits)];
         if (!sizeof(bits))
            return path[1..strlen(path)];
      }
   }
   if (i<sizeof(arr)) {
      return path[1..strlen(path)];
   }
   return 0;
}
int query_only_leaf(string str) {
   string *bits;
   bits = explode(str, ".");
   return _only_leaf[bits[0]];
}
int query_allowed_to_teach(string str) {
   return !_not_allowed_to_teach[str];
}
int query_only_show_if_non_zero(string str) {
   return _only_show_if_non_zero[str];
}
int query_no_bonus(string str) {
   return _no_bonus[str] || _ignore_bits[str];
}
int is_skill_ignored(string skill) {
   return _ignore_bits[skill];
}
int query_skill_depth(string* skill) {
   int depth;
   int i;
   depth = 0;
   for (i = 0; i < sizeof(skill) - 1; i++) {
      if (!is_skill_ignored(implode(skill[0..i], "."))) {
         depth++;
      }
   }
   return depth;
}