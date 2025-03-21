#include <money.h>
mixed *accept_sayings, *bodged_sayings, *finalb_sayings,
    *finals_sayings, *insult_sayings, *offerb_sayings,
    *offers_sayings, *sodoff_sayings;
void create() {
  accept_sayings = ({
      ({ "grin", "Done!" }),
      "Accepted!",
      "Fine...",
      ({ "smile", "Agreed!" }),
      ({ "mutter", "Okay..." }),
      "Taken!",
      "You drive a hard bargain, but taken...",
      "You'll make me bankrupt, but it's a deal...",
      ({ "sigh", "I'll take it..." }),
      "My poor sick children will starve, but done!",
      "Finally!  I accept...",
      ({ "grimace", "Robbed again..." }),
      "A pleasure to do business with you!",
      ({ "scowl", "My spouse will have my hide, but accepted." }) });
  bodged_sayings = ({
      "I must have heard you wrong...",
      "What was that?",
      "I'm sorry, say that again...",
      "What did you say?",
      "Sorry, what was that again?" });
  finalb_sayings = ({
      "I'll pay no more than $offer$; take it or leave it.",
      "You'll get no more than $offer$ from me.",
      "$offer$ and that's final." });
  finals_sayings = ({
      "$asking$ is my lowest price; take it or leave it...",
      "It'll cost you no less than $asking$.",
      "My patience grows thin... $asking$ is final." });
  insult_sayings = ({
      "You will have to do better than that!",
      "That's an insult!",
      "Do you wish to do business or not?",
      "Hah!  Try again...",
      "Ridiculous!",
      "You've got to be kidding!",
      "You'd better be kidding!",
      "You're trying my patience...",
      "I didn't hear that.  Say it again?",
      "Hmmm... Nice weather we're having..." });
  offerb_sayings = ({
      "$asking$ for that piece of junk?  No more than $offer$.",
      "For $asking$ I could own ten of those.  Try $offer$.",
      "$asking$?!?  Never!  $offer$ is more like it...",
      "Let's be reasonable...  How about $offer$?",
      ({ "cough", "$offer$ for that junk, no more..." }),
      "$offer$ and be thankful for it!",
      "$offer$ and not an iotum more...",
      "$asking$?  Ha!  $offer$ is more like it...",
      "Try $offer$...",
      "I wouldn't pay $asking$ for your children!  Try $offer$.",
      ({ "choke", "For that?!?  Let's say $offer$." }),
      "How about $offer$?",
      "That looks like army surplus!  Say $offer$.",
      "I'll buy it as scrap for $offer$.",
      "$asking is too much; let us say $offer$." });
  offers_sayings = ({
      "$offer$ for such a fine item?  Hah!  No less than $asking$.",
      "$offer$ is an insult!  Try $asking$...",
      "$offer$?!?  You would rob my poor starving children?  "+
          "Even they would give $asking$ for this.",
      "Why, I'll take no less than $asking$.",
      ({ "cackle", "No less than $asking$." }),
      "You swine!  No less than $asking$.",
      "$offer$ is far too little;  how about $asking$?",
      "I paid more than $offer$ for it myself!  Try $asking$.",
      ({ "boggle", "$offer$?  Are you mad?!?  How about $asking$?" }),
      "As scrap this would bring $offer$.  Try $asking$.",
      "May the fleas of a thousand camels molest you.  "+
          "I want $asking$.",
      "My mother you can get for $offer$, "+
          "this will cost you $asking$.",
      "May your chickens grow lips!  I want $asking$!",
      "Sell this for such a pittance?  Give me $asking$.",
      "May the Grflx find you tasty!  $asking$?",
      "Your mother was a troll!  $asking$ or I'll tell..." });
  sodoff_sayings = ({
      ({ "Enough!",
          "You have abused my generosity once too often!",
          "Out of my establishment!" }),
      ({ "That does it!",
          "You will waste my time no more!",
          "Out...  Out...  OUT!!!" }),
      ({ "This is getting nowhere!",
          "Leave me alone!",
          "Come back tomorrow..." }),
      ({ "Bah!",
          "No more will you insult me!",
          "Leave my place!  Begone!" }),
      ({ "Begone!",
          "I have had enough abuse for one day.",
          "Come back when you're richer..." }) });
}
int insult_factor( object keeper, object customer ) {
  return 150;
}
int bargain_factor( object keeper, object customer ) {
  return 50;
}
int *sell_haggle( int value, int offer, int asking, int insults,
    string place, object keeper, object customer ) {
  int adjustment, number;
  string text;
  if ( offer > asking ) {
    keeper->do_command( "boggle" );
    number = random( sizeof( bodged_sayings ) );
    keeper->do_command( "'"+ bodged_sayings[ number ] );
    return ({ 0, asking, insults });
  }
  if ( offer == asking ) {
    number = random( sizeof( accept_sayings ) );
    if ( sizeof( accept_sayings[ number ] ) == 2 ) {
      keeper->do_command( accept_sayings[ number ][ 0 ] );
      keeper->do_command( "'"+ accept_sayings[ number ][ 1 ] );
    } else
      keeper->do_command( "'"+ accept_sayings[ number ] );
    return ({ 1, asking, insults });
  }
  if ( ( offer * insult_factor( keeper, customer ) ) >
      ( asking * 100 ) ) {
    adjustment = ( ( asking - offer ) *
        bargain_factor( keeper, customer ) ) / 100;
    if ( adjustment < 0 ) adjustment = 0;
    asking -= adjustment;
    number = random( sizeof( offers_sayings ) );
    if ( sizeof( offers_sayings[ number ] ) == 2 ) {
      keeper->do_command( offers_sayings[ number ][ 0 ] );
      text = offers_sayings[ number ][ 1 ];
    } else
      text = offers_sayings[ number ];
    text = replace( text, "$offer$",
        (string)MONEY_HAND->money_value_string( offer, place ) );
    text = replace( text, "$asking$",
        (string)MONEY_HAND->money_value_string( asking, place ) );
    keeper->do_command( "'"+ text );
    return ({ 0, asking, insults });
  }
  insults++;
  if ( insults < (int)keeper->query_property( "max insults" ) ) {
    number = random( sizeof( insult_sayings ) );
    keeper->do_command( "'"+ insult_sayings[ number ] );
    return ({ 0, asking, insults });
  }
  number = random( sizeof( sodoff_sayings ) );
  keeper->do_command( "lsay "+ sodoff_sayings[ 0 ] );
  keeper->do_command( "'"+ sodoff_sayings[ 1 ] );
  keeper->do_command( "'"+ sodoff_sayings[ 2 ] );
  return ({ 0, 0, -1 });
}