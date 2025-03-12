#include <parse_command.h>
#include "path.h"
#define MAXATONCE 6
inherit "/std/object";
class member {
  string file;
  string short;
  string *adjectives;
  string *names;
  string *plurals;
  string long;
  int *original_number;
}
int n_alive, n_crowd, n_selection, n_cloned, n_here, n_max=MAXATONCE;
int *crowd,*selection;
mixed *here;
mixed *_m_names;
mixed *_m_plurals;
mixed *_m_adjectives;
mixed store=({});
int cnt=0;
mixed query_store() { return ({ store, cnt }); }
int lookflag=0;
int lastmatch=0;
int i_member=0;
mixed *members = ({
  new(class member,
     file : CROWD+"am_poor_beggar",
     short : "poor beggar",
     long : "This is a poor beggar.  "
     "Perhaps you should give $OBJ$ some money.\n"
     "$PRO$ is in good shape.\n"
     "$PRO$ is standing.\n",
     original_number : ({ 0,13,15 }) ),
  new(class member,
     file : CROWD+"am_diseased_beggar",
     short : "diseased beggar",
     long : "This is a diseased beggar.  "
     "Looking at the running sores covering $POSS$ body makes your skin crawl.\n"
     "$PRO$ is in good shape, considering.\n"
     "$PRO$ is standing.\n",
     original_number : ({ 0,17,2 }) ),
  new(class member,
     file : CROWD+"am_crippled_beggar",
     short : "crippled beggar",
     long : "This is a crippled beggar.  "
     "One of $POSS$ legs has wasted so that it ressembles a gnarled branch.\n"
     "$PRO$ is in good shape.\n"
     "$PRO$ is standing awkwardly.\n",
     original_number : ({ 0,6,11 }) )
});
int *query_crowd() { return ({ selection, crowd }); }
int query_n_crowd() { return n_crowd; }
int query_visible() { return n_crowd; }
int group_object() { return n_crowd-1; }
string include_gender( string long, int gender ) {
  switch ( gender ) {
  case 2:
    return
      replace( long, ({ "$POSS$","her","$OBJ$","her","$PRO$","She" }) );
  default:
    return
      replace( long, ({ "$POSS$","his","$OBJ$","him","$PRO$","He" }) );
  }
}
string long(string word, int dark) {
  int i;
  string ret="";
  if ( !lookflag ) {
    foreach (i in crowd) ret += include_gender( (members[i>>2])->long, i&3 );
    return ret;
  }
  else if ( lastmatch ==  0 ) {
    foreach (i in selection )
      ret += include_gender( (members[i>>2])->long, i&3 );
    return ret;
  }
  else if ( lastmatch > 0 ) {
    foreach (i in selection[0..(lastmatch-1)] )
      ret += include_gender( (members[i>>2])->long, i&3 );
    return ret;
  }
  else if (-lastmatch <= sizeof(selection)) {
    i = selection[-lastmatch-1];
    return include_gender( members[i>>2]->long, i&3 );
  }
  return ret;
}
string a_short() {
  string ret="";
  int i,n_match;
  string prev=file_name(previous_object(1));
  if ( prev == "/cmds/living/glance" ||
       prev == "/cmds/living/l_ook" ) {
    lookflag = 0;
    i_member = 0;
    selection = crowd;
    n_selection = n_crowd;
  }
  else if ( file_name(previous_object()) != "/cmds/living/glance" ) {
    lookflag = 0;
  }
  n_match = n_selection;
  if (lookflag && lastmatch && lastmatch < n_match)
    n_match = (lastmatch > 0 ? lastmatch : 1);
  for (i=i_member;i<n_match;i++) {
    ret+="$a_short:"+ file_name(load_object(members[selection[i]>>2]->file)) +"$";
  }
  if (lookflag) { ret = "$M$" + ret + "$M$"; }
  return ret;
}
string the_short() {
  string ret="";
  int i;
  for (i=0;i<n_crowd;i++)
    ret+="$the_short:"+ file_name( this_object() ) +"$";
  return ret;
}
string one_short() {
  string ret="";
  int i;
  for (i=0;i<n_crowd;i++)
    ret+="$one_short:"+ file_name( this_object() ) +"$";
  return ret;
}
string poss_short() {
  return a_short();
}
varargs string short(int dark) {
  return "crowd";
}
void create() {
  class member p;
  int i,j,k;
  string *tmp;
  string *adjs = ({});
  string *names = ({});
  ::create();
  set_name("beggar");
  set_short("crowd of crowd.");
  set_long("This is a crowd of people.");
  enable_commands();
  crowd = ({ });
  for (j=0; j<sizeof(members);j++) {
    p = members[j];
    tmp = explode(p->short," ");
    p->names = ({ tmp[<1] });
    p->plurals = ({ pluralize(tmp[<1]) });
    names += ({ tmp[<1] });
    p->adjectives = tmp[0..<2];
    adjs += tmp[0..<2];
    for (k=0;k<sizeof(p->original_number);k++)
      for (i=0; i<(p->original_number)[k]; i++) crowd += ({ (j<<2)+k });
  }
  crowd = shuffle(shuffle(crowd));
  n_crowd = sizeof(crowd);
  n_alive = sizeof(crowd);
  n_cloned = 0;
  here = ({ });
  n_here = 0;
  _m_names = ({});
  _m_plurals = ({});
  while(sizeof(names)) {
    _m_names += ({ names[0] });
    _m_plurals += ({ pluralize(names[0]) });
    names-= ({ names[0] });
  }
  _m_adjectives = ({});
  while(sizeof(adjs)) {
    _m_adjectives += ({ adjs[0] });
    adjs-= ({ adjs[0] });
  }
}
void crowd_member_died( ) {
  n_alive--;
  n_cloned--;
  if (!n_alive) dest_me();
}
void merge_crowd_member( object member ) {
  tell_room(environment(),"%^YELLOW%^"+sprintf("%O reabsorbed into %O", member, this_object())+"%^RESET%^\n");
  if (member && environment(member)==environment() ) {
    int i;
    for (i=0;i<sizeof(members);i++) {
      if ( base_name(member) == members[i]->file ) {
        n_cloned--;
        n_crowd++;
        n_here--;
        here -= ({ member->crowd_number() });
        n_max = MAXATONCE - ((n_here + n_cloned) >> 2);
        if ( n_max < 1 ) n_max = 1;
        crowd = ({ (i<<2)+member->query_gender() }) + crowd;
        member->dest_me();
      }
    }
  }
}
object make_member() {
  object frog;
  int i,j;
  if (i_member<0 || i_member>=sizeof(selection)) i_member=0;
  i = selection[i_member];
  j = member_array( i, crowd );
  frog = clone_object(members[i>>2]->file);
  if (frog) {
    n_crowd--;
    n_cloned++;
    n_here++;
    n_max = (n_max+1)>>1;
    n_selection--;
    crowd = crowd[0..j-1] + crowd[j+1..<1];
    selection = selection[0..i_member-1]+selection[i_member+1..<1];
    crowd = crowd[0..j-1] + crowd[j+1..<1];
    here += ({ i });
    tell_room(environment(),"%^YELLOW%^"+sprintf("Cloned %O : %i of %i selected (%i remaining)",frog,i_member+1,sizeof(selection)+1,n_crowd)+"%^RESET%^\n");
    frog->fix_gender( i&3 );
    frog->add_effect( CROWD+"crowd_merge_effect", ({ this_object(), i }) );
    frog->move( environment(this_object()) );
  }
  return frog;
}
string *parse_command_id_list() {
  return _m_names;
}
string *parse_command_plural_id_list() {
  return _m_plurals;
}
string *parse_command_adjectiv_id_list() {
  return _m_adjectives;
}
mixed query_parse_id(mixed *arr) {
   string *bits, bat;
   int i;
   selection = ({ });
   i_member = 0;
   if (!n_crowd) return 0;
   lastmatch=arr[P_THING];
   switch (query_verb()) {
   case 0:
   case "look":
   case "glance":
   case "destruct":
   case "lose":
   case "trans":
     lookflag=1;
     break;
   default:
     lookflag=0;
   }
   bits = explode(arr[P_STR]," ");
   bat = bits[<1];
   selection = copy(crowd);
   if ( member_array( bat, _m_names ) != -1 ) {
     for (i=0;i<sizeof(members);i++) {
       if ( member_array( bat, members[i]->names ) == -1)
         selection -= ({ (i<<2)+1, (i<<2)+2 });
     }
     while (sizeof(bits = bits[0..<2])) {
       bat = bits[<1];
       if ( member_array( bat, _m_adjectives ) != -1 ) {
         for (i=0;i<sizeof(members);i++) {
           if ( member_array( bat, members[i]->adjectives ) == -1)
             selection -= ({ (i<<2)+1, (i<<2)+2 });
         }
       }
     }
   }
   else if ( member_array( bat, _m_plurals ) != -1 ) {
     for (i=0;i<sizeof(members);i++) {
       if ( member_array( bat, members[i]->plurals ) == -1)
         selection-= ({ (i<<2)+1, (i<<2)+2 });
     }
     while (sizeof(bits = bits[0..<2])) {
       bat = bits[<1];
       if ( member_array( bat, _m_adjectives ) != -1 ) {
         for (i=0;i<sizeof(members);i++) {
           if ( member_array( bat, members[i]->adjectives ) == -1)
             selection -= ({ (i<<2)+1, (i<<2)+2 });
         }
       }
     }
   }
   if (!(n_selection = sizeof(selection))) return 0;
   if (lookflag) {
     if (lastmatch < 0) i_member = -lastmatch-1;
     if (arr[P_THING] == 0) return this_object();
     if (arr[P_THING] < 0) {
        arr[P_THING]+=n_selection;
        if (arr[P_THING] <0) {
          return 0;
        }
        arr[P_THING] = -10321;
        return this_object();
     }
     if (arr[P_THING] != 1) {
       i=arr[P_THING];
       if (i>n_selection) i = n_selection;
       arr[P_THING]-=i;
       if (!arr[P_THING]) arr[P_THING] = -10101;
       return this_object();
     }
     arr[P_THING] = -10101;
     return this_object();
   }
   if (arr[P_THING] == 0) {
      object *things=({ });
      i = n_max;
      if (i>n_selection) i = n_selection;
      while (i--) things += ({ make_member() });
      return things;
   }
   if (arr[P_THING] < 0) {
      i_member = -arr[P_THING]-1;
      arr[P_THING]+=n_selection;
      if (arr[P_THING] <0) {
         return 0;
      }
      arr[P_THING] = -10321;
      return make_member();
   }
   if (arr[P_THING] != 1) {
      object *things=({ });
      i=arr[P_THING];
      if (i>n_selection) i = n_selection;
      if (i>n_max) i = n_max;
      while (i--) {
         arr[P_THING]--;
	 things += ({ make_member() });
      }
      if (!arr[P_THING]) arr[P_THING] = -10101;
      return things;
   }
   arr[P_THING] = -10101;
   return make_member();
}
void event_enter( object ob, string message, object from ) {
  if (from) {
    object *things;
    n_here = sizeof( things = filter(all_inventory( environment() ),
      (: $1->crowd_object() == this_object() :) ));
    here = ({ });
    if ( n_here ) here = map( things, (: $1->crowd_number() :) );
    n_max = MAXATONCE - ((n_here + n_cloned) >> 2);
    if ( n_max < 1 ) n_max = 1;
    tell_creator("shaggy","ENTER %O: n_here: %i n_cloned: %i n_alive: %i n_crowd:%i n_max: %i %O\n",from,n_here,n_cloned,n_alive,n_crowd,n_max, here);
  }
}
void event_exit( object ob, string message, object to ) {
  object *things;
  n_here = sizeof( things = filter(all_inventory( environment() ),
     (: $1->crowd_object() == this_object() :) ));
  here = ({ });
  if ( n_here ) here = map( things, (: $1->crowd_number() :) );
  n_max = MAXATONCE - ((n_here + n_cloned) >> 2);
  if ( n_max < 1 ) n_max = 1;
  tell_creator("shaggy","EXIT: n_here: %i n_cloned: %i n_alive: %i n_crowd:%i n_max: %i %O\n",n_here,n_cloned,n_alive,n_crowd,n_max, here);
}