private string home_dir;
private nosave string current_path;
string get_path(string str) {
   string *array;
   string *array1;
   string temp;
   int i;
   if (!str) {
      if(!home_dir) {
         home_dir = "/w/" + this_player()->query_name();
      }
      str = home_dir;
   }
   if (str == "~") {
      str = "w/"+this_player()->query_name();
   } else {
      if(str[0] == '~') {
         if(str[1] == '/') {
            sscanf(str, "~%s", temp);
            str = "/w/" + this_player()->query_name() + temp;
         } else {
            string name;
            if (sscanf(str,"~%s/%s",name,str)!=2) {
               name = extract(str,1);
               str = "w/"+name;
            } else {
               str = "w/"+name+"/"+str;
            }
         }
      } else {
         if (str[0] != '/') {
            str = current_path+"/"+str+"/";
         }
      }
      if (str == "/") {
         return "/";
      } else {
         array = explode(str,"/") - ({ "" }) ;
         array1 = ({ });
      }
      for (i = 0; i < sizeof(array); i++) {
         reset_eval_cost();
         if (array[i] == "..") {
           if (sizeof(array1)) {
             array1 = array1[0..<2];
           }
         } else if (array[i] != ".") {
           array1 += ({ array[i] });
         }
      }
      if (sizeof(array1)) {
         str = implode(array1, "/");
      } else {
         str = "";
      }
   }
   return "/"+str;
}
string *get_files( string str ) {
   int loop;
   int count;
   string *filenames;
   string rmpath;
   string temp1;
   string temp2;
   string *names;
   string *files;
   names = explode(str, " ")- ({ "" });
   if(sizeof(names) == 0) {
      return ({ });
   }
   filenames = ({ });
   for(count = 0; count < sizeof(names); count++) {
      str = names[count];
      str = rmpath = get_path(str);
      if(rmpath == "/") {
         filenames += ({ "/" });
         continue;
      }
      if(sscanf(rmpath, "%s/%s", temp1, temp2) == 2) {
         string *path_elements;
         path_elements = explode(rmpath, "/") - ({ "" });
         rmpath = implode(path_elements[0..sizeof(path_elements) - 2], "/");
      }
      files = get_dir(str);
      if(files) {
         int loop2;
         for(loop2 = 0; loop2 < sizeof(files); loop2++) {
            filenames += ({ rmpath + "/" + files[loop2] });
         }
      }
   }
   for(loop = 0; loop < sizeof(filenames); loop++) {
      if(filenames[loop][0] != '/') {
         filenames[loop] = "/" + filenames[loop];
      }
   }
   return filenames;
}
string *get_cfiles(string str) {
   int loop;
   string temp, *names, temp2;
   names = explode(str, " ") - ({ "" });
   for(loop = 0; loop < sizeof(names); loop++) {
      if(sscanf(names[loop], "%s.%s", temp, temp2) != 2) {
         names[loop] += ".c";
      }
   }
   str = implode(names, " ");
   return get_files(str);
}
string query_current_path() {
   return current_path;
}
string query_home_dir() {
   return home_dir;
}
protected int set_home_dir(string dir) {
   home_dir = dir;
   return 1;
}
void set_current_path(string str) {
   current_path = str;
}