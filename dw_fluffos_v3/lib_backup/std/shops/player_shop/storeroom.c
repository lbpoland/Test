inherit "/std/room/basic_room";
#include <player_shop.h>
#include <move_failures.h>
#include "patterns.h"
private nosave string _office = "",
_counter = "",
_mgr_office = "",
_shop_front = "",
_office_dir = "",
_counter_dir = "",
_shop_dir = "";
private nosave object *_cabinets = 0;
private nosave int _num_cabinets, _call_cabs_clear;
private nosave mapping _cache = ([]);
int add_cabinet();
private void clear_cabinets();
string directions_to(string);
private int do_add(object *, mixed *);
private int do_list(mixed *, string);
private int do_remove(mixed *);
private void init_cabinets();
private int pull_roll();
int query_content(int);
int query_num_items(string, int);
string query_office();
int query_stock(string);
string remove_cabinet();
protected void set_directions(string, string, string);
protected void set_office(string);
void create()
{
    do_setup++;
    ::create();
    do_setup--;
    add_property("no burial", 1);
    add_property("determinate", "");
    add_item("cabinet", "There are several cabinets in the room, holding "
      "the entire stock of the shop.  If you are authorised to do so, you "
      "may \"list\" the stock, as well as \"add\" and \"remove\" "
      "items from the cabinets.");
    add_item(({"roll", "bag"}), "You could probably \"pull\" a bag off "
      "the roll and give it to a customer with their purchase.\n"
      "Bags should only be handed out with purchases of 10 or more items.");
    if (!do_setup)
    {
        this_object()->setup();
        this_object()->reset();
    }
    add_help_file("player_shop_storeroom");
}
void init()
{
    ::init();
    if (!_office || _office == "") return;
    add_command("add", ({"<indirect:object:me'item(s)'>",
        "<indirect:object:me'item(s)'> to cabinet <number'cabinet'>"}),
      (: do_add($1,$4) :));
    add_command("pull", "roll", (: pull_roll() :));
    if (_office->query_employee(this_player()->query_name()) ||
      this_player()->query_creator())
    {
        add_command("list", ({LIST_BLANK, LIST_CABINET,
            LIST_ITEM, LIST_ITEM_CABINET}),
          (: do_list($4,$5) :));
        add_command("remove", ({"<number> <string'item(s)'>",
            "<number> <string'item(s)'> from cabinet <number'cabinet'>"}),
          (: do_remove($4) :));
    }
    else if (_office->query_retired(this_player()->query_name()))
        add_command("list", ({LIST_BLANK, LIST_CABINET,
            LIST_ITEM, LIST_ITEM_CABINET}), (: do_list($4,$5) :));
}
int add_cabinet()
{
    object cabinet;
    string cab_name;
    if (previous_object() && previous_object() != find_object(_office))
    {
        LOG_ERROR("storeroom.c", "add_cabinet()");
        return 0;
    }
    if ((_num_cabinets) == MAX_CABINETS) return 0;
    init_cabinets();
    cab_name = "cabinet"+ _num_cabinets++;
    cabinet = clone_object(CABINET);
    cabinet->set_name(cab_name);
    cabinet->set_save_file(_office->query_savedir()+ cab_name);
    _cabinets += ({cabinet});
    return 1;
}
private void clear_cabinets()
{
    if (!_cabinets) return;
#ifdef DEBUG
    tell_creator(CREATOR, "Clearing cabinets.\n");
#endif
    foreach (object cabinet in _cabinets) cabinet->dest_me();
    _cabinets = 0;
}
void dest_me()
{
    remove_call_out(_call_cabs_clear);
    clear_cabinets();
    ::dest_me();
}
string directions_to(string place)
{
    if (place == _counter) return copy(_counter_dir);
    if (place == _office) return copy(_office_dir);
    if (place == _shop_front) return copy(_shop_dir);
    return "here";
}
private int do_add(object *items, mixed *args)
{
    int cab_no = 0;
    object *okay = ({}),
    *failed = ({});
    add_succeeded_mess("");
    if (sizeof(args) > 1)
    {
        cab_no = args[1];
        if (cab_no < 1 || cab_no > _num_cabinets)
        {
            tell_object(this_player(), "That cabinet does not exist!\n");
            return 1;
        }
    }
    init_cabinets();
    foreach (string plural in _office->query_list_array())
    {
        int tot_i, number, temp_num;
        mixed *test;
        parse_command(plural, items, "%i", test);
        if (!test || !sizeof(test)) continue;
        if (!sizeof(_office->query_cabinet(plural)))
        {
            tell_object(this_player(), "There are no cabinets assigned to "+
              plural+ "!\n");
            return 1;
        }
        if ((tot_i = _office->query_max(plural) - query_stock(plural)) < 1)
        {
            tell_object(this_player(),
              "The shop is already fully stocked on "+ plural +".\n");
            test = ({});
            continue;
        }
        test = test[1..];
        if (test[0]->query_collective())
        {
            number = test[0]->query_amount();
        }
        else
        {
            number = sizeof(test);
        }
        if (cab_no)
        {
            int cab_i = 0;
            foreach (object ob in all_inventory(_cabinets[cab_no-1]))
            {
                if (ob->query_collective())
                {
                    cab_i += ob->query_amount();
                }
                else
                {
                    cab_i += 1;
                }
            }
            cab_i = STOCK_PER_CABINET - cab_i;
            if (cab_i < 1)
            {
                tell_object(this_player(), "That cabinet is already full.\n");
                return 1;
            }
            if (member_array(cab_no, _office->query_cabinet(plural)) == -1)
            {
                tell_object(this_player(), plural +
                  " do not belong in that cabinet.\n");
                return 1;
            }
            if (number > cab_i)
            {
                tell_object(this_player(), "You cannot add all of the "+ plural +
                  " to cabinet "+ cab_no+ " without exceeding the maximum.\n");
                if (test[0]->query_collective())
                {
                    object temp = test[0]->make_medium_clone(cab_i);
                    test[0]->adjust_amount(-cab_i);
                    test = ({temp});
                    test->move(this_player());
                }
                else
                {
                    test = test[0 .. (cab_i - 1)];
                }
            }
        }
        else if (number > tot_i)
        {
            tell_object(this_player(), "You cannot add all of the "+ plural +
              " to the stock without exceeding the maximum.\n");
            if (test[0]->query_collective())
            {
                object temp = test[0]->make_medium_clone(tot_i);
                test[0]->adjust_amount(-tot_i);
                test = ({temp});
                test->move(this_player());
            }
            else
            {
                test = test[0 .. (tot_i - 1)];
            }
            number = tot_i;
        }
        temp_num = number;
        if (cab_no)
        {
            object *temp_fail;
            okay += test;
            temp_fail = _cabinets[cab_no - 1]->
            add_items(test, this_player());
            failed += temp_fail;
            if (sizeof(temp_fail))
            {
                temp_num -= temp_fail[0]->query_amount();
            }
            else
            {
                temp_num -= sizeof(temp_fail);
            }
        }
        else
        {
            int cab_i = 0;
            foreach(cab_no in _office->query_cabinet(plural))
            {
                object *temp_fail;
                if (!number) break;
                foreach (object ob in all_inventory(_cabinets[cab_no-1]))
                {
                    if (ob->query_collective())
                    {
                        cab_i += ob->query_amount();
                    }
                    else
                    {
                        cab_i += 1;
                    }
                }
                cab_i = STOCK_PER_CABINET - cab_i;
                if (cab_i < 1) continue;
                if (cab_i > number)
                {
                    cab_i = number;
                }
                if (test[0]->query_collective())
                {
                    object temp = test[0]->make_medium_clone(cab_i);
                    test[0]->adjust_amount(-cab_i);
                    okay += ({temp});
                    temp_fail = _cabinets[cab_no - 1]->
                    add_items(({temp}), this_player());
                }
                else
                {
                    okay += test[0..(cab_i-1)];
                    temp_fail = _cabinets[cab_no - 1]->
                    add_items(test[0 .. (cab_i - 1)], this_player());
                    test -= test[0 .. (cab_i - 1)];
                }
                number -= cab_i;
                failed += temp_fail;
                if (sizeof(temp_fail))
                {
                    if (temp_fail[0]->query_collective())
                    {
                        temp_num -= temp_fail[0]->query_amount();
                    }
                    else
                    {
                        temp_num -= sizeof(temp_fail);
                    }
                }
            }
            if (sizeof(test) && test[0]->query_amount())
            {
                tell_object(this_player(), "There is not enough room in the "
                  "assigned cabinets for "+ query_multiple_short(test)+ ".\n");
                if (test[0]->query_collective())
                {
                    temp_num -= test[0]->query_amount();
                }
                else
                {
                    temp_num -= sizeof(test);
                }
            }
            cab_no = 0;
        }
        test = ({});
        _office->adjust_bought(plural, temp_num);
        if (!_cache[plural])
        {
#ifdef DEBUG
            tell_creator(CREATOR,"Creating %s cache entry.\n", plural);
#endif
            _cache += ([plural:({1,0})]);
        }
        else
        {
            _cache[plural][0] = 1;
        }
    }
    okay -= failed;
    if (sizeof(failed))
    {
        string short = query_multiple_short(failed);
        tell_room(environment(this_player()), this_player()->query_short()+
          " accidentally drops "+ short+
          " on the floor.\n", ({this_player()}));
        tell_object(this_player() , "You accidentally drop "+
          short+ " on the floor.\n");
    }
    if (sizeof(okay))
    {
        string short = query_multiple_short(okay);
        _office->shop_log(PURCHASE, this_player()->query_name(),
          this_player()->convert_message(short)+
          " added to stock", UNPAID);
        add_succeeded_mess("$N $V "+ short+
          " to the stock.\n");
    }
    return 1;
}
private int do_list(mixed *args, string pattern)
{
    object *found_items = ({});
    int i = 0;
    add_succeeded_mess("");
    init_cabinets();
    foreach (object cabinet in _cabinets)
    i += sizeof(all_inventory(cabinet));
    if (!i)
    {
        tell_object(this_player(),
          "There is nothing in stock at the moment.\n");
        return 1;
    }
    if (pattern == LIST_BLANK)
    {
        string result = sprintf("     Stock of %s\n     As at %s\n\n",
          _office->query_shop_name(), ctime(time()));
        foreach(string key in _office->query_list_array())
        {
            found_items = ({});
            found_items += ((class obj_match)match_objects_in_environments(key, _cabinets))->objects;
            if (sizeof(found_items))
                result += query_multiple_short( found_items )+ "\n";
        }
        tell_object(this_player(), "$P$Stock list$P$"+ result);
        return 1;
    }
    if (pattern == LIST_CABINET)
    {
        string result;
        if (args[0] < 1 || args[0] > _num_cabinets)
        {
            tell_object(this_player(), "That cabinet does not exist!\n");
            return 1;
        }
        if (!sizeof(all_inventory(_cabinets[args[0] - 1])))
        {
            result = "There is nothing in that cabinet at the moment.\n";
        }
        else
        {
            result = sprintf("     Stock of cabinet %d\n     As at %s\n\n",
              args[0], ctime(time()));
            foreach(string key in _office->query_list_array())
            {
                if (sizeof(found_items = ((class obj_match)match_objects_in_environments(key,
                        _cabinets[args[0]-1]))->objects ))
                {
                    result += query_multiple_short(found_items)+ "\n";
                }
            }
        }
        tell_object(this_player(), "$P$Cabinet "+ args[0]+
          " stock list$P$"+ result);
        return 1;
    }
    if (pattern == LIST_ITEM)
    {
        string result;
        found_items += ((class obj_match)match_objects_in_environments(args[0], _cabinets))->objects;
        if (!sizeof(found_items))
        {
            tell_object(this_player(),  "There are no "+ args[0]+
              " in stock.\n");
            return 1;
        }
        result = sprintf("     List of %s\n     As at %s\n\n%s", args[0],
          ctime(time()), query_multiple_short(found_items));
        tell_object(this_player(), "$P$List of " + args[0]+ "$P$"+ result);
        return 1;
    }
    if (args[1] < 1 || args[1] > _num_cabinets)
    {
        tell_object(this_player(), "That cabinet does not exist!\n");
        return 1;
    }
    if (!sizeof(all_inventory(_cabinets[args[1] - 1])))
    {
        tell_object(this_player(), "There is nothing in that cabinet at "
          "the moment.\n");
        return 1;
    }
    found_items = ((class obj_match)match_objects_in_environments(args[0],
        _cabinets[args[1]-1]))->objects;
    if (!sizeof(found_items))
    {
        tell_object(this_player(), "There are no "+ args[0]+ " in stock.\n");
        return 1;
    }
    tell_object(this_player(), "$P$List of "+ args[0]+ " in cabinet "+
      args[1]+ "$P$"+ sprintf("     List of %s in cabinet %d\n     "
        "As at %s\n\n%s", args[0], args[1], ctime(time()),
        query_multiple_short(found_items)));
    return 1;
}
private int do_remove(mixed *args)
{
    int cab_no = 0;
    object *items = ({}), *failed;
    failed = ({});
    add_succeeded_mess("");
    if (sizeof(args) > 2) cab_no = args[2];
    if (query_num_items(args[1], cab_no) < args[0])
    {
        tell_object(this_player(), "The stock does not contain "+
          args[0] + " "+ args[1]+ " to remove.\n");
        return 1;
    }
    init_cabinets();
    if (!cab_no)
    {
        int number = args[0];
        for(int i = sizeof(_cabinets); i > 0; i--)
        {
            object *stock = ((class obj_match)match_objects_in_environments(args[1],
                _cabinets[i-1]))->objects;
            if (sizeof(stock))
            {
                if (stock[0]->query_collective())
                {
                    if (stock[0]->query_amount() > number)
                    {
                        object ob = stock[0]->make_medium_clone(number);
                        items += ({ ob });
                        stock[0]->adjust_amount(-number);
                        if (ob->move(this_player()) != MOVE_OK)
                        {
                            ob->move(environment(this_player()));
                            failed += ({ ob });
                        }
                    }
                    else
                    {
                        number -= stock[0]->query_amount();
                        items += stock;
                        failed += _cabinets[i-1]->remove_items(stock, this_player());
                    }
                }
                else
                {
                    if (sizeof(stock) > number) stock = stock[ 0 .. (number-1) ];
                    items += stock;
                    failed += _cabinets[i-1]->remove_items(stock, this_player());
                    number -= sizeof(stock);
                }
            }
            if (!number) break;
        }
    }
    else
    {
        items = ((class obj_match)match_objects_in_environments(args[1],
            _cabinets[cab_no-1]))->objects[0 .. (args[0] - 1)];
        failed = _cabinets[cab_no - 1]->remove_items(items, this_player());
    }
    foreach (string vest in _office->query_list_array())
    {
        if (pluralize(args[1]) == vest)
        {
            args[1] = pluralize(args[1]);
            break;
        }
    }
    if (!_cache[args[1]])
    {
#ifdef DEBUG
        tell_creator(CREATOR,"Creating %s cache entry.\n", args[1]);
#endif
        _cache += ([args[1]:({1,0})]);
    }
    else
    {
        _cache[args[1]][0] = 1;
    }
    items -= failed;
    if (sizeof(failed))
    {
        tell_room(environment(this_player() ), this_player()->query_short()+
          " accidentally drops "+ query_multiple_short(failed)+
          " on the floor.\n", ({this_player()}));
        tell_object(this_player() , "You accidentally drop "+
          query_multiple_short(failed)+ " on the floor.\n");
    }
    if (find_object(_office->query_shopkeeper()) &&
      this_player() == find_object(_office->query_shopkeeper()))
        _office->query_shopkeeper()->set_failed(sizeof(failed));
    if (sizeof(items))
    {
        _office->shop_log(SALE, this_player()->query_name(),
          this_player()->convert_message(query_multiple_short(items))+
          " removed from stock", UNPAID);
        foreach (string plural in _office->query_list_array())
        {
            object *test = ({});
            parse_command(plural, items, "%i", test);
            if (!test || !sizeof(test)) continue;
            _office->adjust_sold(plural, sizeof(test) - 1);
        }
        add_succeeded_mess("$N $V "+ query_multiple_short(items)+
          " from the stock.\n");
    }
    return 1;
}
void event_death(object k, object *o, object k2, string r, string k3)
{
    _office->event_death(k,o,k2,r,k3);
}
void event_enter(object ob, string message, object from)
{
    _office->event_enter(ob, message, from);
}
string long(string word, int dark)
{
    return sprintf("%sThere are currently %d store cabinets "
      "in the room.\n", ::long(word,dark), _num_cabinets);
}
private void init_cabinets()
{
    if (remove_call_out(_call_cabs_clear) == -1 && !_cabinets)
    {
#ifdef DEBUG
        tell_creator(CREATOR, "Initialising cabinets.\n");
#endif
        _cabinets = ({});
        for (int i = 0; i < _num_cabinets; i++)
        {
            string cab_name = "cabinet"+ i;
            object cabinet = clone_object(CABINET);
            cabinet->set_name(cab_name);
            cabinet->set_save_file(_office->query_savedir()+ cab_name);
            _cabinets += ({cabinet});
        }
    }
    _call_cabs_clear = call_out((: clear_cabinets() :), CLEAR_DELAY);
}
private int pull_roll()
{
    object bag;
    string message, day, day2, month;
    bag = clone_object(SHOP_BAG);
    sscanf(amtime(time()), "%*s %s %s %s", day, day2, month);
    if (member_array( month, ({"Offle", "February", "March",
          "April", "May", "June", "Grune", "August", "Spune", "Sektober",
          "Ember", "December", "Ick"}) ) == -1)
        message = sprintf("A very happy %s %s %s\n\nfrom everyone at\n\n%s, %s",
          day, day2, month, _office->query_shop_name(),
          _office->query_place());
    else message = sprintf("With the compliments of\n\n%s, %s.",
          _office->query_shop_name(), _office->query_place());
    bag->set_read_mess(message);
    bag->set_max_cond(400);
    bag->set_cond(400);
    if ((int)bag->move(this_player()) != MOVE_OK)
    {
        bag->move(this_object());
        tell_object(this_player(),
          "You drop the bag as you're carrying too much.\n");
    }
    add_succeeded_mess("$N $V the roll and $I comes off in $p hand.\n",
      ({bag}) );
    return 1;
}
int query_num_items(string item, int cabinet)
{
    object *obs;
    init_cabinets();
    if (cabinet)
    {
        obs = ((class obj_match)match_objects_in_environments(item,
            _cabinets[cabinet-1]))->objects;
        if (!sizeof(obs))
        {
            return 0;
        }
        else if (obs[0]->query_collective())
        {
            return obs[0]->query_amount();
        }
        else
        {
            return sizeof(obs);
        }
    }
    else
    {
        return query_stock(item);
    }
}
string query_office() { return copy(_office); }
int query_stock(string item)
{
    object *obs;
    init_cabinets();
    if (!_cache[item])
    {
#ifdef DEBUG
        tell_creator(CREATOR,"Creating %s cache entry.\n", item);
#endif
        _cache += ([item:({1,0})]);
    }
    if (_cache[item][0])
    {
#ifdef DEBUG
        tell_creator("ringo","Updating %s in cache.\n", item);
#endif
        obs = ((class obj_match)match_objects_in_environments(item, _cabinets))->objects;
        if (!sizeof(obs))
        {
            _cache[item][1] = 0;
        }
        else if (obs[0]->query_collective())
        {
            _cache[item][1] = obs[0]->query_amount();
        }
        else
        {
            _cache[item][1] = sizeof(obs);
        }
        _cache[item][0] = 0;
    }
    return _cache[item][1];
}
string remove_cabinet()
{
    object cabinet;
    if (previous_object() && previous_object() != find_object(_office))
    {
        LOG_ERROR("storeroom.c", "remove_cabinet()");
        return "";
    }
    if ((_num_cabinets) == MIN_CABINETS) return "";
    init_cabinets();
    _num_cabinets--;
    cabinet = _cabinets[_num_cabinets];
    _cabinets -= ({cabinet});
    cabinet->move("/room/rubbish");
    return cabinet->query_name();
}
protected void set_directions(string office, string counter, string shop)
{
    _office_dir = office;
    _counter_dir = counter;
    _shop_dir = shop;
}
protected void set_long(string long_desc)
{
    long_desc += "Employees can \"add\" something to, \"remove\" "
    "something from and \"list\" the stock.\nThere is a roll of "
    "shopping bags conveniently located on one wall.\n";
    ::set_long(long_desc);
}
protected void set_office(string path)
{
    _office = path;
    _counter = _office->query_counter();
    _mgr_office = _office->query_mgr_office();
    _shop_front = _office->query_shop_front();
    _num_cabinets = _office->query_num_cabinets();
}