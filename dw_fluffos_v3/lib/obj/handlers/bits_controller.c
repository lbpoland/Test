#include <bits_controller.h>
object *bits;
private void do_update();
void create() {
  bits = ({ });
}
void add_bit(object ob) {
  if (!sizeof(bits))
    call_out( (: do_update() :), TIME_OUT);
  bits += ({ ob });
}
void remove_bit(object ob) {
  int i;
  if ((i = member_array(ob, bits)) == -1)
    return ;
  bits = delete(bits, i, 1);
}
private void do_update() {
  int i;
  bits = bits - ({ 0 });
  if (sizeof(bits))
    call_out((: do_update() :), TIME_OUT);
  for (i = sizeof(bits) - 1; i > -1; i--) {
    reset_eval_cost();
    bits[i]->do_decay();
  }
  bits = bits - ({ 0 });
}
int query_num_bits() { return sizeof(bits); }
object *query_bits() { return bits; }
void kickstart() {
  do_update();
}