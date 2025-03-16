private int _do_setup;
protected void inc_setup() {
   _do_setup++;
}
protected void dec_setup() {
   _do_setup--;
}
protected void do_setup() {
   if (!_do_setup) {
      this_object()->setup();
   }
}
protected void do_reset() {
   if (!_do_setup) {
      this_object()->reset();
   }
}