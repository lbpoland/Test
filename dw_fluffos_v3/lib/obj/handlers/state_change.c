#include <state_change.h>
#define PROP "state name"
#define DATA_DIR "/obj/state_change/"
mapping table = ([ ]);
void set_amount_of_ob( object ob, int amount );
mixed query_table() { return table; }
void create() {
    string *files;
    int i;
    seteuid("/secure/master"->creator_file(file_name(this_object())));
    files = ({ "base.hdr" });
    files += get_dir(DATA_DIR + "*.dat");
    for (i = 0; i < sizeof(files); i++) {
        files[i] = DATA_DIR + files[i];
    }
    table += "/obj/handlers/data"->compile_data(files);
}
varargs object transform( object ob, string transformation, object player ) {
    string index, name;
    object ret;
    class state_change c;
    function f;
    int *weight_unit;
    if (!stringp(name = ob->query_property(PROP)))
      if (!stringp(name = ob->query_medium_alias()))
        name = ob->short();
    if ( !player )
      player = this_player();
    index = transformation + ":" + name;
    if (undefinedp(table[index]))
      return 0;
    c = table[index];
    ret = clone_object(c->result);
    foreach (f in c->func)
      evaluate(f, ob, ret, player);
    if (ret->query_continuous()) {
        if ( ob->query_continuous() || ob->query_collective() ) {
            ret->set_amount(to_int(ob->query_amount() * c->factor));
        } else {
            weight_unit = ret->query_weight_unit();
            set_amount_of_ob( ret, to_int( ob->query_weight() * c->factor *
              weight_unit[1] / weight_unit[0] ) );
        }
    } else {
        if ( ob->query_continuous() || ob->query_collective() ) {
            weight_unit = ob->query_weight_unit();
            ret->set_weight(to_int(ob->query_amount() * c->factor *
                                   weight_unit[0] / weight_unit[1]));
        } else {
            ret->set_weight(to_int(ob->query_weight() * c->factor));
        }
    }
    log_file( "STATE_CHANGE", "Changed %d amount of %s to %d amount of %s via %s.\n",
      ob->query_amount(), ob->query_medium_alias(), ret->query_amount(),
      ret->query_medium_alias(), transformation );
    return ret;
}
void set_amount_of_ob( object ob, int amount ) {
  if ( !ob )
      return;
  if ( !amount )
      ob->dest_me();
  ob->set_amount( amount );
  return;
}