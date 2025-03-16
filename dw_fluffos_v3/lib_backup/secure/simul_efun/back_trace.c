string back_trace() {
  string ret = "", *progs, *funcs, *obs, name;
  int i;
  progs = map(call_stack(0), (: $1[1..<3] :));
  obs = map(call_stack(1), (: file_name($1)[1..] :));
  funcs = call_stack(2);
  i = sizeof(progs);
  ret = "Time: " + ctime(time()) + "\n";
  while (i-- > 1) {
    if (objectp(obs[i]))
      name = obs[i]->query_name();
    if (!name)
      name = "null";
    if (obs[i] == progs[i])
      ret += sprintf("%s() in /%s (%s)\n", funcs[i], progs[i], name);
    else
      ret += sprintf("%s() in inherited file /%s in /%s (%s)\n", funcs[i],
                     progs[i], obs[i], name);
    name = 0;
  }
  return ret;
}