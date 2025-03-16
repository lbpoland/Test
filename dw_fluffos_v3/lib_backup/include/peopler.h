#ifndef __PEOPLE_H
#define __PEOPLE_H
#define NAME 0
#define C_NAME 1
#define STRING 2
#define GENDER 3
#define IP_NUMBER 4
#define IP_NAME 5
#define TYPE 6
#define AGE 7
#define GUILD 8
#define RACE 9
#define LEVEL 10
#define TERMINAL 11
#define ROWS 12
#define COLS 13
#define ROOM 14
#define EUID 15
#define UID 16
#define CFILE 17
#define CUR_DIR 18
#define ND_ALLOWED 19
#define CENTER 128
#define RIGHT 64
#define MASK (RIGHT+CENTER)
#define ABBREV ({ \
          "n", \
          "N", \
          "",  \
          "G", \
          "#", \
          "I", \
          "T", \
          "A", \
          "g", \
          "R", \
          "L", \
          "t", \
          "r", \
          "c", \
          "O", \
          "E", \
          "U", \
          "F", \
          "/", \
          "a"  \
        })
#define DE_NAMES ({ \
          "Name", \
          "Capitalized Name", \
          "", \
          "Gender", \
          "IP Number", \
          "IP Name", \
          "Type", \
          "Age", \
          "Guild", \
          "Race", \
          "Level", \
          "Terminal type", \
          "Rows", \
          "Cols", \
          "Room", \
          "Euid", \
          "Uid", \
          "Creator file", \
          "Current dir", \
          "Not allowed with" \
        })
#define P_DEFAULT ({ \
          NAME, 15, \
          TYPE|CENTER, 3, \
          GENDER|CENTER, 6, \
          STRING, " ", \
          GUILD|CENTER, 10, \
          STRING, " ", \
          LEVEL|RIGHT, 4, \
          STRING, " ", \
          AGE, 5, \
          ROOM, 30 \
        })
#define QP_DEFAULT ({ \
          AGE|RIGHT, 4, \
          STRING, " ", \
          NAME, 30, \
        })
#define T_DEFAULT ({ \
          NAME, 12, \
          ROWS|CENTER, 5, \
          STRING, " ", \
          COLS|CENTER, 4, \
          STRING, " ", \
          TERMINAL, 30, \
        })
#define N_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          IP_NAME, 30, \
        })
#define SN_DEFAULT ({ \
          IP_NAME, 30, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          NAME, 12, \
        })
#define D_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          CUR_DIR, 25, \
          STRING, " ", \
          ROOM, 40, \
        })
#define ND_DEFAULT ({ \
          NAME, 12, \
          STRING, " ", \
          IP_NUMBER, 16, \
          STRING, " ", \
          IP_NAME, 20, \
          STRING, " ", \
          ND_ALLOWED, 100, \
        })
#endif