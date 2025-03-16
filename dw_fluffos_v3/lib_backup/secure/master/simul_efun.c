string get_simul_efun() {
  string fname;
  fname = "/secure/simul_efun";
  if (catch(call_other(fname, "??"))) {
    write("Failed to load " + fname + "\n");
    shutdown();
    return 0;
  }
  return fname;
}