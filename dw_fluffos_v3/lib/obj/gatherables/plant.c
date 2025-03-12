inherit "/obj/gatherable";
void setup() {
    set_name("plant");
    set_short("hidden plant");
    set_long("There are all sorts of herbs and flowers here.  Use "
             "\"gather\" to collect specific types.\n");
    set_get_failure_mess("There are all sorts of flowers and herbs "
                         "around here.  Use \"gather\" to get "
                         "specific varieties.\n");
}