#include <quest_handler.h>
#include <player_handler.h>
#include <player_handler.h>
#define BACKUP_DIR "/save/creators/"
int employ_creator( string name );
int create_domain( string name , string lord );
int dismiss_creator( string str );
int eligible_creator( object player );
void backup_vaults(string, int);
void backup_bank(string, int);
void backup_quest_library(string, int);
int create_domain(string name, string lord) {
  string file;
  object *interactives;
  if (!( master()->high_programmer(previous_object(-1)) &&
        sizeof((interactives = filter(previous_object(-1),
                                      (: interactive($1) :))) ))) {
    write("Cheat!\n");
    return 0;
  }
  if ( master()->high_programmer(capitalize(name))) {
    write("Invalid name....\n");
    return 0;
  }
  if (file_size("/d/"+name) != -1) {
    write("Domain already exists (or invalid).\n");
    return 0;
  }
  if (sizeof(explode(name, "/")) > 1) {
    write("Invalid to have a / in the domain name.\n");
    return 0;
  }
  if (!PLAYER_HANDLER->test_creator(lord)) {
    write("The lord must exist.... and be a creator already.\n");
    return 0;
  }
  mkdir("/d/"+name);
  master()->add_lord(lord);
  file = read_file("/std/dom/master.c");
  write_file("/d/"+name+"/master.c", "#define LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/master.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/master.c", file);
  file = read_file("/std/dom/common.c");
  write_file("/d/"+name+"/common.c",
             "#define DOM_TITLE \"the domain of "+name+"\"\n");
  write_file("/d/"+name+"/common.c", "#define LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/common.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/common.c", file);
  file = read_file("/std/dom/loader.c");
  write_file("/d/"+name+"/loader.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/loader.c", file);
  save_object("/secure/master");
  write("Created domain "+name+".\n");
  write_file("/log/PROMOTIONS", "Domain "+name+" created with a lord of "+
             lord+" by "+geteuid(interactives[0])+" at "+ctime(time())+"\n");
  return 1;
}
int employ_creator(string name) {
  object *interactives;
  string fname;
  if (!( master()->query_lord(previous_object(-1)) &&
        sizeof((interactives = filter(previous_object(-1),
                                      (: interactive($1) :))))))
    return 0;
  if (!PLAYER_HANDLER->test_user(name)) {
    write("User does not exist.\n");
    return 1;
  }
  if (file_size("/save/creators/"+ name + "/save_file.o") > 0) {
    write( "Player file has already been backed up.\n" );
    return 1;
  }
  fname = PLAYER_HANDLER->query_player_file_name(name);
  if (file_size(fname + ".o.gz") > 0) {
    unguarded((: uncompress_file, fname + ".o.gz" :));
  }
  mkdir (BACKUP_DIR + name);
  unguarded((: cp, fname + ".o",
               "/save/creators/" + name + "/save_file.o" :));
  backup_vaults(name, 0);
  backup_bank(name, 0);
  backup_quest_library(name, 0);
  if (find_player(name)) {
    find_player(name)->set_creator(1);
    find_player(name)->save();
    tell_object( find_player( name ), "You have been employed by "+
                 capitalize( geteuid( interactives[0] ) ) +".\n" );
    tell_object( find_player( name ), "Quit and log back in to get the "
                 "creator commands.\n" );
    tell_object( find_player( name ), "Be sure to look over the "
                 "directories, especially /doc.  \"help create\" will give "
                 "you a brief list of commands.\n" );
    tell_object( find_player( name ), "Womble on, mighty frog.\n" );
  } else {
    unguarded((: write_file, fname + ".o",
                 "creator 1\nhome_dir \"/w/"+ name +"\"\n" :));
  }
  unguarded((: compress_file, fname + ".o.gz" :));
  if ( file_size( "/w/"+ name ) == -1 ) {
    unguarded((: mkdir, "/w/"+ name :));
    unguarded((: write_file, "/w/"+ name +"/workroom.c",
                 "#define CREATOR \""+ name +"\"\n" :));
    unguarded((: write_file, "/w/"+ name +"/workroom.c",
                 read_file( "/std/creator/workroom.c" ) :));
    unguarded((: cp, "/std/creator/creator_kit.o", "/w/" + name +
                 "/creator_kit.o" :));
  }
  unguarded((: write_file, "/log/EMPLOYMENT",
               sprintf( "%s: %s employed by %s\n", ctime( time() ), name,
                        (string)interactives[0]->query_name() ) :));
  write( capitalize( name ) +" employed.\n" );
  PLAYER_HANDLER->remove_cache_entry(name);
  return 2;
}
int dismiss_creator(string str) {
  string name;
  string reason;
  string fname;
  string save_file;
  object *interactives;
  if (!( master()->query_lord(previous_object(-1)) &&
        sizeof((interactives = filter(previous_object(-1),
                                      (: interactive($1) :))))))
    return 0;
  if (sscanf(str, "%s %s", name, reason) != 2) {
    notify_fail("You need to give a reason!\n");
    return 0;
  }
  if (!PLAYER_HANDLER->test_creator(name)) {
    return notify_fail(name + " is not a creator!\n");
  }
  if ( master()->query_lord(name)) {
    write( "Cannot dismiss Lords.\n" );
    return 0;
  }
  unguarded((: write_file, "/log/DISMISSALS",
               sprintf( "%s: %s dismissed by %s\nreason: %s\n",
                        ctime( time() ), name,
                        (string)interactives[0]->query_name(), reason ) :));
  fname = PLAYER_HANDLER->query_player_file_name(name);
  if (find_player(name)) {
    find_player(name)->set_creator(0);
    find_player(name)->save();
    tell_object(find_player(name),
                "You have been dismissed by "+
                capitalize( (string)interactives[0]->query_name() ) +".\n" );
    find_player(name)->quit();
    if (file_size(fname + ".o.gz") != -1) {
       unguarded((: uncompress_file, fname + ".o.gz" :));
    }
  } else {
    if (file_size(fname + ".o.gz") != -1) {
       unguarded((: uncompress_file, fname + ".o.gz" :));
    }
    unguarded((: write_file, fname+".o",
                 "creator 0\nhome_dir 0\n" :));
    unguarded((: compress_file, fname+".o" :));
  }
  write( capitalize( name ) +" dismissed.\n" );
  save_file = "/save/creators/" + name + "/save_file.o";
  if (file_size (save_file) == -1) {
    save_file = BACKUP_DIR + name + ".o";
  }
  backup_vaults (name, 1);
  backup_bank (name, 1);
  backup_quest_library (name, 1);
  if (file_size(save_file) > 0) {
    unguarded((: write_file, save_file, "last_log_on "+time()+"\n" :));
    unguarded((: cp, save_file, fname+".o" :));
    unguarded((: rm, save_file :));
    unguarded((: rm, fname+".o.gz" :));
    unguarded((: compress_file, fname+".o" :));
  }
  if(file_size("/w/"+name) == -2) {
    unguarded((: rename, "/w/"+name, "/w/.old_creators/"+name :) );
  }
  rm (save_file);
  rmdir (BACKUP_DIR + name);
  PLAYER_HANDLER->remove_cache_entry(name);
  return 1;
}
int eligible_creator( object player ) {
  int age, level;
  string age_str, reasoning;
  reasoning =
    "  You do not have a *right* to create here.  In order to enhance your\n"
    "chances to be employed, you should demonstrate by your actions that you\n"
    "are worthy.\n"
    "  If our Creators find lots of your bug, typo, and idea reports in their\n"
    "directories, then your chances are improved.  If you have been a trouble-\n"
    "maker here, your chances are very slim.  Harrassing the Lords for a\n"
    "position will not help your chances either.\n"
    "  Having access to a MUD's file system is a great responsibility.  It\n"
    "cannot be given out to strangers who have not demonstrated their trust-\n"
    "worthiness.  After investing a fair amount of your time and energy in\n"
    "playing at DiscWorld, you are less likely to try to hurt it.  This is\n"
    "why we cannot give out instant creatorships unless we know you from\n"
    "elsewhere.  Please try to be understanding about our policy.\n\n";
  age   = - ( (int) player->query_time_on() );
  level = (int)player->query_level();
  if ( ( level >= 150 ) && ( age > 432000 ) ) {
    write("  You have achieved the *minimum* requirements necessary to apply "
          "for a\n"
          "creatorship at " + mud_name() + ".  You must now pass a review of the Lords "
          "to be\naccepted.\n"+ reasoning );
    return 1;
  }
  age_str = "";
  if ( age >  86400 )
    age_str += sprintf( "%d day" , age/86400 );
  if ( age > 172800 )
    age_str += "s";
  if ( age%86400 > 3600) {
    if ( age > 86400 )
      age_str += " and ";
    age_str += sprintf( "%d hour" , (age%86400)/3600 );
  }
  if ( age%86400 > 7200)  age_str += "s";
  write("  The *minimum* requirements to apply for a creatorship on " + mud_name() + " "
        "are\nto be level 150 in your guild and at least five "
        "days old .\nYou are level " + level + ", and your age is "+
        age_str + ".\n" + reasoning );
  return 0;
}
private void backup_vaults(string name, int restore) {
  string base = "/save/vaults/";
  string creator_dir = BACKUP_DIR + name + "/vaults/";
  string *vaults, *tmp;
  string file;
  if (!restore) {
    vaults = get_dir (base);
    mkdir (creator_dir);
    foreach (string vault in vaults) {
      file = base + vault + "/" + name + ".o";
      if (file_size (file) != -1) {
        cp (file, creator_dir + "/" + vault + ".o");
      }
    }
  }
  else {
    if (file_size (creator_dir) == -1) {
      return;
    }
    vaults = get_dir (base);
    foreach (string vault in vaults) {
      file = base + vault + "/" + name + ".o";
      if (file_size (file) != -1) {
        rm (file);
      }
    }
    vaults = get_dir (creator_dir);
    foreach (string vault in vaults) {
      tmp = explode (vault, ".");
      cp (creator_dir + vault, base  + tmp[0] + "/" + name  + ".o");
      rm (creator_dir + vault);
    }
    rmdir (creator_dir);
  }
}
private void backup_bank (string name, int restore) {
  string base = "/save/bank_accounts/";
  string bank_file = base + name[0..0] + "/" + name + ".o";
  string bank_dir = BACKUP_DIR + name + "/bank_account";
  string saved_file;
  if (!restore) {
    mkdir (bank_dir);
    if (file_size (bank_file) == -1) {
      return;
    }
    cp (bank_file, bank_dir);
  }
  else {
    saved_file = bank_dir + "/" + name + ".o";
    if (file_size (bank_dir) == -1) {
      return;
    }
    rm (bank_file);
    if (file_size (saved_file) == -1) {
      return;
    }
    cp (saved_file, bank_file);
    rm (saved_file);
    rmdir (bank_dir);
  }
}
private void backup_quest_library (string name, int restore) {
  string base = "/save/library/";
  string library_file = base + name[0..0] + "/" + name + ".o";
  string library_dir = BACKUP_DIR + name + "/quest_library";
  string saved_file;
  if (!restore) {
    mkdir (library_dir);
    if (file_size (library_file) == -1) {
      return;
    }
    cp (library_file, library_dir);
  }
  else {
    saved_file = library_dir + "/" + name + ".o";
    if (file_size (library_dir) == -1) {
      return;
    }
    rm (library_file);
    if (file_size (saved_file) == -1) {
      return;
    }
    cp (saved_file, library_file);
    rm (saved_file);
    rmdir (library_dir);
  }
}