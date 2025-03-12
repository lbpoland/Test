inherit "/std/room/basic_room";
#include <player_shop.h>
#include <mail.h>
private nosave class applying_player
{
    int step;
    string *answers;
}
private nosave string _inside = "",
_outside = "",
_office = "",
_counter = "",
_storeroom = "",
_mgr_office = "",
_channel;
private void abort_app(class applying_player);
private void apply(class applying_player);
private string cap_name(string);
int check_employee(string, object, string);
private void confirm_abort(string, class applying_player);
private void confirm_apply(string, string, class applying_player);
private void continue_loop(class applying_player);
string directions_to(string);
private int do_apply();
private int do_cancel();
private int do_complain();
private int do_confirm();
private int do_push();
private int do_suggestion();
private void end_app(class applying_player);
private void end_complaint(string);
private void end_suggestion(string);
private void finish_edit(string, class applying_player);
string query_office();
string query_outside();
protected void set_exit_counter(string);
protected void set_exit_out(string, string);
protected void set_office(string);
string sign_text();
int tinkle_bell(string);
void create()
{
    do_setup++;
    ::create();
    do_setup--;
    add_property("no burial", 1);
    add_property("los", "closed");
    add_property("determinate", "");
    add_item("counter", "The counter divides this room of the shop in two.  "
      "You get the feeling that only employees can pass it.  There's a "
      "%^BOLD%^card%^RESET%^ on the counter that catches your attention, "
      "next to which is a small %^BOLD%^bell%^RESET%^.");
    add_item("card", "The card seems to be a simple form.  One section "
      "seems to allow you to \"apply\" for a job here, whilst the "
      "bottom section could be filled out to make a \"suggestion\".\n"
      "If you wish to \"complain\" about an employee, you may do so here.  "
      "If you have been accepted for employment, you can also \"confirm\" "
      "you accept, or you can \"cancel\" your application at any time.");
    add_item("doorbell", "The bell above the door is positioned so that as the "
      "door passes underneath it, it will ring.");
    add_item(({"bell", "push-bell"}),
      ({"long", "This is a small push-bell for summoning the employees.",
        "push", (: do_push() :)}));
    if (!do_setup)
    {
        this_object()->setup();
        this_object()->reset();
    }
    add_help_file("player_shop_shopfront");
}
void init()
{
    string tp;
    ::init();
    if (!_office || _office == "") return;
    tp = this_player()->query_name();
    _office->summon_shopkeeper();
    add_command("complain", "", (: do_complain() :));
    add_command("suggestion", "", (: do_suggestion() :));
    if (!check_employee("void", this_player(), "void"))
        add_command("apply", "", (: do_apply() :));
    if ( _office->query_applicant(tp) == HIRED)
        add_command("confirm", "employment", (: do_confirm() :));
    if (_office->query_applicant(tp))
        add_command( "cancel", "application", (: do_cancel() :) );
}
private void abort_app(class applying_player player_info)
{
    tell_object(this_player(),
      "Are you sure you want to ABORT the application? ");
    input_to((: confirm_abort($1,$(player_info)) :), 0);
}
private void apply(class applying_player player_info)
{
    object tp = this_player();
    tell_object(tp, "\n\n");
    tell_object(tp, "%^BOLD%^Application for employment with "+
      _office->query_shop_name()+ "%^RESET%^\n\n"
      "Please note that a blank entry will abort your application.\n");
    tell_object(tp, "There are " + query_num(sizeof(APP_QUESTIONS))+
      " questions on this application form.  Please answer them all.  "
      "You will get an opportunity at the end to let us know anything "
      "else about you that seems relevant.\n\n" );
    continue_loop(player_info);
}
private string cap_name(string name)
{
    if (test_player(name))
        return PLAYER_HANDLER->query_cap_name(name);
    else return capitalize(name);
}
int check_employee(string verb, object thing, string special)
{
    if (thing->query_creator() ||
      _office->query_retired(thing->query_name())) return 1;
    return _office->query_employee(thing->query_name());
}
private void confirm_abort(string confirm, class applying_player player_info)
{
    confirm = lower_case(confirm);
    if (strlen(confirm) < 1 || (confirm[0] != 'y' && confirm[0] != 'n'))
    {
        tell_object(this_player(), "Please enter 'yes' or 'no'.\n"
          "Are you sure you want to ABORT the application? ");
        input_to((: confirm_abort($1,$(player_info)) :), 0);
        return ;
    }
    if (confirm[0..0] != "y")
    {
        continue_loop(player_info);
        return ;
    }
    tell_object(this_player(), "Application aborted.\n");
    return;
}
private void confirm_apply(string str, string message,
  class applying_player player_info)
{
    string from, *managers;
    str = lower_case( str );
    if (strlen(str) < 1 || (str[0] != 'y' && str[0] != 'n'))
    {
        tell_object(this_player(), "Are you sure you want to send "
          "the application (Yes or No)? ");
        input_to((: confirm_apply($1,$(message),$(player_info)) :), 0);
        return;
    }
    if(str[0] == 'n')
    {
        confirm_abort("y", player_info);
        return;
    }
    from = (string)this_player()->query_name();
    managers = _office->get_managers();
    if (!sizeof(managers)) managers = ({ _office->query_creator() });
    AUTO_MAILER->auto_mail(implode(managers, ","),
      _office->query_proprietor(), "Application for employment with "+
      _office->shop_very_short(), "", "There is a new application to be "
      "viewed.\nPlease vote on "+ cap_name( from )+ "'s application as "
      "soon as possible.\n", 0, 0);
    _office->add_applicant(from, message);
    tell_object(this_player(), "\nYour application has now been sent "
      "to the managers.  You will hear from us as soon as they have "
      "made a decision.  Thank you for your application, and good luck.\n");
}
private void continue_loop(class applying_player player_info)
{
    string q_str = "Question #"+(player_info->step+1)+": ";
    tell_object(this_player(), "\n%^CYAN%^" + sprintf("%s%-=*s\n",
        q_str, this_player()->query_cols() - strlen(q_str),
        APP_QUESTIONS[player_info->step]) + "%^RESET%^");
    this_player()->do_edit("", (: finish_edit($1,$(player_info)) :), 0);
}
string directions_to(string place)
{
    if (place == _counter || place == _office || place == _storeroom)
        return copy(_inside);
    return "here";
}
private int do_apply()
{
    int awaiting_vacancies = 0;
    mapping applicants;
    string tp = this_player()->query_name();
    class applying_player player_info;
    if (_office->query_applicant(tp))
    {
        tell_object(this_player(), "You've already applied here!\n");
        return 1;
    }
    if (_office->query_declined(tp))
    {
        tell_object(this_player(), "I'm sorry, but you cannot make another "
          "application just yet.\n");
        return 1;
    }
    applicants = _office->get_applicants();
    foreach (string applicant in m_indices(applicants))
    if (applicants[applicant][APP_TYPE] == AWAITING)
        awaiting_vacancies++;
    if ((awaiting_vacancies > (_office->query_maxemp() / 10)))
    {
        tell_object(this_player(), "I'm sorry, but we do not have any "
          "vacancies at the moment.  Please try again at a later date.\n");
        return 1;
    }
    player_info = new(class applying_player);
    player_info->step = 0;
    player_info->answers = ({});
    call_out((: apply($(player_info)) :), 0);
    add_succeeded_mess("");
    return 1;
}
private int do_cancel() { return _office->do_cancel(); }
private int do_complain()
{
    tell_object(this_player(), COMPLAINT_TEXT +
      "  This complaint will then be sent to the managers of the shop.  "
      "If you would rather remain anonymous to the managers, please "
      "contact a liaison, or send a mail with all the above details to "+
      cap_name(_office->query_creator())+ ".\n");
    this_player()->do_edit("%^CYAN%^"+ COMPLAINT_TEXT + "%^RESET%^\n\n",
      (: end_complaint($1) :));
    add_succeeded_mess("");
    return 1;
}
private int do_confirm() { return _office->do_confirm(); }
private int do_push()
{
    if (this_player()->query_property("shop bell pressed"))
        return notify_fail( "Calm down!  You've only just pushed it.  Try "
          "in a minute or so if there's still no reply.\n" );
    if (check_employee("void", this_player(), "void"))
        return notify_fail("There's already an employee here: You!\n");
    if (!_channel || _channel == "")
        return notify_fail( "You push the bell, but no-one can hear you.\n" );
    this_player()->add_property("shop bell pressed", 1, BELL_TIMEOUT);
    HISTORY_HANDLER->add_chat_history(_channel, "Shop: ", this_player()->
      query_short() + " called for assistance.");
    children(BADGE)->receive(_channel, "Shop", this_player()->query_short()+
      " is calling for assistance.");
    add_succeeded_mess("$N $V the bell.\n");
    return 1;
}
private int do_suggestion()
{
    tell_object(this_player(), SUGGEST_TEXT+ "\n");
    this_player()->do_edit("%^CYAN%^"+ SUGGEST_TEXT+ "%^RESET%^\n",
      (: end_suggestion($1) :));
    add_succeeded_mess("");
    return 1;
}
private void end_app(class applying_player player_info)
{
    string message = "";
    for (int i = 0; i < sizeof(APP_QUESTIONS); i++)
    {
        message += "%^CYAN%^" + sprintf("%2d) %-=*s\n", (i+1), 70,
          APP_QUESTIONS[i]) + "%^RESET%^" +
        sprintf("      %-=*s\n\n", 72, player_info->answers[i]);
    }
    tell_object(this_player(), "We have your application as:\n" + message+
      "\nDo you wish to send it? ");
    input_to((: confirm_apply($1,$(message),$(player_info)) :), 0);
}
private void end_complaint(string text)
{
    string *managers;
    if (!text)
    {
        tell_object(this_player(), "Aborted.\n");
        return;
    }
    if (!sizeof(managers = _office->get_managers()))
        managers = ({_office->query_creator()});
    AUTO_MAILER->auto_mail(implode(managers, ","),
      this_player()->query_name(), _office->shop_very_short()+ " complaint",
      "", text, 0, 0);
    tell_object(this_player(), "Your complaint has now been sent to the "
      "managers, and will be dealt with as soon as possible.\n");
}
private void end_suggestion(string text)
{
    string *managers;
    if (!text)
    {
        tell_object( this_player(), "Aborted.\n" );
        return;
    }
    if (!sizeof(managers = _office->get_managers()))
        managers = ({_office->query_creator()});
    AUTO_MAILER->auto_mail( implode( managers, "," ),
      this_player()->query_name(), _office->shop_very_short()+ " suggestion",
      "", text, 0, 0 );
    tell_object(this_player(), "Your suggestion has been sent to the "
      "managers, and will be dealt with as soon as possible.\n");
}
void event_death(object k, object *o, object k2, string r, string k3)
{
    _office->event_death(k,o,k2,r,k3);
}
void event_enter(object ob, string message, object from)
{
    mapping baddies;
    int days;
    string name = ob->query_name();
    if (_office->query_baddie(name))
    {
        baddies = _office->get_baddies();
        days = (((BAN_LENGTH*60*60*24) -
            (time() - baddies[name][2])) / (60*60*24)) + 1;
        tell_room(this_object(), ob->query_short()+
          " drifts out of the door, seemingly against "+
          ob->query_possessive()+ " will.\n", ({ob}));
        tell_object(ob, "You feel yourself pushed out of the shop by "
          "a mysterious force.\nYou have been banned from this shop for "+
          baddies[name][0]+ " and will not be re-admitted for a maximum of "+
          query_num(days)+ " days.\n");
        ob->move(_outside);
    }
}
string long(string word, int dark)
{
    int emps_in = 0;
    if (find_object(_office->query_shopkeeper()) &&
      _office->query_employee(_office->query_shopkeeper()->
        query_name()) & CLOCKED_IN)
    {
        emps_in = 1;
    }
    emps_in += _office->num_employees_in();
    return sprintf("%s%s %s currently clocked in.\n",
      ::long(word,dark), _office->employees_clocked_in(),
      (emps_in == 1)? "is" : "are");
}
private void finish_edit(string message, class applying_player player_info)
{
    if (!message || message == "")
    {
        abort_app(player_info);
        return;
    }
    player_info->answers += ({message});
    player_info->step++;
    if (player_info->step == sizeof(APP_QUESTIONS)) end_app(player_info);
    else continue_loop(player_info);
}
string query_office() { return copy(_office); }
string query_outside() { return copy(_outside); }
protected void set_exit_counter(string direction)
{
    _inside = direction;
    add_exit(direction, _counter, "hidden");
    modify_exit(direction, ({"function", "check_employee"}));
}
protected void set_exit_out(string direction, string path)
{
    _outside = path;
    add_exit(direction, path, "door");
    modify_exit(direction, ({"open/close func", ({this_object(),
          "tinkle_bell"})}));
}
protected void set_office(string path)
{
    _office = path;
    _counter = path->query_counter();
    _mgr_office = path->query_mgr_office();
    _storeroom = path->query_storeroom();
    _channel = path->query_channel();
    set_short( path->query_shop_name() );
    add_sign("A small golden plaque with engraved text.\n",
      (: sign_text :), "small plaque", "plaque",
      "common")->add_property("there", "on one wall");
}
string sign_text()
{
    string *eom = _office->query_eom();
    return sprintf("\n%%^YELLOW%%^  Employee Of The Month for %s : %s%%^RESET%%^\n\n",
       eom[0], cap_name(eom[1]));
}
int tinkle_bell(string action)
{
    tell_room(this_object(), "The bell tinkles as the door "+
      action+ "s.\n");
    tell_room(find_object(_counter), "The bell over the shop door "
      "tinkles.\n");
    tell_room(find_object(_office), "You hear the bell tinkle in "
      "the main room of the shop.\n");
    tell_room(find_object(_storeroom), "You hear the bell tinkle in "
      "the main room of the shop.\n");
    tell_room(find_object(_mgr_office), "You hear the bell tinkle in "
      "the main room of the shop.\n");
    return 1;
}