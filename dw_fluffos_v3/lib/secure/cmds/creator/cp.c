inherit "/cmds/base";
mixed cmd(string str) {
  string *filenames, dest, *fnames, dstr;
  int loop, fs;
  if(!str)
    return notify_fail("Usage : cp file [file|dir...]\n");
  fnames = explode(str, " ");
  filenames = this_player()->get_files(implode(fnames[0..sizeof(fnames) -2],
                                               "/"));
  filenames = filter(filenames, (:$1[<1] != '.':));
  if(!sizeof(filenames)) {
    notify_fail("Usage : cp file [file|dir...]\n");
    return 0;
  }
  dest = fnames[sizeof(fnames) - 1];
  dest = this_player()->get_path(dest);
  if(!dest) {
    write("No destination\n");
    return 1;
  }
  for(loop = 0; loop < sizeof(filenames); loop++) {
    str = filenames[loop];
    if(!master()->valid_copy(str, geteuid(this_player()), ""))
      return notify_fail("Permission denied.\n");
    fs = file_size(dest);
    if(fs == -2) {
      string *names;
      names = explode(str, "/");
      fs = file_size(dest + "/" + names[sizeof(names) - 1]);
      if(fs != -1) {
        write("file exists " + dest + "/" + names[sizeof(names) - 1] + "\n");
        continue;
      }
      dstr = dest + "/" + names[sizeof(names) - 1];
    } else {
      if(fs != -1) {
        write("File exists : " + dest + "\n");
        continue;
      }
      dstr = dest;
    }
    switch(cp(str, dstr)) {
    case 1:
      write(str + " copied to " + dstr + ".\n");
      break;
    case -1:
      write(str + " is unreadable.\n");
      break;
    case -2:
      write(dstr + " is unreadable.\n");
      break;
    case -3:
      write("I/O error copying " + str + " to " + dstr + ".\n");
      break;
    }
  }
  return 1;
}