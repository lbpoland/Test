int valid_override(string file, string func, string filename) {
  string *bing;
  bing = explode(file, "/") - ({ "", "." });
  switch (bing[0]) {
    case "secure" :
      return 1;
    case "std" :
    case "obj" :
    case "simul_efun" :
    case "global" :
    case "cmds" :
      return (func != "snoop");
    default :
      return 0;
  }
}