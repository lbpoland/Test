#define CREATOR "Ceres"
#include <player.h>
#include <move_failures.h>
#include <tasks.h>
#define ASKILL "fighting.combat.range.thrown"
#define DSKILL "fighting.combat.dodging.range"
#define PSKILL "fighting.combat.parry.range"
#define COMMAND_GP_COST 5
inherit "/cmds/base";
int valid_target( object target, object thrower, object item );
int cmd( mixed *indirect_obs ) {
    object target, item;
    int dchance, damage;
    if ( sizeof( indirect_obs[ 0 ] ) > 1 ) {
        add_failed_mess( "You can only throw one item at a time!\n" );
        return 0;
    }
    item = indirect_obs[ 0 ][ 0 ];
    if ( sizeof( indirect_obs[ 1 ] ) > 1 ) {
        add_failed_mess( "You can only throw $I at one target at a time!\n",
            ({ item }) );
        return 0;
    }
    target = indirect_obs[ 1 ][ 0 ];
    if ( item->query_wielded() != this_player() ) {
        add_failed_mess( "You must be holding $I to throw it.\n",
            ({ item }) );
        return 0;
    }
    if ( this_player() == target ) {
        add_failed_mess( "You cannot throw $I at yourself!\n", ({ item }) );
        return 0;
    }
    if ( !living( target ) && !target->query_property( "targetable" ) ) {
        add_failed_mess( "Why do you want to throw $I at " +
            target->the_short() + "?\n", ({ item }) );
        return 0;
    }
    if (this_player()->query_gp() < COMMAND_GP_COST) {
        add_failed_mess( "You need " + COMMAND_GP_COST + " points to "
            "throw " + item->the_short() + " at " + target->the_short() +
            ".\n");
        return 0;
    }
    if ( !valid_target( target, this_player(), item ) ) {
        add_failed_mess( "You decide against throwing $I at " +
            target->the_short() + ".\n", ({ item }) );
        return 0;
    }
    if ( living( target ) ) {
        switch ( (string)target->query_combat_response() ) {
            case "dodge" :
                dchance = target->query_skill_bonus( DSKILL );
            break;
            default:
                dchance = target->query_skill_bonus( PSKILL );
        }
    }
    else {
        dchance = target->query_property( "targetable" );
    }
    dchance += item->query_weight() / ( this_player()->query_str() / 2 );
    if( !this_player()->query_visible( target ) ) {
        dchance /= 2;
    }
    this_player()->adjust_gp(-COMMAND_GP_COST);
    switch( TASKER->perform_task(this_player(), ASKILL, dchance, TM_FREE) ) {
        case AWARD:
            tell_object(this_player(), "%^YELLOW%^You feel that your "
                "skill in throwing weapons has increased.%^RESET%^\n");
        case SUCCEED:
            tell_object( this_player(), "You throw " + item->the_short() +
                " at " + target->the_short() + " and hit!\n" );
            tell_room( environment( this_player() ),
                this_player()->the_short() + " throws " + item->a_short() +
                    " at " + target->the_short() + " and hits!\n",
                    this_player() );
            if ( living( target ) ) {
                damage = ( item->query_weight() / 4 ) +
                    ( this_player()->query_str() * 2) +
                    ( this_player()->query_skill_bonus( ASKILL ) / 3 );
                damage -= target->query_ac( "blunt", damage );
                target->attack_by( this_player() );
                target->adjust_hp( -damage, this_player() );
                this_player()->attack_ob( target );
                event( item, "thrown", this_player(), target );
                    this_player()->adjust_time_left(-(ROUND_TIME*2));
            }
            target->thrown_at( this_player(), 1, item );
            if ( item->move( target ) != MOVE_OK ) {
                item->move( environment( target ) );
            }
        break;
        default:
            tell_object( this_player(), "You throw " + item->the_short() +
                " at " + target->the_short() + " but miss.\n" );
            tell_room( environment( this_player() ),
                this_player()->the_short() + " throws " + item->a_short() +
                " at " + target->the_short() + " but misses.\n", this_player() );
            item->move( environment( target ) );
            if( !interactive( target ) && living( target ) ) {
                this_player()->attack_ob( target );
                target->attack_by( this_player() );
            }
            target->thrown_at( this_player(), 0 );
        break;
    }
    return 1;
}
int valid_target( object target, object thrower, object item ) {
    mixed owner;
    if ( target->query_property( "dead" ) || target->query_auto_loading() ) {
        return 0;
    }
    if ( userp( target ) && !interactive( target ) ) {
        return 0;
    }
    if ( pk_check( thrower, target ) )
        return 0;
    if ( ( owner = target->query_owner() ) && pk_check( thrower, owner ) ) {
        return 0;
    }
    return 1;
}
mixed *query_patterns() {
    return ({ "<indirect:object:me'weapon'> at <indirect:object'target'>",
        (: cmd($1) :) });
}