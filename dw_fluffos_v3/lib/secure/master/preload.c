protected string *load_file(string fname) {
  string *bits;
  string str;
  str = read_file("/secure/config/"+fname);
  if (!str)
    return ({ });
  bits = explode(str, "\n");
  bits = filter(bits, (: $1[0] != '#' :));
  return bits;
}
string *epilog() {
  return load_file("preload");
}
void preload(string file) {
  mixed e;
  printf("Preloading: "+file+".\n");
  if ((e = catch(load_object(file)))) {
    printf("            "+e+"\n");
  }
}