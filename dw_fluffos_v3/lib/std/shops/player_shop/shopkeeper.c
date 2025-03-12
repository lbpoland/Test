inherit "/obj/monster";
#include <player_shop.h>
#include <money.h>
#include <living.h>
#include <move_failures.h>
#define set_busy(O) (_busy = O)
#define reset_busy() (_busy = 0)
#define NOT_EIGHT (({ "between seven and nine", \
                     "just over seven", \
                     "just under nine", \
                     "seven plus one", \
                     "nine minus one", \
                     "two times four", \
                  })[random(5)])
#define num_str(i) ((i == 8)?NOT_EIGHT:query_num(i))
#define DEARIE (", "+ _dearie[random(sizeof(_dearie)-1)])
private nosave object _busy = 0;
private nosave mixed _info = 0;
private nosave string _office = "",
_storeroom = "",
_shop_front = "",
_counter = "",
_place = "",
_smallest_in,
_smallest_plural_in,
*_dearie = ({""});
private nosave int * _work_hrs = ({9,0,17,30,}),
_smallest_value_in,
_failed = 0;
private nosave mapping _values_sing = ([]),
_values_plural = ([]);
private void announce_number();
private void announce_price();
private void buy_something(object *);
private void check_money(mixed);
private void deposit_money();
int do_buy(string);
int do_browse(string);
int do_list(mixed  *);
int do_sell(object *);
private void end_shift();
private void get_from_store();
private void get_money();
private void get_more_stuff();
private void give_stuff();
private void how_many(string);
private void how_much(string);
private void look_chart();
private void look_how_much();
private void no_coins();
private int outside_hours(int);
private void put_in_store();
private int query_busy();
string query_office();
private void say_to_room(object, string, string);
private void sell_something(string);
protected object * item_test(object *);
protected void set_dearie(string *);
void set_failed(int);
protected void set_office(string);
protected void set_work_hours(int *);
void shuffle_to(string,function);
private int sort_keys(string, string, int);
void start_shift();
private void taken_over();
private void what_items();
void create()
{
    do_setup++;
    ::create();
    do_setup--;
    add_property("determinate", "");
    add_property("unique", 1);
    add_property("run away", -1);
    add_alias("shopkeeper");
    if (!do_setup)
    {
        this_object()->setup();
        this_object()->reset();
    }
}
private void announce_number()
{
    if (stringp(_info))
    {
        int number = _storeroom->query_num_items(_info);
        if (!number) do_command("'I'm afraid we don't have any "+ _info +
              " in stock"+ DEARIE+ ".");
        else do_command("'You're in luck"+ DEARIE+ ".  We have "+
              num_str(number) + " in stock.");
    }
    reset_busy();
    _info = 0;
}
private void announce_price()
{
    if (stringp(_info))
        do_command("'We sell "+ _info + " for "+
          num_str(_office->query_sell(_info))+ " "+ _smallest_plural_in+
          " each, and buy them for "+ num_str(_office->query_buy(_info))+
          " "+ _smallest_plural_in + " each.");
    reset_busy();
    _info = 0;
}
void attack_by(object baddie)
{
    if (_office == "") return;
    this_object()->stop_fight(baddie);
    baddie->stop_fight(this_object());
    do_command("'Why are you attacking me, "+ baddie->query_cap_name()+ "?");
    do_command("'I'm not staying here for this!");
    do_command(_office->query_channel()+ "@ is being attacked by "+
      baddie->query_cap_name()+ ".");
    call_out("shuffle_to", NPC_DELAY, _office, (: end_shift() :));
    _office->event_death(this_object(), 0, baddie, 0, 0);
#ifdef DEBUG
    tell_creator(CREATOR,  "Attacked by %s.\n", baddie->query_short());
#endif
}
private void buy_something(object *obs)
{
    int spare, number, amount = 0;
    object *give_back, cont = clone_object("/std/container");
    obs->move(cont);
    _info = ({});
    foreach(string item in _office->query_list_array())
    _info += ((class obj_match)match_objects_in_environments(item, cont))->objects;
    give_back = obs - _info;
    if (sizeof(give_back))
    {
        give_back->move(_busy);
        do_command("'I'm afraid I can't buy "+
          query_multiple_short(give_back)+ " from you"+ DEARIE+ ".");
    }
    if (number = sizeof(_info))
    {
        if (_info[0]->query_collective())
            number = _info[0]->query_amount();
    }
    if (number > (MAX_INVEN + query_dex()))
    {
        _info->move(_busy);
        do_command("'I'm sorry"+ DEARIE+ ", but I can only carry "+
          num_str(MAX_INVEN+ query_dex())+ " items.");
        cont->dest_me();
        reset_busy();
        return;
    }
    give_back = ({});
    give_back = filter(_info, (: ($1)->query_continuous() :));
    if (sizeof(give_back))
    {
        _info -= give_back;
        do_command("'I have nothing to carry "+
          query_multiple_short(give_back)+ " in.");
        give_back->move(_busy);
    }
    give_back = item_test(_info);
    if (sizeof(give_back))
    {
        give_back->move(_busy);
        _info -= give_back;
    }
    if (!(number = sizeof(_info)))
    {
        do_command("'You don't have anything to sell"+ DEARIE+ ".");
        cont->dest_me();
        reset_busy();
        return;
    }
    if (_info[0]->query_collective())
        number = _info[0]->query_amount();
#ifdef DEBUG
    tell_creator(CREATOR,  "Checking stock.\n");
#endif
    spare = _office->query_max(pluralize(_info[0]->query_name())) -
    _office->query_stock(pluralize(_info[0]->query_name()));
    if (spare < 1)
        foreach(string alias in _info[0]->query_alias())
    {
        int check_spare;
        if((check_spare = _office->query_max(pluralize(alias)) -
            _office->query_stock(pluralize(alias))) > 0)
            spare = check_spare;
    }
    if (spare < 1)
        spare = _office->query_max(pluralize(_info[0]->query_short())) -
        _office->query_stock(pluralize(_info[0]->query_short()));
    if (spare < 1)
    {
        do_command("'I'm afraid we don't need any of those"+ DEARIE+ ".");
        _info->move(_busy);
        cont->dest_me();
        reset_busy();
        return;
    }
    if (number > spare)
    {
        do_command("'I'm afraid we don't need that many"+ DEARIE+
          ", but I could take "+ num_str(spare)+ " from you.");
        _info->move(_busy);
        cont->dest_me();
        reset_busy();
        return;
    }
#ifdef DEBUG
    tell_creator(CREATOR,  "Checking money.\n");
#endif
    foreach(string item in _office->query_list_array())
    {
obs = ((class obj_match)match_objects_in_environments(item, this_object()))->objects;
        if (number = sizeof(obs))
        {
            if (obs[0]->query_collective())
                number = obs[0]->query_amount();
            amount += _office->query_buy(item) * number;
        }
        if (_counter->query_register() < amount * _smallest_value_in)
        {
            do_command("'I'm afraid we don't have enough money to buy "+
              query_multiple_short(_info) + " from you" + DEARIE+ ".");
            _info->move(_busy);
            cont->dest_me();
            reset_busy();
            return;
        }
    }
    give_back = ({});
#ifdef DEBUG
    tell_creator(CREATOR,  "Checking we can carry it.\n");
#endif
    if (sizeof(_info))
    {
        obs = _info;
        foreach(object thing in obs)
        if ((int)thing->move(this_object()) != MOVE_OK)
        {
#ifdef DEBUG
            tell_creator(CREATOR,  "Can't carry %O.\n", thing);
#endif            _info -= ({ thing });
            give_back += ({ thing });
        }
        tell_room(environment(this_object()), query_short()+
          " takes "+ query_multiple_short(_info) +".\n");
    }
    obs = all_inventory(cont) - give_back;
    if (sizeof(give_back))
    {
        do_command("'I cannot carry "+ query_multiple_short(give_back, "the")
          +DEARIE+".");
        give_back->move(_busy);
    }
    if (sizeof(obs))
    {
        do_command("'I'm afraid we can't buy "+
          query_multiple_short(obs, "the") +" from you"+ DEARIE+ ".");
        obs->move(_busy);
    }
    obs = all_inventory(cont);
    if (sizeof(obs)) obs->move(environment(_busy),
          "$N manage$s to get knocked onto the floor.");
    if (sizeof(_info))
    {
#ifdef DEBUG
        tell_creator(CREATOR,  "Buying: %O\n", _info);
#endif
        do_command("'I'll be right back.");
        call_out("shuffle_to", NPC_DELAY, _counter, (: get_money() :));
    }
    else reset_busy();
    cont->dest_me();
}
private void check_money(mixed monies)
{
#ifdef DEBUG
    tell_creator(CREATOR, "Buying %d %s for %d each - total %d.\n", monies[1],
      monies[2], monies[3], monies[0] );
#endif
    if (monies[0] > query_value_in(_place))
    {
#ifdef DEBUG
        tell_creator(CREATOR, "No correct change (%d).\n", query_value_in(_place));
#endif
        do_command("put coins in register");
        call_out("shuffle_to", NPC_DELAY, _shop_front, (: no_coins() :));
        return;
    }
    do_command("log shop bought "+ monies[1] +" "+ monies[2] +
      " for "+ (monies[3] * monies[1]));
#ifdef DEBUG
    tell_creator(CREATOR, "Total: %d   My value: %d\n", monies[0],
      query_value_in( _place ) );
#endif
    call_out("shuffle_to", NPC_DELAY, _storeroom, (: put_in_store() :));
}
private void deposit_money()
{
    if (pointerp(_info))
    {
        do_command("log shop sold "+ _info[1]+ " "+ _info[0]+ " for "+
          _info[2]);
        do_command("put coins in register");
    }
    call_out("shuffle_to", NPC_DELAY, _storeroom, (: get_from_store() :));
}
int do_buy(string stuff)
{
#ifdef DEBUG
    tell_creator(CREATOR,  "In do_buy()\n");
#endif
    if (outside_hours(TRUE)) return 1;
    say_to_room(this_player(), "say", "I would like to buy "+ stuff +
      ", please.\n%^RESET%^");
    if (query_busy())
        init_command(":seems busy at the moment.", NPC_DELAY);
    else
    {
        set_busy(this_player());
        call_out((: sell_something($(stuff)) :), NPC_DELAY);
    }
    return 1;
}
int do_browse(string item)
{
#ifdef DEBUG
    tell_creator(CREATOR,  "In do_browse()\n");
#endif
    if (outside_hours(TRUE)) return 1;
    say_to_room(this_player(), "ask", "How much do "+ item +" cost?\n");
    if (query_busy())
        init_command(":seems busy at the moment.", NPC_DELAY);
    else
    {
        set_busy(this_player());
        call_out((: how_much($(item)) :), NPC_DELAY);
    }
    return 1;
}
int do_list(mixed *args)
{
#ifdef DEBUG
    tell_creator(CREATOR,  "In do_list()\n");
#endif
    if (outside_hours(TRUE)) return 1;
    if (!sizeof(args) || !args[0] || args[0] == "")
    {
        say_to_room( this_player(), "ask", "What items do you buy and sell?\n");
        if (query_busy())
            init_command(":seems busy at the moment.", NPC_DELAY);
        else
        {
            set_busy(this_player());
            call_out((: what_items() :), NPC_DELAY);
        }
        return 1;
    }
    say_to_room(this_player(), "ask", "How many "+ args[0]+ " do you have?\n");
    if (query_busy())
        init_command(":seems busy at the moment.", NPC_DELAY);
    else
    {
        set_busy(this_player());
        call_out((: how_many($(args[0])) :), NPC_DELAY);
    }
    return 1;
}
int do_sell(object *obs)
{
#ifdef DEBUG
    tell_creator(CREATOR,  "In do_sell()\n" );
#endif
    if (outside_hours(TRUE)) return 1;
    say_to_room(this_player(), "say", "I would like to sell " +
      query_multiple_short(obs, "the")+ ", please.\n%^RESET%^");
    if (query_busy())
        init_command(":seems busy at the moment.", NPC_DELAY);
    else
    {
        set_busy(this_player());
        call_out((: buy_something($(obs)) :), NPC_DELAY);
    }
    return 1;
}
private void end_shift()
{
    if (environment() != find_object("/room/rubbish"))
        do_command(_office->query_channel()+ "@ is clocking out.");
    do_command("clock out");
    move("/room/rubbish", "$N make$s some tea.", "$N go$s home for tea.");
}
void event_person_say(object thing, string start, string mess, string lang)
{
    string words;
#ifdef DEBUG
    tell_creator(CREATOR,  "In event_person_say()\n" );
#endif
    if (outside_hours(TRUE)) return;
    if (!mess || (mess == "")) return;
    mess = lower_case(mess);
    if (query_busy()) return;
    set_busy(thing);
    if (sscanf(mess, "%*s buy %s, please.", words) == 2)
    {
        call_out((: sell_something($(words)) :), NPC_DELAY);
        return;
    }
    if (sscanf(mess, "%*show many %s", words) == 2)
    {
        call_out((: how_many($(words)) :), NPC_DELAY);
        return;
    }
    if (sscanf(mess, "%*show much %s", words) == 2)
    {
        call_out((: how_much($(words)) :), NPC_DELAY);
        return;
    }
    if (( sscanf( mess, "%*s take over%*s") == 2) &&
      (_office->query_employee(thing->query_name()) ||
        thing->query_name() == CREATOR))
    {
        call_out((: taken_over() :), NPC_DELAY);
        return;
    }
    reset_busy();
    ::event_person_say(thing, start, mess, lang);
}
private void get_from_store()
{
    if (pointerp(_info))
    {
        int number, bag_item_weight, info1 = to_int(_info[1]);
        object *inven;
        _failed = 0;
        if (info1 > (MAX_INVEN + query_dex())) number = MAX_INVEN + query_dex();
        else number = info1;
#ifdef DEBUG
        tell_creator(CREATOR, "Removing %d %s\n", number, _info[0]);
#endif
        inven = all_inventory();
        do_command("remove " + number+ " "+ _info[0]);
        if (_failed)
        {
            do_command("add "+ _failed+ " "+ _info[0]);
            do_command("get "+ _info[0]);
        }
        inven = all_inventory() - inven;
        number -= _failed;
        info1 -= number;
        foreach(object thing in inven)
        if (thing->query_weight() < MAX_BAG_WEIGHT/5)
            bag_item_weight += thing->query_weight();
        bag_item_weight = (MAX_BAG_WEIGHT+bag_item_weight-1)/MAX_BAG_WEIGHT;
        if ( number > 9 )
        {
            number = (((number+9)/10) > bag_item_weight)?
            (number+9)/10:bag_item_weight;
            for(int i=0; i < number; i++) do_command("pull roll");
            for(int i=0; i < number; i++)
                do_command("put "+ _info[0]+ " in bag "+ (i+1));
        }
        if (info1)
        {
            _info[1] = sprintf("%d",info1);
            call_out("shuffle_to", NPC_DELAY, _shop_front,
              (: get_more_stuff() :));
            return;
        }
    }
    call_out("shuffle_to", NPC_DELAY, _shop_front, (: give_stuff() :));
}
private void get_money()
{
    if (pointerp(_info))
    {
        int total;
        mixed monies = ({0,0,0,0,});
        string *sort_keys_sing = sort_array(keys(_values_sing),
          (: sort_keys($1,$2,1) :));
        string *sort_keys_plural = sort_array(keys(_values_plural),
          (: sort_keys($1,$2,0) :));
#ifdef DEBUG
        tell_creator(CREATOR, "Singular: %O\n", sort_keys_sing);
        tell_creator(CREATOR, "Plural: %O\n", sort_keys_plural);
#endif
        foreach(string item in _office->query_list_array())
        {
            object *things = ((class obj_match)match_objects_in_environments(item,
              this_object()))->objects;
#ifdef DEBUG
            tell_creator(CREATOR, "We have %d %s\n", sizeof(things), item);
#endif
            if (monies[1] = sizeof(things))
            {
                if (things[0]->query_collective())
                    monies[1] = things[0]->query_amount();
                monies[3] = _office->query_buy(item);
                do_command( "'"+ capitalize(item) +" are worth "+
                  num_str(monies[3]) +" "+ _smallest_plural_in +
                  " each, and I have "+ num_str(monies[1]) + ".");
                monies[0] += monies[3] * monies[1];
                monies[2] = item;
                break;
            }
        }
        monies[0] *= _smallest_value_in;
        total = monies[0];
        for (int i=0; i < sizeof(sort_keys_sing); i++)
        {
            if (total < _values_sing[sort_keys_sing[i]]) continue;
            for (int c = total / _values_sing[sort_keys_sing[i]]; c > 0; c--)
            {
                string coins = sprintf("%d %s", c,
                  (c == 1)?sort_keys_sing[i]:sort_keys_plural[i]);
#ifdef DEBUG
                tell_creator(CREATOR, "Trying to get %s\n", coins);
#endif
                do_command("get "+ coins+ " from register");
                if (sizeof(match_objects_for_existence(coins, this_object())))
                {
                    total -= (c * _values_sing[sort_keys_sing[i]]);
#ifdef DEBUG
                    tell_creator(CREATOR, "New total: %d\n", total);
#endif
                    break;
                }
            }
        }
#ifdef DEBUG
        tell_creator(CREATOR, "Buying %d %s for %d each.\n", monies[1],
          monies[2], monies[3]);
#endif
        call_out((: check_money($(monies)) :), 1);
    }
    else
        call_out("shuffle_to", NPC_DELAY, _storeroom, (: put_in_store() :));
}
private void get_more_stuff()
{
    if (query_busy())
    {
        do_command("give all to "+ _busy->query_name());
        do_command("drop all");
        do_command("'I still need to get you "+ num_str(to_int(_info[1]))+ " "+
          _info[0]+ DEARIE+ ".  I won't be long.");
        call_out( "shuffle_to", NPC_DELAY, _storeroom,
          (: get_from_store() :) );
        return;
    }
    else
    {
        do_command("'Well now.  I wonder where they could have gone.");
        do_command("ponder");
    }
    do_command("drop all");
    reset_busy();
    _info = 0;
}
private void give_stuff()
{
    if (query_busy())
    {
        do_command("give all to "+ _busy->query_name());
        do_command("'Thank you for your custom" + DEARIE+ ".");
    }
    else
    {
        do_command("'Well now.  I wonder where they could have gone.");
        do_command("ponder");
    }
    do_command("drop all");
    reset_busy();
    _info = 0;
}
private void how_many(string item)
{
    _info = 0;
    foreach (string thing in _office->query_list_array())
    if (sscanf(item, "%*s"+ thing +"%*s") == 2) _info = item;
    if (!_info)
    {
        do_command("'I'm afraid we don't deal in those" + DEARIE+ ".");
        reset_busy();
        return;
    }
    do_command("'"+ capitalize( _info ) +"?  I'll just go and see.");
    call_out("shuffle_to", NPC_DELAY, _office, (: look_chart() :));
}
private void how_much(string item)
{
    _info = 0;
    foreach (string thing in _office->query_list_array())
    if (sscanf(item, "%*s"+ thing +"%*s") == 2) _info = thing;
    if (!_info)
    {
        do_command("'I'm afraid we don't deal in those"+ DEARIE+ ".");
        reset_busy();
        return;
    }
    do_command("'"+ capitalize( _info ) +"?  I'll just go and see.");
    call_out("shuffle_to", NPC_DELAY, _office, (: look_how_much() :));
}
void init()
{
    object tp = this_player();
#ifdef DEBUG
    tell_creator(CREATOR,  "In init()\n" );
#endif
    if (environment(this_object()) == find_object("/room/rubbish")) return;
#ifdef DEBUG
    tell_creator(CREATOR,  "Not in /room/rubbish\n");
#endif
    ::init();
    tp->add_command("buy", this_object(), "<string'item(s)'>",
      (: do_buy($4[0]) :));
    tp->add_command("sell", this_object(), "<indirect:object:me>",
      (: do_sell($1) :));
    tp->add_command("list", this_object(), ({"", "<string'item(s)'>"}),
      (: do_list($4) :));
    tp->add_command("browse", this_object(), "<string'item(s)'>",
      (: do_browse($4[0]) :));
    outside_hours(TRUE);
}
private void look_chart()
{
    if (stringp(_info)) do_command("'Now, let me see, "+ _info +"...");
    call_out("shuffle_to", NPC_DELAY, _shop_front, (: announce_number() :));
}
private void look_how_much()
{
    if (stringp(_info)) do_command("'Now, let me see, "+ _info +"...");
    call_out("shuffle_to", NPC_DELAY, _shop_front, (: announce_price() :));
}
private void no_coins()
{
    if (query_busy())
    {
        do_command("give all to "+ _busy->query_name());
        do_command("'I'm sorry" + DEARIE+ ".  I don't have the correct "
          "change to give you.  Please call again later.");
    }
    else
    {
        do_command("'Well now.  I wonder where they could have gone.");
        do_command("ponder");
    }
    do_command("drop all");
    reset_busy();
    _info = 0;
}
private int outside_hours(int working)
{
    int hrs, mins;
    string am_pm;
    if (query_busy())
    {
#ifdef DEBUG
        tell_creator(CREATOR, "Outside working hours but already busy.  "
          "Continuing.\n");
#endif
        return FALSE;
    }
    if (sscanf(amtime(time()), "%d:%d%s,%*s", hrs, mins, am_pm) == 4)
    {
#ifdef DEBUG
        tell_creator(CREATOR, "Time is %02d:%02d%s.\n", hrs, mins, am_pm);
#endif
        if (am_pm == "am")
        {
            if (hrs == 12) hrs = 0;
        }
        else
        if (hrs != 12) hrs += 12;
#ifdef DEBUG
        tell_creator(CREATOR, "Which is %02d:%02d.\n", hrs, mins);
#endif
        if ((hrs < _work_hrs[0] ||
            (hrs == _work_hrs[0] && mins < _work_hrs[1])) ||
          (hrs > _work_hrs[2] ||
            (hrs == _work_hrs[2] && mins > _work_hrs[3])))
        {
            if (!working)
            {
#ifdef DEBUG
                tell_creator(CREATOR, "Outside working hours & not "
                  "working.  Sending to /room/rubbish.\n");
#endif
                move("/room/rubbish");
                return TRUE;
            }
#ifdef DEBUG
            tell_creator(CREATOR, "Outside working hours & working.  "
              "Sending home now.\n");
#endif
            call_out("shuffle_to", NPC_DELAY, _office, (: end_shift() :));
            return TRUE;
        }
    }
    return FALSE;
}
private void put_in_store()
{
    if (pointerp(_info)) do_command("add all");
    do_command("drop all");
    foreach (string value in keys(_values_sing))
    do_command("get every "+ value);
    call_out("shuffle_to", NPC_DELAY, _shop_front, (: give_stuff() :));
}
private int query_busy()
{
    if (!objectp(_busy) || !interactive(_busy) || _busy->query_invis())
        return 0;
    if (environment(_busy) != find_object(_shop_front)) return 0;
    return (_busy != 0);
}
string query_office() { return copy(_office); }
private void say_to_room(object me, string t, string message)
{
    tell_object(me, "You "+ t+ ": "+ message);
    foreach(object player in all_inventory(environment(this_object())))
    if (interactive(player) && player != me)
        tell_object(player, player->colour_event("say", "%^CYAN%^")+
          me->query_short()+ " "+ t + "s: "+ message);
}
private void sell_something(string items)
{
    int each, number, in_stock;
    mixed *money_array;
    _info = 0;
    foreach (string item in _office->query_list_array())
    if (sscanf(items, "%*s"+ item +"%*s") == 2) _info = item;
    else if (sscanf(pluralize(items), "%*s"+ item +"%*s") == 2)
        _info = item;
    if (!_info)
    {
        do_command("'I'm afraid we don't deal in those"+ DEARIE+ ".");
        reset_busy();
        return;
    }
    if (sscanf(items, "%*s%d "+ _info +"%*s", number) != 3) number = 1;
#ifdef DEBUG
    tell_creator(CREATOR, "Customer asked for %d %s.\n", number, _info);
#endif
    if (number > (in_stock = _storeroom->query_num_items(_info)))
    {
        if (!in_stock)
        {
            do_command("'I'm afraid we don't have any "+ _info+ " in stock"+
              DEARIE+ ".");
            reset_busy();
            return;
        }
        do_command("'I'm afraid we don't have that many "+ _info +
          " in stock, but I can sell you "+ num_str(in_stock)+ ".");
        reset_busy();
        return;
    }
    if (number < 1)
    {
        do_command("'My, my.  You are amusing aren't you" + DEARIE+ "?");
        do_command("peer "+ _busy->query_name());
        reset_busy();
        return;
    }
    each = _office->query_sell(_info);
    do_command( "'"+ capitalize(_info) +" are worth "+
      num_str(each) +" "+ _smallest_plural_in + " each, and you want "+
      num_str(number) + ".");
    each *= number;
    if (_busy->query_value_in(_place) < (each * _smallest_value_in))
    {
        do_command("'I'm afraid you don't have enough money" + DEARIE+ ".");
        reset_busy();
        return;
    }
    money_array = MONEY_HAND->create_money_array(each * _smallest_value_in,
      _place);
    _busy->pay_money(money_array, _place);
    adjust_money(money_array);
#ifdef DEBUG
    tell_creator(CREATOR, "Monies adjusted by %O.\n", money_array);
#endif
    tell_room( environment( this_object() ), query_short()+
      " takes the money.\n" );
    do_command("'I'll be right back"+ DEARIE+ ".");
    _info = ({ _info, sprintf("%d", number), sprintf("%d", each) });
#ifdef DEBUG
    tell_creator(CREATOR,  "Selling: %O\n", _info);
#endif
    call_out("shuffle_to", NPC_DELAY, _counter, (: deposit_money() :));
}
protected object * item_test(mixed * items) { return ({}); }
protected void set_dearie(string *dearie) { _dearie = dearie; }
void set_failed(int failed) { _failed = failed; }
protected void set_office(string path)
{
    mapping values;
    string new_key;
    _office = path;
    _place = _office->query_place();
    _smallest_in = MONEY_HAND->smallest_in( _place );
    _smallest_value_in = MONEY_HAND->smallest_value_in(_place);
    _smallest_plural_in = MONEY_HAND->query_plural_for(_smallest_in);
    values = MONEY_HAND->query_mapped_values_in(_place);
    foreach(string key in keys(values))
    {
        new_key = MONEY_HAND->query_aliases_for(key)[0];
        _values_sing += ([new_key:values[key]]);
    new_key = MONEY_HAND->query_details_for(key)[5];
    _values_plural += ([new_key:values[key]]);
}
#ifdef DEBUG
tell_creator(CREATOR, "Singular values: %O.\n", _values_sing);
tell_creator(CREATOR, "Plural values: %O.\n", _values_plural);
#endif
_storeroom = _office->query_storeroom();
_counter = _office->query_counter();
_shop_front = _office->query_shop_front();
add_respond_to_with(({ "@say", "hello" }), "'Hello, $hcname$.  What can I do for you?");
add_respond_to_with(({ "@smile", query_name() }), "smile at $hname$");
}
protected void set_work_hours(int *hours) { _work_hrs = hours; }
void shuffle_to(string location, function next_action)
{
    string direc = environment()->directions_to(location);
    if (!direc)
    {
        if (environment() == find_object("/room/rubbish")) return;
        if (environment() == _shop_front->query_outside())
        {
            move(_shop_front, "$N enter$s the shop.",
              "$N enter$s _shop_front->query_short().");
        }
        else
        {
            do_command("'I seem to be lost...");
            do_command("sob");
            move(_office, "$N runs in, sobbing.", "$N leave$s, sobbing.");
            end_shift();
            return;
        }
        call_out("shuffle_to", NPC_DELAY, location, next_action);
        return;
    }
    if (direc == "here")
    {
        do_command("smile brightly");
        do_command("'Here we are.");
        if (next_action) call_out(next_action, NPC_DELAY);
        else reset_busy();
        return;
    }
    do_command(direc);
    call_out("shuffle_to", NPC_DELAY, location, next_action);
}
private int sort_keys(string s1, string s2, int sing)
{
    if (sing) return (_values_sing[s1] < _values_sing[s2])?1:-1;
    else return (_values_plural[s1] < _values_plural[s2])?1:-1;
}
void start_shift()
{
#ifdef DEBUG
    tell_creator(CREATOR,  "In start_shift()\n" );
#endif
    if (outside_hours(FALSE)) return;
    set_busy(this_object());
    move(_office, "$N arrive$s for " + query_possessive()+ " shift.");
    if (_office->query_employee(query_name()) & CLOCKED_IN)
        do_command("clock out");
    do_command("claim badge");
    do_command("wear badge");
    do_command("clock in");
    do_command(_office->query_channel()+ "@ is clocking in.");
    call_out("shuffle_to", NPC_DELAY, _shop_front, 0);
}
private void taken_over()
{
    do_command("'Okay then" + DEARIE+ ".  See you later.");
    set_busy(this_object());
    call_out("shuffle_to", NPC_DELAY, _office, (: end_shift() :));
}
private void what_items()
{
    do_command("'Well" + DEARIE+ ", we trade in "+
      _office->query_list_string()+ ".");
    reset_busy();
}