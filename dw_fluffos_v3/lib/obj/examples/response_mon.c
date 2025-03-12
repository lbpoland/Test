inherit "/w/pinkfish/tmp/response_mon";
object weapc;
string *tale;
void setup() {
    set_name("guard");
    add_adjective(({ "big", "gate" }));
    set_short("Big gate guard");
    set_long("This is one of the common guards of Amber.  "+
     "He looks quite big, maybe you shouldn't upset him...\n");
    set_race("human");
    set_class("fighter");
    set_level(45);
    set_al(250);
    set_gender(1);
    tale = ({ "There once was a frog with 5 legs.\n",
              "This frog was very very unhappy.\n",
              "All other frogs made fun of him.\n",
              "And no lady frog wanted to marry him.\n",
              "One day, a womble appeared, and bit one of his legs off.\n",
              "Since then the frog had 4 legs, and lived happily ever after.\n"
            });
    set_respond_to_with(([ ({ "help", "me" }) : "'I can't help you." ,
                         ({ ({ "hi","hello","greetings" }) }) :
                                      ({ "'Hello $hcname$.",
                                         "emote salutes you." }),
                            ({ ({ "remove","unwield","unhold" }),
                               ({ "axe","weapon" }) }) :
                                       "#remov",
                            ({ ({ "wield","hold" }),
                               ({ "axe","weapon" }) }) :
                                       "#wiel",
                            ({ "tell" , "story" }) :
                                      "#story" ]));
  weapc = clone_object("/obj/weapons/axe.wep");
  weapc->move(this_object());
  do_equip();
}
int remov() {
  init_command("unhold axe");
}
int wiel() {
 init_command("hold axe");
}
void story(object tpl) {
  command("'Very well, "+tpl->query_cap_name()+ " I will tell you a story.\n");
  set_stop_responding(1);
  call_out("tell_story",2,0);
}
void tell_story(int arg) {
  remove_call_out("tell_story");
  if (arg == sizeof(tale)) {
    set_stop_responding(0);
    return ;
  }
  command("'"+tale[arg]);
  call_out("tell_story",2,arg+1);
}