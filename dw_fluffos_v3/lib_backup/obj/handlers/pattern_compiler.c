#include <user_parser.h>
#define PATTERN_CACHE_SIZE 200
nosave mapping patterns;
nosave mapping pattern_short;
nosave string *pattern_order;
nosave int hits, reqs, cache_callout;
nomask mixed *compile_pattern(string str);
void create() {
   patterns = ([ "" : ({ 100 }) ]);
   pattern_short = ([ "" : "" ]);
}
void clean_cache() {
  int i;
  for(i=0; i<(sizeof(pattern_order)-PATTERN_CACHE_SIZE); i++) {
    map_delete(patterns, pattern_order[i]);
    map_delete(pattern_short, pattern_order[i]);
  }
  pattern_order = pattern_order[i..];
  cache_callout = 0;
}
nomask mixed *query_pattern(string pattern) {
  if (!patterns[pattern]) {
    patterns[pattern] = compile_pattern(pattern);
  }
  return patterns[pattern];
}
nomask mixed *compile_pattern(string str) {
   mixed *pattern;
   mixed *bits;
   int i;
   int failed;
   int type;
   int weight;
   mixed env;
   string short;
   string short_bit;
   int pos;
   int pos2;
   int j;
   int k;
   bits = explode(str, " ") - ({ 0, "" });
   pattern = ({ });
   short = "";
   for (i = 0; i < sizeof(bits) && !failed; i++) {
      switch (bits[i][0]) {
      case '<' :
         pos = strsrch(bits[i], "'");
         if (pos != -1) {
             pos2 = strsrch(bits[i][pos + 1..], "'", pos + 1);
             if (pos2 == -1) {
                for (j = i + 1; j < sizeof(bits); j++) {
                   pos2 = strsrch(bits[j], "'");
                   if (pos2 != -1) {
                      break;
                   }
                }
                if (j < sizeof(bits)) {
                   for (k = i + 1; k <= j; k++) {
                      bits[i] += " " + bits[k];
                   }
                   bits[j] = bits[i];
                   i = j;
                   pos2 = strsrch(bits[i], "'", -1);
                }
             } else {
                pos2 += pos + 1;
             }
             if (pos2 != -1) {
                short_bit = bits[i][pos+1..pos2-1];
                bits[i] = bits[i][0..pos-1] + bits[i][pos2+1..];
             } else {
                short_bit = 0;
             }
         } else {
             short_bit = 0;
         }
         bits[i] = bits[i][1..<2];
         bits[i] = explode(bits[i], ":");
         if (!bits[i]) {
            bits[i] = ({ "" });
         }
         switch (bits[i][0]) {
         case "direct" :
            weight += 7;
            if (sizeof(bits[i]) > 1) {
               switch (bits[i][1]) {
               case "living" :
                  type = LIVING;
                  break;
               case "distant-living" :
                  type = DISTANT_LIVING;
                  break;
               case "any-living" :
                  type = ANY_LIVING;
                  break;
               case "object" :
                  type = ANY_OBJECT;
                  break;
               case "player" :
                  type = TARGET_PLAYER;
                  break;
               default :
                  failed = 1;
                  printf("Unknown type of direct (%s).\n", bits[i][1]);
                  break;
               }
               if (!short_bit) {
                   short += "<"+bits[i][1]+"> ";
               } else {
                   short += "<" + short_bit + "> ";
               }
            } else {
               type = ANY_OBJECT;
               bits[i] += ({ "object" });
               if (!short_bit) {
                  short += "<object> ";
               } else {
                   short += "<" + short_bit + "> ";
               }
            }
            env = ENV_ME_HERE;
            if (sizeof(bits[i]) > 2)
               switch (bits[i][2]) {
               case "here" :
                  env = ENV_HERE;
                  break;
               case "me" :
                  env = ENV_ME;
                  break;
               case "direct-obs" :
                  env = ENV_DIRECT_OBS;
                  break;
               case "me-here" :
                  env = ENV_ME_HERE;
                  break;
               case "here-me" :
                  env = ENV_HERE_ME;
                  break;
               default :
                  env = bits[i][2];
                  break;
               }
            pattern += ({ DIRECT_OBJECT, type, env });
            break;
         case "indirect" :
            weight += 7;
            if (sizeof(bits[i]) > 1) {
               switch (bits[i][1]) {
               case "living" :
                  type = LIVING;
                  break;
               case "distant-living" :
                  type = DISTANT_LIVING;
                  break;
               case "any-living" :
                  type = ANY_LIVING;
                  break;
               case "object" :
                  type = ANY_OBJECT;
                  break;
               case "player" :
                  type = TARGET_PLAYER;
                  break;
               case "wiz-present" :
                  type = WIZ_PRESENT_TARGET;
                  break;
               default :
                  failed = 1;
                  printf("Unknown type of indirect (%s).\n", bits[i][1]);
                  break;
               }
               if (!short_bit) {
                  short += "<"+bits[i][1]+"> ";
               } else {
                   short += "<" + short_bit + "> ";
               }
            } else {
               type = ANY_OBJECT;
               bits[i] += ({ "object" });
               if (!short_bit) {
                  short += "<object> ";
               } else {
                   short += "<" + short_bit + "> ";
               }
            }
            env = ENV_ME_HERE;
            if (sizeof(bits[i]) > 2)
               switch (bits[i][2]) {
               case "here" :
                  env = ENV_HERE;
                  break;
               case "me" :
                  env = ENV_ME;
                  break;
               case "direct-obs" :
                  env = ENV_DIRECT_OBS;
                  break;
               case "me-here" :
                  env = ENV_ME_HERE;
                  break;
               case "here-me" :
                  env = ENV_HERE_ME;
                  break;
               default :
                  env = bits[i][2];
                  break;
               }
            pattern += ({ INDIRECT_OBJECT, type, env });
            break;
         case "string" :
            if (sizeof(bits[i]) > 1) {
               switch (bits[i][1]) {
               case "small" :
                  if (!short_bit) {
                     short += "<string> ";
                  } else {
                     short += "<" + short_bit + "> ";
                  }
                  weight += 6;
                  pattern += ({ SHORT_STRING });
                  break;
               case "long" :
                  if (!short_bit) {
                     short += "<string> ";
                  } else {
                     short += "<" + short_bit + "> ";
                  }
                  weight += 5;
                  pattern += ({ STRING });
                  break;
               case "quoted" :
                  if (!short_bit) {
                     short += "\"<string>\" ";
                  } else {
                     short += "\"<" + short_bit + ">\" ";
                  }
                  weight += 8;
                  pattern += ({ QUOTED_STRING });
                  break;
               default :
                  printf("Invalid type of string (%s).\n", bits[i][1]);
                  failed = 1;
                  break;
               }
            } else {
               if (!short_bit) {
                  short += "<string> ";
               } else {
                  short += "<" + short_bit + "> ";
               }
               weight += 5;
               pattern += ({ STRING });
            }
            break;
         case   "number" :
            if (!short_bit) {
               short += "<number> ";
            } else {
               short += "<" + short_bit + "> ";
            }
            weight += 10;
            pattern += ({ NUMBER });
            break;
         case "word" :
            if (!short_bit) {
               short += "<word> ";
            } else {
               short += "<" + short_bit + "> ";
            }
            weight += 7;
            pattern += ({ SINGLE_WORD });
            break;
         case "fraction" :
            if (!short_bit) {
               short += "<fraction> ";
            } else {
               short += "<" + short_bit + "> ";
            }
            weight += 10;
            pattern += ({ FRACTION });
            break;
         default :
            weight += 10;
            bits[i] = implode(bits[i], ":");
            if (master()->query_word_list(bits[i])
                  || this_player()->query_word_list(bits[i])) {
               if (!short_bit) {
                  short += "<"+bits[i]+"> ";
               } else {
                  short += "<" + short_bit + "> ";
               }
               pattern += ({ WORD_LIST, bits[i] });
            } else {
               printf("Unknown word list name (%s)\n", bits[i]);
               failed = 1;
            }
            break;
         }
         break;
      case '{' :
         weight += 10;
         if (bits[i][<1] == '}') {
            pattern += ({ WORD_LIST, explode(bits[i][1..<2], "|") });
            short += bits[i]+" ";
         } else {
            int old = i;
            string elm, *res;
            for (++i; bits[i][<1] != '}'; i++);
            res = ({});
            foreach (elm in explode(implode(bits[old..i], " ")[1..<2], "|"))
               res += ({ explode(elm, " ") });
            pattern += ({ WORD_LIST_SPACES, res });
            short += implode(bits[old..i], " ")+" ";
         }
         break;
      case '[' :
         weight += 4;
         if (bits[i][1] == '<') {
            if (MASTER->query_word_list(bits[i][2..<3])
                  || this_player()->query_word_list(bits[i][2..<3]))
               pattern += ({ OPTIONAL, bits[i][2..<3] });
            else {
               printf("Unknown word list name (%s)\n", bits[i]);
               failed = 1;
               pattern += ({ OPTIONAL, bits[i][2..<3] });
            }
            short += bits[i]+" ";
         } else if (bits[i][1] == '{') {
            if (bits[i][<1] == ']') {
               pattern += ({ OPTIONAL, explode(bits[i][2..<3], "|") });
               short += bits[i]+" ";
            } else {
               int old = i;
               string elm, *res;
               for (++i; bits[i][<1] != ']'; i++);
               res = ({});
               foreach (elm in explode(implode(bits[old..i], " ")[2..<3], "|"))
                  res += ({ explode(elm, " ") });
               pattern += ({ OPTIONAL_SPACES, res });
               short += implode(bits[old..i], " ")+" ";
            }
         } else if (bits[i][<1] == ']') {
            pattern += ({ OPTIONAL, explode(bits[i][1..<2], "|") });
            short += bits[i]+" ";
         } else {
            int old = i;
            string elm, *res;
            for (++i; bits[i][<1] != ']'; i++);
            res = ({});
            foreach (elm in explode(implode(bits[old..i], " ")[1..<2], "|"))
               res += ({ explode(elm, " ") });
            pattern += ({ OPTIONAL_SPACES, res });
            short += implode(bits[old..i], " ")+" ";
         }
         break;
      default :
         weight += 10;
         short += bits[i]+" ";
         pattern += ({ WORD_LIST, ({ bits[i] }) });
         break;
      }
   }
   if (failed) {
      return 0;
   }
   pattern_short[str] = short;
   return ({ weight }) + pattern;
}
string query_short_pattern(string str) {
  reqs++;
  if(!pattern_short[str])
    compile_pattern(str);
  else
    hits++;
  return pattern_short[str];
}
mixed *stats() {
  return  ({
    ({ "patterns", sizeof(keys(pattern_short)), }),
        ({ "requests", reqs, }),
          ({ "cache hit percent", (hits * 100) / reqs, }),
            });
}