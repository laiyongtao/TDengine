/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "qSqlparser.h"
#include "tcmdtype.h"
#include "ttoken.h"
#include "ttokendef.h"
#include "tutil.h"
#include "tvariant.h"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned short int
#define YYNOCODE 292
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE SStrToken
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  SLimitVal yy6;
  SSqlNode* yy86;
  tVariant yy110;
  TAOS_FIELD yy115;
  tSqlExpr* yy142;
  SIntervalVal yy238;
  SSessionWindowVal yy319;
  SRelationInfo* yy328;
  SRangeVal yy330;
  SCreateDbInfo yy436;
  SCreatedTableInfo yy480;
  int32_t yy508;
  SCreateAcctInfo yy517;
  SArray* yy525;
  int64_t yy543;
  SWindowStateVal yy546;
  SCreateTableSql* yy572;
  int yy580;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL SSqlInfo* pInfo;
#define ParseARG_PDECL ,SSqlInfo* pInfo
#define ParseARG_FETCH SSqlInfo* pInfo = yypParser->pInfo
#define ParseARG_STORE yypParser->pInfo = pInfo
#define YYFALLBACK 1
#define YYNSTATE             398
#define YYNRULE              320
#define YYNTOKEN             204
#define YY_MAX_SHIFT         397
#define YY_MIN_SHIFTREDUCE   625
#define YY_MAX_SHIFTREDUCE   944
#define YY_ERROR_ACTION      945
#define YY_ACCEPT_ACTION     946
#define YY_NO_ACTION         947
#define YY_MIN_REDUCE        948
#define YY_MAX_REDUCE        1267
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (867)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   105,  676,  396,  243,  946,  397,  262, 1122,  676,  677,
 /*    10 */  1183,  712, 1184,  314,   37,   38,  677,   41,   42,  390,
 /*    20 */  1034,  265,   31,   30,   29,  246,  163,   40,  347,   45,
 /*    30 */    43,   46,   44, 1086, 1087,   55, 1090,   36,   35,   24,
 /*    40 */   216,   34,   33,   32,   37,   38,  252,   41,   42, 1241,
 /*    50 */  1241,  265,   31,   30,   29,  217, 1122,   40,  347,   45,
 /*    60 */    43,   46,   44,  318,  100, 1241,   99,   36,   35,  218,
 /*    70 */   214,   34,   33,   32,  288,  760,  131,  125,  136, 1241,
 /*    80 */  1241, 1243, 1244,  135, 1106,  141,  144,  134,   37,   38,
 /*    90 */    88,   41,   42,   51,  138,  265,   31,   30,   29,  295,
 /*   100 */   294,   40,  347,   45,   43,   46,   44,  372,  371,  343,
 /*   110 */   178,   36,   35, 1131,  223,   34,   33,   32,   37,   38,
 /*   120 */    58,   41,   42,   59, 1241,  265,   31,   30,   29,  304,
 /*   130 */   224,   40,  347,   45,   43,   46,   44,   34,   33,   32,
 /*   140 */  1241,   36,   35,  676,  225,   34,   33,   32,   13,   37,
 /*   150 */    39,  677,   41,   42, 1241,  803,  265,   31,   30,   29,
 /*   160 */  1263,  874,   40,  347,   45,   43,   46,   44,  245,  395,
 /*   170 */   393,  653,   36,   35,   59, 1104,   34,   33,   32,  209,
 /*   180 */   207,  205,  107,   86,   10, 1128,  204,  151,  150,  149,
 /*   190 */   148,  626,  627,  628,  629,  630,  631,  632,  633,  634,
 /*   200 */   635,  636,  637,  638,  639,  160,  250,  244,   38,   59,
 /*   210 */    41,   42,  382, 1107,  265,   31,   30,   29,  280,  255,
 /*   220 */    40,  347,   45,   43,   46,   44, 1104,  284,  283,  676,
 /*   230 */    36,   35, 1255,  257,   34,   33,   32,  677,   41,   42,
 /*   240 */  1107,  296,  265,   31,   30,   29,  834,  835,   40,  347,
 /*   250 */    45,   43,   46,   44,  256,  159,  157,  156,   36,   35,
 /*   260 */    59, 1104,   34,   33,   32,   67,  341,  389,  388,  340,
 /*   270 */   339,  338,  387,  337,  336,  335,  386,  334,  385,  384,
 /*   280 */  1065, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061,
 /*   290 */  1062, 1063, 1064, 1066, 1067,  237,  890,   25,  297,  878,
 /*   300 */  1233,  881,   94,  884,  788,  359,  133,  785, 1194,  786,
 /*   310 */  1241,  787, 1104, 1232,  222, 1231,  237,  890,  382,  259,
 /*   320 */   878,  230,  881, 1241,  884, 1241, 1107,  147,  146,  145,
 /*   330 */   229,  241,  242, 1122,  355,   94,    5,   62,  189,  270,
 /*   340 */   271,   59,   68,  188,  114,  119,  110,  118,  268,  103,
 /*   350 */   822,  247,  241,  242,  825,  345,  349,   45,   43,   46,
 /*   360 */    44,  274,  330,   85,   89,   36,   35, 1193,  239,   34,
 /*   370 */    33,   32,  317,  261,   67,   68,  389,  388, 1241,  240,
 /*   380 */    47,  387,  300,  301,   59,  386,  360,  385,  384, 1241,
 /*   390 */    36,   35,  346, 1104,   34,   33,   32, 1088,  287,   59,
 /*   400 */    84,   47,  266,   59,  880,   59,  883,  238,  879, 1073,
 /*   410 */   882, 1071, 1072,   59,  345,   59, 1074,  891,  885,  887,
 /*   420 */  1075, 1097, 1076, 1077,  220,  789,  272, 1089,  269,  361,
 /*   430 */   267,  264,  358,  357, 1241,  806, 1104,  218,  891,  885,
 /*   440 */   887,  276,  886,  273,  362,  367,  366, 1241,  368, 1244,
 /*   450 */   369, 1104,  221,    6,  226, 1104,  108, 1104,  370,  275,
 /*   460 */   374,  219, 1241,  886, 1241, 1104,  218, 1104,  258,  248,
 /*   470 */   185, 1241,  227,  228,   59,  232, 1241,  233, 1244,  234,
 /*   480 */   231,  215, 1241, 1241,  275, 1241,  275, 1241,  275, 1241,
 /*   490 */  1241, 1241, 1091,  996,  854,  186, 1181,  348, 1182, 1105,
 /*   500 */   199,  102,  289,  101, 1006,  997,    1,  187,    3,  200,
 /*   510 */    91,  199,  199,   92,   76,  343,   60,  299,  298,  831,
 /*   520 */   841,  842,   79,  810,  888,  770, 1103,  322,  889,  772,
 /*   530 */   324,  771,  919,  165,   71,   48,   54,  263,  892,   60,
 /*   540 */   351,   60,  352,   71,  106,   71,    9,  675,  253,   15,
 /*   550 */   291,   14,    9,  291,  853,  124,   83,  123,   17,   77,
 /*   560 */    16,    9,  350, 1190,  795,   80,  796, 1189,  793,  325,
 /*   570 */   794,  364,  363,   19,  254,   18,  181,  877,  130,  373,
 /*   580 */   129,   21,  285,   20,  143,  142,  161,  162,  759, 1102,
 /*   590 */  1130,   26, 1141, 1138, 1139, 1123,  292, 1143,  164,  169,
 /*   600 */   310, 1098,  180,  158, 1173, 1172, 1171,  182, 1096, 1170,
 /*   610 */  1120,  183,  821,  184, 1011,  327,  328,  329,  332,  333,
 /*   620 */   170,  171,  173,   69,  212,   65,  344,  319,  303, 1005,
 /*   630 */   249,  356,  305,  307,   81,   78, 1262,  121, 1261,   28,
 /*   640 */   172,  315, 1258,  190,  365,  313, 1254,  174,  127,  895,
 /*   650 */   306,  311,  175, 1253, 1250,  191, 1031,  309,  302,   66,
 /*   660 */    61,   70,  213,  993,  137,  991,  139,   27,  140,  989,
 /*   670 */   988,  277,  202,  203,  985,  984,  983,   87,  982,  981,
 /*   680 */   980,  979,  206,  208,  971,  210,  968,  331,  211,  964,
 /*   690 */   383,  132,  290, 1100,   90,   95,  375,  308,  376,  377,
 /*   700 */   378,  379,  380,  381,  391,  944,  279,   82,  260,  278,
 /*   710 */   326,  943,  282,  281,  942,  925,  235,  236,  924,  286,
 /*   720 */   291,  115, 1010, 1009,   11,  116,  321,   93,  798,  293,
 /*   730 */    52,   96,  830,   74,  828,  827,  824,  987,  193, 1032,
 /*   740 */   194,  192,  195,  197,  196,  198,  986,    2,  152,  823,
 /*   750 */   153, 1069,  320,  978,  977, 1033,  154,   53,  179,  176,
 /*   760 */   177,  155,  970,  969,   75,  168,  832,    4, 1079,  166,
 /*   770 */   251,  843,  167,   63,  837,   97,   22,  839,   98,  312,
 /*   780 */   350,  316,   64,   12,  104,   23,  323,  109,   49,   50,
 /*   790 */   107,  112,  690,  725,  723,   56,  722,  721,  111,  719,
 /*   800 */   718,   57,  113,  717,  714,  680,  342,  117,    7,  916,
 /*   810 */   914,  894,  917,  893,  915,    8,  353,  354,  896,   72,
 /*   820 */   120,  122,   60,  792,  791,   73,  126,  762,  128,  761,
 /*   830 */   758,  706,  704,  696,  702,  698,  700,  694,  692,  728,
 /*   840 */   727,  726,  724,  720,  716,  715,  201,  678,  948,  643,
 /*   850 */   652,  947,  650,  947,  947,  947,  947,  947,  947,  947,
 /*   860 */   947,  947,  947,  947,  392,  947,  394,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   215,    1,  207,  208,  205,  206,  214,  257,    1,    9,
 /*    10 */   286,    5,  288,  289,   14,   15,    9,   17,   18,  229,
 /*    20 */   230,   21,   22,   23,   24,  275,  207,   27,   28,   29,
 /*    30 */    30,   31,   32,  248,  249,  250,  251,   37,   38,  278,
 /*    40 */   278,   41,   42,   43,   14,   15,    1,   17,   18,  288,
 /*    50 */   288,   21,   22,   23,   24,  278,  257,   27,   28,   29,
 /*    60 */    30,   31,   32,  285,  286,  288,  288,   37,   38,  278,
 /*    70 */   278,   41,   42,   43,  275,    5,   66,   67,   68,  288,
 /*    80 */   288,  290,  290,   73,  260,   75,   76,   77,   14,   15,
 /*    90 */    90,   17,   18,   86,   84,   21,   22,   23,   24,  280,
 /*   100 */   281,   27,   28,   29,   30,   31,   32,   37,   38,   88,
 /*   110 */   265,   37,   38,  207,  278,   41,   42,   43,   14,   15,
 /*   120 */    90,   17,   18,  207,  288,   21,   22,   23,   24,  284,
 /*   130 */   278,   27,   28,   29,   30,   31,   32,   41,   42,   43,
 /*   140 */   288,   37,   38,    1,  278,   41,   42,   43,   86,   14,
 /*   150 */    15,    9,   17,   18,  288,  101,   21,   22,   23,   24,
 /*   160 */   260,   87,   27,   28,   29,   30,   31,   32,  252,   69,
 /*   170 */    70,   71,   37,   38,  207,  259,   41,   42,   43,   66,
 /*   180 */    67,   68,  120,  121,  130,  279,   73,   74,   75,   76,
 /*   190 */    77,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   200 */    58,   59,   60,   61,   62,   63,  253,   65,   15,  207,
 /*   210 */    17,   18,   94,  260,   21,   22,   23,   24,  150,  252,
 /*   220 */    27,   28,   29,   30,   31,   32,  259,  159,  160,    1,
 /*   230 */    37,   38,  260,  253,   41,   42,   43,    9,   17,   18,
 /*   240 */   260,  283,   21,   22,   23,   24,  132,  133,   27,   28,
 /*   250 */    29,   30,   31,   32,  252,   66,   67,   68,   37,   38,
 /*   260 */   207,  259,   41,   42,   43,  102,  103,  104,  105,  106,
 /*   270 */   107,  108,  109,  110,  111,  112,  113,  114,  115,  116,
 /*   280 */   231,  232,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   290 */   241,  242,  243,  244,  245,    1,    2,   48,  283,    5,
 /*   300 */   278,    7,   86,    9,    2,  252,   82,    5,  247,    7,
 /*   310 */   288,    9,  259,  278,   65,  278,    1,    2,   94,  253,
 /*   320 */     5,   72,    7,  288,    9,  288,  260,   78,   79,   80,
 /*   330 */    81,   37,   38,  257,   85,   86,   66,   67,   68,   37,
 /*   340 */    38,  207,  126,   73,   74,   75,   76,   77,   72,  261,
 /*   350 */     5,  275,   37,   38,    9,   47,   41,   29,   30,   31,
 /*   360 */    32,   72,   92,  215,  276,   37,   38,  247,  278,   41,
 /*   370 */    42,   43,   64,  214,  102,  126,  104,  105,  288,  278,
 /*   380 */    86,  109,   37,   38,  207,  113,  252,  115,  116,  288,
 /*   390 */    37,   38,   25,  259,   41,   42,   43,  249,  149,  207,
 /*   400 */   151,   86,  214,  207,    5,  207,    7,  158,    5,  231,
 /*   410 */     7,  233,  234,  207,   47,  207,  238,  123,  124,  125,
 /*   420 */   242,  207,  244,  245,  278,  123,  124,    0,  152,  252,
 /*   430 */   154,   64,  156,  157,  288,   41,  259,  278,  123,  124,
 /*   440 */   125,  152,  148,  154,  252,  156,  157,  288,  252,  290,
 /*   450 */   252,  259,  278,   86,  278,  259,  215,  259,  252,  207,
 /*   460 */   252,  278,  288,  148,  288,  259,  278,  259,  254,  124,
 /*   470 */   218,  288,  278,  278,  207,  278,  288,  278,  290,  278,
 /*   480 */   278,  278,  288,  288,  207,  288,  207,  288,  207,  288,
 /*   490 */   288,  288,  251,  213,   80,  218,  286,  218,  288,  218,
 /*   500 */   220,  286,   87,  288,  213,  213,  216,  217,  211,  212,
 /*   510 */    87,  220,  220,   87,  101,   88,  101,   37,   38,   87,
 /*   520 */    87,   87,  101,  129,  125,   87,  259,   87,  125,   87,
 /*   530 */    87,   87,   87,  101,  101,  101,   86,    1,   87,  101,
 /*   540 */    25,  101,   16,  101,  101,  101,  101,   87,  247,  153,
 /*   550 */   127,  155,  101,  127,  140,  153,   86,  155,  153,  146,
 /*   560 */   155,  101,   47,  247,    5,  144,    7,  247,    5,  119,
 /*   570 */     7,   37,   38,  153,  247,  155,  255,   41,  153,  247,
 /*   580 */   155,  153,  207,  155,   82,   83,  207,  207,  118,  207,
 /*   590 */   207,  277,  207,  207,  207,  257,  257,  207,  207,  207,
 /*   600 */   207,  257,  262,   64,  287,  287,  287,  207,  207,  287,
 /*   610 */   274,  207,  125,  207,  207,  207,  207,  207,  207,  207,
 /*   620 */   273,  272,  270,  207,  207,  207,  207,  138,  282,  207,
 /*   630 */   282,  207,  282,  282,  143,  145,  207,  207,  207,  142,
 /*   640 */   271,  141,  207,  207,  207,  136,  207,  269,  207,  123,
 /*   650 */   137,  135,  268,  207,  207,  207,  207,  134,  131,  207,
 /*   660 */   207,  207,  207,  207,  207,  207,  207,  147,  207,  207,
 /*   670 */   207,  207,  207,  207,  207,  207,  207,  122,  207,  207,
 /*   680 */   207,  207,  207,  207,  207,  207,  207,   93,  207,  207,
 /*   690 */   117,  100,  209,  209,  209,  209,   99,  209,   55,   96,
 /*   700 */    98,   59,   97,   95,   88,    5,    5,  209,  209,  161,
 /*   710 */   209,    5,    5,  161,    5,  104,  209,  209,  103,  150,
 /*   720 */   127,  215,  219,  219,   86,  215,  119,  128,   87,  101,
 /*   730 */    86,  101,   87,  101,  125,  125,    5,  209,  226,  228,
 /*   740 */   222,  227,  225,  224,  223,  221,  209,  216,  210,    5,
 /*   750 */   210,  246,  256,  209,  209,  230,  210,  264,  263,  267,
 /*   760 */   266,  210,  209,  209,   86,  101,   87,  211,  246,   86,
 /*   770 */     1,   87,   86,  101,   87,   86,  139,   87,   86,   86,
 /*   780 */    47,    1,  101,   86,   90,  139,  119,   82,   86,   86,
 /*   790 */   120,   74,    5,    9,    5,   91,    5,    5,   90,    5,
 /*   800 */     5,   91,   90,    5,    5,   89,   16,   82,   86,    9,
 /*   810 */     9,   87,    9,   87,    9,   86,   28,   63,  123,   17,
 /*   820 */   155,  155,  101,  125,  125,   17,  155,    5,  155,    5,
 /*   830 */    87,    5,    5,    5,    5,    5,    5,    5,    5,    5,
 /*   840 */     5,    5,    5,    5,    5,    5,  101,   89,    0,   64,
 /*   850 */     9,  291,    9,  291,  291,  291,  291,  291,  291,  291,
 /*   860 */   291,  291,  291,  291,   22,  291,   22,  291,  291,  291,
 /*   870 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   880 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   890 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   900 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   910 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   920 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   930 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   940 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   950 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   960 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   970 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   980 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*   990 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1000 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1010 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1020 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1030 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1040 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1050 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1060 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*  1070 */   291,
};
#define YY_SHIFT_COUNT    (397)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (848)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   249,  163,  163,  272,  272,   21,  315,  294,  294,  294,
 /*    10 */     7,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*    20 */   228,  228,   45,   45,    0,  142,  294,  294,  294,  294,
 /*    30 */   294,  294,  294,  294,  294,  294,  294,  294,  294,  294,
 /*    40 */   294,  294,  294,  294,  294,  294,  294,  294,  302,  302,
 /*    50 */   302,  216,  216,  114,  228,  427,  228,  228,  228,  228,
 /*    60 */   228,  224,   21,   45,   45,  118,  118,    6,  867,  867,
 /*    70 */   867,  302,  302,  302,  345,  345,   70,   70,   70,   70,
 /*    80 */    70,   70,   62,   70,  228,  228,  228,  228,  228,  394,
 /*    90 */   228,  228,  228,  216,  216,  228,  228,  228,  228,  414,
 /*   100 */   414,  414,  414,   54,  216,  228,  228,  228,  228,  228,
 /*   110 */   228,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*   120 */   228,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*   130 */   228,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*   140 */   228,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*   150 */   228,  228,  228,  228,  228,  228,  228,  228,  228,  228,
 /*   160 */   228,  539,  539,  539,  539,  487,  487,  487,  487,  539,
 /*   170 */   491,  490,  489,  497,  500,  509,  516,  523,  513,  527,
 /*   180 */   520,  555,  539,  539,  539,  594,  594,  573,   21,   21,
 /*   190 */   539,  539,  591,  597,  643,  603,  602,  642,  605,  608,
 /*   200 */   573,    6,  539,  539,  616,  616,  539,  616,  539,  616,
 /*   210 */   539,  539,  867,  867,   30,   74,  104,  104,  104,  135,
 /*   220 */   193,  221,  270,  328,  328,  328,  328,  328,  328,   10,
 /*   230 */   113,  353,  353,  353,  353,  276,  289,  367,   68,   96,
 /*   240 */    96,  399,  403,  100,  189,  415,  423,  426,  480,  432,
 /*   250 */   433,  434,  308,  413,  421,  438,  440,  442,  443,  444,
 /*   260 */   450,  445,  451,  515,  536,  526,  460,  396,  402,  405,
 /*   270 */   559,  563,  534,  420,  425,  470,  428,  502,  700,  548,
 /*   280 */   701,  706,  552,  707,  709,  611,  615,  569,  593,  607,
 /*   290 */   638,  599,  641,  644,  628,  630,  645,  632,  609,  610,
 /*   300 */   731,  744,  678,  679,  683,  684,  686,  687,  664,  689,
 /*   310 */   690,  692,  769,  693,  672,  637,  733,  780,  681,  646,
 /*   320 */   694,  697,  607,  702,  667,  703,  670,  705,  704,  708,
 /*   330 */   717,  787,  710,  712,  784,  789,  791,  792,  794,  795,
 /*   340 */   798,  799,  716,  790,  725,  800,  801,  722,  724,  726,
 /*   350 */   803,  805,  695,  729,  788,  754,  802,  665,  666,  721,
 /*   360 */   721,  721,  721,  698,  699,  808,  671,  673,  721,  721,
 /*   370 */   721,  822,  824,  743,  721,  826,  827,  828,  829,  830,
 /*   380 */   831,  832,  833,  834,  835,  836,  837,  838,  839,  840,
 /*   390 */   745,  758,  841,  842,  843,  844,  785,  848,
};
#define YY_REDUCE_COUNT (213)
#define YY_REDUCE_MIN   (-276)
#define YY_REDUCE_MAX   (556)
static const short yy_reduce_ofst[] = {
 /*     0 */  -201,   49,   49,  178,  178, -215, -208,  159,  188, -209,
 /*    10 */  -181,  -84,  -33,    2,   53,  134,  177,  192,  196,  198,
 /*    20 */   206,  208, -276, -222,  -94, -205, -239, -238, -223, -164,
 /*    30 */  -148, -134,   22,   35,   37,   90,  101,  146,  174,  176,
 /*    40 */   183,  194,  195,  197,  199,  201,  202,  203,  -47,  -20,
 /*    50 */    66, -250,   76, -155,  214,  241,  252,  277,  279,  281,
 /*    60 */   267,  280,  148,  210,  215,  291,  292, -210,   88,  290,
 /*    70 */   297, -176, -100,  -28,  -42,   15,   61,  120,  301,  316,
 /*    80 */   320,  327,  321,  332,  375,  379,  380,  382,  383,  314,
 /*    90 */   385,  386,  387,  338,  339,  390,  391,  392,  393,  317,
 /*   100 */   318,  319,  322,  340,  344,  400,  401,  404,  406,  407,
 /*   110 */   408,  409,  410,  411,  412,  416,  417,  418,  419,  422,
 /*   120 */   424,  429,  430,  431,  435,  436,  437,  439,  441,  446,
 /*   130 */   447,  448,  449,  452,  453,  454,  455,  456,  457,  458,
 /*   140 */   459,  461,  462,  463,  464,  465,  466,  467,  468,  469,
 /*   150 */   471,  472,  473,  474,  475,  476,  477,  478,  479,  481,
 /*   160 */   482,  483,  484,  485,  486,  346,  348,  350,  351,  488,
 /*   170 */   336,  347,  349,  369,  352,  378,  384,  492,  494,  493,
 /*   180 */   495,  496,  498,  499,  501,  503,  504,  505,  506,  510,
 /*   190 */   507,  508,  511,  514,  512,  518,  517,  521,  519,  524,
 /*   200 */   522,  525,  528,  537,  538,  540,  544,  546,  545,  551,
 /*   210 */   553,  554,  531,  556,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   945, 1068, 1007, 1078,  994, 1004, 1246, 1246, 1246, 1246,
 /*    10 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*    20 */   945,  945,  945,  945, 1132,  965,  945,  945,  945,  945,
 /*    30 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*    40 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*    50 */   945,  945,  945, 1156,  945, 1004,  945,  945,  945,  945,
 /*    60 */   945, 1014, 1004,  945,  945, 1014, 1014,  945, 1127, 1052,
 /*    70 */  1070,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*    80 */   945,  945, 1099,  945,  945,  945,  945,  945,  945, 1134,
 /*    90 */  1140, 1137,  945,  945,  945, 1142,  945,  945,  945, 1178,
 /*   100 */  1178, 1178, 1178, 1125,  945,  945,  945,  945,  945,  945,
 /*   110 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   120 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   130 */   945,  945,  945,  945,  945,  945,  945,  992,  945,  990,
 /*   140 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   150 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   160 */   963,  967,  967,  967,  967,  945,  945,  945,  945,  967,
 /*   170 */  1187, 1191, 1168, 1185, 1179, 1163, 1161, 1159, 1167, 1152,
 /*   180 */  1195, 1101,  967,  967,  967, 1012, 1012, 1008, 1004, 1004,
 /*   190 */   967,  967, 1030, 1028, 1026, 1018, 1024, 1020, 1022, 1016,
 /*   200 */   995,  945,  967,  967, 1002, 1002,  967, 1002,  967, 1002,
 /*   210 */   967,  967, 1052, 1070, 1245,  945, 1196, 1186, 1245,  945,
 /*   220 */  1228, 1227,  945, 1236, 1235, 1234, 1226, 1225, 1224,  945,
 /*   230 */   945, 1220, 1223, 1222, 1221,  945,  945, 1198,  945, 1230,
 /*   240 */  1229,  945,  945,  945,  945,  945,  945,  945, 1149,  945,
 /*   250 */   945,  945, 1174, 1192, 1188,  945,  945,  945,  945,  945,
 /*   260 */   945,  945,  945, 1199,  945,  945,  945,  945,  945,  945,
 /*   270 */   945,  945, 1113,  945,  945, 1080,  945,  945,  945,  945,
 /*   280 */   945,  945,  945,  945,  945,  945,  945,  945, 1124,  945,
 /*   290 */   945,  945,  945,  945, 1136, 1135,  945,  945,  945,  945,
 /*   300 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   310 */   945,  945,  945,  945, 1180,  945, 1175,  945, 1169,  945,
 /*   320 */   945,  945, 1092,  945,  945,  945,  945,  945,  945,  945,
 /*   330 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   340 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   350 */   945,  945,  945,  945,  945,  945,  945,  945,  945, 1264,
 /*   360 */  1259, 1260, 1257,  945,  945,  945,  945,  945, 1256, 1251,
 /*   370 */  1252,  945,  945,  945, 1249,  945,  945,  945,  945,  945,
 /*   380 */   945,  945,  945,  945,  945,  945,  945,  945,  945,  945,
 /*   390 */  1036,  945,  945,  974,  945,  972,  945,  945,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         ID => nothing */
    1,  /*       BOOL => ID */
    1,  /*    TINYINT => ID */
    1,  /*   SMALLINT => ID */
    1,  /*    INTEGER => ID */
    1,  /*     BIGINT => ID */
    1,  /*      FLOAT => ID */
    1,  /*     DOUBLE => ID */
    1,  /*     STRING => ID */
    1,  /*  TIMESTAMP => ID */
    1,  /*     BINARY => ID */
    1,  /*      NCHAR => ID */
    1,  /*       JSON => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*        NOT => nothing */
    0,  /*         EQ => nothing */
    0,  /*         NE => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         IS => nothing */
    1,  /*       LIKE => ID */
    1,  /*      MATCH => ID */
    1,  /*     NMATCH => ID */
    0,  /*   CONTAINS => nothing */
    1,  /*       GLOB => ID */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*         GT => nothing */
    0,  /*         GE => nothing */
    0,  /*         LT => nothing */
    0,  /*         LE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     DIVIDE => nothing */
    0,  /*      TIMES => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*      ARROW => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*     TOPICS => nothing */
    0,  /*  FUNCTIONS => nothing */
    0,  /*     MNODES => nothing */
    0,  /*     DNODES => nothing */
    0,  /*   ACCOUNTS => nothing */
    0,  /*      USERS => nothing */
    0,  /*    MODULES => nothing */
    0,  /*    QUERIES => nothing */
    0,  /* CONNECTIONS => nothing */
    0,  /*    STREAMS => nothing */
    0,  /*  VARIABLES => nothing */
    0,  /*     SCORES => nothing */
    0,  /*     GRANTS => nothing */
    0,  /*     VNODES => nothing */
    0,  /*        DOT => nothing */
    0,  /*     CREATE => nothing */
    0,  /*      TABLE => nothing */
    1,  /*     STABLE => ID */
    1,  /*   DATABASE => ID */
    0,  /*     TABLES => nothing */
    0,  /*    STABLES => nothing */
    0,  /*    VGROUPS => nothing */
    0,  /*       DROP => nothing */
    0,  /*      TOPIC => nothing */
    0,  /*   FUNCTION => nothing */
    0,  /*      DNODE => nothing */
    0,  /*       USER => nothing */
    0,  /*    ACCOUNT => nothing */
    0,  /*        USE => nothing */
    0,  /*   DESCRIBE => nothing */
    1,  /*       DESC => ID */
    0,  /*      ALTER => nothing */
    0,  /*       PASS => nothing */
    0,  /*  PRIVILEGE => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*    COMPACT => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*         IF => nothing */
    0,  /*     EXISTS => nothing */
    0,  /*         AS => nothing */
    0,  /* OUTPUTTYPE => nothing */
    0,  /*  AGGREGATE => nothing */
    0,  /*    BUFSIZE => nothing */
    0,  /*        PPS => nothing */
    0,  /*    TSERIES => nothing */
    0,  /*        DBS => nothing */
    0,  /*    STORAGE => nothing */
    0,  /*      QTIME => nothing */
    0,  /*      CONNS => nothing */
    0,  /*      STATE => nothing */
    0,  /*      COMMA => nothing */
    0,  /*       KEEP => nothing */
    0,  /*      CACHE => nothing */
    0,  /*    REPLICA => nothing */
    0,  /*     QUORUM => nothing */
    0,  /*       DAYS => nothing */
    0,  /*    MINROWS => nothing */
    0,  /*    MAXROWS => nothing */
    0,  /*     BLOCKS => nothing */
    0,  /*      CTIME => nothing */
    0,  /*        WAL => nothing */
    0,  /*      FSYNC => nothing */
    0,  /*       COMP => nothing */
    0,  /*  PRECISION => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*  CACHELAST => nothing */
    0,  /* PARTITIONS => nothing */
    0,  /*   UNSIGNED => nothing */
    0,  /*       TAGS => nothing */
    0,  /*      USING => nothing */
    0,  /*         TO => nothing */
    0,  /*      SPLIT => nothing */
    1,  /*       NULL => ID */
    1,  /*        NOW => ID */
    0,  /*   VARIABLE => nothing */
    0,  /*     SELECT => nothing */
    0,  /*      UNION => nothing */
    1,  /*        ALL => ID */
    0,  /*   DISTINCT => nothing */
    0,  /*       FROM => nothing */
    0,  /*      RANGE => nothing */
    0,  /*   INTERVAL => nothing */
    0,  /*      EVERY => nothing */
    0,  /*    SESSION => nothing */
    0,  /* STATE_WINDOW => nothing */
    0,  /*       FILL => nothing */
    0,  /*    SLIDING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    1,  /*        ASC => ID */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    1,  /*     OFFSET => ID */
    0,  /*     SLIMIT => nothing */
    0,  /*    SOFFSET => nothing */
    0,  /*      WHERE => nothing */
    1,  /*      TODAY => ID */
    0,  /*      RESET => nothing */
    0,  /*      QUERY => nothing */
    0,  /*     SYNCDB => nothing */
    0,  /*        ADD => nothing */
    0,  /*     COLUMN => nothing */
    0,  /*     MODIFY => nothing */
    0,  /*        TAG => nothing */
    0,  /*     CHANGE => nothing */
    0,  /*        SET => nothing */
    0,  /*       KILL => nothing */
    0,  /* CONNECTION => nothing */
    0,  /*     STREAM => nothing */
    0,  /*      COLON => nothing */
    1,  /*      ABORT => ID */
    1,  /*      AFTER => ID */
    1,  /*     ATTACH => ID */
    1,  /*     BEFORE => ID */
    1,  /*      BEGIN => ID */
    1,  /*    CASCADE => ID */
    1,  /*    CLUSTER => ID */
    1,  /*   CONFLICT => ID */
    1,  /*       COPY => ID */
    1,  /*   DEFERRED => ID */
    1,  /* DELIMITERS => ID */
    1,  /*     DETACH => ID */
    1,  /*       EACH => ID */
    1,  /*        END => ID */
    1,  /*    EXPLAIN => ID */
    1,  /*       FAIL => ID */
    1,  /*        FOR => ID */
    1,  /*     IGNORE => ID */
    1,  /*  IMMEDIATE => ID */
    1,  /*  INITIALLY => ID */
    1,  /*    INSTEAD => ID */
    1,  /*        KEY => ID */
    1,  /*         OF => ID */
    1,  /*      RAISE => ID */
    1,  /*    REPLACE => ID */
    1,  /*   RESTRICT => ID */
    1,  /*        ROW => ID */
    1,  /*  STATEMENT => ID */
    1,  /*    TRIGGER => ID */
    1,  /*       VIEW => ID */
    1,  /*    IPTOKEN => ID */
    1,  /*       SEMI => ID */
    1,  /*       NONE => ID */
    1,  /*       PREV => ID */
    1,  /*     LINEAR => ID */
    1,  /*     IMPORT => ID */
    1,  /*     TBNAME => ID */
    1,  /*       JOIN => ID */
    1,  /*     INSERT => ID */
    1,  /*       INTO => ID */
    1,  /*     VALUES => ID */
    1,  /*       FILE => ID */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "ID",
  /*    2 */ "BOOL",
  /*    3 */ "TINYINT",
  /*    4 */ "SMALLINT",
  /*    5 */ "INTEGER",
  /*    6 */ "BIGINT",
  /*    7 */ "FLOAT",
  /*    8 */ "DOUBLE",
  /*    9 */ "STRING",
  /*   10 */ "TIMESTAMP",
  /*   11 */ "BINARY",
  /*   12 */ "NCHAR",
  /*   13 */ "JSON",
  /*   14 */ "OR",
  /*   15 */ "AND",
  /*   16 */ "NOT",
  /*   17 */ "EQ",
  /*   18 */ "NE",
  /*   19 */ "ISNULL",
  /*   20 */ "NOTNULL",
  /*   21 */ "IS",
  /*   22 */ "LIKE",
  /*   23 */ "MATCH",
  /*   24 */ "NMATCH",
  /*   25 */ "CONTAINS",
  /*   26 */ "GLOB",
  /*   27 */ "BETWEEN",
  /*   28 */ "IN",
  /*   29 */ "GT",
  /*   30 */ "GE",
  /*   31 */ "LT",
  /*   32 */ "LE",
  /*   33 */ "BITAND",
  /*   34 */ "BITOR",
  /*   35 */ "LSHIFT",
  /*   36 */ "RSHIFT",
  /*   37 */ "PLUS",
  /*   38 */ "MINUS",
  /*   39 */ "DIVIDE",
  /*   40 */ "TIMES",
  /*   41 */ "STAR",
  /*   42 */ "SLASH",
  /*   43 */ "REM",
  /*   44 */ "UMINUS",
  /*   45 */ "UPLUS",
  /*   46 */ "BITNOT",
  /*   47 */ "ARROW",
  /*   48 */ "SHOW",
  /*   49 */ "DATABASES",
  /*   50 */ "TOPICS",
  /*   51 */ "FUNCTIONS",
  /*   52 */ "MNODES",
  /*   53 */ "DNODES",
  /*   54 */ "ACCOUNTS",
  /*   55 */ "USERS",
  /*   56 */ "MODULES",
  /*   57 */ "QUERIES",
  /*   58 */ "CONNECTIONS",
  /*   59 */ "STREAMS",
  /*   60 */ "VARIABLES",
  /*   61 */ "SCORES",
  /*   62 */ "GRANTS",
  /*   63 */ "VNODES",
  /*   64 */ "DOT",
  /*   65 */ "CREATE",
  /*   66 */ "TABLE",
  /*   67 */ "STABLE",
  /*   68 */ "DATABASE",
  /*   69 */ "TABLES",
  /*   70 */ "STABLES",
  /*   71 */ "VGROUPS",
  /*   72 */ "DROP",
  /*   73 */ "TOPIC",
  /*   74 */ "FUNCTION",
  /*   75 */ "DNODE",
  /*   76 */ "USER",
  /*   77 */ "ACCOUNT",
  /*   78 */ "USE",
  /*   79 */ "DESCRIBE",
  /*   80 */ "DESC",
  /*   81 */ "ALTER",
  /*   82 */ "PASS",
  /*   83 */ "PRIVILEGE",
  /*   84 */ "LOCAL",
  /*   85 */ "COMPACT",
  /*   86 */ "LP",
  /*   87 */ "RP",
  /*   88 */ "IF",
  /*   89 */ "EXISTS",
  /*   90 */ "AS",
  /*   91 */ "OUTPUTTYPE",
  /*   92 */ "AGGREGATE",
  /*   93 */ "BUFSIZE",
  /*   94 */ "PPS",
  /*   95 */ "TSERIES",
  /*   96 */ "DBS",
  /*   97 */ "STORAGE",
  /*   98 */ "QTIME",
  /*   99 */ "CONNS",
  /*  100 */ "STATE",
  /*  101 */ "COMMA",
  /*  102 */ "KEEP",
  /*  103 */ "CACHE",
  /*  104 */ "REPLICA",
  /*  105 */ "QUORUM",
  /*  106 */ "DAYS",
  /*  107 */ "MINROWS",
  /*  108 */ "MAXROWS",
  /*  109 */ "BLOCKS",
  /*  110 */ "CTIME",
  /*  111 */ "WAL",
  /*  112 */ "FSYNC",
  /*  113 */ "COMP",
  /*  114 */ "PRECISION",
  /*  115 */ "UPDATE",
  /*  116 */ "CACHELAST",
  /*  117 */ "PARTITIONS",
  /*  118 */ "UNSIGNED",
  /*  119 */ "TAGS",
  /*  120 */ "USING",
  /*  121 */ "TO",
  /*  122 */ "SPLIT",
  /*  123 */ "NULL",
  /*  124 */ "NOW",
  /*  125 */ "VARIABLE",
  /*  126 */ "SELECT",
  /*  127 */ "UNION",
  /*  128 */ "ALL",
  /*  129 */ "DISTINCT",
  /*  130 */ "FROM",
  /*  131 */ "RANGE",
  /*  132 */ "INTERVAL",
  /*  133 */ "EVERY",
  /*  134 */ "SESSION",
  /*  135 */ "STATE_WINDOW",
  /*  136 */ "FILL",
  /*  137 */ "SLIDING",
  /*  138 */ "ORDER",
  /*  139 */ "BY",
  /*  140 */ "ASC",
  /*  141 */ "GROUP",
  /*  142 */ "HAVING",
  /*  143 */ "LIMIT",
  /*  144 */ "OFFSET",
  /*  145 */ "SLIMIT",
  /*  146 */ "SOFFSET",
  /*  147 */ "WHERE",
  /*  148 */ "TODAY",
  /*  149 */ "RESET",
  /*  150 */ "QUERY",
  /*  151 */ "SYNCDB",
  /*  152 */ "ADD",
  /*  153 */ "COLUMN",
  /*  154 */ "MODIFY",
  /*  155 */ "TAG",
  /*  156 */ "CHANGE",
  /*  157 */ "SET",
  /*  158 */ "KILL",
  /*  159 */ "CONNECTION",
  /*  160 */ "STREAM",
  /*  161 */ "COLON",
  /*  162 */ "ABORT",
  /*  163 */ "AFTER",
  /*  164 */ "ATTACH",
  /*  165 */ "BEFORE",
  /*  166 */ "BEGIN",
  /*  167 */ "CASCADE",
  /*  168 */ "CLUSTER",
  /*  169 */ "CONFLICT",
  /*  170 */ "COPY",
  /*  171 */ "DEFERRED",
  /*  172 */ "DELIMITERS",
  /*  173 */ "DETACH",
  /*  174 */ "EACH",
  /*  175 */ "END",
  /*  176 */ "EXPLAIN",
  /*  177 */ "FAIL",
  /*  178 */ "FOR",
  /*  179 */ "IGNORE",
  /*  180 */ "IMMEDIATE",
  /*  181 */ "INITIALLY",
  /*  182 */ "INSTEAD",
  /*  183 */ "KEY",
  /*  184 */ "OF",
  /*  185 */ "RAISE",
  /*  186 */ "REPLACE",
  /*  187 */ "RESTRICT",
  /*  188 */ "ROW",
  /*  189 */ "STATEMENT",
  /*  190 */ "TRIGGER",
  /*  191 */ "VIEW",
  /*  192 */ "IPTOKEN",
  /*  193 */ "SEMI",
  /*  194 */ "NONE",
  /*  195 */ "PREV",
  /*  196 */ "LINEAR",
  /*  197 */ "IMPORT",
  /*  198 */ "TBNAME",
  /*  199 */ "JOIN",
  /*  200 */ "INSERT",
  /*  201 */ "INTO",
  /*  202 */ "VALUES",
  /*  203 */ "FILE",
  /*  204 */ "error",
  /*  205 */ "program",
  /*  206 */ "cmd",
  /*  207 */ "ids",
  /*  208 */ "dbPrefix",
  /*  209 */ "cpxName",
  /*  210 */ "ifexists",
  /*  211 */ "alter_db_optr",
  /*  212 */ "alter_topic_optr",
  /*  213 */ "acct_optr",
  /*  214 */ "exprlist",
  /*  215 */ "ifnotexists",
  /*  216 */ "db_optr",
  /*  217 */ "topic_optr",
  /*  218 */ "typename",
  /*  219 */ "bufsize",
  /*  220 */ "pps",
  /*  221 */ "tseries",
  /*  222 */ "dbs",
  /*  223 */ "streams",
  /*  224 */ "storage",
  /*  225 */ "qtime",
  /*  226 */ "users",
  /*  227 */ "conns",
  /*  228 */ "state",
  /*  229 */ "intitemlist",
  /*  230 */ "intitem",
  /*  231 */ "keep",
  /*  232 */ "cache",
  /*  233 */ "replica",
  /*  234 */ "quorum",
  /*  235 */ "days",
  /*  236 */ "minrows",
  /*  237 */ "maxrows",
  /*  238 */ "blocks",
  /*  239 */ "ctime",
  /*  240 */ "wal",
  /*  241 */ "fsync",
  /*  242 */ "comp",
  /*  243 */ "prec",
  /*  244 */ "update",
  /*  245 */ "cachelast",
  /*  246 */ "partitions",
  /*  247 */ "signed",
  /*  248 */ "create_table_args",
  /*  249 */ "create_stable_args",
  /*  250 */ "create_table_list",
  /*  251 */ "create_from_stable",
  /*  252 */ "columnlist",
  /*  253 */ "tagitemlist",
  /*  254 */ "tagNamelist",
  /*  255 */ "to_opt",
  /*  256 */ "split_opt",
  /*  257 */ "select",
  /*  258 */ "to_split",
  /*  259 */ "column",
  /*  260 */ "tagitem",
  /*  261 */ "selcollist",
  /*  262 */ "from",
  /*  263 */ "where_opt",
  /*  264 */ "range_option",
  /*  265 */ "interval_option",
  /*  266 */ "sliding_opt",
  /*  267 */ "session_option",
  /*  268 */ "windowstate_option",
  /*  269 */ "fill_opt",
  /*  270 */ "groupby_opt",
  /*  271 */ "having_opt",
  /*  272 */ "orderby_opt",
  /*  273 */ "slimit_opt",
  /*  274 */ "limit_opt",
  /*  275 */ "union",
  /*  276 */ "sclp",
  /*  277 */ "distinct",
  /*  278 */ "expr",
  /*  279 */ "as",
  /*  280 */ "tablelist",
  /*  281 */ "sub",
  /*  282 */ "tmvar",
  /*  283 */ "timestamp",
  /*  284 */ "intervalKey",
  /*  285 */ "sortlist",
  /*  286 */ "item",
  /*  287 */ "sortorder",
  /*  288 */ "arrow",
  /*  289 */ "grouplist",
  /*  290 */ "expritem",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= cmd",
 /*   1 */ "cmd ::= SHOW DATABASES",
 /*   2 */ "cmd ::= SHOW TOPICS",
 /*   3 */ "cmd ::= SHOW FUNCTIONS",
 /*   4 */ "cmd ::= SHOW MNODES",
 /*   5 */ "cmd ::= SHOW DNODES",
 /*   6 */ "cmd ::= SHOW ACCOUNTS",
 /*   7 */ "cmd ::= SHOW USERS",
 /*   8 */ "cmd ::= SHOW MODULES",
 /*   9 */ "cmd ::= SHOW QUERIES",
 /*  10 */ "cmd ::= SHOW CONNECTIONS",
 /*  11 */ "cmd ::= SHOW STREAMS",
 /*  12 */ "cmd ::= SHOW VARIABLES",
 /*  13 */ "cmd ::= SHOW SCORES",
 /*  14 */ "cmd ::= SHOW GRANTS",
 /*  15 */ "cmd ::= SHOW VNODES",
 /*  16 */ "cmd ::= SHOW VNODES ids",
 /*  17 */ "dbPrefix ::=",
 /*  18 */ "dbPrefix ::= ids DOT",
 /*  19 */ "cpxName ::=",
 /*  20 */ "cpxName ::= DOT ids",
 /*  21 */ "cmd ::= SHOW CREATE TABLE ids cpxName",
 /*  22 */ "cmd ::= SHOW CREATE STABLE ids cpxName",
 /*  23 */ "cmd ::= SHOW CREATE DATABASE ids",
 /*  24 */ "cmd ::= SHOW dbPrefix TABLES",
 /*  25 */ "cmd ::= SHOW dbPrefix TABLES LIKE STRING",
 /*  26 */ "cmd ::= SHOW dbPrefix STABLES",
 /*  27 */ "cmd ::= SHOW dbPrefix STABLES LIKE STRING",
 /*  28 */ "cmd ::= SHOW dbPrefix VGROUPS",
 /*  29 */ "cmd ::= DROP TABLE ifexists ids cpxName",
 /*  30 */ "cmd ::= DROP STABLE ifexists ids cpxName",
 /*  31 */ "cmd ::= DROP DATABASE ifexists ids",
 /*  32 */ "cmd ::= DROP TOPIC ifexists ids",
 /*  33 */ "cmd ::= DROP FUNCTION ids",
 /*  34 */ "cmd ::= DROP DNODE ids",
 /*  35 */ "cmd ::= DROP USER ids",
 /*  36 */ "cmd ::= DROP ACCOUNT ids",
 /*  37 */ "cmd ::= USE ids",
 /*  38 */ "cmd ::= DESCRIBE ids cpxName",
 /*  39 */ "cmd ::= DESC ids cpxName",
 /*  40 */ "cmd ::= ALTER USER ids PASS ids",
 /*  41 */ "cmd ::= ALTER USER ids PRIVILEGE ids",
 /*  42 */ "cmd ::= ALTER DNODE ids ids",
 /*  43 */ "cmd ::= ALTER DNODE ids ids ids",
 /*  44 */ "cmd ::= ALTER LOCAL ids",
 /*  45 */ "cmd ::= ALTER LOCAL ids ids",
 /*  46 */ "cmd ::= ALTER DATABASE ids alter_db_optr",
 /*  47 */ "cmd ::= ALTER TOPIC ids alter_topic_optr",
 /*  48 */ "cmd ::= ALTER ACCOUNT ids acct_optr",
 /*  49 */ "cmd ::= ALTER ACCOUNT ids PASS ids acct_optr",
 /*  50 */ "cmd ::= COMPACT VNODES IN LP exprlist RP",
 /*  51 */ "ids ::= ID",
 /*  52 */ "ids ::= STRING",
 /*  53 */ "ifexists ::= IF EXISTS",
 /*  54 */ "ifexists ::=",
 /*  55 */ "ifnotexists ::= IF NOT EXISTS",
 /*  56 */ "ifnotexists ::=",
 /*  57 */ "cmd ::= CREATE DNODE ids",
 /*  58 */ "cmd ::= CREATE ACCOUNT ids PASS ids acct_optr",
 /*  59 */ "cmd ::= CREATE DATABASE ifnotexists ids db_optr",
 /*  60 */ "cmd ::= CREATE TOPIC ifnotexists ids topic_optr",
 /*  61 */ "cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize",
 /*  62 */ "cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize",
 /*  63 */ "cmd ::= CREATE USER ids PASS ids",
 /*  64 */ "bufsize ::=",
 /*  65 */ "bufsize ::= BUFSIZE INTEGER",
 /*  66 */ "pps ::=",
 /*  67 */ "pps ::= PPS INTEGER",
 /*  68 */ "tseries ::=",
 /*  69 */ "tseries ::= TSERIES INTEGER",
 /*  70 */ "dbs ::=",
 /*  71 */ "dbs ::= DBS INTEGER",
 /*  72 */ "streams ::=",
 /*  73 */ "streams ::= STREAMS INTEGER",
 /*  74 */ "storage ::=",
 /*  75 */ "storage ::= STORAGE INTEGER",
 /*  76 */ "qtime ::=",
 /*  77 */ "qtime ::= QTIME INTEGER",
 /*  78 */ "users ::=",
 /*  79 */ "users ::= USERS INTEGER",
 /*  80 */ "conns ::=",
 /*  81 */ "conns ::= CONNS INTEGER",
 /*  82 */ "state ::=",
 /*  83 */ "state ::= STATE ids",
 /*  84 */ "acct_optr ::= pps tseries storage streams qtime dbs users conns state",
 /*  85 */ "intitemlist ::= intitemlist COMMA intitem",
 /*  86 */ "intitemlist ::= intitem",
 /*  87 */ "intitem ::= INTEGER",
 /*  88 */ "keep ::= KEEP intitemlist",
 /*  89 */ "cache ::= CACHE INTEGER",
 /*  90 */ "replica ::= REPLICA INTEGER",
 /*  91 */ "quorum ::= QUORUM INTEGER",
 /*  92 */ "days ::= DAYS INTEGER",
 /*  93 */ "minrows ::= MINROWS INTEGER",
 /*  94 */ "maxrows ::= MAXROWS INTEGER",
 /*  95 */ "blocks ::= BLOCKS INTEGER",
 /*  96 */ "ctime ::= CTIME INTEGER",
 /*  97 */ "wal ::= WAL INTEGER",
 /*  98 */ "fsync ::= FSYNC INTEGER",
 /*  99 */ "comp ::= COMP INTEGER",
 /* 100 */ "prec ::= PRECISION STRING",
 /* 101 */ "update ::= UPDATE INTEGER",
 /* 102 */ "cachelast ::= CACHELAST INTEGER",
 /* 103 */ "partitions ::= PARTITIONS INTEGER",
 /* 104 */ "db_optr ::=",
 /* 105 */ "db_optr ::= db_optr cache",
 /* 106 */ "db_optr ::= db_optr replica",
 /* 107 */ "db_optr ::= db_optr quorum",
 /* 108 */ "db_optr ::= db_optr days",
 /* 109 */ "db_optr ::= db_optr minrows",
 /* 110 */ "db_optr ::= db_optr maxrows",
 /* 111 */ "db_optr ::= db_optr blocks",
 /* 112 */ "db_optr ::= db_optr ctime",
 /* 113 */ "db_optr ::= db_optr wal",
 /* 114 */ "db_optr ::= db_optr fsync",
 /* 115 */ "db_optr ::= db_optr comp",
 /* 116 */ "db_optr ::= db_optr prec",
 /* 117 */ "db_optr ::= db_optr keep",
 /* 118 */ "db_optr ::= db_optr update",
 /* 119 */ "db_optr ::= db_optr cachelast",
 /* 120 */ "topic_optr ::= db_optr",
 /* 121 */ "topic_optr ::= topic_optr partitions",
 /* 122 */ "alter_db_optr ::=",
 /* 123 */ "alter_db_optr ::= alter_db_optr replica",
 /* 124 */ "alter_db_optr ::= alter_db_optr quorum",
 /* 125 */ "alter_db_optr ::= alter_db_optr keep",
 /* 126 */ "alter_db_optr ::= alter_db_optr blocks",
 /* 127 */ "alter_db_optr ::= alter_db_optr comp",
 /* 128 */ "alter_db_optr ::= alter_db_optr update",
 /* 129 */ "alter_db_optr ::= alter_db_optr cachelast",
 /* 130 */ "alter_topic_optr ::= alter_db_optr",
 /* 131 */ "alter_topic_optr ::= alter_topic_optr partitions",
 /* 132 */ "typename ::= ids",
 /* 133 */ "typename ::= ids LP signed RP",
 /* 134 */ "typename ::= ids UNSIGNED",
 /* 135 */ "signed ::= INTEGER",
 /* 136 */ "signed ::= PLUS INTEGER",
 /* 137 */ "signed ::= MINUS INTEGER",
 /* 138 */ "cmd ::= CREATE TABLE create_table_args",
 /* 139 */ "cmd ::= CREATE TABLE create_stable_args",
 /* 140 */ "cmd ::= CREATE STABLE create_stable_args",
 /* 141 */ "cmd ::= CREATE TABLE create_table_list",
 /* 142 */ "create_table_list ::= create_from_stable",
 /* 143 */ "create_table_list ::= create_table_list create_from_stable",
 /* 144 */ "create_table_args ::= ifnotexists ids cpxName LP columnlist RP",
 /* 145 */ "create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP",
 /* 146 */ "create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP",
 /* 147 */ "create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP",
 /* 148 */ "tagNamelist ::= tagNamelist COMMA ids",
 /* 149 */ "tagNamelist ::= ids",
 /* 150 */ "create_table_args ::= ifnotexists ids cpxName to_opt split_opt AS select",
 /* 151 */ "to_opt ::=",
 /* 152 */ "to_opt ::= TO ids cpxName",
 /* 153 */ "split_opt ::=",
 /* 154 */ "split_opt ::= SPLIT ids",
 /* 155 */ "columnlist ::= columnlist COMMA column",
 /* 156 */ "columnlist ::= column",
 /* 157 */ "column ::= ids typename",
 /* 158 */ "tagitemlist ::= tagitemlist COMMA tagitem",
 /* 159 */ "tagitemlist ::= tagitem",
 /* 160 */ "tagitem ::= INTEGER",
 /* 161 */ "tagitem ::= FLOAT",
 /* 162 */ "tagitem ::= STRING",
 /* 163 */ "tagitem ::= BOOL",
 /* 164 */ "tagitem ::= NULL",
 /* 165 */ "tagitem ::= NOW",
 /* 166 */ "tagitem ::= NOW PLUS VARIABLE",
 /* 167 */ "tagitem ::= NOW MINUS VARIABLE",
 /* 168 */ "tagitem ::= MINUS INTEGER",
 /* 169 */ "tagitem ::= MINUS FLOAT",
 /* 170 */ "tagitem ::= PLUS INTEGER",
 /* 171 */ "tagitem ::= PLUS FLOAT",
 /* 172 */ "select ::= SELECT selcollist from where_opt range_option interval_option sliding_opt session_option windowstate_option fill_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt",
 /* 173 */ "select ::= LP select RP",
 /* 174 */ "union ::= select",
 /* 175 */ "union ::= union UNION ALL select",
 /* 176 */ "cmd ::= union",
 /* 177 */ "select ::= SELECT selcollist",
 /* 178 */ "sclp ::= selcollist COMMA",
 /* 179 */ "sclp ::=",
 /* 180 */ "selcollist ::= sclp distinct expr as",
 /* 181 */ "selcollist ::= sclp STAR",
 /* 182 */ "as ::= AS ids",
 /* 183 */ "as ::= ids",
 /* 184 */ "as ::=",
 /* 185 */ "distinct ::= DISTINCT",
 /* 186 */ "distinct ::=",
 /* 187 */ "from ::= FROM tablelist",
 /* 188 */ "from ::= FROM sub",
 /* 189 */ "sub ::= LP union RP",
 /* 190 */ "sub ::= LP union RP ids",
 /* 191 */ "sub ::= sub COMMA LP union RP ids",
 /* 192 */ "tablelist ::= ids cpxName",
 /* 193 */ "tablelist ::= ids cpxName ids",
 /* 194 */ "tablelist ::= tablelist COMMA ids cpxName",
 /* 195 */ "tablelist ::= tablelist COMMA ids cpxName ids",
 /* 196 */ "tmvar ::= VARIABLE",
 /* 197 */ "timestamp ::= INTEGER",
 /* 198 */ "timestamp ::= MINUS INTEGER",
 /* 199 */ "timestamp ::= PLUS INTEGER",
 /* 200 */ "timestamp ::= STRING",
 /* 201 */ "timestamp ::= NOW",
 /* 202 */ "timestamp ::= NOW PLUS VARIABLE",
 /* 203 */ "timestamp ::= NOW MINUS VARIABLE",
 /* 204 */ "range_option ::=",
 /* 205 */ "range_option ::= RANGE LP timestamp COMMA timestamp RP",
 /* 206 */ "interval_option ::= intervalKey LP tmvar RP",
 /* 207 */ "interval_option ::= intervalKey LP tmvar COMMA tmvar RP",
 /* 208 */ "interval_option ::=",
 /* 209 */ "intervalKey ::= INTERVAL",
 /* 210 */ "intervalKey ::= EVERY",
 /* 211 */ "session_option ::=",
 /* 212 */ "session_option ::= SESSION LP ids cpxName COMMA tmvar RP",
 /* 213 */ "windowstate_option ::=",
 /* 214 */ "windowstate_option ::= STATE_WINDOW LP ids RP",
 /* 215 */ "fill_opt ::=",
 /* 216 */ "fill_opt ::= FILL LP ID COMMA tagitemlist RP",
 /* 217 */ "fill_opt ::= FILL LP ID RP",
 /* 218 */ "sliding_opt ::= SLIDING LP tmvar RP",
 /* 219 */ "sliding_opt ::=",
 /* 220 */ "orderby_opt ::=",
 /* 221 */ "orderby_opt ::= ORDER BY sortlist",
 /* 222 */ "sortlist ::= sortlist COMMA item sortorder",
 /* 223 */ "sortlist ::= sortlist COMMA arrow sortorder",
 /* 224 */ "sortlist ::= item sortorder",
 /* 225 */ "sortlist ::= arrow sortorder",
 /* 226 */ "item ::= ID",
 /* 227 */ "item ::= ID DOT ID",
 /* 228 */ "sortorder ::= ASC",
 /* 229 */ "sortorder ::= DESC",
 /* 230 */ "sortorder ::=",
 /* 231 */ "groupby_opt ::=",
 /* 232 */ "groupby_opt ::= GROUP BY grouplist",
 /* 233 */ "grouplist ::= grouplist COMMA item",
 /* 234 */ "grouplist ::= grouplist COMMA arrow",
 /* 235 */ "grouplist ::= item",
 /* 236 */ "grouplist ::= arrow",
 /* 237 */ "having_opt ::=",
 /* 238 */ "having_opt ::= HAVING expr",
 /* 239 */ "limit_opt ::=",
 /* 240 */ "limit_opt ::= LIMIT signed",
 /* 241 */ "limit_opt ::= LIMIT signed OFFSET signed",
 /* 242 */ "limit_opt ::= LIMIT signed COMMA signed",
 /* 243 */ "slimit_opt ::=",
 /* 244 */ "slimit_opt ::= SLIMIT signed",
 /* 245 */ "slimit_opt ::= SLIMIT signed SOFFSET signed",
 /* 246 */ "slimit_opt ::= SLIMIT signed COMMA signed",
 /* 247 */ "where_opt ::=",
 /* 248 */ "where_opt ::= WHERE expr",
 /* 249 */ "expr ::= LP expr RP",
 /* 250 */ "expr ::= ID",
 /* 251 */ "expr ::= ID DOT ID",
 /* 252 */ "expr ::= ID DOT STAR",
 /* 253 */ "expr ::= INTEGER",
 /* 254 */ "expr ::= MINUS INTEGER",
 /* 255 */ "expr ::= PLUS INTEGER",
 /* 256 */ "expr ::= FLOAT",
 /* 257 */ "expr ::= MINUS FLOAT",
 /* 258 */ "expr ::= PLUS FLOAT",
 /* 259 */ "expr ::= STRING",
 /* 260 */ "expr ::= NOW",
 /* 261 */ "expr ::= TODAY",
 /* 262 */ "expr ::= VARIABLE",
 /* 263 */ "expr ::= PLUS VARIABLE",
 /* 264 */ "expr ::= MINUS VARIABLE",
 /* 265 */ "expr ::= BOOL",
 /* 266 */ "expr ::= NULL",
 /* 267 */ "expr ::= ID LP exprlist RP",
 /* 268 */ "expr ::= ID LP STAR RP",
 /* 269 */ "expr ::= ID LP expr AS typename RP",
 /* 270 */ "expr ::= expr IS NULL",
 /* 271 */ "expr ::= expr IS NOT NULL",
 /* 272 */ "expr ::= expr LT expr",
 /* 273 */ "expr ::= expr GT expr",
 /* 274 */ "expr ::= expr LE expr",
 /* 275 */ "expr ::= expr GE expr",
 /* 276 */ "expr ::= expr NE expr",
 /* 277 */ "expr ::= expr EQ expr",
 /* 278 */ "expr ::= expr BETWEEN expr AND expr",
 /* 279 */ "expr ::= expr AND expr",
 /* 280 */ "expr ::= expr OR expr",
 /* 281 */ "expr ::= expr PLUS expr",
 /* 282 */ "expr ::= expr MINUS expr",
 /* 283 */ "expr ::= expr STAR expr",
 /* 284 */ "expr ::= expr SLASH expr",
 /* 285 */ "expr ::= expr REM expr",
 /* 286 */ "expr ::= expr LIKE expr",
 /* 287 */ "expr ::= expr MATCH expr",
 /* 288 */ "expr ::= expr NMATCH expr",
 /* 289 */ "expr ::= ID CONTAINS STRING",
 /* 290 */ "expr ::= ID DOT ID CONTAINS STRING",
 /* 291 */ "arrow ::= ID ARROW STRING",
 /* 292 */ "arrow ::= ID DOT ID ARROW STRING",
 /* 293 */ "expr ::= arrow",
 /* 294 */ "expr ::= expr IN LP exprlist RP",
 /* 295 */ "exprlist ::= exprlist COMMA expritem",
 /* 296 */ "exprlist ::= expritem",
 /* 297 */ "expritem ::= expr",
 /* 298 */ "expritem ::=",
 /* 299 */ "cmd ::= RESET QUERY CACHE",
 /* 300 */ "cmd ::= SYNCDB ids REPLICA",
 /* 301 */ "cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist",
 /* 302 */ "cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids",
 /* 303 */ "cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist",
 /* 304 */ "cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist",
 /* 305 */ "cmd ::= ALTER TABLE ids cpxName DROP TAG ids",
 /* 306 */ "cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids",
 /* 307 */ "cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem",
 /* 308 */ "cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist",
 /* 309 */ "cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist",
 /* 310 */ "cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids",
 /* 311 */ "cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist",
 /* 312 */ "cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist",
 /* 313 */ "cmd ::= ALTER STABLE ids cpxName DROP TAG ids",
 /* 314 */ "cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids",
 /* 315 */ "cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem",
 /* 316 */ "cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist",
 /* 317 */ "cmd ::= KILL CONNECTION INTEGER",
 /* 318 */ "cmd ::= KILL STREAM INTEGER COLON INTEGER",
 /* 319 */ "cmd ::= KILL QUERY INTEGER COLON INTEGER",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypParser){
  yyParser *pParser = (yyParser*)yypParser;
#ifdef YYTRACKMAXSTACKDEPTH
  pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  pParser->yytos = NULL;
  pParser->yystack = NULL;
  pParser->yystksz = 0;
  if( yyGrowStack(pParser) ){
    pParser->yystack = &pParser->yystk0;
    pParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  pParser->yyerrcnt = -1;
#endif
  pParser->yytos = pParser->yystack;
  pParser->yystack[0].stateno = 0;
  pParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  pParser->yystackEnd = &pParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ) ParseInit(pParser);
  return pParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 214: /* exprlist */
    case 261: /* selcollist */
    case 276: /* sclp */
{
tSqlExprListDestroy((yypminor->yy525));
}
      break;
    case 229: /* intitemlist */
    case 231: /* keep */
    case 252: /* columnlist */
    case 253: /* tagitemlist */
    case 254: /* tagNamelist */
    case 269: /* fill_opt */
    case 270: /* groupby_opt */
    case 272: /* orderby_opt */
    case 285: /* sortlist */
    case 289: /* grouplist */
{
taosArrayDestroy(&(yypminor->yy525));
}
      break;
    case 250: /* create_table_list */
{
destroyCreateTableSql((yypminor->yy572));
}
      break;
    case 257: /* select */
{
destroySqlNode((yypminor->yy86));
}
      break;
    case 262: /* from */
    case 280: /* tablelist */
    case 281: /* sub */
{
destroyRelationInfo((yypminor->yy328));
}
      break;
    case 263: /* where_opt */
    case 271: /* having_opt */
    case 278: /* expr */
    case 283: /* timestamp */
    case 288: /* arrow */
    case 290: /* expritem */
{
tSqlExprDestroy((yypminor->yy142));
}
      break;
    case 275: /* union */
{
destroyAllSqlNode((yypminor->yy525));
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 && i+YYNTOKEN<=sizeof(yy_lookahead)/sizeof(yy_lookahead[0]) );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;       /* Symbol on the left-hand side of the rule */
  signed char nrhs;     /* Negative of the number of RHS symbols in the rule */
} yyRuleInfo[] = {
  {  205,   -1 }, /* (0) program ::= cmd */
  {  206,   -2 }, /* (1) cmd ::= SHOW DATABASES */
  {  206,   -2 }, /* (2) cmd ::= SHOW TOPICS */
  {  206,   -2 }, /* (3) cmd ::= SHOW FUNCTIONS */
  {  206,   -2 }, /* (4) cmd ::= SHOW MNODES */
  {  206,   -2 }, /* (5) cmd ::= SHOW DNODES */
  {  206,   -2 }, /* (6) cmd ::= SHOW ACCOUNTS */
  {  206,   -2 }, /* (7) cmd ::= SHOW USERS */
  {  206,   -2 }, /* (8) cmd ::= SHOW MODULES */
  {  206,   -2 }, /* (9) cmd ::= SHOW QUERIES */
  {  206,   -2 }, /* (10) cmd ::= SHOW CONNECTIONS */
  {  206,   -2 }, /* (11) cmd ::= SHOW STREAMS */
  {  206,   -2 }, /* (12) cmd ::= SHOW VARIABLES */
  {  206,   -2 }, /* (13) cmd ::= SHOW SCORES */
  {  206,   -2 }, /* (14) cmd ::= SHOW GRANTS */
  {  206,   -2 }, /* (15) cmd ::= SHOW VNODES */
  {  206,   -3 }, /* (16) cmd ::= SHOW VNODES ids */
  {  208,    0 }, /* (17) dbPrefix ::= */
  {  208,   -2 }, /* (18) dbPrefix ::= ids DOT */
  {  209,    0 }, /* (19) cpxName ::= */
  {  209,   -2 }, /* (20) cpxName ::= DOT ids */
  {  206,   -5 }, /* (21) cmd ::= SHOW CREATE TABLE ids cpxName */
  {  206,   -5 }, /* (22) cmd ::= SHOW CREATE STABLE ids cpxName */
  {  206,   -4 }, /* (23) cmd ::= SHOW CREATE DATABASE ids */
  {  206,   -3 }, /* (24) cmd ::= SHOW dbPrefix TABLES */
  {  206,   -5 }, /* (25) cmd ::= SHOW dbPrefix TABLES LIKE STRING */
  {  206,   -3 }, /* (26) cmd ::= SHOW dbPrefix STABLES */
  {  206,   -5 }, /* (27) cmd ::= SHOW dbPrefix STABLES LIKE STRING */
  {  206,   -3 }, /* (28) cmd ::= SHOW dbPrefix VGROUPS */
  {  206,   -5 }, /* (29) cmd ::= DROP TABLE ifexists ids cpxName */
  {  206,   -5 }, /* (30) cmd ::= DROP STABLE ifexists ids cpxName */
  {  206,   -4 }, /* (31) cmd ::= DROP DATABASE ifexists ids */
  {  206,   -4 }, /* (32) cmd ::= DROP TOPIC ifexists ids */
  {  206,   -3 }, /* (33) cmd ::= DROP FUNCTION ids */
  {  206,   -3 }, /* (34) cmd ::= DROP DNODE ids */
  {  206,   -3 }, /* (35) cmd ::= DROP USER ids */
  {  206,   -3 }, /* (36) cmd ::= DROP ACCOUNT ids */
  {  206,   -2 }, /* (37) cmd ::= USE ids */
  {  206,   -3 }, /* (38) cmd ::= DESCRIBE ids cpxName */
  {  206,   -3 }, /* (39) cmd ::= DESC ids cpxName */
  {  206,   -5 }, /* (40) cmd ::= ALTER USER ids PASS ids */
  {  206,   -5 }, /* (41) cmd ::= ALTER USER ids PRIVILEGE ids */
  {  206,   -4 }, /* (42) cmd ::= ALTER DNODE ids ids */
  {  206,   -5 }, /* (43) cmd ::= ALTER DNODE ids ids ids */
  {  206,   -3 }, /* (44) cmd ::= ALTER LOCAL ids */
  {  206,   -4 }, /* (45) cmd ::= ALTER LOCAL ids ids */
  {  206,   -4 }, /* (46) cmd ::= ALTER DATABASE ids alter_db_optr */
  {  206,   -4 }, /* (47) cmd ::= ALTER TOPIC ids alter_topic_optr */
  {  206,   -4 }, /* (48) cmd ::= ALTER ACCOUNT ids acct_optr */
  {  206,   -6 }, /* (49) cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
  {  206,   -6 }, /* (50) cmd ::= COMPACT VNODES IN LP exprlist RP */
  {  207,   -1 }, /* (51) ids ::= ID */
  {  207,   -1 }, /* (52) ids ::= STRING */
  {  210,   -2 }, /* (53) ifexists ::= IF EXISTS */
  {  210,    0 }, /* (54) ifexists ::= */
  {  215,   -3 }, /* (55) ifnotexists ::= IF NOT EXISTS */
  {  215,    0 }, /* (56) ifnotexists ::= */
  {  206,   -3 }, /* (57) cmd ::= CREATE DNODE ids */
  {  206,   -6 }, /* (58) cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
  {  206,   -5 }, /* (59) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
  {  206,   -5 }, /* (60) cmd ::= CREATE TOPIC ifnotexists ids topic_optr */
  {  206,   -8 }, /* (61) cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
  {  206,   -9 }, /* (62) cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
  {  206,   -5 }, /* (63) cmd ::= CREATE USER ids PASS ids */
  {  219,    0 }, /* (64) bufsize ::= */
  {  219,   -2 }, /* (65) bufsize ::= BUFSIZE INTEGER */
  {  220,    0 }, /* (66) pps ::= */
  {  220,   -2 }, /* (67) pps ::= PPS INTEGER */
  {  221,    0 }, /* (68) tseries ::= */
  {  221,   -2 }, /* (69) tseries ::= TSERIES INTEGER */
  {  222,    0 }, /* (70) dbs ::= */
  {  222,   -2 }, /* (71) dbs ::= DBS INTEGER */
  {  223,    0 }, /* (72) streams ::= */
  {  223,   -2 }, /* (73) streams ::= STREAMS INTEGER */
  {  224,    0 }, /* (74) storage ::= */
  {  224,   -2 }, /* (75) storage ::= STORAGE INTEGER */
  {  225,    0 }, /* (76) qtime ::= */
  {  225,   -2 }, /* (77) qtime ::= QTIME INTEGER */
  {  226,    0 }, /* (78) users ::= */
  {  226,   -2 }, /* (79) users ::= USERS INTEGER */
  {  227,    0 }, /* (80) conns ::= */
  {  227,   -2 }, /* (81) conns ::= CONNS INTEGER */
  {  228,    0 }, /* (82) state ::= */
  {  228,   -2 }, /* (83) state ::= STATE ids */
  {  213,   -9 }, /* (84) acct_optr ::= pps tseries storage streams qtime dbs users conns state */
  {  229,   -3 }, /* (85) intitemlist ::= intitemlist COMMA intitem */
  {  229,   -1 }, /* (86) intitemlist ::= intitem */
  {  230,   -1 }, /* (87) intitem ::= INTEGER */
  {  231,   -2 }, /* (88) keep ::= KEEP intitemlist */
  {  232,   -2 }, /* (89) cache ::= CACHE INTEGER */
  {  233,   -2 }, /* (90) replica ::= REPLICA INTEGER */
  {  234,   -2 }, /* (91) quorum ::= QUORUM INTEGER */
  {  235,   -2 }, /* (92) days ::= DAYS INTEGER */
  {  236,   -2 }, /* (93) minrows ::= MINROWS INTEGER */
  {  237,   -2 }, /* (94) maxrows ::= MAXROWS INTEGER */
  {  238,   -2 }, /* (95) blocks ::= BLOCKS INTEGER */
  {  239,   -2 }, /* (96) ctime ::= CTIME INTEGER */
  {  240,   -2 }, /* (97) wal ::= WAL INTEGER */
  {  241,   -2 }, /* (98) fsync ::= FSYNC INTEGER */
  {  242,   -2 }, /* (99) comp ::= COMP INTEGER */
  {  243,   -2 }, /* (100) prec ::= PRECISION STRING */
  {  244,   -2 }, /* (101) update ::= UPDATE INTEGER */
  {  245,   -2 }, /* (102) cachelast ::= CACHELAST INTEGER */
  {  246,   -2 }, /* (103) partitions ::= PARTITIONS INTEGER */
  {  216,    0 }, /* (104) db_optr ::= */
  {  216,   -2 }, /* (105) db_optr ::= db_optr cache */
  {  216,   -2 }, /* (106) db_optr ::= db_optr replica */
  {  216,   -2 }, /* (107) db_optr ::= db_optr quorum */
  {  216,   -2 }, /* (108) db_optr ::= db_optr days */
  {  216,   -2 }, /* (109) db_optr ::= db_optr minrows */
  {  216,   -2 }, /* (110) db_optr ::= db_optr maxrows */
  {  216,   -2 }, /* (111) db_optr ::= db_optr blocks */
  {  216,   -2 }, /* (112) db_optr ::= db_optr ctime */
  {  216,   -2 }, /* (113) db_optr ::= db_optr wal */
  {  216,   -2 }, /* (114) db_optr ::= db_optr fsync */
  {  216,   -2 }, /* (115) db_optr ::= db_optr comp */
  {  216,   -2 }, /* (116) db_optr ::= db_optr prec */
  {  216,   -2 }, /* (117) db_optr ::= db_optr keep */
  {  216,   -2 }, /* (118) db_optr ::= db_optr update */
  {  216,   -2 }, /* (119) db_optr ::= db_optr cachelast */
  {  217,   -1 }, /* (120) topic_optr ::= db_optr */
  {  217,   -2 }, /* (121) topic_optr ::= topic_optr partitions */
  {  211,    0 }, /* (122) alter_db_optr ::= */
  {  211,   -2 }, /* (123) alter_db_optr ::= alter_db_optr replica */
  {  211,   -2 }, /* (124) alter_db_optr ::= alter_db_optr quorum */
  {  211,   -2 }, /* (125) alter_db_optr ::= alter_db_optr keep */
  {  211,   -2 }, /* (126) alter_db_optr ::= alter_db_optr blocks */
  {  211,   -2 }, /* (127) alter_db_optr ::= alter_db_optr comp */
  {  211,   -2 }, /* (128) alter_db_optr ::= alter_db_optr update */
  {  211,   -2 }, /* (129) alter_db_optr ::= alter_db_optr cachelast */
  {  212,   -1 }, /* (130) alter_topic_optr ::= alter_db_optr */
  {  212,   -2 }, /* (131) alter_topic_optr ::= alter_topic_optr partitions */
  {  218,   -1 }, /* (132) typename ::= ids */
  {  218,   -4 }, /* (133) typename ::= ids LP signed RP */
  {  218,   -2 }, /* (134) typename ::= ids UNSIGNED */
  {  247,   -1 }, /* (135) signed ::= INTEGER */
  {  247,   -2 }, /* (136) signed ::= PLUS INTEGER */
  {  247,   -2 }, /* (137) signed ::= MINUS INTEGER */
  {  206,   -3 }, /* (138) cmd ::= CREATE TABLE create_table_args */
  {  206,   -3 }, /* (139) cmd ::= CREATE TABLE create_stable_args */
  {  206,   -3 }, /* (140) cmd ::= CREATE STABLE create_stable_args */
  {  206,   -3 }, /* (141) cmd ::= CREATE TABLE create_table_list */
  {  250,   -1 }, /* (142) create_table_list ::= create_from_stable */
  {  250,   -2 }, /* (143) create_table_list ::= create_table_list create_from_stable */
  {  248,   -6 }, /* (144) create_table_args ::= ifnotexists ids cpxName LP columnlist RP */
  {  249,  -10 }, /* (145) create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP */
  {  251,  -10 }, /* (146) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP */
  {  251,  -13 }, /* (147) create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP */
  {  254,   -3 }, /* (148) tagNamelist ::= tagNamelist COMMA ids */
  {  254,   -1 }, /* (149) tagNamelist ::= ids */
  {  248,   -7 }, /* (150) create_table_args ::= ifnotexists ids cpxName to_opt split_opt AS select */
  {  255,    0 }, /* (151) to_opt ::= */
  {  255,   -3 }, /* (152) to_opt ::= TO ids cpxName */
  {  256,    0 }, /* (153) split_opt ::= */
  {  256,   -2 }, /* (154) split_opt ::= SPLIT ids */
  {  252,   -3 }, /* (155) columnlist ::= columnlist COMMA column */
  {  252,   -1 }, /* (156) columnlist ::= column */
  {  259,   -2 }, /* (157) column ::= ids typename */
  {  253,   -3 }, /* (158) tagitemlist ::= tagitemlist COMMA tagitem */
  {  253,   -1 }, /* (159) tagitemlist ::= tagitem */
  {  260,   -1 }, /* (160) tagitem ::= INTEGER */
  {  260,   -1 }, /* (161) tagitem ::= FLOAT */
  {  260,   -1 }, /* (162) tagitem ::= STRING */
  {  260,   -1 }, /* (163) tagitem ::= BOOL */
  {  260,   -1 }, /* (164) tagitem ::= NULL */
  {  260,   -1 }, /* (165) tagitem ::= NOW */
  {  260,   -3 }, /* (166) tagitem ::= NOW PLUS VARIABLE */
  {  260,   -3 }, /* (167) tagitem ::= NOW MINUS VARIABLE */
  {  260,   -2 }, /* (168) tagitem ::= MINUS INTEGER */
  {  260,   -2 }, /* (169) tagitem ::= MINUS FLOAT */
  {  260,   -2 }, /* (170) tagitem ::= PLUS INTEGER */
  {  260,   -2 }, /* (171) tagitem ::= PLUS FLOAT */
  {  257,  -15 }, /* (172) select ::= SELECT selcollist from where_opt range_option interval_option sliding_opt session_option windowstate_option fill_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt */
  {  257,   -3 }, /* (173) select ::= LP select RP */
  {  275,   -1 }, /* (174) union ::= select */
  {  275,   -4 }, /* (175) union ::= union UNION ALL select */
  {  206,   -1 }, /* (176) cmd ::= union */
  {  257,   -2 }, /* (177) select ::= SELECT selcollist */
  {  276,   -2 }, /* (178) sclp ::= selcollist COMMA */
  {  276,    0 }, /* (179) sclp ::= */
  {  261,   -4 }, /* (180) selcollist ::= sclp distinct expr as */
  {  261,   -2 }, /* (181) selcollist ::= sclp STAR */
  {  279,   -2 }, /* (182) as ::= AS ids */
  {  279,   -1 }, /* (183) as ::= ids */
  {  279,    0 }, /* (184) as ::= */
  {  277,   -1 }, /* (185) distinct ::= DISTINCT */
  {  277,    0 }, /* (186) distinct ::= */
  {  262,   -2 }, /* (187) from ::= FROM tablelist */
  {  262,   -2 }, /* (188) from ::= FROM sub */
  {  281,   -3 }, /* (189) sub ::= LP union RP */
  {  281,   -4 }, /* (190) sub ::= LP union RP ids */
  {  281,   -6 }, /* (191) sub ::= sub COMMA LP union RP ids */
  {  280,   -2 }, /* (192) tablelist ::= ids cpxName */
  {  280,   -3 }, /* (193) tablelist ::= ids cpxName ids */
  {  280,   -4 }, /* (194) tablelist ::= tablelist COMMA ids cpxName */
  {  280,   -5 }, /* (195) tablelist ::= tablelist COMMA ids cpxName ids */
  {  282,   -1 }, /* (196) tmvar ::= VARIABLE */
  {  283,   -1 }, /* (197) timestamp ::= INTEGER */
  {  283,   -2 }, /* (198) timestamp ::= MINUS INTEGER */
  {  283,   -2 }, /* (199) timestamp ::= PLUS INTEGER */
  {  283,   -1 }, /* (200) timestamp ::= STRING */
  {  283,   -1 }, /* (201) timestamp ::= NOW */
  {  283,   -3 }, /* (202) timestamp ::= NOW PLUS VARIABLE */
  {  283,   -3 }, /* (203) timestamp ::= NOW MINUS VARIABLE */
  {  264,    0 }, /* (204) range_option ::= */
  {  264,   -6 }, /* (205) range_option ::= RANGE LP timestamp COMMA timestamp RP */
  {  265,   -4 }, /* (206) interval_option ::= intervalKey LP tmvar RP */
  {  265,   -6 }, /* (207) interval_option ::= intervalKey LP tmvar COMMA tmvar RP */
  {  265,    0 }, /* (208) interval_option ::= */
  {  284,   -1 }, /* (209) intervalKey ::= INTERVAL */
  {  284,   -1 }, /* (210) intervalKey ::= EVERY */
  {  267,    0 }, /* (211) session_option ::= */
  {  267,   -7 }, /* (212) session_option ::= SESSION LP ids cpxName COMMA tmvar RP */
  {  268,    0 }, /* (213) windowstate_option ::= */
  {  268,   -4 }, /* (214) windowstate_option ::= STATE_WINDOW LP ids RP */
  {  269,    0 }, /* (215) fill_opt ::= */
  {  269,   -6 }, /* (216) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
  {  269,   -4 }, /* (217) fill_opt ::= FILL LP ID RP */
  {  266,   -4 }, /* (218) sliding_opt ::= SLIDING LP tmvar RP */
  {  266,    0 }, /* (219) sliding_opt ::= */
  {  272,    0 }, /* (220) orderby_opt ::= */
  {  272,   -3 }, /* (221) orderby_opt ::= ORDER BY sortlist */
  {  285,   -4 }, /* (222) sortlist ::= sortlist COMMA item sortorder */
  {  285,   -4 }, /* (223) sortlist ::= sortlist COMMA arrow sortorder */
  {  285,   -2 }, /* (224) sortlist ::= item sortorder */
  {  285,   -2 }, /* (225) sortlist ::= arrow sortorder */
  {  286,   -1 }, /* (226) item ::= ID */
  {  286,   -3 }, /* (227) item ::= ID DOT ID */
  {  287,   -1 }, /* (228) sortorder ::= ASC */
  {  287,   -1 }, /* (229) sortorder ::= DESC */
  {  287,    0 }, /* (230) sortorder ::= */
  {  270,    0 }, /* (231) groupby_opt ::= */
  {  270,   -3 }, /* (232) groupby_opt ::= GROUP BY grouplist */
  {  289,   -3 }, /* (233) grouplist ::= grouplist COMMA item */
  {  289,   -3 }, /* (234) grouplist ::= grouplist COMMA arrow */
  {  289,   -1 }, /* (235) grouplist ::= item */
  {  289,   -1 }, /* (236) grouplist ::= arrow */
  {  271,    0 }, /* (237) having_opt ::= */
  {  271,   -2 }, /* (238) having_opt ::= HAVING expr */
  {  274,    0 }, /* (239) limit_opt ::= */
  {  274,   -2 }, /* (240) limit_opt ::= LIMIT signed */
  {  274,   -4 }, /* (241) limit_opt ::= LIMIT signed OFFSET signed */
  {  274,   -4 }, /* (242) limit_opt ::= LIMIT signed COMMA signed */
  {  273,    0 }, /* (243) slimit_opt ::= */
  {  273,   -2 }, /* (244) slimit_opt ::= SLIMIT signed */
  {  273,   -4 }, /* (245) slimit_opt ::= SLIMIT signed SOFFSET signed */
  {  273,   -4 }, /* (246) slimit_opt ::= SLIMIT signed COMMA signed */
  {  263,    0 }, /* (247) where_opt ::= */
  {  263,   -2 }, /* (248) where_opt ::= WHERE expr */
  {  278,   -3 }, /* (249) expr ::= LP expr RP */
  {  278,   -1 }, /* (250) expr ::= ID */
  {  278,   -3 }, /* (251) expr ::= ID DOT ID */
  {  278,   -3 }, /* (252) expr ::= ID DOT STAR */
  {  278,   -1 }, /* (253) expr ::= INTEGER */
  {  278,   -2 }, /* (254) expr ::= MINUS INTEGER */
  {  278,   -2 }, /* (255) expr ::= PLUS INTEGER */
  {  278,   -1 }, /* (256) expr ::= FLOAT */
  {  278,   -2 }, /* (257) expr ::= MINUS FLOAT */
  {  278,   -2 }, /* (258) expr ::= PLUS FLOAT */
  {  278,   -1 }, /* (259) expr ::= STRING */
  {  278,   -1 }, /* (260) expr ::= NOW */
  {  278,   -1 }, /* (261) expr ::= TODAY */
  {  278,   -1 }, /* (262) expr ::= VARIABLE */
  {  278,   -2 }, /* (263) expr ::= PLUS VARIABLE */
  {  278,   -2 }, /* (264) expr ::= MINUS VARIABLE */
  {  278,   -1 }, /* (265) expr ::= BOOL */
  {  278,   -1 }, /* (266) expr ::= NULL */
  {  278,   -4 }, /* (267) expr ::= ID LP exprlist RP */
  {  278,   -4 }, /* (268) expr ::= ID LP STAR RP */
  {  278,   -6 }, /* (269) expr ::= ID LP expr AS typename RP */
  {  278,   -3 }, /* (270) expr ::= expr IS NULL */
  {  278,   -4 }, /* (271) expr ::= expr IS NOT NULL */
  {  278,   -3 }, /* (272) expr ::= expr LT expr */
  {  278,   -3 }, /* (273) expr ::= expr GT expr */
  {  278,   -3 }, /* (274) expr ::= expr LE expr */
  {  278,   -3 }, /* (275) expr ::= expr GE expr */
  {  278,   -3 }, /* (276) expr ::= expr NE expr */
  {  278,   -3 }, /* (277) expr ::= expr EQ expr */
  {  278,   -5 }, /* (278) expr ::= expr BETWEEN expr AND expr */
  {  278,   -3 }, /* (279) expr ::= expr AND expr */
  {  278,   -3 }, /* (280) expr ::= expr OR expr */
  {  278,   -3 }, /* (281) expr ::= expr PLUS expr */
  {  278,   -3 }, /* (282) expr ::= expr MINUS expr */
  {  278,   -3 }, /* (283) expr ::= expr STAR expr */
  {  278,   -3 }, /* (284) expr ::= expr SLASH expr */
  {  278,   -3 }, /* (285) expr ::= expr REM expr */
  {  278,   -3 }, /* (286) expr ::= expr LIKE expr */
  {  278,   -3 }, /* (287) expr ::= expr MATCH expr */
  {  278,   -3 }, /* (288) expr ::= expr NMATCH expr */
  {  278,   -3 }, /* (289) expr ::= ID CONTAINS STRING */
  {  278,   -5 }, /* (290) expr ::= ID DOT ID CONTAINS STRING */
  {  288,   -3 }, /* (291) arrow ::= ID ARROW STRING */
  {  288,   -5 }, /* (292) arrow ::= ID DOT ID ARROW STRING */
  {  278,   -1 }, /* (293) expr ::= arrow */
  {  278,   -5 }, /* (294) expr ::= expr IN LP exprlist RP */
  {  214,   -3 }, /* (295) exprlist ::= exprlist COMMA expritem */
  {  214,   -1 }, /* (296) exprlist ::= expritem */
  {  290,   -1 }, /* (297) expritem ::= expr */
  {  290,    0 }, /* (298) expritem ::= */
  {  206,   -3 }, /* (299) cmd ::= RESET QUERY CACHE */
  {  206,   -3 }, /* (300) cmd ::= SYNCDB ids REPLICA */
  {  206,   -7 }, /* (301) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
  {  206,   -7 }, /* (302) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
  {  206,   -7 }, /* (303) cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist */
  {  206,   -7 }, /* (304) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
  {  206,   -7 }, /* (305) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
  {  206,   -8 }, /* (306) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
  {  206,   -9 }, /* (307) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
  {  206,   -7 }, /* (308) cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist */
  {  206,   -7 }, /* (309) cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist */
  {  206,   -7 }, /* (310) cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids */
  {  206,   -7 }, /* (311) cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist */
  {  206,   -7 }, /* (312) cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist */
  {  206,   -7 }, /* (313) cmd ::= ALTER STABLE ids cpxName DROP TAG ids */
  {  206,   -8 }, /* (314) cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids */
  {  206,   -9 }, /* (315) cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem */
  {  206,   -7 }, /* (316) cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist */
  {  206,   -3 }, /* (317) cmd ::= KILL CONNECTION INTEGER */
  {  206,   -5 }, /* (318) cmd ::= KILL STREAM INTEGER COLON INTEGER */
  {  206,   -5 }, /* (319) cmd ::= KILL QUERY INTEGER COLON INTEGER */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= cmd */
      case 138: /* cmd ::= CREATE TABLE create_table_args */ yytestcase(yyruleno==138);
      case 139: /* cmd ::= CREATE TABLE create_stable_args */ yytestcase(yyruleno==139);
      case 140: /* cmd ::= CREATE STABLE create_stable_args */ yytestcase(yyruleno==140);
{}
        break;
      case 1: /* cmd ::= SHOW DATABASES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DB, 0, 0);}
        break;
      case 2: /* cmd ::= SHOW TOPICS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_TP, 0, 0);}
        break;
      case 3: /* cmd ::= SHOW FUNCTIONS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_FUNCTION, 0, 0);}
        break;
      case 4: /* cmd ::= SHOW MNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MNODE, 0, 0);}
        break;
      case 5: /* cmd ::= SHOW DNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DNODE, 0, 0);}
        break;
      case 6: /* cmd ::= SHOW ACCOUNTS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_ACCT, 0, 0);}
        break;
      case 7: /* cmd ::= SHOW USERS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_USER, 0, 0);}
        break;
      case 8: /* cmd ::= SHOW MODULES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MODULE, 0, 0);  }
        break;
      case 9: /* cmd ::= SHOW QUERIES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_QUERIES, 0, 0);  }
        break;
      case 10: /* cmd ::= SHOW CONNECTIONS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_CONNS, 0, 0);}
        break;
      case 11: /* cmd ::= SHOW STREAMS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_STREAMS, 0, 0);  }
        break;
      case 12: /* cmd ::= SHOW VARIABLES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VARIABLES, 0, 0);  }
        break;
      case 13: /* cmd ::= SHOW SCORES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_SCORES, 0, 0);   }
        break;
      case 14: /* cmd ::= SHOW GRANTS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_GRANTS, 0, 0);   }
        break;
      case 15: /* cmd ::= SHOW VNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, 0, 0); }
        break;
      case 16: /* cmd ::= SHOW VNODES ids */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, &yymsp[0].minor.yy0, 0); }
        break;
      case 17: /* dbPrefix ::= */
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.type = 0;}
        break;
      case 18: /* dbPrefix ::= ids DOT */
{yylhsminor.yy0 = yymsp[-1].minor.yy0;  }
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* cpxName ::= */
{yymsp[1].minor.yy0.n = 0;  }
        break;
      case 20: /* cpxName ::= DOT ids */
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; yymsp[-1].minor.yy0.n += 1;    }
        break;
      case 21: /* cmd ::= SHOW CREATE TABLE ids cpxName */
{
   yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
   setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_TABLE, 1, &yymsp[-1].minor.yy0);
}
        break;
      case 22: /* cmd ::= SHOW CREATE STABLE ids cpxName */
{
   yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
   setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_STABLE, 1, &yymsp[-1].minor.yy0);
}
        break;
      case 23: /* cmd ::= SHOW CREATE DATABASE ids */
{
  setDCLSqlElems(pInfo, TSDB_SQL_SHOW_CREATE_DATABASE, 1, &yymsp[0].minor.yy0);
}
        break;
      case 24: /* cmd ::= SHOW dbPrefix TABLES */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-1].minor.yy0, 0);
}
        break;
      case 25: /* cmd ::= SHOW dbPrefix TABLES LIKE STRING */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0);
}
        break;
      case 26: /* cmd ::= SHOW dbPrefix STABLES */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &yymsp[-1].minor.yy0, 0);
}
        break;
      case 27: /* cmd ::= SHOW dbPrefix STABLES LIKE STRING */
{
    SStrToken token;
    tSetDbName(&token, &yymsp[-3].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &token, &yymsp[0].minor.yy0);
}
        break;
      case 28: /* cmd ::= SHOW dbPrefix VGROUPS */
{
    SStrToken token;
    tSetDbName(&token, &yymsp[-1].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_VGROUP, &token, 0);
}
        break;
      case 29: /* cmd ::= DROP TABLE ifexists ids cpxName */
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDropDbTableInfo(pInfo, TSDB_SQL_DROP_TABLE, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0, -1, -1);
}
        break;
      case 30: /* cmd ::= DROP STABLE ifexists ids cpxName */
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDropDbTableInfo(pInfo, TSDB_SQL_DROP_TABLE, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0, -1, TSDB_SUPER_TABLE);
}
        break;
      case 31: /* cmd ::= DROP DATABASE ifexists ids */
{ setDropDbTableInfo(pInfo, TSDB_SQL_DROP_DB, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0, TSDB_DB_TYPE_DEFAULT, -1); }
        break;
      case 32: /* cmd ::= DROP TOPIC ifexists ids */
{ setDropDbTableInfo(pInfo, TSDB_SQL_DROP_DB, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0, TSDB_DB_TYPE_TOPIC, -1); }
        break;
      case 33: /* cmd ::= DROP FUNCTION ids */
{ setDropFuncInfo(pInfo, TSDB_SQL_DROP_FUNCTION, &yymsp[0].minor.yy0); }
        break;
      case 34: /* cmd ::= DROP DNODE ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_DNODE, 1, &yymsp[0].minor.yy0);    }
        break;
      case 35: /* cmd ::= DROP USER ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_USER, 1, &yymsp[0].minor.yy0);     }
        break;
      case 36: /* cmd ::= DROP ACCOUNT ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_DROP_ACCT, 1, &yymsp[0].minor.yy0);  }
        break;
      case 37: /* cmd ::= USE ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_USE_DB, 1, &yymsp[0].minor.yy0);}
        break;
      case 38: /* cmd ::= DESCRIBE ids cpxName */
      case 39: /* cmd ::= DESC ids cpxName */ yytestcase(yyruleno==39);
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDCLSqlElems(pInfo, TSDB_SQL_DESCRIBE_TABLE, 1, &yymsp[-1].minor.yy0);
}
        break;
      case 40: /* cmd ::= ALTER USER ids PASS ids */
{ setAlterUserSql(pInfo, TSDB_ALTER_USER_PASSWD, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, NULL);    }
        break;
      case 41: /* cmd ::= ALTER USER ids PRIVILEGE ids */
{ setAlterUserSql(pInfo, TSDB_ALTER_USER_PRIVILEGES, &yymsp[-2].minor.yy0, NULL, &yymsp[0].minor.yy0);}
        break;
      case 42: /* cmd ::= ALTER DNODE ids ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_DNODE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
        break;
      case 43: /* cmd ::= ALTER DNODE ids ids ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_DNODE, 3, &yymsp[-2].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);      }
        break;
      case 44: /* cmd ::= ALTER LOCAL ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_LOCAL, 1, &yymsp[0].minor.yy0);              }
        break;
      case 45: /* cmd ::= ALTER LOCAL ids ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_CFG_LOCAL, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
        break;
      case 46: /* cmd ::= ALTER DATABASE ids alter_db_optr */
      case 47: /* cmd ::= ALTER TOPIC ids alter_topic_optr */ yytestcase(yyruleno==47);
{ SStrToken t = {0};  setCreateDbInfo(pInfo, TSDB_SQL_ALTER_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy436, &t);}
        break;
      case 48: /* cmd ::= ALTER ACCOUNT ids acct_optr */
{ setCreateAcctSql(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-1].minor.yy0, NULL, &yymsp[0].minor.yy517);}
        break;
      case 49: /* cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
{ setCreateAcctSql(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy517);}
        break;
      case 50: /* cmd ::= COMPACT VNODES IN LP exprlist RP */
{ setCompactVnodeSql(pInfo, TSDB_SQL_COMPACT_VNODE, yymsp[-1].minor.yy525);}
        break;
      case 51: /* ids ::= ID */
      case 52: /* ids ::= STRING */ yytestcase(yyruleno==52);
{yylhsminor.yy0 = yymsp[0].minor.yy0; }
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 53: /* ifexists ::= IF EXISTS */
{ yymsp[-1].minor.yy0.n = 1;}
        break;
      case 54: /* ifexists ::= */
      case 56: /* ifnotexists ::= */ yytestcase(yyruleno==56);
      case 186: /* distinct ::= */ yytestcase(yyruleno==186);
{ yymsp[1].minor.yy0.n = 0;}
        break;
      case 55: /* ifnotexists ::= IF NOT EXISTS */
{ yymsp[-2].minor.yy0.n = 1;}
        break;
      case 57: /* cmd ::= CREATE DNODE ids */
{ setDCLSqlElems(pInfo, TSDB_SQL_CREATE_DNODE, 1, &yymsp[0].minor.yy0);}
        break;
      case 58: /* cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
{ setCreateAcctSql(pInfo, TSDB_SQL_CREATE_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy517);}
        break;
      case 59: /* cmd ::= CREATE DATABASE ifnotexists ids db_optr */
      case 60: /* cmd ::= CREATE TOPIC ifnotexists ids topic_optr */ yytestcase(yyruleno==60);
{ setCreateDbInfo(pInfo, TSDB_SQL_CREATE_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy436, &yymsp[-2].minor.yy0);}
        break;
      case 61: /* cmd ::= CREATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
{ setCreateFuncInfo(pInfo, TSDB_SQL_CREATE_FUNCTION, &yymsp[-5].minor.yy0, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy115, &yymsp[0].minor.yy0, 1);}
        break;
      case 62: /* cmd ::= CREATE AGGREGATE FUNCTION ids AS ids OUTPUTTYPE typename bufsize */
{ setCreateFuncInfo(pInfo, TSDB_SQL_CREATE_FUNCTION, &yymsp[-5].minor.yy0, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy115, &yymsp[0].minor.yy0, 2);}
        break;
      case 63: /* cmd ::= CREATE USER ids PASS ids */
{ setCreateUserSql(pInfo, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);}
        break;
      case 64: /* bufsize ::= */
      case 66: /* pps ::= */ yytestcase(yyruleno==66);
      case 68: /* tseries ::= */ yytestcase(yyruleno==68);
      case 70: /* dbs ::= */ yytestcase(yyruleno==70);
      case 72: /* streams ::= */ yytestcase(yyruleno==72);
      case 74: /* storage ::= */ yytestcase(yyruleno==74);
      case 76: /* qtime ::= */ yytestcase(yyruleno==76);
      case 78: /* users ::= */ yytestcase(yyruleno==78);
      case 80: /* conns ::= */ yytestcase(yyruleno==80);
      case 82: /* state ::= */ yytestcase(yyruleno==82);
{ yymsp[1].minor.yy0.n = 0;   }
        break;
      case 65: /* bufsize ::= BUFSIZE INTEGER */
      case 67: /* pps ::= PPS INTEGER */ yytestcase(yyruleno==67);
      case 69: /* tseries ::= TSERIES INTEGER */ yytestcase(yyruleno==69);
      case 71: /* dbs ::= DBS INTEGER */ yytestcase(yyruleno==71);
      case 73: /* streams ::= STREAMS INTEGER */ yytestcase(yyruleno==73);
      case 75: /* storage ::= STORAGE INTEGER */ yytestcase(yyruleno==75);
      case 77: /* qtime ::= QTIME INTEGER */ yytestcase(yyruleno==77);
      case 79: /* users ::= USERS INTEGER */ yytestcase(yyruleno==79);
      case 81: /* conns ::= CONNS INTEGER */ yytestcase(yyruleno==81);
      case 83: /* state ::= STATE ids */ yytestcase(yyruleno==83);
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;     }
        break;
      case 84: /* acct_optr ::= pps tseries storage streams qtime dbs users conns state */
{
    yylhsminor.yy517.maxUsers   = (yymsp[-2].minor.yy0.n>0)?atoi(yymsp[-2].minor.yy0.z):-1;
    yylhsminor.yy517.maxDbs     = (yymsp[-3].minor.yy0.n>0)?atoi(yymsp[-3].minor.yy0.z):-1;
    yylhsminor.yy517.maxTimeSeries = (yymsp[-7].minor.yy0.n>0)?atoi(yymsp[-7].minor.yy0.z):-1;
    yylhsminor.yy517.maxStreams = (yymsp[-5].minor.yy0.n>0)?atoi(yymsp[-5].minor.yy0.z):-1;
    yylhsminor.yy517.maxPointsPerSecond     = (yymsp[-8].minor.yy0.n>0)?atoi(yymsp[-8].minor.yy0.z):-1;
    yylhsminor.yy517.maxStorage = (yymsp[-6].minor.yy0.n>0)?strtoll(yymsp[-6].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy517.maxQueryTime   = (yymsp[-4].minor.yy0.n>0)?strtoll(yymsp[-4].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy517.maxConnections   = (yymsp[-1].minor.yy0.n>0)?atoi(yymsp[-1].minor.yy0.z):-1;
    yylhsminor.yy517.stat    = yymsp[0].minor.yy0;
}
  yymsp[-8].minor.yy517 = yylhsminor.yy517;
        break;
      case 85: /* intitemlist ::= intitemlist COMMA intitem */
      case 158: /* tagitemlist ::= tagitemlist COMMA tagitem */ yytestcase(yyruleno==158);
{ yylhsminor.yy525 = tVariantListAppend(yymsp[-2].minor.yy525, &yymsp[0].minor.yy110, -1);    }
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 86: /* intitemlist ::= intitem */
      case 159: /* tagitemlist ::= tagitem */ yytestcase(yyruleno==159);
{ yylhsminor.yy525 = tVariantListAppend(NULL, &yymsp[0].minor.yy110, -1); }
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 87: /* intitem ::= INTEGER */
      case 160: /* tagitem ::= INTEGER */ yytestcase(yyruleno==160);
      case 161: /* tagitem ::= FLOAT */ yytestcase(yyruleno==161);
      case 162: /* tagitem ::= STRING */ yytestcase(yyruleno==162);
      case 163: /* tagitem ::= BOOL */ yytestcase(yyruleno==163);
{ toTSDBType(yymsp[0].minor.yy0.type); tVariantCreate(&yylhsminor.yy110, &yymsp[0].minor.yy0); }
  yymsp[0].minor.yy110 = yylhsminor.yy110;
        break;
      case 88: /* keep ::= KEEP intitemlist */
{ yymsp[-1].minor.yy525 = yymsp[0].minor.yy525; }
        break;
      case 89: /* cache ::= CACHE INTEGER */
      case 90: /* replica ::= REPLICA INTEGER */ yytestcase(yyruleno==90);
      case 91: /* quorum ::= QUORUM INTEGER */ yytestcase(yyruleno==91);
      case 92: /* days ::= DAYS INTEGER */ yytestcase(yyruleno==92);
      case 93: /* minrows ::= MINROWS INTEGER */ yytestcase(yyruleno==93);
      case 94: /* maxrows ::= MAXROWS INTEGER */ yytestcase(yyruleno==94);
      case 95: /* blocks ::= BLOCKS INTEGER */ yytestcase(yyruleno==95);
      case 96: /* ctime ::= CTIME INTEGER */ yytestcase(yyruleno==96);
      case 97: /* wal ::= WAL INTEGER */ yytestcase(yyruleno==97);
      case 98: /* fsync ::= FSYNC INTEGER */ yytestcase(yyruleno==98);
      case 99: /* comp ::= COMP INTEGER */ yytestcase(yyruleno==99);
      case 100: /* prec ::= PRECISION STRING */ yytestcase(yyruleno==100);
      case 101: /* update ::= UPDATE INTEGER */ yytestcase(yyruleno==101);
      case 102: /* cachelast ::= CACHELAST INTEGER */ yytestcase(yyruleno==102);
      case 103: /* partitions ::= PARTITIONS INTEGER */ yytestcase(yyruleno==103);
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; }
        break;
      case 104: /* db_optr ::= */
{setDefaultCreateDbOption(&yymsp[1].minor.yy436); yymsp[1].minor.yy436.dbType = TSDB_DB_TYPE_DEFAULT;}
        break;
      case 105: /* db_optr ::= db_optr cache */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.cacheBlockSize = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 106: /* db_optr ::= db_optr replica */
      case 123: /* alter_db_optr ::= alter_db_optr replica */ yytestcase(yyruleno==123);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.replica = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 107: /* db_optr ::= db_optr quorum */
      case 124: /* alter_db_optr ::= alter_db_optr quorum */ yytestcase(yyruleno==124);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.quorum = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 108: /* db_optr ::= db_optr days */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.daysPerFile = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 109: /* db_optr ::= db_optr minrows */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.minRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 110: /* db_optr ::= db_optr maxrows */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.maxRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 111: /* db_optr ::= db_optr blocks */
      case 126: /* alter_db_optr ::= alter_db_optr blocks */ yytestcase(yyruleno==126);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.numOfBlocks = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 112: /* db_optr ::= db_optr ctime */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.commitTime = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 113: /* db_optr ::= db_optr wal */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.walLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 114: /* db_optr ::= db_optr fsync */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.fsyncPeriod = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 115: /* db_optr ::= db_optr comp */
      case 127: /* alter_db_optr ::= alter_db_optr comp */ yytestcase(yyruleno==127);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.compressionLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 116: /* db_optr ::= db_optr prec */
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.precision = yymsp[0].minor.yy0; }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 117: /* db_optr ::= db_optr keep */
      case 125: /* alter_db_optr ::= alter_db_optr keep */ yytestcase(yyruleno==125);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.keep = yymsp[0].minor.yy525; }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 118: /* db_optr ::= db_optr update */
      case 128: /* alter_db_optr ::= alter_db_optr update */ yytestcase(yyruleno==128);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.update = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 119: /* db_optr ::= db_optr cachelast */
      case 129: /* alter_db_optr ::= alter_db_optr cachelast */ yytestcase(yyruleno==129);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.cachelast = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 120: /* topic_optr ::= db_optr */
      case 130: /* alter_topic_optr ::= alter_db_optr */ yytestcase(yyruleno==130);
{ yylhsminor.yy436 = yymsp[0].minor.yy436; yylhsminor.yy436.dbType = TSDB_DB_TYPE_TOPIC; }
  yymsp[0].minor.yy436 = yylhsminor.yy436;
        break;
      case 121: /* topic_optr ::= topic_optr partitions */
      case 131: /* alter_topic_optr ::= alter_topic_optr partitions */ yytestcase(yyruleno==131);
{ yylhsminor.yy436 = yymsp[-1].minor.yy436; yylhsminor.yy436.partitions = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy436 = yylhsminor.yy436;
        break;
      case 122: /* alter_db_optr ::= */
{ setDefaultCreateDbOption(&yymsp[1].minor.yy436); yymsp[1].minor.yy436.dbType = TSDB_DB_TYPE_DEFAULT;}
        break;
      case 132: /* typename ::= ids */
{
  yymsp[0].minor.yy0.type = 0;
  tSetColumnType (&yylhsminor.yy115, &yymsp[0].minor.yy0);
}
  yymsp[0].minor.yy115 = yylhsminor.yy115;
        break;
      case 133: /* typename ::= ids LP signed RP */
{
  if (yymsp[-1].minor.yy543 <= 0) {
    yymsp[-3].minor.yy0.type = 0;
    tSetColumnType(&yylhsminor.yy115, &yymsp[-3].minor.yy0);
  } else {
    yymsp[-3].minor.yy0.type = -yymsp[-1].minor.yy543;  // negative value of name length
    tSetColumnType(&yylhsminor.yy115, &yymsp[-3].minor.yy0);
  }
}
  yymsp[-3].minor.yy115 = yylhsminor.yy115;
        break;
      case 134: /* typename ::= ids UNSIGNED */
{
  yymsp[-1].minor.yy0.type = 0;
  yymsp[-1].minor.yy0.n = ((yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z);
  tSetColumnType (&yylhsminor.yy115, &yymsp[-1].minor.yy0);
}
  yymsp[-1].minor.yy115 = yylhsminor.yy115;
        break;
      case 135: /* signed ::= INTEGER */
{ yylhsminor.yy543 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[0].minor.yy543 = yylhsminor.yy543;
        break;
      case 136: /* signed ::= PLUS INTEGER */
{ yymsp[-1].minor.yy543 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
        break;
      case 137: /* signed ::= MINUS INTEGER */
{ yymsp[-1].minor.yy543 = -strtol(yymsp[0].minor.yy0.z, NULL, 10);}
        break;
      case 141: /* cmd ::= CREATE TABLE create_table_list */
{ pInfo->type = TSDB_SQL_CREATE_TABLE; pInfo->pCreateTableInfo = yymsp[0].minor.yy572;}
        break;
      case 142: /* create_table_list ::= create_from_stable */
{
  SCreateTableSql* pCreateTable = calloc(1, sizeof(SCreateTableSql));
  pCreateTable->childTableInfo = taosArrayInit(4, sizeof(SCreatedTableInfo));

  taosArrayPush(pCreateTable->childTableInfo, &yymsp[0].minor.yy480);
  pCreateTable->type = TSQL_CREATE_TABLE_FROM_STABLE;
  yylhsminor.yy572 = pCreateTable;
}
  yymsp[0].minor.yy572 = yylhsminor.yy572;
        break;
      case 143: /* create_table_list ::= create_table_list create_from_stable */
{
  taosArrayPush(yymsp[-1].minor.yy572->childTableInfo, &yymsp[0].minor.yy480);
  yylhsminor.yy572 = yymsp[-1].minor.yy572;
}
  yymsp[-1].minor.yy572 = yylhsminor.yy572;
        break;
      case 144: /* create_table_args ::= ifnotexists ids cpxName LP columnlist RP */
{
  yylhsminor.yy572 = tSetCreateTableInfo(yymsp[-1].minor.yy525, NULL, NULL, TSQL_CREATE_TABLE);
  setSqlInfo(pInfo, yylhsminor.yy572, NULL, TSDB_SQL_CREATE_TABLE);

  yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-4].minor.yy0, &yymsp[-5].minor.yy0);
}
  yymsp[-5].minor.yy572 = yylhsminor.yy572;
        break;
      case 145: /* create_stable_args ::= ifnotexists ids cpxName LP columnlist RP TAGS LP columnlist RP */
{
  yylhsminor.yy572 = tSetCreateTableInfo(yymsp[-5].minor.yy525, yymsp[-1].minor.yy525, NULL, TSQL_CREATE_STABLE);
  setSqlInfo(pInfo, yylhsminor.yy572, NULL, TSDB_SQL_CREATE_TABLE);

  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-8].minor.yy0, &yymsp[-9].minor.yy0);
}
  yymsp[-9].minor.yy572 = yylhsminor.yy572;
        break;
      case 146: /* create_from_stable ::= ifnotexists ids cpxName USING ids cpxName TAGS LP tagitemlist RP */
{
  yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  yylhsminor.yy480 = createNewChildTableInfo(&yymsp[-5].minor.yy0, NULL, yymsp[-1].minor.yy525, &yymsp[-8].minor.yy0, &yymsp[-9].minor.yy0);
}
  yymsp[-9].minor.yy480 = yylhsminor.yy480;
        break;
      case 147: /* create_from_stable ::= ifnotexists ids cpxName USING ids cpxName LP tagNamelist RP TAGS LP tagitemlist RP */
{
  yymsp[-8].minor.yy0.n += yymsp[-7].minor.yy0.n;
  yymsp[-11].minor.yy0.n += yymsp[-10].minor.yy0.n;
  yylhsminor.yy480 = createNewChildTableInfo(&yymsp[-8].minor.yy0, yymsp[-5].minor.yy525, yymsp[-1].minor.yy525, &yymsp[-11].minor.yy0, &yymsp[-12].minor.yy0);
}
  yymsp[-12].minor.yy480 = yylhsminor.yy480;
        break;
      case 148: /* tagNamelist ::= tagNamelist COMMA ids */
{taosArrayPush(yymsp[-2].minor.yy525, &yymsp[0].minor.yy0); yylhsminor.yy525 = yymsp[-2].minor.yy525;  }
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 149: /* tagNamelist ::= ids */
{yylhsminor.yy525 = taosArrayInit(4, sizeof(SStrToken)); taosArrayPush(yylhsminor.yy525, &yymsp[0].minor.yy0);}
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 150: /* create_table_args ::= ifnotexists ids cpxName to_opt split_opt AS select */
{
  yylhsminor.yy572 = tSetCreateTableInfo(NULL, NULL, yymsp[0].minor.yy86, TSQL_CREATE_STREAM);
  setSqlInfo(pInfo, yylhsminor.yy572, NULL, TSDB_SQL_CREATE_TABLE);

  setCreatedStreamOpt(pInfo, &yymsp[-3].minor.yy0, &yymsp[-2].minor.yy0);
  yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
  setCreatedTableName(pInfo, &yymsp[-5].minor.yy0, &yymsp[-6].minor.yy0);
}
  yymsp[-6].minor.yy572 = yylhsminor.yy572;
        break;
      case 151: /* to_opt ::= */
      case 153: /* split_opt ::= */ yytestcase(yyruleno==153);
{yymsp[1].minor.yy0.n = 0;}
        break;
      case 152: /* to_opt ::= TO ids cpxName */
{
   yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
   yymsp[-2].minor.yy0.n += yymsp[0].minor.yy0.n;
}
        break;
      case 154: /* split_opt ::= SPLIT ids */
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;}
        break;
      case 155: /* columnlist ::= columnlist COMMA column */
{taosArrayPush(yymsp[-2].minor.yy525, &yymsp[0].minor.yy115); yylhsminor.yy525 = yymsp[-2].minor.yy525;  }
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 156: /* columnlist ::= column */
{yylhsminor.yy525 = taosArrayInit(4, sizeof(TAOS_FIELD)); taosArrayPush(yylhsminor.yy525, &yymsp[0].minor.yy115);}
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 157: /* column ::= ids typename */
{
  tSetColumnInfo(&yylhsminor.yy115, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy115);
}
  yymsp[-1].minor.yy115 = yylhsminor.yy115;
        break;
      case 164: /* tagitem ::= NULL */
{ yymsp[0].minor.yy0.type = 0; tVariantCreate(&yylhsminor.yy110, &yymsp[0].minor.yy0); }
  yymsp[0].minor.yy110 = yylhsminor.yy110;
        break;
      case 165: /* tagitem ::= NOW */
{ yymsp[0].minor.yy0.type = TSDB_DATA_TYPE_TIMESTAMP; tVariantCreateExt(&yylhsminor.yy110, &yymsp[0].minor.yy0, TK_NOW, true);}
  yymsp[0].minor.yy110 = yylhsminor.yy110;
        break;
      case 166: /* tagitem ::= NOW PLUS VARIABLE */
{
    yymsp[0].minor.yy0.type = TSDB_DATA_TYPE_TIMESTAMP;
    tVariantCreateExt(&yymsp[-2].minor.yy110, &yymsp[0].minor.yy0, TK_PLUS, true);
}
        break;
      case 167: /* tagitem ::= NOW MINUS VARIABLE */
{
    yymsp[0].minor.yy0.type = TSDB_DATA_TYPE_TIMESTAMP;
    tVariantCreateExt(&yymsp[-2].minor.yy110, &yymsp[0].minor.yy0, TK_MINUS, true);
}
        break;
      case 168: /* tagitem ::= MINUS INTEGER */
      case 169: /* tagitem ::= MINUS FLOAT */ yytestcase(yyruleno==169);
      case 170: /* tagitem ::= PLUS INTEGER */ yytestcase(yyruleno==170);
      case 171: /* tagitem ::= PLUS FLOAT */ yytestcase(yyruleno==171);
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    yymsp[-1].minor.yy0.type = yymsp[0].minor.yy0.type;
    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantCreate(&yylhsminor.yy110, &yymsp[-1].minor.yy0);
}
  yymsp[-1].minor.yy110 = yylhsminor.yy110;
        break;
      case 172: /* select ::= SELECT selcollist from where_opt range_option interval_option sliding_opt session_option windowstate_option fill_opt groupby_opt having_opt orderby_opt slimit_opt limit_opt */
{
  yylhsminor.yy86 = tSetQuerySqlNode(&yymsp[-14].minor.yy0, yymsp[-13].minor.yy525, yymsp[-12].minor.yy328, yymsp[-11].minor.yy142, yymsp[-4].minor.yy525, yymsp[-2].minor.yy525, &yymsp[-9].minor.yy238, &yymsp[-7].minor.yy319, &yymsp[-6].minor.yy546, &yymsp[-8].minor.yy0, yymsp[-5].minor.yy525, &yymsp[0].minor.yy6, &yymsp[-1].minor.yy6, yymsp[-3].minor.yy142, &yymsp[-10].minor.yy330);
}
  yymsp[-14].minor.yy86 = yylhsminor.yy86;
        break;
      case 173: /* select ::= LP select RP */
{yymsp[-2].minor.yy86 = yymsp[-1].minor.yy86;}
        break;
      case 174: /* union ::= select */
{ yylhsminor.yy525 = setSubclause(NULL, yymsp[0].minor.yy86); }
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 175: /* union ::= union UNION ALL select */
{ yylhsminor.yy525 = appendSelectClause(yymsp[-3].minor.yy525, yymsp[0].minor.yy86); }
  yymsp[-3].minor.yy525 = yylhsminor.yy525;
        break;
      case 176: /* cmd ::= union */
{ setSqlInfo(pInfo, yymsp[0].minor.yy525, NULL, TSDB_SQL_SELECT); }
        break;
      case 177: /* select ::= SELECT selcollist */
{
  yylhsminor.yy86 = tSetQuerySqlNode(&yymsp[-1].minor.yy0, yymsp[0].minor.yy525, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}
  yymsp[-1].minor.yy86 = yylhsminor.yy86;
        break;
      case 178: /* sclp ::= selcollist COMMA */
{yylhsminor.yy525 = yymsp[-1].minor.yy525;}
  yymsp[-1].minor.yy525 = yylhsminor.yy525;
        break;
      case 179: /* sclp ::= */
      case 220: /* orderby_opt ::= */ yytestcase(yyruleno==220);
{yymsp[1].minor.yy525 = 0;}
        break;
      case 180: /* selcollist ::= sclp distinct expr as */
{
   yylhsminor.yy525 = tSqlExprListAppend(yymsp[-3].minor.yy525, yymsp[-1].minor.yy142,  yymsp[-2].minor.yy0.n? &yymsp[-2].minor.yy0:0, yymsp[0].minor.yy0.n?&yymsp[0].minor.yy0:0);
}
  yymsp[-3].minor.yy525 = yylhsminor.yy525;
        break;
      case 181: /* selcollist ::= sclp STAR */
{
   tSqlExpr *pNode = tSqlExprCreateIdValue(pInfo, NULL, TK_ALL);
   yylhsminor.yy525 = tSqlExprListAppend(yymsp[-1].minor.yy525, pNode, 0, 0);
}
  yymsp[-1].minor.yy525 = yylhsminor.yy525;
        break;
      case 182: /* as ::= AS ids */
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;    }
        break;
      case 183: /* as ::= ids */
{ yylhsminor.yy0 = yymsp[0].minor.yy0;    }
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 184: /* as ::= */
{ yymsp[1].minor.yy0.n = 0;  }
        break;
      case 185: /* distinct ::= DISTINCT */
{ yylhsminor.yy0 = yymsp[0].minor.yy0;  }
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 187: /* from ::= FROM tablelist */
      case 188: /* from ::= FROM sub */ yytestcase(yyruleno==188);
{yymsp[-1].minor.yy328 = yymsp[0].minor.yy328;}
        break;
      case 189: /* sub ::= LP union RP */
{yymsp[-2].minor.yy328 = addSubqueryElem(NULL, yymsp[-1].minor.yy525, NULL);}
        break;
      case 190: /* sub ::= LP union RP ids */
{yymsp[-3].minor.yy328 = addSubqueryElem(NULL, yymsp[-2].minor.yy525, &yymsp[0].minor.yy0);}
        break;
      case 191: /* sub ::= sub COMMA LP union RP ids */
{yylhsminor.yy328 = addSubqueryElem(yymsp[-5].minor.yy328, yymsp[-2].minor.yy525, &yymsp[0].minor.yy0);}
  yymsp[-5].minor.yy328 = yylhsminor.yy328;
        break;
      case 192: /* tablelist ::= ids cpxName */
{
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy328 = setTableNameList(NULL, &yymsp[-1].minor.yy0, NULL);
}
  yymsp[-1].minor.yy328 = yylhsminor.yy328;
        break;
      case 193: /* tablelist ::= ids cpxName ids */
{
  yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
  yylhsminor.yy328 = setTableNameList(NULL, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);
}
  yymsp[-2].minor.yy328 = yylhsminor.yy328;
        break;
      case 194: /* tablelist ::= tablelist COMMA ids cpxName */
{
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy328 = setTableNameList(yymsp[-3].minor.yy328, &yymsp[-1].minor.yy0, NULL);
}
  yymsp[-3].minor.yy328 = yylhsminor.yy328;
        break;
      case 195: /* tablelist ::= tablelist COMMA ids cpxName ids */
{
  yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
  yylhsminor.yy328 = setTableNameList(yymsp[-4].minor.yy328, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);
}
  yymsp[-4].minor.yy328 = yylhsminor.yy328;
        break;
      case 196: /* tmvar ::= VARIABLE */
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 197: /* timestamp ::= INTEGER */
{ yylhsminor.yy142 = tSqlExprCreateTimestamp(&yymsp[0].minor.yy0, TK_INTEGER);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 198: /* timestamp ::= MINUS INTEGER */
      case 199: /* timestamp ::= PLUS INTEGER */ yytestcase(yyruleno==199);
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_INTEGER; yylhsminor.yy142 = tSqlExprCreateTimestamp(&yymsp[-1].minor.yy0, TK_INTEGER);}
  yymsp[-1].minor.yy142 = yylhsminor.yy142;
        break;
      case 200: /* timestamp ::= STRING */
{ yylhsminor.yy142 = tSqlExprCreateTimestamp(&yymsp[0].minor.yy0, TK_STRING);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 201: /* timestamp ::= NOW */
{ yylhsminor.yy142 = tSqlExprCreateTimestamp(&yymsp[0].minor.yy0, TK_NOW); }
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 202: /* timestamp ::= NOW PLUS VARIABLE */
{yymsp[-2].minor.yy142 = tSqlExprCreateTimestamp(&yymsp[0].minor.yy0, TK_PLUS);  }
        break;
      case 203: /* timestamp ::= NOW MINUS VARIABLE */
{yymsp[-2].minor.yy142 = tSqlExprCreateTimestamp(&yymsp[0].minor.yy0, TK_MINUS); }
        break;
      case 204: /* range_option ::= */
{yymsp[1].minor.yy330.start = 0; yymsp[1].minor.yy330.end = 0;}
        break;
      case 205: /* range_option ::= RANGE LP timestamp COMMA timestamp RP */
{yymsp[-5].minor.yy330.start = yymsp[-3].minor.yy142; yymsp[-5].minor.yy330.end = yymsp[-1].minor.yy142;}
        break;
      case 206: /* interval_option ::= intervalKey LP tmvar RP */
{yylhsminor.yy238.interval = yymsp[-1].minor.yy0; yylhsminor.yy238.offset.n = 0; yylhsminor.yy238.token = yymsp[-3].minor.yy508;}
  yymsp[-3].minor.yy238 = yylhsminor.yy238;
        break;
      case 207: /* interval_option ::= intervalKey LP tmvar COMMA tmvar RP */
{yylhsminor.yy238.interval = yymsp[-3].minor.yy0; yylhsminor.yy238.offset = yymsp[-1].minor.yy0;   yylhsminor.yy238.token = yymsp[-5].minor.yy508;}
  yymsp[-5].minor.yy238 = yylhsminor.yy238;
        break;
      case 208: /* interval_option ::= */
{memset(&yymsp[1].minor.yy238, 0, sizeof(yymsp[1].minor.yy238));}
        break;
      case 209: /* intervalKey ::= INTERVAL */
{yymsp[0].minor.yy508 = TK_INTERVAL;}
        break;
      case 210: /* intervalKey ::= EVERY */
{yymsp[0].minor.yy508 = TK_EVERY;   }
        break;
      case 211: /* session_option ::= */
{yymsp[1].minor.yy319.col.n = 0; yymsp[1].minor.yy319.gap.n = 0;}
        break;
      case 212: /* session_option ::= SESSION LP ids cpxName COMMA tmvar RP */
{
   yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
   yymsp[-6].minor.yy319.col = yymsp[-4].minor.yy0;
   yymsp[-6].minor.yy319.gap = yymsp[-1].minor.yy0;
}
        break;
      case 213: /* windowstate_option ::= */
{ yymsp[1].minor.yy546.col.n = 0; yymsp[1].minor.yy546.col.z = NULL;}
        break;
      case 214: /* windowstate_option ::= STATE_WINDOW LP ids RP */
{ yymsp[-3].minor.yy546.col = yymsp[-1].minor.yy0; }
        break;
      case 215: /* fill_opt ::= */
{ yymsp[1].minor.yy525 = 0;     }
        break;
      case 216: /* fill_opt ::= FILL LP ID COMMA tagitemlist RP */
{
    tVariant A = {0};
    toTSDBType(yymsp[-3].minor.yy0.type);
    tVariantCreate(&A, &yymsp[-3].minor.yy0);

    tVariantListInsert(yymsp[-1].minor.yy525, &A, -1, 0);
    yymsp[-5].minor.yy525 = yymsp[-1].minor.yy525;
}
        break;
      case 217: /* fill_opt ::= FILL LP ID RP */
{
    toTSDBType(yymsp[-1].minor.yy0.type);
    yymsp[-3].minor.yy525 = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1, true);
}
        break;
      case 218: /* sliding_opt ::= SLIDING LP tmvar RP */
{yymsp[-3].minor.yy0 = yymsp[-1].minor.yy0;     }
        break;
      case 219: /* sliding_opt ::= */
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.z = NULL; yymsp[1].minor.yy0.type = 0;   }
        break;
      case 221: /* orderby_opt ::= ORDER BY sortlist */
{yymsp[-2].minor.yy525 = yymsp[0].minor.yy525;}
        break;
      case 222: /* sortlist ::= sortlist COMMA item sortorder */
{
  yylhsminor.yy525 = commonItemAppend(yymsp[-3].minor.yy525, &yymsp[-1].minor.yy110, NULL, false, yymsp[0].minor.yy580);
}
  yymsp[-3].minor.yy525 = yylhsminor.yy525;
        break;
      case 223: /* sortlist ::= sortlist COMMA arrow sortorder */
{
  yylhsminor.yy525 = commonItemAppend(yymsp[-3].minor.yy525, NULL, yymsp[-1].minor.yy142, true, yymsp[0].minor.yy580);
}
  yymsp[-3].minor.yy525 = yylhsminor.yy525;
        break;
      case 224: /* sortlist ::= item sortorder */
{
  yylhsminor.yy525 = commonItemAppend(NULL, &yymsp[-1].minor.yy110, NULL, false, yymsp[0].minor.yy580);
}
  yymsp[-1].minor.yy525 = yylhsminor.yy525;
        break;
      case 225: /* sortlist ::= arrow sortorder */
{
  yylhsminor.yy525 = commonItemAppend(NULL, NULL, yymsp[-1].minor.yy142, true, yymsp[0].minor.yy580);
}
  yymsp[-1].minor.yy525 = yylhsminor.yy525;
        break;
      case 226: /* item ::= ID */
{
  toTSDBType(yymsp[0].minor.yy0.type);
  tVariantCreate(&yylhsminor.yy110, &yymsp[0].minor.yy0);
}
  yymsp[0].minor.yy110 = yylhsminor.yy110;
        break;
      case 227: /* item ::= ID DOT ID */
{
  toTSDBType(yymsp[-2].minor.yy0.type);
  yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n);
  tVariantCreate(&yylhsminor.yy110, &yymsp[-2].minor.yy0);
}
  yymsp[-2].minor.yy110 = yylhsminor.yy110;
        break;
      case 228: /* sortorder ::= ASC */
{ yymsp[0].minor.yy580 = TSDB_ORDER_ASC; }
        break;
      case 229: /* sortorder ::= DESC */
{ yymsp[0].minor.yy580 = TSDB_ORDER_DESC;}
        break;
      case 230: /* sortorder ::= */
{ yymsp[1].minor.yy580 = TSDB_ORDER_ASC; }
        break;
      case 231: /* groupby_opt ::= */
{ yymsp[1].minor.yy525 = 0;}
        break;
      case 232: /* groupby_opt ::= GROUP BY grouplist */
{ yymsp[-2].minor.yy525 = yymsp[0].minor.yy525;}
        break;
      case 233: /* grouplist ::= grouplist COMMA item */
{
  yylhsminor.yy525 = commonItemAppend(yymsp[-2].minor.yy525, &yymsp[0].minor.yy110, NULL, false, -1);
}
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 234: /* grouplist ::= grouplist COMMA arrow */
{
  yylhsminor.yy525 = commonItemAppend(yymsp[-2].minor.yy525, NULL, yymsp[0].minor.yy142, true, -1);
}
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 235: /* grouplist ::= item */
{
  yylhsminor.yy525 = commonItemAppend(NULL, &yymsp[0].minor.yy110, NULL, false, -1);
}
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 236: /* grouplist ::= arrow */
{
  yylhsminor.yy525 = commonItemAppend(NULL, NULL, yymsp[0].minor.yy142, true, -1);
}
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 237: /* having_opt ::= */
      case 247: /* where_opt ::= */ yytestcase(yyruleno==247);
      case 298: /* expritem ::= */ yytestcase(yyruleno==298);
{yymsp[1].minor.yy142 = 0;}
        break;
      case 238: /* having_opt ::= HAVING expr */
      case 248: /* where_opt ::= WHERE expr */ yytestcase(yyruleno==248);
{yymsp[-1].minor.yy142 = yymsp[0].minor.yy142;}
        break;
      case 239: /* limit_opt ::= */
      case 243: /* slimit_opt ::= */ yytestcase(yyruleno==243);
{yymsp[1].minor.yy6.limit = -1; yymsp[1].minor.yy6.offset = 0;}
        break;
      case 240: /* limit_opt ::= LIMIT signed */
      case 244: /* slimit_opt ::= SLIMIT signed */ yytestcase(yyruleno==244);
{yymsp[-1].minor.yy6.limit = yymsp[0].minor.yy543;  yymsp[-1].minor.yy6.offset = 0;}
        break;
      case 241: /* limit_opt ::= LIMIT signed OFFSET signed */
{ yymsp[-3].minor.yy6.limit = yymsp[-2].minor.yy543;  yymsp[-3].minor.yy6.offset = yymsp[0].minor.yy543;}
        break;
      case 242: /* limit_opt ::= LIMIT signed COMMA signed */
{ yymsp[-3].minor.yy6.limit = yymsp[0].minor.yy543;  yymsp[-3].minor.yy6.offset = yymsp[-2].minor.yy543;}
        break;
      case 245: /* slimit_opt ::= SLIMIT signed SOFFSET signed */
{yymsp[-3].minor.yy6.limit = yymsp[-2].minor.yy543;  yymsp[-3].minor.yy6.offset = yymsp[0].minor.yy543;}
        break;
      case 246: /* slimit_opt ::= SLIMIT signed COMMA signed */
{yymsp[-3].minor.yy6.limit = yymsp[0].minor.yy543;  yymsp[-3].minor.yy6.offset = yymsp[-2].minor.yy543;}
        break;
      case 249: /* expr ::= LP expr RP */
{yylhsminor.yy142 = yymsp[-1].minor.yy142; yylhsminor.yy142->exprToken.z = yymsp[-2].minor.yy0.z; yylhsminor.yy142->exprToken.n = (yymsp[0].minor.yy0.z - yymsp[-2].minor.yy0.z + 1);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 250: /* expr ::= ID */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_ID);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 251: /* expr ::= ID DOT ID */
{ yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[-2].minor.yy0, TK_ID);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 252: /* expr ::= ID DOT STAR */
{ yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[-2].minor.yy0, TK_ALL);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 253: /* expr ::= INTEGER */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_INTEGER);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 254: /* expr ::= MINUS INTEGER */
      case 255: /* expr ::= PLUS INTEGER */ yytestcase(yyruleno==255);
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_INTEGER; yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[-1].minor.yy0, TK_INTEGER);}
  yymsp[-1].minor.yy142 = yylhsminor.yy142;
        break;
      case 256: /* expr ::= FLOAT */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_FLOAT);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 257: /* expr ::= MINUS FLOAT */
      case 258: /* expr ::= PLUS FLOAT */ yytestcase(yyruleno==258);
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_FLOAT; yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[-1].minor.yy0, TK_FLOAT);}
  yymsp[-1].minor.yy142 = yylhsminor.yy142;
        break;
      case 259: /* expr ::= STRING */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_STRING);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 260: /* expr ::= NOW */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_NOW); }
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 261: /* expr ::= TODAY */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_TODAY); }
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 262: /* expr ::= VARIABLE */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_VARIABLE);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 263: /* expr ::= PLUS VARIABLE */
      case 264: /* expr ::= MINUS VARIABLE */ yytestcase(yyruleno==264);
{ yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_VARIABLE; yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[-1].minor.yy0, TK_VARIABLE);}
  yymsp[-1].minor.yy142 = yylhsminor.yy142;
        break;
      case 265: /* expr ::= BOOL */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_BOOL);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 266: /* expr ::= NULL */
{ yylhsminor.yy142 = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_NULL);}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 267: /* expr ::= ID LP exprlist RP */
{ tStrTokenAppend(pInfo->funcs, &yymsp[-3].minor.yy0); yylhsminor.yy142 = tSqlExprCreateFunction(yymsp[-1].minor.yy525, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type); }
  yymsp[-3].minor.yy142 = yylhsminor.yy142;
        break;
      case 268: /* expr ::= ID LP STAR RP */
{ tStrTokenAppend(pInfo->funcs, &yymsp[-3].minor.yy0); yylhsminor.yy142 = tSqlExprCreateFunction(NULL, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type); }
  yymsp[-3].minor.yy142 = yylhsminor.yy142;
        break;
      case 269: /* expr ::= ID LP expr AS typename RP */
{ tStrTokenAppend(pInfo->funcs, &yymsp[-5].minor.yy0); yylhsminor.yy142 = tSqlExprCreateFuncWithParams(pInfo, yymsp[-3].minor.yy142, &yymsp[-1].minor.yy115, &yymsp[-5].minor.yy0, &yymsp[0].minor.yy0, yymsp[-5].minor.yy0.type); }
  yymsp[-5].minor.yy142 = yylhsminor.yy142;
        break;
      case 270: /* expr ::= expr IS NULL */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, NULL, TK_ISNULL);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 271: /* expr ::= expr IS NOT NULL */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-3].minor.yy142, NULL, TK_NOTNULL);}
  yymsp[-3].minor.yy142 = yylhsminor.yy142;
        break;
      case 272: /* expr ::= expr LT expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_LT);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 273: /* expr ::= expr GT expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_GT);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 274: /* expr ::= expr LE expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_LE);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 275: /* expr ::= expr GE expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_GE);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 276: /* expr ::= expr NE expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_NE);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 277: /* expr ::= expr EQ expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_EQ);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 278: /* expr ::= expr BETWEEN expr AND expr */
{ tSqlExpr* X2 = tSqlExprClone(yymsp[-4].minor.yy142); yylhsminor.yy142 = tSqlExprCreate(tSqlExprCreate(yymsp[-4].minor.yy142, yymsp[-2].minor.yy142, TK_GE), tSqlExprCreate(X2, yymsp[0].minor.yy142, TK_LE), TK_AND);}
  yymsp[-4].minor.yy142 = yylhsminor.yy142;
        break;
      case 279: /* expr ::= expr AND expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_AND);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 280: /* expr ::= expr OR expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_OR); }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 281: /* expr ::= expr PLUS expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_PLUS);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 282: /* expr ::= expr MINUS expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_MINUS); }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 283: /* expr ::= expr STAR expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_STAR);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 284: /* expr ::= expr SLASH expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_DIVIDE);}
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 285: /* expr ::= expr REM expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_REM);   }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 286: /* expr ::= expr LIKE expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_LIKE);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 287: /* expr ::= expr MATCH expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_MATCH);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 288: /* expr ::= expr NMATCH expr */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-2].minor.yy142, yymsp[0].minor.yy142, TK_NMATCH);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 289: /* expr ::= ID CONTAINS STRING */
{ tSqlExpr* S = tSqlExprCreateIdValue(pInfo, &yymsp[-2].minor.yy0, TK_ID); tSqlExpr* M = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_STRING); yylhsminor.yy142 = tSqlExprCreate(S, M, TK_CONTAINS);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 290: /* expr ::= ID DOT ID CONTAINS STRING */
{ yymsp[-4].minor.yy0.n += (1+yymsp[-2].minor.yy0.n); tSqlExpr* S = tSqlExprCreateIdValue(pInfo, &yymsp[-4].minor.yy0, TK_ID); tSqlExpr* M = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_STRING); yylhsminor.yy142 = tSqlExprCreate(S, M, TK_CONTAINS);  }
  yymsp[-4].minor.yy142 = yylhsminor.yy142;
        break;
      case 291: /* arrow ::= ID ARROW STRING */
{tSqlExpr* S = tSqlExprCreateIdValue(pInfo, &yymsp[-2].minor.yy0, TK_ID); tSqlExpr* M = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_STRING); yylhsminor.yy142 = tSqlExprCreate(S, M, TK_ARROW);  }
  yymsp[-2].minor.yy142 = yylhsminor.yy142;
        break;
      case 292: /* arrow ::= ID DOT ID ARROW STRING */
{yymsp[-4].minor.yy0.n += (1+yymsp[-2].minor.yy0.n); tSqlExpr* S = tSqlExprCreateIdValue(pInfo, &yymsp[-4].minor.yy0, TK_ID); tSqlExpr* M = tSqlExprCreateIdValue(pInfo, &yymsp[0].minor.yy0, TK_STRING); yylhsminor.yy142 = tSqlExprCreate(S, M, TK_ARROW);  }
  yymsp[-4].minor.yy142 = yylhsminor.yy142;
        break;
      case 293: /* expr ::= arrow */
      case 297: /* expritem ::= expr */ yytestcase(yyruleno==297);
{yylhsminor.yy142 = yymsp[0].minor.yy142;}
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 294: /* expr ::= expr IN LP exprlist RP */
{yylhsminor.yy142 = tSqlExprCreate(yymsp[-4].minor.yy142, (tSqlExpr*)yymsp[-1].minor.yy525, TK_IN); }
  yymsp[-4].minor.yy142 = yylhsminor.yy142;
        break;
      case 295: /* exprlist ::= exprlist COMMA expritem */
{yylhsminor.yy525 = tSqlExprListAppend(yymsp[-2].minor.yy525,yymsp[0].minor.yy142,0, 0);}
  yymsp[-2].minor.yy525 = yylhsminor.yy525;
        break;
      case 296: /* exprlist ::= expritem */
{yylhsminor.yy525 = tSqlExprListAppend(0,yymsp[0].minor.yy142,0, 0);}
  yymsp[0].minor.yy525 = yylhsminor.yy525;
        break;
      case 299: /* cmd ::= RESET QUERY CACHE */
{ setDCLSqlElems(pInfo, TSDB_SQL_RESET_CACHE, 0);}
        break;
      case 300: /* cmd ::= SYNCDB ids REPLICA */
{ setDCLSqlElems(pInfo, TSDB_SQL_SYNC_DB_REPLICA, 1, &yymsp[-1].minor.yy0);}
        break;
      case 301: /* cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_ADD_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 302: /* cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, K, TSDB_ALTER_TABLE_DROP_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 303: /* cmd ::= ALTER TABLE ids cpxName MODIFY COLUMN columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_CHANGE_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 304: /* cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_ADD_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 305: /* cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, A, TSDB_ALTER_TABLE_DROP_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 306: /* cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1, false);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-5].minor.yy0, NULL, A, TSDB_ALTER_TABLE_CHANGE_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 307: /* cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1, false);
    A = tVariantListAppend(A, &yymsp[0].minor.yy110, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-6].minor.yy0, NULL, A, TSDB_ALTER_TABLE_UPDATE_TAG_VAL, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 308: /* cmd ::= ALTER TABLE ids cpxName MODIFY TAG columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_MODIFY_TAG_COLUMN, -1);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 309: /* cmd ::= ALTER STABLE ids cpxName ADD COLUMN columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_ADD_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 310: /* cmd ::= ALTER STABLE ids cpxName DROP COLUMN ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, K, TSDB_ALTER_TABLE_DROP_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 311: /* cmd ::= ALTER STABLE ids cpxName MODIFY COLUMN columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_CHANGE_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 312: /* cmd ::= ALTER STABLE ids cpxName ADD TAG columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_ADD_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 313: /* cmd ::= ALTER STABLE ids cpxName DROP TAG ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, NULL, A, TSDB_ALTER_TABLE_DROP_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 314: /* cmd ::= ALTER STABLE ids cpxName CHANGE TAG ids ids */
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1, false);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1, false);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-5].minor.yy0, NULL, A, TSDB_ALTER_TABLE_CHANGE_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 315: /* cmd ::= ALTER STABLE ids cpxName SET TAG ids EQ tagitem */
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    SArray* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1, false);
    A = tVariantListAppend(A, &yymsp[0].minor.yy110, -1);

    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-6].minor.yy0, NULL, A, TSDB_ALTER_TABLE_UPDATE_TAG_VAL, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 316: /* cmd ::= ALTER STABLE ids cpxName MODIFY TAG columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableInfo* pAlterTable = tSetAlterTableInfo(&yymsp[-4].minor.yy0, yymsp[0].minor.yy525, NULL, TSDB_ALTER_TABLE_MODIFY_TAG_COLUMN, TSDB_SUPER_TABLE);
    setSqlInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 317: /* cmd ::= KILL CONNECTION INTEGER */
{setKillSql(pInfo, TSDB_SQL_KILL_CONNECTION, &yymsp[0].minor.yy0);}
        break;
      case 318: /* cmd ::= KILL STREAM INTEGER COLON INTEGER */
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSql(pInfo, TSDB_SQL_KILL_STREAM, &yymsp[-2].minor.yy0);}
        break;
      case 319: /* cmd ::= KILL QUERY INTEGER COLON INTEGER */
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSql(pInfo, TSDB_SQL_KILL_QUERY, &yymsp[-2].minor.yy0);}
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/

  pInfo->valid = false;
  int32_t outputBufLen = tListLen(pInfo->msg);
  int32_t len = 0;

  if(TOKEN.z) {
    char msg[] = "syntax error near \"%s\"";
    int32_t sqlLen = strlen(&TOKEN.z[0]);

    if (sqlLen + sizeof(msg)/sizeof(msg[0]) + 1 > outputBufLen) {
        char tmpstr[128] = {0};
        memcpy(tmpstr, &TOKEN.z[0], sizeof(tmpstr)/sizeof(tmpstr[0]) - 1);
        len = sprintf(pInfo->msg, msg, tmpstr);
    } else {
        len = sprintf(pInfo->msg, msg, &TOKEN.z[0]);
    }

  } else {
    len = sprintf(pInfo->msg, "Incomplete SQL statement");
  }

  assert(len <= outputBufLen);
/************ End %syntax_error code ******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/

/*********** End %parse_accept code *******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    int stateno = yypParser->yytos->stateno;
    if( stateno < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],stateno);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],stateno-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact >= YY_MIN_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,yyminor);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
