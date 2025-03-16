#include <player_handler.h>
#define ONE_DAY (60*60*24)
#define SAVE_FILE "/save/del_pl_check"
int last_clear;
void create() {
  seteuid("Root");
  restore_object(SAVE_FILE);
  if (last_clear+ONE_DAY < time()) {
    call_out("do_delete_check", 0);
  } else {
    call_out("do_delete_check", last_clear+ONE_DAY-time());
  }
}
protected void do_delete_check() {
  string *bits;
  int i;
  mixed *rubbish;
  bits = get_dir("/players/"+DELETE_DIR+"