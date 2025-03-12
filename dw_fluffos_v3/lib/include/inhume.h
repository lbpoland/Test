#ifndef __SYS__INHUME
#define __SYS__INHUME
#ifdef LOG
#undef LOG
#endif
#undef DEBUG
#define INHUME "/obj/handlers/secure_handlers/inhume"
#define NO_INHUME_PROP  "cannot inhume"
#define NO_CONTRACT_PROP "cannot place contracts"
#define LOGDIR          "/log/secure/assassins/"
#define LOG             ( LOGDIR + "INHUME" )
#define INHUMED         ( LOGDIR + "INHUMED" )
#define RECEIPTS        ( LOGDIR + "INHUME_RECEIPTS" )
#define LOGFILE         ( LOGDIR + "inhume_debug" )
#define PLAY_LOG        ( LOGDIR + "play_inhume_debug" )
#define TM_LOG          ( LOGDIR + "INHUME_TMS" )
#define NPC_LOG         ( LOGDIR + "NPC_CONTRACTS" )
#define CONTRACT_NO_LOCATION 10
class contract {
   int status;
   string bastard;
   int value;
   int time;
   int reveal;
   string message;
   string name;
   string place;
   int nodeath;
   string originator;
   string location;
}
#define EXP_TIME   2419200
#define TAXES      40
#define SURCHARGE  10
#define NOTME_MULT 1.1
#define MIN_LEVEL  50
#define PK_MULT    0
#define COST_MULT  ( 5 * 400 )
#define COST_GUILD ( 6 * 400 )
#define MAXTIMES 4
#define NO_DEATH_MULT 0.5
#define LOW          -1
#define NON_KILLER   -2
#define CRE          -3
#define TOO_SOON     -4
#define REQUESTED 0
#define VALIDATED 1
#define INFORMED 2
#define ACTIVE 3
#define SPECIAL 4
#define INHUME_COLLECT_NONE   0
#define INHUME_COLLECT_REFUND 1
#define INHUME_COLLECT_WAGES  2
#define INHUME_COLLECT_MIXED  3
#define INHUME_PK_THRESH_GUILD_LEVEL   175
#define INHUME_PK_THRESH_NUM_CONTRACTS 4
#define INHUME_PK_THRESH_AGE_DAYS      10
#define REPEAT_RATE ( 60 * 60 * 24 * 7 * 2 )
#define NPC_TIME ( 60 * 60 * 24 * 7 * 2 )
#define INHUME_ON_SIGHT_THRESH 10
#define INHUME_CRIME_EXPIRY_TIME ( 60 * 60 * 24 * 3 )
#define INHUME_NPC_WAIT_TIME ( 60 * 60 * 12 )
#endif