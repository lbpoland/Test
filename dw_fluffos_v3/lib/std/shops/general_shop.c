#include <armoury.h>
#include <money.h>
#include <move_failures.h>
#include <shop.h>
#include <tasks.h>
inherit "/std/room/basic_room";
inherit "/std/shops/inherit/open_shop";
private mixed our_storeroom;
private mixed buy_mess;
private mixed sell_mess;
private mixed list_mess;
private mixed value_mess;
private mixed too_costly_mess;
private mixed not_worthy_mess;
private mixed browse_mess;
private mixed *other_shops;
private int amount_sold;
private int amount_bought;
private int strict_shop;
private int no_steal;
private int sell_stolen;
private int steal_difficulty;
private int min_amount;
private int max_inventory;
private int sell_large;
private mixed shop_type;
private mixed buy_func;
private mixed sell_func;
private mixed value_func;
private mixed too_costly_func;
private mixed cannot_sell_func;
private mixed browse_func;
private mixed list_func;
private nosave string shoplift_handler;
private string original_storeroom;
private int _strict_currency;
private nosave mapping elist = (["north" : "south", "south" : "north",
  "east" : "west", "west" : "east", "up" : "down", "down" : "up"]);
string shop_list(mixed arr, int detail);
string shop_parse(string str, mixed ob, object client, string money,
  string extra, string which);
string find_free_exit();
int do_buy(object *ob);
int do_list_these(object *obs);
void do_buy_things( object *obs, int cost, object pl );
void do_parse(mixed arr, mixed ob, object client, string money,
  string extra);
