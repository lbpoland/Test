#include "virtual.h"
void initialize_methods();
void create() {
    initialize_methods();
    seteuid(getuid());
}
void initialize_methods() {
    SERVER->add_method("c",  file_name(this_object()), "compile_c");
}
object compile_c(string name, int clone) {
    if (!clone) {
	name->go_ahead_make_my_womble();
	return efun::find_object(name);
    } else {
	return efun::clone_object(name);
    }
}