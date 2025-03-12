#include <creator.h>
inherit "/cmds/base";
mixed cmd(string str) {
  object *ob, thing;
  mixed *ob1, *thing1;
  string s, bing;
  string long_fields, temp;
  int long_length;
  bing = "";
  str = (string)this_player()->expand_nickname(str);
  ob = WIZ_PRESENT->wiz_present(str, this_player());
  if (!sizeof(ob)) {
    write("No such object.\n");
    return 1;
  }
  foreach (thing in ob) {
    ob1 = (mixed *)thing->stats();
    if (!pointerp(ob1))
      continue;
    s = "";
    long_fields = "";
    long_length = ( (int)this_player()->query_cols() / 3 ) - 1;
    foreach (thing1 in (pointerp(ob1[0][0])?ob1[0]:ob1)) {
      if (thing1[1]) {
        temp = thing1[0] +": "+ sprintf("%O", thing1[1]) +"\n";
        if (strlen(temp) > long_length) {
          long_fields += temp;
        } else {
          s += temp;
        }
      }
    }
    bing += sprintf("%-*#s\n", this_player()->query_cols(), long_fields) +
      sprintf( "%-*#s\n", this_player()->query_cols(), s );
  }
  this_player()->more_string(bing, "Stat");
  return 1;
}