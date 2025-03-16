inherit "/cmds/report_base";
void create() {
   ::create();
   set_error_type("BUG");
   set_use_last_error(1);
}