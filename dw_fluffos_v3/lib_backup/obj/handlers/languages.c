#include <language.h>
#define L_NEW 512
#define REPLACEMENTS (["no1":"noone",\
                       "ne1":"anyone",\
                       "any1":"anyone",\
                       "u":"you",\
                       "r":"are", \
                       "NE1":"anyone",\
                       "U":"you",\
                       "R":"are", \
                       "ur":"you are",\
                       "teh":"the", \
                       "some1":"someone", \
                       "c":"see", \
                       "cing":"seeing",\
                       "sum1":"someone",\
                       "urs":"yours",\
                       "thier":"their", \
                       "pls":"please",\
                       "PLZ":"please",\
                       "plz":"please",\
                       "b4":"before", \
                       "tnx":"thanks"])
mapping languages;
string search;
void create() {
  languages = ([
  "rabbit" : ({ L_SPOKEN|L_WRITTEN|L_DISTANCE|L_ALWAYS_SPEAK|L_NEW,
                "/std/languages/rabbit", 10 }),
  "general" : ({ L_SPOKEN|L_WRITTEN|L_DISTANCE|L_ALWAYS_SPEAK,
                "/std/languages/general", 10 }),
  "grunt" : ({ L_SPOKEN | L_ALWAYS_SPEAK, "/std/languages/grunt", 100 }),
  "wommon" : ({ L_WRITTEN|L_SPOKEN|L_DISTANCE|L_MAGIC,
                "/std/languages/wommon", 10 }),
              ]);
  search = "(" + implode(keys(REPLACEMENTS), "|") + ")";
}
int query_language_spoken(string str) {
  if (!languages[str])
    return 0;
  return languages[str][0]&L_SPOKEN;
}
int query_language_written(string str) {
  if (!languages[str])
    return 0;
  return languages[str][0]&L_WRITTEN;
}
int query_language_distance(string str) {
  if (!languages[str])
    return 0;
  return languages[str][0]&L_DISTANCE;
}
int query_language_new(string str) {
  if (!languages[str])
     return 0;
  return languages[str][0]&L_NEW;
}
int query_language_magic(string str) {
  if (!languages[str])
    return 0;
  return languages[str][0]&L_MAGIC;
}
int query_language_size(string str) {
  if (!languages[str])
    return 0;
  return languages[str][2];
}
int query_language_always_spoken(string str) {
  if (!languages[str])
    return 0;
  return languages[str][0]&L_ALWAYS_SPEAK;
}
mixed squidge_text(string lang, mixed str, int size) {
  if (!languages[lang])
    return 0;
  if (!(languages[lang][0]&L_MAGIC))
    return str[0..(size/languages[lang][2])];
  return (mixed)languages[lang][1]->squidge_text(str, size);
}
int query_flags(string name) {
  if (!languages[name])
    return 0;
  return languages[name][0];
}
string query_garble_object(string name) {
  if (!languages[name])
    return 0;
  return languages[name][1];
}
string *query_languages() {
  return m_indices(languages);
}
int test_language(string str) {
  return pointerp(languages[str]);
}
string query_language_spoken_skill(string lang) {
  return LANGUAGE_SKILL_START + replace(lang, " ", "_") + "." + SPOKEN_SKILL;
}
string query_language_written_skill(string lang) {
  return LANGUAGE_SKILL_START + replace(lang, " ", "_") + "." + WRITTEN_SKILL;
}
mixed garble_say(string lang, string start, string mess,
                 object player, object from, string type) {
   string garble_ob;
   if (query_language_new(lang)) {
      garble_ob = query_garble_object(lang);
      if (living (from) && garble_ob) {
         return garble_ob->garble_say(start, mess, player, from, type,
                                      query_language_spoken_skill(lang),
                                      type == SHOUT_TYPE);
      }
   } else {
      if (player->query_skill(query_language_spoken_skill(lang)) < 99) {
         garble_ob = query_garble_object(lang);
         if(garble_ob)
           return garble_ob->garble_say(start, mess, player, type);
         else
           debug_printf("Error, %s has no garble object.", lang);
      }
   }
   return ({ start, mess });
}
string garble_text(string lang, mixed text, object thing, object player ) {
   string garble_ob;
   if (functionp(text)) {
      text = evaluate(text);
   }
   if (query_language_new(lang)) {
      garble_ob = query_garble_object(lang);
      if (garble_ob) {
         return garble_ob->garble_text(text, thing, player,
                                       query_language_written_skill(lang));
      }
   } else {
      if (player->query_skill(query_language_written_skill(lang)) < 99) {
         garble_ob = query_garble_object(lang);
         if( !garble_ob )
            return "You do not recognise the language.\n";
         else
            return garble_ob->garble_text(text, thing, player);
      }
      if (query_language_magic(lang)) {
         garble_ob = query_garble_object(lang);
         return garble_ob->magical_text(text, thing, player);
      }
      return text;
   }
   if (query_language_magic(lang))
      return 0;
   return "Text written in " + lang + " could not have been written.  "
          "There are "
          "broken bits of letters scattered over the page, looks like "
          "someone had a bad game of scrabble.\n";
}
string do_replacements(string mess) {
  string *bits, name, value;
  mixed *tmp;
  int index, i, add_space;
  mess = replace(mess, ({"ne1 no ", "anyone know "}));
  if(!regexp(mess, search))
    return mess;
  if(mess[<1] == ' ')
    add_space = 1;
  bits = explode(mess, " ");
  foreach(name, value in REPLACEMENTS) {
    tmp = regexp(bits, "(^|[^A-Za-z0-9\\\\./_&-]+)"+name+"($|[^A-Za-z0-9\\./&_-]+)", 1);
    if(sizeof(tmp)) {
      for(i=0; i<sizeof(tmp); i+=2) {
        index = tmp[i+1]-1;
        bits[index] = replace(bits[index], name, value);
      }
    }
  }
  return implode(bits, " ") + (add_space ? " " : "");
}
string fix_shorthand(string mess) {
  string pre, mid, post, res;
  if (!stringp(mess)) {
     return "";
  }
  res = "";
  while(sscanf(mess, "%s'%s'%s", pre, mid, post) == 3) {
    res += do_replacements(pre) + "'" + mid;
    mess = "'" + post;
  }
  res += do_replacements(mess);
  return res;
}