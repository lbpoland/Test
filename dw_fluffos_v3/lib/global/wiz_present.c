#include <obj_parser.h>
string desc_object(mixed o){
  string str;
  if (!o) return "** Null-space **";
  if (!catch(str = (string)o->short()) && str) return str;
  if (!catch(str = (string)o->query_name()) && str) return str;
  return file_name(o);
}
string desc_f_object(object o){
  string str, tmp;
  str = desc_object(o);
  if (o && str != file_name(o)) {
    if (tmp)
      str += " (" + tmp + ")";
    else
      str += " (" + file_name(o) + ")";
  }
  return str;
}
object *wzpresent2(string str, mixed onobj) {
  object *obs, ob, *obs2, obj;
  string s1;
  class obj_match result;
  if (pointerp(onobj)) {
    obs = ({ });
    foreach(ob in onobj)
      obs += wzpresent2(str,ob);
    return obs;
  }
  if (str == "all")
    return all_inventory(onobj);
  if (sscanf(str,"every %s",s1) == 1) {
    obs2 = all_inventory(onobj);
    obs = ({ });
    foreach (ob in obs2)
      if (ob->id(s1)) obs += ({ ob });
    return obs;
  }
  result = (class obj_match)match_objects_in_environments(str,onobj);
  if (result->result == OBJ_PARSER_SUCCESS ||
      result->result == OBJ_PARSER_AMBIGUOUS) {
    return result->objects;
  }
  if (obj = present(str,onobj)) return ({ obj });
  for (obj = first_inventory(onobj); obj; obj = next_inventory(obj)) {
    s1 = file_name(obj);
    if (sscanf(s1, "%*s/"+str+"#%*d") || sscanf(s1, "%*s#"+str))
      return ({ obj });
  }
  return ({ });
}
varargs object *wiz_present(string str, object onobj, int nogoout) {
  int j;
  object ob, *obs, *obs2;
  string s1, s2, *sts;
  mixed thing;
  class obj_match result;
  if (!str || !onobj)
    return ({ });
  seteuid(geteuid(this_player()));
  if(str[0] == '@') {
    if (ob = find_living(
        (string)this_player()->expand_nickname(extract(str, 1))))
      return ({ ob });
    notify_fail("Unable to find living object: "+extract(str,1)+".\n");
    return ({ });
  }
  if (str == "me") return ({ this_player() });
  if (str == "here") return ({ environment(this_player()) });
  if( str == "everyone") {
    if(!this_object()->query_lord())
      return ({ });
    obs = users();
    if(nogoout)
      return filter( obs, (: environment( $1 ) == $(onobj) :) );
    return obs;
  }
  if( str == "creators" ) {
    obs = filter( users(), (: $1->query_creator() :) );
    if(nogoout)
      return filter( obs, (: environment( $1 ) == $(onobj) :) );
    return obs;
  }
  if(str[0] == '/') {
    if (ob = find_object(str)) return ({ ob });
    if (sizeof((sts = (string *)this_player()->get_cfiles(str))))  {
      obs = ({ });
      obs = map(sts, (: find_object($1) :)) - ({0});
      return obs;
    }
    notify_fail("No loaded object: "+str+".\n");
    return ({ });
  }
  if (str[0] == '(' && str[strlen(str) - 1] == ')') {
    obs = wiz_present(extract(str,1,strlen(str) - 2),onobj);
    if (!sizeof(obs)) return obs;
    obs = map(obs, (: environment($1) :)) - ({0});
    return obs;
  }
  if (sscanf(str,"%s on %s",s1,s2) == 2 ||
      sscanf(str,"%s in %s",s1,s2) == 2) {
    obs = wiz_present(s2, onobj);
    if (!sizeof(obs)) return obs;
    obs2 = ({ });
    foreach (ob in obs)
      obs2 += wiz_present(s1, ob, 1);
    return obs2;
  }
  if (sscanf(str,"%s and %s",s1,s2) == 2) {
    obs = wiz_present(s1, onobj);
    obs2= wiz_present(s2, onobj);
    obs2 += filter(obs, (: member_array($1, $(obs2)) < 0 :));
    return obs2;
  }
  if (sscanf(str,"%s except %s",s1,s2) == 2 ||
      sscanf(str,"%s but %s",s1,s2) == 2) {
    obs = wiz_present(s1, onobj);
    obs2= wiz_present(s2, onobj);
    foreach (ob in obs2)
      while ((j=member_array(ob, obs)) > -1)
        obs = delete(obs,j--,1);
    return obs;
  }
  if (sscanf(str, "env of %s", s1) == 1) {
    obs = wiz_present(s1, onobj);
    if (!sizeof(obs)) {
       return obs;
    }
    return map(obs, (: environment($1) :)) - ({0});
  }
  if (sscanf(str, "children of %s", s1) == 1) {
    obs = wiz_present(s1, onobj);
    obs2 = ({ });
    foreach (ob in obs) {
      s1 = file_name(ob);
      sscanf(s1, "%s#%*d", s1);
      obs2 += children(s1);
    }
    return obs2;
  }
  if (sscanf(str,"player %s",s1)) {
    return ({ find_player(s1) });
  }
  if (!sizeof(obs2 = wzpresent2(str,onobj)) && !nogoout) {
    obs2 = wzpresent2(str, environment(onobj));
  }
  if (sizeof(obs2)) {
    return obs2;
  }
  result = (class obj_match)match_objects_in_environments(str,onobj);
  if (result->result == OBJ_PARSER_SUCCESS ||
      result->result == OBJ_PARSER_AMBIGUOUS) {
    return result->objects;
  }
  ob = find_living( this_player()->expand_nickname(str) );
  if( ob && ( !nogoout || ( environment(ob) == onobj ) ) )
    return ({ ob });
  if (thing = this_player()->get_obvar(str)) {
    if (objectp(thing)) return ({ thing });
    if (pointerp(thing)) {
      return filter( thing, (: objectp( $1 ) :) );
    }
  }
  if (sizeof((sts = (string *)this_player()->get_cfiles(str))))  {
    obs = ({ });
    obs = map(sts, (: find_object($1) :)) - ({0});
    return obs;
  }
  return ({ });
}