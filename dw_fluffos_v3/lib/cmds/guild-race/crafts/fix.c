#include <money.h>
#include <tasks.h>
#define TEACH_LEVEL 10
#define LEARN_LEVEL 10
#define SKILL "crafts.smithing.black"
#define SKILLS ({ "crafts.smithing.black.weapons", \
                  "crafts.smithing.black.armour", \
                  "crafts.smithing.black.tools" })
#define A_MAX 5
#define C_MAX 100
#define A_COND 5
#define C_COND 25
#define SCALE 50
#define USE_WEAPON_SKILL 1
#define USE_ARMOUR_SKILL 2
#define USE_TOOL_SKILL 3
inherit "/cmds/guild_base";
int query_item_type( object ob );
int query_fix_cost( object player, object smithy, object item, int costing, int max, int cond, int low );
int test_fixed( object item );
void create() {
   ::create();
   set_nroff_file("fix");
   set_command_name("fix");
   add_teach_skill(SKILL, 10, 10);
}
object find_smithy(object player) {
   if (environment(player)->query_property("smithy")) {
      return environment(player);
   }
   foreach (object ob in all_inventory(player)) {
      if (ob->query_smithy()) {
         return ob;
      }
   }
   return 0;
}
int cmd( object *things, int costing ) {
    int type, bonus, cond, low, max, diff, cost, val, award;
    int new_cost;
    object here, item, fixer;
    string place;
    fixer = this_player();
    here = find_smithy(fixer);
    if ( !here || !here->query_property( "smithy" ) ) {
        add_failed_mess( "You are not in a smithy, so you cannot fix "
            "anything.\n" );
        return 0;
    }
    place = here->query_property( "place" );
    if ( !place || ( place == "" ) )
        place = "default";
    if ( sizeof( things ) > 1 ) {
        add_failed_mess( "You can only fix one thing at a time.\n" );
        return 0;
    }
    item = things[ 0 ];
    type = query_item_type( item );
    if ( !type ) {
      add_failed_mess( "$I is neither armour nor a weapon.\n", things );
      return 0;
    }
    if ( item->query_worn_by() ) {
        add_failed_mess( "You should probably remove $I before making it "
                         "hot and hitting it with a hammer.\n", things );
        return 0;
    }
    if( member_array( "leather", item->query_materials() ) != -1 ) {
      add_failed_mess( "$I would be destroyed if you put it in the fire.\n",
                       things );
      return 0;
    }
    if( member_array( "wool", item->query_materials() ) != -1 ) {
      add_failed_mess( "Putting a woolen item in the fire isn't going "
                       "to improve its condition.\n",
                       things );
      return 0;
    }
    if( item->query_unfixable() ) {
        add_failed_mess( "Sticking $I in a hot forge probably isn't "
            "going to do much for its condition.\n", things );
        return 0;
    }
    bonus = (int)fixer->query_skill_bonus( SKILLS[ type - 1 ] );
    val = (int)fixer->query_value_in( place );
    if ( place != "default" )
        val += (int)fixer->query_value_in( "default" );
    low = (int)item->query_lowest_cond();
    if ( !low )
        low = 1;
    cond = (int)item->query_cond();
    max = (int)item->query_max_cond();
    if ( !max )
        max = 1;
    if ( test_fixed( item ) ) {
        add_failed_mess( "$I is already in top condition.\n", things );
        return 0;
    }
    diff = max - cond;
    cost = query_fix_cost( this_player(), here, item, costing, max, cond, low );
    new_cost = here->generate_cost(cost, 0);
    if (new_cost == -1) {
       return 0;
    }
    if (new_cost) {
       cost = new_cost;
    }
    if ( ( diff > bonus ) && !costing ) {
        diff = ( 150 * diff ) / max;
        switch ( (int)TASKER->perform_task( fixer,
            SKILLS[ type-1 ], diff, TM_COMMAND ) ) {
            case AWARD :
                award = 1;
            case SUCCEED :
                diff = max - cond;
            break;
            default :
                diff = bonus;
        }
    }
    if ( ( val < cost ) &&
         !fixer->query_property( "freelance smith" ) && !costing ) {
        add_failed_mess( "You cannot afford the materials to fix "
            "$I.\n", things );
        return 0;
    }
    if ( costing ) {
      add_succeeded_mess( ({ "To attempt to fix $I, it would probably cost "
        "you about " + MONEY_HAND->money_value_string( cost, place ) +
        ".\n", "" }), things );
        return 1;
    }
    if ( !cond ) {
        add_succeeded_mess( ({ "You begin to work on $I when it breaks!  "
            "It must have been too damaged to fix.\n",
            "$N begin$s to work on $I when it breaks!\n" }), things );
        item->break_me();
        return 1;
    }
    item->adjust_cond( diff );
    if ( !fixer->query_property( "freelance smith" ) ) {
        fixer->pay_money( (mixed *)MONEY_HAND->create_money_array( cost,
            place ), place );
        here->generate_cost(cost, 1);
    }
    if ( award ) {
        write( "%^YELLOW%^"+ replace( ({ "As you begin to fix $I, you realise "
            "how to make better use of the materials.", "As you work on $I, "
            "you find that you're able to fix it completely.", "You discover "
            "that you can fix $I more effectively." })[ random( 3 ) ], "$I",
            item->the_short() ) +"%^RESET%^\n" );
    }
    if ( test_fixed( item ) )
        write( "You fix "+ item->the_short() +
        ", bringing it to top condition.\n" );
    else
        write( "You manage to fix "+ item->the_short() +
            " a little, although it's still not in top condition.\n" );
    write( "The repair materials cost you " +
        MONEY_HAND->money_value_string( cost, place ) +".\n" );
    add_succeeded_mess( ({ "", "$N fixes up $I.\n" }), things );
    return 1;
}
int test_fixed( object item ) {
    return ( 100 * item->query_cond() > 98 * item->query_max_cond() );
}
int query_item_type( object ob ) {
    if ( ob->query_weapon() == 1 ) {
        return USE_WEAPON_SKILL;
    }
    if ( ob->query_armour() || ob->query_scabbard() ) {
        return USE_ARMOUR_SKILL;
    }
    if ( ob->query_material() == "metal" ) {
        return USE_TOOL_SKILL;
    }
    return 0;
}
int query_fix_cost( object player, object smithy,
                            object item, int costing, int max, int cond, int low ) {
    int cost, diff, per;
    if ( !max )
        max = item->query_max_cond();
    if ( !cond )
        cond = item->query_cond();
    if ( !low )
        low = item->query_lowest_cond();
    diff = max - cond;
    per = 100 - smithy->query_discount( player );
    if ( per < 0 )
        per = 0;
    cost = ( diff * sqrt( item->query_full_value() ) ) / max;
    cost *= A_MAX + ( C_MAX * ( max - low ) ) / max;
    cost *= A_COND + ( C_COND * ( cond - low ) ) / ( cond + !cond );
    cost /= SCALE;
    if ( costing ) {
        cost *= 2;
    }
    else {
        cost += roll_MdN( 4, cost / 4 );
    }
    cost = ( cost * per ) / 100;
    if ( cost < 100 ) {
        cost = 100;
    }
    return cost;
}
mixed *query_patterns() {
  return ({ "<indirect:object:me>", (: cmd($1, 0) :),
            "cost <indirect:object:me>", (: cmd($1, 1) :) });
}