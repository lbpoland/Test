#include <obj_parser.h>
#if !efun_defined(query_multiple_short)
inherit "/secure/simul_efun/multiple_short";
#endif
#include <playtesters.h>
#ifdef DEBUG
#define TRACE(ARG) tell_creator("pinkfish", ARG + "\n")
#else
#define TRACE(ARG)
#endif
#define EVERY_NUM 18729487
private nosave mapping _ordinals;
private nosave mapping _counters;
private nosave mapping _fractions;
void tell_creator(string player, string text, mixed arg ...);
#if !efun_defined(living)
int living (object);
#endif
class obj_match match_objects_in_environments( string input, mixed env_list,
                                      int type, object player);
void create()
{
   _ordinals = ([
      "any" : 1,
      "a" : 1,
      "an" : 1,
      "the" : 1,
      "1st" : 1, "first" : 1,
      "2nd" : 2, "second" : 2,
      "3rd" : 3, "third" : 3,
      "4th" : 4, "fourth" : 4,
      "5th" : 5, "fifth" : 5,
      "6th" : 6, "sixth" : 6,
      "7th" : 7, "seventh" : 7,
      "8th" : 8, "eighth" : 8,
      "9th" : 9, "ninth" : 9,
      "10th" : 10, "tenth" : 10,
      "last" : -1
   ]);
   _counters = ([
      "1" : 1, "one" : 1,
      "2" : 2, "two" : 2,
      "3" : 3, "three" : 3,
      "4" : 4, "four" : 4,
      "5" : 5, "five" : 5,
      "6" : 6, "six" : 6,
      "7" : 7, "seven" : 7,
      "8" : 8, "eight" : 8,
      "9" : 9, "nine" : 9,
      "10" : 10, "ten" : 10,
      "11" : 11, "eleven" : 11,
      "12" : 12, "twelve" : 12,
      "13" : 13, "thirteen" : 13,
      "14" : 14, "fourteen" : 14,
      "15" : 15, "fifteen" : 15,
      "16" : 16, "sixteen" : 16,
      "17" : 17, "seventeen" : 17,
      "18" : 18, "eighteen" : 18,
      "19" : 19, "nineteen" : 19,
      "20" : 20, "twenty" : 20,
      "many" : 20,
      "every" : EVERY_NUM,
   ]);
   _fractions = ([
      "half" : ({ 1, 2 }),
      "quarter" : ({ 1, 4 }),
      "some" : ({ 1, 50 })
   ]);
}
private void fixup_context(object player,
                   object* objects,
                   class obj_match_context context) {
   if (!player || !sizeof(objects)) {
      return ;
   }
   if (sizeof(objects) > 1) {
      context->plural = objects;
   } else if (living(objects[0]) && objects[0] != player) {
      if (objects[0]->query_male()) {
         context->him = objects[0];
      } else if (objects[0]->query_female() != 0) {
         context->her = objects[0];
      } else {
         context->it = objects[0];
      }
   } else {
      context->it = objects[0];
   }
   player->set_it_them(context);
}
class obj_match match_object_in_array( string input,
                     object *ob_list,
                     int type,
                     object player)
{
   object ob;
   object *singular_objects;
   object *plural_objects;
   object thing;
   string first_word;
   string rest;
   string *bits;
   string bit;
   string inside_match;
   string nick;
   int n;
   int ord;
   int random_item;
   int count;
   int *fraction;
   mixed *obj_info;
   class obj_match result;
   class obj_match omatch;
   class obj_match_context context;
   if (!player) {
      player = this_player();
   }
   input = lower_case(input);
   if (player) {
      context = player->query_it_them();
   }
   if (!classp(context) || sizeof(context) != 9) {
      context = new(class obj_match_context);
      context->plural = ({ });
      if (player) {
         player->set_it_them(context);
      }
   }
   TRACE( "            Processed input: " + input );
   omatch = new( class obj_match );
   omatch->text = input;
   omatch->objects = ({ });
   if( strsrch( input, "&" ) != -1 ) {
      TRACE( "            Splitting input" );
      foreach( bit in explode(input, "&") - ({ "" }) )
      {
         result = match_object_in_array( bit, ob_list,
                                type, player);
         if( result->result == OBJ_PARSER_SUCCESS ) {
            omatch->objects |= result->objects;
         }
      }
      if (!sizeof(omatch->objects)) {
         omatch->text = input;
         omatch->result = OBJ_PARSER_NO_MATCH;
         return omatch;
      }
      fixup_context(player, omatch->objects, context);
      omatch->result = OBJ_PARSER_SUCCESS;
      return omatch;
   }
   if (!(type & OBJ_PARSER_TYPE_EXISTENCE) &&
       player && !player->query_property(OBJ_PARSER_USE_AND_AS_BREAK_PROP)) {
      input = replace_string(input, " and ", ",");
   }
   if( strsrch( input, "," ) != -1 )
   {
      TRACE( "            Splitting input" );
      foreach( bit in explode(input, ",") - ({ "" }) )
      {
         result = match_object_in_array( bit, ob_list,
                                type, player);
         if( result->result == OBJ_PARSER_SUCCESS ) {
            omatch->objects |= result->objects;
         } else if (!(type & OBJ_PARSER_TYPE_EXISTENCE)) {
            return result;
         }
      }
      fixup_context(player, omatch->objects, context);
      omatch->result = OBJ_PARSER_SUCCESS;
      return omatch;
   }
   if (player) {
      nick = player->expand_nickname(input);
      if (nick && nick!="") {
        input = nick;
      }
   }
   if (!(type & OBJ_PARSER_TYPE_NO_NESTED)) {
      n = strsrch(input, " in ", -1);
      if (n == -1) {
         n = strsrch(input, " on ", -1);
      }
      if (n != -1) {
         inside_match = input[0..n - 1];
         input = input[n + 4..];
      } else {
         inside_match = 0;
      }
   }
   n = strsrch( input, " " );
   ord = 0;
   if( n != -1 )
   {
      first_word = input[ 0 .. n - 1 ];
      rest = input[ n + 1 .. ];
      fraction = _fractions[ first_word ];
      if (!fraction) {
         if (sscanf(first_word, "%d/%d", n, count) == 2) {
            if (n > count || n < 0 || count <= 0) {
               omatch = new( class obj_match );
               omatch->text = input;
               omatch->objects = ({ });
               omatch->result = OBJ_PARSER_BAD_FRACTION;
               return omatch;
            }
            fraction = ({ n, count });
         }
         count = 0;
      }
      if (fraction) {
         input = rest;
         if (input[0..2] == "of ") {
            input = input[3..];
         }
      }
      n = strsrch(input, " ");
   }
   if( n != -1 )
   {
      first_word = input[ 0 .. n - 1 ];
      rest = input[ n + 1 .. ];
      ord = _ordinals[ first_word ];
      if( ord > 0 ) {
         input = rest;
      }
      if( !ord )
      {
         count = _counters[ first_word ];
         if( !count ) {
            sscanf( first_word, "%d", count );
         }
         if( count > 0 ) {
            input = rest;
         }
         if (!count) {
            n = strsrch( input, " ", -1);
            if (n != -1) {
               if (sscanf(input[n + 1..], "%d", ord) == 1) {
                  input = input[0..n-1];
               }
            }
         }
      }
      n = strsrch(input, " ");
   }
   if (n != -1 && input[0 .. n - 1] == "random") {
      if (ord) {
         random_item = ord;
      } else {
         random_item = 1;
      }
      count = EVERY_NUM;
      ord = 0;
      input = input[n + 1..];
   }
   omatch = new( class obj_match );
   omatch->text = input;
   omatch->objects = ({ });
   bits = explode(input, " ");
   if (!sizeof(bits)) {
      omatch->result = OBJ_PARSER_NO_MATCH;
   }
   context->ordinal = ord;
   context->number_included = count;
   context->ignore_rest = 0;
   context->fraction = fraction;
   singular_objects = ({ });
   plural_objects = ({ });
   if (player) {
      ob_list = filter(ob_list, (: $1->query_visible($(player)) :));
   }
   foreach( ob in ob_list )
   {
      if (!inside_match && (type & OBJ_PARSER_TYPE_LIVING)) {
         if (!living(ob)) {
            continue;
         }
      }
      if (!inside_match && (type & OBJ_PARSER_TYPE_PLAYER)) {
         if (!userp(ob)) {
            continue;
         }
      }
      obj_info = ob->parse_match_object( bits, player, context );
      if (obj_info) {
         if (obj_info[OBJ_PARSER_MATCH_TYPE] & OBJ_PARSER_MATCH_PLURAL)
         {
            plural_objects += obj_info[OBJ_PARSER_OBJECTS];
         }
         if (obj_info[OBJ_PARSER_MATCH_TYPE] & OBJ_PARSER_MATCH_SINGULAR)
         {
            singular_objects += obj_info[OBJ_PARSER_OBJECTS];
         }
      }
      if (context->ignore_rest) {
         break;
      }
   }
   if (sizeof(singular_objects) > 1 &&
       (!ord && !count)) {
      if (player && !player->query_property(OBJ_PARSER_AMBIGUOUS_PROP)) {
         omatch->objects = singular_objects;
         omatch->result = OBJ_PARSER_AMBIGUOUS;
         return omatch;
      }
      if (!random_item) {
         singular_objects = singular_objects[0..0];
      } else {
         n = random(sizeof(singular_objects));
         singular_objects = singular_objects[n..n];
      }
   }
   if( !sizeof( singular_objects ) &&
       !sizeof( plural_objects))
   {
      TRACE( "            No matches" );
      omatch->result = OBJ_PARSER_NO_MATCH;
      return omatch;
   }
   if (type & OBJ_PARSER_TYPE_SLOPPY_MATCHING) {
      omatch->objects = singular_objects & plural_objects;
   } else if (random_item) {
      if (sizeof(plural_objects)) {
         omatch->objects = plural_objects;
      } else {
         omatch->objects = singular_objects;
      }
      n = random(sizeof(omatch->objects));
      omatch->objects = omatch->objects[n..n];
   } else if (ord || count == 1 || count == EVERY_NUM) {
      if (ord == -1) {
         omatch->objects = singular_objects[<1..<1];
      } else {
         omatch->objects = singular_objects;
      }
   } else if (count) {
      omatch->objects = plural_objects;
   } else {
      if (sizeof(plural_objects)) {
         omatch->objects = plural_objects;
      } else {
         omatch->objects = singular_objects;
      }
   }
   if (sizeof(omatch->objects) > 1 && fraction) {
      omatch->result = OBJ_PARSER_FRACTION;
      return omatch;
   }
   if (context->number_included && count != EVERY_NUM) {
      omatch->result = OBJ_PARSER_NOT_ENOUGH;
      return omatch;
   }
   if (inside_match) {
      foreach (thing in omatch->objects) {
         if (!thing->can_find_match_recurse_into(player)) {
            omatch->objects -= ({ thing });
         }
      }
      if (sizeof(omatch->objects)) {
         result = match_objects_in_environments(inside_match,
                                             omatch->objects,
                                             type,
                                             player);
         omatch->objects = ({ });
         if (result->result == OBJ_PARSER_SUCCESS) {
            foreach (thing in result->objects) {
               if (environment(thing) &&
                   environment(thing)->can_find_match_reference_inside_object(thing, player)) {
                  omatch->objects += ({ thing });
               }
            }
         } else {
            result->text = inside_match + " in " + input;
            return result;
         }
      }
   }
   if( sizeof( omatch->objects ) == 0 )
   {
      TRACE( "            No matches (living/visible elimination)" );
      omatch->result = OBJ_PARSER_NO_MATCH;
      return omatch;
   }
   fixup_context(player, omatch->objects, context);
   omatch->result = OBJ_PARSER_SUCCESS;
   return omatch;
}
class obj_match match_objects_in_environments( string input, mixed env_list,
                                      int type, object player)
{
   object* tmp_expanded;
   object* stuff;
   object ob;
   class obj_match omatch;
   if (!player) {
      player = this_player();
   }
   if (!pointerp(env_list)) {
      if (input == "all" &&
          env_list->query_is_room() &&
          player->check_dark(env_list->query_light())) {
         omatch = new( class obj_match );
         omatch->text = input;
         omatch->objects = ({ });
         omatch->result = OBJ_PARSER_TOO_DARK;
         return omatch;
      }
      tmp_expanded = env_list->find_inv_match(input,player);
   } else {
      tmp_expanded = ({ });
      foreach (ob in env_list) {
         if (!ob) {
            continue;
         }
         if (input == "all" &&
             ob->query_is_room() &&
             player->check_dark(ob->query_light())) {
            continue;
         }
         stuff = ob->find_inv_match(input,player);
         if (stuff && sizeof(stuff)) {
            tmp_expanded += stuff;
         }
      }
   }
   if (!sizeof(tmp_expanded)) {
      omatch = new( class obj_match );
      omatch->text = input;
      omatch->objects = ({ });
      omatch->result = OBJ_PARSER_NO_MATCH;
      return omatch;
   }
   return match_object_in_array(input, tmp_expanded, type,
                                player);
}
object* match_objects_for_existence(string input,
                                    object* env_list,
                                    object player) {
   class obj_match stuff;
   stuff = match_objects_in_environments(input, env_list,
                                         OBJ_PARSER_TYPE_EXISTENCE, player);
   switch (stuff->result) {
   case OBJ_PARSER_SUCCESS :
   case OBJ_PARSER_AMBIGUOUS :
      return stuff->objects;
   default :
      return ({ });
   }
}
string match_objects_failed_mess(class obj_match failed_match) {
   switch (failed_match->result) {
   case OBJ_PARSER_BAD_ENVIRONMENT :
      return "Cannot find \""+ failed_match->text +
                         "\" here, access is not allowed.\n";
   case OBJ_PARSER_NOT_LIVING :
      return "The objects \""+
             query_multiple_short(failed_match->objects) +
             "\" are not living.\n";
   case OBJ_PARSER_TOO_DARK :
      return "Cannot find \""+ failed_match->text +
             "\", it is too dark.\n";
   case OBJ_PARSER_NO_MATCH :
      return "Cannot find \""+ failed_match->text +
             "\", no match.\n";
   case OBJ_PARSER_BAD_FRACTION :
      return "The fraction \""+ failed_match->text +
             "\" is incorrectly specified.\n";
   case OBJ_PARSER_FRACTION :
      return "Can only reference a single object with a "
             "fraction, matched " +
             query_multiple_short(failed_match->objects) +
             " please be more specific.\n";
   case OBJ_PARSER_AMBIGUOUS :
      return "There are multiple matches for \"" + failed_match->text +
             "\".  See 'help parser' for more information on how to "
             "be more specific.\n";
   case OBJ_PARSER_NOT_ENOUGH :
      return "There are not enough \"" + failed_match->text +
             "\" to match as specified.\n";
   default :
      return "Unknow parser errror " + failed_match->result + ".\n";
   }
}