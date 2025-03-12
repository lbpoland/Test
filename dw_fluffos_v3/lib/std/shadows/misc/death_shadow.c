object my_player;
int cost_life, resurrect_adds_life;
int test_add(object ob) {
   if (ob->query_property("dead usable"))
      return 1;
   return 0;
}
void set_death_cost_life( int i ) { cost_life = i; }
int query_death_cost_life() { return cost_life; }
void set_resurrect_adds_life( int i ) { resurrect_adds_life = i; }
int query_resurrect_adds_life() { return resurrect_adds_life; }
void attack() {
}
void adjust_hp() {
}
void set_hp() {
}
void do_death() {
}
void setup_shadow( object ob ) {
   shadow( ob, 1 );
   my_player = ob;
   cost_life = my_player->query_property( "death cost life" );
   my_player->remove_property( "death cost life" );
   resurrect_adds_life = my_player->query_property( "resurrect should add life" );
   my_player->remove_property( "resurrect should add life" );
}
int attack_by( object ob ) {
   tell_object( ob, "This person is a ghost... You cannot attack them.\n" );
   ob->stop_fight( my_player );
   return 1;
}
int attack_ob( object ob ) {
   write( "Your hand passes right through it!  You are just a ghost!\n" );
   return 0;
}
string short() {
   if ( !my_player )
      return "Death shadow";
   return "the ghost of "+my_player->short();
}
void dest_death_shadow() {
   destruct( this_object() );
}
int cast() {
   write( "Casting spells when you are dead?\n" );
   return 1;
}
int do_shout() {
   write( "You are dead, that is not possible.\n" );
   return 1;
}
int do_echo() {
   write( "You are dead...\n" );
   return 1;
}
int do_guild_command() {
   write( "You are dead!\n" );
   return 1;
}
int do_race_command() {
   write( "You are dead!\n" );
   return 1;
}
int score() {
   write( "You are just a disembodied spirit.  What use has a wispy thing "
         "like you have for a collection of meaningless numbers?\n" );
   return 1;
}
void second_life() {
}
mapping query_dynamic_auto_load() {
   if ( my_player ) {
      my_player->add_property( "death cost life", cost_life );
      my_player->add_property( "resurrect should add life",
                              resurrect_adds_life );
      return my_player->query_dynamic_auto_load();
   } else
      return ([ ]);
}