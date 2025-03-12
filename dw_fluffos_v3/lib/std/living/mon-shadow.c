object npc;
void setup_shadow(object ob) {
  shadow(ob,1);
  npc = ob;
}
void death_shadow() { destruct( this_object() ); }
object query_npc() { return npc; }