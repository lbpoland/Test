#include <creator.h>
#include <peopler.h>
int cmd(string str) {
   mixed *bing;
   bing = this_player()->query_property("netdups list");
   if (!bing) {
      bing = ND_DEFAULT;
   }
   return PEOPLER->do_command(bing, str,
      (: query_ip_number($1) == 0 || query_ip_number($2) == 0 ||
         strcmp(query_ip_number($1), query_ip_number($2)) :),
      1);
}
mixed *query_patterns() {
   return ({ "", (: cmd(0) :),
             "<word>", (: cmd($4[0]) :) });
}