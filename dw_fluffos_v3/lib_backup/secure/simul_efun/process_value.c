string *pattern = ({
  "\\|", " *[0-9]+ *", ".*"
});
#define PV_BAR 2
#define PV_INT 3
#define PV_STR 4
#define PV_QUOTED 5
int *token = ({ 2, 3, 4 });
mixed process_value(string s) {
  string func, file, arg;
  mixed assoc, params;
  object ob;
  int i;
  if (sscanf(s, "%s|%s", func, arg) == 2) {
  } else {
    func = s;
    arg = 0;
  }
  if (sscanf(func, "%s:%s", func, file) == 2) {
    if (!objectp(ob = find_object(file)))
      return 0;
  } else {
    ob = this_object();
  }
  params = ({ func });
  if (stringp(arg)) {
    assoc = reg_assoc(arg, pattern, token);
    for (i = 0; i < sizeof(assoc[0]); i++) {
      if ((assoc[0][i] == "") && (assoc[1][i] == 0)) {
        assoc[0] = assoc[0][0..i  - 1] + assoc[0][i + 1..];
        assoc[1] = assoc[1][0..i  - 1] + assoc[1][i + 1..];
      } else if (assoc[1][i] == 0) {
        write("process_value: syntax error: " + assoc[0][i] + "\n");
        return 0;
      }
    }
    for (i = 0; i < sizeof(assoc[0])-1; i++) {
      if ((assoc[1][i+1] == PV_BAR)
          && (strsrch(assoc[0][i], "\\", -1) == strlen(assoc[0][i])-1)) {
        assoc[0][i] = assoc[0][i][0..sizeof(assoc[0][i])-2];
        if (i+2 < sizeof(assoc[0])) {
          assoc[0][i] += assoc[0][i+1] + assoc[0][i+2];
          assoc[0] = assoc[1][0..i] + assoc[1][i + 2..];
        } else {
          assoc[0][i] += assoc[0][i+1];
          assoc[0] = assoc[1][0..i] + assoc[1][i + 2..];
        }
      }
    }
    for (i = 0; i < sizeof(assoc[0]); i++) {
      switch (assoc[1][i]) {
      case PV_BAR:
        break;
      case PV_INT:
        params += ({ to_int(assoc[0][i]) });
        break;
      case PV_STR:
      case PV_QUOTED:
        params += ({ assoc[0][i] });
        break;
      default:
      }
    }
  }
  return call_other( ob, params );
}
string process_string(string s) {
  string *ss, proc;
  int i;
  ss = explode(s, "@@");
  if (strsrch(s, "@@") == 0)
    ss = ({ "" }) + ss;
  for (i = 1; i < sizeof(ss); i += 2) {
    proc = process_value(ss[i]);
    if (stringp(proc))
      ss[i] = proc;
  }
  return implode(ss, "");
}