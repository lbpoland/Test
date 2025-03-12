#include <random_names.h>
#include <player_handler.h>
private mapping rules;
private string* _test_rules;
void create() {
   seteuid("Room");
   rules = ([ ]);
   _test_rules = ({ });
   unguarded((: restore_object, RANDOM_NAME_SAVE_FILE :));
   if (!_test_rules) {
      _test_rules = ({ });
   }
}
private void save_me() {
   unguarded((: save_object, RANDOM_NAME_SAVE_FILE :));
}
void open_file(string f) {
   string str, *bits, *stuff, lang;
   int i;
   bits = explode(f, ".");
   if (sizeof(bits) > 1) {
      lang = implode(bits[0..sizeof(bits)-2], ".");
   } else {
      lang = f;
   }
   lang = replace(lang, "_", " ");
   str = unguarded((: read_file, RANDOM_NAME_DATA_DIR+f :));
   bits = explode(str, "\n");
   rules[lang] = ([ ]);
   for (i=0;i<sizeof(bits);i++) {
      sscanf(bits[i], "%s#%*s", bits[i]);
      if (strlen(bits[i])) {
         stuff = explode("G"+bits[i], ":");
         if (sizeof(stuff) >= 3) {
            rules[lang][stuff[1]] = stuff[2];
         } else {
            write("Incorrect file format at line "+i+", less than 3 "
                  ": seporated bits.\n");
         }
      }
   }
   save_me();
}
string random_name(string lang) {
   string word = "W", *bing;
   int some_caps = 1, i;
   do {
      some_caps = 0;
      for (i = 0; i < strlen(word); i++)
         if (word[i] >= 'A' && word[i] <= 'Z') {
            bing = explode(rules[lang][word[i..i]], " ") - ({ "" });
            word = word[0..i-1] + bing[random(sizeof(bing))] + word[i+1..];
            some_caps = 1;
         }
   } while (some_caps);
   return word;
}
string *query_languages() { return keys(rules) - _test_rules; }
string *query_test_languages() {
   return _test_rules;
}
void add_test_language(string lang) {
   _test_rules += ({ lang });
   save_me();
}
void remove_test_language(string lang) {
   _test_rules -= ({ lang });
   save_me();
}
string unique_name(string lang) {
   string str;
   int ok;
   do {
      ok = 1;
      str = random_name(lang);
      if (strlen(str) < 2 || strlen(str) > 11)
         ok = 0;
      if (ok && PLAYER_HANDLER->test_user(str))
         ok = 0;
      if (ok && !PLAYER_HANDLER->test_valid(str))
         ok = 0;
      if (ok && find_living(str))
         ok = 0;
   } while (!ok);
   return str;
}
void dest_me() {
   destruct(this_object());
}