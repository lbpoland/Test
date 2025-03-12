#define INV_CHECK "/d/admin/obj/inv_check"
inherit "/cmds/base";
int cmd( string filename, string switch_on) {
    switch (switch_on) {
      case "ban":
        INV_CHECK->ban_object (filename);
      break;
      case "unban":
        INV_CHECK->unban_object (filename);
      break;
      default:
        tell_object (this_player(), INV_CHECK->list_banned());
      break;
    }
    return 1;
}
mixed *query_patterns() {
    return ({ "ban <string'filename'>", (: cmd( $4[0], "ban"):),
      "unban <string'filename'>", (: cmd( $4[0], "unban"  ):),
      "list", (: cmd("", "list"):)});
}