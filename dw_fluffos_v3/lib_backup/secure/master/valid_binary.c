int valid_save_binary(string fname) {
  string *bits;
  bits = explode(fname, "/");
  switch (bits[0]) {
    case "global" :
    case "std" :
    case "secure" :
    case "cmds" :
    case "d" :
    case "www" :
      return 1;
    case "obj" :
        return 1;
  }
  return 0;
}