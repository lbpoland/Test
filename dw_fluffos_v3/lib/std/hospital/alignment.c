#define TOTAL_CHANCE 150
#define CENTRE 0
#define LIMIT_ONE     35
#define LIMIT_TWO     68
#define LIMIT_THREE   95
#define LIMIT_FOUR   115
#define LIMIT_FIVE   130
#define LIMIT_SIX    139
#define LIMIT_SEVEN  145
#define LIMIT_EIGHT  147
#define LIMIT_NINE   149
int pick_al( int average, int range ) {
   int choice, section, section_width, result;
   if( range < 0 ) {
      range = -range;
   }
   if( range < 10 ) {
      range = 10;
   }
   section_width = floor( range / 10 );
   choice = random( TOTAL_CHANCE );
   switch( choice ) {
      case CENTRE..LIMIT_ONE:
         section = 0;
         break;
      case ( LIMIT_ONE + 1 )..LIMIT_TWO:
         section = 1;
         break;
      case ( LIMIT_TWO + 1 )..LIMIT_THREE:
         section = 2;
         break;
      case ( LIMIT_THREE + 1 )..LIMIT_FOUR:
         section = 3;
         break;
      case ( LIMIT_FOUR + 1 )..LIMIT_FIVE:
         section = 4;
         break;
      case ( LIMIT_FIVE + 1 )..LIMIT_SIX:
         section = 5;
         break;
      case ( LIMIT_SIX + 1 )..LIMIT_SEVEN:
         section = 6;
         break;
      case ( LIMIT_SEVEN + 1 )..LIMIT_EIGHT:
         section = 7;
         break;
      case ( LIMIT_EIGHT + 1 )..LIMIT_NINE:
         section = 8;
         break;
      default:
         section = 9;
         break;
   }
   result = section * section_width;
   result = result + random( section_width );
   switch( random( 2 ) ) {
      case( 0 ):
         result = average + result;
         break;
      default:
         result = average - result;
         break;
   }
   result = result + average;
   return result;
}