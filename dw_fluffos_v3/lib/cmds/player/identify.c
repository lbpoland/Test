#define EFFECT "/std/effects/object/identity_hold"
inherit "/cmds/base";
mixed cmd(object *indirect_obs, string new_name)
{
   string  word;
   object  thing;
   object *things;
   int *ees;
   int keep;
   if (!new_name)  {
      things = filter(indirect_obs, (: $1->query_identifier() :));
      if (!sizeof(things))  {
         if (sizeof(indirect_obs) > 1) {
            write("You do not have any of those objects identified.\n");
         } else {
            write("You do not have " + indirect_obs[0]->the_short() +
                  " identified.\n");
         }
      } else foreach (thing in things)  {
         write("You have " + thing->the_short() + " identified as \"" +
               thing->query_full_identifier() + "\".\n");
      }
   } else if (sizeof(indirect_obs) == 1)  {
      word = lower_case(new_name);
      if (word == "none") {
         ees = indirect_obs[0]->effects_matching(EFFECT->query_classification());
         if (!sizeof(ees)) {
            add_failed_mess("No identities to remove.");
            return 0;
         }
         keep = indirect_obs[0]->query_keep();
         indirect_obs[0]->delete_effect(ees[0]);
         if (keep) {
            thing->add_effect( EFFECT, ([ "keep" : 1 ]) );
         }
         write("You remove the description from " +
               indirect_obs[0]->the_short() + ".\n");
      } else {
         indirect_obs[0]->add_effect(EFFECT, ([ "identity" : word ]));
         write(indirect_obs[0]->the_short() + " may now be identified as \"" +
               word + "\".\n");
      }
   } else {
      write("You may only identify one thing at a time.\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object:me'object'> as <string'some new name'>",
             (: cmd($1, $4[1]) :),
             "<indirect:object:me'object(s)'>",
             (: cmd($1, 0) :) });
}