#ifndef __VAULT_H
#define __VAULT_H
#include <money.h>
#define FEE_AMT 100
#define INIT_AMT 2000
#define FEE_AMT_STRING (string)(MONEY_HAND->money_value_string(100, this_object()->query_property("place")))
#define INIT_AMT_STRING (string)(MONEY_HAND->money_value_string(2000, this_object()->query_property("place")))
#define VAULT_SAVE "/save/vaults/"
#endif