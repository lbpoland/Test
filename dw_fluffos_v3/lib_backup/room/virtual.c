inherit "/std/room/basic_room";
int no_init(){
  return 1;
}
void init(){
  previous_object()->move("/room/rubbish");
}
string long(object npc){
  if(query_verb() == "scry"){
    object ob;
    string where;
    ob = load_object(where = npc->query_true_location());
    if(!ob || environment(npc) == this_object()){
      return "This is where NPCs hide from players.";
    }
    return environment(npc)->long();
  }
  return "Go away!";
}