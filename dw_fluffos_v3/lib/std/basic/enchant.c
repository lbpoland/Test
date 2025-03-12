nosave private int _enchanted;
nosave private int _set_enchant_time;
nosave private int _degrade_enchant;
#define ENCHANT_DEGRADE_TIME (8 * 7 * 24 * 60 * 60)
int query_max_enchant()
{
   return 5 + (int) this_object()->query_weight() / 4;
}
int query_degrade_enchant() {
   if (!_degrade_enchant) {
      return this_object()->query_max_enchant() / 2;
   }
   return _degrade_enchant;
}
void set_degrade_enchant(int enchant) {
   if (enchant > this_object()->query_max_enchant()) {
      enchant = this_object()->query_max_enchant();
   }
   _degrade_enchant = enchant;
}
string enchant_string()
{
   string tal_msg;
   string ench_msg;
   if (this_object()->query_property("talisman")) {
      tal_msg = (string) this_object()->query_property("talisman_mess");
      if (!tal_msg)
         tal_msg = "It has the hazy octarine sparkle of a magical talisman.";
      tal_msg += "\n";
   } else {
      tal_msg = "";
   }
   if (this_object()->query_property("octarine_mess")) {
      ench_msg = (string) this_object()->query_property("octarine_mess")
         + "\n";
   } else {
      switch ((this_object()->query_enchant() * 100) /
              this_object()->query_max_enchant()) {
      case 1..10:
         ench_msg = "It occasionally pulses with octarine light.\n";
         break;
      case 11..20:
         ench_msg = "It emits a slight octarine glow.\n";
         break;
      case 21..30:
         ench_msg = "It softly pulses in dull octarine shades.\n";
         break;
      case 31..40:
         ench_msg = "It gives off a steady but dull octarine glow.\n";
         break;
      case 41..50:
         ench_msg = "It gives off a steady octarine glow.\n";
         break;
      case 51..60:
         ench_msg = "It glows an intense octarine.\n";
         break;
      case 61..70:
         ench_msg = "It emits a bright octarine colour.\n";
         break;
      case 71..80:
         ench_msg = "It brightly pulses octarine.\n";
         break;
      case 81..90:
         ench_msg = "It glows brilliant octarine shades.\n";
         break;
      case 91..100:
         ench_msg = "It radiates pure octarine brilliance.\n";
         break;
      default:
         ench_msg = "";
      }
   }
   return ench_msg + tal_msg;
}
void set_enchant(int number)
{
   if (number > this_object()->query_max_enchant()) {
      number = this_object()->query_max_enchant();
   }
   _set_enchant_time = time();
   _enchanted = number;
}
int add_enchant(int number)
{
   set_enchant(this_object()->query_enchant() + number);
   return _enchanted;
}
int query_enchant()
{
   int max;
   int tmp;
   int tmp2;
   int degrade;
   max = this_object()->query_max_enchant();
   if (_enchanted > max) {
      _enchanted = max;
   }
   degrade = this_object()->query_degrade_enchant();
   if (_enchanted > degrade) {
      if (!_set_enchant_time) {
         _set_enchant_time = time();
      }
      if (time() - _set_enchant_time >= ENCHANT_DEGRADE_TIME) {
         _enchanted = degrade;
      } else {
         tmp2 = tmp = (_enchanted - degrade) * 100 + 99;
         tmp *= 100 - (((time() - _set_enchant_time) * 100) /
                       ENCHANT_DEGRADE_TIME);
         return degrade + (tmp / 10000);
      }
   }
   return _enchanted;
}
int query_real_enchant()
{
   return _enchanted;
}
int query_enchant_set_time()
{
   return _set_enchant_time;
}
protected void set_enchant_set_time(int tim)
{
   _set_enchant_time = tim;
}