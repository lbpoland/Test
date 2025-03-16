inherit "/secure/simul_efun/add_a";
#if !efun_defined(add_action)
inherit "/secure/simul_efun/add_action";
#endif
inherit "/secure/simul_efun/add_command";
inherit "/secure/simul_efun/aggregate";
inherit "/secure/simul_efun/amtime";
inherit "/secure/simul_efun/array";
inherit "/secure/simul_efun/ctime_elapsed";
inherit "/secure/simul_efun/back_trace";
#if !efun_defined(dump_socket_status)
inherit "/secure/simul_efun/dump_socket_status";
#endif
inherit "/secure/simul_efun/find_match";
inherit "/secure/simul_efun/find_member";
inherit "/secure/simul_efun/find_other_call_out";
inherit "/secure/simul_efun/get_function_pointer";
inherit "/secure/simul_efun/inside_shorts";
inherit "/secure/simul_efun/mapping";
inherit "/secure/simul_efun/modified_efuns";
inherit "/secure/simul_efun/pk_check";
inherit "/secure/simul_efun/pl_to_ob";
inherit "/secure/simul_efun/process_value";
inherit "/secure/simul_efun/query_ident";
inherit "/secure/simul_efun/query_number";
inherit "/secure/simul_efun/roll_MdN";
#if !efun_defined(shuffle)
inherit "/secure/simul_efun/shuffle";
#endif
inherit "/secure/simul_efun/snoop_simul";
inherit "/secure/simul_efun/sqrt";
inherit "/secure/simul_efun/strip_colours";
inherit "/secure/simul_efun/str_inven";
inherit "/secure/simul_efun/debug";
inherit "/secure/simul_efun/unguarded";
inherit "/secure/simul_efun/virtual";
void create() {
  seteuid("Root");
  find_match::create();
}