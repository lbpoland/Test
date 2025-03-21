int gender;
nosave int womens_day;
int query_female() { return (gender == 2) || womens_day; }
int query_gender() { return (womens_day?2:gender); }
int query_male() { return gender == 1 && !womens_day; }
int query_neuter() { return !gender && !womens_day; }
string query_gender_string() {
    if (!gender && !womens_day) return "neuter";
    else if (gender == 1 && !womens_day) return "male";
    else return "female";
}
string query_gender_title() {
    if (!gender && !womens_day) return "creature";
    else if (gender == 1 && !womens_day) return "sir";
    else return "madam";
}
string query_gender_name() {
    if (!gender && !womens_day) return "neuter";
    else if (gender == 1 && !womens_day) return "man";
    else return "woman";
}
string query_objective() {
    if (!gender && !womens_day)
        return "it";
    else if (gender == 1 && !womens_day)
        return "him";
    else return "her";
}
string query_possessive() {
    if (!gender && !womens_day)
        return "its";
    else if (gender == 1 && !womens_day)
        return "his";
    else return "her";
}
string query_pronoun() {
    if (!gender && !womens_day)
        return "it";
    else if (gender == 1 && !womens_day)
        return "he";
    else return "she";
}
void set_gender(mixed arg) {
  if(stringp(arg)) {
    if(arg == "male")
      gender = 1;
    else if(arg == "female")
      gender = 2;
    else
      gender = 0;
  } else {
    gender = arg;
  }
}
void set_womens_day(int bing) {
  womens_day = bing;
}
int query_womens_day() {
    return womens_day;
}
nomask int query_real_gender() {
   return gender;
}