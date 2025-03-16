int roll_MdN( int dice, int sides ) {
   int roll;
   if ( ( dice > 0 ) && ( sides > 0 ) ) {
      while ( dice ) {
         roll += 1 + random( sides );
         dice--;
      }
   }
   return roll;
}