object create_mercenary(object rep);
void event_shoplift(object command_ob, object thief, object victim);
object query_store_room();
int creator_object (object);
void create() {
    buy_mess = ({
      "You buy $ob$ for $money$.\n",
      "$client$ buys $ob$.\n"});
    sell_mess = ({
      "You sell $ob$ for $money$.\n",
      "$client$ sells $ob$.\n"});
    list_mess = "$extra$";
    value_mess = "$ob$ is valued at $money$.\n";
    too_costly_mess = "$ob$ is worth too much to be sold here.\n";
    not_worthy_mess = "$ob$ is not worth enough to be sold here.\n";
    browse_mess = "$ob$ costs $money$, it looks like:\n$extra$";
    other_shops = ({ });
    max_inventory = MAX_INVENTORY;
    min_amount = 50;
    add_help_file("shop");
    _strict_currency = 1;
    ::create();
}
void reset() {
    if(!random(3)) {
        remove_property("inventory_loss");
    }
    call_out("send_out_reps", 2);
}
void set_buy_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        buy_func = func;
    }
}
void set_sell_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        sell_func = func;
    }
}
void set_value_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        value_func = func;
    }
}
void set_too_costly_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        too_costly_func = func;
    }
}
void set_cannot_sell_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        cannot_sell_func = func;
    }
}
void set_browse_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        browse_func = func;
    }
}
void set_list_function(mixed func) {
    if (stringp(func) || functionp(func)) {
        list_func = func;
    }
}
void set_sell_message(mixed str) {
    sell_mess = str;
}
void set_buy_message(mixed str) {
    buy_mess = str;
}
void set_value_message(mixed str) {
    value_mess = str;
}
void set_too_costly_message(mixed str) {
    too_costly_mess = str;
}
void set_not_worthy_message(mixed str) {
    not_worthy_mess = str;
}
void set_browse_message(mixed str) {
    browse_mess = str;
}
void set_list_message(mixed str) {
    list_mess = str;
}
void set_open_condition(mixed str) {
   if (functionp(str)) {
      ::set_open_function(str);
   } else if (intp(str)) {
      ::set_open_function( (: $(str) :) );
   } else if (pointerp(str)) {
      ::set_open_function( (: call_other($(str[0]), $(str[1]), $1) :) );
   } if ( stringp(str) ) {
      ::set_open_function( (: call_other( this_object(), $(str), $1 ) :) );
   }
}
void set_no_steal(int i) {
    no_steal = i;
}
void set_steal_difficulty(int i) {
    steal_difficulty = i;
}
void set_sell_stolen(int i) {
    sell_stolen = i;
    no_steal = 1;
}
void set_sell_large(int i) { sell_large = i; }
mixed query_sell_mess() {
    return sell_mess;
}
mixed query_list_mess() {
    return list_mess;
}
mixed query_value_mess() {
    return value_mess;
}
mixed query_too_costly_mess() {
    return too_costly_mess;
}
mixed query_not_worthy_mess() {
    return not_worthy_mess;
}
mixed query_buy_mess() {
    return buy_mess;
}
mixed query_browse_mess() {
    return browse_mess;
}
int query_no_steal() {
    return no_steal;
}
int query_steal_difficulty(int i) {
    return steal_difficulty;
}
string query_shoplift_response_handler() {
    return shoplift_handler;
}
int query_shop() {
    return 1;
}
object *query_shop_lift_items(string str, object player) {
    return match_objects_for_existence(str, ({ query_store_room() }));
}
object shoplift_success(object ob) {
    return ob;
}
void set_shoplift_response_handler(string word) {
    shoplift_handler = word;
}
void set_min_amount(int i) { min_amount = i; }
void set_max_inventory(int i) { max_inventory = i; }
void init() {
    string room;
    ::init();
    if(stringp(our_storeroom)) {
        room = our_storeroom;
    } else if(our_storeroom) {
        room = file_name(our_storeroom);
    } else {
      tell_room(this_object(),
                "Oh dear, we don't seem to have a storeroom.\n");
    }
    add_command("sell", "<indirect:object:me>");
    add_command("buy", "<indirect:object:"+room+">");
    add_command("list", "[all]");
    add_command("list", "<indirect:object:"+room+">",
      (: do_list_these($1) :));
    add_command("browse", "<indirect:object:"+room+">");
    add_command("value", "<indirect:object:me>");
}
int query_max_amount() {
    return MAX_AMOUNT;
}
int query_min_amount() {
    return min_amount;
}
varargs int query_value(object thing, int sell) {
     if ( thing->query_property("cost here") && !sell ) {
         return (int)thing->query_property("cost here");
     }
     else {
        return (int)thing->query_value_at( this_object() );
     }
}
int scaled_value(int n) {
    int i, tot, *fish;
    fish = PAY_RATES;
    if(n < fish[0]) {
        return n;
    } else {
        tot = fish[0];
        n -= fish[0];
    }
    i = 0;
    while(n && ((i + 1) < sizeof(fish))) {
        if(n >= fish[i]) {
            tot += fish[i + 1] * fish[i] / 100;
            n -= fish[i];
        } else {
            tot += fish[i + 1] * n / 100;
            n = 0;
        }
        i += 2;
    }
    if(n) {
        tot += (n * fish[sizeof(fish) - 1]) / 100;
    }
    return tot;
}
int do_sell(object *in_obs) {
    int i, amt, total_amt;
    string place, filename, *text = ({ });
    object money, *obs, *selling, *cannot, *stolen, storeob, one_item, *cre;
    object thing;
    mixed *m_array;
    if(!is_open(this_player(), 0)) {
        return 0;
    }
    in_obs = uniq_array( in_obs );
    obs = filter_array(in_obs, (: !$1->query_keep() :));
    cre = filter (obs, (: creator_object ($1) :));
    if (sizeof (cre) && strsrch (file_name (this_object()),
      "_dev") == -1) {
      if (!this_player()->query_creator()) {
        tell_object (this_player(), "Oh dear, you shouldn't have " +
          query_multiple_short (cre) + "!  They disappear with a flash "
          "of octarine light.\n");
        cre->move ("/room/rubbish");
      }
      else {
        tell_object (this_player(), "Oh dear, you shouldn't be trying to sell " +
          query_multiple_short (cre) + "!\n");
      }
      foreach (thing in cre) {
        if ( thing->query_property( "virtual name" ) ) {
          filename = thing->query_property( "virtual name" );
        } else {
          filename = base_name (thing);
        }
        text += ({filename});
      }
      log_file ("ILLEGAL_OBJECT", sprintf ("%s: %s tried to sell %s at "
        "%s.\n\n", ctime (time()), this_player()->query_name(),
        query_multiple_short (text), file_name (this_object())));
      obs -= cre;
   }
    if(!sizeof(obs)) {
        this_player()->add_failed_mess(this_object(),
          "You previously decided to keep $I.\n", in_obs);
        return 0;
    }
    in_obs = this_player()->query_holding() + this_player()->query_armours();
    cannot = filter(obs, (: member_array($1, $2) != -1 :), in_obs);
    if (sizeof(cannot)) {
        obs -= cannot;
        tell_object(this_player(), "You decide not to sell " +
          query_multiple_short(cannot, "the") + ", because "
          "you are wearing or holding $V$0=it,them$V$.\n");
    }
    if(objectp(our_storeroom)) {
        storeob = our_storeroom;
    } else {
        our_storeroom->rabbit_away();
        storeob = find_object(our_storeroom);
    }
    if(sizeof(all_inventory(storeob)) > max_inventory) {
        this_player()->add_failed_mess(this_object(),
          "Sorry, the shop is full up and isn't buying items!\n", ({ }));
        call_out("tidy_inventory", random(20));
        return 0;
    }
    if(sizeof(obs) > MAX_OBS) {
        write("The shopkeeper can't cope with all those objects.\n");
        obs = obs[0..MAX_OBS - 1];
    }
    selling = cannot = stolen = ({ });
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    for(i = 0; i < sizeof(obs); i++) {
        if(!sell_stolen && obs[i]->query_property("stolen")) {
            stolen += ({obs[i]});
            continue;
        } else {
            obs[i]->remove_property("stolen");
        }
        if((this_object()->query_value(obs[i], 1) > 0) &&
          !obs[i]->do_not_sell() &&
          !this_object()->do_not_buy(obs[i]) && (!strict_shop ||
            shop_type == obs[i]->query_property("shop type")) &&
          environment(obs[i]) == this_player()) {
            if(obs[i]->move(our_storeroom)) {
                if(obs[i]->short()) {
                    cannot += ({obs[i]});
                }
                continue;
            }
            amt = (int)this_object()->query_value(obs[i], 1);
            if(!(obs[i]->query_property("sale_value"))) {
                amt = scaled_value( amt );
            }
            if((amt <= (int)this_object()->query_max_amount()) &&
              (amt >= (int)this_object()->query_min_amount())) {
                if(shop_type != obs[i]->query_property("shop type")) {
                    amt = (amt * 90) / 100;
                }
                total_amt += amt;
                selling += ({obs[i]});
                obs[i]->being_sold();
            } else {
                if(obs[i]->short())
                    cannot += ({obs[i]});
                obs[i]->move(this_player());
            }
        } else {
            if(obs[i]->short()) {
                cannot += ({obs[i]});
            }
        }
    }
    if (!sizeof(selling)) {
        if (sizeof(cannot)) {
            if (stringp(cannot_sell_func)) {
                call_other(this_object(), cannot_sell_func, this_player(), cannot);
            } else if (functionp(cannot_sell_func)) {
                evaluate(cannot_sell_func, this_player(), cannot);
            }
            this_player()->add_failed_mess(this_object(),
              "You cannot sell $I.\n", cannot);
        } else if(sizeof(stolen)) {
            if(sizeof(stolen) > 1) {
                this_player()->add_failed_mess(this_object(),
                  "You cannot sell $I because they're stolen!\n", stolen);
            } else {
                this_player()->add_failed_mess(this_object(),
                  "You cannot sell $I because it's stolen!\n", stolen);
            }
            foreach(one_item in obs) {
                if(one_item->query_property("stolen") == this_player()->query_name()) {
                    event_shoplift(this_object(), this_player(), this_object());
                    break;
                }
            }
        } else {
            this_player()->add_failed_mess(this_object(),
              "You have nothing to sell.\n", ({ }));
        }
        return 0;
    }
    if(this_object()->cannot_afford(total_amt)) {
        selling->move(this_player());
        this_player()->add_failed_mess(this_object(),
          "The shop cannot afford to buy $I from you.\n", selling);
        return 0;
    }
    amount_sold += total_amt;
    m_array = (mixed *)MONEY_HAND->create_money_array(total_amt, place);
    money = clone_object(MONEY_OBJECT);
    money->set_money_array(m_array);
    if(sizeof(cannot)) {
        if(stringp(cannot_sell_func)) {
            call_other(this_object(), cannot_sell_func, this_player(), cannot);
        } else if (functionp(cannot_sell_func)) {
            evaluate(cannot_sell_func, this_player(), cannot);
        }
        write("You cannot sell "+query_multiple_short(cannot)+".\n");
        cannot->move(this_player());
    }
    if(stringp(sell_func)) {
        call_other(this_object(), sell_func, this_player(), obs);
    } else if (functionp(sell_func)) {
        evaluate(sell_func, this_player(), obs);
    }
    do_parse(sell_mess, selling, this_player(),
      (string)MONEY_HAND->money_string(m_array), "");
    if((int)money->move(this_player()) != MOVE_OK) {
        tell_object(this_player(),
          "You're too heavily burdened to accept all that money, "
          "so the shopkeeper puts it on the floor.\n");
        money->move(this_object());
    }
    this_object()->made_transaction(-total_amt, selling);
    return 1;
}
int creator_object( object ob ) {
    string path;
    if ( file_name( ob )[0..2] == "/w/" ) {
        return 1;
    }
    if ( ( path = ob->query_property( "virtual name" ) ) &&
      path[0..2] == "/w/" ) {
        return 1;
    }
    return 0;
}
int do_buy(object *obs) {
    int i, amt, ob_amt, total_cost;
    string place;
    object money, *to_buy, *cannot, *too_much;
    object *creator_obs;
    if(!is_open(this_player(), 0)) {
        return 0;
    }
    if(sizeof(obs) > MAX_OBS) {
        write("The shopkeeper can't cope with all those objects.\n");
        obs = obs[0..MAX_OBS-1];
    }
    creator_obs = filter( obs, (: creator_object( $1 ) :) );
    if ( sizeof( creator_obs ) && file_name()[0..2] != "/w/" ) {
        tell_object( this_player(), "You cannot buy " +
          query_multiple_short( creator_obs, "the" ) +
          " because they shouldn't be in the game!\n" );
        obs -= creator_obs;
    }
    to_buy = too_much = cannot = ({ });
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    money = present(MONEY_ALIAS, this_player());
    if(!money) {
        if(stringp(too_costly_func)) {
            call_other(this_object(), too_costly_func, this_player(), obs);
        } else if (functionp(too_costly_func)) {
            evaluate(too_costly_func, this_player(), obs);
        }
        this_player()->add_failed_mess(this_object(),
          "You have no money.\n", obs);
        return 0;
    }
    amt = money->query_value_in(place);
    if(place != "default" && !_strict_currency ) {
        amt += money->query_value_in("default");
    }
    while(i < sizeof(obs)) {
        ob_amt = this_object()->query_value(obs[i], 0);
        if(ob_amt > amt) {
            if(obs[i]->short()) {
                too_much += ({obs[i]});
            }
            obs = delete(obs, i, 1);
            continue;
        }
        if(obs[i]->move(this_player())) {
            if(!sell_large) {
                if(obs[i]->short()) {
                    cannot += ({obs[i]});
                }
                i++;
                continue;
            } else {
                obs[i]->move(this_object());
            }
        }
        amt -= ob_amt;
        total_cost += ob_amt;
        to_buy += ({obs[i]});
        i++;
    }
    amount_bought += total_cost;
    if(sizeof(cannot)) {
        this_player()->add_failed_mess(this_object(),
          "You cannot pick up $I.\n", cannot);
    }
    if(sizeof(too_much)) {
        if(stringp(too_costly_func)) {
            call_other(this_object(), too_costly_func, this_player(), cannot);
        } else if (functionp(too_costly_func)) {
            evaluate(too_costly_func, this_player(), cannot);
        }
        this_player()->add_failed_mess(this_object(),
          "$I costs too much.\n", too_much);
    }
    if(!sizeof(to_buy)) {
        return 0;
    }
    do_buy_things(to_buy, total_cost, this_player());
    return 1;
}
void do_buy_things(object *obs, int cost, object pl) {
    int i, j;
    string place;
    object money, change;
    mixed m_array, p_array;
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    money = present(MONEY_ALIAS, pl);
    if(!money) {
        if(stringp(too_costly_func)) {
            call_other(this_object(), too_costly_func, this_player(), obs);
        } else if (functionp(too_costly_func)) {
            evaluate(too_costly_func, this_object(), obs);
        }
        this_player()->add_failed_mess(this_object(),
          "You don't have any money.\n", obs);
        return 0;
    }
    change = clone_object(MONEY_OBJECT);
    m_array = (int)MONEY_HAND->create_money_array(cost, place);
    for(i = 0; i < sizeof(m_array); i += 2) {
        p_array = (mixed *)MONEY_HAND->make_payment(m_array[i],
          m_array[i + 1], money, place);
        if(!pointerp(p_array)) {
            continue;
        }
        for(j = 0; j < sizeof(p_array[0]); j += 2) {
            money->adjust_money(-p_array[0][j + 1], p_array[0][j]);
        }
        change->adjust_money(p_array[1]);
    }
    do_parse(buy_mess, obs, pl,
      (string)MONEY_HAND->money_string(m_array), "");
    if(stringp(buy_func)) {
        call_other(this_object(), buy_func, pl, obs);
    } else if (functionp(buy_func)) {
        evaluate(buy_func, pl, obs);
    }
    if((int)change->move(pl) != MOVE_OK) {
        tell_object(pl, "You are too heavily burdened to accept "
          "your change, so the shopkeeper puts it on the floor.\n");
        change->move(this_object());
    }
    this_object()->made_transaction(cost, obs);
}
int do_list() {
    object ob;
    if(!is_open(this_player(), 0)) {
        return 0;
    }
    if(objectp(our_storeroom)) {
        ob = our_storeroom;
    } else {
        if ( original_storeroom ) {
            our_storeroom = load_object( original_storeroom );
            ob = our_storeroom;
        }
        else {
            add_failed_mess( "Please notify a creator: the storeroom for "
                "this shop cannot load or has gone missing.\n" );
            return 0;
        }
    }
    if(stringp(list_func)) {
        call_other(this_object(), list_func, this_player());
    } else if (functionp(list_func)) {
        evaluate(list_func, this_player());
    }
    do_parse(list_mess, ({ this_object() }), this_player(), "",
      shop_list(all_inventory(ob), 0));
    return 1;
}
int do_list_these(object *obs) {
    if(!is_open(this_player(), 0)) {
        return 0;
    }
    do_parse(list_mess, ({this_object()}),
      this_player(), "", shop_list(obs, 1));
    return 1;
}
int do_browse(object *obs) {
    int i, value;
    string place;
    if (!is_open(this_player(), 0)) {
        return 0;
    }
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    if(stringp(browse_func)) {
        call_other(this_object(), browse_func, this_player(), obs);
    } else if (functionp(browse_func)) {
        evaluate(browse_func, this_player(), obs);
    }
    for(i = 0; i < sizeof(obs); i++) {
        value = (int)this_object()->query_value(obs[i], 0);
        do_parse(browse_mess, obs[i..i], this_player(),
          (string)MONEY_HAND->money_value_string(value, place),
          (string)obs[i]->long());
    }
    return 1;
}
int do_value(object *obs) {
    int i;
    int val;
    int total;
    string place;
    int obnum;
    if(!is_open(this_player(), 0)) {
        return 0;
    }
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    for(i = 0; i < sizeof(obs); i++) {
        if(obs[i]->do_not_sell() || this_object()->do_not_buy(obs[i]) ||
          (environment(obs[i] ) != this_player()) ||
          (strict_shop &&
            (shop_type != (string)obs[i]->query_property("shop type")))) {
            val = 0;
        } else {
            val = (int)this_object()->query_value(obs[i], 1);
            if (shop_type != (string)obs[i]->query_property("shop type")) {
                val = (val * 90) / 100;
            }
        }
        val = scaled_value(val);
        total += val;
        if(val > (int)this_object()->query_max_amount()) {
            do_parse(too_costly_mess, obs[i..i], this_player(), "",
              (string)obs[i]->do_not_sell());
            total -= val;
        } else if(val < (int)this_object()->query_min_amount()) {
            do_parse(not_worthy_mess, obs[i..i], this_player(), "",
              (string)obs[i]->do_not_sell());
            total -= val;
        } else {
            do_parse(value_mess, obs[i..i], this_player(),
              (string)MONEY_HAND->money_value_string(val, place),
              (string)obs[i]->do_not_sell());
            if(stringp(value_func)) {
                call_other(this_object(), value_func, this_player(), obs,
                  MONEY_HAND->money_string(MONEY_HAND->create_money_array(val,
                      place)));
            } else if (functionp(value_func)) {
                evaluate(value_func, this_player(), obs,
                  MONEY_HAND->money_string(MONEY_HAND->create_money_array(val,
                      place)));
            }
        obnum++;
        }
    }
    if (obnum > 1) {
        write("This gives you a total value of " +
          MONEY_HAND->money_value_string(total, place) +
          ".\n");
        return 1;
    }
    this_player()->add_failed_mess( this_object(), "None of your items are "
        "suitable for sale here!\n", obs );
    return obnum;
}
string shop_list(mixed arr, int detail) {
    int i, j, value, num;
    string s, mon, place, *shorts, *vals;
    object *list;
    mapping inv, costs;
    mixed ind;
    if(pointerp(arr)) {
        list = arr;
    } else {
        list = all_inventory(this_object());
    }
    inv = ([ ]);
    for(i = 0; i < sizeof(list); i++) {
        s = (string)list[i]->short();
        if(!s || !this_object()->query_value(list[i], 1)) {
            continue;
        }
        if(!stringp(s)) {
            s = "get a creator for this one!";
        }
        if(inv[s]) {
            inv[s] += ({list[i]});
        } else {
            inv[s] = ({list[i]});
        }
    }
    s = "";
    shorts = m_indices(inv);
    if(!sizeof(shorts)) {
        if(detail) {
            return "The shop is all out of what you wanted.\n";
        } else {
            return "The shop is totally out of stock.\n";
        }
    }
    s = "You find on offer:\n";
    place = query_property("place");
    if(!place || (place == "")) {
        place = "default";
    }
    for(i = 0; i < sizeof(shorts); i++) {
        ind = inv[shorts[i]];
	num = sizeof(ind);
	if(num == 1 && ind[0]->query_collective())
	  num = ind[0]->query_amount();
        switch(num) {
        case 1:
            s += "Our very last " + shorts[i];
            break;
        case 2..5 :
            s += capitalize(query_num(num, 0)+" "+
			    (string)ind[0]->query_plural());
            break;
        default:
            if(detail) {
                s += capitalize(query_num(num, 0) + " " +
                  (string)ind[0]->query_plural());
            } else {
                s += "A large selection of "+
                (string)ind[0]->query_plural();
            }
        }
        if(detail) {
            costs = ([ ]);
            for(j = 0; j < sizeof(ind); j++) {
                value = (int)this_object()->query_value(ind[j], 0);
                mon = (string)MONEY_HAND->money_value_string(value, place);
                if(!costs[mon]) {
                    costs[mon] = ({""+(j + 1)});
                } else {
                    costs[mon] += ({""+(j + 1)});
                }
            }
            if(m_sizeof(costs) == 1) {
                s += " for "+m_indices(costs)[0];
                if(sizeof(m_values(costs)[0]) > 1) {
                    s += " each.\n";
                } else {
                    s += ".\n";
                }
            } else {
                s += ":-\n";
                vals = m_indices(costs);
                for(j = 0; j < sizeof(vals); j++) {
                    s += "  [#"+implode(costs[vals[j]], ",")+"] for "
                    +vals[j]+".\n";
                }
            }
        } else {
            s += ".\n";
        }
    }
    return s;
}
void set_store_room(mixed ob) {
    if(stringp(ob)) {
        original_storeroom = ob;
        our_storeroom = find_object(ob);
        if(!our_storeroom) {
            our_storeroom = load_object(ob);
        }
    }
    else our_storeroom = ob;
}
void guards(object tp) {
    object ob;
    if(environment(tp) != this_object() && environment(tp) != our_storeroom) {
        return;
    }
    while(!random(6)) {
        ob = create_mercenary(0);
        ob->move(environment(tp));
        ob->attack_ob(tp);
    }
}
object query_store_room() {
    return our_storeroom;
}
void do_parse(mixed arr, object *ob, object client,
  string money, string extra) {
    if(stringp(arr)) {
        this_player()->show_message("$P$List$P$"+
          this_player()->convert_message(replace(arr,
              ({"$ob$", query_multiple_short(ob),
                "$client$", this_player()->short(),
                "$money$", money, "$extra$", extra}))));
        this_player()->add_succeeded_mess(this_object(), "", ob);
    } else if (functionp(arr)) {
        evaluate(arr, ob, client, money, extra);
    } else {
        this_player()->show_message("$P$List$P$"+
          this_player()->convert_message(replace(arr[0],
              ({"$ob$", query_multiple_short(ob),
                "$client$", this_player()->short(),
                "$money$", money, "$extra$", extra}))));
        this_player()->add_succeeded_mess(this_object(),
          ({"", replace(arr[1], ({"$ob$", "$I", "$client$",
                "$N", "$money$", money, "$extra$", extra}))}), ob);
    }
}
string shop_parse(string str, mixed ob, object client, string money,
  string extra, string which) {
    if(sizeof(ob)) {
        str = replace(str, "$ob$", query_multiple_short(ob, which));
    } else {
        str = replace(str, "$ob$", call_other(ob, which +"_short"));
    }
    if(client) {
        str = replace(str, "$client$", client->the_short());
    }
    str = replace(str, ({"$money$", money, "$extra$", extra}));
    return str;
}
void add_other_shop(mixed shop) {
    other_shops += ({shop});
}
string query_shop_type() {
    return shop_type;
}
void set_shop_type(string ty) {
    shop_type = ty;
}
void set_strict_shop(int i) {
    strict_shop = i;
}
int query_strict_shop() {
    return strict_shop;
}
object create_rep() {
    object ob;
    ob = clone_object("/obj/monster");
    ob->set_name("rep");
    ob->set_short("sales rep");
    ob->add_adjective("sales");
    ob->set_long("This is tall strong looking sales rep.  He "
      "stares at you with bright piercing eyes.\n");
    ob->add_alias("Sales rep alias");
    ob->set_guild("fighter");
    ob->set_race("human");
    ob->adjust_bon_str(15);
    ob->set_level(60);
    ARMOURY->request_weapon("dagger", 100)->move(ob);
    ARMOURY->request_armour("cloth robe", 100)->move(ob);
    ob->init_equip();
    ob->add_property("rep type", shop_type);
    all_inventory(ob)->add_property("mine", 1);
    return ob;
}
void send_out_reps() {
    int i;
    object ob;
    for(i = 0; i < sizeof(other_shops); i++) {
        ob = (object)this_object()->create_rep();
        ob->add_property("goto destination", other_shops[i]);
        ob->add_property("goto property", "shop");
        ob->move(this_object(),
          "$N stride$s determinedly into the room.");
        ob->add_triggered_action("froggy", "goto_destination",
          file_name(this_object()), "rep_made_it");
    }
}
void rep_made_it(int bing) {
    object *obs, rep;
    int i, cost;
    if(!bing) {
        previous_object()->init_command("'Oh no!  I am utterly lost!");
        previous_object()->init_command("sigh");
        call_out("set_up_return", 5, previous_object());
        return ;
    }
    rep = present("Sales rep alias",
      (object)previous_object()->query_current_room());
    obs = (previous_object()->query_current_room())->query_stock(shop_type);
    if(!obs) {
        obs = ({ });
    }
    if(!sizeof(obs)) {
        this_object()->none_to_sell();
        call_out("set_up_return", 5, previous_object());
        return ;
    }
    for(i = 0; i < sizeof(obs); i++) {
        if(obs[i]) {
            cost += (int)this_object()->query_value( obs[ i ], 1 ) * 2 / 3;
        }
    }
    call_out("do_rep_buy", 5, ({previous_object(), obs, cost}));
    cost += (int)this_object()->query_value(obs[i], 1) * 2 / 3;
    call_out("do_rep_buy", 5, ({previous_object(), obs, cost}));
    previous_object()->adjust_value(cost);
}
object create_mercenary(object rep) {
    object ob;
    string nam;
    if(rep) {
        nam = implode(rep->query_adjectives(), " ")+" "+rep->query_name();
    }
    ob = clone_object("/obj/monster");
    ob->set_name("mercenary");
    ob->add_alias("troll");
    ob->add_adjective("troll");
    ob->set_short("troll mercenary");
    ob->set_main_plural("troll mercenaries");
    ob->set_race("troll");
    ob->set_class("fighter");
    ob->set_level(200 + random(200));
    ob->set_long("This is a large, hulking troll.  He looks "
      "quite competent and capable of mashing you with or "
      "without a weapon.\n");
    if(rep) {
        ob->move(environment(rep));
        ob->do_command("follow "+nam);
        ob->do_command("protect "+nam);
        ob->add_property("merchant", rep);
    } else {
        ARMOURY->request_weapon("spiked club", 100)->move(ob);
    }
    ob->set_natural(1);
    ob->init_equip();
    ob->set_join_fights("Troll yells something incomprehensible.\n");
    ob->set_join_fight_type(0);
    return ob;
}
object *query_stock(string type) {
    mapping blue;
    blue = (mapping)our_storeroom->query_shop_type_mapping();
    if(!blue[type]) {
        return ({ });
    }
    return blue[type];
}
void do_rep_buy(mixed *bing) {
    object rep, *obs;
    int cost;
    rep = bing[0];
    obs = bing[1];
    cost = bing[2];
    rep->adjust_money(cost, "brass");
    rep->query_current_room()->do_buy(obs, cost, rep);
    obs->move(present("Sales rep alias", rep->query_current_room()));
    call_out("set_up_return", 5, rep);
}
void set_up_return(object rep) {
    rep->add_property("goto destination", file_name(this_object()));
    rep->add_triggered_action("froggy", "goto_destination",
      this_object(), "rep_came_back");
}
void rep_came_back() {
    int i;
    object *obs, *obs2, rep;
    obs = previous_object()->find_inv_match("all", previous_object());
    obs2 = ({ });
    for(i = 0; i < sizeof(obs); i++) {
        if(obs[i]->query_property("mine")) {
            continue;
        }
        if(obs[i]->query_property("money")) {
            continue;
        }
        obs[i]->move(our_storeroom);
        obs2 += ({obs[i]});
    }
    if(sizeof(obs2)) {
        tell_room(this_object(), previous_object()->short()+" puts "+
          query_multiple_short(obs2)+" into the stock.\n");
    }
    rep = present("Sales rep alias",
      (object)previous_object()->query_current_room());
    obs = all_inventory(this_object());
    obs2 = ({ });
    for(i = 0; i < sizeof(obs); i++) {
        if((object)obs[i]->query_property("merchant") == rep) {
            obs2 += ({ obs[i] });
        }
    }
    if(sizeof(obs2)) {
        tell_room(this_object(),
          query_multiple_short(obs2+({previous_object()}), "one")+" go away.\n");
    } else {
        tell_room(this_object(), previous_object()->short()+" goes away.\n");
    }
    obs2->dest_me();
    previous_object()->dest_me();
}
void summon_guards(object tp) {
    object ob;
    int i;
    if(environment(tp) != this_object()) {
        return;
    }
    ob = environment(tp)->create_mercenary(0);
    if(!ob) {
        return;
    }
    ob->move(this_object(),
      "$N charge$s in to protect the shop!");
    ob->attack_ob(tp);
    for(i = 0; i < random(5); i++) {
        ob = create_mercenary(0);
        ob->move(this_object(),
          "$N charge$s in to protect the shop!");
        ob->attack_ob(tp);
    }
}
void set_strict_currency( int new_strict ) {
    _strict_currency = new_strict;
}
int query_strict_currency() {
    return _strict_currency;
}
void event_shoplift(object command_ob, object thief, object victim) {
    if(stringp(shoplift_handler)) {
        if(shoplift_handler != "none") {
            shoplift_handler->handle_shoplift(thief, victim);
        }
    } else if (functionp(shoplift_handler)) {
        evaluate(shoplift_handler, thief, victim);
    } else {
        "/obj/handlers/theft_handler"->handle_shoplift(thief, victim);
    }
}
void tidy_inventory() {
    object storeob;
    object *inventory;
    int i, inv_to_leave;
    int count;
    inv_to_leave = max_inventory - (max_inventory / 4);
    if(objectp(our_storeroom)) {
        storeob = our_storeroom;
    } else {
        our_storeroom->rabbit_away();
        storeob = find_object(our_storeroom);
    }
    if(sizeof(all_inventory(storeob)) < inv_to_leave)
        return;
    inventory = all_inventory(storeob);
    while(sizeof(inventory) > inv_to_leave) {
        i = random(sizeof(inventory));
        if(inventory[i])
            inventory[i]->dest_me();
        if(count++ > 500)
            break;
        inventory = all_inventory(storeob);
    }
}
void dest_me() {
    if(our_storeroom)
        our_storeroom->dest_me();
    ::dest_me();
}
mixed *stats() {
    return ::stats()+({
      ({"total sold", amount_sold}),
      ({"total bought", amount_bought}),
      ({"shop type", shop_type}),
      ({"shoplift handler", shoplift_handler }),
      ({"strict shop", strict_shop})});
}