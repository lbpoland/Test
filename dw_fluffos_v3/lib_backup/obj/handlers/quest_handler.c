#include <library.h>
#include <player_handler.h>
#define QUEST_LOG "QUESTS"
#define SAVE_FILE "/save/quests"
#define BACKUP_FILE "/save/quests/quests"
inherit "/std/object";
private int *quest_level;
private int *num_times_done;
private int *quest_status;
private string *quest_name;
private string *quest_title;
private string *quest_story;
private string *last_done_by;
private nosave int total_qp;
void load_quests() { unguarded( (: restore_object, SAVE_FILE :) ); }
void save_quests() { unguarded( (: save_object, SAVE_FILE :) ); }
void create() {
   int i;
   ::create();
   load_quests();
   if ( !quest_name ) {
      quest_name = ({ });
   }
   if ( !quest_level ) {
      quest_level = ({ });
   }
   if ( !quest_title ) {
      quest_title = ({ });
   }
   if ( !quest_story ) {
      quest_story = ({ });
   }
   if ( !last_done_by ) {
      last_done_by = ({ });
   }
   if ( !num_times_done ) {
      num_times_done = ({ });
   }
   if ( !quest_status ) {
     if(sizeof(quest_name)) {
       quest_status = allocate(sizeof(quest_name));
       for(i=0; i<sizeof(quest_name); i++) {
         quest_status[i] = 1;
       }
     } else {
       quest_status = ({ });
     }
   }
   for(i = 0; i<sizeof(quest_level); i++) {
     if(quest_status[i]) {
       total_qp += quest_level[i];
     }
   }
}
int query_total_qp() { return total_qp; }
int add_quest( string name, int level, string title, string story ) {
   string log_name;
   if ( member_array( name, quest_name ) != -1 )
      return 0;
   quest_name += ({ name });
   quest_level += ({ level });
   quest_title += ({ title });
   quest_story += ({ story });
   last_done_by += ({ "nobody" });
   num_times_done += ({ 0 });
   quest_status += ({ 1 });
   if ( this_player() ) {
      log_name = this_player()->query_name();
   }
   else {
      log_name = file_name( previous_object() );
   }
   log_file( QUEST_LOG, log_name +
         " added: "+ name +", "+ level +", "+ title +", "+ story +"\n" );
   save_quests();
   unguarded( (: cp, SAVE_FILE +".o", BACKUP_FILE +"."+ time() :) );
   total_qp += level;
   return 1;
}
int change_quest_status(string name) {
  int temp;
  temp = member_array(name, quest_name);
  if(temp == -1) {
    return -1;
  }
  quest_status[temp] = !quest_status[temp];
  return quest_status[temp];
}
int query_quest_status(string name) {
  int temp;
  temp = member_array(name, quest_name);
  if(temp == -1) {
    return -1;
  }
  return quest_status[temp];
}
int query_quest_level(string name) {
  int temp;
  temp = member_array(name, quest_name);
  if(temp == -1) {
    return -1;
  }
  return quest_level[temp];
}
int set_quest_level(string name, int level) {
   int temp;
   string log_name;
   temp = member_array(name, quest_name);
   if(temp == -1) {
      return 0;
   }
   if ( this_player() ) {
      log_name = this_player()->query_name();
   }
   else {
      log_name = file_name( previous_object() );
   }
   log_file(QUEST_LOG, "%s : level set for %s to %d\n\n",
            log_name, name, level);
   quest_level[ temp ] = level;
   save_quests();
   return 1;
}
string query_quest_story(string name) {
  int temp;
  temp = member_array(name, quest_name);
  if(temp == -1) {
    return "did nothing";
  }
  return quest_story[temp];
}
int set_quest_story(string name, string story) {
   int temp;
   string log_name;
   temp = member_array(name, quest_name);
   if(temp == -1) {
      return 0;
   }
   if ( this_player() ) {
      log_name = this_player()->query_name();
   }
   else {
      log_name = file_name( previous_object() );
   }
   log_file(QUEST_LOG, "%s : story set for %s to %s\n\n",
            log_name, name, story);
   quest_story[ temp ] = story;
   save_quests();
   return 1;
}
string query_quest_title(string name) {
  int temp;
  temp = member_array(name, quest_name);
  if(temp == -1 || quest_title[temp] == "") {
    return "Unknown Quester";
  }
  return quest_title[temp];
}
int set_quest_title(string name, string title) {
   int temp;
   string log_name;
   temp = member_array(name, quest_name);
   if(temp == -1) {
      return 0;
   }
   if ( this_player() ) {
      log_name = this_player()->query_name();
   }
   else {
      log_name = file_name( previous_object() );
   }
   log_file(QUEST_LOG, "%s : title set for %s to %s\n\n",
            log_name, name, title);
   quest_title[ temp ] = title;
   save_quests();
   return 1;
}
int query_quest_times( string name ) {
   int i;
   i = member_array( name, quest_name );
   if ( i == -1 )
      return -1;
   return num_times_done[ i ];
}
mixed query_quest_done( string name ) {
   int i;
   i = member_array( name, quest_name );
   if ( i == -1 )
      return -1;
   return last_done_by[ i ];
}
int delete_quest(string name) {
   int temp;
   string log_name;
   if ( this_player() ) {
      log_name = this_player()->query_name();
   }
   else {
      log_name = file_name( previous_object() );
   }
   log_file(QUEST_LOG, log_name + " removed : " +
            name + "\n\n");
   temp = member_array(name, quest_name);
   if(temp == -1) {
      return 0;
   }
   total_qp -= quest_level[temp];
   quest_name = delete(quest_name, temp, 1);
   quest_level = delete(quest_level, temp, 1);
   quest_title = delete(quest_title, temp, 1);
   quest_story = delete(quest_story, temp, 1);
   last_done_by = delete( last_done_by, temp, 1 );
   num_times_done = delete( num_times_done, temp, 1 );
   save_quests();
   return 1;
}
string *query_quest_names() {
  return quest_name + ({ });
}
int *query_quest_levels() {
  return quest_level + ({ });
}
string *query_quest_titles() {
  return quest_title + ({ });
}
string *query_quest_stories() {
  return quest_story + ({ });
}
void quest_completed( string name, string quest, object prev_ob ) {
   int i;
   string word;
   log_file( QUEST_LOG, ctime( time() ) +" "+ name +" completed "+
         quest +"\n" );
   user_event( "inform", name +" completes "+ quest, "quest" );
   if ( file_name( previous_object() ) != LIBRARY ) {
      prev_ob = previous_object();
   }
   word = (string)prev_ob->query_name();
   if ( !word ) {
      word = file_name( prev_ob );
   } else {
      word += " ("+ file_name( prev_ob ) +")";
   }
   log_file( QUEST_LOG, "given by "+ word +"\n" );
   i = member_array( quest, quest_name );
   if ( i == -1 ) {
      log_file( QUEST_LOG, "non existent quest\n" );
      return;
   }
   last_done_by[ i ] = name;
   num_times_done[ i ]++;
   save_quests();
}
int query_player_fame(string name){
   int playerqp, rank;
   if (!name){
      return 0;
   }
   if (this_player()){
      name = (string)this_player()->expand_nickname(name);
   }
   if (!PLAYER_HANDLER->test_user(name)){
      return 0;
   }
   playerqp = (int)LIBRARY->query_quest_points(name);
   rank = ( playerqp * 125 ) / query_total_qp();
   return rank;
}
string query_fame_str( string name ) {
   switch ( query_player_fame( name ) ) {
      case 0 .. 4 :
         return "completely unknown";
      case 5 .. 14 :
         return "unknown";
      case 15 .. 24 :
         return "unknown";
      case 25 .. 34 :
         return "moderately well known";
      case 35 .. 44 :
         return "well known";
      case 45 .. 54 :
         return "very well known";
      case 55 .. 64 :
         return "known throughout the region";
      case 65 .. 74 :
         return "famous";
      case 75 .. 84 :
         return "renowned";
      case 85 .. 94 :
         return "Disc renowned";
      default :
         return "so renowned that no introduction is needed";
   }
}
string *query_player_story(string name){
   string *quests;
   string *story;
   int i;
   story = ({ });
   if (!name){
      return ({ });
   }
   if (this_player()){
      name = (string)this_player()->expand_nickname(name);
   }
   if (!PLAYER_HANDLER->test_user(name)){
      return 0;
   }
   quests = query_quest_names();
   if (sizeof(quests) == 1){
      story = ({"Is an under achiever."});
   }
   else{
      for(i=0;i<sizeof(quests);i++){
         if (LIBRARY->query_quest_done(name, quests[i])){
            story = ({ query_quest_story( quests[ i ] ) }) + story;
         }
      }
   }
   return story;
}
void print_some_stats()  {
   int i;
   for (i = 0; i < sizeof(quest_name); i++)
      printf("%s: %6d, %3d\n", quest_name[i], num_times_done[i], quest_level[i]);
}