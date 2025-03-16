#include <gossip.h>
mixed *gossip;
mixed *rumours;
nosave mixed *filter_these;
private void save_stuff();
void create() {
   seteuid(getuid());
   filter_these = ({ "fuck", "fucking", "fucker", "cunt", "bitch", "shit" });
   gossip = ({ });
   rumours = ({ });
   unguarded( (: restore_object(GOSSIP_SAVE_FILE) :) );
   call_out((: save_stuff :), 10*60);
}
private void save_stuff() {
   call_out((: save_stuff :), 10*60);
   if (sizeof(gossip) > GOSSIP_KEEP_LEVEL) {
      gossip = gossip[sizeof(gossip)-GOSSIP_KEEP_LEVEL..];
   }
   if (sizeof(rumours) > RUMOUR_KEEP_LEVEL) {
      rumours = rumours[sizeof(rumours)-RUMOUR_KEEP_LEVEL..];
   }
   unguarded( (: save_object(GOSSIP_SAVE_FILE) :) );
}
void add_gossip(string name, string mess) {
   string *bits;
   int i;
   bits = explode(mess, " ");
   for (i = 0; i < sizeof(bits); i++) {
      if (member_array(bits[i], filter_these) != -1) {
         return ;
      }
   }
   gossip += ({ ({ name, mess }) });
}
varargs string remove_gossip(string match, int force)
{
  int pos, index;
  if (!match || match == "") return "Must provide a match string";;
  pos = -1;
  for (index = sizeof(gossip); index; index--) {
    if (strsrch(gossip[index - 1][1], match) != -1) {
      if (pos == -1)
        pos = index - 1;
      else if (!force) {
        return "too many matches";
      }
    }
  }
  if (pos != -1) {
    string found = "found " + gossip[pos][1] + " by " + gossip[pos][0];
    gossip = delete(gossip, pos, 1);
    return found;
  } else
    return "No match";
}
void add_rumour(string name, string mess) {
   rumours += ({ ({ name, mess }) });
   save_stuff();
}
string *query_random_gossip() {
   if (sizeof(rumours) && random(2)) {
      return rumours[random(sizeof(rumours))];
   } else {
      if (sizeof(gossip))
	 return gossip[random(sizeof(gossip))];
      else
	 return 0;
   }
}
mixed *query_gossip() {
   return gossip;
}
string *query_filter() {
   return filter_these;
}
mixed *query_rumours() {
   return rumours;
}