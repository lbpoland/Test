#define OBJ_PARSER_NO_CLASSES
#include <obj_parser.h>
inherit "/secure/simul_efun/obj_parser";
#include <playtesters.h>
private nosave mixed *rest;
mixed *query_strange_inventory(mixed *arr);
private object query_simul_efun_id(object ob, mixed *arr);
private object query_frac_simul_efun_id(object ob, mixed *arr);
#if !efun_defined(living)
int living(object);
#endif
int is_in_me_or_environment(object thing, object person)  {
   object env;
   if ((env = environment(thing)) == environment(person))
      return 1;
   if (!env)
      return 1;
   while (env  &&  !living(env))
      env = environment(env);
   if (env == person)
      return 1;
   return 0;
}
object* filter_in_me_or_environment(object* obs, object player) {
   return filter(obs, (: is_in_me_or_environment($1, $2) :), player);
}