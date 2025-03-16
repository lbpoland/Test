#define PEOPLER "/obj/handlers/peopler"
protected int do_gauge(string str);
int add_command(string name, object ob, string format, function func);
protected void wiz_commands() {
  add_command("gauge", this_object(), "<string>", (: do_gauge($4[0]) :));
  if(clonep())
    call_out("driver_version", 20);
}
int driver_version(){
  string old = this_object()->query_property("driver_version");
  if(!old) {
    return this_object()->add_property("driver_version", __VERSION__);
  }
  if(old != __VERSION__){
    this_object()->add_property("driver_version", __VERSION__);
    write("%^RED%^The driver has been changed to version " +
          __VERSION__ + ", see /doc/driver/Changes for more information.%^RESET%^\n");
  }
  return 1;
}
int review() {
  PEOPLER->review();
  return 1;
}
protected int do_gauge(string str) {
  int eval_cost;
  if (this_player(1) != this_object()) return 0;
  if(!str) {
    notify_fail("Usage : gauge command.\n");
    return 0;
  }
  eval_cost = command(str);
  write("\nThe command '" + str + "' took: " + eval_cost + " CPU cycles.\n");
  return 1;
}