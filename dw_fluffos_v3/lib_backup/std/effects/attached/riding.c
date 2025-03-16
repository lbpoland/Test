class riding {
   object transport;
   mixed saved_info;
}
string extra_look(object player) {
   return player->query_pronoun() + " is riding on " +
          environment(player)->the_short();
}
string query_classification() {
   return "mudlib.riding.transport";
}
int query_indefinate() {
   return 1;
}
class riding beginning(object player, mixed arg, int id) {
   class riding bing;
   bing = new(class riding);
   return bing;
}
class riding end(object player, class riding arg) {
}
void restart(object player, class riding bing) {
}