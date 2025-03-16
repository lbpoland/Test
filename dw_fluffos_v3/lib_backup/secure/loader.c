string *pre_load;
void create() {
  int i;
  string domain;
  foreach(domain in "/secure/master"->query_domains()) {
    unguarded((: restore_object, "/d/"+ domain + "/loader" :));
    if (!pre_load)
      pre_load = ({ });
    for (i=0;i<sizeof(pre_load);i++) {
      if(pre_load[i] && explode(pre_load[i], "/")[1] != domain)
        printf("invalid " + domain + " preload: " + pre_load[i] +
               "\n");
      else {
        printf(domain +" pre_loading "+pre_load[i]+".\n");
        if(catch(call_other(pre_load[i], "??")))
          call_out("do_load", 0, pre_load[i]);
      }
    }
  }
}
void do_load(string str) {
  call_other(str, "??");
}
private int validate(string domain, object who) {
  string name;
  if(member_array(domain, "/secure/master"->query_domains()) == -1)
    return 0;
  if(!userp(who) || !interactive(who))
    return 0;
  name = who->query_name();
  if(!!"/secure/master"->query_trustee(name) &&
     !"/secure/master"->is_leader_of(name, domain) &&
     !"/secure/master"->is_deputy_of(name, domain))
    return 0;
  return 1;
}
int add_pre_load(string domain, string str) {
  if(!validate(domain, previous_object(1)))
    return 0;
  if(explode(str, "/")[1] != domain)
    return 0;
  unguarded((: restore_object, "/d/"+ domain + "/loader" :));
  if (!pre_load)
    pre_load = ({ });
  if (member_array(str, pre_load) == -1)
    pre_load += ({ str });
  save_object("/d/" + domain + "/loader");
  return 1;
}
int remove_pre_load(string domain, string str) {
  int i;
  if(!validate(domain, previous_object(1)))
    return 0;
  unguarded((: restore_object, "/d/"+ domain + "/loader" :));
  if (!pre_load)
    pre_load = ({ });
  if ((i=member_array(str, pre_load)) == -1)
    return 0;
  pre_load = delete(pre_load, i, 1);
  save_object("/d/" + domain + "/loader");
}
string *query_pre_load(string domain) {
  if(member_array(domain, "/secure/master"->query_domains()) == -1)
    return ({ });
  unguarded((: restore_object, "/d/"+ domain + "/loader" :));
  if (!pre_load)
    pre_load = ({ });
  return pre_load;
}