private mixed _processes;
void create() {
   _processes = ([ ]);
}
mapping query_processes() {
   return _processes;
}
mapping query_processes_nocase() {
  mapping lc_processes = ([]);
  filter( this_object()->query_processes(),
                 (: $3 += ([ lower_case( $1 ) : $2 ]) :), lc_processes );
  return lc_processes;
}
int add_process(string name, string ob) {
   _processes[name] = ob;
   return 1;
}
int remove_process(string name) {
  string process, name_lc;
  name_lc = lower_case(name);
  foreach (process in keys(_processes)) {
     if (lower_case(process) == name_lc) {
        map_delete(_processes, process);
     }
  }
  return 1;
}
string query_process( string word ) {
   return _processes[word];
}
protected void reset_processes() {
   _processes = ([ ]);
}