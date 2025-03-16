#define CREATOR "calroth"
#define UNSET_STR "__RINGO_WOZ_ERE__"
#define PSOBJDIR "/obj/misc/player_shop/"
#define CABINET (PSOBJDIR + "shop_cabinet")
#define BADGE (PSOBJDIR + "shop_badge")
#define STAFF_BOOK (PSOBJDIR + "staff_book")
#define MGR_BOOK (PSOBJDIR + "mgr_book")
#define SHOP_BAG (PSOBJDIR + "shopping_bag")
#define SHOP_CHART (PSOBJDIR + "shop_chart")
#define SHOP_NOTICE (PSOBJDIR + "shop_notice")
#define TRUE 1
#define FALSE 0
#define PAID 1
#define UNPAID 0
#define EMP_POINTS 0
#define EMP_BANK 1
#define EMP_PAY 2
#define EMP_INACTIVE 3
#define EMP_NOBONUS 4
#define EMP_NOPROMOTE 5
#define EMP_EOM 6
#define EMPLOYEE 1
#define NPC 2
#define SUPERVISOR 4
#define MANAGER 8
#define CLOCKED_IN 16
#define EMP_MAP ({EMPLOYEE,0,0,0,1,0,0,})
#define MANAGER_POINTS 1000
#define SUPER_POINTS 500
#define BAD_REASON 0
#define BAD_BANNER 1
#define BAD_TIME 2
#define BAD_MAP ({"","",0,})
#define APP_TYPE 0
#define APP_TIME 1
#define APP_FOR 2
#define APP_AGAINST 3
#define APP_ABSTAIN 4
#define APP_MESSAGE 5
#define APPLIED 1
#define HIRED 2
#define AWAITING 3
#define VFOR      1
#define VAGAINST  0
#define VABSTAIN -1
#define APP_MAP ({APPLIED,0,({}),({}),({}),"",})
#define MIN_CABINETS 5
#define MAX_CABINETS 20
#define STOCK_PER_CABINET 50
#define MAX_STOCK (MAX_CABINETS * STOCK_PER_CABINET)
#define CABINET_COST 400000
#define LOG_ENTRY 1
#define PURCHASE 2
#define SALE 3
#define PERSONNEL 4
#define ACCOUNTS 5
#define GENERAL 6
#define CHARTLOG 7
#define CHART_MAX 0
#define CHART_AVE 1
#define CHART_BUY 2
#define CHART_SELL 3
#define CHART_CAB 4
#define CHART_AVESALE 5
#define CHART_SOLD 6
#define CHART_BOUGHT 7
#define POLICY_TIME 0
#define POLICY_MGR 1
#define POLICY_TEXT 2
#define POLICY_FOR 3
#define POLICY_AGAINST 4
#define POLICY_TYPE 5
#define POLICY_MAP ({0,"","",({}),({}),0,})
#define PLAYER_SHOP "/obj/handlers/player_shop"
#define HISTORY_HANDLER "/obj/handlers/hist_handler"
#define BANK_HANDLER "/obj/handlers/bank_handler"
#define PLAYER_HANDLER "/obj/handlers/player_handler"
#define BANKS ({ ({ "Bing's First National", "Bing's First", }), \
                 ({ "Lancrastian Farmers' Co-operative", "LFC", }), \
                 ({ "Klatchian Continental", "Klatchian Continental", }), \
              })
#define BELL_TIMEOUT 120
#define MIN_EMP 10
#define MAX_EMP 40
#define PERCENT_M 10
#define PERCENT_S 20
#define START_PAY 20
#define MAX_LEAVE 14
#define BAN_LENGTH 28
#define DECLINE_LENGTH 14
#define MGR_DEMOTE 14
#define MGR_WARN 7
#define SPR_DEMOTE 28
#define SPR_WARN 14
#define EMP_FIRE 62
#define EMP_WARN 14
#define MAX_BAG_ITEMS 10
#define MAX_BAG_WEIGHT 50
#define LOG_DAYS 14
#define HIRE_TIMEOUT (86400*14)
#define HIST_TIMEOUT (86400*91)
#define VOTE_TIMEOUT (86400*14)
#define NPC_DELAY (2 + random(3))
#define NPC_RELOAD 3600
#define SAVE_DELAY 1
#define PERS_DELAY 5
#define CLEAR_DELAY 300
#define COMPLAINT_TEXT "Please fully state your complaint below.  " \
                       "Include as much detail as you can and any " \
                       "evidence/witnesses to support your complaint."
#define SUGGEST_TEXT "Please detail your suggestion below."
#define APP_QUESTIONS ({ "Why do you want to work for "+ \
                     _office->query_shop_name()+ "?", \
                     "What is your (DW) age?", \
                     "What Guild do you belong to?", \
                     "What relevant experience do you have of collecting " \
                      " and/or recognising our stock?", \
                     "How much time (hours/week) do you think you can " \
                     "commit to the shop?  Please also tell us at what " \
                     "time you will usually be on.", \
                     "Do you already know anyone who is an employee " \
                     "here, who could recommend you?  If so, who?", \
                     "Have you previously held a position at this shop?  " \
                     "If so, why did you leave?", \
                     "Do you currently work at any other shop?", \
                     "Have you applied for employment here before?  " \
                     "If so, what was the outcome?", \
                     "Do you have anything else you'd like to tell us in " \
                     "support of your application?  Please expand on above " \
                     "points if necessary.  What you say here will influence " \
                     "whether or not you are hired." \
                })
#define LOG_ERROR(A,B) log_file( "/log/PLAYER_SHOP", "%s: %s : %s called by %s\n",\
                       ctime(time()), A, B, previous_object()->query_name() )
#define last_login(N) (PLAYER_HANDLER)->test_last(N)
#define test_cre(N) (PLAYER_HANDLER)->test_creator(N)
#define test_player(N) (PLAYER_HANDLER)->test_user(N)
#define test_prop(N,P) (PLAYER_HANDLER)->test_property(N,P)