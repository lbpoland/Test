inherit "/obj/gatherable";
void setup() {
    set_name("rock");
    set_short("hidden rock");
    set_long("There are rocks of all shapes and sizes here.  Use "
             "\"gather\" to collect specific types.\n");
    set_get_failure_mess("There are all sorts of rocks and minerals "
                         "around here.  Use \"gather\" to get "
                         "specific varieties.\n");
}