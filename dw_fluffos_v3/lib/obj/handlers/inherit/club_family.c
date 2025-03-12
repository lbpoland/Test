inherit "/obj/handlers/inherit/club_personal";
#define __CLUBS_H_NO_CLASSES
#include <clubs.h>
#include <player_handler.h>
private nosave mapping _valid_relationships;
private nosave mapping _gender_relationship;
private void add_valid_relationship(string relation,
                                    string relation2,
                                    int flags);
private void add_gender_relationship(string region,
                                     string relationship,
                                     string male,
                                     string female);
string* query_gender_relationships(string relationship);
class family_info {
   mapping relationships;
   string *never_join;
   string tmp;
   int tmp2;
}
#define CLUB_INTERFAMILY_FLAG 1
#define CLUB_JOIN_FAMILY_FLAG 2
class relationship_type_data {
   string opposite;
   int flags;
}
void create() {
   _valid_relationships = ([ ]);
   _gender_relationship = ([ ]);
   ::create();
   add_valid_relationship("spouse",
                          "spouse",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "spouse",
                           "husband",
                           "wife");
   add_valid_relationship("lover",
                          "lover",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "lover",
                           "lover",
                           "lover");
   add_valid_relationship("sibling",
                          "sibling",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "sibling",
                           "brother",
                           "sister");
   add_valid_relationship("sibling-in-law",
                          "sibling-in-law",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "sibling-in-law",
                           "brother-in-law",
                           "sister-in-law");
   add_valid_relationship("parent-in-law",
                          "child-in-law",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "parent-in-law",
                           "father-in-law",
                           "mother-in-law");
   add_gender_relationship("Ankh-Morpork",
                           "child-in-law",
                           "son-in-law",
                           "daughter-in-law");
   add_valid_relationship("child",
                          "parent",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "child",
                          "son",
                          "daughter");
   add_gender_relationship("Ankh-Morpork",
                           "parent",
                           "father",
                           "mother");
   add_valid_relationship("grandparent",
                          "grandchild",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "grandparent",
                           "grandfather",
                           "grandmother");
   add_gender_relationship("Ankh-Morpork",
                           "grandchild",
                           "grandson",
                           "granddaughter");
   add_valid_relationship("godchild",
                          "godparent",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "godchild",
                           "godson",
                           "goddaughter");
   add_gender_relationship("Ankh-Morpork",
                           "godparent",
                           "godfather",
                           "godmother");
   add_valid_relationship("uncle",
                          "niece",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "uncle",
                           "uncle",
                           "aunt");
   add_gender_relationship("Ankh-Morpork",
                           "niece",
                           "nephew",
                           "niece");
   add_valid_relationship("cousin",
                          "cousin",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "cousin",
                           "cousin",
                           "cousin");
   add_valid_relationship("master",
                          "maid",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "maid",
                           "butler",
                           "maid");
   add_gender_relationship("Ankh-Morpork",
                           "master",
                           "master",
                           "mistress");
   add_valid_relationship("apprentice",
                          "tutor",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "apprentice",
                           "apprentice",
                           "apprentice");
   add_gender_relationship("Ankh-Morpork",
                           "tutor",
                           "tutor",
                           "tutor");
   add_valid_relationship("guardian",
                          "ward",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "guardian",
                           "guardian",
                           "guardian");
   add_gender_relationship("Ankh-Morpork",
                           "ward",
                           "ward",
                           "ward");
   add_valid_relationship("ex-spouse",
                          "ex-spouse",
                          CLUB_INTERFAMILY_FLAG | CLUB_JOIN_FAMILY_FLAG);
   add_gender_relationship("Ankh-Morpork",
                           "ex-spouse",
                           "ex-husband",
                           "ex-wife");
}
protected void create_extra_data(string name) {
   class family_info f_info;
   class club_info data;
   data = (class club_info)query_club_info(name);
   if (query_club_type(name) == CLUB_FAMILY) {
      f_info = new(class family_info);
      f_info->relationships = ([ ]);
      f_info->never_join = ({ });
      data->extra_data = f_info;
   } else {
      ::create_extra_data(name);
   }
   set_club_changed(name);
}
int query_club_cost_per_period(string club_name) {
   if (is_club(club_name)) {
      if (is_family(club_name)) {
         return FAMILY_COST_PER_YEAR +
              sizeof(query_members(club_name)) * FAMILY_COST_PER_MEMBER_PER_YEAR;
      } else {
         return ::query_club_cost_per_period(club_name);
      }
   }
   return 0;
}
private class family_info query_family_info(string name) {
   class club_info data;
   if (is_family(name)) {
      data = (class club_info)query_club_info(name);
      return data->extra_data;
   }
}
void add_valid_relationship(string relation1,
                            string relation2,
                            int flags) {
   class relationship_type_data frog;
   frog = new(class relationship_type_data);
   frog->opposite = relation2;
   frog->flags = flags;
   _valid_relationships[relation1] = frog;
   frog = new(class relationship_type_data);
   frog->opposite = relation1;
   frog->flags = flags;
   _valid_relationships[relation2] = frog;
}
string query_opposite_relationship(string relation) {
   if (_valid_relationships[relation]) {
      return _valid_relationships[relation]->opposite;
   }
   return 0;
}
int is_valid_relationship(string str) {
   return _valid_relationships[str] != 0;
}
int is_valid_interfamily_relationship(string str) {
   class relationship_type_data frog;
   frog = _valid_relationships[str];
   if (frog) {
      if (frog->flags & CLUB_INTERFAMILY_FLAG) {
         return 1;
      }
   }
   return 0;
}
int is_valid_join_family_relationship(string str) {
   class relationship_type_data frog;
   frog = _valid_relationships[str];
   if (frog) {
      if (frog->flags & CLUB_JOIN_FAMILY_FLAG) {
         return 1;
      }
   }
   return 0;
}
string *query_all_valid_relationships() {
   return keys(_valid_relationships);
}
private void add_gender_relationship(string region,
                                     string relationship,
                                     string male,
                                     string female) {
   _gender_relationship[male] = relationship;
   _gender_relationship[female] = relationship;
   if (!mapp(_gender_relationship[relationship])) {
      _gender_relationship[relationship] = ([ ]);
   }
   _gender_relationship[relationship][region] = ({ male,
                                                   female });
}
string query_ungendered_relationship(string relationship) {
   if (stringp(_gender_relationship[relationship])) {
      return _gender_relationship[relationship];
   }
   if (mapp(_gender_relationship[relationship])) {
      return relationship;
   }
   return 0;
}
string *query_all_relationships() {
   return keys(_gender_relationship);
}
string query_relationship_gender(string relationship,
                                 int female,
                                 string region) {
   string rel;
   rel = query_ungendered_relationship(relationship);
   if (!rel ||
       female < 0 ||
       female > 1) {
      return 0;
   }
   if (!region || !_gender_relationship[rel][region]) {
      region = "Ankh-Morpork";
   }
   return _gender_relationship[rel][region][female];
}
private void real_add_relationship(string name,
                                   string person,
                                   string dest,
                                   string relationship) {
   class family_info womble;
   class relationship_data plum;
   womble = query_family_info(name);
   if (!womble->relationships[person]) {
      womble->relationships[person] = ({ });
   }
   plum = new(class relationship_data);
   plum->related_to = dest;
   plum->relationship = relationship;
   womble->relationships[person] += ({ plum });
   set_club_changed(name);
}
private void real_remove_relationship(string name,
                                      string person,
                                      string dest,
                                      string relationship) {
   class family_info womble;
   int i;
   womble = query_family_info(name);
   for (i = 0; i < sizeof(womble->relationships[person]); i++) {
      if (womble->relationships[person][i]->related_to == dest &&
          womble->relationships[person][i]->relationship == relationship) {
         womble->relationships[person] = womble->relationships[person][0..i-1] +
                                         womble->relationships[person][i+1..];
         set_club_changed(name);
      }
   }
}
int add_relationship(string name,
                     string person,
                     string dest_name,
                     string dest,
                     string relationship) {
   if (is_family(name) &&
       is_family(dest_name) &&
       is_member_of(name, person) &&
       is_member_of(dest_name, dest) &&
       is_valid_relationship(relationship)) {
      real_add_relationship(name,
                            person,
                            dest,
                            relationship);
      real_add_relationship(dest_name,
                            dest,
                            person,
                            query_opposite_relationship(relationship));
      save_club(name);
      return 1;
   }
   return 0;
}
class relationship_data *query_relationships(string name,
                                             string person) {
   class family_info womble;
   if (is_family(name)) {
      womble = query_family_info(name);
      if (womble->relationships[person]) {
         return womble->relationships[person];
      }
   }
   return ({ });
}
int move_family_member(string curr_family,
                       string person,
                       string dest_family) {
  class relationship_data *stuff;
  class family_info womble;
  if (is_family(curr_family) &&
      is_family(dest_family) &&
      is_member_of(curr_family, person)) {
    stuff = query_relationships(curr_family,
                                person);
    womble = query_family_info(curr_family);
    map_delete(womble->relationships, person);
    set_club_changed(curr_family);
    remove_member(curr_family, person);
    add_member(dest_family, person);
    womble = query_family_info(dest_family);
    womble->relationships[person] = stuff;
    set_club_changed(dest_family);
    return 1;
  }
  return 0;
}
string *query_relationships_to(string name,
                               string person,
                               string related) {
   class relationship_data frog;
   string *relationships;
   relationships = ({ });
   foreach (frog in query_relationships(name, person)) {
      if (frog->related_to == related) {
         relationships += ({ frog->relationship });
      }
   }
   return relationships;
}
int is_relationship(string name,
                    string person,
                    string related,
                    string relationship) {
   class relationship_data frog;
   foreach (frog in query_relationships(name, person)) {
      if (frog->related_to == related &&
          frog->relationship == relationship) {
         return 1;
      }
   }
   return 0;
}
int remove_relationship(string name,
            string person,
                        string dest_name,
      string dest,
      string relationship) {
   if (is_relationship(name, person, dest, relationship)) {
      real_remove_relationship(name,
                   person,
             dest,
             relationship);
      if (dest_name) {
         real_remove_relationship(dest_name,
                      dest,
                person,
                      query_opposite_relationship(relationship));
      }
      return 1;
   }
   return 0;
}
protected void check_family_information(string name,
                                        string member,
                                        int startup) {
   class family_info fam_data;
   string family;
   fam_data = query_family_info(name);
   if (fam_data) {
      if (member &&
         fam_data->relationships[member]) {
         family = PLAYER_HANDLER->test_family(member);
         if (!family ||
              normalise_name(family) != name) {
            if (find_player(member)) {
               find_player(member)->set_family_name(family);
            } else {
               log_file("CLUB", ctime(time()) +
                                ": removed " +
                                member + " from " + family +
                                " family deficent.\n");
               remove_member(name, member);
            }
         }
         if (!undefinedp(fam_data->relationships)) {
            map_delete(fam_data->relationships, member);
            set_club_changed(name);
         }
      }
   }
}