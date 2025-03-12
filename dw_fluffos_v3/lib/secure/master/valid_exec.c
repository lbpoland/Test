int valid_exec(string name) {
  if (name == "secure/login.c")
    return 1;
  if(name == "secure/nlogin.c")
    return 1;
  return 0;
}