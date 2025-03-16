#define MAX_SIZE 50000
varargs void say(string str, mixed avoid)
{
  if (!pointerp(avoid))
    avoid = ({ this_player(), previous_object() }) + ({ avoid });
  else
    avoid += ({ this_player(), previous_object() });
  if (!environment(previous_object()))
    if(this_player() && environment(this_player()))
      event(environment(this_player()), "say", str, avoid);
    else
      event(previous_object(), "say", str, avoid);
  else
  {
    if (environment(environment(previous_object())))
      event(environment(environment(previous_object())), "say", str, avoid);
    else
      event(environment(previous_object()), "say", str, avoid);
  }
}
varargs void tell_room(object ob, string str, mixed avoid) {
  if (!ob || !objectp(ob))
    return ;
  event(ob, "say", str, avoid);
}
void tell_object(object ob, string str) {
  if (objectp(ob))
    ob->event_write(previous_object(), str);
}
object find_living(string str) {
  string nick;
  object ob;
  if (this_player() && (nick = (string)this_player()->expand_nickname(str)))
    str = nick;
  if ((ob = efun::find_living(str)))
    if ((int)ob->query_invis() == 2) {
      if (member_array(this_player()->query_name(),
                       (object *)ob->query_allowed()) == -1)
        return 0;
    }
  return ob;
}
object find_player(string str) {
  object ob;
  if ((ob = efun::find_player(str)))
    if ((int)ob->query_invis() == 2)
      if (member_array(this_player()->query_name(),
                       (object *)ob->query_allowed()) == -1)
        return 0;
  return ob;
}
void log_file(string name, string mess) {
  if (file_size("/log/"+name) > MAX_SIZE) {
    seteuid("Root");
    rm("/log/"+name+".old");
    rename("/log/"+name, "/log/"+name+".old");
  }
  seteuid("Root");
  write_file("/log/"+name, mess);
  seteuid(0);
}
#ifdef MUD_NAME
string mud_name() {
  return capitalize(MUD_NAME);
}
#endif
void cat(string file, int start_line, int number) {
  string bing;
  seteuid(geteuid(previous_object()));
  bing = read_file(file, start_line, number);
  seteuid(0);
  if (bing)
    printf("%s", bing[0..5000]);
}
#define HANDLER "/global/virtual/handler"
object clone_object(string name) {
  seteuid(geteuid(previous_object()));
  if(name[0..2] == "/d/" || name[0..1] == "d/")
    return (object)HANDLER->clone_virtual_object(name);
  return efun::clone_object(name);
}
void destruct(mixed name) {
  object obj;
  if(stringp(name)) {
    obj = find_object(name);
    if(obj->query_property("file_name"))
      HANDLER->destruct_virtual_object(obj);
    destruct(obj);
  } else if(objectp(name)) {
    if(name->query_property("file_name"))
      HANDLER->destruct_virtual_object(name);
    destruct(name);
  }
}
string file_name(object obj) {
  string name, number, file;
  name = efun::file_name(obj);
  if(sscanf(name, "%s#%s", name, number) == 2) {
    if(file = (string)obj->query_property("file_name")) {
      return file + "#" + number;
    } else {
      return name + "#" + number;
    }
  }
  return name;
}
object find_object(string str) {
  object obj;
  if(obj = efun::find_object(str))
    return obj;
  return (object)HANDLER->find_virtual_object(str);
}