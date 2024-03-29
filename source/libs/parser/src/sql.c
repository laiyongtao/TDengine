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
#include <assert.h>
/************ Begin %include sections from the grammar ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define ALLOW_FORBID_FUNC

#include "functionMgt.h"
#include "nodes.h"
#include "parToken.h"
#include "ttokendef.h"
#include "parAst.h"

#define YYSTACKDEPTH 0
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols.
***************** Begin token definitions *************************************/
#ifndef TK_OR
#define TK_OR                              1
#define TK_AND                             2
#define TK_UNION                           3
#define TK_ALL                             4
#define TK_MINUS                           5
#define TK_EXCEPT                          6
#define TK_INTERSECT                       7
#define TK_NK_BITAND                       8
#define TK_NK_BITOR                        9
#define TK_NK_LSHIFT                      10
#define TK_NK_RSHIFT                      11
#define TK_NK_PLUS                        12
#define TK_NK_MINUS                       13
#define TK_NK_STAR                        14
#define TK_NK_SLASH                       15
#define TK_NK_REM                         16
#define TK_NK_CONCAT                      17
#define TK_CREATE                         18
#define TK_ACCOUNT                        19
#define TK_NK_ID                          20
#define TK_PASS                           21
#define TK_NK_STRING                      22
#define TK_ALTER                          23
#define TK_PPS                            24
#define TK_TSERIES                        25
#define TK_STORAGE                        26
#define TK_STREAMS                        27
#define TK_QTIME                          28
#define TK_DBS                            29
#define TK_USERS                          30
#define TK_CONNS                          31
#define TK_STATE                          32
#define TK_NK_COMMA                       33
#define TK_HOST                           34
#define TK_USER                           35
#define TK_ENABLE                         36
#define TK_NK_INTEGER                     37
#define TK_SYSINFO                        38
#define TK_ADD                            39
#define TK_DROP                           40
#define TK_GRANT                          41
#define TK_ON                             42
#define TK_TO                             43
#define TK_REVOKE                         44
#define TK_FROM                           45
#define TK_SUBSCRIBE                      46
#define TK_READ                           47
#define TK_WRITE                          48
#define TK_NK_DOT                         49
#define TK_WITH                           50
#define TK_DNODE                          51
#define TK_PORT                           52
#define TK_DNODES                         53
#define TK_RESTORE                        54
#define TK_NK_IPTOKEN                     55
#define TK_FORCE                          56
#define TK_UNSAFE                         57
#define TK_CLUSTER                        58
#define TK_LOCAL                          59
#define TK_QNODE                          60
#define TK_BNODE                          61
#define TK_SNODE                          62
#define TK_MNODE                          63
#define TK_VNODE                          64
#define TK_DATABASE                       65
#define TK_USE                            66
#define TK_FLUSH                          67
#define TK_TRIM                           68
#define TK_COMPACT                        69
#define TK_IF                             70
#define TK_NOT                            71
#define TK_EXISTS                         72
#define TK_BUFFER                         73
#define TK_CACHEMODEL                     74
#define TK_CACHESIZE                      75
#define TK_COMP                           76
#define TK_DURATION                       77
#define TK_NK_VARIABLE                    78
#define TK_MAXROWS                        79
#define TK_MINROWS                        80
#define TK_KEEP                           81
#define TK_PAGES                          82
#define TK_PAGESIZE                       83
#define TK_TSDB_PAGESIZE                  84
#define TK_PRECISION                      85
#define TK_REPLICA                        86
#define TK_VGROUPS                        87
#define TK_SINGLE_STABLE                  88
#define TK_RETENTIONS                     89
#define TK_SCHEMALESS                     90
#define TK_WAL_LEVEL                      91
#define TK_WAL_FSYNC_PERIOD               92
#define TK_WAL_RETENTION_PERIOD           93
#define TK_WAL_RETENTION_SIZE             94
#define TK_WAL_ROLL_PERIOD                95
#define TK_WAL_SEGMENT_SIZE               96
#define TK_STT_TRIGGER                    97
#define TK_TABLE_PREFIX                   98
#define TK_TABLE_SUFFIX                   99
#define TK_KEEP_TIME_OFFSET               100
#define TK_NK_COLON                       101
#define TK_BWLIMIT                        102
#define TK_START                          103
#define TK_TIMESTAMP                      104
#define TK_END                            105
#define TK_TABLE                          106
#define TK_NK_LP                          107
#define TK_NK_RP                          108
#define TK_STABLE                         109
#define TK_COLUMN                         110
#define TK_MODIFY                         111
#define TK_RENAME                         112
#define TK_TAG                            113
#define TK_SET                            114
#define TK_NK_EQ                          115
#define TK_USING                          116
#define TK_TAGS                           117
#define TK_PRIMARY                        118
#define TK_KEY                            119
#define TK_BOOL                           120
#define TK_TINYINT                        121
#define TK_SMALLINT                       122
#define TK_INT                            123
#define TK_INTEGER                        124
#define TK_BIGINT                         125
#define TK_FLOAT                          126
#define TK_DOUBLE                         127
#define TK_BINARY                         128
#define TK_NCHAR                          129
#define TK_UNSIGNED                       130
#define TK_JSON                           131
#define TK_VARCHAR                        132
#define TK_MEDIUMBLOB                     133
#define TK_BLOB                           134
#define TK_VARBINARY                      135
#define TK_GEOMETRY                       136
#define TK_DECIMAL                        137
#define TK_COMMENT                        138
#define TK_MAX_DELAY                      139
#define TK_WATERMARK                      140
#define TK_ROLLUP                         141
#define TK_TTL                            142
#define TK_SMA                            143
#define TK_DELETE_MARK                    144
#define TK_FIRST                          145
#define TK_LAST                           146
#define TK_SHOW                           147
#define TK_PRIVILEGES                     148
#define TK_DATABASES                      149
#define TK_TABLES                         150
#define TK_STABLES                        151
#define TK_MNODES                         152
#define TK_QNODES                         153
#define TK_FUNCTIONS                      154
#define TK_INDEXES                        155
#define TK_ACCOUNTS                       156
#define TK_APPS                           157
#define TK_CONNECTIONS                    158
#define TK_LICENCES                       159
#define TK_GRANTS                         160
#define TK_FULL                           161
#define TK_LOGS                           162
#define TK_MACHINES                       163
#define TK_QUERIES                        164
#define TK_SCORES                         165
#define TK_TOPICS                         166
#define TK_VARIABLES                      167
#define TK_BNODES                         168
#define TK_SNODES                         169
#define TK_TRANSACTIONS                   170
#define TK_DISTRIBUTED                    171
#define TK_CONSUMERS                      172
#define TK_SUBSCRIPTIONS                  173
#define TK_VNODES                         174
#define TK_ALIVE                          175
#define TK_VIEWS                          176
#define TK_VIEW                           177
#define TK_COMPACTS                       178
#define TK_NORMAL                         179
#define TK_CHILD                          180
#define TK_LIKE                           181
#define TK_TBNAME                         182
#define TK_QTAGS                          183
#define TK_AS                             184
#define TK_SYSTEM                         185
#define TK_INDEX                          186
#define TK_FUNCTION                       187
#define TK_INTERVAL                       188
#define TK_COUNT                          189
#define TK_LAST_ROW                       190
#define TK_META                           191
#define TK_ONLY                           192
#define TK_TOPIC                          193
#define TK_CONSUMER                       194
#define TK_GROUP                          195
#define TK_DESC                           196
#define TK_DESCRIBE                       197
#define TK_RESET                          198
#define TK_QUERY                          199
#define TK_CACHE                          200
#define TK_EXPLAIN                        201
#define TK_ANALYZE                        202
#define TK_VERBOSE                        203
#define TK_NK_BOOL                        204
#define TK_RATIO                          205
#define TK_NK_FLOAT                       206
#define TK_OUTPUTTYPE                     207
#define TK_AGGREGATE                      208
#define TK_BUFSIZE                        209
#define TK_LANGUAGE                       210
#define TK_REPLACE                        211
#define TK_STREAM                         212
#define TK_INTO                           213
#define TK_PAUSE                          214
#define TK_RESUME                         215
#define TK_TRIGGER                        216
#define TK_AT_ONCE                        217
#define TK_WINDOW_CLOSE                   218
#define TK_IGNORE                         219
#define TK_EXPIRED                        220
#define TK_FILL_HISTORY                   221
#define TK_UPDATE                         222
#define TK_SUBTABLE                       223
#define TK_UNTREATED                      224
#define TK_KILL                           225
#define TK_CONNECTION                     226
#define TK_TRANSACTION                    227
#define TK_BALANCE                        228
#define TK_VGROUP                         229
#define TK_LEADER                         230
#define TK_MERGE                          231
#define TK_REDISTRIBUTE                   232
#define TK_SPLIT                          233
#define TK_DELETE                         234
#define TK_INSERT                         235
#define TK_NULL                           236
#define TK_NK_QUESTION                    237
#define TK_NK_ALIAS                       238
#define TK_NK_ARROW                       239
#define TK_ROWTS                          240
#define TK_QSTART                         241
#define TK_QEND                           242
#define TK_QDURATION                      243
#define TK_WSTART                         244
#define TK_WEND                           245
#define TK_WDURATION                      246
#define TK_IROWTS                         247
#define TK_ISFILLED                       248
#define TK_CAST                           249
#define TK_NOW                            250
#define TK_TODAY                          251
#define TK_TIMEZONE                       252
#define TK_CLIENT_VERSION                 253
#define TK_SERVER_VERSION                 254
#define TK_SERVER_STATUS                  255
#define TK_CURRENT_USER                   256
#define TK_CASE                           257
#define TK_WHEN                           258
#define TK_THEN                           259
#define TK_ELSE                           260
#define TK_BETWEEN                        261
#define TK_IS                             262
#define TK_NK_LT                          263
#define TK_NK_GT                          264
#define TK_NK_LE                          265
#define TK_NK_GE                          266
#define TK_NK_NE                          267
#define TK_MATCH                          268
#define TK_NMATCH                         269
#define TK_CONTAINS                       270
#define TK_IN                             271
#define TK_JOIN                           272
#define TK_INNER                          273
#define TK_SELECT                         274
#define TK_NK_HINT                        275
#define TK_DISTINCT                       276
#define TK_WHERE                          277
#define TK_PARTITION                      278
#define TK_BY                             279
#define TK_SESSION                        280
#define TK_STATE_WINDOW                   281
#define TK_EVENT_WINDOW                   282
#define TK_COUNT_WINDOW                   283
#define TK_SLIDING                        284
#define TK_FILL                           285
#define TK_VALUE                          286
#define TK_VALUE_F                        287
#define TK_NONE                           288
#define TK_PREV                           289
#define TK_NULL_F                         290
#define TK_LINEAR                         291
#define TK_NEXT                           292
#define TK_HAVING                         293
#define TK_RANGE                          294
#define TK_EVERY                          295
#define TK_ORDER                          296
#define TK_SLIMIT                         297
#define TK_SOFFSET                        298
#define TK_LIMIT                          299
#define TK_OFFSET                         300
#define TK_ASC                            301
#define TK_NULLS                          302
#define TK_ABORT                          303
#define TK_AFTER                          304
#define TK_ATTACH                         305
#define TK_BEFORE                         306
#define TK_BEGIN                          307
#define TK_BITAND                         308
#define TK_BITNOT                         309
#define TK_BITOR                          310
#define TK_BLOCKS                         311
#define TK_CHANGE                         312
#define TK_COMMA                          313
#define TK_CONCAT                         314
#define TK_CONFLICT                       315
#define TK_COPY                           316
#define TK_DEFERRED                       317
#define TK_DELIMITERS                     318
#define TK_DETACH                         319
#define TK_DIVIDE                         320
#define TK_DOT                            321
#define TK_EACH                           322
#define TK_FAIL                           323
#define TK_FILE                           324
#define TK_FOR                            325
#define TK_GLOB                           326
#define TK_ID                             327
#define TK_IMMEDIATE                      328
#define TK_IMPORT                         329
#define TK_INITIALLY                      330
#define TK_INSTEAD                        331
#define TK_ISNULL                         332
#define TK_MODULES                        333
#define TK_NK_BITNOT                      334
#define TK_NK_SEMI                        335
#define TK_NOTNULL                        336
#define TK_OF                             337
#define TK_PLUS                           338
#define TK_PRIVILEGE                      339
#define TK_RAISE                          340
#define TK_RESTRICT                       341
#define TK_ROW                            342
#define TK_SEMI                           343
#define TK_STAR                           344
#define TK_STATEMENT                      345
#define TK_STRICT                         346
#define TK_STRING                         347
#define TK_TIMES                          348
#define TK_VALUES                         349
#define TK_VARIABLE                       350
#define TK_WAL                            351
#endif
/**************** End token definitions ***************************************/

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
**    ParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ParseCTX_*         As ParseARG_ except for %extra_context
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
#define YYNOCODE 513
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE  SToken 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  EFillMode yy18;
  ENullOrder yy109;
  int8_t yy125;
  EOrder yy164;
  int64_t yy207;
  SShowTablesOption yy385;
  SNodeList* yy388;
  SDataType yy412;
  int32_t yy424;
  SAlterOption yy443;
  STokenPair yy453;
  SNode* yy560;
  EShowKind yy591;
  EOperatorType yy668;
  EJoinType yy684;
  SToken yy965;
  bool yy983;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  SAstCreateContext* pCxt ;
#define ParseARG_PDECL , SAstCreateContext* pCxt 
#define ParseARG_PARAM ,pCxt 
#define ParseARG_FETCH  SAstCreateContext* pCxt =yypParser->pCxt ;
#define ParseARG_STORE yypParser->pCxt =pCxt ;
#define ParseCTX_SDECL
#define ParseCTX_PDECL
#define ParseCTX_PARAM
#define ParseCTX_FETCH
#define ParseCTX_STORE
#define YYFALLBACK 1
#define YYNSTATE             854
#define YYNRULE              650
#define YYNRULE_WITH_ACTION  650
#define YYNTOKEN             352
#define YY_MAX_SHIFT         853
#define YY_MIN_SHIFTREDUCE   1258
#define YY_MAX_SHIFTREDUCE   1907
#define YY_ERROR_ACTION      1908
#define YY_ACCEPT_ACTION     1909
#define YY_NO_ACTION         1910
#define YY_MIN_REDUCE        1911
#define YY_MAX_REDUCE        2560
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

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
#define YY_ACTTAB_COUNT (3149)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   422,  413,  567, 2155,  704,  568, 1954, 2531,  168,  171,
 /*    10 */   399,  173,   48,   46, 1829,  400, 2103, 2103, 2153, 2040,
 /*    20 */   419, 1912, 1670, 2153, 1909,  703,  203,  716,  146,  468,
 /*    30 */  2532,  705,  484, 2216,  467, 1755, 1997, 1668, 2240,   38,
 /*    40 */   321, 2536,  127, 1698, 2531,  126,  125,  124,  123,  122,
 /*    50 */   121,  120,  119,  118,   41,   40, 2238,  724,   47,   45,
 /*    60 */    44,   43,   42, 2535,  184, 1750, 1699, 2532, 2534,   41,
 /*    70 */    40,   19, 1695,   47,   45,   44,   43,   42, 1676,  675,
 /*    80 */   575,  219, 2531,  568, 1954, 1696,  385,  127, 2220,  736,
 /*    90 */   126,  125,  124,  123,  122,  121,  120,  119,  118,   68,
 /*   100 */  2537,  203,  196,  434,  850, 2532,  705,   15,  433,  825,
 /*   110 */   824,  823,  822,  431, 2142,  821,  820,  151,  815,  814,
 /*   120 */   813,  812,  811,  810,  809,  150,  803,  802,  801,  430,
 /*   130 */   429,  798,  797,  796,  183,  182,  795,  301, 2458,  715,
 /*   140 */  1305,  138,  714,  238, 2531, 1757, 1758,  570,  572, 1962,
 /*   150 */   172,  737, 2101,  675,  569,  341, 2531,   47,   45,   44,
 /*   160 */    43,   42,  703,  203, 1303, 1304, 2240, 2532,  705, 1873,
 /*   170 */  2173,  137,  339,   74, 2537,  203,   73,  736,  610, 2532,
 /*   180 */   705,  412, 1730, 1740, 2237,  724,  368,  240, 2155, 1756,
 /*   190 */  1759,  570,  658, 1962,   63,  383, 1695,  587,  236,  549,
 /*   200 */   547,  544,   63, 2153, 1671,  584, 1669,  303,   41,   40,
 /*   210 */  1498, 1499,   47,   45,   44,   43,   42, 1934,   41,   40,
 /*   220 */     9,   34,   47,   45,   44,   43,   42,   41,   40,   52,
 /*   230 */   199,   47,   45,   44,   43,   42, 1674, 1675, 1727,   63,
 /*   240 */  1729, 1732, 1733, 1734, 1735, 1736, 1737, 1738, 1739,  749,
 /*   250 */   745, 1748, 1749, 1751, 1752, 1753, 1754,    2,   48,   46,
 /*   260 */   698,  585, 2233,  365,   51, 1693,  419,  699, 1670,  794,
 /*   270 */  2326,  377,  518,  704,  475,  537, 2531,  737, 2101,   64,
 /*   280 */   536, 1755,  583, 1668, 1700,   41,   40, 2465, 2378,   47,
 /*   290 */    45,   44,   43,   42,  703,  203,  498,  208,  538, 2532,
 /*   300 */   705,   41,   40,  366,  500,   47,   45,   44,   43,   42,
 /*   310 */  1833, 1750, 1911, 2462,  478, 1784, 1695,   19, 1845,  534,
 /*   320 */   532, 1324,  367, 1323, 1676,  174,  217, 1923,   84,   83,
 /*   330 */   471,  513,  512,  216,  716,  146,  136,  135,  134,  133,
 /*   340 */   132,  131,  130,  129,  128,  656,  463,  461, 1765,  697,
 /*   350 */   850,  386, 1405,   15, 1695, 1463, 1325,  364, 1569, 1570,
 /*   360 */   450,  305,  486,  447,  443,  439,  436,  464,  736,  305,
 /*   370 */    12, 1454,  782,  781,  780, 1458,  779, 1460, 1461,  778,
 /*   380 */   775, 1785, 1469,  772, 1471, 1472,  769,  766,  763, 2149,
 /*   390 */  2150, 1757, 1758, 1407, 2227, 2206,  305,  525,  524,  523,
 /*   400 */   522,  517,  516,  515,  514,  369,  305,  428,  427,  504,
 /*   410 */   503,  502,  501,  495,  494,  493, 1676,  488,  487,  384,
 /*   420 */    44,   43,   42,  479, 1557, 1558,  716,  146, 1730, 1740,
 /*   430 */  1576,  305, 1677,   41,   40, 1756, 1759,   47,   45,   44,
 /*   440 */    43,   42, 1786,  718,  201, 2458, 2459,  564,  144, 2463,
 /*   450 */  1671, 1818, 1669, 2465, 2536,   51,  562, 2531,   30,  558,
 /*   460 */   554,   37,  417, 1779, 1780, 1781, 1782, 1783, 1787, 1788,
 /*   470 */  1789, 1790, 2199, 1904,  391,  390, 2535,  170, 1731, 2461,
 /*   480 */  2532, 2533, 1674, 1675, 1727, 1727, 1729, 1732, 1733, 1734,
 /*   490 */  1735, 1736, 1737, 1738, 1739,  749,  745, 1748, 1749, 1751,
 /*   500 */  1752, 1753, 1754,    2,   12,   48,   46,   63,  674,  785,
 /*   510 */   716,  146, 1298,  419,  482, 1670, 1731,  490, 2216,   41,
 /*   520 */    40, 1695,   35,   47,   45,   44,   43,   42, 1755, 2360,
 /*   530 */  1668, 1305, 1791, 1874, 1728,  256,  202, 2458, 2459, 2319,
 /*   540 */   144, 2463,  719,  326,  520, 2216,  389,  388, 1695,  612,
 /*   550 */    12,  179,   10,  659, 1300, 1303, 1304,  197, 1750, 1933,
 /*   560 */   604,  600,  596,  592,   19,  255,  221,  629,  628,  627,
 /*   570 */  2378, 1676, 1728,  614,  619,  143,  623,  613, 1903,  273,
 /*   580 */   622, 1854, 2326,  272,  753,  621,  626,  393,  392,  675,
 /*   590 */  2536,  620, 2531,  226,  616, 1696, 1855,  850, 1670,  808,
 /*   600 */    15, 1680, 2062,  466, 2360,  465,   96, 1698,   63,  253,
 /*   610 */  2537,  203, 2326, 1668, 2465, 2532,  705,  754, 1932, 1931,
 /*   620 */   204, 2458, 2459, 2359,  144, 2463, 2397,  577, 2279,  114,
 /*   630 */  2361,  757, 2363, 2364,  752,  464,  747, 1853, 1757, 1758,
 /*   640 */  2460,  186,   61, 2450, 1324, 2378, 1323,  415, 2446, 2078,
 /*   650 */   672,  659,   98,  452, 1676,  372,  112, 2326,  398,  753,
 /*   660 */   649,  142,  205,  792,  161,  160,  789,  788,  787,  158,
 /*   670 */  2480, 2326, 2326,  147,  305, 1730, 1740,  243,   36, 1325,
 /*   680 */   850, 2093, 1756, 1759,   41,   40,  252,  245,   47,   45,
 /*   690 */    44,   43,   42,  250,  581, 1897, 2090, 1671, 2359, 1669,
 /*   700 */  2155, 2397, 1930, 2288,  114, 2361,  757, 2363, 2364,  752,
 /*   710 */  1731,  747,  242, 2086,  149,  723,  156, 2421, 2450,  223,
 /*   720 */  1589, 1590,  415, 2446,  424,  661, 2279, 2148, 2150, 1674,
 /*   730 */  1675, 1727,  184, 1729, 1732, 1733, 1734, 1735, 1736, 1737,
 /*   740 */  1738, 1739,  749,  745, 1748, 1749, 1751, 1752, 1753, 1754,
 /*   750 */     2,   48,   46, 1760, 2360, 2326, 2221,  275, 1417,  419,
 /*   760 */    90, 1670, 2088,   89, 1588, 1591, 1728,  719, 2076, 2189,
 /*   770 */  1862,  303, 2084, 1416, 1755,  305, 1668,   95,  737, 2101,
 /*   780 */  1671,  528, 1669,  456,  694,  274, 2360,  792,  161,  160,
 /*   790 */   789,  788,  787,  158,  387, 2378,  737, 2101,  137,  754,
 /*   800 */  1929, 1964,  805, 2096, 1750,  615,  739, 2326, 2422,  753,
 /*   810 */   458,  454, 1674, 1675, 2336,  647,   56, 1676,   14,   13,
 /*   820 */   691,  690, 1860, 1861, 1863, 1864, 1865, 2378, 2092, 2155,
 /*   830 */   645,   88,  643,  270,  269,  741,  409, 2422, 2340, 2326,
 /*   840 */   539,  753, 1699,  850, 2153,  228,   49,  784, 2359, 1327,
 /*   850 */  1328, 2397, 1699, 2326,  114, 2361,  757, 2363, 2364,  752,
 /*   860 */  2000,  747, 2360, 1638, 1639,  281,  186,  807, 2450,  527,
 /*   870 */   227, 1928,  415, 2446, 1927,  751,  700,  695,  688,  684,
 /*   880 */  2359,  748, 2342, 2397, 1757, 1758,  114, 2361,  757, 2363,
 /*   890 */  2364,  752,  747,  747, 1926, 2481,  737, 2101, 2551,  617,
 /*   900 */  2450,  106, 1925, 2378,  415, 2446,  792,  161,  160,  789,
 /*   910 */   788,  787,  158,  312,  313, 2326,  472,  753,  311,  737,
 /*   920 */  2101, 1730, 1740, 1402, 2326, 1798, 2094, 2326, 1756, 1759,
 /*   930 */   737, 2101,  511,  629,  628,  627,  510,  606,  605,  473,
 /*   940 */   619,  143,  623, 1671,  509, 1669,  622, 2326,  625,  624,
 /*   950 */   492,  621,  626,  393,  392, 2326, 2359,  620, 2041, 2397,
 /*   960 */   616, 1699,  357, 2361,  757, 2363, 2364,  752,  750,  747,
 /*   970 */   738, 2415, 2077,  608,  607, 1674, 1675, 1727, 1922, 1729,
 /*   980 */  1732, 1733, 1734, 1735, 1736, 1737, 1738, 1739,  749,  745,
 /*   990 */  1748, 1749, 1751, 1752, 1753, 1754,    2,   48,   46, 2360,
 /*  1000 */  1826,  737, 2101, 2320, 2155,  419,  194, 1670, 1921,  614,
 /*  1010 */   636,  414,  754,  613, 2488,  737, 2101,  737, 2101, 2153,
 /*  1020 */  1755,  505, 1668,  737, 2101,  648,  737, 2101,  737, 2101,
 /*  1030 */  1920, 2326, 2360,  819,  817,  506,   95,  507,  737, 2101,
 /*  1040 */  2378,  271,  794,  586, 1695,  754, 2098, 2501,  276, 2307,
 /*  1050 */  1750,  171, 2326,  675,  753, 1919, 2531,  639,  284, 2104,
 /*  1060 */  1700, 2326, 2097, 1676,  633,  631,  737, 2101,  422,  148,
 /*  1070 */  1700,  268, 2421, 2378, 2537,  203,  171,  737, 2101, 2532,
 /*  1080 */   705, 2535, 1307, 2326, 2103, 2326,  722,  753, 1694,  850,
 /*  1090 */   737, 2101,   49, 2359,  737, 2101, 2397,  316,  711,  114,
 /*  1100 */  2361,  757, 2363, 2364,  752, 2310,  747, 2360, 2326, 2155,
 /*  1110 */   734, 2551,   72, 2450,  735,   71,  654,  415, 2446, 1918,
 /*  1120 */   754,  737, 2101,  660,  732,  198, 2359, 1917, 2336, 2397,
 /*  1130 */  1757, 1758,  114, 2361,  757, 2363, 2364,  752, 2155,  747,
 /*  1140 */   786,  322, 2344, 2146, 2551,  423, 2450,  708, 2378,  425,
 /*  1150 */   415, 2446, 2340, 2153, 1924, 2155,  441,  171,  737, 2101,
 /*  1160 */  2326,  790,  753, 1916, 2146, 2103,  675, 1730, 1740, 2531,
 /*  1170 */  2154, 1915, 2326,  675, 1756, 1759, 2531,  298,  426, 1700,
 /*  1180 */  2326,  791,   99, 1421, 2146, 1939,  845, 2537,  203, 1671,
 /*  1190 */   692, 1669, 2532,  705, 2537,  203, 2342,  416, 1420, 2532,
 /*  1200 */   705, 2359, 1914,  744, 2397,    3,  747,  175, 2361,  757,
 /*  1210 */  2363, 2364,  752, 1617,  747,  335, 2326,   54, 2132, 2470,
 /*  1220 */  1818, 1674, 1675, 1727, 2326, 1729, 1732, 1733, 1734, 1735,
 /*  1230 */  1736, 1737, 1738, 1739,  749,  745, 1748, 1749, 1751, 1752,
 /*  1240 */  1753, 1754,    2,   48,   46, 2360,  159, 2336, 2079,  676,
 /*  1250 */  2491,  419,  720, 1670,   76, 2326,  261,  139,  754,  259,
 /*  1260 */   686, 2345, 1728,  618,  263,  541, 1755,  262, 1668,   86,
 /*  1270 */   265, 2340, 1825,  264,  267, 1984,  159,  266, 2360,  210,
 /*  1280 */   159,  152, 1982,  651,  141,  650, 2378, 1400, 1973, 1971,
 /*  1290 */   285,  754,  682, 2524,   50,   50, 1750,  630, 2326, 2494,
 /*  1300 */   753, 1679,  675, 2347,  632, 2531,   14,   13,   87, 1676,
 /*  1310 */   634,  637,  187,  159,   50, 2342, 1906, 1907,  292, 2378,
 /*  1320 */   310,   55, 2379, 2537,  203,  747,   75,  157, 2532,  705,
 /*  1330 */   159, 2326,   66,  753,  100,  850,   50, 2038,   15, 2359,
 /*  1340 */    50, 2037, 2397, 2225,  761,  114, 2361,  757, 2363, 2364,
 /*  1350 */   752, 1633,  747,  157,  159, 1636, 1965, 2551,  140, 2450,
 /*  1360 */  1955, 2349,  111,  415, 2446,  712,  157, 1849, 1776, 1859,
 /*  1370 */  1858,  108, 2359, 2484,  707, 2397, 1757, 1758,  114, 2361,
 /*  1380 */   757, 2363, 2364,  752, 1678,  747,  799,  290,  721, 1586,
 /*  1390 */  2551, 1360, 2450,  800,  689,  314,  415, 2446,  405,  696,
 /*  1400 */   401,  729,  318, 2360,  726, 1447,  432, 1792,  843, 2226,
 /*  1410 */  1379, 1741,  709, 1730, 1740,  334,  754, 1377, 2469, 1476,
 /*  1420 */  1756, 1759, 1961, 2143,  668, 2485,  717, 2063, 1480, 1487,
 /*  1430 */  2495,  300, 1361, 1485,  297, 1671,  304, 1669,  440,    5,
 /*  1440 */   435,  162,  381,  448, 2378,  449, 1703,  459,  211,  212,
 /*  1450 */   460,  214,  329,  462, 1610, 1693, 2326,  476,  753, 1694,
 /*  1460 */   483,  225,  485,  489,  491,  530,  496, 1674, 1675, 1727,
 /*  1470 */  1682, 1729, 1732, 1733, 1734, 1735, 1736, 1737, 1738, 1739,
 /*  1480 */   749,  745, 1748, 1749, 1751, 1752, 1753, 1754,    2,  428,
 /*  1490 */   427,  508,  543,  519, 2218,  526,  521, 2359,  529, 1684,
 /*  1500 */  2397,  531,  542,  114, 2361,  757, 2363, 2364,  752,  540,
 /*  1510 */   747,  231, 1755,  230, 1677, 2551,  545, 2450,  546,  233,
 /*  1520 */   548,  415, 2446, 2360,  550, 1701,  565,  566,    4,  573,
 /*  1530 */  1696,  574,  576,  578,  241,   92,  754, 1702, 1704,  579,
 /*  1540 */   580,  244, 1750,  582, 1705, 2234,  588,  609,  655,  247,
 /*  1550 */  2297,  249,   93, 1681,   94, 1676,  254, 2360,  640,  641,
 /*  1560 */   653,  116,   97,  361, 2378,  153, 1697,  663,  664,  330,
 /*  1570 */   754,  277, 2280,  611,  662,  280, 2326, 2091,  753,  258,
 /*  1580 */  2087,  743,  260,  282,  164,  165, 2089, 2085,  166,  167,
 /*  1590 */  2360,  693,  667, 2294,  670, 2500,  727,    8, 2378, 2472,
 /*  1600 */  2499,  178,  702,  754, 2293,  291,  679,  293,  680,  678,
 /*  1610 */  2326,  295,  753,  677, 2554,  713,  406, 2359,  299,  294,
 /*  1620 */  2397,  287, 1818,  114, 2361,  757, 2363, 2364,  752,  710,
 /*  1630 */   747, 2378,  289,  145, 1698, 2425,  669, 2450, 1823,  296,
 /*  1640 */   206,  415, 2446, 2326, 2530,  753, 1821,  190,  306,  331,
 /*  1650 */   154, 2359,  725, 2466, 2397,  332,  730,  115, 2361,  757,
 /*  1660 */  2363, 2364,  752,  731,  747, 2360, 2248,   62, 2247,  155,
 /*  1670 */   105, 2450,  107,  759, 2246,  411, 2447,  333,  754, 2147,
 /*  1680 */  2431, 1685,  324, 1680, 2359, 2102,  336, 2397, 1282,  844,
 /*  1690 */   114, 2361,  757, 2363, 2364,  752,  847,  747, 2360,    1,
 /*  1700 */   360,  163, 2423,   53, 2450,  849, 2378, 2318,  415, 2446,
 /*  1710 */   373,  754,  345, 1688, 1690,  340,  359,  374, 2326,  349,
 /*  1720 */   753,  338, 2317, 2316,   81, 2311,  437,  745, 1748, 1749,
 /*  1730 */  1751, 1752, 1753, 1754, 2360,  438, 1661, 1662,  209, 2378,
 /*  1740 */   442, 2309,  444,  445,  446, 1660, 2308,  754,  382, 2306,
 /*  1750 */   451, 2326, 2305,  753,  453, 2304,  455, 2303,  457, 2359,
 /*  1760 */  1649, 2284, 2397,  213, 2283,  114, 2361,  757, 2363, 2364,
 /*  1770 */   752,  215,  747, 1613,   82, 2378, 1612,  740, 2261, 2450,
 /*  1780 */  2260, 2259,  470,  415, 2446,  469, 2258, 2326, 2257,  753,
 /*  1790 */  2208, 2360, 2359,  474, 1556, 2397, 2205,  477,  115, 2361,
 /*  1800 */   757, 2363, 2364,  752,  754,  747, 2204, 2198,  480,  481,
 /*  1810 */  2195,  218, 2450, 2194, 2360,   85, 2449, 2446, 2193, 2192,
 /*  1820 */  2197,  220, 2196, 2191, 2190, 2188, 2187,  754, 2359, 2360,
 /*  1830 */  2186, 2397, 2378, 2185,  115, 2361,  757, 2363, 2364,  752,
 /*  1840 */   222,  747,  754,  499, 2326,  497,  753, 2183, 2450, 2182,
 /*  1850 */  2181, 2180,  742, 2446, 2203, 2378, 2179, 2178, 2177, 2201,
 /*  1860 */  2184, 2176, 2175, 2174, 2172, 2171, 2170, 2326, 2169,  753,
 /*  1870 */  2378, 2168, 2167, 2166,   91, 2165,  224, 2164, 2163, 2202,
 /*  1880 */  2200, 2162, 2326, 2161,  753,  755, 2160,  229, 2397, 1562,
 /*  1890 */  2159,  115, 2361,  757, 2363, 2364,  752,  533,  747, 2158,
 /*  1900 */  2157,  535, 2156,  370, 1418, 2450, 1422, 2003, 2359,  376,
 /*  1910 */  2446, 2397, 2002,  232,  176, 2361,  757, 2363, 2364,  752,
 /*  1920 */   371,  747, 1414, 2359, 2001, 1999, 2397, 1996,  551,  175,
 /*  1930 */  2361,  757, 2363, 2364,  752,  553,  747, 2360,  552,  234,
 /*  1940 */  1995,  235,  555,  556, 1988,  557,  559,  560, 1975, 1950,
 /*  1950 */   754,  563,  561,  237, 2360,   78,  185, 1306, 1949,   79,
 /*  1960 */  2346,  239, 2282, 2278,  195,  571, 2268,  754,  706, 2552,
 /*  1970 */  2256,  246, 2492, 2360,  248, 2255, 2232,  251, 2378, 2080,
 /*  1980 */  1998, 1994,  589,  403,  590, 1992,  754,  593,  591,  594,
 /*  1990 */  2326, 1353,  753,  595, 1990, 2378,  597,  599,  598, 1987,
 /*  2000 */   404,  601,  603,  602, 1970, 1968, 1969, 2326, 1967,  753,
 /*  2010 */  1946, 2082,   65, 1491, 2378, 1492, 2081,  257, 1985, 1404,
 /*  2020 */  1403, 1401,  816, 1399, 1398, 1397, 2326, 1396,  753, 1395,
 /*  2030 */   818, 2359, 1392, 1391, 2397, 1390,  394,  358, 2361,  757,
 /*  2040 */  2363, 2364,  752, 1983,  747,  395, 1389, 2360, 2359, 1974,
 /*  2050 */   396, 2397, 1972,  635,  358, 2361,  757, 2363, 2364,  752,
 /*  2060 */   754,  747,  397,  638, 1945, 1944, 1943, 2359,  642, 2360,
 /*  2070 */  2397,  644, 1941,  351, 2361,  757, 2363, 2364,  752, 1942,
 /*  2080 */   747,  646,  754,  117, 2360, 1643, 2281, 1645, 2378, 2277,
 /*  2090 */  1642,  279, 1621, 1619, 2267,  665,  169,  751, 2254, 1623,
 /*  2100 */  2326, 1647,  753, 2253,   57,   29,   58, 2536,   69,   20,
 /*  2110 */  2378,   17,  671,  283,   31,  410,  666,  681, 1598,  701,
 /*  2120 */  1597,  402, 2326, 1876,  753, 2378,  673,  286,    6, 1850,
 /*  2130 */   685,  683,    7,  687,   21,  288,  177, 2326,   22,  753,
 /*  2140 */  1857, 2359,  188,   32, 2397, 1844,  189,  176, 2361,  757,
 /*  2150 */  2363, 2364,  752,   80,  747, 2360,  200, 2347,   33, 1896,
 /*  2160 */    67,   24, 1897, 2359, 1891,  657, 2397, 1890,  754,  358,
 /*  2170 */  2361,  757, 2363, 2364,  752,  407,  747,   23, 2359, 1895,
 /*  2180 */    18, 2397, 1894,  853,  357, 2361,  757, 2363, 2364,  752,
 /*  2190 */  2360,  747,  408, 2416,   60, 1815, 2378, 2252, 1814,  328,
 /*  2200 */   302,  418, 2553,  754, 2231,  180,  101,  102, 2326,   59,
 /*  2210 */   753, 2230,  103,   25,   26,  193,  108,  309, 1852,  191,
 /*  2220 */   320,  315,   70,  104,  841,  837,  833,  829, 1767,  325,
 /*  2230 */    11, 2378,  728,  317, 1766,   13,  420, 1686, 1777, 2400,
 /*  2240 */   181, 1745,  746, 2326, 1743,  753,   39,  192, 1742, 2359,
 /*  2250 */    16,   27, 2397, 1720, 1712,  358, 2361,  757, 2363, 2364,
 /*  2260 */   752, 2360,  747,  760,  758,   28,  421, 1477, 1474,  762,
 /*  2270 */   113,  764,  756,  319,  754,  765,  767, 1473,  770,  768,
 /*  2280 */   773, 1470,  771,  774, 2359, 2360, 1464, 2397, 1462,  776,
 /*  2290 */   358, 2361,  757, 2363, 2364,  752,  777,  747,  754,  109,
 /*  2300 */   323,  110, 2378, 1453, 1468,  783, 1486,  733,   77, 1467,
 /*  2310 */  1482, 1386, 1351, 1466, 2326, 1465,  753,  793, 1383, 1382,
 /*  2320 */  1381, 1380, 1378, 1376, 1375, 1412, 2378, 1374, 2360,  804,
 /*  2330 */   207, 1411, 1372,  806, 1369, 1371, 1370, 1368, 2326, 1367,
 /*  2340 */   753,  754, 1366, 1408, 1406, 1363, 1362, 1359, 1358, 1357,
 /*  2350 */   308, 1356, 1993,  826,  827,  652, 1991,  307, 2397,  828,
 /*  2360 */   830,  353, 2361,  757, 2363, 2364,  752,  832,  747, 2378,
 /*  2370 */   831, 1989,  834,  835,  836, 1986,  278,  838,  840, 2359,
 /*  2380 */   839, 2326, 2397,  753,  842,  343, 2361,  757, 2363, 2364,
 /*  2390 */   752, 1966,  747, 2360, 1295, 1940, 1283,  846,  327,  848,
 /*  2400 */  1910, 1672,  337,  851, 1910,  852,  754, 1910, 1910, 1910,
 /*  2410 */  2360, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2420 */  1910, 1910, 2359,  754, 1910, 2397, 2360, 1910,  342, 2361,
 /*  2430 */   757, 2363, 2364,  752, 2378,  747, 1910, 1910, 1910,  754,
 /*  2440 */  1910, 1910, 1910, 1910, 1910, 1910, 2326, 1910,  753, 1910,
 /*  2450 */  1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2460 */  1910, 1910, 1910, 2326, 1910,  753, 1910, 2378, 1910, 1910,
 /*  2470 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 2326,
 /*  2480 */  1910,  753, 1910, 1910, 1910, 1910, 1910, 2359, 1910, 1910,
 /*  2490 */  2397, 1910, 1910,  344, 2361,  757, 2363, 2364,  752, 1910,
 /*  2500 */   747, 1910, 1910, 2360, 2359, 1910, 1910, 2397, 1910, 1910,
 /*  2510 */   350, 2361,  757, 2363, 2364,  752,  754,  747, 1910, 1910,
 /*  2520 */  2359, 2360, 1910, 2397, 1910, 1910,  354, 2361,  757, 2363,
 /*  2530 */  2364,  752, 1910,  747,  754, 1910, 1910, 2360, 1910, 1910,
 /*  2540 */  1910, 1910, 1910, 1910, 2378, 1910, 1910, 1910, 1910, 1910,
 /*  2550 */   754, 1910, 1910, 1910, 1910, 1910, 2326, 1910,  753, 1910,
 /*  2560 */  1910, 1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2570 */  1910, 1910, 1910, 1910, 2326, 1910,  753, 1910, 2378, 1910,
 /*  2580 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2590 */  2326, 1910,  753, 1910, 1910, 1910, 1910, 2359, 1910, 1910,
 /*  2600 */  2397, 1910, 1910,  346, 2361,  757, 2363, 2364,  752, 1910,
 /*  2610 */   747, 1910, 1910, 1910, 2360, 2359, 1910, 1910, 2397, 1910,
 /*  2620 */  1910,  355, 2361,  757, 2363, 2364,  752,  754,  747, 1910,
 /*  2630 */  2360, 2359, 1910, 1910, 2397, 1910, 1910,  347, 2361,  757,
 /*  2640 */  2363, 2364,  752,  754,  747, 1910, 2360, 1910, 1910, 1910,
 /*  2650 */  1910, 1910, 1910, 1910, 1910, 2378, 1910, 1910, 1910,  754,
 /*  2660 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 2326, 1910,  753,
 /*  2670 */  1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2680 */  1910, 1910, 1910, 2326, 1910,  753, 1910, 2378, 1910, 1910,
 /*  2690 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 2326,
 /*  2700 */  1910,  753, 1910, 1910, 1910, 1910, 1910, 1910, 2359, 1910,
 /*  2710 */  1910, 2397, 1910, 2360,  356, 2361,  757, 2363, 2364,  752,
 /*  2720 */  1910,  747, 1910, 1910, 2359, 1910,  754, 2397, 1910, 1910,
 /*  2730 */   348, 2361,  757, 2363, 2364,  752, 1910,  747, 1910, 2360,
 /*  2740 */  2359, 1910, 1910, 2397, 1910, 1910,  362, 2361,  757, 2363,
 /*  2750 */  2364,  752,  754,  747, 2378, 1910, 1910, 1910, 1910, 1910,
 /*  2760 */  1910, 1910, 1910, 1910, 1910, 1910, 2326, 1910,  753, 1910,
 /*  2770 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2780 */  2378, 1910, 2360, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2790 */  1910, 1910, 2326, 1910,  753,  754, 1910, 1910, 1910, 1910,
 /*  2800 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 2359, 1910, 1910,
 /*  2810 */  2397, 1910, 1910,  363, 2361,  757, 2363, 2364,  752, 2360,
 /*  2820 */   747, 1910, 1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2830 */  1910, 1910,  754, 2359, 1910, 2326, 2397,  753, 1910, 2372,
 /*  2840 */  2361,  757, 2363, 2364,  752, 1910,  747, 1910, 1910, 2360,
 /*  2850 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2860 */  2378, 1910,  754, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2870 */  1910, 1910, 2326, 1910,  753, 1910, 2359, 1910, 1910, 2397,
 /*  2880 */  1910, 1910, 2371, 2361,  757, 2363, 2364,  752, 1910,  747,
 /*  2890 */  2378, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2900 */  1910, 1910, 2326, 1910,  753, 1910, 1910, 1910, 1910, 1910,
 /*  2910 */  1910, 1910, 1910, 2359, 2360, 1910, 2397, 1910, 1910, 2370,
 /*  2920 */  2361,  757, 2363, 2364,  752, 1910,  747,  754, 1910, 1910,
 /*  2930 */  1910, 1910, 2360, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2940 */  1910, 1910, 1910, 2359, 1910,  754, 2397, 1910, 2360,  378,
 /*  2950 */  2361,  757, 2363, 2364,  752, 2378,  747, 1910, 1910, 1910,
 /*  2960 */  1910,  754, 1910, 1910, 1910, 1910, 1910, 2326, 1910,  753,
 /*  2970 */  1910, 1910, 1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  2980 */  1910, 1910, 1910, 1910, 1910, 2326, 1910,  753, 1910, 2378,
 /*  2990 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  3000 */  1910, 2326, 1910,  753, 1910, 1910, 1910, 1910, 2359, 1910,
 /*  3010 */  1910, 2397, 1910, 1910,  379, 2361,  757, 2363, 2364,  752,
 /*  3020 */  1910,  747, 1910, 1910, 1910, 2360, 2359, 1910, 1910, 2397,
 /*  3030 */  1910, 1910,  375, 2361,  757, 2363, 2364,  752,  754,  747,
 /*  3040 */  1910, 2360, 2359, 1910, 1910, 2397, 1910, 1910,  380, 2361,
 /*  3050 */   757, 2363, 2364,  752,  754,  747, 1910, 1910, 1910, 1910,
 /*  3060 */  1910, 1910, 1910, 1910, 1910, 1910, 2378, 1910, 1910, 1910,
 /*  3070 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 2326, 1910,
 /*  3080 */   753, 1910, 2378, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  3090 */  1910, 1910, 1910, 1910, 2326, 1910,  753, 1910, 1910, 1910,
 /*  3100 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,
 /*  3110 */  1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910, 1910,  755,
 /*  3120 */  1910, 1910, 2397, 1910, 1910,  353, 2361,  757, 2363, 2364,
 /*  3130 */   752, 1910,  747, 1910, 1910, 2359, 1910, 1910, 2397, 1910,
 /*  3140 */  1910,  352, 2361,  757, 2363, 2364,  752, 1910,  747,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   388,  388,  362,  396,  481,  365,  366,  484,  396,  396,
 /*    10 */   403,  377,   12,   13,   14,  403,  404,  404,  411,  385,
 /*    20 */    20,    0,   22,  411,  352,  502,  503,  367,  368,  431,
 /*    30 */   507,  508,  367,  368,  436,   35,    0,   37,  410,  470,
 /*    40 */   471,  481,   21,   20,  484,   24,   25,   26,   27,   28,
 /*    50 */    29,   30,   31,   32,    8,    9,  428,  429,   12,   13,
 /*    60 */    14,   15,   16,  503,  396,   65,   20,  507,  508,    8,
 /*    70 */     9,   71,   20,   12,   13,   14,   15,   16,   78,  481,
 /*    80 */   362,  416,  484,  365,  366,   20,  418,   21,  420,   20,
 /*    90 */    24,   25,   26,   27,   28,   29,   30,   31,   32,    4,
 /*   100 */   502,  503,  395,  431,  104,  507,  508,  107,  436,   73,
 /*   110 */    74,   75,   76,   77,  407,   79,   80,   81,   82,   83,
 /*   120 */    84,   85,   86,   87,   88,   89,   90,   91,   92,   93,
 /*   130 */    94,   95,   96,   97,   98,   99,  100,  477,  478,  479,
 /*   140 */    23,  481,  482,  363,  484,  145,  146,  367,   14,  369,
 /*   150 */    18,  367,  368,  481,   20,   23,  484,   12,   13,   14,
 /*   160 */    15,   16,  502,  503,   47,   48,  410,  507,  508,  108,
 /*   170 */     0,  387,   40,   41,  502,  503,   44,   20,  394,  507,
 /*   180 */   508,  425,  182,  183,  428,  429,   54,  363,  396,  189,
 /*   190 */   190,  367,   20,  369,  107,  403,   20,   70,   66,   67,
 /*   200 */    68,   69,  107,  411,  204,  367,  206,  184,    8,    9,
 /*   210 */   145,  146,   12,   13,   14,   15,   16,  355,    8,    9,
 /*   220 */    42,    2,   12,   13,   14,   15,   16,    8,    9,  107,
 /*   230 */   184,   12,   13,   14,   15,   16,  236,  237,  238,  107,
 /*   240 */   240,  241,  242,  243,  244,  245,  246,  247,  248,  249,
 /*   250 */   250,  251,  252,  253,  254,  255,  256,  257,   12,   13,
 /*   260 */   368,  423,  424,   18,  107,   20,   20,   20,   22,   70,
 /*   270 */   408,   71,   27,  481,  367,   30,  484,  367,  368,  147,
 /*   280 */    35,   35,   20,   37,  238,    8,    9,  454,  396,   12,
 /*   290 */    13,   14,   15,   16,  502,  503,   51,  387,   53,  507,
 /*   300 */   508,    8,    9,   58,   59,   12,   13,   14,   15,   16,
 /*   310 */    14,   65,    0,  480,   69,  115,   20,   71,  108,  412,
 /*   320 */   413,   20,  415,   22,   78,  354,  419,  356,  196,  197,
 /*   330 */   198,  161,  162,  201,  367,  368,   24,   25,   26,   27,
 /*   340 */    28,   29,   30,   31,   32,  117,  214,  215,   14,  457,
 /*   350 */   104,  106,   37,  107,   20,  104,   55,  225,  182,  183,
 /*   360 */   228,  274,  117,  231,  232,  233,  234,  235,   20,  274,
 /*   370 */   258,  120,  121,  122,  123,  124,  125,  126,  127,  128,
 /*   380 */   129,  181,  131,  132,  133,  134,  135,  136,  137,  409,
 /*   390 */   410,  145,  146,   78,  149,  150,  274,  152,  153,  154,
 /*   400 */   155,  156,  157,  158,  159,  160,  274,   12,   13,  164,
 /*   410 */   165,  166,  167,  168,  169,  170,   78,  172,  173,  174,
 /*   420 */    14,   15,   16,  178,  179,  180,  367,  368,  182,  183,
 /*   430 */   185,  274,   37,    8,    9,  189,  190,   12,   13,   14,
 /*   440 */    15,   16,  181,  476,  477,  478,  479,   51,  481,  482,
 /*   450 */   204,  273,  206,  454,  481,  107,   60,  484,   33,   63,
 /*   460 */    64,  261,  262,  263,  264,  265,  266,  267,  268,  269,
 /*   470 */   270,  271,    0,  196,   39,   40,  503,  184,  182,  480,
 /*   480 */   507,  508,  236,  237,  238,  238,  240,  241,  242,  243,
 /*   490 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*   500 */   254,  255,  256,  257,  258,   12,   13,  107,   50,  117,
 /*   510 */   367,  368,    4,   20,   42,   22,  182,  367,  368,    8,
 /*   520 */     9,   20,  261,   12,   13,   14,   15,   16,   35,  355,
 /*   530 */    37,   23,  271,  108,  238,   35,  477,  478,  479,  431,
 /*   540 */   481,  482,  368,   34,  367,  368,  111,  112,   20,  114,
 /*   550 */   258,   51,  260,  367,   46,   47,   48,  437,   65,  355,
 /*   560 */    60,   61,   62,   63,   71,   65,  416,   73,   74,   75,
 /*   570 */   396,   78,  238,  138,   80,   81,   82,  142,  301,  140,
 /*   580 */    86,   22,  408,  144,  410,   91,   92,   93,   94,  481,
 /*   590 */     3,   97,  484,  416,  100,   20,   37,  104,   22,  383,
 /*   600 */   107,  206,  386,  203,  355,  205,  106,   20,  107,  109,
 /*   610 */   502,  503,  408,   37,  454,  507,  508,  368,  355,  355,
 /*   620 */   477,  478,  479,  449,  481,  482,  452,  441,  442,  455,
 /*   630 */   456,  457,  458,  459,  460,  235,  462,   78,  145,  146,
 /*   640 */   480,  467,  184,  469,   20,  396,   22,  473,  474,    0,
 /*   650 */   192,  367,  213,   69,   78,  216,  374,  408,  219,  410,
 /*   660 */   221,   37,  488,  138,  139,  140,  141,  142,  143,  144,
 /*   670 */   496,  408,  408,  391,  274,  182,  183,  177,    2,   55,
 /*   680 */   104,  399,  189,  190,    8,    9,  186,  187,   12,   13,
 /*   690 */    14,   15,   16,  193,  194,  108,  397,  204,  449,  206,
 /*   700 */   396,  452,  355,  392,  455,  456,  457,  458,  459,  460,
 /*   710 */   182,  462,  212,  397,  465,  411,  467,  468,  469,   65,
 /*   720 */   145,  146,  473,  474,  406,  441,  442,  409,  410,  236,
 /*   730 */   237,  238,  396,  240,  241,  242,  243,  244,  245,  246,
 /*   740 */   247,  248,  249,  250,  251,  252,  253,  254,  255,  256,
 /*   750 */   257,   12,   13,   14,  355,  408,  420,  446,   22,   20,
 /*   760 */   106,   22,  397,  109,  189,  190,  238,  368,    0,    0,
 /*   770 */   236,  184,  397,   37,   35,  274,   37,  376,  367,  368,
 /*   780 */   204,   87,  206,  199,  188,  139,  355,  138,  139,  140,
 /*   790 */   141,  142,  143,  144,  393,  396,  367,  368,  387,  368,
 /*   800 */   355,  370,   13,  402,   65,  394,  466,  408,  468,  410,
 /*   810 */   226,  227,  236,  237,  384,   21,  387,   78,    1,    2,
 /*   820 */   286,  287,  288,  289,  290,  291,  292,  396,  398,  396,
 /*   830 */    36,  177,   38,   39,   40,  466,  403,  468,  408,  408,
 /*   840 */   104,  410,   20,  104,  411,  151,  107,  397,  449,   56,
 /*   850 */    57,  452,   20,  408,  455,  456,  457,  458,  459,  460,
 /*   860 */     0,  462,  355,  217,  218,  397,  467,   78,  469,  175,
 /*   870 */   176,  355,  473,  474,  355,  368,  280,  281,  282,  283,
 /*   880 */   449,  397,  452,  452,  145,  146,  455,  456,  457,  458,
 /*   890 */   459,  460,  462,  462,  355,  496,  367,  368,  467,   13,
 /*   900 */   469,  374,  355,  396,  473,  474,  138,  139,  140,  141,
 /*   910 */   142,  143,  144,  139,  140,  408,  387,  410,  144,  367,
 /*   920 */   368,  182,  183,   37,  408,  108,  399,  408,  189,  190,
 /*   930 */   367,  368,  163,   73,   74,   75,  167,  372,  373,  387,
 /*   940 */    80,   81,   82,  204,  175,  206,   86,  408,  381,  382,
 /*   950 */   387,   91,   92,   93,   94,  408,  449,   97,  385,  452,
 /*   960 */   100,   20,  455,  456,  457,  458,  459,  460,  461,  462,
 /*   970 */   463,  464,    0,  372,  373,  236,  237,  238,  355,  240,
 /*   980 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   990 */   251,  252,  253,  254,  255,  256,  257,   12,   13,  355,
 /*  1000 */     4,  367,  368,  431,  396,   20,  184,   22,  355,  138,
 /*  1010 */     4,  403,  368,  142,  370,  367,  368,  367,  368,  411,
 /*  1020 */    35,  387,   37,  367,  368,   19,  367,  368,  367,  368,
 /*  1030 */   355,  408,  355,  381,  382,  387,  376,  387,  367,  368,
 /*  1040 */   396,   35,   70,  387,   20,  368,  387,  370,  387,    0,
 /*  1050 */    65,  396,  408,  481,  410,  355,  484,   51,  387,  404,
 /*  1060 */   238,  408,  402,   78,   58,   59,  367,  368,  388,  465,
 /*  1070 */   238,   65,  468,  396,  502,  503,  396,  367,  368,  507,
 /*  1080 */   508,    3,   14,  408,  404,  408,  387,  410,   20,  104,
 /*  1090 */   367,  368,  107,  449,  367,  368,  452,  387,   33,  455,
 /*  1100 */   456,  457,  458,  459,  460,    0,  462,  355,  408,  396,
 /*  1110 */   387,  467,  106,  469,  387,  109,  431,  473,  474,  355,
 /*  1120 */   368,  367,  368,  431,  411,  184,  449,  355,  384,  452,
 /*  1130 */   145,  146,  455,  456,  457,  458,  459,  460,  396,  462,
 /*  1140 */   405,  387,  398,  408,  467,  403,  469,   33,  396,  388,
 /*  1150 */   473,  474,  408,  411,  356,  396,   51,  396,  367,  368,
 /*  1160 */   408,  405,  410,  355,  408,  404,  481,  182,  183,  484,
 /*  1170 */   411,  355,  408,  481,  189,  190,  484,  511,  387,  238,
 /*  1180 */   408,  405,  177,   22,  408,  358,  359,  502,  503,  204,
 /*  1190 */   500,  206,  507,  508,  502,  503,  452,  453,   37,  507,
 /*  1200 */   508,  449,  355,   71,  452,   33,  462,  455,  456,  457,
 /*  1210 */   458,  459,  460,  208,  462,  389,  408,   45,  392,  272,
 /*  1220 */   273,  236,  237,  238,  408,  240,  241,  242,  243,  244,
 /*  1230 */   245,  246,  247,  248,  249,  250,  251,  252,  253,  254,
 /*  1240 */   255,  256,  257,   12,   13,  355,   33,  384,    0,  497,
 /*  1250 */   498,   20,  431,   22,  117,  408,  110,   33,  368,  113,
 /*  1260 */   370,  398,  238,   13,  110,  104,   35,  113,   37,   45,
 /*  1270 */   110,  408,  276,  113,  110,    0,   33,  113,  355,  230,
 /*  1280 */    33,   33,    0,  220,  371,  222,  396,   37,    0,    0,
 /*  1290 */    65,  368,   33,  370,   33,   33,   65,   22,  408,  421,
 /*  1300 */   410,   37,  481,   49,   22,  484,    1,    2,  171,   78,
 /*  1310 */    22,   22,   33,   33,   33,  452,  145,  146,  493,  396,
 /*  1320 */    33,  108,  396,  502,  503,  462,   33,   33,  507,  508,
 /*  1330 */    33,  408,   33,  410,  109,  104,   33,  384,  107,  449,
 /*  1340 */    33,  384,  452,  421,   33,  455,  456,  457,  458,  459,
 /*  1350 */   460,  108,  462,   33,   33,  108,    0,  467,   33,  469,
 /*  1360 */   366,  107,  107,  473,  474,  300,   33,  108,  236,  108,
 /*  1370 */   108,  116,  449,  421,  296,  452,  145,  146,  455,  456,
 /*  1380 */   457,  458,  459,  460,   37,  462,   13,  108,  108,  108,
 /*  1390 */   467,   37,  469,   13,  499,  108,  473,  474,  499,  499,
 /*  1400 */   430,  108,  108,  355,  499,  108,  371,  108,   52,  421,
 /*  1410 */    37,  108,  298,  182,  183,  108,  368,   37,  370,  108,
 /*  1420 */   189,  190,  368,  407,  438,  421,  483,  386,  108,  108,
 /*  1430 */   421,  504,   78,  108,  475,  204,  486,  206,   51,  277,
 /*  1440 */   432,  108,  451,   42,  396,  450,   20,  219,  448,  376,
 /*  1450 */   443,  376,  434,  443,  202,   20,  408,  367,  410,   20,
 /*  1460 */   368,   45,  417,  368,  417,  181,  414,  236,  237,  238,
 /*  1470 */   206,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*  1480 */   249,  250,  251,  252,  253,  254,  255,  256,  257,   12,
 /*  1490 */    13,  367,  380,  368,  367,  414,  417,  449,  414,   22,
 /*  1500 */   452,  414,  105,  455,  456,  457,  458,  459,  460,  103,
 /*  1510 */   462,  367,   35,  379,   37,  467,  102,  469,  378,  367,
 /*  1520 */   367,  473,  474,  355,  367,   20,  360,  364,   50,  360,
 /*  1530 */    20,  364,  443,  410,  376,  376,  368,   20,   20,  369,
 /*  1540 */   433,  376,   65,  369,   20,  424,  367,  360,  447,  376,
 /*  1550 */   408,  376,  376,  206,  376,   78,  376,  355,  358,  358,
 /*  1560 */   223,  367,  107,  360,  396,  445,   20,  210,  440,  443,
 /*  1570 */   368,  374,  442,  396,  209,  439,  408,  396,  410,  396,
 /*  1580 */   396,  104,  396,  374,  396,  396,  396,  396,  396,  396,
 /*  1590 */   355,  285,  410,  408,  367,  492,  284,  293,  396,  495,
 /*  1600 */   492,  492,  195,  368,  408,  494,  408,  491,  295,  294,
 /*  1610 */   408,  489,  410,  278,  512,  299,  302,  449,  505,  490,
 /*  1620 */   452,  426,  273,  455,  456,  457,  458,  459,  460,  297,
 /*  1630 */   462,  396,  426,  368,   20,  467,  432,  469,  117,  432,
 /*  1640 */   485,  473,  474,  408,  506,  410,  275,  369,  374,  426,
 /*  1650 */   374,  449,  408,  454,  452,  426,  187,  455,  456,  457,
 /*  1660 */   458,  459,  460,  422,  462,  355,  408,  107,  408,  374,
 /*  1670 */   374,  469,  107,  400,  408,  408,  474,  392,  368,  408,
 /*  1680 */   472,  204,  374,  206,  449,  368,  367,  452,   22,   38,
 /*  1690 */   455,  456,  457,  458,  459,  460,  357,  462,  355,  487,
 /*  1700 */   444,  361,  467,  435,  469,  360,  396,    0,  473,  474,
 /*  1710 */   427,  368,  390,  236,  237,  353,  390,  427,  408,  390,
 /*  1720 */   410,  375,    0,    0,   45,    0,   37,  250,  251,  252,
 /*  1730 */   253,  254,  255,  256,  355,  229,   37,   37,   37,  396,
 /*  1740 */   229,    0,   37,   37,  229,   37,    0,  368,  229,    0,
 /*  1750 */    37,  408,    0,  410,   37,    0,   22,    0,   37,  449,
 /*  1760 */   224,    0,  452,  212,    0,  455,  456,  457,  458,  459,
 /*  1770 */   460,  212,  462,  206,  213,  396,  204,  467,    0,  469,
 /*  1780 */     0,    0,  199,  473,  474,  200,    0,  408,    0,  410,
 /*  1790 */   150,  355,  449,   49,   49,  452,    0,   37,  455,  456,
 /*  1800 */   457,  458,  459,  460,  368,  462,    0,    0,   37,   51,
 /*  1810 */     0,   49,  469,    0,  355,   45,  473,  474,    0,    0,
 /*  1820 */     0,   49,    0,    0,    0,    0,    0,  368,  449,  355,
 /*  1830 */     0,  452,  396,    0,  455,  456,  457,  458,  459,  460,
 /*  1840 */   167,  462,  368,  167,  408,   37,  410,    0,  469,    0,
 /*  1850 */     0,    0,  473,  474,    0,  396,    0,    0,    0,    0,
 /*  1860 */     0,    0,    0,    0,    0,    0,    0,  408,    0,  410,
 /*  1870 */   396,    0,    0,    0,   45,    0,   49,    0,    0,    0,
 /*  1880 */     0,    0,  408,    0,  410,  449,    0,  150,  452,   22,
 /*  1890 */     0,  455,  456,  457,  458,  459,  460,  149,  462,    0,
 /*  1900 */     0,  148,    0,   50,   22,  469,   22,    0,  449,  473,
 /*  1910 */   474,  452,    0,   65,  455,  456,  457,  458,  459,  460,
 /*  1920 */    50,  462,   37,  449,    0,    0,  452,    0,   37,  455,
 /*  1930 */   456,  457,  458,  459,  460,   42,  462,  355,   51,   65,
 /*  1940 */     0,   65,   37,   51,    0,   42,   37,   51,    0,    0,
 /*  1950 */   368,   37,   42,   45,  355,   42,   33,   14,    0,   42,
 /*  1960 */    49,   43,    0,    0,   49,   49,    0,  368,  509,  510,
 /*  1970 */     0,   42,  498,  355,  195,    0,    0,   49,  396,    0,
 /*  1980 */     0,    0,   37,  401,   51,    0,  368,   37,   42,   51,
 /*  1990 */   408,   72,  410,   42,    0,  396,   37,   42,   51,    0,
 /*  2000 */   401,   37,   42,   51,    0,    0,    0,  408,    0,  410,
 /*  2010 */     0,    0,  115,   22,  396,   37,    0,  113,    0,   37,
 /*  2020 */    37,   37,   33,   37,   37,   37,  408,   37,  410,   37,
 /*  2030 */    33,  449,   37,   37,  452,   22,   22,  455,  456,  457,
 /*  2040 */   458,  459,  460,    0,  462,   22,   37,  355,  449,    0,
 /*  2050 */    22,  452,    0,   53,  455,  456,  457,  458,  459,  460,
 /*  2060 */   368,  462,   22,   37,    0,    0,    0,  449,   37,  355,
 /*  2070 */   452,   37,    0,  455,  456,  457,  458,  459,  460,    0,
 /*  2080 */   462,   22,  368,   20,  355,   37,    0,   37,  396,    0,
 /*  2090 */    37,   49,   22,   37,    0,   22,  207,  368,    0,  211,
 /*  2100 */   408,  108,  410,    0,  184,  107,  184,    3,  107,   33,
 /*  2110 */   396,  279,  191,  187,  107,  401,  184,   37,  184,  501,
 /*  2120 */   184,   37,  408,  108,  410,  396,  191,  107,   50,  108,
 /*  2130 */   105,  107,   50,  103,   33,  108,  107,  408,   33,  410,
 /*  2140 */   108,  449,  107,  107,  452,  108,   33,  455,  456,  457,
 /*  2150 */   458,  459,  460,  107,  462,  355,   49,   49,   33,  108,
 /*  2160 */     3,   33,  108,  449,   37,    1,  452,   37,  368,  455,
 /*  2170 */   456,  457,  458,  459,  460,   37,  462,  279,  449,   37,
 /*  2180 */   279,  452,   37,   19,  455,  456,  457,  458,  459,  460,
 /*  2190 */   355,  462,   37,  464,   33,  108,  396,    0,  108,   35,
 /*  2200 */    49,  401,  510,  368,    0,   49,  107,   42,  408,  272,
 /*  2210 */   410,    0,   42,  107,   33,   51,  116,  108,  108,  107,
 /*  2220 */    49,  107,  107,  107,   60,   61,   62,   63,  105,   65,
 /*  2230 */   259,  396,  188,  186,  105,    2,  401,   22,  236,  107,
 /*  2240 */    49,  108,  107,  408,  108,  410,  107,   49,  108,  449,
 /*  2250 */   107,  107,  452,   22,  108,  455,  456,  457,  458,  459,
 /*  2260 */   460,  355,  462,   37,  117,  107,   37,  108,  108,  107,
 /*  2270 */   106,   37,  239,  109,  368,  107,   37,  108,   37,  107,
 /*  2280 */    37,  108,  107,  107,  449,  355,  108,  452,  108,   37,
 /*  2290 */   455,  456,  457,  458,  459,  460,  107,  462,  368,  107,
 /*  2300 */    33,  107,  396,  119,  130,  118,   37,  143,  107,  130,
 /*  2310 */    22,   37,   72,  130,  408,  130,  410,   71,   37,   37,
 /*  2320 */    37,   37,   37,   37,   37,   78,  396,   37,  355,  101,
 /*  2330 */    33,   78,   37,  101,   22,   37,   37,   37,  408,   37,
 /*  2340 */   410,  368,   37,   78,   37,   37,   37,   37,   37,   22,
 /*  2350 */   186,   37,    0,   37,   51,  449,    0,  193,  452,   42,
 /*  2360 */    37,  455,  456,  457,  458,  459,  460,   42,  462,  396,
 /*  2370 */    51,    0,   37,   51,   42,    0,  212,   37,   42,  449,
 /*  2380 */    51,  408,  452,  410,   37,  455,  456,  457,  458,  459,
 /*  2390 */   460,    0,  462,  355,   37,    0,   22,   33,   22,   21,
 /*  2400 */   513,   22,   22,   21,  513,   20,  368,  513,  513,  513,
 /*  2410 */   355,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2420 */   513,  513,  449,  368,  513,  452,  355,  513,  455,  456,
 /*  2430 */   457,  458,  459,  460,  396,  462,  513,  513,  513,  368,
 /*  2440 */   513,  513,  513,  513,  513,  513,  408,  513,  410,  513,
 /*  2450 */   513,  396,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2460 */   513,  513,  513,  408,  513,  410,  513,  396,  513,  513,
 /*  2470 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  408,
 /*  2480 */   513,  410,  513,  513,  513,  513,  513,  449,  513,  513,
 /*  2490 */   452,  513,  513,  455,  456,  457,  458,  459,  460,  513,
 /*  2500 */   462,  513,  513,  355,  449,  513,  513,  452,  513,  513,
 /*  2510 */   455,  456,  457,  458,  459,  460,  368,  462,  513,  513,
 /*  2520 */   449,  355,  513,  452,  513,  513,  455,  456,  457,  458,
 /*  2530 */   459,  460,  513,  462,  368,  513,  513,  355,  513,  513,
 /*  2540 */   513,  513,  513,  513,  396,  513,  513,  513,  513,  513,
 /*  2550 */   368,  513,  513,  513,  513,  513,  408,  513,  410,  513,
 /*  2560 */   513,  513,  396,  513,  513,  513,  513,  513,  513,  513,
 /*  2570 */   513,  513,  513,  513,  408,  513,  410,  513,  396,  513,
 /*  2580 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2590 */   408,  513,  410,  513,  513,  513,  513,  449,  513,  513,
 /*  2600 */   452,  513,  513,  455,  456,  457,  458,  459,  460,  513,
 /*  2610 */   462,  513,  513,  513,  355,  449,  513,  513,  452,  513,
 /*  2620 */   513,  455,  456,  457,  458,  459,  460,  368,  462,  513,
 /*  2630 */   355,  449,  513,  513,  452,  513,  513,  455,  456,  457,
 /*  2640 */   458,  459,  460,  368,  462,  513,  355,  513,  513,  513,
 /*  2650 */   513,  513,  513,  513,  513,  396,  513,  513,  513,  368,
 /*  2660 */   513,  513,  513,  513,  513,  513,  513,  408,  513,  410,
 /*  2670 */   513,  396,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2680 */   513,  513,  513,  408,  513,  410,  513,  396,  513,  513,
 /*  2690 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  408,
 /*  2700 */   513,  410,  513,  513,  513,  513,  513,  513,  449,  513,
 /*  2710 */   513,  452,  513,  355,  455,  456,  457,  458,  459,  460,
 /*  2720 */   513,  462,  513,  513,  449,  513,  368,  452,  513,  513,
 /*  2730 */   455,  456,  457,  458,  459,  460,  513,  462,  513,  355,
 /*  2740 */   449,  513,  513,  452,  513,  513,  455,  456,  457,  458,
 /*  2750 */   459,  460,  368,  462,  396,  513,  513,  513,  513,  513,
 /*  2760 */   513,  513,  513,  513,  513,  513,  408,  513,  410,  513,
 /*  2770 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2780 */   396,  513,  355,  513,  513,  513,  513,  513,  513,  513,
 /*  2790 */   513,  513,  408,  513,  410,  368,  513,  513,  513,  513,
 /*  2800 */   513,  513,  513,  513,  513,  513,  513,  449,  513,  513,
 /*  2810 */   452,  513,  513,  455,  456,  457,  458,  459,  460,  355,
 /*  2820 */   462,  513,  513,  396,  513,  513,  513,  513,  513,  513,
 /*  2830 */   513,  513,  368,  449,  513,  408,  452,  410,  513,  455,
 /*  2840 */   456,  457,  458,  459,  460,  513,  462,  513,  513,  355,
 /*  2850 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2860 */   396,  513,  368,  513,  513,  513,  513,  513,  513,  513,
 /*  2870 */   513,  513,  408,  513,  410,  513,  449,  513,  513,  452,
 /*  2880 */   513,  513,  455,  456,  457,  458,  459,  460,  513,  462,
 /*  2890 */   396,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  2900 */   513,  513,  408,  513,  410,  513,  513,  513,  513,  513,
 /*  2910 */   513,  513,  513,  449,  355,  513,  452,  513,  513,  455,
 /*  2920 */   456,  457,  458,  459,  460,  513,  462,  368,  513,  513,
 /*  2930 */   513,  513,  355,  513,  513,  513,  513,  513,  513,  513,
 /*  2940 */   513,  513,  513,  449,  513,  368,  452,  513,  355,  455,
 /*  2950 */   456,  457,  458,  459,  460,  396,  462,  513,  513,  513,
 /*  2960 */   513,  368,  513,  513,  513,  513,  513,  408,  513,  410,
 /*  2970 */   513,  513,  513,  396,  513,  513,  513,  513,  513,  513,
 /*  2980 */   513,  513,  513,  513,  513,  408,  513,  410,  513,  396,
 /*  2990 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  3000 */   513,  408,  513,  410,  513,  513,  513,  513,  449,  513,
 /*  3010 */   513,  452,  513,  513,  455,  456,  457,  458,  459,  460,
 /*  3020 */   513,  462,  513,  513,  513,  355,  449,  513,  513,  452,
 /*  3030 */   513,  513,  455,  456,  457,  458,  459,  460,  368,  462,
 /*  3040 */   513,  355,  449,  513,  513,  452,  513,  513,  455,  456,
 /*  3050 */   457,  458,  459,  460,  368,  462,  513,  513,  513,  513,
 /*  3060 */   513,  513,  513,  513,  513,  513,  396,  513,  513,  513,
 /*  3070 */   513,  513,  513,  513,  513,  513,  513,  513,  408,  513,
 /*  3080 */   410,  513,  396,  513,  513,  513,  513,  513,  513,  513,
 /*  3090 */   513,  513,  513,  513,  408,  513,  410,  513,  513,  513,
 /*  3100 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*  3110 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  449,
 /*  3120 */   513,  513,  452,  513,  513,  455,  456,  457,  458,  459,
 /*  3130 */   460,  513,  462,  513,  513,  449,  513,  513,  452,  513,
 /*  3140 */   513,  455,  456,  457,  458,  459,  460,  513,  462,  352,
 /*  3150 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3160 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3170 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3180 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3190 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3200 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3210 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3220 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3230 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3240 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3250 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3260 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3270 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3280 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3290 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3300 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3310 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3320 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3330 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3340 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3350 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3360 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3370 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3380 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3390 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3400 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3410 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3420 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3430 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3440 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3450 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3460 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3470 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3480 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3490 */   352,  352,  352,  352,  352,  352,  352,  352,  352,  352,
 /*  3500 */   352,
};
#define YY_SHIFT_COUNT    (853)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (2395)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   132,    0,  246,    0,  493,  493,  493,  493,  493,  493,
 /*    10 */   493,  493,  493,  493,  493,  493,  739,  985,  985, 1231,
 /*    20 */   985,  985,  985,  985,  985,  985,  985,  985,  985,  985,
 /*    30 */   985,  985,  985,  985,  985,  985,  985,  985,  985,  985,
 /*    40 */   985,  985,  985,  985,  985,  985,  985,  985,  985,  985,
 /*    50 */   985,  157,  501,  400,  348,   87,  122,   87,   87,  348,
 /*    60 */   348,   87, 1477,   87,  245, 1477, 1477,   95,   87,   52,
 /*    70 */   575,   69,   69,  508,  508,  575,  176,   65,  134,  134,
 /*    80 */   247,   69,   69,   69,   69,   69,   69,   69,   69,   69,
 /*    90 */    69,   69,  172,  262,   69,   69,  127,   52,   69,  172,
 /*   100 */    69,   52,   69,   69,   52,   69,   69,   52,   69,   52,
 /*   110 */    52,   52,   69,  199,  200,  200,  494,   66,  576,  576,
 /*   120 */   576,  576,  576,  576,  576,  576,  576,  576,  576,  576,
 /*   130 */   576,  576,  576,  576,  576,  576,  576,  435,  587,  176,
 /*   140 */    65,  793,  793,  315,   23,   23,   23,  972,  292,  292,
 /*   150 */   789,  315,  127,  228,   52,   52,  112,   52,  338,   52,
 /*   160 */   338,  338,  392,  509,  251,  251,  251,  251,  251,  251,
 /*   170 */   251,  251, 2164,  860,   21,   46,  277,  534,  596,  624,
 /*   180 */   296,  334,  395,  395,  822,  117,  941,  559,  559,  559,
 /*   190 */   458,  559,  528,  301,  832, 1068,  871, 1005,  832,  832,
 /*   200 */  1024,  947,  178, 1078,  947, 1172,  996,  789, 1162, 1387,
 /*   210 */  1401, 1426, 1228,  127, 1426,  127, 1252, 1435, 1439, 1416,
 /*   220 */  1439, 1416, 1284, 1435, 1439, 1435, 1416, 1284, 1284, 1284,
 /*   230 */  1397, 1406, 1435, 1414, 1435, 1435, 1435, 1505, 1478, 1505,
 /*   240 */  1478, 1426,  127,  127, 1510,  127, 1517, 1518,  127, 1517,
 /*   250 */   127, 1524,  127,  127, 1435,  127, 1505,   52,   52,   52,
 /*   260 */    52,   52,   52,   52,   52,   52,   52,   52, 1435,  509,
 /*   270 */   509, 1505,  338,  338,  338, 1337, 1455, 1426,  199, 1546,
 /*   280 */  1357, 1365, 1510,  199, 1162, 1435,  338, 1306, 1312, 1306,
 /*   290 */  1312, 1304, 1407, 1306, 1313, 1315, 1335, 1162, 1314, 1316,
 /*   300 */  1332, 1349, 1439, 1614, 1521, 1371, 1517,  199,  199, 1312,
 /*   310 */   338,  338,  338,  338, 1312,  338, 1469,  199,  392,  199,
 /*   320 */  1439, 1560, 1565,  338, 1435,  199, 1666, 1651, 1505, 3149,
 /*   330 */  3149, 3149, 3149, 3149, 3149, 3149, 3149, 3149,   36,  500,
 /*   340 */   312, 1006,  425,   61,  210,  649,  219,  676,  293,  768,
 /*   350 */   511,  511,  511,  511,  511,  511,  511,  511,  511,  525,
 /*   360 */   439,  794,  145,  145,  584,  654,  769,  694,  396,  170,
 /*   370 */   736, 1161,  646,  774,  774,  406,  817,  261,  406,  406,
 /*   380 */   406, 1105, 1049, 1213,  472, 1224, 1137, 1248, 1146, 1154,
 /*   390 */  1160, 1164,  886, 1250, 1275, 1282, 1288, 1289, 1063, 1243,
 /*   400 */  1247, 1225, 1259, 1261, 1262, 1279, 1171, 1114, 1065, 1280,
 /*   410 */  1281, 1287, 1293, 1294, 1297, 1305, 1299, 1132, 1303, 1254,
 /*   420 */  1307, 1311, 1320, 1321, 1325, 1333, 1255, 1264, 1347, 1373,
 /*   430 */  1380, 1354, 1356, 1707, 1722, 1723, 1679, 1725, 1689, 1506,
 /*   440 */  1699, 1700, 1701, 1511, 1741, 1705, 1706, 1515, 1708, 1746,
 /*   450 */  1519, 1749, 1713, 1752, 1717, 1755, 1734, 1757, 1721, 1536,
 /*   460 */  1761, 1551, 1764, 1559, 1561, 1567, 1572, 1778, 1780, 1781,
 /*   470 */  1585, 1583, 1786, 1788, 1640, 1744, 1745, 1796, 1760, 1806,
 /*   480 */  1807, 1771, 1758, 1810, 1762, 1813, 1770, 1818, 1819, 1820,
 /*   490 */  1772, 1822, 1823, 1824, 1825, 1826, 1830, 1673, 1808, 1833,
 /*   500 */  1676, 1847, 1849, 1850, 1851, 1854, 1856, 1857, 1858, 1859,
 /*   510 */  1860, 1861, 1862, 1863, 1864, 1865, 1866, 1868, 1871, 1872,
 /*   520 */  1827, 1873, 1829, 1875, 1877, 1878, 1879, 1880, 1881, 1883,
 /*   530 */  1867, 1886, 1737, 1890, 1748, 1899, 1753, 1900, 1902, 1882,
 /*   540 */  1853, 1884, 1870, 1907, 1848, 1885, 1912, 1874, 1924, 1876,
 /*   550 */  1925, 1927, 1891, 1887, 1893, 1940, 1905, 1892, 1903, 1944,
 /*   560 */  1909, 1896, 1910, 1948, 1914, 1949, 1908, 1913, 1923, 1911,
 /*   570 */  1915, 1943, 1916, 1958, 1918, 1917, 1962, 1963, 1966, 1970,
 /*   580 */  1929, 1779, 1975, 1911, 1928, 1976, 1979, 1919, 1980, 1981,
 /*   590 */  1945, 1933, 1946, 1985, 1950, 1938, 1951, 1994, 1959, 1947,
 /*   600 */  1955, 1999, 1964, 1952, 1960, 2004, 2005, 2006, 2008, 2010,
 /*   610 */  2011, 1897, 1904, 1978, 1991, 2016, 1982, 1983, 1984, 1986,
 /*   620 */  1987, 1988, 1990, 1992, 1989, 1997, 1995, 1996, 2013, 2009,
 /*   630 */  2018, 2014, 2043, 2023, 2049, 2028, 2000, 2052, 2040, 2026,
 /*   640 */  2064, 2065, 2066, 2031, 2079, 2034, 2072, 2059, 2063, 2048,
 /*   650 */  2050, 2053, 1993, 1998, 2086, 1920, 2001, 1888, 1911, 2042,
 /*   660 */  2089, 1922, 2056, 2070, 2094, 1889, 2073, 1932, 1926, 2098,
 /*   670 */  2103, 1934, 1921, 1936, 1935, 2104, 2076, 1832, 2007, 2015,
 /*   680 */  2020, 2021, 2080, 2084, 2024, 2078, 2025, 2082, 2030, 2027,
 /*   690 */  2101, 2105, 2032, 2029, 2035, 2036, 2037, 2113, 2107, 2108,
 /*   700 */  2046, 2125, 1898, 2051, 2054, 2157, 2128, 1901, 2127, 2130,
 /*   710 */  2138, 2142, 2145, 2155, 2087, 2090, 2151, 1937, 2161, 2156,
 /*   720 */  2197, 2204, 2099, 2165, 2106, 2109, 2110, 2112, 2114, 2044,
 /*   730 */  2115, 2211, 2170, 2047, 2116, 2100, 1911, 2171, 2181, 2123,
 /*   740 */  1971, 2129, 2233, 2215, 2002, 2132, 2133, 2135, 2136, 2139,
 /*   750 */  2140, 2191, 2143, 2144, 2198, 2146, 2231, 2033, 2158, 2147,
 /*   760 */  2159, 2226, 2229, 2162, 2160, 2234, 2168, 2169, 2239, 2172,
 /*   770 */  2173, 2241, 2175, 2178, 2243, 2176, 2180, 2252, 2189, 2174,
 /*   780 */  2179, 2183, 2185, 2184, 2187, 2192, 2267, 2194, 2269, 2201,
 /*   790 */  2267, 2267, 2288, 2240, 2246, 2274, 2281, 2282, 2283, 2284,
 /*   800 */  2285, 2286, 2287, 2290, 2247, 2228, 2253, 2232, 2297, 2295,
 /*   810 */  2298, 2299, 2312, 2300, 2302, 2305, 2265, 1989, 2307, 1997,
 /*   820 */  2308, 2309, 2310, 2311, 2327, 2314, 2352, 2316, 2303, 2317,
 /*   830 */  2356, 2323, 2319, 2325, 2371, 2335, 2322, 2332, 2375, 2340,
 /*   840 */  2329, 2336, 2391, 2347, 2357, 2395, 2374, 2364, 2376, 2378,
 /*   850 */  2379, 2380, 2382, 2385,
};
#define YY_REDUCE_COUNT (337)
#define YY_REDUCE_MIN   (-477)
#define YY_REDUCE_MAX   (2686)
static const short yy_reduce_ofst[] = {
 /*     0 */  -328,  174,  249,  399,  431,  644,  677,  890,  923, 1048,
 /*    10 */  1168, 1235, 1310, 1343, 1379, 1436,  507,  752, 1459, 1202,
 /*    20 */  1474, 1582, 1599, 1618, 1692, 1714, 1729, 1800, 1835, 1906,
 /*    30 */  1930, 1973, 2038, 2055, 2071, 2148, 2166, 2182, 2259, 2275,
 /*    40 */  2291, 2358, 2384, 2427, 2464, 2494, 2559, 2577, 2593, 2670,
 /*    50 */  2686, -340, -208, -402,  -33,  108,  572,  685,  692,   59,
 /*    60 */   143,  821,  744, -477,  -93,  430,  863, -440,  -27, -388,
 /*    70 */  -244, -216,  411, -360, -282, -372, -332,  318, -220, -176,
 /*    80 */  -108,  -90,  429,  529,  552, -335,  150,  563,  634,  648,
 /*    90 */   650,  177,  186, -162,  656,  659,  401, -393,  661,  284,
 /*   100 */   671,  433,  699,  710, -387,  723,  727,  608,  754,  680,
 /*   110 */   742,  761,  791,  282, -431, -431, -366,  -29, -138,  204,
 /*   120 */   263,  264,  347,  445,  516,  519,  539,  547,  623,  653,
 /*   130 */   675,  700,  764,  772,  808,  816,  847, -293, -167,  336,
 /*   140 */   -20,  565,  601,  567, -167,   -1,  160,  527,  340,  369,
 /*   150 */   216,  652,  660,  311,  304,  713,  604,  655,  735,  759,
 /*   160 */   756,  776,  826,  827,  299,  316,  365,  375,  450,  468,
 /*   170 */   484,  450,  120,  573,  798,  878,  666,  690,  825,  913,
 /*   180 */   926,  926,  953,  957,  922,  994,  952,  895,  899,  900,
 /*   190 */   970,  905,  926, 1035,  988, 1054, 1016,  986, 1004, 1009,
 /*   200 */   926,  943,  943,  927,  943,  959,  950, 1041, 1008,  991,
 /*   210 */   995, 1007, 1000, 1073, 1010, 1075, 1018, 1090, 1092, 1045,
 /*   220 */  1095, 1047, 1052, 1124, 1125, 1127, 1079, 1081, 1084, 1087,
 /*   230 */  1112, 1134, 1144, 1140, 1152, 1153, 1157, 1166, 1163, 1169,
 /*   240 */  1167, 1089, 1158, 1159, 1123, 1165, 1170, 1107, 1173, 1174,
 /*   250 */  1175, 1121, 1176, 1178, 1179, 1180, 1187, 1177, 1181, 1183,
 /*   260 */  1184, 1186, 1188, 1189, 1190, 1191, 1192, 1193, 1194, 1200,
 /*   270 */  1201, 1203, 1142, 1185, 1196, 1101, 1120, 1126, 1197, 1130,
 /*   280 */  1128, 1136, 1182, 1209, 1204, 1227, 1198, 1103, 1195, 1108,
 /*   290 */  1206, 1104, 1111, 1109, 1116, 1129, 1122, 1207, 1102, 1138,
 /*   300 */  1113,  943, 1265, 1199, 1212, 1155, 1278, 1274, 1276, 1223,
 /*   310 */  1244, 1258, 1260, 1266, 1229, 1267, 1241, 1295, 1285, 1296,
 /*   320 */  1317, 1208, 1273, 1271, 1319, 1308, 1339, 1340, 1345, 1268,
 /*   330 */  1256, 1283, 1290, 1322, 1326, 1329, 1346, 1362,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    10 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    20 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    30 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    40 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    50 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    60 */  1908, 2249, 1908, 1908, 2212, 1908, 1908, 1908, 1908, 1908,
 /*    70 */  1908, 1908, 1908, 1908, 1908, 1908, 2219, 1908, 1908, 1908,
 /*    80 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*    90 */  1908, 1908, 1908, 1908, 1908, 1908, 2007, 1908, 1908, 1908,
 /*   100 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   110 */  1908, 1908, 1908, 2005, 2452, 1908, 1908, 1908, 1908, 1908,
 /*   120 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   130 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 2464, 1908,
 /*   140 */  1908, 1979, 1979, 1908, 2464, 2464, 2464, 2005, 2424, 2424,
 /*   150 */  1908, 1908, 2007, 2287, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   160 */  1908, 1908, 2131, 1938, 1908, 1908, 1908, 1908, 2155, 1908,
 /*   170 */  1908, 1908, 2275, 1908, 1908, 2493, 2555, 1908, 2496, 1908,
 /*   180 */  1908, 1908, 1908, 1908, 2224, 1908, 2483, 1908, 1908, 1908,
 /*   190 */  1908, 1908, 1908, 1908, 1908, 1908, 2083, 2269, 1908, 1908,
 /*   200 */  1908, 2456, 2470, 2539, 2457, 2454, 2477, 1908, 2487, 1908,
 /*   210 */  2312, 1908, 2301, 2007, 1908, 2007, 2262, 2207, 1908, 2217,
 /*   220 */  1908, 2217, 2214, 1908, 1908, 1908, 2217, 2214, 2214, 2214,
 /*   230 */  2072, 2068, 1908, 2066, 1908, 1908, 1908, 1908, 1963, 1908,
 /*   240 */  1963, 1908, 2007, 2007, 1908, 2007, 1908, 1908, 2007, 1908,
 /*   250 */  2007, 1908, 2007, 2007, 1908, 2007, 1908, 1908, 1908, 1908,
 /*   260 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   270 */  1908, 1908, 1908, 1908, 1908, 2299, 2285, 1908, 2005, 1908,
 /*   280 */  2273, 2271, 1908, 2005, 2487, 1908, 1908, 2509, 2504, 2509,
 /*   290 */  2504, 2523, 2519, 2509, 2528, 2525, 2489, 2487, 2558, 2545,
 /*   300 */  2541, 2470, 1908, 1908, 2475, 2473, 1908, 2005, 2005, 2504,
 /*   310 */  1908, 1908, 1908, 1908, 2504, 1908, 1908, 2005, 1908, 2005,
 /*   320 */  1908, 1908, 2099, 1908, 1908, 2005, 1908, 1947, 1908, 2264,
 /*   330 */  2290, 2245, 2245, 2134, 2134, 2134, 2008, 1913, 1908, 1908,
 /*   340 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   350 */  2522, 2521, 2377, 1908, 2428, 2427, 2426, 2417, 2376, 2095,
 /*   360 */  1908, 1908, 2375, 2374, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   370 */  1908, 1908, 1908, 2236, 2235, 2368, 1908, 1908, 2369, 2367,
 /*   380 */  2366, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   390 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   400 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 2542, 2546, 1908,
 /*   410 */  1908, 1908, 1908, 1908, 1908, 2453, 1908, 1908, 1908, 2348,
 /*   420 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   430 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   440 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   450 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   460 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   470 */  1908, 1908, 1908, 1908, 2213, 1908, 1908, 1908, 1908, 1908,
 /*   480 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   490 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   500 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   510 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   520 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   530 */  1908, 1908, 1908, 1908, 1908, 1908, 2228, 1908, 1908, 1908,
 /*   540 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   550 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   560 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1952, 2355,
 /*   570 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   580 */  1908, 1908, 1908, 2358, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   590 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   600 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   610 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   620 */  1908, 1908, 1908, 1908, 2047, 2046, 1908, 1908, 1908, 1908,
 /*   630 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   640 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   650 */  1908, 1908, 2359, 1908, 1908, 1908, 1908, 1908, 2350, 1908,
 /*   660 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   670 */  1908, 1908, 1908, 1908, 1908, 2538, 2490, 1908, 1908, 1908,
 /*   680 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   690 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 2348,
 /*   700 */  1908, 2520, 1908, 1908, 2536, 1908, 2540, 1908, 1908, 1908,
 /*   710 */  1908, 1908, 1908, 1908, 2463, 2459, 1908, 1908, 2455, 1908,
 /*   720 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   730 */  1908, 1908, 1908, 1908, 1908, 1908, 2347, 1908, 2414, 1908,
 /*   740 */  1908, 1908, 2448, 1908, 1908, 2399, 1908, 1908, 1908, 1908,
 /*   750 */  1908, 1908, 1908, 1908, 1908, 2359, 1908, 2362, 1908, 1908,
 /*   760 */  1908, 1908, 1908, 2128, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   770 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 2112,
 /*   780 */  2110, 2109, 2108, 1908, 2105, 1908, 2141, 1908, 1908, 1908,
 /*   790 */  2137, 2136, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   800 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 2026, 1908,
 /*   810 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 2018, 1908, 2017,
 /*   820 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   830 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908, 1908,
 /*   840 */  1908, 1908, 1908, 1908, 1908, 1908, 1908, 1937, 1908, 1908,
 /*   850 */  1908, 1908, 1908, 1908,
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
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*      UNION => nothing */
    0,  /*        ALL => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     EXCEPT => nothing */
    0,  /*  INTERSECT => nothing */
    0,  /*  NK_BITAND => nothing */
    0,  /*   NK_BITOR => nothing */
    0,  /*  NK_LSHIFT => nothing */
    0,  /*  NK_RSHIFT => nothing */
    0,  /*    NK_PLUS => nothing */
    0,  /*   NK_MINUS => nothing */
    0,  /*    NK_STAR => nothing */
    0,  /*   NK_SLASH => nothing */
    0,  /*     NK_REM => nothing */
    0,  /*  NK_CONCAT => nothing */
    0,  /*     CREATE => nothing */
    0,  /*    ACCOUNT => nothing */
    0,  /*      NK_ID => nothing */
    0,  /*       PASS => nothing */
    0,  /*  NK_STRING => nothing */
    0,  /*      ALTER => nothing */
    0,  /*        PPS => nothing */
    0,  /*    TSERIES => nothing */
    0,  /*    STORAGE => nothing */
    0,  /*    STREAMS => nothing */
    0,  /*      QTIME => nothing */
    0,  /*        DBS => nothing */
    0,  /*      USERS => nothing */
    0,  /*      CONNS => nothing */
    0,  /*      STATE => nothing */
    0,  /*   NK_COMMA => nothing */
    0,  /*       HOST => nothing */
    0,  /*       USER => nothing */
    0,  /*     ENABLE => nothing */
    0,  /* NK_INTEGER => nothing */
    0,  /*    SYSINFO => nothing */
    0,  /*        ADD => nothing */
    0,  /*       DROP => nothing */
    0,  /*      GRANT => nothing */
    0,  /*         ON => nothing */
    0,  /*         TO => nothing */
    0,  /*     REVOKE => nothing */
    0,  /*       FROM => nothing */
    0,  /*  SUBSCRIBE => nothing */
    0,  /*       READ => nothing */
    0,  /*      WRITE => nothing */
    0,  /*     NK_DOT => nothing */
    0,  /*       WITH => nothing */
    0,  /*      DNODE => nothing */
    0,  /*       PORT => nothing */
    0,  /*     DNODES => nothing */
    0,  /*    RESTORE => nothing */
    0,  /* NK_IPTOKEN => nothing */
    0,  /*      FORCE => nothing */
    0,  /*     UNSAFE => nothing */
    0,  /*    CLUSTER => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*      QNODE => nothing */
    0,  /*      BNODE => nothing */
    0,  /*      SNODE => nothing */
    0,  /*      MNODE => nothing */
    0,  /*      VNODE => nothing */
    0,  /*   DATABASE => nothing */
    0,  /*        USE => nothing */
    0,  /*      FLUSH => nothing */
    0,  /*       TRIM => nothing */
    0,  /*    COMPACT => nothing */
    0,  /*         IF => nothing */
    0,  /*        NOT => nothing */
    0,  /*     EXISTS => nothing */
    0,  /*     BUFFER => nothing */
    0,  /* CACHEMODEL => nothing */
    0,  /*  CACHESIZE => nothing */
    0,  /*       COMP => nothing */
    0,  /*   DURATION => nothing */
    0,  /* NK_VARIABLE => nothing */
    0,  /*    MAXROWS => nothing */
    0,  /*    MINROWS => nothing */
    0,  /*       KEEP => nothing */
    0,  /*      PAGES => nothing */
    0,  /*   PAGESIZE => nothing */
    0,  /* TSDB_PAGESIZE => nothing */
    0,  /*  PRECISION => nothing */
    0,  /*    REPLICA => nothing */
    0,  /*    VGROUPS => nothing */
    0,  /* SINGLE_STABLE => nothing */
    0,  /* RETENTIONS => nothing */
    0,  /* SCHEMALESS => nothing */
    0,  /*  WAL_LEVEL => nothing */
    0,  /* WAL_FSYNC_PERIOD => nothing */
    0,  /* WAL_RETENTION_PERIOD => nothing */
    0,  /* WAL_RETENTION_SIZE => nothing */
    0,  /* WAL_ROLL_PERIOD => nothing */
    0,  /* WAL_SEGMENT_SIZE => nothing */
    0,  /* STT_TRIGGER => nothing */
    0,  /* TABLE_PREFIX => nothing */
    0,  /* TABLE_SUFFIX => nothing */
    0,  /* KEEP_TIME_OFFSET => nothing */
    0,  /*   NK_COLON => nothing */
    0,  /*    BWLIMIT => nothing */
    0,  /*      START => nothing */
    0,  /*  TIMESTAMP => nothing */
  303,  /*        END => ABORT */
    0,  /*      TABLE => nothing */
    0,  /*      NK_LP => nothing */
    0,  /*      NK_RP => nothing */
    0,  /*     STABLE => nothing */
    0,  /*     COLUMN => nothing */
    0,  /*     MODIFY => nothing */
    0,  /*     RENAME => nothing */
    0,  /*        TAG => nothing */
    0,  /*        SET => nothing */
    0,  /*      NK_EQ => nothing */
    0,  /*      USING => nothing */
    0,  /*       TAGS => nothing */
    0,  /*    PRIMARY => nothing */
  303,  /*        KEY => ABORT */
    0,  /*       BOOL => nothing */
    0,  /*    TINYINT => nothing */
    0,  /*   SMALLINT => nothing */
    0,  /*        INT => nothing */
    0,  /*    INTEGER => nothing */
    0,  /*     BIGINT => nothing */
    0,  /*      FLOAT => nothing */
    0,  /*     DOUBLE => nothing */
    0,  /*     BINARY => nothing */
    0,  /*      NCHAR => nothing */
    0,  /*   UNSIGNED => nothing */
    0,  /*       JSON => nothing */
    0,  /*    VARCHAR => nothing */
    0,  /* MEDIUMBLOB => nothing */
    0,  /*       BLOB => nothing */
    0,  /*  VARBINARY => nothing */
    0,  /*   GEOMETRY => nothing */
    0,  /*    DECIMAL => nothing */
    0,  /*    COMMENT => nothing */
    0,  /*  MAX_DELAY => nothing */
    0,  /*  WATERMARK => nothing */
    0,  /*     ROLLUP => nothing */
    0,  /*        TTL => nothing */
    0,  /*        SMA => nothing */
    0,  /* DELETE_MARK => nothing */
    0,  /*      FIRST => nothing */
    0,  /*       LAST => nothing */
    0,  /*       SHOW => nothing */
    0,  /* PRIVILEGES => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*     TABLES => nothing */
    0,  /*    STABLES => nothing */
    0,  /*     MNODES => nothing */
    0,  /*     QNODES => nothing */
    0,  /*  ARBGROUPS => nothing */
    0,  /*  FUNCTIONS => nothing */
    0,  /*    INDEXES => nothing */
    0,  /*   ACCOUNTS => nothing */
    0,  /*       APPS => nothing */
    0,  /* CONNECTIONS => nothing */
    0,  /*   LICENCES => nothing */
    0,  /*     GRANTS => nothing */
    0,  /*       FULL => nothing */
    0,  /*       LOGS => nothing */
    0,  /*   MACHINES => nothing */
    0,  /*    QUERIES => nothing */
    0,  /*     SCORES => nothing */
    0,  /*     TOPICS => nothing */
    0,  /*  VARIABLES => nothing */
    0,  /*     BNODES => nothing */
    0,  /*     SNODES => nothing */
    0,  /* TRANSACTIONS => nothing */
    0,  /* DISTRIBUTED => nothing */
    0,  /*  CONSUMERS => nothing */
    0,  /* SUBSCRIPTIONS => nothing */
    0,  /*     VNODES => nothing */
    0,  /*      ALIVE => nothing */
    0,  /*      VIEWS => nothing */
  303,  /*       VIEW => ABORT */
    0,  /*   COMPACTS => nothing */
    0,  /*     NORMAL => nothing */
    0,  /*      CHILD => nothing */
    0,  /*       LIKE => nothing */
    0,  /*     TBNAME => nothing */
    0,  /*      QTAGS => nothing */
    0,  /*         AS => nothing */
    0,  /*     SYSTEM => nothing */
    0,  /*      INDEX => nothing */
    0,  /*   FUNCTION => nothing */
    0,  /*   INTERVAL => nothing */
    0,  /*      COUNT => nothing */
    0,  /*   LAST_ROW => nothing */
    0,  /*       META => nothing */
    0,  /*       ONLY => nothing */
    0,  /*      TOPIC => nothing */
    0,  /*   CONSUMER => nothing */
    0,  /*      GROUP => nothing */
    0,  /*       DESC => nothing */
    0,  /*   DESCRIBE => nothing */
    0,  /*      RESET => nothing */
    0,  /*      QUERY => nothing */
    0,  /*      CACHE => nothing */
    0,  /*    EXPLAIN => nothing */
    0,  /*    ANALYZE => nothing */
    0,  /*    VERBOSE => nothing */
    0,  /*    NK_BOOL => nothing */
    0,  /*      RATIO => nothing */
    0,  /*   NK_FLOAT => nothing */
    0,  /* OUTPUTTYPE => nothing */
    0,  /*  AGGREGATE => nothing */
    0,  /*    BUFSIZE => nothing */
    0,  /*   LANGUAGE => nothing */
    0,  /*    REPLACE => nothing */
    0,  /*     STREAM => nothing */
    0,  /*       INTO => nothing */
    0,  /*      PAUSE => nothing */
    0,  /*     RESUME => nothing */
    0,  /*    TRIGGER => nothing */
    0,  /*    AT_ONCE => nothing */
    0,  /* WINDOW_CLOSE => nothing */
    0,  /*     IGNORE => nothing */
    0,  /*    EXPIRED => nothing */
    0,  /* FILL_HISTORY => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*   SUBTABLE => nothing */
    0,  /*  UNTREATED => nothing */
    0,  /*       KILL => nothing */
    0,  /* CONNECTION => nothing */
    0,  /* TRANSACTION => nothing */
    0,  /*    BALANCE => nothing */
    0,  /*     VGROUP => nothing */
    0,  /*     LEADER => nothing */
    0,  /*      MERGE => nothing */
    0,  /* REDISTRIBUTE => nothing */
    0,  /*      SPLIT => nothing */
    0,  /*     DELETE => nothing */
    0,  /*     INSERT => nothing */
    0,  /*     NK_BIN => nothing */
    0,  /*     NK_HEX => nothing */
    0,  /*       NULL => nothing */
    0,  /* NK_QUESTION => nothing */
    0,  /*   NK_ALIAS => nothing */
    0,  /*   NK_ARROW => nothing */
    0,  /*      ROWTS => nothing */
    0,  /*     QSTART => nothing */
    0,  /*       QEND => nothing */
    0,  /*  QDURATION => nothing */
    0,  /*     WSTART => nothing */
    0,  /*       WEND => nothing */
    0,  /*  WDURATION => nothing */
    0,  /*     IROWTS => nothing */
    0,  /*   ISFILLED => nothing */
    0,  /*       CAST => nothing */
    0,  /*        NOW => nothing */
    0,  /*      TODAY => nothing */
    0,  /*   TIMEZONE => nothing */
    0,  /* CLIENT_VERSION => nothing */
    0,  /* SERVER_VERSION => nothing */
    0,  /* SERVER_STATUS => nothing */
    0,  /* CURRENT_USER => nothing */
    0,  /*       CASE => nothing */
    0,  /*       WHEN => nothing */
    0,  /*       THEN => nothing */
    0,  /*       ELSE => nothing */
    0,  /*    BETWEEN => nothing */
    0,  /*         IS => nothing */
    0,  /*      NK_LT => nothing */
    0,  /*      NK_GT => nothing */
    0,  /*      NK_LE => nothing */
    0,  /*      NK_GE => nothing */
    0,  /*      NK_NE => nothing */
    0,  /*      MATCH => nothing */
    0,  /*     NMATCH => nothing */
    0,  /*   CONTAINS => nothing */
    0,  /*         IN => nothing */
    0,  /*       JOIN => nothing */
    0,  /*      INNER => nothing */
    0,  /*     SELECT => nothing */
    0,  /*    NK_HINT => nothing */
    0,  /*   DISTINCT => nothing */
    0,  /*      WHERE => nothing */
    0,  /*  PARTITION => nothing */
    0,  /*         BY => nothing */
    0,  /*    SESSION => nothing */
    0,  /* STATE_WINDOW => nothing */
    0,  /* EVENT_WINDOW => nothing */
    0,  /* COUNT_WINDOW => nothing */
    0,  /*    SLIDING => nothing */
    0,  /*       FILL => nothing */
    0,  /*      VALUE => nothing */
    0,  /*    VALUE_F => nothing */
    0,  /*       NONE => nothing */
    0,  /*       PREV => nothing */
    0,  /*     NULL_F => nothing */
    0,  /*     LINEAR => nothing */
    0,  /*       NEXT => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      RANGE => nothing */
    0,  /*      EVERY => nothing */
    0,  /*      ORDER => nothing */
    0,  /*     SLIMIT => nothing */
    0,  /*    SOFFSET => nothing */
    0,  /*      LIMIT => nothing */
    0,  /*     OFFSET => nothing */
    0,  /*        ASC => nothing */
    0,  /*      NULLS => nothing */
    0,  /*      ABORT => nothing */
  303,  /*      AFTER => ABORT */
  303,  /*     ATTACH => ABORT */
  303,  /*     BEFORE => ABORT */
  303,  /*      BEGIN => ABORT */
  303,  /*     BITAND => ABORT */
  303,  /*     BITNOT => ABORT */
  303,  /*      BITOR => ABORT */
  303,  /*     BLOCKS => ABORT */
  303,  /*     CHANGE => ABORT */
  303,  /*      COMMA => ABORT */
  303,  /*     CONCAT => ABORT */
  303,  /*   CONFLICT => ABORT */
  303,  /*       COPY => ABORT */
  303,  /*   DEFERRED => ABORT */
  303,  /* DELIMITERS => ABORT */
  303,  /*     DETACH => ABORT */
  303,  /*     DIVIDE => ABORT */
  303,  /*        DOT => ABORT */
  303,  /*       EACH => ABORT */
  303,  /*       FAIL => ABORT */
  303,  /*       FILE => ABORT */
  303,  /*        FOR => ABORT */
  303,  /*       GLOB => ABORT */
  303,  /*         ID => ABORT */
  303,  /*  IMMEDIATE => ABORT */
  303,  /*     IMPORT => ABORT */
  303,  /*  INITIALLY => ABORT */
  303,  /*    INSTEAD => ABORT */
  303,  /*     ISNULL => ABORT */
  303,  /*    MODULES => ABORT */
  303,  /*  NK_BITNOT => ABORT */
  303,  /*    NK_SEMI => ABORT */
  303,  /*    NOTNULL => ABORT */
  303,  /*         OF => ABORT */
  303,  /*       PLUS => ABORT */
  303,  /*  PRIVILEGE => ABORT */
  303,  /*      RAISE => ABORT */
  303,  /*   RESTRICT => ABORT */
  303,  /*        ROW => ABORT */
  303,  /*       SEMI => ABORT */
  303,  /*       STAR => ABORT */
  303,  /*  STATEMENT => ABORT */
  303,  /*     STRICT => ABORT */
  303,  /*     STRING => ABORT */
  303,  /*      TIMES => ABORT */
  303,  /*     VALUES => ABORT */
  303,  /*   VARIABLE => ABORT */
  303,  /*        WAL => ABORT */
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
  ParseCTX_SDECL                /* A place to hold %extra_context */
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
  /*    1 */ "OR",
  /*    2 */ "AND",
  /*    3 */ "UNION",
  /*    4 */ "ALL",
  /*    5 */ "MINUS",
  /*    6 */ "EXCEPT",
  /*    7 */ "INTERSECT",
  /*    8 */ "NK_BITAND",
  /*    9 */ "NK_BITOR",
  /*   10 */ "NK_LSHIFT",
  /*   11 */ "NK_RSHIFT",
  /*   12 */ "NK_PLUS",
  /*   13 */ "NK_MINUS",
  /*   14 */ "NK_STAR",
  /*   15 */ "NK_SLASH",
  /*   16 */ "NK_REM",
  /*   17 */ "NK_CONCAT",
  /*   18 */ "CREATE",
  /*   19 */ "ACCOUNT",
  /*   20 */ "NK_ID",
  /*   21 */ "PASS",
  /*   22 */ "NK_STRING",
  /*   23 */ "ALTER",
  /*   24 */ "PPS",
  /*   25 */ "TSERIES",
  /*   26 */ "STORAGE",
  /*   27 */ "STREAMS",
  /*   28 */ "QTIME",
  /*   29 */ "DBS",
  /*   30 */ "USERS",
  /*   31 */ "CONNS",
  /*   32 */ "STATE",
  /*   33 */ "NK_COMMA",
  /*   34 */ "HOST",
  /*   35 */ "USER",
  /*   36 */ "ENABLE",
  /*   37 */ "NK_INTEGER",
  /*   38 */ "SYSINFO",
  /*   39 */ "ADD",
  /*   40 */ "DROP",
  /*   41 */ "GRANT",
  /*   42 */ "ON",
  /*   43 */ "TO",
  /*   44 */ "REVOKE",
  /*   45 */ "FROM",
  /*   46 */ "SUBSCRIBE",
  /*   47 */ "READ",
  /*   48 */ "WRITE",
  /*   49 */ "NK_DOT",
  /*   50 */ "WITH",
  /*   51 */ "DNODE",
  /*   52 */ "PORT",
  /*   53 */ "DNODES",
  /*   54 */ "RESTORE",
  /*   55 */ "NK_IPTOKEN",
  /*   56 */ "FORCE",
  /*   57 */ "UNSAFE",
  /*   58 */ "CLUSTER",
  /*   59 */ "LOCAL",
  /*   60 */ "QNODE",
  /*   61 */ "BNODE",
  /*   62 */ "SNODE",
  /*   63 */ "MNODE",
  /*   64 */ "VNODE",
  /*   65 */ "DATABASE",
  /*   66 */ "USE",
  /*   67 */ "FLUSH",
  /*   68 */ "TRIM",
  /*   69 */ "COMPACT",
  /*   70 */ "IF",
  /*   71 */ "NOT",
  /*   72 */ "EXISTS",
  /*   73 */ "BUFFER",
  /*   74 */ "CACHEMODEL",
  /*   75 */ "CACHESIZE",
  /*   76 */ "COMP",
  /*   77 */ "DURATION",
  /*   78 */ "NK_VARIABLE",
  /*   79 */ "MAXROWS",
  /*   80 */ "MINROWS",
  /*   81 */ "KEEP",
  /*   82 */ "PAGES",
  /*   83 */ "PAGESIZE",
  /*   84 */ "TSDB_PAGESIZE",
  /*   85 */ "PRECISION",
  /*   86 */ "REPLICA",
  /*   87 */ "VGROUPS",
  /*   88 */ "SINGLE_STABLE",
  /*   89 */ "RETENTIONS",
  /*   90 */ "SCHEMALESS",
  /*   91 */ "WAL_LEVEL",
  /*   92 */ "WAL_FSYNC_PERIOD",
  /*   93 */ "WAL_RETENTION_PERIOD",
  /*   94 */ "WAL_RETENTION_SIZE",
  /*   95 */ "WAL_ROLL_PERIOD",
  /*   96 */ "WAL_SEGMENT_SIZE",
  /*   97 */ "STT_TRIGGER",
  /*   98 */ "TABLE_PREFIX",
  /*   99 */ "TABLE_SUFFIX",
  /*  100 */ "KEEP_TIME_OFFSET",
  /*  101 */ "NK_COLON",
  /*  102 */ "BWLIMIT",
  /*  103 */ "START",
  /*  104 */ "TIMESTAMP",
  /*  105 */ "END",
  /*  106 */ "TABLE",
  /*  107 */ "NK_LP",
  /*  108 */ "NK_RP",
  /*  109 */ "STABLE",
  /*  110 */ "COLUMN",
  /*  111 */ "MODIFY",
  /*  112 */ "RENAME",
  /*  113 */ "TAG",
  /*  114 */ "SET",
  /*  115 */ "NK_EQ",
  /*  116 */ "USING",
  /*  117 */ "TAGS",
  /*  118 */ "PRIMARY",
  /*  119 */ "KEY",
  /*  120 */ "BOOL",
  /*  121 */ "TINYINT",
  /*  122 */ "SMALLINT",
  /*  123 */ "INT",
  /*  124 */ "INTEGER",
  /*  125 */ "BIGINT",
  /*  126 */ "FLOAT",
  /*  127 */ "DOUBLE",
  /*  128 */ "BINARY",
  /*  129 */ "NCHAR",
  /*  130 */ "UNSIGNED",
  /*  131 */ "JSON",
  /*  132 */ "VARCHAR",
  /*  133 */ "MEDIUMBLOB",
  /*  134 */ "BLOB",
  /*  135 */ "VARBINARY",
  /*  136 */ "GEOMETRY",
  /*  137 */ "DECIMAL",
  /*  138 */ "COMMENT",
  /*  139 */ "MAX_DELAY",
  /*  140 */ "WATERMARK",
  /*  141 */ "ROLLUP",
  /*  142 */ "TTL",
  /*  143 */ "SMA",
  /*  144 */ "DELETE_MARK",
  /*  145 */ "FIRST",
  /*  146 */ "LAST",
  /*  147 */ "SHOW",
  /*  148 */ "PRIVILEGES",
  /*  149 */ "DATABASES",
  /*  150 */ "TABLES",
  /*  151 */ "STABLES",
  /*  152 */ "MNODES",
  /*  153 */ "QNODES",
  /*  154 */ "FUNCTIONS",
  /*  155 */ "INDEXES",
  /*  156 */ "ACCOUNTS",
  /*  157 */ "APPS",
  /*  158 */ "CONNECTIONS",
  /*  159 */ "LICENCES",
  /*  160 */ "GRANTS",
  /*  161 */ "FULL",
  /*  162 */ "LOGS",
  /*  163 */ "MACHINES",
  /*  164 */ "QUERIES",
  /*  165 */ "SCORES",
  /*  166 */ "TOPICS",
  /*  167 */ "VARIABLES",
  /*  168 */ "BNODES",
  /*  169 */ "SNODES",
  /*  170 */ "TRANSACTIONS",
  /*  171 */ "DISTRIBUTED",
  /*  172 */ "CONSUMERS",
  /*  173 */ "SUBSCRIPTIONS",
  /*  174 */ "VNODES",
  /*  175 */ "ALIVE",
  /*  176 */ "VIEWS",
  /*  177 */ "VIEW",
  /*  178 */ "COMPACTS",
  /*  179 */ "NORMAL",
  /*  180 */ "CHILD",
  /*  181 */ "LIKE",
  /*  182 */ "TBNAME",
  /*  183 */ "QTAGS",
  /*  184 */ "AS",
  /*  185 */ "SYSTEM",
  /*  186 */ "INDEX",
  /*  187 */ "FUNCTION",
  /*  188 */ "INTERVAL",
  /*  189 */ "COUNT",
  /*  190 */ "LAST_ROW",
  /*  191 */ "META",
  /*  192 */ "ONLY",
  /*  193 */ "TOPIC",
  /*  194 */ "CONSUMER",
  /*  195 */ "GROUP",
  /*  196 */ "DESC",
  /*  197 */ "DESCRIBE",
  /*  198 */ "RESET",
  /*  199 */ "QUERY",
  /*  200 */ "CACHE",
  /*  201 */ "EXPLAIN",
  /*  202 */ "ANALYZE",
  /*  203 */ "VERBOSE",
  /*  204 */ "NK_BOOL",
  /*  205 */ "RATIO",
  /*  206 */ "NK_FLOAT",
  /*  207 */ "OUTPUTTYPE",
  /*  208 */ "AGGREGATE",
  /*  209 */ "BUFSIZE",
  /*  210 */ "LANGUAGE",
  /*  211 */ "REPLACE",
  /*  212 */ "STREAM",
  /*  213 */ "INTO",
  /*  214 */ "PAUSE",
  /*  215 */ "RESUME",
  /*  216 */ "TRIGGER",
  /*  217 */ "AT_ONCE",
  /*  218 */ "WINDOW_CLOSE",
  /*  219 */ "IGNORE",
  /*  220 */ "EXPIRED",
  /*  221 */ "FILL_HISTORY",
  /*  222 */ "UPDATE",
  /*  223 */ "SUBTABLE",
  /*  224 */ "UNTREATED",
  /*  225 */ "KILL",
  /*  226 */ "CONNECTION",
  /*  227 */ "TRANSACTION",
  /*  228 */ "BALANCE",
  /*  229 */ "VGROUP",
  /*  230 */ "LEADER",
  /*  231 */ "MERGE",
  /*  232 */ "REDISTRIBUTE",
  /*  233 */ "SPLIT",
  /*  234 */ "DELETE",
  /*  235 */ "INSERT",
  /*  236 */ "NULL",
  /*  237 */ "NK_QUESTION",
  /*  238 */ "NK_ALIAS",
  /*  239 */ "NK_ARROW",
  /*  240 */ "ROWTS",
  /*  241 */ "QSTART",
  /*  242 */ "QEND",
  /*  243 */ "QDURATION",
  /*  244 */ "WSTART",
  /*  245 */ "WEND",
  /*  246 */ "WDURATION",
  /*  247 */ "IROWTS",
  /*  248 */ "ISFILLED",
  /*  249 */ "CAST",
  /*  250 */ "NOW",
  /*  251 */ "TODAY",
  /*  252 */ "TIMEZONE",
  /*  253 */ "CLIENT_VERSION",
  /*  254 */ "SERVER_VERSION",
  /*  255 */ "SERVER_STATUS",
  /*  256 */ "CURRENT_USER",
  /*  257 */ "CASE",
  /*  258 */ "WHEN",
  /*  259 */ "THEN",
  /*  260 */ "ELSE",
  /*  261 */ "BETWEEN",
  /*  262 */ "IS",
  /*  263 */ "NK_LT",
  /*  264 */ "NK_GT",
  /*  265 */ "NK_LE",
  /*  266 */ "NK_GE",
  /*  267 */ "NK_NE",
  /*  268 */ "MATCH",
  /*  269 */ "NMATCH",
  /*  270 */ "CONTAINS",
  /*  271 */ "IN",
  /*  272 */ "JOIN",
  /*  273 */ "INNER",
  /*  274 */ "SELECT",
  /*  275 */ "NK_HINT",
  /*  276 */ "DISTINCT",
  /*  277 */ "WHERE",
  /*  278 */ "PARTITION",
  /*  279 */ "BY",
  /*  280 */ "SESSION",
  /*  281 */ "STATE_WINDOW",
  /*  282 */ "EVENT_WINDOW",
  /*  283 */ "COUNT_WINDOW",
  /*  284 */ "SLIDING",
  /*  285 */ "FILL",
  /*  286 */ "VALUE",
  /*  287 */ "VALUE_F",
  /*  288 */ "NONE",
  /*  289 */ "PREV",
  /*  290 */ "NULL_F",
  /*  291 */ "LINEAR",
  /*  292 */ "NEXT",
  /*  293 */ "HAVING",
  /*  294 */ "RANGE",
  /*  295 */ "EVERY",
  /*  296 */ "ORDER",
  /*  297 */ "SLIMIT",
  /*  298 */ "SOFFSET",
  /*  299 */ "LIMIT",
  /*  300 */ "OFFSET",
  /*  301 */ "ASC",
  /*  302 */ "NULLS",
  /*  303 */ "ABORT",
  /*  304 */ "AFTER",
  /*  305 */ "ATTACH",
  /*  306 */ "BEFORE",
  /*  307 */ "BEGIN",
  /*  308 */ "BITAND",
  /*  309 */ "BITNOT",
  /*  310 */ "BITOR",
  /*  311 */ "BLOCKS",
  /*  312 */ "CHANGE",
  /*  313 */ "COMMA",
  /*  314 */ "CONCAT",
  /*  315 */ "CONFLICT",
  /*  316 */ "COPY",
  /*  317 */ "DEFERRED",
  /*  318 */ "DELIMITERS",
  /*  319 */ "DETACH",
  /*  320 */ "DIVIDE",
  /*  321 */ "DOT",
  /*  322 */ "EACH",
  /*  323 */ "FAIL",
  /*  324 */ "FILE",
  /*  325 */ "FOR",
  /*  326 */ "GLOB",
  /*  327 */ "ID",
  /*  328 */ "IMMEDIATE",
  /*  329 */ "IMPORT",
  /*  330 */ "INITIALLY",
  /*  331 */ "INSTEAD",
  /*  332 */ "ISNULL",
  /*  333 */ "MODULES",
  /*  334 */ "NK_BITNOT",
  /*  335 */ "NK_SEMI",
  /*  336 */ "NOTNULL",
  /*  337 */ "OF",
  /*  338 */ "PLUS",
  /*  339 */ "PRIVILEGE",
  /*  340 */ "RAISE",
  /*  341 */ "RESTRICT",
  /*  342 */ "ROW",
  /*  343 */ "SEMI",
  /*  344 */ "STAR",
  /*  345 */ "STATEMENT",
  /*  346 */ "STRICT",
  /*  347 */ "STRING",
  /*  348 */ "TIMES",
  /*  349 */ "VALUES",
  /*  350 */ "VARIABLE",
  /*  351 */ "WAL",
  /*  352 */ "cmd",
  /*  353 */ "account_options",
  /*  354 */ "alter_account_options",
  /*  355 */ "literal",
  /*  356 */ "alter_account_option",
  /*  357 */ "ip_range_list",
  /*  358 */ "white_list",
  /*  359 */ "white_list_opt",
  /*  360 */ "user_name",
  /*  361 */ "sysinfo_opt",
  /*  362 */ "privileges",
  /*  363 */ "priv_level",
  /*  364 */ "with_opt",
  /*  365 */ "priv_type_list",
  /*  366 */ "priv_type",
  /*  367 */ "db_name",
  /*  368 */ "table_name",
  /*  369 */ "topic_name",
  /*  370 */ "search_condition",
  /*  371 */ "dnode_endpoint",
  /*  372 */ "force_opt",
  /*  373 */ "unsafe_opt",
  /*  374 */ "not_exists_opt",
  /*  375 */ "db_options",
  /*  376 */ "exists_opt",
  /*  377 */ "alter_db_options",
  /*  378 */ "speed_opt",
  /*  379 */ "start_opt",
  /*  380 */ "end_opt",
  /*  381 */ "integer_list",
  /*  382 */ "variable_list",
  /*  383 */ "retention_list",
  /*  384 */ "signed",
  /*  385 */ "alter_db_option",
  /*  386 */ "retention",
  /*  387 */ "full_table_name",
  /*  388 */ "column_def_list",
  /*  389 */ "tags_def_opt",
  /*  390 */ "table_options",
  /*  391 */ "multi_create_clause",
  /*  392 */ "tags_def",
  /*  393 */ "multi_drop_clause",
  /*  394 */ "alter_table_clause",
  /*  395 */ "alter_table_options",
  /*  396 */ "column_name",
  /*  397 */ "type_name",
  /*  398 */ "signed_literal",
  /*  399 */ "create_subtable_clause",
  /*  400 */ "specific_cols_opt",
  /*  401 */ "expression_list",
  /*  402 */ "drop_table_clause",
  /*  403 */ "col_name_list",
  /*  404 */ "column_def",
  /*  405 */ "duration_list",
  /*  406 */ "rollup_func_list",
  /*  407 */ "alter_table_option",
  /*  408 */ "duration_literal",
  /*  409 */ "rollup_func_name",
  /*  410 */ "function_name",
  /*  411 */ "col_name",
  /*  412 */ "db_kind_opt",
  /*  413 */ "table_kind_db_name_cond_opt",
  /*  414 */ "like_pattern_opt",
  /*  415 */ "db_name_cond_opt",
  /*  416 */ "table_name_cond",
  /*  417 */ "from_db_opt",
  /*  418 */ "tag_list_opt",
  /*  419 */ "table_kind",
  /*  420 */ "tag_item",
  /*  421 */ "column_alias",
  /*  422 */ "index_options",
  /*  423 */ "full_index_name",
  /*  424 */ "index_name",
  /*  425 */ "func_list",
  /*  426 */ "sliding_opt",
  /*  427 */ "sma_stream_opt",
  /*  428 */ "func",
  /*  429 */ "sma_func_name",
  /*  430 */ "with_meta",
  /*  431 */ "query_or_subquery",
  /*  432 */ "where_clause_opt",
  /*  433 */ "cgroup_name",
  /*  434 */ "analyze_opt",
  /*  435 */ "explain_options",
  /*  436 */ "insert_query",
  /*  437 */ "or_replace_opt",
  /*  438 */ "agg_func_opt",
  /*  439 */ "bufsize_opt",
  /*  440 */ "language_opt",
  /*  441 */ "full_view_name",
  /*  442 */ "view_name",
  /*  443 */ "stream_name",
  /*  444 */ "stream_options",
  /*  445 */ "col_list_opt",
  /*  446 */ "tag_def_or_ref_opt",
  /*  447 */ "subtable_opt",
  /*  448 */ "ignore_opt",
  /*  449 */ "expression",
  /*  450 */ "on_vgroup_id",
  /*  451 */ "dnode_list",
  /*  452 */ "literal_func",
  /*  453 */ "literal_list",
  /*  454 */ "table_alias",
  /*  455 */ "expr_or_subquery",
  /*  456 */ "pseudo_column",
  /*  457 */ "column_reference",
  /*  458 */ "function_expression",
  /*  459 */ "case_when_expression",
  /*  460 */ "star_func",
  /*  461 */ "star_func_para_list",
  /*  462 */ "noarg_func",
  /*  463 */ "other_para_list",
  /*  464 */ "star_func_para",
  /*  465 */ "when_then_list",
  /*  466 */ "case_when_else_opt",
  /*  467 */ "common_expression",
  /*  468 */ "when_then_expr",
  /*  469 */ "predicate",
  /*  470 */ "compare_op",
  /*  471 */ "in_op",
  /*  472 */ "in_predicate_value",
  /*  473 */ "boolean_value_expression",
  /*  474 */ "boolean_primary",
  /*  475 */ "from_clause_opt",
  /*  476 */ "table_reference_list",
  /*  477 */ "table_reference",
  /*  478 */ "table_primary",
  /*  479 */ "joined_table",
  /*  480 */ "alias_opt",
  /*  481 */ "subquery",
  /*  482 */ "parenthesized_joined_table",
  /*  483 */ "join_type",
  /*  484 */ "query_specification",
  /*  485 */ "hint_list",
  /*  486 */ "set_quantifier_opt",
  /*  487 */ "tag_mode_opt",
  /*  488 */ "select_list",
  /*  489 */ "partition_by_clause_opt",
  /*  490 */ "range_opt",
  /*  491 */ "every_opt",
  /*  492 */ "fill_opt",
  /*  493 */ "twindow_clause_opt",
  /*  494 */ "group_by_clause_opt",
  /*  495 */ "having_clause_opt",
  /*  496 */ "select_item",
  /*  497 */ "partition_list",
  /*  498 */ "partition_item",
  /*  499 */ "interval_sliding_duration_literal",
  /*  500 */ "fill_mode",
  /*  501 */ "group_by_list",
  /*  502 */ "query_expression",
  /*  503 */ "query_simple",
  /*  504 */ "order_by_clause_opt",
  /*  505 */ "slimit_clause_opt",
  /*  506 */ "limit_clause_opt",
  /*  507 */ "union_query_expression",
  /*  508 */ "query_simple_or_subquery",
  /*  509 */ "sort_specification_list",
  /*  510 */ "sort_specification",
  /*  511 */ "ordering_specification_opt",
  /*  512 */ "null_ordering_opt",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "cmd ::= CREATE ACCOUNT NK_ID PASS NK_STRING account_options",
 /*   1 */ "cmd ::= ALTER ACCOUNT NK_ID alter_account_options",
 /*   2 */ "account_options ::=",
 /*   3 */ "account_options ::= account_options PPS literal",
 /*   4 */ "account_options ::= account_options TSERIES literal",
 /*   5 */ "account_options ::= account_options STORAGE literal",
 /*   6 */ "account_options ::= account_options STREAMS literal",
 /*   7 */ "account_options ::= account_options QTIME literal",
 /*   8 */ "account_options ::= account_options DBS literal",
 /*   9 */ "account_options ::= account_options USERS literal",
 /*  10 */ "account_options ::= account_options CONNS literal",
 /*  11 */ "account_options ::= account_options STATE literal",
 /*  12 */ "alter_account_options ::= alter_account_option",
 /*  13 */ "alter_account_options ::= alter_account_options alter_account_option",
 /*  14 */ "alter_account_option ::= PASS literal",
 /*  15 */ "alter_account_option ::= PPS literal",
 /*  16 */ "alter_account_option ::= TSERIES literal",
 /*  17 */ "alter_account_option ::= STORAGE literal",
 /*  18 */ "alter_account_option ::= STREAMS literal",
 /*  19 */ "alter_account_option ::= QTIME literal",
 /*  20 */ "alter_account_option ::= DBS literal",
 /*  21 */ "alter_account_option ::= USERS literal",
 /*  22 */ "alter_account_option ::= CONNS literal",
 /*  23 */ "alter_account_option ::= STATE literal",
 /*  24 */ "ip_range_list ::= NK_STRING",
 /*  25 */ "ip_range_list ::= ip_range_list NK_COMMA NK_STRING",
 /*  26 */ "white_list ::= HOST ip_range_list",
 /*  27 */ "white_list_opt ::=",
 /*  28 */ "white_list_opt ::= white_list",
 /*  29 */ "cmd ::= CREATE USER user_name PASS NK_STRING sysinfo_opt white_list_opt",
 /*  30 */ "cmd ::= ALTER USER user_name PASS NK_STRING",
 /*  31 */ "cmd ::= ALTER USER user_name ENABLE NK_INTEGER",
 /*  32 */ "cmd ::= ALTER USER user_name SYSINFO NK_INTEGER",
 /*  33 */ "cmd ::= ALTER USER user_name ADD white_list",
 /*  34 */ "cmd ::= ALTER USER user_name DROP white_list",
 /*  35 */ "cmd ::= DROP USER user_name",
 /*  36 */ "sysinfo_opt ::=",
 /*  37 */ "sysinfo_opt ::= SYSINFO NK_INTEGER",
 /*  38 */ "cmd ::= GRANT privileges ON priv_level with_opt TO user_name",
 /*  39 */ "cmd ::= REVOKE privileges ON priv_level with_opt FROM user_name",
 /*  40 */ "privileges ::= ALL",
 /*  41 */ "privileges ::= priv_type_list",
 /*  42 */ "privileges ::= SUBSCRIBE",
 /*  43 */ "priv_type_list ::= priv_type",
 /*  44 */ "priv_type_list ::= priv_type_list NK_COMMA priv_type",
 /*  45 */ "priv_type ::= READ",
 /*  46 */ "priv_type ::= WRITE",
 /*  47 */ "priv_type ::= ALTER",
 /*  48 */ "priv_level ::= NK_STAR NK_DOT NK_STAR",
 /*  49 */ "priv_level ::= db_name NK_DOT NK_STAR",
 /*  50 */ "priv_level ::= db_name NK_DOT table_name",
 /*  51 */ "priv_level ::= topic_name",
 /*  52 */ "with_opt ::=",
 /*  53 */ "with_opt ::= WITH search_condition",
 /*  54 */ "cmd ::= CREATE DNODE dnode_endpoint",
 /*  55 */ "cmd ::= CREATE DNODE dnode_endpoint PORT NK_INTEGER",
 /*  56 */ "cmd ::= DROP DNODE NK_INTEGER force_opt",
 /*  57 */ "cmd ::= DROP DNODE dnode_endpoint force_opt",
 /*  58 */ "cmd ::= DROP DNODE NK_INTEGER unsafe_opt",
 /*  59 */ "cmd ::= DROP DNODE dnode_endpoint unsafe_opt",
 /*  60 */ "cmd ::= ALTER DNODE NK_INTEGER NK_STRING",
 /*  61 */ "cmd ::= ALTER DNODE NK_INTEGER NK_STRING NK_STRING",
 /*  62 */ "cmd ::= ALTER ALL DNODES NK_STRING",
 /*  63 */ "cmd ::= ALTER ALL DNODES NK_STRING NK_STRING",
 /*  64 */ "cmd ::= RESTORE DNODE NK_INTEGER",
 /*  65 */ "dnode_endpoint ::= NK_STRING",
 /*  66 */ "dnode_endpoint ::= NK_ID",
 /*  67 */ "dnode_endpoint ::= NK_IPTOKEN",
 /*  68 */ "force_opt ::=",
 /*  69 */ "force_opt ::= FORCE",
 /*  70 */ "unsafe_opt ::= UNSAFE",
 /*  71 */ "cmd ::= ALTER CLUSTER NK_STRING",
 /*  72 */ "cmd ::= ALTER CLUSTER NK_STRING NK_STRING",
 /*  73 */ "cmd ::= ALTER LOCAL NK_STRING",
 /*  74 */ "cmd ::= ALTER LOCAL NK_STRING NK_STRING",
 /*  75 */ "cmd ::= CREATE QNODE ON DNODE NK_INTEGER",
 /*  76 */ "cmd ::= DROP QNODE ON DNODE NK_INTEGER",
 /*  77 */ "cmd ::= RESTORE QNODE ON DNODE NK_INTEGER",
 /*  78 */ "cmd ::= CREATE BNODE ON DNODE NK_INTEGER",
 /*  79 */ "cmd ::= DROP BNODE ON DNODE NK_INTEGER",
 /*  80 */ "cmd ::= CREATE SNODE ON DNODE NK_INTEGER",
 /*  81 */ "cmd ::= DROP SNODE ON DNODE NK_INTEGER",
 /*  82 */ "cmd ::= CREATE MNODE ON DNODE NK_INTEGER",
 /*  83 */ "cmd ::= DROP MNODE ON DNODE NK_INTEGER",
 /*  84 */ "cmd ::= RESTORE MNODE ON DNODE NK_INTEGER",
 /*  85 */ "cmd ::= RESTORE VNODE ON DNODE NK_INTEGER",
 /*  86 */ "cmd ::= CREATE DATABASE not_exists_opt db_name db_options",
 /*  87 */ "cmd ::= DROP DATABASE exists_opt db_name",
 /*  88 */ "cmd ::= USE db_name",
 /*  89 */ "cmd ::= ALTER DATABASE db_name alter_db_options",
 /*  90 */ "cmd ::= FLUSH DATABASE db_name",
 /*  91 */ "cmd ::= TRIM DATABASE db_name speed_opt",
 /*  92 */ "cmd ::= COMPACT DATABASE db_name start_opt end_opt",
 /*  93 */ "not_exists_opt ::= IF NOT EXISTS",
 /*  94 */ "not_exists_opt ::=",
 /*  95 */ "exists_opt ::= IF EXISTS",
 /*  96 */ "exists_opt ::=",
 /*  97 */ "db_options ::=",
 /*  98 */ "db_options ::= db_options BUFFER NK_INTEGER",
 /*  99 */ "db_options ::= db_options CACHEMODEL NK_STRING",
 /* 100 */ "db_options ::= db_options CACHESIZE NK_INTEGER",
 /* 101 */ "db_options ::= db_options COMP NK_INTEGER",
 /* 102 */ "db_options ::= db_options DURATION NK_INTEGER",
 /* 103 */ "db_options ::= db_options DURATION NK_VARIABLE",
 /* 104 */ "db_options ::= db_options MAXROWS NK_INTEGER",
 /* 105 */ "db_options ::= db_options MINROWS NK_INTEGER",
 /* 106 */ "db_options ::= db_options KEEP integer_list",
 /* 107 */ "db_options ::= db_options KEEP variable_list",
 /* 108 */ "db_options ::= db_options PAGES NK_INTEGER",
 /* 109 */ "db_options ::= db_options PAGESIZE NK_INTEGER",
 /* 110 */ "db_options ::= db_options TSDB_PAGESIZE NK_INTEGER",
 /* 111 */ "db_options ::= db_options PRECISION NK_STRING",
 /* 112 */ "db_options ::= db_options REPLICA NK_INTEGER",
 /* 113 */ "db_options ::= db_options VGROUPS NK_INTEGER",
 /* 114 */ "db_options ::= db_options SINGLE_STABLE NK_INTEGER",
 /* 115 */ "db_options ::= db_options RETENTIONS retention_list",
 /* 116 */ "db_options ::= db_options SCHEMALESS NK_INTEGER",
 /* 117 */ "db_options ::= db_options WAL_LEVEL NK_INTEGER",
 /* 118 */ "db_options ::= db_options WAL_FSYNC_PERIOD NK_INTEGER",
 /* 119 */ "db_options ::= db_options WAL_RETENTION_PERIOD NK_INTEGER",
 /* 120 */ "db_options ::= db_options WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER",
 /* 121 */ "db_options ::= db_options WAL_RETENTION_SIZE NK_INTEGER",
 /* 122 */ "db_options ::= db_options WAL_RETENTION_SIZE NK_MINUS NK_INTEGER",
 /* 123 */ "db_options ::= db_options WAL_ROLL_PERIOD NK_INTEGER",
 /* 124 */ "db_options ::= db_options WAL_SEGMENT_SIZE NK_INTEGER",
 /* 125 */ "db_options ::= db_options STT_TRIGGER NK_INTEGER",
 /* 126 */ "db_options ::= db_options TABLE_PREFIX signed",
 /* 127 */ "db_options ::= db_options TABLE_SUFFIX signed",
 /* 128 */ "db_options ::= db_options KEEP_TIME_OFFSET NK_INTEGER",
 /* 129 */ "alter_db_options ::= alter_db_option",
 /* 130 */ "alter_db_options ::= alter_db_options alter_db_option",
 /* 131 */ "alter_db_option ::= BUFFER NK_INTEGER",
 /* 132 */ "alter_db_option ::= CACHEMODEL NK_STRING",
 /* 133 */ "alter_db_option ::= CACHESIZE NK_INTEGER",
 /* 134 */ "alter_db_option ::= WAL_FSYNC_PERIOD NK_INTEGER",
 /* 135 */ "alter_db_option ::= KEEP integer_list",
 /* 136 */ "alter_db_option ::= KEEP variable_list",
 /* 137 */ "alter_db_option ::= PAGES NK_INTEGER",
 /* 138 */ "alter_db_option ::= REPLICA NK_INTEGER",
 /* 139 */ "alter_db_option ::= WAL_LEVEL NK_INTEGER",
 /* 140 */ "alter_db_option ::= STT_TRIGGER NK_INTEGER",
 /* 141 */ "alter_db_option ::= MINROWS NK_INTEGER",
 /* 142 */ "alter_db_option ::= WAL_RETENTION_PERIOD NK_INTEGER",
 /* 143 */ "alter_db_option ::= WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER",
 /* 144 */ "alter_db_option ::= WAL_RETENTION_SIZE NK_INTEGER",
 /* 145 */ "alter_db_option ::= WAL_RETENTION_SIZE NK_MINUS NK_INTEGER",
 /* 146 */ "alter_db_option ::= KEEP_TIME_OFFSET NK_INTEGER",
 /* 147 */ "integer_list ::= NK_INTEGER",
 /* 148 */ "integer_list ::= integer_list NK_COMMA NK_INTEGER",
 /* 149 */ "variable_list ::= NK_VARIABLE",
 /* 150 */ "variable_list ::= variable_list NK_COMMA NK_VARIABLE",
 /* 151 */ "retention_list ::= retention",
 /* 152 */ "retention_list ::= retention_list NK_COMMA retention",
 /* 153 */ "retention ::= NK_VARIABLE NK_COLON NK_VARIABLE",
 /* 154 */ "retention ::= NK_MINUS NK_COLON NK_VARIABLE",
 /* 155 */ "speed_opt ::=",
 /* 156 */ "speed_opt ::= BWLIMIT NK_INTEGER",
 /* 157 */ "start_opt ::=",
 /* 158 */ "start_opt ::= START WITH NK_INTEGER",
 /* 159 */ "start_opt ::= START WITH NK_STRING",
 /* 160 */ "start_opt ::= START WITH TIMESTAMP NK_STRING",
 /* 161 */ "end_opt ::=",
 /* 162 */ "end_opt ::= END WITH NK_INTEGER",
 /* 163 */ "end_opt ::= END WITH NK_STRING",
 /* 164 */ "end_opt ::= END WITH TIMESTAMP NK_STRING",
 /* 165 */ "cmd ::= CREATE TABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def_opt table_options",
 /* 166 */ "cmd ::= CREATE TABLE multi_create_clause",
 /* 167 */ "cmd ::= CREATE STABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def table_options",
 /* 168 */ "cmd ::= DROP TABLE multi_drop_clause",
 /* 169 */ "cmd ::= DROP STABLE exists_opt full_table_name",
 /* 170 */ "cmd ::= ALTER TABLE alter_table_clause",
 /* 171 */ "cmd ::= ALTER STABLE alter_table_clause",
 /* 172 */ "alter_table_clause ::= full_table_name alter_table_options",
 /* 173 */ "alter_table_clause ::= full_table_name ADD COLUMN column_name type_name",
 /* 174 */ "alter_table_clause ::= full_table_name DROP COLUMN column_name",
 /* 175 */ "alter_table_clause ::= full_table_name MODIFY COLUMN column_name type_name",
 /* 176 */ "alter_table_clause ::= full_table_name RENAME COLUMN column_name column_name",
 /* 177 */ "alter_table_clause ::= full_table_name ADD TAG column_name type_name",
 /* 178 */ "alter_table_clause ::= full_table_name DROP TAG column_name",
 /* 179 */ "alter_table_clause ::= full_table_name MODIFY TAG column_name type_name",
 /* 180 */ "alter_table_clause ::= full_table_name RENAME TAG column_name column_name",
 /* 181 */ "alter_table_clause ::= full_table_name SET TAG column_name NK_EQ signed_literal",
 /* 182 */ "multi_create_clause ::= create_subtable_clause",
 /* 183 */ "multi_create_clause ::= multi_create_clause create_subtable_clause",
 /* 184 */ "create_subtable_clause ::= not_exists_opt full_table_name USING full_table_name specific_cols_opt TAGS NK_LP expression_list NK_RP table_options",
 /* 185 */ "multi_drop_clause ::= drop_table_clause",
 /* 186 */ "multi_drop_clause ::= multi_drop_clause NK_COMMA drop_table_clause",
 /* 187 */ "drop_table_clause ::= exists_opt full_table_name",
 /* 188 */ "specific_cols_opt ::=",
 /* 189 */ "specific_cols_opt ::= NK_LP col_name_list NK_RP",
 /* 190 */ "full_table_name ::= table_name",
 /* 191 */ "full_table_name ::= db_name NK_DOT table_name",
 /* 192 */ "column_def_list ::= column_def",
 /* 193 */ "column_def_list ::= column_def_list NK_COMMA column_def",
 /* 194 */ "column_def ::= column_name type_name",
 /* 195 */ "column_def ::= column_name type_name PRIMARY KEY",
 /* 196 */ "type_name ::= BOOL",
 /* 197 */ "type_name ::= TINYINT",
 /* 198 */ "type_name ::= SMALLINT",
 /* 199 */ "type_name ::= INT",
 /* 200 */ "type_name ::= INTEGER",
 /* 201 */ "type_name ::= BIGINT",
 /* 202 */ "type_name ::= FLOAT",
 /* 203 */ "type_name ::= DOUBLE",
 /* 204 */ "type_name ::= BINARY NK_LP NK_INTEGER NK_RP",
 /* 205 */ "type_name ::= TIMESTAMP",
 /* 206 */ "type_name ::= NCHAR NK_LP NK_INTEGER NK_RP",
 /* 207 */ "type_name ::= TINYINT UNSIGNED",
 /* 208 */ "type_name ::= SMALLINT UNSIGNED",
 /* 209 */ "type_name ::= INT UNSIGNED",
 /* 210 */ "type_name ::= BIGINT UNSIGNED",
 /* 211 */ "type_name ::= JSON",
 /* 212 */ "type_name ::= VARCHAR NK_LP NK_INTEGER NK_RP",
 /* 213 */ "type_name ::= MEDIUMBLOB",
 /* 214 */ "type_name ::= BLOB",
 /* 215 */ "type_name ::= VARBINARY NK_LP NK_INTEGER NK_RP",
 /* 216 */ "type_name ::= GEOMETRY NK_LP NK_INTEGER NK_RP",
 /* 217 */ "type_name ::= DECIMAL",
 /* 218 */ "type_name ::= DECIMAL NK_LP NK_INTEGER NK_RP",
 /* 219 */ "type_name ::= DECIMAL NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP",
 /* 220 */ "tags_def_opt ::=",
 /* 221 */ "tags_def_opt ::= tags_def",
 /* 222 */ "tags_def ::= TAGS NK_LP column_def_list NK_RP",
 /* 223 */ "table_options ::=",
 /* 224 */ "table_options ::= table_options COMMENT NK_STRING",
 /* 225 */ "table_options ::= table_options MAX_DELAY duration_list",
 /* 226 */ "table_options ::= table_options WATERMARK duration_list",
 /* 227 */ "table_options ::= table_options ROLLUP NK_LP rollup_func_list NK_RP",
 /* 228 */ "table_options ::= table_options TTL NK_INTEGER",
 /* 229 */ "table_options ::= table_options SMA NK_LP col_name_list NK_RP",
 /* 230 */ "table_options ::= table_options DELETE_MARK duration_list",
 /* 231 */ "alter_table_options ::= alter_table_option",
 /* 232 */ "alter_table_options ::= alter_table_options alter_table_option",
 /* 233 */ "alter_table_option ::= COMMENT NK_STRING",
 /* 234 */ "alter_table_option ::= TTL NK_INTEGER",
 /* 235 */ "duration_list ::= duration_literal",
 /* 236 */ "duration_list ::= duration_list NK_COMMA duration_literal",
 /* 237 */ "rollup_func_list ::= rollup_func_name",
 /* 238 */ "rollup_func_list ::= rollup_func_list NK_COMMA rollup_func_name",
 /* 239 */ "rollup_func_name ::= function_name",
 /* 240 */ "rollup_func_name ::= FIRST",
 /* 241 */ "rollup_func_name ::= LAST",
 /* 242 */ "col_name_list ::= col_name",
 /* 243 */ "col_name_list ::= col_name_list NK_COMMA col_name",
 /* 244 */ "col_name ::= column_name",
 /* 245 */ "cmd ::= SHOW DNODES",
 /* 246 */ "cmd ::= SHOW USERS",
 /* 247 */ "cmd ::= SHOW USER PRIVILEGES",
 /* 248 */ "cmd ::= SHOW db_kind_opt DATABASES",
 /* 249 */ "cmd ::= SHOW table_kind_db_name_cond_opt TABLES like_pattern_opt",
 /* 250 */ "cmd ::= SHOW db_name_cond_opt STABLES like_pattern_opt",
 /* 251 */ "cmd ::= SHOW db_name_cond_opt VGROUPS",
 /* 252 */ "cmd ::= SHOW MNODES",
 /* 253 */ "cmd ::= SHOW QNODES",
 /* 254 */ "cmd ::= SHOW FUNCTIONS",
 /* 255 */ "cmd ::= SHOW INDEXES FROM table_name_cond from_db_opt",
 /* 256 */ "cmd ::= SHOW INDEXES FROM db_name NK_DOT table_name",
 /* 257 */ "cmd ::= SHOW STREAMS",
 /* 258 */ "cmd ::= SHOW ACCOUNTS",
 /* 259 */ "cmd ::= SHOW APPS",
 /* 260 */ "cmd ::= SHOW CONNECTIONS",
 /* 261 */ "cmd ::= SHOW LICENCES",
 /* 262 */ "cmd ::= SHOW GRANTS",
 /* 263 */ "cmd ::= SHOW GRANTS FULL",
 /* 264 */ "cmd ::= SHOW GRANTS LOGS",
 /* 265 */ "cmd ::= SHOW CLUSTER MACHINES",
 /* 266 */ "cmd ::= SHOW CREATE DATABASE db_name",
 /* 267 */ "cmd ::= SHOW CREATE TABLE full_table_name",
 /* 268 */ "cmd ::= SHOW CREATE STABLE full_table_name",
 /* 269 */ "cmd ::= SHOW QUERIES",
 /* 270 */ "cmd ::= SHOW SCORES",
 /* 271 */ "cmd ::= SHOW TOPICS",
 /* 272 */ "cmd ::= SHOW VARIABLES",
 /* 273 */ "cmd ::= SHOW CLUSTER VARIABLES",
 /* 274 */ "cmd ::= SHOW LOCAL VARIABLES",
 /* 275 */ "cmd ::= SHOW DNODE NK_INTEGER VARIABLES like_pattern_opt",
 /* 276 */ "cmd ::= SHOW BNODES",
 /* 277 */ "cmd ::= SHOW SNODES",
 /* 278 */ "cmd ::= SHOW CLUSTER",
 /* 279 */ "cmd ::= SHOW TRANSACTIONS",
 /* 280 */ "cmd ::= SHOW TABLE DISTRIBUTED full_table_name",
 /* 281 */ "cmd ::= SHOW CONSUMERS",
 /* 282 */ "cmd ::= SHOW SUBSCRIPTIONS",
 /* 283 */ "cmd ::= SHOW TAGS FROM table_name_cond from_db_opt",
 /* 284 */ "cmd ::= SHOW TAGS FROM db_name NK_DOT table_name",
 /* 285 */ "cmd ::= SHOW TABLE TAGS tag_list_opt FROM table_name_cond from_db_opt",
 /* 286 */ "cmd ::= SHOW TABLE TAGS tag_list_opt FROM db_name NK_DOT table_name",
 /* 287 */ "cmd ::= SHOW VNODES ON DNODE NK_INTEGER",
 /* 288 */ "cmd ::= SHOW VNODES",
 /* 289 */ "cmd ::= SHOW db_name_cond_opt ALIVE",
 /* 290 */ "cmd ::= SHOW CLUSTER ALIVE",
 /* 291 */ "cmd ::= SHOW db_name_cond_opt VIEWS like_pattern_opt",
 /* 292 */ "cmd ::= SHOW CREATE VIEW full_table_name",
 /* 293 */ "cmd ::= SHOW COMPACTS",
 /* 294 */ "cmd ::= SHOW COMPACT NK_INTEGER",
 /* 295 */ "table_kind_db_name_cond_opt ::=",
 /* 296 */ "table_kind_db_name_cond_opt ::= table_kind",
 /* 297 */ "table_kind_db_name_cond_opt ::= db_name NK_DOT",
 /* 298 */ "table_kind_db_name_cond_opt ::= table_kind db_name NK_DOT",
 /* 299 */ "table_kind ::= NORMAL",
 /* 300 */ "table_kind ::= CHILD",
 /* 301 */ "db_name_cond_opt ::=",
 /* 302 */ "db_name_cond_opt ::= db_name NK_DOT",
 /* 303 */ "like_pattern_opt ::=",
 /* 304 */ "like_pattern_opt ::= LIKE NK_STRING",
 /* 305 */ "table_name_cond ::= table_name",
 /* 306 */ "from_db_opt ::=",
 /* 307 */ "from_db_opt ::= FROM db_name",
 /* 308 */ "tag_list_opt ::=",
 /* 309 */ "tag_list_opt ::= tag_item",
 /* 310 */ "tag_list_opt ::= tag_list_opt NK_COMMA tag_item",
 /* 311 */ "tag_item ::= TBNAME",
 /* 312 */ "tag_item ::= QTAGS",
 /* 313 */ "tag_item ::= column_name",
 /* 314 */ "tag_item ::= column_name column_alias",
 /* 315 */ "tag_item ::= column_name AS column_alias",
 /* 316 */ "db_kind_opt ::=",
 /* 317 */ "db_kind_opt ::= USER",
 /* 318 */ "db_kind_opt ::= SYSTEM",
 /* 319 */ "cmd ::= CREATE SMA INDEX not_exists_opt col_name ON full_table_name index_options",
 /* 320 */ "cmd ::= CREATE INDEX not_exists_opt col_name ON full_table_name NK_LP col_name_list NK_RP",
 /* 321 */ "cmd ::= DROP INDEX exists_opt full_index_name",
 /* 322 */ "full_index_name ::= index_name",
 /* 323 */ "full_index_name ::= db_name NK_DOT index_name",
 /* 324 */ "index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_RP sliding_opt sma_stream_opt",
 /* 325 */ "index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_COMMA duration_literal NK_RP sliding_opt sma_stream_opt",
 /* 326 */ "func_list ::= func",
 /* 327 */ "func_list ::= func_list NK_COMMA func",
 /* 328 */ "func ::= sma_func_name NK_LP expression_list NK_RP",
 /* 329 */ "sma_func_name ::= function_name",
 /* 330 */ "sma_func_name ::= COUNT",
 /* 331 */ "sma_func_name ::= FIRST",
 /* 332 */ "sma_func_name ::= LAST",
 /* 333 */ "sma_func_name ::= LAST_ROW",
 /* 334 */ "sma_stream_opt ::=",
 /* 335 */ "sma_stream_opt ::= sma_stream_opt WATERMARK duration_literal",
 /* 336 */ "sma_stream_opt ::= sma_stream_opt MAX_DELAY duration_literal",
 /* 337 */ "sma_stream_opt ::= sma_stream_opt DELETE_MARK duration_literal",
 /* 338 */ "with_meta ::= AS",
 /* 339 */ "with_meta ::= WITH META AS",
 /* 340 */ "with_meta ::= ONLY META AS",
 /* 341 */ "cmd ::= CREATE TOPIC not_exists_opt topic_name AS query_or_subquery",
 /* 342 */ "cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta DATABASE db_name",
 /* 343 */ "cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta STABLE full_table_name where_clause_opt",
 /* 344 */ "cmd ::= DROP TOPIC exists_opt topic_name",
 /* 345 */ "cmd ::= DROP CONSUMER GROUP exists_opt cgroup_name ON topic_name",
 /* 346 */ "cmd ::= DESC full_table_name",
 /* 347 */ "cmd ::= DESCRIBE full_table_name",
 /* 348 */ "cmd ::= RESET QUERY CACHE",
 /* 349 */ "cmd ::= EXPLAIN analyze_opt explain_options query_or_subquery",
 /* 350 */ "cmd ::= EXPLAIN analyze_opt explain_options insert_query",
 /* 351 */ "analyze_opt ::=",
 /* 352 */ "analyze_opt ::= ANALYZE",
 /* 353 */ "explain_options ::=",
 /* 354 */ "explain_options ::= explain_options VERBOSE NK_BOOL",
 /* 355 */ "explain_options ::= explain_options RATIO NK_FLOAT",
 /* 356 */ "cmd ::= CREATE or_replace_opt agg_func_opt FUNCTION not_exists_opt function_name AS NK_STRING OUTPUTTYPE type_name bufsize_opt language_opt",
 /* 357 */ "cmd ::= DROP FUNCTION exists_opt function_name",
 /* 358 */ "agg_func_opt ::=",
 /* 359 */ "agg_func_opt ::= AGGREGATE",
 /* 360 */ "bufsize_opt ::=",
 /* 361 */ "bufsize_opt ::= BUFSIZE NK_INTEGER",
 /* 362 */ "language_opt ::=",
 /* 363 */ "language_opt ::= LANGUAGE NK_STRING",
 /* 364 */ "or_replace_opt ::=",
 /* 365 */ "or_replace_opt ::= OR REPLACE",
 /* 366 */ "cmd ::= CREATE or_replace_opt VIEW full_view_name AS query_or_subquery",
 /* 367 */ "cmd ::= DROP VIEW exists_opt full_view_name",
 /* 368 */ "full_view_name ::= view_name",
 /* 369 */ "full_view_name ::= db_name NK_DOT view_name",
 /* 370 */ "cmd ::= CREATE STREAM not_exists_opt stream_name stream_options INTO full_table_name col_list_opt tag_def_or_ref_opt subtable_opt AS query_or_subquery",
 /* 371 */ "cmd ::= DROP STREAM exists_opt stream_name",
 /* 372 */ "cmd ::= PAUSE STREAM exists_opt stream_name",
 /* 373 */ "cmd ::= RESUME STREAM exists_opt ignore_opt stream_name",
 /* 374 */ "col_list_opt ::=",
 /* 375 */ "col_list_opt ::= NK_LP col_name_list NK_RP",
 /* 376 */ "tag_def_or_ref_opt ::=",
 /* 377 */ "tag_def_or_ref_opt ::= tags_def",
 /* 378 */ "tag_def_or_ref_opt ::= TAGS NK_LP col_name_list NK_RP",
 /* 379 */ "stream_options ::=",
 /* 380 */ "stream_options ::= stream_options TRIGGER AT_ONCE",
 /* 381 */ "stream_options ::= stream_options TRIGGER WINDOW_CLOSE",
 /* 382 */ "stream_options ::= stream_options TRIGGER MAX_DELAY duration_literal",
 /* 383 */ "stream_options ::= stream_options WATERMARK duration_literal",
 /* 384 */ "stream_options ::= stream_options IGNORE EXPIRED NK_INTEGER",
 /* 385 */ "stream_options ::= stream_options FILL_HISTORY NK_INTEGER",
 /* 386 */ "stream_options ::= stream_options DELETE_MARK duration_literal",
 /* 387 */ "stream_options ::= stream_options IGNORE UPDATE NK_INTEGER",
 /* 388 */ "subtable_opt ::=",
 /* 389 */ "subtable_opt ::= SUBTABLE NK_LP expression NK_RP",
 /* 390 */ "ignore_opt ::=",
 /* 391 */ "ignore_opt ::= IGNORE UNTREATED",
 /* 392 */ "cmd ::= KILL CONNECTION NK_INTEGER",
 /* 393 */ "cmd ::= KILL QUERY NK_STRING",
 /* 394 */ "cmd ::= KILL TRANSACTION NK_INTEGER",
 /* 395 */ "cmd ::= KILL COMPACT NK_INTEGER",
 /* 396 */ "cmd ::= BALANCE VGROUP",
 /* 397 */ "cmd ::= BALANCE VGROUP LEADER on_vgroup_id",
 /* 398 */ "cmd ::= MERGE VGROUP NK_INTEGER NK_INTEGER",
 /* 399 */ "cmd ::= REDISTRIBUTE VGROUP NK_INTEGER dnode_list",
 /* 400 */ "cmd ::= SPLIT VGROUP NK_INTEGER",
 /* 401 */ "on_vgroup_id ::=",
 /* 402 */ "on_vgroup_id ::= ON NK_INTEGER",
 /* 403 */ "dnode_list ::= DNODE NK_INTEGER",
 /* 404 */ "dnode_list ::= dnode_list DNODE NK_INTEGER",
 /* 405 */ "cmd ::= DELETE FROM full_table_name where_clause_opt",
 /* 406 */ "cmd ::= query_or_subquery",
 /* 407 */ "cmd ::= insert_query",
 /* 408 */ "insert_query ::= INSERT INTO full_table_name NK_LP col_name_list NK_RP query_or_subquery",
 /* 409 */ "insert_query ::= INSERT INTO full_table_name query_or_subquery",
 /* 410 */ "literal ::= NK_INTEGER",
 /* 411 */ "literal ::= NK_FLOAT",
 /* 412 */ "literal ::= NK_STRING",
 /* 413 */ "literal ::= NK_BOOL",
 /* 414 */ "literal ::= TIMESTAMP NK_STRING",
 /* 415 */ "literal ::= duration_literal",
 /* 416 */ "literal ::= NULL",
 /* 417 */ "literal ::= NK_QUESTION",
 /* 418 */ "duration_literal ::= NK_VARIABLE",
 /* 419 */ "signed ::= NK_INTEGER",
 /* 420 */ "signed ::= NK_PLUS NK_INTEGER",
 /* 421 */ "signed ::= NK_MINUS NK_INTEGER",
 /* 422 */ "signed ::= NK_FLOAT",
 /* 423 */ "signed ::= NK_PLUS NK_FLOAT",
 /* 424 */ "signed ::= NK_MINUS NK_FLOAT",
 /* 425 */ "signed_literal ::= signed",
 /* 426 */ "signed_literal ::= NK_STRING",
 /* 427 */ "signed_literal ::= NK_BOOL",
 /* 428 */ "signed_literal ::= TIMESTAMP NK_STRING",
 /* 429 */ "signed_literal ::= duration_literal",
 /* 430 */ "signed_literal ::= NULL",
 /* 431 */ "signed_literal ::= literal_func",
 /* 432 */ "signed_literal ::= NK_QUESTION",
 /* 433 */ "literal_list ::= signed_literal",
 /* 434 */ "literal_list ::= literal_list NK_COMMA signed_literal",
 /* 435 */ "db_name ::= NK_ID",
 /* 436 */ "table_name ::= NK_ID",
 /* 437 */ "column_name ::= NK_ID",
 /* 438 */ "function_name ::= NK_ID",
 /* 439 */ "view_name ::= NK_ID",
 /* 440 */ "table_alias ::= NK_ID",
 /* 441 */ "column_alias ::= NK_ID",
 /* 442 */ "column_alias ::= NK_ALIAS",
 /* 443 */ "user_name ::= NK_ID",
 /* 444 */ "topic_name ::= NK_ID",
 /* 445 */ "stream_name ::= NK_ID",
 /* 446 */ "cgroup_name ::= NK_ID",
 /* 447 */ "index_name ::= NK_ID",
 /* 448 */ "expr_or_subquery ::= expression",
 /* 449 */ "expression ::= literal",
 /* 450 */ "expression ::= pseudo_column",
 /* 451 */ "expression ::= column_reference",
 /* 452 */ "expression ::= function_expression",
 /* 453 */ "expression ::= case_when_expression",
 /* 454 */ "expression ::= NK_LP expression NK_RP",
 /* 455 */ "expression ::= NK_PLUS expr_or_subquery",
 /* 456 */ "expression ::= NK_MINUS expr_or_subquery",
 /* 457 */ "expression ::= expr_or_subquery NK_PLUS expr_or_subquery",
 /* 458 */ "expression ::= expr_or_subquery NK_MINUS expr_or_subquery",
 /* 459 */ "expression ::= expr_or_subquery NK_STAR expr_or_subquery",
 /* 460 */ "expression ::= expr_or_subquery NK_SLASH expr_or_subquery",
 /* 461 */ "expression ::= expr_or_subquery NK_REM expr_or_subquery",
 /* 462 */ "expression ::= column_reference NK_ARROW NK_STRING",
 /* 463 */ "expression ::= expr_or_subquery NK_BITAND expr_or_subquery",
 /* 464 */ "expression ::= expr_or_subquery NK_BITOR expr_or_subquery",
 /* 465 */ "expression_list ::= expr_or_subquery",
 /* 466 */ "expression_list ::= expression_list NK_COMMA expr_or_subquery",
 /* 467 */ "column_reference ::= column_name",
 /* 468 */ "column_reference ::= table_name NK_DOT column_name",
 /* 469 */ "column_reference ::= NK_ALIAS",
 /* 470 */ "column_reference ::= table_name NK_DOT NK_ALIAS",
 /* 471 */ "pseudo_column ::= ROWTS",
 /* 472 */ "pseudo_column ::= TBNAME",
 /* 473 */ "pseudo_column ::= table_name NK_DOT TBNAME",
 /* 474 */ "pseudo_column ::= QSTART",
 /* 475 */ "pseudo_column ::= QEND",
 /* 476 */ "pseudo_column ::= QDURATION",
 /* 477 */ "pseudo_column ::= WSTART",
 /* 478 */ "pseudo_column ::= WEND",
 /* 479 */ "pseudo_column ::= WDURATION",
 /* 480 */ "pseudo_column ::= IROWTS",
 /* 481 */ "pseudo_column ::= ISFILLED",
 /* 482 */ "pseudo_column ::= QTAGS",
 /* 483 */ "function_expression ::= function_name NK_LP expression_list NK_RP",
 /* 484 */ "function_expression ::= star_func NK_LP star_func_para_list NK_RP",
 /* 485 */ "function_expression ::= CAST NK_LP expr_or_subquery AS type_name NK_RP",
 /* 486 */ "function_expression ::= literal_func",
 /* 487 */ "literal_func ::= noarg_func NK_LP NK_RP",
 /* 488 */ "literal_func ::= NOW",
 /* 489 */ "noarg_func ::= NOW",
 /* 490 */ "noarg_func ::= TODAY",
 /* 491 */ "noarg_func ::= TIMEZONE",
 /* 492 */ "noarg_func ::= DATABASE",
 /* 493 */ "noarg_func ::= CLIENT_VERSION",
 /* 494 */ "noarg_func ::= SERVER_VERSION",
 /* 495 */ "noarg_func ::= SERVER_STATUS",
 /* 496 */ "noarg_func ::= CURRENT_USER",
 /* 497 */ "noarg_func ::= USER",
 /* 498 */ "star_func ::= COUNT",
 /* 499 */ "star_func ::= FIRST",
 /* 500 */ "star_func ::= LAST",
 /* 501 */ "star_func ::= LAST_ROW",
 /* 502 */ "star_func_para_list ::= NK_STAR",
 /* 503 */ "star_func_para_list ::= other_para_list",
 /* 504 */ "other_para_list ::= star_func_para",
 /* 505 */ "other_para_list ::= other_para_list NK_COMMA star_func_para",
 /* 506 */ "star_func_para ::= expr_or_subquery",
 /* 507 */ "star_func_para ::= table_name NK_DOT NK_STAR",
 /* 508 */ "case_when_expression ::= CASE when_then_list case_when_else_opt END",
 /* 509 */ "case_when_expression ::= CASE common_expression when_then_list case_when_else_opt END",
 /* 510 */ "when_then_list ::= when_then_expr",
 /* 511 */ "when_then_list ::= when_then_list when_then_expr",
 /* 512 */ "when_then_expr ::= WHEN common_expression THEN common_expression",
 /* 513 */ "case_when_else_opt ::=",
 /* 514 */ "case_when_else_opt ::= ELSE common_expression",
 /* 515 */ "predicate ::= expr_or_subquery compare_op expr_or_subquery",
 /* 516 */ "predicate ::= expr_or_subquery BETWEEN expr_or_subquery AND expr_or_subquery",
 /* 517 */ "predicate ::= expr_or_subquery NOT BETWEEN expr_or_subquery AND expr_or_subquery",
 /* 518 */ "predicate ::= expr_or_subquery IS NULL",
 /* 519 */ "predicate ::= expr_or_subquery IS NOT NULL",
 /* 520 */ "predicate ::= expr_or_subquery in_op in_predicate_value",
 /* 521 */ "compare_op ::= NK_LT",
 /* 522 */ "compare_op ::= NK_GT",
 /* 523 */ "compare_op ::= NK_LE",
 /* 524 */ "compare_op ::= NK_GE",
 /* 525 */ "compare_op ::= NK_NE",
 /* 526 */ "compare_op ::= NK_EQ",
 /* 527 */ "compare_op ::= LIKE",
 /* 528 */ "compare_op ::= NOT LIKE",
 /* 529 */ "compare_op ::= MATCH",
 /* 530 */ "compare_op ::= NMATCH",
 /* 531 */ "compare_op ::= CONTAINS",
 /* 532 */ "in_op ::= IN",
 /* 533 */ "in_op ::= NOT IN",
 /* 534 */ "in_predicate_value ::= NK_LP literal_list NK_RP",
 /* 535 */ "boolean_value_expression ::= boolean_primary",
 /* 536 */ "boolean_value_expression ::= NOT boolean_primary",
 /* 537 */ "boolean_value_expression ::= boolean_value_expression OR boolean_value_expression",
 /* 538 */ "boolean_value_expression ::= boolean_value_expression AND boolean_value_expression",
 /* 539 */ "boolean_primary ::= predicate",
 /* 540 */ "boolean_primary ::= NK_LP boolean_value_expression NK_RP",
 /* 541 */ "common_expression ::= expr_or_subquery",
 /* 542 */ "common_expression ::= boolean_value_expression",
 /* 543 */ "from_clause_opt ::=",
 /* 544 */ "from_clause_opt ::= FROM table_reference_list",
 /* 545 */ "table_reference_list ::= table_reference",
 /* 546 */ "table_reference_list ::= table_reference_list NK_COMMA table_reference",
 /* 547 */ "table_reference ::= table_primary",
 /* 548 */ "table_reference ::= joined_table",
 /* 549 */ "table_primary ::= table_name alias_opt",
 /* 550 */ "table_primary ::= db_name NK_DOT table_name alias_opt",
 /* 551 */ "table_primary ::= subquery alias_opt",
 /* 552 */ "table_primary ::= parenthesized_joined_table",
 /* 553 */ "alias_opt ::=",
 /* 554 */ "alias_opt ::= table_alias",
 /* 555 */ "alias_opt ::= AS table_alias",
 /* 556 */ "parenthesized_joined_table ::= NK_LP joined_table NK_RP",
 /* 557 */ "parenthesized_joined_table ::= NK_LP parenthesized_joined_table NK_RP",
 /* 558 */ "joined_table ::= table_reference join_type JOIN table_reference ON search_condition",
 /* 559 */ "join_type ::=",
 /* 560 */ "join_type ::= INNER",
 /* 561 */ "query_specification ::= SELECT hint_list set_quantifier_opt tag_mode_opt select_list from_clause_opt where_clause_opt partition_by_clause_opt range_opt every_opt fill_opt twindow_clause_opt group_by_clause_opt having_clause_opt",
 /* 562 */ "hint_list ::=",
 /* 563 */ "hint_list ::= NK_HINT",
 /* 564 */ "tag_mode_opt ::=",
 /* 565 */ "tag_mode_opt ::= TAGS",
 /* 566 */ "set_quantifier_opt ::=",
 /* 567 */ "set_quantifier_opt ::= DISTINCT",
 /* 568 */ "set_quantifier_opt ::= ALL",
 /* 569 */ "select_list ::= select_item",
 /* 570 */ "select_list ::= select_list NK_COMMA select_item",
 /* 571 */ "select_item ::= NK_STAR",
 /* 572 */ "select_item ::= common_expression",
 /* 573 */ "select_item ::= common_expression column_alias",
 /* 574 */ "select_item ::= common_expression AS column_alias",
 /* 575 */ "select_item ::= table_name NK_DOT NK_STAR",
 /* 576 */ "where_clause_opt ::=",
 /* 577 */ "where_clause_opt ::= WHERE search_condition",
 /* 578 */ "partition_by_clause_opt ::=",
 /* 579 */ "partition_by_clause_opt ::= PARTITION BY partition_list",
 /* 580 */ "partition_list ::= partition_item",
 /* 581 */ "partition_list ::= partition_list NK_COMMA partition_item",
 /* 582 */ "partition_item ::= expr_or_subquery",
 /* 583 */ "partition_item ::= expr_or_subquery column_alias",
 /* 584 */ "partition_item ::= expr_or_subquery AS column_alias",
 /* 585 */ "twindow_clause_opt ::=",
 /* 586 */ "twindow_clause_opt ::= SESSION NK_LP column_reference NK_COMMA interval_sliding_duration_literal NK_RP",
 /* 587 */ "twindow_clause_opt ::= STATE_WINDOW NK_LP expr_or_subquery NK_RP",
 /* 588 */ "twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_RP sliding_opt fill_opt",
 /* 589 */ "twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_COMMA interval_sliding_duration_literal NK_RP sliding_opt fill_opt",
 /* 590 */ "twindow_clause_opt ::= EVENT_WINDOW START WITH search_condition END WITH search_condition",
 /* 591 */ "twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_RP",
 /* 592 */ "twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP",
 /* 593 */ "sliding_opt ::=",
 /* 594 */ "sliding_opt ::= SLIDING NK_LP interval_sliding_duration_literal NK_RP",
 /* 595 */ "interval_sliding_duration_literal ::= NK_VARIABLE",
 /* 596 */ "interval_sliding_duration_literal ::= NK_STRING",
 /* 597 */ "interval_sliding_duration_literal ::= NK_INTEGER",
 /* 598 */ "fill_opt ::=",
 /* 599 */ "fill_opt ::= FILL NK_LP fill_mode NK_RP",
 /* 600 */ "fill_opt ::= FILL NK_LP VALUE NK_COMMA expression_list NK_RP",
 /* 601 */ "fill_opt ::= FILL NK_LP VALUE_F NK_COMMA expression_list NK_RP",
 /* 602 */ "fill_mode ::= NONE",
 /* 603 */ "fill_mode ::= PREV",
 /* 604 */ "fill_mode ::= NULL",
 /* 605 */ "fill_mode ::= NULL_F",
 /* 606 */ "fill_mode ::= LINEAR",
 /* 607 */ "fill_mode ::= NEXT",
 /* 608 */ "group_by_clause_opt ::=",
 /* 609 */ "group_by_clause_opt ::= GROUP BY group_by_list",
 /* 610 */ "group_by_list ::= expr_or_subquery",
 /* 611 */ "group_by_list ::= group_by_list NK_COMMA expr_or_subquery",
 /* 612 */ "having_clause_opt ::=",
 /* 613 */ "having_clause_opt ::= HAVING search_condition",
 /* 614 */ "range_opt ::=",
 /* 615 */ "range_opt ::= RANGE NK_LP expr_or_subquery NK_COMMA expr_or_subquery NK_RP",
 /* 616 */ "range_opt ::= RANGE NK_LP expr_or_subquery NK_RP",
 /* 617 */ "every_opt ::=",
 /* 618 */ "every_opt ::= EVERY NK_LP duration_literal NK_RP",
 /* 619 */ "query_expression ::= query_simple order_by_clause_opt slimit_clause_opt limit_clause_opt",
 /* 620 */ "query_simple ::= query_specification",
 /* 621 */ "query_simple ::= union_query_expression",
 /* 622 */ "union_query_expression ::= query_simple_or_subquery UNION ALL query_simple_or_subquery",
 /* 623 */ "union_query_expression ::= query_simple_or_subquery UNION query_simple_or_subquery",
 /* 624 */ "query_simple_or_subquery ::= query_simple",
 /* 625 */ "query_simple_or_subquery ::= subquery",
 /* 626 */ "query_or_subquery ::= query_expression",
 /* 627 */ "query_or_subquery ::= subquery",
 /* 628 */ "order_by_clause_opt ::=",
 /* 629 */ "order_by_clause_opt ::= ORDER BY sort_specification_list",
 /* 630 */ "slimit_clause_opt ::=",
 /* 631 */ "slimit_clause_opt ::= SLIMIT NK_INTEGER",
 /* 632 */ "slimit_clause_opt ::= SLIMIT NK_INTEGER SOFFSET NK_INTEGER",
 /* 633 */ "slimit_clause_opt ::= SLIMIT NK_INTEGER NK_COMMA NK_INTEGER",
 /* 634 */ "limit_clause_opt ::=",
 /* 635 */ "limit_clause_opt ::= LIMIT NK_INTEGER",
 /* 636 */ "limit_clause_opt ::= LIMIT NK_INTEGER OFFSET NK_INTEGER",
 /* 637 */ "limit_clause_opt ::= LIMIT NK_INTEGER NK_COMMA NK_INTEGER",
 /* 638 */ "subquery ::= NK_LP query_expression NK_RP",
 /* 639 */ "subquery ::= NK_LP subquery NK_RP",
 /* 640 */ "search_condition ::= common_expression",
 /* 641 */ "sort_specification_list ::= sort_specification",
 /* 642 */ "sort_specification_list ::= sort_specification_list NK_COMMA sort_specification",
 /* 643 */ "sort_specification ::= expr_or_subquery ordering_specification_opt null_ordering_opt",
 /* 644 */ "ordering_specification_opt ::=",
 /* 645 */ "ordering_specification_opt ::= ASC",
 /* 646 */ "ordering_specification_opt ::= DESC",
 /* 647 */ "null_ordering_opt ::=",
 /* 648 */ "null_ordering_opt ::= NULLS FIRST",
 /* 649 */ "null_ordering_opt ::= NULLS LAST",
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
void ParseInit(void *yypRawParser ParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
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
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ParseCTX_STORE
    ParseInit(yypParser ParseCTX_PARAM);
  }
  return (void*)yypParser;
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
  ParseARG_FETCH
  ParseCTX_FETCH
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
      /* Default NON-TERMINAL Destructor */
    case 352: /* cmd */
    case 355: /* literal */
    case 364: /* with_opt */
    case 370: /* search_condition */
    case 375: /* db_options */
    case 377: /* alter_db_options */
    case 379: /* start_opt */
    case 380: /* end_opt */
    case 384: /* signed */
    case 386: /* retention */
    case 387: /* full_table_name */
    case 390: /* table_options */
    case 394: /* alter_table_clause */
    case 395: /* alter_table_options */
    case 398: /* signed_literal */
    case 399: /* create_subtable_clause */
    case 402: /* drop_table_clause */
    case 404: /* column_def */
    case 408: /* duration_literal */
    case 409: /* rollup_func_name */
    case 411: /* col_name */
    case 414: /* like_pattern_opt */
    case 415: /* db_name_cond_opt */
    case 416: /* table_name_cond */
    case 417: /* from_db_opt */
    case 420: /* tag_item */
    case 422: /* index_options */
    case 423: /* full_index_name */
    case 426: /* sliding_opt */
    case 427: /* sma_stream_opt */
    case 428: /* func */
    case 431: /* query_or_subquery */
    case 432: /* where_clause_opt */
    case 435: /* explain_options */
    case 436: /* insert_query */
    case 441: /* full_view_name */
    case 444: /* stream_options */
    case 447: /* subtable_opt */
    case 449: /* expression */
    case 452: /* literal_func */
    case 455: /* expr_or_subquery */
    case 456: /* pseudo_column */
    case 457: /* column_reference */
    case 458: /* function_expression */
    case 459: /* case_when_expression */
    case 464: /* star_func_para */
    case 466: /* case_when_else_opt */
    case 467: /* common_expression */
    case 468: /* when_then_expr */
    case 469: /* predicate */
    case 472: /* in_predicate_value */
    case 473: /* boolean_value_expression */
    case 474: /* boolean_primary */
    case 475: /* from_clause_opt */
    case 476: /* table_reference_list */
    case 477: /* table_reference */
    case 478: /* table_primary */
    case 479: /* joined_table */
    case 481: /* subquery */
    case 482: /* parenthesized_joined_table */
    case 484: /* query_specification */
    case 490: /* range_opt */
    case 491: /* every_opt */
    case 492: /* fill_opt */
    case 493: /* twindow_clause_opt */
    case 495: /* having_clause_opt */
    case 496: /* select_item */
    case 498: /* partition_item */
    case 499: /* interval_sliding_duration_literal */
    case 502: /* query_expression */
    case 503: /* query_simple */
    case 505: /* slimit_clause_opt */
    case 506: /* limit_clause_opt */
    case 507: /* union_query_expression */
    case 508: /* query_simple_or_subquery */
    case 510: /* sort_specification */
{
#line 7 "sql.y"
 nodesDestroyNode((yypminor->yy560)); 
#line 3298 "sql.c"
}
      break;
    case 353: /* account_options */
    case 354: /* alter_account_options */
    case 356: /* alter_account_option */
    case 378: /* speed_opt */
    case 430: /* with_meta */
    case 439: /* bufsize_opt */
{
#line 54 "sql.y"
 
#line 3310 "sql.c"
}
      break;
    case 357: /* ip_range_list */
    case 358: /* white_list */
    case 359: /* white_list_opt */
    case 381: /* integer_list */
    case 382: /* variable_list */
    case 383: /* retention_list */
    case 388: /* column_def_list */
    case 389: /* tags_def_opt */
    case 391: /* multi_create_clause */
    case 392: /* tags_def */
    case 393: /* multi_drop_clause */
    case 400: /* specific_cols_opt */
    case 401: /* expression_list */
    case 403: /* col_name_list */
    case 405: /* duration_list */
    case 406: /* rollup_func_list */
    case 418: /* tag_list_opt */
    case 425: /* func_list */
    case 445: /* col_list_opt */
    case 446: /* tag_def_or_ref_opt */
    case 451: /* dnode_list */
    case 453: /* literal_list */
    case 461: /* star_func_para_list */
    case 463: /* other_para_list */
    case 465: /* when_then_list */
    case 485: /* hint_list */
    case 488: /* select_list */
    case 489: /* partition_by_clause_opt */
    case 494: /* group_by_clause_opt */
    case 497: /* partition_list */
    case 501: /* group_by_list */
    case 504: /* order_by_clause_opt */
    case 509: /* sort_specification_list */
{
#line 85 "sql.y"
 nodesDestroyList((yypminor->yy388)); 
#line 3349 "sql.c"
}
      break;
    case 360: /* user_name */
    case 367: /* db_name */
    case 368: /* table_name */
    case 369: /* topic_name */
    case 371: /* dnode_endpoint */
    case 396: /* column_name */
    case 410: /* function_name */
    case 421: /* column_alias */
    case 424: /* index_name */
    case 429: /* sma_func_name */
    case 433: /* cgroup_name */
    case 440: /* language_opt */
    case 442: /* view_name */
    case 443: /* stream_name */
    case 450: /* on_vgroup_id */
    case 454: /* table_alias */
    case 460: /* star_func */
    case 462: /* noarg_func */
    case 480: /* alias_opt */
{
#line 820 "sql.y"
 
#line 3374 "sql.c"
}
      break;
    case 364: /* sysinfo_opt */
{
 
#line 3381 "sql.c"
}
      break;
    case 365: /* privileges */
    case 368: /* priv_type_list */
    case 369: /* priv_type */
{
#line 121 "sql.y"
 
#line 3390 "sql.c"
}
      break;
    case 366: /* priv_level */
{
 
#line 3397 "sql.c"
}
      break;
    case 372: /* force_opt */
    case 373: /* unsafe_opt */
    case 374: /* not_exists_opt */
    case 376: /* exists_opt */
    case 434: /* analyze_opt */
    case 437: /* or_replace_opt */
    case 438: /* agg_func_opt */
    case 448: /* ignore_opt */
    case 486: /* set_quantifier_opt */
    case 487: /* tag_mode_opt */
{
#line 167 "sql.y"
 
#line 3413 "sql.c"
}
      break;
    case 385: /* alter_db_option */
    case 407: /* alter_table_option */
{
 
#line 3421 "sql.c"
}
      break;
    case 400: /* type_name */
{
#line 393 "sql.y"
 
#line 3428 "sql.c"
}
      break;
    case 412: /* db_kind_opt */
    case 419: /* table_kind */
{
#line 561 "sql.y"
 
#line 3436 "sql.c"
}
      break;
    case 413: /* table_kind_db_name_cond_opt */
{
#line 526 "sql.y"
 
#line 3443 "sql.c"
}
      break;
    case 470: /* compare_op */
    case 471: /* in_op */
{
#line 1010 "sql.y"
 
#line 3451 "sql.c"
}
      break;
    case 483: /* join_type */
{
#line 1086 "sql.y"
 
#line 3458 "sql.c"
}
      break;
    case 500: /* fill_mode */
{
#line 1181 "sql.y"
 
#line 3465 "sql.c"
}
      break;
    case 511: /* ordering_specification_opt */
{
#line 1266 "sql.y"
 
#line 3472 "sql.c"
}
      break;
    case 512: /* null_ordering_opt */
{
#line 1272 "sql.y"
 
#line 3479 "sql.c"
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
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    assert( i<=YY_ACTTAB_COUNT );
    assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    assert( i<(int)YY_NLOOKAHEAD );
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      assert( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0]) );
      iFallback = yyFallback[iLookAhead];
      if( iFallback!=0 ){
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
        assert( j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) );
        if( yy_lookahead[j]==YYWILDCARD && iLookAhead>0 ){
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
      assert( i>=0 && i<sizeof(yy_action)/sizeof(yy_action[0]) );
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
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
   ParseARG_FETCH
   ParseCTX_FETCH
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
   ParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ParseCTX_STORE
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
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
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
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
   352,  /* (0) cmd ::= CREATE ACCOUNT NK_ID PASS NK_STRING account_options */
   352,  /* (1) cmd ::= ALTER ACCOUNT NK_ID alter_account_options */
   353,  /* (2) account_options ::= */
   353,  /* (3) account_options ::= account_options PPS literal */
   353,  /* (4) account_options ::= account_options TSERIES literal */
   353,  /* (5) account_options ::= account_options STORAGE literal */
   353,  /* (6) account_options ::= account_options STREAMS literal */
   353,  /* (7) account_options ::= account_options QTIME literal */
   353,  /* (8) account_options ::= account_options DBS literal */
   353,  /* (9) account_options ::= account_options USERS literal */
   353,  /* (10) account_options ::= account_options CONNS literal */
   353,  /* (11) account_options ::= account_options STATE literal */
   354,  /* (12) alter_account_options ::= alter_account_option */
   354,  /* (13) alter_account_options ::= alter_account_options alter_account_option */
   356,  /* (14) alter_account_option ::= PASS literal */
   356,  /* (15) alter_account_option ::= PPS literal */
   356,  /* (16) alter_account_option ::= TSERIES literal */
   356,  /* (17) alter_account_option ::= STORAGE literal */
   356,  /* (18) alter_account_option ::= STREAMS literal */
   356,  /* (19) alter_account_option ::= QTIME literal */
   356,  /* (20) alter_account_option ::= DBS literal */
   356,  /* (21) alter_account_option ::= USERS literal */
   356,  /* (22) alter_account_option ::= CONNS literal */
   356,  /* (23) alter_account_option ::= STATE literal */
   357,  /* (24) ip_range_list ::= NK_STRING */
   357,  /* (25) ip_range_list ::= ip_range_list NK_COMMA NK_STRING */
   358,  /* (26) white_list ::= HOST ip_range_list */
   359,  /* (27) white_list_opt ::= */
   359,  /* (28) white_list_opt ::= white_list */
   352,  /* (29) cmd ::= CREATE USER user_name PASS NK_STRING sysinfo_opt white_list_opt */
   352,  /* (30) cmd ::= ALTER USER user_name PASS NK_STRING */
   352,  /* (31) cmd ::= ALTER USER user_name ENABLE NK_INTEGER */
   352,  /* (32) cmd ::= ALTER USER user_name SYSINFO NK_INTEGER */
   352,  /* (33) cmd ::= ALTER USER user_name ADD white_list */
   352,  /* (34) cmd ::= ALTER USER user_name DROP white_list */
   352,  /* (35) cmd ::= DROP USER user_name */
   361,  /* (36) sysinfo_opt ::= */
   361,  /* (37) sysinfo_opt ::= SYSINFO NK_INTEGER */
   352,  /* (38) cmd ::= GRANT privileges ON priv_level with_opt TO user_name */
   352,  /* (39) cmd ::= REVOKE privileges ON priv_level with_opt FROM user_name */
   362,  /* (40) privileges ::= ALL */
   362,  /* (41) privileges ::= priv_type_list */
   362,  /* (42) privileges ::= SUBSCRIBE */
   365,  /* (43) priv_type_list ::= priv_type */
   365,  /* (44) priv_type_list ::= priv_type_list NK_COMMA priv_type */
   366,  /* (45) priv_type ::= READ */
   366,  /* (46) priv_type ::= WRITE */
   366,  /* (47) priv_type ::= ALTER */
   363,  /* (48) priv_level ::= NK_STAR NK_DOT NK_STAR */
   363,  /* (49) priv_level ::= db_name NK_DOT NK_STAR */
   363,  /* (50) priv_level ::= db_name NK_DOT table_name */
   363,  /* (51) priv_level ::= topic_name */
   364,  /* (52) with_opt ::= */
   364,  /* (53) with_opt ::= WITH search_condition */
   352,  /* (54) cmd ::= CREATE DNODE dnode_endpoint */
   352,  /* (55) cmd ::= CREATE DNODE dnode_endpoint PORT NK_INTEGER */
   352,  /* (56) cmd ::= DROP DNODE NK_INTEGER force_opt */
   352,  /* (57) cmd ::= DROP DNODE dnode_endpoint force_opt */
   352,  /* (58) cmd ::= DROP DNODE NK_INTEGER unsafe_opt */
   352,  /* (59) cmd ::= DROP DNODE dnode_endpoint unsafe_opt */
   352,  /* (60) cmd ::= ALTER DNODE NK_INTEGER NK_STRING */
   352,  /* (61) cmd ::= ALTER DNODE NK_INTEGER NK_STRING NK_STRING */
   352,  /* (62) cmd ::= ALTER ALL DNODES NK_STRING */
   352,  /* (63) cmd ::= ALTER ALL DNODES NK_STRING NK_STRING */
   352,  /* (64) cmd ::= RESTORE DNODE NK_INTEGER */
   371,  /* (65) dnode_endpoint ::= NK_STRING */
   371,  /* (66) dnode_endpoint ::= NK_ID */
   371,  /* (67) dnode_endpoint ::= NK_IPTOKEN */
   372,  /* (68) force_opt ::= */
   372,  /* (69) force_opt ::= FORCE */
   373,  /* (70) unsafe_opt ::= UNSAFE */
   352,  /* (71) cmd ::= ALTER CLUSTER NK_STRING */
   352,  /* (72) cmd ::= ALTER CLUSTER NK_STRING NK_STRING */
   352,  /* (73) cmd ::= ALTER LOCAL NK_STRING */
   352,  /* (74) cmd ::= ALTER LOCAL NK_STRING NK_STRING */
   352,  /* (75) cmd ::= CREATE QNODE ON DNODE NK_INTEGER */
   352,  /* (76) cmd ::= DROP QNODE ON DNODE NK_INTEGER */
   352,  /* (77) cmd ::= RESTORE QNODE ON DNODE NK_INTEGER */
   352,  /* (78) cmd ::= CREATE BNODE ON DNODE NK_INTEGER */
   352,  /* (79) cmd ::= DROP BNODE ON DNODE NK_INTEGER */
   352,  /* (80) cmd ::= CREATE SNODE ON DNODE NK_INTEGER */
   352,  /* (81) cmd ::= DROP SNODE ON DNODE NK_INTEGER */
   352,  /* (82) cmd ::= CREATE MNODE ON DNODE NK_INTEGER */
   352,  /* (83) cmd ::= DROP MNODE ON DNODE NK_INTEGER */
   352,  /* (84) cmd ::= RESTORE MNODE ON DNODE NK_INTEGER */
   352,  /* (85) cmd ::= RESTORE VNODE ON DNODE NK_INTEGER */
   352,  /* (86) cmd ::= CREATE DATABASE not_exists_opt db_name db_options */
   352,  /* (87) cmd ::= DROP DATABASE exists_opt db_name */
   352,  /* (88) cmd ::= USE db_name */
   352,  /* (89) cmd ::= ALTER DATABASE db_name alter_db_options */
   352,  /* (90) cmd ::= FLUSH DATABASE db_name */
   352,  /* (91) cmd ::= TRIM DATABASE db_name speed_opt */
   352,  /* (92) cmd ::= COMPACT DATABASE db_name start_opt end_opt */
   374,  /* (93) not_exists_opt ::= IF NOT EXISTS */
   374,  /* (94) not_exists_opt ::= */
   376,  /* (95) exists_opt ::= IF EXISTS */
   376,  /* (96) exists_opt ::= */
   375,  /* (97) db_options ::= */
   375,  /* (98) db_options ::= db_options BUFFER NK_INTEGER */
   375,  /* (99) db_options ::= db_options CACHEMODEL NK_STRING */
   375,  /* (100) db_options ::= db_options CACHESIZE NK_INTEGER */
   375,  /* (101) db_options ::= db_options COMP NK_INTEGER */
   375,  /* (102) db_options ::= db_options DURATION NK_INTEGER */
   375,  /* (103) db_options ::= db_options DURATION NK_VARIABLE */
   375,  /* (104) db_options ::= db_options MAXROWS NK_INTEGER */
   375,  /* (105) db_options ::= db_options MINROWS NK_INTEGER */
   375,  /* (106) db_options ::= db_options KEEP integer_list */
   375,  /* (107) db_options ::= db_options KEEP variable_list */
   375,  /* (108) db_options ::= db_options PAGES NK_INTEGER */
   375,  /* (109) db_options ::= db_options PAGESIZE NK_INTEGER */
   375,  /* (110) db_options ::= db_options TSDB_PAGESIZE NK_INTEGER */
   375,  /* (111) db_options ::= db_options PRECISION NK_STRING */
   375,  /* (112) db_options ::= db_options REPLICA NK_INTEGER */
   375,  /* (113) db_options ::= db_options VGROUPS NK_INTEGER */
   375,  /* (114) db_options ::= db_options SINGLE_STABLE NK_INTEGER */
   375,  /* (115) db_options ::= db_options RETENTIONS retention_list */
   375,  /* (116) db_options ::= db_options SCHEMALESS NK_INTEGER */
   375,  /* (117) db_options ::= db_options WAL_LEVEL NK_INTEGER */
   375,  /* (118) db_options ::= db_options WAL_FSYNC_PERIOD NK_INTEGER */
   375,  /* (119) db_options ::= db_options WAL_RETENTION_PERIOD NK_INTEGER */
   375,  /* (120) db_options ::= db_options WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
   375,  /* (121) db_options ::= db_options WAL_RETENTION_SIZE NK_INTEGER */
   375,  /* (122) db_options ::= db_options WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
   375,  /* (123) db_options ::= db_options WAL_ROLL_PERIOD NK_INTEGER */
   375,  /* (124) db_options ::= db_options WAL_SEGMENT_SIZE NK_INTEGER */
   375,  /* (125) db_options ::= db_options STT_TRIGGER NK_INTEGER */
   375,  /* (126) db_options ::= db_options TABLE_PREFIX signed */
   375,  /* (127) db_options ::= db_options TABLE_SUFFIX signed */
   375,  /* (128) db_options ::= db_options KEEP_TIME_OFFSET NK_INTEGER */
   377,  /* (129) alter_db_options ::= alter_db_option */
   377,  /* (130) alter_db_options ::= alter_db_options alter_db_option */
   385,  /* (131) alter_db_option ::= BUFFER NK_INTEGER */
   385,  /* (132) alter_db_option ::= CACHEMODEL NK_STRING */
   385,  /* (133) alter_db_option ::= CACHESIZE NK_INTEGER */
   385,  /* (134) alter_db_option ::= WAL_FSYNC_PERIOD NK_INTEGER */
   385,  /* (135) alter_db_option ::= KEEP integer_list */
   385,  /* (136) alter_db_option ::= KEEP variable_list */
   385,  /* (137) alter_db_option ::= PAGES NK_INTEGER */
   385,  /* (138) alter_db_option ::= REPLICA NK_INTEGER */
   385,  /* (139) alter_db_option ::= WAL_LEVEL NK_INTEGER */
   385,  /* (140) alter_db_option ::= STT_TRIGGER NK_INTEGER */
   385,  /* (141) alter_db_option ::= MINROWS NK_INTEGER */
   385,  /* (142) alter_db_option ::= WAL_RETENTION_PERIOD NK_INTEGER */
   385,  /* (143) alter_db_option ::= WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
   385,  /* (144) alter_db_option ::= WAL_RETENTION_SIZE NK_INTEGER */
   385,  /* (145) alter_db_option ::= WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
   385,  /* (146) alter_db_option ::= KEEP_TIME_OFFSET NK_INTEGER */
   381,  /* (147) integer_list ::= NK_INTEGER */
   381,  /* (148) integer_list ::= integer_list NK_COMMA NK_INTEGER */
   382,  /* (149) variable_list ::= NK_VARIABLE */
   382,  /* (150) variable_list ::= variable_list NK_COMMA NK_VARIABLE */
   383,  /* (151) retention_list ::= retention */
   383,  /* (152) retention_list ::= retention_list NK_COMMA retention */
   386,  /* (153) retention ::= NK_VARIABLE NK_COLON NK_VARIABLE */
   386,  /* (154) retention ::= NK_MINUS NK_COLON NK_VARIABLE */
   378,  /* (155) speed_opt ::= */
   378,  /* (156) speed_opt ::= BWLIMIT NK_INTEGER */
   379,  /* (157) start_opt ::= */
   379,  /* (158) start_opt ::= START WITH NK_INTEGER */
   379,  /* (159) start_opt ::= START WITH NK_STRING */
   379,  /* (160) start_opt ::= START WITH TIMESTAMP NK_STRING */
   380,  /* (161) end_opt ::= */
   380,  /* (162) end_opt ::= END WITH NK_INTEGER */
   380,  /* (163) end_opt ::= END WITH NK_STRING */
   380,  /* (164) end_opt ::= END WITH TIMESTAMP NK_STRING */
   352,  /* (165) cmd ::= CREATE TABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def_opt table_options */
   352,  /* (166) cmd ::= CREATE TABLE multi_create_clause */
   352,  /* (167) cmd ::= CREATE STABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def table_options */
   352,  /* (168) cmd ::= DROP TABLE multi_drop_clause */
   352,  /* (169) cmd ::= DROP STABLE exists_opt full_table_name */
   352,  /* (170) cmd ::= ALTER TABLE alter_table_clause */
   352,  /* (171) cmd ::= ALTER STABLE alter_table_clause */
   394,  /* (172) alter_table_clause ::= full_table_name alter_table_options */
   394,  /* (173) alter_table_clause ::= full_table_name ADD COLUMN column_name type_name */
   394,  /* (174) alter_table_clause ::= full_table_name DROP COLUMN column_name */
   394,  /* (175) alter_table_clause ::= full_table_name MODIFY COLUMN column_name type_name */
   394,  /* (176) alter_table_clause ::= full_table_name RENAME COLUMN column_name column_name */
   394,  /* (177) alter_table_clause ::= full_table_name ADD TAG column_name type_name */
   394,  /* (178) alter_table_clause ::= full_table_name DROP TAG column_name */
   394,  /* (179) alter_table_clause ::= full_table_name MODIFY TAG column_name type_name */
   394,  /* (180) alter_table_clause ::= full_table_name RENAME TAG column_name column_name */
   394,  /* (181) alter_table_clause ::= full_table_name SET TAG column_name NK_EQ signed_literal */
   391,  /* (182) multi_create_clause ::= create_subtable_clause */
   391,  /* (183) multi_create_clause ::= multi_create_clause create_subtable_clause */
   399,  /* (184) create_subtable_clause ::= not_exists_opt full_table_name USING full_table_name specific_cols_opt TAGS NK_LP expression_list NK_RP table_options */
   393,  /* (185) multi_drop_clause ::= drop_table_clause */
   393,  /* (186) multi_drop_clause ::= multi_drop_clause NK_COMMA drop_table_clause */
   402,  /* (187) drop_table_clause ::= exists_opt full_table_name */
   400,  /* (188) specific_cols_opt ::= */
   400,  /* (189) specific_cols_opt ::= NK_LP col_name_list NK_RP */
   387,  /* (190) full_table_name ::= table_name */
   387,  /* (191) full_table_name ::= db_name NK_DOT table_name */
   388,  /* (192) column_def_list ::= column_def */
   388,  /* (193) column_def_list ::= column_def_list NK_COMMA column_def */
   404,  /* (194) column_def ::= column_name type_name */
   404,  /* (195) column_def ::= column_name type_name PRIMARY KEY */
   397,  /* (196) type_name ::= BOOL */
   397,  /* (197) type_name ::= TINYINT */
   397,  /* (198) type_name ::= SMALLINT */
   397,  /* (199) type_name ::= INT */
   397,  /* (200) type_name ::= INTEGER */
   397,  /* (201) type_name ::= BIGINT */
   397,  /* (202) type_name ::= FLOAT */
   397,  /* (203) type_name ::= DOUBLE */
   397,  /* (204) type_name ::= BINARY NK_LP NK_INTEGER NK_RP */
   397,  /* (205) type_name ::= TIMESTAMP */
   397,  /* (206) type_name ::= NCHAR NK_LP NK_INTEGER NK_RP */
   397,  /* (207) type_name ::= TINYINT UNSIGNED */
   397,  /* (208) type_name ::= SMALLINT UNSIGNED */
   397,  /* (209) type_name ::= INT UNSIGNED */
   397,  /* (210) type_name ::= BIGINT UNSIGNED */
   397,  /* (211) type_name ::= JSON */
   397,  /* (212) type_name ::= VARCHAR NK_LP NK_INTEGER NK_RP */
   397,  /* (213) type_name ::= MEDIUMBLOB */
   397,  /* (214) type_name ::= BLOB */
   397,  /* (215) type_name ::= VARBINARY NK_LP NK_INTEGER NK_RP */
   397,  /* (216) type_name ::= GEOMETRY NK_LP NK_INTEGER NK_RP */
   397,  /* (217) type_name ::= DECIMAL */
   397,  /* (218) type_name ::= DECIMAL NK_LP NK_INTEGER NK_RP */
   397,  /* (219) type_name ::= DECIMAL NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
   389,  /* (220) tags_def_opt ::= */
   389,  /* (221) tags_def_opt ::= tags_def */
   392,  /* (222) tags_def ::= TAGS NK_LP column_def_list NK_RP */
   390,  /* (223) table_options ::= */
   390,  /* (224) table_options ::= table_options COMMENT NK_STRING */
   390,  /* (225) table_options ::= table_options MAX_DELAY duration_list */
   390,  /* (226) table_options ::= table_options WATERMARK duration_list */
   390,  /* (227) table_options ::= table_options ROLLUP NK_LP rollup_func_list NK_RP */
   390,  /* (228) table_options ::= table_options TTL NK_INTEGER */
   390,  /* (229) table_options ::= table_options SMA NK_LP col_name_list NK_RP */
   390,  /* (230) table_options ::= table_options DELETE_MARK duration_list */
   395,  /* (231) alter_table_options ::= alter_table_option */
   395,  /* (232) alter_table_options ::= alter_table_options alter_table_option */
   407,  /* (233) alter_table_option ::= COMMENT NK_STRING */
   407,  /* (234) alter_table_option ::= TTL NK_INTEGER */
   405,  /* (235) duration_list ::= duration_literal */
   405,  /* (236) duration_list ::= duration_list NK_COMMA duration_literal */
   406,  /* (237) rollup_func_list ::= rollup_func_name */
   406,  /* (238) rollup_func_list ::= rollup_func_list NK_COMMA rollup_func_name */
   409,  /* (239) rollup_func_name ::= function_name */
   409,  /* (240) rollup_func_name ::= FIRST */
   409,  /* (241) rollup_func_name ::= LAST */
   403,  /* (242) col_name_list ::= col_name */
   403,  /* (243) col_name_list ::= col_name_list NK_COMMA col_name */
   411,  /* (244) col_name ::= column_name */
   352,  /* (245) cmd ::= SHOW DNODES */
   352,  /* (246) cmd ::= SHOW USERS */
   352,  /* (247) cmd ::= SHOW USER PRIVILEGES */
   352,  /* (248) cmd ::= SHOW db_kind_opt DATABASES */
   352,  /* (249) cmd ::= SHOW table_kind_db_name_cond_opt TABLES like_pattern_opt */
   352,  /* (250) cmd ::= SHOW db_name_cond_opt STABLES like_pattern_opt */
   352,  /* (251) cmd ::= SHOW db_name_cond_opt VGROUPS */
   352,  /* (252) cmd ::= SHOW MNODES */
   352,  /* (253) cmd ::= SHOW QNODES */
   352,  /* (254) cmd ::= SHOW FUNCTIONS */
   352,  /* (255) cmd ::= SHOW INDEXES FROM table_name_cond from_db_opt */
   352,  /* (256) cmd ::= SHOW INDEXES FROM db_name NK_DOT table_name */
   352,  /* (257) cmd ::= SHOW STREAMS */
   352,  /* (258) cmd ::= SHOW ACCOUNTS */
   352,  /* (259) cmd ::= SHOW APPS */
   352,  /* (260) cmd ::= SHOW CONNECTIONS */
   352,  /* (261) cmd ::= SHOW LICENCES */
   352,  /* (262) cmd ::= SHOW GRANTS */
   352,  /* (263) cmd ::= SHOW GRANTS FULL */
   352,  /* (264) cmd ::= SHOW GRANTS LOGS */
   352,  /* (265) cmd ::= SHOW CLUSTER MACHINES */
   352,  /* (266) cmd ::= SHOW CREATE DATABASE db_name */
   352,  /* (267) cmd ::= SHOW CREATE TABLE full_table_name */
   352,  /* (268) cmd ::= SHOW CREATE STABLE full_table_name */
   352,  /* (269) cmd ::= SHOW QUERIES */
   352,  /* (270) cmd ::= SHOW SCORES */
   352,  /* (271) cmd ::= SHOW TOPICS */
   352,  /* (272) cmd ::= SHOW VARIABLES */
   352,  /* (273) cmd ::= SHOW CLUSTER VARIABLES */
   352,  /* (274) cmd ::= SHOW LOCAL VARIABLES */
   352,  /* (275) cmd ::= SHOW DNODE NK_INTEGER VARIABLES like_pattern_opt */
   352,  /* (276) cmd ::= SHOW BNODES */
   352,  /* (277) cmd ::= SHOW SNODES */
   352,  /* (278) cmd ::= SHOW CLUSTER */
   352,  /* (279) cmd ::= SHOW TRANSACTIONS */
   352,  /* (280) cmd ::= SHOW TABLE DISTRIBUTED full_table_name */
   352,  /* (281) cmd ::= SHOW CONSUMERS */
   352,  /* (282) cmd ::= SHOW SUBSCRIPTIONS */
   352,  /* (283) cmd ::= SHOW TAGS FROM table_name_cond from_db_opt */
   352,  /* (284) cmd ::= SHOW TAGS FROM db_name NK_DOT table_name */
   352,  /* (285) cmd ::= SHOW TABLE TAGS tag_list_opt FROM table_name_cond from_db_opt */
   352,  /* (286) cmd ::= SHOW TABLE TAGS tag_list_opt FROM db_name NK_DOT table_name */
   352,  /* (287) cmd ::= SHOW VNODES ON DNODE NK_INTEGER */
   352,  /* (288) cmd ::= SHOW VNODES */
   352,  /* (289) cmd ::= SHOW db_name_cond_opt ALIVE */
   352,  /* (290) cmd ::= SHOW CLUSTER ALIVE */
   352,  /* (291) cmd ::= SHOW db_name_cond_opt VIEWS like_pattern_opt */
   352,  /* (292) cmd ::= SHOW CREATE VIEW full_table_name */
   352,  /* (293) cmd ::= SHOW COMPACTS */
   352,  /* (294) cmd ::= SHOW COMPACT NK_INTEGER */
   413,  /* (295) table_kind_db_name_cond_opt ::= */
   413,  /* (296) table_kind_db_name_cond_opt ::= table_kind */
   413,  /* (297) table_kind_db_name_cond_opt ::= db_name NK_DOT */
   413,  /* (298) table_kind_db_name_cond_opt ::= table_kind db_name NK_DOT */
   419,  /* (299) table_kind ::= NORMAL */
   419,  /* (300) table_kind ::= CHILD */
   415,  /* (301) db_name_cond_opt ::= */
   415,  /* (302) db_name_cond_opt ::= db_name NK_DOT */
   414,  /* (303) like_pattern_opt ::= */
   414,  /* (304) like_pattern_opt ::= LIKE NK_STRING */
   416,  /* (305) table_name_cond ::= table_name */
   417,  /* (306) from_db_opt ::= */
   417,  /* (307) from_db_opt ::= FROM db_name */
   418,  /* (308) tag_list_opt ::= */
   418,  /* (309) tag_list_opt ::= tag_item */
   418,  /* (310) tag_list_opt ::= tag_list_opt NK_COMMA tag_item */
   420,  /* (311) tag_item ::= TBNAME */
   420,  /* (312) tag_item ::= QTAGS */
   420,  /* (313) tag_item ::= column_name */
   420,  /* (314) tag_item ::= column_name column_alias */
   420,  /* (315) tag_item ::= column_name AS column_alias */
   412,  /* (316) db_kind_opt ::= */
   412,  /* (317) db_kind_opt ::= USER */
   412,  /* (318) db_kind_opt ::= SYSTEM */
   352,  /* (319) cmd ::= CREATE SMA INDEX not_exists_opt col_name ON full_table_name index_options */
   352,  /* (320) cmd ::= CREATE INDEX not_exists_opt col_name ON full_table_name NK_LP col_name_list NK_RP */
   352,  /* (321) cmd ::= DROP INDEX exists_opt full_index_name */
   423,  /* (322) full_index_name ::= index_name */
   423,  /* (323) full_index_name ::= db_name NK_DOT index_name */
   422,  /* (324) index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_RP sliding_opt sma_stream_opt */
   422,  /* (325) index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_COMMA duration_literal NK_RP sliding_opt sma_stream_opt */
   425,  /* (326) func_list ::= func */
   425,  /* (327) func_list ::= func_list NK_COMMA func */
   428,  /* (328) func ::= sma_func_name NK_LP expression_list NK_RP */
   429,  /* (329) sma_func_name ::= function_name */
   429,  /* (330) sma_func_name ::= COUNT */
   429,  /* (331) sma_func_name ::= FIRST */
   429,  /* (332) sma_func_name ::= LAST */
   429,  /* (333) sma_func_name ::= LAST_ROW */
   427,  /* (334) sma_stream_opt ::= */
   427,  /* (335) sma_stream_opt ::= sma_stream_opt WATERMARK duration_literal */
   427,  /* (336) sma_stream_opt ::= sma_stream_opt MAX_DELAY duration_literal */
   427,  /* (337) sma_stream_opt ::= sma_stream_opt DELETE_MARK duration_literal */
   430,  /* (338) with_meta ::= AS */
   430,  /* (339) with_meta ::= WITH META AS */
   430,  /* (340) with_meta ::= ONLY META AS */
   352,  /* (341) cmd ::= CREATE TOPIC not_exists_opt topic_name AS query_or_subquery */
   352,  /* (342) cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta DATABASE db_name */
   352,  /* (343) cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta STABLE full_table_name where_clause_opt */
   352,  /* (344) cmd ::= DROP TOPIC exists_opt topic_name */
   352,  /* (345) cmd ::= DROP CONSUMER GROUP exists_opt cgroup_name ON topic_name */
   352,  /* (346) cmd ::= DESC full_table_name */
   352,  /* (347) cmd ::= DESCRIBE full_table_name */
   352,  /* (348) cmd ::= RESET QUERY CACHE */
   352,  /* (349) cmd ::= EXPLAIN analyze_opt explain_options query_or_subquery */
   352,  /* (350) cmd ::= EXPLAIN analyze_opt explain_options insert_query */
   434,  /* (351) analyze_opt ::= */
   434,  /* (352) analyze_opt ::= ANALYZE */
   435,  /* (353) explain_options ::= */
   435,  /* (354) explain_options ::= explain_options VERBOSE NK_BOOL */
   435,  /* (355) explain_options ::= explain_options RATIO NK_FLOAT */
   352,  /* (356) cmd ::= CREATE or_replace_opt agg_func_opt FUNCTION not_exists_opt function_name AS NK_STRING OUTPUTTYPE type_name bufsize_opt language_opt */
   352,  /* (357) cmd ::= DROP FUNCTION exists_opt function_name */
   438,  /* (358) agg_func_opt ::= */
   438,  /* (359) agg_func_opt ::= AGGREGATE */
   439,  /* (360) bufsize_opt ::= */
   439,  /* (361) bufsize_opt ::= BUFSIZE NK_INTEGER */
   440,  /* (362) language_opt ::= */
   440,  /* (363) language_opt ::= LANGUAGE NK_STRING */
   437,  /* (364) or_replace_opt ::= */
   437,  /* (365) or_replace_opt ::= OR REPLACE */
   352,  /* (366) cmd ::= CREATE or_replace_opt VIEW full_view_name AS query_or_subquery */
   352,  /* (367) cmd ::= DROP VIEW exists_opt full_view_name */
   441,  /* (368) full_view_name ::= view_name */
   441,  /* (369) full_view_name ::= db_name NK_DOT view_name */
   352,  /* (370) cmd ::= CREATE STREAM not_exists_opt stream_name stream_options INTO full_table_name col_list_opt tag_def_or_ref_opt subtable_opt AS query_or_subquery */
   352,  /* (371) cmd ::= DROP STREAM exists_opt stream_name */
   352,  /* (372) cmd ::= PAUSE STREAM exists_opt stream_name */
   352,  /* (373) cmd ::= RESUME STREAM exists_opt ignore_opt stream_name */
   445,  /* (374) col_list_opt ::= */
   445,  /* (375) col_list_opt ::= NK_LP col_name_list NK_RP */
   446,  /* (376) tag_def_or_ref_opt ::= */
   446,  /* (377) tag_def_or_ref_opt ::= tags_def */
   446,  /* (378) tag_def_or_ref_opt ::= TAGS NK_LP col_name_list NK_RP */
   444,  /* (379) stream_options ::= */
   444,  /* (380) stream_options ::= stream_options TRIGGER AT_ONCE */
   444,  /* (381) stream_options ::= stream_options TRIGGER WINDOW_CLOSE */
   444,  /* (382) stream_options ::= stream_options TRIGGER MAX_DELAY duration_literal */
   444,  /* (383) stream_options ::= stream_options WATERMARK duration_literal */
   444,  /* (384) stream_options ::= stream_options IGNORE EXPIRED NK_INTEGER */
   444,  /* (385) stream_options ::= stream_options FILL_HISTORY NK_INTEGER */
   444,  /* (386) stream_options ::= stream_options DELETE_MARK duration_literal */
   444,  /* (387) stream_options ::= stream_options IGNORE UPDATE NK_INTEGER */
   447,  /* (388) subtable_opt ::= */
   447,  /* (389) subtable_opt ::= SUBTABLE NK_LP expression NK_RP */
   448,  /* (390) ignore_opt ::= */
   448,  /* (391) ignore_opt ::= IGNORE UNTREATED */
   352,  /* (392) cmd ::= KILL CONNECTION NK_INTEGER */
   352,  /* (393) cmd ::= KILL QUERY NK_STRING */
   352,  /* (394) cmd ::= KILL TRANSACTION NK_INTEGER */
   352,  /* (395) cmd ::= KILL COMPACT NK_INTEGER */
   352,  /* (396) cmd ::= BALANCE VGROUP */
   352,  /* (397) cmd ::= BALANCE VGROUP LEADER on_vgroup_id */
   352,  /* (398) cmd ::= MERGE VGROUP NK_INTEGER NK_INTEGER */
   352,  /* (399) cmd ::= REDISTRIBUTE VGROUP NK_INTEGER dnode_list */
   352,  /* (400) cmd ::= SPLIT VGROUP NK_INTEGER */
   450,  /* (401) on_vgroup_id ::= */
   450,  /* (402) on_vgroup_id ::= ON NK_INTEGER */
   451,  /* (403) dnode_list ::= DNODE NK_INTEGER */
   451,  /* (404) dnode_list ::= dnode_list DNODE NK_INTEGER */
   352,  /* (405) cmd ::= DELETE FROM full_table_name where_clause_opt */
   352,  /* (406) cmd ::= query_or_subquery */
   352,  /* (407) cmd ::= insert_query */
   436,  /* (408) insert_query ::= INSERT INTO full_table_name NK_LP col_name_list NK_RP query_or_subquery */
   436,  /* (409) insert_query ::= INSERT INTO full_table_name query_or_subquery */
   355,  /* (410) literal ::= NK_INTEGER */
   355,  /* (411) literal ::= NK_FLOAT */
   355,  /* (412) literal ::= NK_STRING */
   355,  /* (413) literal ::= NK_BOOL */
   355,  /* (414) literal ::= TIMESTAMP NK_STRING */
   355,  /* (415) literal ::= duration_literal */
   355,  /* (416) literal ::= NULL */
   355,  /* (417) literal ::= NK_QUESTION */
   408,  /* (418) duration_literal ::= NK_VARIABLE */
   384,  /* (419) signed ::= NK_INTEGER */
   384,  /* (420) signed ::= NK_PLUS NK_INTEGER */
   384,  /* (421) signed ::= NK_MINUS NK_INTEGER */
   384,  /* (422) signed ::= NK_FLOAT */
   384,  /* (423) signed ::= NK_PLUS NK_FLOAT */
   384,  /* (424) signed ::= NK_MINUS NK_FLOAT */
   398,  /* (425) signed_literal ::= signed */
   398,  /* (426) signed_literal ::= NK_STRING */
   398,  /* (427) signed_literal ::= NK_BOOL */
   398,  /* (428) signed_literal ::= TIMESTAMP NK_STRING */
   398,  /* (429) signed_literal ::= duration_literal */
   398,  /* (430) signed_literal ::= NULL */
   398,  /* (431) signed_literal ::= literal_func */
   398,  /* (432) signed_literal ::= NK_QUESTION */
   453,  /* (433) literal_list ::= signed_literal */
   453,  /* (434) literal_list ::= literal_list NK_COMMA signed_literal */
   367,  /* (435) db_name ::= NK_ID */
   368,  /* (436) table_name ::= NK_ID */
   396,  /* (437) column_name ::= NK_ID */
   410,  /* (438) function_name ::= NK_ID */
   442,  /* (439) view_name ::= NK_ID */
   454,  /* (440) table_alias ::= NK_ID */
   421,  /* (441) column_alias ::= NK_ID */
   421,  /* (442) column_alias ::= NK_ALIAS */
   360,  /* (443) user_name ::= NK_ID */
   369,  /* (444) topic_name ::= NK_ID */
   443,  /* (445) stream_name ::= NK_ID */
   433,  /* (446) cgroup_name ::= NK_ID */
   424,  /* (447) index_name ::= NK_ID */
   455,  /* (448) expr_or_subquery ::= expression */
   449,  /* (449) expression ::= literal */
   449,  /* (450) expression ::= pseudo_column */
   449,  /* (451) expression ::= column_reference */
   449,  /* (452) expression ::= function_expression */
   449,  /* (453) expression ::= case_when_expression */
   449,  /* (454) expression ::= NK_LP expression NK_RP */
   449,  /* (455) expression ::= NK_PLUS expr_or_subquery */
   449,  /* (456) expression ::= NK_MINUS expr_or_subquery */
   449,  /* (457) expression ::= expr_or_subquery NK_PLUS expr_or_subquery */
   449,  /* (458) expression ::= expr_or_subquery NK_MINUS expr_or_subquery */
   449,  /* (459) expression ::= expr_or_subquery NK_STAR expr_or_subquery */
   449,  /* (460) expression ::= expr_or_subquery NK_SLASH expr_or_subquery */
   449,  /* (461) expression ::= expr_or_subquery NK_REM expr_or_subquery */
   449,  /* (462) expression ::= column_reference NK_ARROW NK_STRING */
   449,  /* (463) expression ::= expr_or_subquery NK_BITAND expr_or_subquery */
   449,  /* (464) expression ::= expr_or_subquery NK_BITOR expr_or_subquery */
   401,  /* (465) expression_list ::= expr_or_subquery */
   401,  /* (466) expression_list ::= expression_list NK_COMMA expr_or_subquery */
   457,  /* (467) column_reference ::= column_name */
   457,  /* (468) column_reference ::= table_name NK_DOT column_name */
   457,  /* (469) column_reference ::= NK_ALIAS */
   457,  /* (470) column_reference ::= table_name NK_DOT NK_ALIAS */
   456,  /* (471) pseudo_column ::= ROWTS */
   456,  /* (472) pseudo_column ::= TBNAME */
   456,  /* (473) pseudo_column ::= table_name NK_DOT TBNAME */
   456,  /* (474) pseudo_column ::= QSTART */
   456,  /* (475) pseudo_column ::= QEND */
   456,  /* (476) pseudo_column ::= QDURATION */
   456,  /* (477) pseudo_column ::= WSTART */
   456,  /* (478) pseudo_column ::= WEND */
   456,  /* (479) pseudo_column ::= WDURATION */
   456,  /* (480) pseudo_column ::= IROWTS */
   456,  /* (481) pseudo_column ::= ISFILLED */
   456,  /* (482) pseudo_column ::= QTAGS */
   458,  /* (483) function_expression ::= function_name NK_LP expression_list NK_RP */
   458,  /* (484) function_expression ::= star_func NK_LP star_func_para_list NK_RP */
   458,  /* (485) function_expression ::= CAST NK_LP expr_or_subquery AS type_name NK_RP */
   458,  /* (486) function_expression ::= literal_func */
   452,  /* (487) literal_func ::= noarg_func NK_LP NK_RP */
   452,  /* (488) literal_func ::= NOW */
   462,  /* (489) noarg_func ::= NOW */
   462,  /* (490) noarg_func ::= TODAY */
   462,  /* (491) noarg_func ::= TIMEZONE */
   462,  /* (492) noarg_func ::= DATABASE */
   462,  /* (493) noarg_func ::= CLIENT_VERSION */
   462,  /* (494) noarg_func ::= SERVER_VERSION */
   462,  /* (495) noarg_func ::= SERVER_STATUS */
   462,  /* (496) noarg_func ::= CURRENT_USER */
   462,  /* (497) noarg_func ::= USER */
   460,  /* (498) star_func ::= COUNT */
   460,  /* (499) star_func ::= FIRST */
   460,  /* (500) star_func ::= LAST */
   460,  /* (501) star_func ::= LAST_ROW */
   461,  /* (502) star_func_para_list ::= NK_STAR */
   461,  /* (503) star_func_para_list ::= other_para_list */
   463,  /* (504) other_para_list ::= star_func_para */
   463,  /* (505) other_para_list ::= other_para_list NK_COMMA star_func_para */
   464,  /* (506) star_func_para ::= expr_or_subquery */
   464,  /* (507) star_func_para ::= table_name NK_DOT NK_STAR */
   459,  /* (508) case_when_expression ::= CASE when_then_list case_when_else_opt END */
   459,  /* (509) case_when_expression ::= CASE common_expression when_then_list case_when_else_opt END */
   465,  /* (510) when_then_list ::= when_then_expr */
   465,  /* (511) when_then_list ::= when_then_list when_then_expr */
   468,  /* (512) when_then_expr ::= WHEN common_expression THEN common_expression */
   466,  /* (513) case_when_else_opt ::= */
   466,  /* (514) case_when_else_opt ::= ELSE common_expression */
   469,  /* (515) predicate ::= expr_or_subquery compare_op expr_or_subquery */
   469,  /* (516) predicate ::= expr_or_subquery BETWEEN expr_or_subquery AND expr_or_subquery */
   469,  /* (517) predicate ::= expr_or_subquery NOT BETWEEN expr_or_subquery AND expr_or_subquery */
   469,  /* (518) predicate ::= expr_or_subquery IS NULL */
   469,  /* (519) predicate ::= expr_or_subquery IS NOT NULL */
   469,  /* (520) predicate ::= expr_or_subquery in_op in_predicate_value */
   470,  /* (521) compare_op ::= NK_LT */
   470,  /* (522) compare_op ::= NK_GT */
   470,  /* (523) compare_op ::= NK_LE */
   470,  /* (524) compare_op ::= NK_GE */
   470,  /* (525) compare_op ::= NK_NE */
   470,  /* (526) compare_op ::= NK_EQ */
   470,  /* (527) compare_op ::= LIKE */
   470,  /* (528) compare_op ::= NOT LIKE */
   470,  /* (529) compare_op ::= MATCH */
   470,  /* (530) compare_op ::= NMATCH */
   470,  /* (531) compare_op ::= CONTAINS */
   471,  /* (532) in_op ::= IN */
   471,  /* (533) in_op ::= NOT IN */
   472,  /* (534) in_predicate_value ::= NK_LP literal_list NK_RP */
   473,  /* (535) boolean_value_expression ::= boolean_primary */
   473,  /* (536) boolean_value_expression ::= NOT boolean_primary */
   473,  /* (537) boolean_value_expression ::= boolean_value_expression OR boolean_value_expression */
   473,  /* (538) boolean_value_expression ::= boolean_value_expression AND boolean_value_expression */
   474,  /* (539) boolean_primary ::= predicate */
   474,  /* (540) boolean_primary ::= NK_LP boolean_value_expression NK_RP */
   467,  /* (541) common_expression ::= expr_or_subquery */
   467,  /* (542) common_expression ::= boolean_value_expression */
   475,  /* (543) from_clause_opt ::= */
   475,  /* (544) from_clause_opt ::= FROM table_reference_list */
   476,  /* (545) table_reference_list ::= table_reference */
   476,  /* (546) table_reference_list ::= table_reference_list NK_COMMA table_reference */
   477,  /* (547) table_reference ::= table_primary */
   477,  /* (548) table_reference ::= joined_table */
   478,  /* (549) table_primary ::= table_name alias_opt */
   478,  /* (550) table_primary ::= db_name NK_DOT table_name alias_opt */
   478,  /* (551) table_primary ::= subquery alias_opt */
   478,  /* (552) table_primary ::= parenthesized_joined_table */
   480,  /* (553) alias_opt ::= */
   480,  /* (554) alias_opt ::= table_alias */
   480,  /* (555) alias_opt ::= AS table_alias */
   482,  /* (556) parenthesized_joined_table ::= NK_LP joined_table NK_RP */
   482,  /* (557) parenthesized_joined_table ::= NK_LP parenthesized_joined_table NK_RP */
   479,  /* (558) joined_table ::= table_reference join_type JOIN table_reference ON search_condition */
   483,  /* (559) join_type ::= */
   483,  /* (560) join_type ::= INNER */
   484,  /* (561) query_specification ::= SELECT hint_list set_quantifier_opt tag_mode_opt select_list from_clause_opt where_clause_opt partition_by_clause_opt range_opt every_opt fill_opt twindow_clause_opt group_by_clause_opt having_clause_opt */
   485,  /* (562) hint_list ::= */
   485,  /* (563) hint_list ::= NK_HINT */
   487,  /* (564) tag_mode_opt ::= */
   487,  /* (565) tag_mode_opt ::= TAGS */
   486,  /* (566) set_quantifier_opt ::= */
   486,  /* (567) set_quantifier_opt ::= DISTINCT */
   486,  /* (568) set_quantifier_opt ::= ALL */
   488,  /* (569) select_list ::= select_item */
   488,  /* (570) select_list ::= select_list NK_COMMA select_item */
   496,  /* (571) select_item ::= NK_STAR */
   496,  /* (572) select_item ::= common_expression */
   496,  /* (573) select_item ::= common_expression column_alias */
   496,  /* (574) select_item ::= common_expression AS column_alias */
   496,  /* (575) select_item ::= table_name NK_DOT NK_STAR */
   432,  /* (576) where_clause_opt ::= */
   432,  /* (577) where_clause_opt ::= WHERE search_condition */
   489,  /* (578) partition_by_clause_opt ::= */
   489,  /* (579) partition_by_clause_opt ::= PARTITION BY partition_list */
   497,  /* (580) partition_list ::= partition_item */
   497,  /* (581) partition_list ::= partition_list NK_COMMA partition_item */
   498,  /* (582) partition_item ::= expr_or_subquery */
   498,  /* (583) partition_item ::= expr_or_subquery column_alias */
   498,  /* (584) partition_item ::= expr_or_subquery AS column_alias */
   493,  /* (585) twindow_clause_opt ::= */
   493,  /* (586) twindow_clause_opt ::= SESSION NK_LP column_reference NK_COMMA interval_sliding_duration_literal NK_RP */
   493,  /* (587) twindow_clause_opt ::= STATE_WINDOW NK_LP expr_or_subquery NK_RP */
   493,  /* (588) twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
   493,  /* (589) twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_COMMA interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
   493,  /* (590) twindow_clause_opt ::= EVENT_WINDOW START WITH search_condition END WITH search_condition */
   493,  /* (591) twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_RP */
   493,  /* (592) twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
   426,  /* (593) sliding_opt ::= */
   426,  /* (594) sliding_opt ::= SLIDING NK_LP interval_sliding_duration_literal NK_RP */
   499,  /* (595) interval_sliding_duration_literal ::= NK_VARIABLE */
   499,  /* (596) interval_sliding_duration_literal ::= NK_STRING */
   499,  /* (597) interval_sliding_duration_literal ::= NK_INTEGER */
   492,  /* (598) fill_opt ::= */
   492,  /* (599) fill_opt ::= FILL NK_LP fill_mode NK_RP */
   492,  /* (600) fill_opt ::= FILL NK_LP VALUE NK_COMMA expression_list NK_RP */
   492,  /* (601) fill_opt ::= FILL NK_LP VALUE_F NK_COMMA expression_list NK_RP */
   500,  /* (602) fill_mode ::= NONE */
   500,  /* (603) fill_mode ::= PREV */
   500,  /* (604) fill_mode ::= NULL */
   500,  /* (605) fill_mode ::= NULL_F */
   500,  /* (606) fill_mode ::= LINEAR */
   500,  /* (607) fill_mode ::= NEXT */
   494,  /* (608) group_by_clause_opt ::= */
   494,  /* (609) group_by_clause_opt ::= GROUP BY group_by_list */
   501,  /* (610) group_by_list ::= expr_or_subquery */
   501,  /* (611) group_by_list ::= group_by_list NK_COMMA expr_or_subquery */
   495,  /* (612) having_clause_opt ::= */
   495,  /* (613) having_clause_opt ::= HAVING search_condition */
   490,  /* (614) range_opt ::= */
   490,  /* (615) range_opt ::= RANGE NK_LP expr_or_subquery NK_COMMA expr_or_subquery NK_RP */
   490,  /* (616) range_opt ::= RANGE NK_LP expr_or_subquery NK_RP */
   491,  /* (617) every_opt ::= */
   491,  /* (618) every_opt ::= EVERY NK_LP duration_literal NK_RP */
   502,  /* (619) query_expression ::= query_simple order_by_clause_opt slimit_clause_opt limit_clause_opt */
   503,  /* (620) query_simple ::= query_specification */
   503,  /* (621) query_simple ::= union_query_expression */
   507,  /* (622) union_query_expression ::= query_simple_or_subquery UNION ALL query_simple_or_subquery */
   507,  /* (623) union_query_expression ::= query_simple_or_subquery UNION query_simple_or_subquery */
   508,  /* (624) query_simple_or_subquery ::= query_simple */
   508,  /* (625) query_simple_or_subquery ::= subquery */
   431,  /* (626) query_or_subquery ::= query_expression */
   431,  /* (627) query_or_subquery ::= subquery */
   504,  /* (628) order_by_clause_opt ::= */
   504,  /* (629) order_by_clause_opt ::= ORDER BY sort_specification_list */
   505,  /* (630) slimit_clause_opt ::= */
   505,  /* (631) slimit_clause_opt ::= SLIMIT NK_INTEGER */
   505,  /* (632) slimit_clause_opt ::= SLIMIT NK_INTEGER SOFFSET NK_INTEGER */
   505,  /* (633) slimit_clause_opt ::= SLIMIT NK_INTEGER NK_COMMA NK_INTEGER */
   506,  /* (634) limit_clause_opt ::= */
   506,  /* (635) limit_clause_opt ::= LIMIT NK_INTEGER */
   506,  /* (636) limit_clause_opt ::= LIMIT NK_INTEGER OFFSET NK_INTEGER */
   506,  /* (637) limit_clause_opt ::= LIMIT NK_INTEGER NK_COMMA NK_INTEGER */
   481,  /* (638) subquery ::= NK_LP query_expression NK_RP */
   481,  /* (639) subquery ::= NK_LP subquery NK_RP */
   370,  /* (640) search_condition ::= common_expression */
   509,  /* (641) sort_specification_list ::= sort_specification */
   509,  /* (642) sort_specification_list ::= sort_specification_list NK_COMMA sort_specification */
   510,  /* (643) sort_specification ::= expr_or_subquery ordering_specification_opt null_ordering_opt */
   511,  /* (644) ordering_specification_opt ::= */
   511,  /* (645) ordering_specification_opt ::= ASC */
   511,  /* (646) ordering_specification_opt ::= DESC */
   512,  /* (647) null_ordering_opt ::= */
   512,  /* (648) null_ordering_opt ::= NULLS FIRST */
   512,  /* (649) null_ordering_opt ::= NULLS LAST */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -6,  /* (0) cmd ::= CREATE ACCOUNT NK_ID PASS NK_STRING account_options */
   -4,  /* (1) cmd ::= ALTER ACCOUNT NK_ID alter_account_options */
    0,  /* (2) account_options ::= */
   -3,  /* (3) account_options ::= account_options PPS literal */
   -3,  /* (4) account_options ::= account_options TSERIES literal */
   -3,  /* (5) account_options ::= account_options STORAGE literal */
   -3,  /* (6) account_options ::= account_options STREAMS literal */
   -3,  /* (7) account_options ::= account_options QTIME literal */
   -3,  /* (8) account_options ::= account_options DBS literal */
   -3,  /* (9) account_options ::= account_options USERS literal */
   -3,  /* (10) account_options ::= account_options CONNS literal */
   -3,  /* (11) account_options ::= account_options STATE literal */
   -1,  /* (12) alter_account_options ::= alter_account_option */
   -2,  /* (13) alter_account_options ::= alter_account_options alter_account_option */
   -2,  /* (14) alter_account_option ::= PASS literal */
   -2,  /* (15) alter_account_option ::= PPS literal */
   -2,  /* (16) alter_account_option ::= TSERIES literal */
   -2,  /* (17) alter_account_option ::= STORAGE literal */
   -2,  /* (18) alter_account_option ::= STREAMS literal */
   -2,  /* (19) alter_account_option ::= QTIME literal */
   -2,  /* (20) alter_account_option ::= DBS literal */
   -2,  /* (21) alter_account_option ::= USERS literal */
   -2,  /* (22) alter_account_option ::= CONNS literal */
   -2,  /* (23) alter_account_option ::= STATE literal */
   -1,  /* (24) ip_range_list ::= NK_STRING */
   -3,  /* (25) ip_range_list ::= ip_range_list NK_COMMA NK_STRING */
   -2,  /* (26) white_list ::= HOST ip_range_list */
    0,  /* (27) white_list_opt ::= */
   -1,  /* (28) white_list_opt ::= white_list */
   -7,  /* (29) cmd ::= CREATE USER user_name PASS NK_STRING sysinfo_opt white_list_opt */
   -5,  /* (30) cmd ::= ALTER USER user_name PASS NK_STRING */
   -5,  /* (31) cmd ::= ALTER USER user_name ENABLE NK_INTEGER */
   -5,  /* (32) cmd ::= ALTER USER user_name SYSINFO NK_INTEGER */
   -5,  /* (33) cmd ::= ALTER USER user_name ADD white_list */
   -5,  /* (34) cmd ::= ALTER USER user_name DROP white_list */
   -3,  /* (35) cmd ::= DROP USER user_name */
    0,  /* (36) sysinfo_opt ::= */
   -2,  /* (37) sysinfo_opt ::= SYSINFO NK_INTEGER */
   -7,  /* (38) cmd ::= GRANT privileges ON priv_level with_opt TO user_name */
   -7,  /* (39) cmd ::= REVOKE privileges ON priv_level with_opt FROM user_name */
   -1,  /* (40) privileges ::= ALL */
   -1,  /* (41) privileges ::= priv_type_list */
   -1,  /* (42) privileges ::= SUBSCRIBE */
   -1,  /* (43) priv_type_list ::= priv_type */
   -3,  /* (44) priv_type_list ::= priv_type_list NK_COMMA priv_type */
   -1,  /* (45) priv_type ::= READ */
   -1,  /* (46) priv_type ::= WRITE */
   -1,  /* (47) priv_type ::= ALTER */
   -3,  /* (48) priv_level ::= NK_STAR NK_DOT NK_STAR */
   -3,  /* (49) priv_level ::= db_name NK_DOT NK_STAR */
   -3,  /* (50) priv_level ::= db_name NK_DOT table_name */
   -1,  /* (51) priv_level ::= topic_name */
    0,  /* (52) with_opt ::= */
   -2,  /* (53) with_opt ::= WITH search_condition */
   -3,  /* (54) cmd ::= CREATE DNODE dnode_endpoint */
   -5,  /* (55) cmd ::= CREATE DNODE dnode_endpoint PORT NK_INTEGER */
   -4,  /* (56) cmd ::= DROP DNODE NK_INTEGER force_opt */
   -4,  /* (57) cmd ::= DROP DNODE dnode_endpoint force_opt */
   -4,  /* (58) cmd ::= DROP DNODE NK_INTEGER unsafe_opt */
   -4,  /* (59) cmd ::= DROP DNODE dnode_endpoint unsafe_opt */
   -4,  /* (60) cmd ::= ALTER DNODE NK_INTEGER NK_STRING */
   -5,  /* (61) cmd ::= ALTER DNODE NK_INTEGER NK_STRING NK_STRING */
   -4,  /* (62) cmd ::= ALTER ALL DNODES NK_STRING */
   -5,  /* (63) cmd ::= ALTER ALL DNODES NK_STRING NK_STRING */
   -3,  /* (64) cmd ::= RESTORE DNODE NK_INTEGER */
   -1,  /* (65) dnode_endpoint ::= NK_STRING */
   -1,  /* (66) dnode_endpoint ::= NK_ID */
   -1,  /* (67) dnode_endpoint ::= NK_IPTOKEN */
    0,  /* (68) force_opt ::= */
   -1,  /* (69) force_opt ::= FORCE */
   -1,  /* (70) unsafe_opt ::= UNSAFE */
   -3,  /* (71) cmd ::= ALTER CLUSTER NK_STRING */
   -4,  /* (72) cmd ::= ALTER CLUSTER NK_STRING NK_STRING */
   -3,  /* (73) cmd ::= ALTER LOCAL NK_STRING */
   -4,  /* (74) cmd ::= ALTER LOCAL NK_STRING NK_STRING */
   -5,  /* (75) cmd ::= CREATE QNODE ON DNODE NK_INTEGER */
   -5,  /* (76) cmd ::= DROP QNODE ON DNODE NK_INTEGER */
   -5,  /* (77) cmd ::= RESTORE QNODE ON DNODE NK_INTEGER */
   -5,  /* (78) cmd ::= CREATE BNODE ON DNODE NK_INTEGER */
   -5,  /* (79) cmd ::= DROP BNODE ON DNODE NK_INTEGER */
   -5,  /* (80) cmd ::= CREATE SNODE ON DNODE NK_INTEGER */
   -5,  /* (81) cmd ::= DROP SNODE ON DNODE NK_INTEGER */
   -5,  /* (82) cmd ::= CREATE MNODE ON DNODE NK_INTEGER */
   -5,  /* (83) cmd ::= DROP MNODE ON DNODE NK_INTEGER */
   -5,  /* (84) cmd ::= RESTORE MNODE ON DNODE NK_INTEGER */
   -5,  /* (85) cmd ::= RESTORE VNODE ON DNODE NK_INTEGER */
   -5,  /* (86) cmd ::= CREATE DATABASE not_exists_opt db_name db_options */
   -4,  /* (87) cmd ::= DROP DATABASE exists_opt db_name */
   -2,  /* (88) cmd ::= USE db_name */
   -4,  /* (89) cmd ::= ALTER DATABASE db_name alter_db_options */
   -3,  /* (90) cmd ::= FLUSH DATABASE db_name */
   -4,  /* (91) cmd ::= TRIM DATABASE db_name speed_opt */
   -5,  /* (92) cmd ::= COMPACT DATABASE db_name start_opt end_opt */
   -3,  /* (93) not_exists_opt ::= IF NOT EXISTS */
    0,  /* (94) not_exists_opt ::= */
   -2,  /* (95) exists_opt ::= IF EXISTS */
    0,  /* (96) exists_opt ::= */
    0,  /* (97) db_options ::= */
   -3,  /* (98) db_options ::= db_options BUFFER NK_INTEGER */
   -3,  /* (99) db_options ::= db_options CACHEMODEL NK_STRING */
   -3,  /* (100) db_options ::= db_options CACHESIZE NK_INTEGER */
   -3,  /* (101) db_options ::= db_options COMP NK_INTEGER */
   -3,  /* (102) db_options ::= db_options DURATION NK_INTEGER */
   -3,  /* (103) db_options ::= db_options DURATION NK_VARIABLE */
   -3,  /* (104) db_options ::= db_options MAXROWS NK_INTEGER */
   -3,  /* (105) db_options ::= db_options MINROWS NK_INTEGER */
   -3,  /* (106) db_options ::= db_options KEEP integer_list */
   -3,  /* (107) db_options ::= db_options KEEP variable_list */
   -3,  /* (108) db_options ::= db_options PAGES NK_INTEGER */
   -3,  /* (109) db_options ::= db_options PAGESIZE NK_INTEGER */
   -3,  /* (110) db_options ::= db_options TSDB_PAGESIZE NK_INTEGER */
   -3,  /* (111) db_options ::= db_options PRECISION NK_STRING */
   -3,  /* (112) db_options ::= db_options REPLICA NK_INTEGER */
   -3,  /* (113) db_options ::= db_options VGROUPS NK_INTEGER */
   -3,  /* (114) db_options ::= db_options SINGLE_STABLE NK_INTEGER */
   -3,  /* (115) db_options ::= db_options RETENTIONS retention_list */
   -3,  /* (116) db_options ::= db_options SCHEMALESS NK_INTEGER */
   -3,  /* (117) db_options ::= db_options WAL_LEVEL NK_INTEGER */
   -3,  /* (118) db_options ::= db_options WAL_FSYNC_PERIOD NK_INTEGER */
   -3,  /* (119) db_options ::= db_options WAL_RETENTION_PERIOD NK_INTEGER */
   -4,  /* (120) db_options ::= db_options WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
   -3,  /* (121) db_options ::= db_options WAL_RETENTION_SIZE NK_INTEGER */
   -4,  /* (122) db_options ::= db_options WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
   -3,  /* (123) db_options ::= db_options WAL_ROLL_PERIOD NK_INTEGER */
   -3,  /* (124) db_options ::= db_options WAL_SEGMENT_SIZE NK_INTEGER */
   -3,  /* (125) db_options ::= db_options STT_TRIGGER NK_INTEGER */
   -3,  /* (126) db_options ::= db_options TABLE_PREFIX signed */
   -3,  /* (127) db_options ::= db_options TABLE_SUFFIX signed */
   -3,  /* (128) db_options ::= db_options KEEP_TIME_OFFSET NK_INTEGER */
   -1,  /* (129) alter_db_options ::= alter_db_option */
   -2,  /* (130) alter_db_options ::= alter_db_options alter_db_option */
   -2,  /* (131) alter_db_option ::= BUFFER NK_INTEGER */
   -2,  /* (132) alter_db_option ::= CACHEMODEL NK_STRING */
   -2,  /* (133) alter_db_option ::= CACHESIZE NK_INTEGER */
   -2,  /* (134) alter_db_option ::= WAL_FSYNC_PERIOD NK_INTEGER */
   -2,  /* (135) alter_db_option ::= KEEP integer_list */
   -2,  /* (136) alter_db_option ::= KEEP variable_list */
   -2,  /* (137) alter_db_option ::= PAGES NK_INTEGER */
   -2,  /* (138) alter_db_option ::= REPLICA NK_INTEGER */
   -2,  /* (139) alter_db_option ::= WAL_LEVEL NK_INTEGER */
   -2,  /* (140) alter_db_option ::= STT_TRIGGER NK_INTEGER */
   -2,  /* (141) alter_db_option ::= MINROWS NK_INTEGER */
   -2,  /* (142) alter_db_option ::= WAL_RETENTION_PERIOD NK_INTEGER */
   -3,  /* (143) alter_db_option ::= WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
   -2,  /* (144) alter_db_option ::= WAL_RETENTION_SIZE NK_INTEGER */
   -3,  /* (145) alter_db_option ::= WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
   -2,  /* (146) alter_db_option ::= KEEP_TIME_OFFSET NK_INTEGER */
   -1,  /* (147) integer_list ::= NK_INTEGER */
   -3,  /* (148) integer_list ::= integer_list NK_COMMA NK_INTEGER */
   -1,  /* (149) variable_list ::= NK_VARIABLE */
   -3,  /* (150) variable_list ::= variable_list NK_COMMA NK_VARIABLE */
   -1,  /* (151) retention_list ::= retention */
   -3,  /* (152) retention_list ::= retention_list NK_COMMA retention */
   -3,  /* (153) retention ::= NK_VARIABLE NK_COLON NK_VARIABLE */
   -3,  /* (154) retention ::= NK_MINUS NK_COLON NK_VARIABLE */
    0,  /* (155) speed_opt ::= */
   -2,  /* (156) speed_opt ::= BWLIMIT NK_INTEGER */
    0,  /* (157) start_opt ::= */
   -3,  /* (158) start_opt ::= START WITH NK_INTEGER */
   -3,  /* (159) start_opt ::= START WITH NK_STRING */
   -4,  /* (160) start_opt ::= START WITH TIMESTAMP NK_STRING */
    0,  /* (161) end_opt ::= */
   -3,  /* (162) end_opt ::= END WITH NK_INTEGER */
   -3,  /* (163) end_opt ::= END WITH NK_STRING */
   -4,  /* (164) end_opt ::= END WITH TIMESTAMP NK_STRING */
   -9,  /* (165) cmd ::= CREATE TABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def_opt table_options */
   -3,  /* (166) cmd ::= CREATE TABLE multi_create_clause */
   -9,  /* (167) cmd ::= CREATE STABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def table_options */
   -3,  /* (168) cmd ::= DROP TABLE multi_drop_clause */
   -4,  /* (169) cmd ::= DROP STABLE exists_opt full_table_name */
   -3,  /* (170) cmd ::= ALTER TABLE alter_table_clause */
   -3,  /* (171) cmd ::= ALTER STABLE alter_table_clause */
   -2,  /* (172) alter_table_clause ::= full_table_name alter_table_options */
   -5,  /* (173) alter_table_clause ::= full_table_name ADD COLUMN column_name type_name */
   -4,  /* (174) alter_table_clause ::= full_table_name DROP COLUMN column_name */
   -5,  /* (175) alter_table_clause ::= full_table_name MODIFY COLUMN column_name type_name */
   -5,  /* (176) alter_table_clause ::= full_table_name RENAME COLUMN column_name column_name */
   -5,  /* (177) alter_table_clause ::= full_table_name ADD TAG column_name type_name */
   -4,  /* (178) alter_table_clause ::= full_table_name DROP TAG column_name */
   -5,  /* (179) alter_table_clause ::= full_table_name MODIFY TAG column_name type_name */
   -5,  /* (180) alter_table_clause ::= full_table_name RENAME TAG column_name column_name */
   -6,  /* (181) alter_table_clause ::= full_table_name SET TAG column_name NK_EQ signed_literal */
   -1,  /* (182) multi_create_clause ::= create_subtable_clause */
   -2,  /* (183) multi_create_clause ::= multi_create_clause create_subtable_clause */
  -10,  /* (184) create_subtable_clause ::= not_exists_opt full_table_name USING full_table_name specific_cols_opt TAGS NK_LP expression_list NK_RP table_options */
   -1,  /* (185) multi_drop_clause ::= drop_table_clause */
   -3,  /* (186) multi_drop_clause ::= multi_drop_clause NK_COMMA drop_table_clause */
   -2,  /* (187) drop_table_clause ::= exists_opt full_table_name */
    0,  /* (188) specific_cols_opt ::= */
   -3,  /* (189) specific_cols_opt ::= NK_LP col_name_list NK_RP */
   -1,  /* (190) full_table_name ::= table_name */
   -3,  /* (191) full_table_name ::= db_name NK_DOT table_name */
   -1,  /* (192) column_def_list ::= column_def */
   -3,  /* (193) column_def_list ::= column_def_list NK_COMMA column_def */
   -2,  /* (194) column_def ::= column_name type_name */
   -4,  /* (195) column_def ::= column_name type_name PRIMARY KEY */
   -1,  /* (196) type_name ::= BOOL */
   -1,  /* (197) type_name ::= TINYINT */
   -1,  /* (198) type_name ::= SMALLINT */
   -1,  /* (199) type_name ::= INT */
   -1,  /* (200) type_name ::= INTEGER */
   -1,  /* (201) type_name ::= BIGINT */
   -1,  /* (202) type_name ::= FLOAT */
   -1,  /* (203) type_name ::= DOUBLE */
   -4,  /* (204) type_name ::= BINARY NK_LP NK_INTEGER NK_RP */
   -1,  /* (205) type_name ::= TIMESTAMP */
   -4,  /* (206) type_name ::= NCHAR NK_LP NK_INTEGER NK_RP */
   -2,  /* (207) type_name ::= TINYINT UNSIGNED */
   -2,  /* (208) type_name ::= SMALLINT UNSIGNED */
   -2,  /* (209) type_name ::= INT UNSIGNED */
   -2,  /* (210) type_name ::= BIGINT UNSIGNED */
   -1,  /* (211) type_name ::= JSON */
   -4,  /* (212) type_name ::= VARCHAR NK_LP NK_INTEGER NK_RP */
   -1,  /* (213) type_name ::= MEDIUMBLOB */
   -1,  /* (214) type_name ::= BLOB */
   -4,  /* (215) type_name ::= VARBINARY NK_LP NK_INTEGER NK_RP */
   -4,  /* (216) type_name ::= GEOMETRY NK_LP NK_INTEGER NK_RP */
   -1,  /* (217) type_name ::= DECIMAL */
   -4,  /* (218) type_name ::= DECIMAL NK_LP NK_INTEGER NK_RP */
   -6,  /* (219) type_name ::= DECIMAL NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
    0,  /* (220) tags_def_opt ::= */
   -1,  /* (221) tags_def_opt ::= tags_def */
   -4,  /* (222) tags_def ::= TAGS NK_LP column_def_list NK_RP */
    0,  /* (223) table_options ::= */
   -3,  /* (224) table_options ::= table_options COMMENT NK_STRING */
   -3,  /* (225) table_options ::= table_options MAX_DELAY duration_list */
   -3,  /* (226) table_options ::= table_options WATERMARK duration_list */
   -5,  /* (227) table_options ::= table_options ROLLUP NK_LP rollup_func_list NK_RP */
   -3,  /* (228) table_options ::= table_options TTL NK_INTEGER */
   -5,  /* (229) table_options ::= table_options SMA NK_LP col_name_list NK_RP */
   -3,  /* (230) table_options ::= table_options DELETE_MARK duration_list */
   -1,  /* (231) alter_table_options ::= alter_table_option */
   -2,  /* (232) alter_table_options ::= alter_table_options alter_table_option */
   -2,  /* (233) alter_table_option ::= COMMENT NK_STRING */
   -2,  /* (234) alter_table_option ::= TTL NK_INTEGER */
   -1,  /* (235) duration_list ::= duration_literal */
   -3,  /* (236) duration_list ::= duration_list NK_COMMA duration_literal */
   -1,  /* (237) rollup_func_list ::= rollup_func_name */
   -3,  /* (238) rollup_func_list ::= rollup_func_list NK_COMMA rollup_func_name */
   -1,  /* (239) rollup_func_name ::= function_name */
   -1,  /* (240) rollup_func_name ::= FIRST */
   -1,  /* (241) rollup_func_name ::= LAST */
   -1,  /* (242) col_name_list ::= col_name */
   -3,  /* (243) col_name_list ::= col_name_list NK_COMMA col_name */
   -1,  /* (244) col_name ::= column_name */
   -2,  /* (245) cmd ::= SHOW DNODES */
   -2,  /* (246) cmd ::= SHOW USERS */
   -3,  /* (247) cmd ::= SHOW USER PRIVILEGES */
   -3,  /* (248) cmd ::= SHOW db_kind_opt DATABASES */
   -4,  /* (249) cmd ::= SHOW table_kind_db_name_cond_opt TABLES like_pattern_opt */
   -4,  /* (250) cmd ::= SHOW db_name_cond_opt STABLES like_pattern_opt */
   -3,  /* (251) cmd ::= SHOW db_name_cond_opt VGROUPS */
   -2,  /* (252) cmd ::= SHOW MNODES */
   -2,  /* (253) cmd ::= SHOW QNODES */
   -2,  /* (254) cmd ::= SHOW FUNCTIONS */
   -5,  /* (255) cmd ::= SHOW INDEXES FROM table_name_cond from_db_opt */
   -6,  /* (256) cmd ::= SHOW INDEXES FROM db_name NK_DOT table_name */
   -2,  /* (257) cmd ::= SHOW STREAMS */
   -2,  /* (258) cmd ::= SHOW ACCOUNTS */
   -2,  /* (259) cmd ::= SHOW APPS */
   -2,  /* (260) cmd ::= SHOW CONNECTIONS */
   -2,  /* (261) cmd ::= SHOW LICENCES */
   -2,  /* (262) cmd ::= SHOW GRANTS */
   -3,  /* (263) cmd ::= SHOW GRANTS FULL */
   -3,  /* (264) cmd ::= SHOW GRANTS LOGS */
   -3,  /* (265) cmd ::= SHOW CLUSTER MACHINES */
   -4,  /* (266) cmd ::= SHOW CREATE DATABASE db_name */
   -4,  /* (267) cmd ::= SHOW CREATE TABLE full_table_name */
   -4,  /* (268) cmd ::= SHOW CREATE STABLE full_table_name */
   -2,  /* (269) cmd ::= SHOW QUERIES */
   -2,  /* (270) cmd ::= SHOW SCORES */
   -2,  /* (271) cmd ::= SHOW TOPICS */
   -2,  /* (272) cmd ::= SHOW VARIABLES */
   -3,  /* (273) cmd ::= SHOW CLUSTER VARIABLES */
   -3,  /* (274) cmd ::= SHOW LOCAL VARIABLES */
   -5,  /* (275) cmd ::= SHOW DNODE NK_INTEGER VARIABLES like_pattern_opt */
   -2,  /* (276) cmd ::= SHOW BNODES */
   -2,  /* (277) cmd ::= SHOW SNODES */
   -2,  /* (278) cmd ::= SHOW CLUSTER */
   -2,  /* (279) cmd ::= SHOW TRANSACTIONS */
   -4,  /* (280) cmd ::= SHOW TABLE DISTRIBUTED full_table_name */
   -2,  /* (281) cmd ::= SHOW CONSUMERS */
   -2,  /* (282) cmd ::= SHOW SUBSCRIPTIONS */
   -5,  /* (283) cmd ::= SHOW TAGS FROM table_name_cond from_db_opt */
   -6,  /* (284) cmd ::= SHOW TAGS FROM db_name NK_DOT table_name */
   -7,  /* (285) cmd ::= SHOW TABLE TAGS tag_list_opt FROM table_name_cond from_db_opt */
   -8,  /* (286) cmd ::= SHOW TABLE TAGS tag_list_opt FROM db_name NK_DOT table_name */
   -5,  /* (287) cmd ::= SHOW VNODES ON DNODE NK_INTEGER */
   -2,  /* (288) cmd ::= SHOW VNODES */
   -3,  /* (289) cmd ::= SHOW db_name_cond_opt ALIVE */
   -3,  /* (290) cmd ::= SHOW CLUSTER ALIVE */
   -4,  /* (291) cmd ::= SHOW db_name_cond_opt VIEWS like_pattern_opt */
   -4,  /* (292) cmd ::= SHOW CREATE VIEW full_table_name */
   -2,  /* (293) cmd ::= SHOW COMPACTS */
   -3,  /* (294) cmd ::= SHOW COMPACT NK_INTEGER */
    0,  /* (295) table_kind_db_name_cond_opt ::= */
   -1,  /* (296) table_kind_db_name_cond_opt ::= table_kind */
   -2,  /* (297) table_kind_db_name_cond_opt ::= db_name NK_DOT */
   -3,  /* (298) table_kind_db_name_cond_opt ::= table_kind db_name NK_DOT */
   -1,  /* (299) table_kind ::= NORMAL */
   -1,  /* (300) table_kind ::= CHILD */
    0,  /* (301) db_name_cond_opt ::= */
   -2,  /* (302) db_name_cond_opt ::= db_name NK_DOT */
    0,  /* (303) like_pattern_opt ::= */
   -2,  /* (304) like_pattern_opt ::= LIKE NK_STRING */
   -1,  /* (305) table_name_cond ::= table_name */
    0,  /* (306) from_db_opt ::= */
   -2,  /* (307) from_db_opt ::= FROM db_name */
    0,  /* (308) tag_list_opt ::= */
   -1,  /* (309) tag_list_opt ::= tag_item */
   -3,  /* (310) tag_list_opt ::= tag_list_opt NK_COMMA tag_item */
   -1,  /* (311) tag_item ::= TBNAME */
   -1,  /* (312) tag_item ::= QTAGS */
   -1,  /* (313) tag_item ::= column_name */
   -2,  /* (314) tag_item ::= column_name column_alias */
   -3,  /* (315) tag_item ::= column_name AS column_alias */
    0,  /* (316) db_kind_opt ::= */
   -1,  /* (317) db_kind_opt ::= USER */
   -1,  /* (318) db_kind_opt ::= SYSTEM */
   -8,  /* (319) cmd ::= CREATE SMA INDEX not_exists_opt col_name ON full_table_name index_options */
   -9,  /* (320) cmd ::= CREATE INDEX not_exists_opt col_name ON full_table_name NK_LP col_name_list NK_RP */
   -4,  /* (321) cmd ::= DROP INDEX exists_opt full_index_name */
   -1,  /* (322) full_index_name ::= index_name */
   -3,  /* (323) full_index_name ::= db_name NK_DOT index_name */
  -10,  /* (324) index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_RP sliding_opt sma_stream_opt */
  -12,  /* (325) index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_COMMA duration_literal NK_RP sliding_opt sma_stream_opt */
   -1,  /* (326) func_list ::= func */
   -3,  /* (327) func_list ::= func_list NK_COMMA func */
   -4,  /* (328) func ::= sma_func_name NK_LP expression_list NK_RP */
   -1,  /* (329) sma_func_name ::= function_name */
   -1,  /* (330) sma_func_name ::= COUNT */
   -1,  /* (331) sma_func_name ::= FIRST */
   -1,  /* (332) sma_func_name ::= LAST */
   -1,  /* (333) sma_func_name ::= LAST_ROW */
    0,  /* (334) sma_stream_opt ::= */
   -3,  /* (335) sma_stream_opt ::= sma_stream_opt WATERMARK duration_literal */
   -3,  /* (336) sma_stream_opt ::= sma_stream_opt MAX_DELAY duration_literal */
   -3,  /* (337) sma_stream_opt ::= sma_stream_opt DELETE_MARK duration_literal */
   -1,  /* (338) with_meta ::= AS */
   -3,  /* (339) with_meta ::= WITH META AS */
   -3,  /* (340) with_meta ::= ONLY META AS */
   -6,  /* (341) cmd ::= CREATE TOPIC not_exists_opt topic_name AS query_or_subquery */
   -7,  /* (342) cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta DATABASE db_name */
   -8,  /* (343) cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta STABLE full_table_name where_clause_opt */
   -4,  /* (344) cmd ::= DROP TOPIC exists_opt topic_name */
   -7,  /* (345) cmd ::= DROP CONSUMER GROUP exists_opt cgroup_name ON topic_name */
   -2,  /* (346) cmd ::= DESC full_table_name */
   -2,  /* (347) cmd ::= DESCRIBE full_table_name */
   -3,  /* (348) cmd ::= RESET QUERY CACHE */
   -4,  /* (349) cmd ::= EXPLAIN analyze_opt explain_options query_or_subquery */
   -4,  /* (350) cmd ::= EXPLAIN analyze_opt explain_options insert_query */
    0,  /* (351) analyze_opt ::= */
   -1,  /* (352) analyze_opt ::= ANALYZE */
    0,  /* (353) explain_options ::= */
   -3,  /* (354) explain_options ::= explain_options VERBOSE NK_BOOL */
   -3,  /* (355) explain_options ::= explain_options RATIO NK_FLOAT */
  -12,  /* (356) cmd ::= CREATE or_replace_opt agg_func_opt FUNCTION not_exists_opt function_name AS NK_STRING OUTPUTTYPE type_name bufsize_opt language_opt */
   -4,  /* (357) cmd ::= DROP FUNCTION exists_opt function_name */
    0,  /* (358) agg_func_opt ::= */
   -1,  /* (359) agg_func_opt ::= AGGREGATE */
    0,  /* (360) bufsize_opt ::= */
   -2,  /* (361) bufsize_opt ::= BUFSIZE NK_INTEGER */
    0,  /* (362) language_opt ::= */
   -2,  /* (363) language_opt ::= LANGUAGE NK_STRING */
    0,  /* (364) or_replace_opt ::= */
   -2,  /* (365) or_replace_opt ::= OR REPLACE */
   -6,  /* (366) cmd ::= CREATE or_replace_opt VIEW full_view_name AS query_or_subquery */
   -4,  /* (367) cmd ::= DROP VIEW exists_opt full_view_name */
   -1,  /* (368) full_view_name ::= view_name */
   -3,  /* (369) full_view_name ::= db_name NK_DOT view_name */
  -12,  /* (370) cmd ::= CREATE STREAM not_exists_opt stream_name stream_options INTO full_table_name col_list_opt tag_def_or_ref_opt subtable_opt AS query_or_subquery */
   -4,  /* (371) cmd ::= DROP STREAM exists_opt stream_name */
   -4,  /* (372) cmd ::= PAUSE STREAM exists_opt stream_name */
   -5,  /* (373) cmd ::= RESUME STREAM exists_opt ignore_opt stream_name */
    0,  /* (374) col_list_opt ::= */
   -3,  /* (375) col_list_opt ::= NK_LP col_name_list NK_RP */
    0,  /* (376) tag_def_or_ref_opt ::= */
   -1,  /* (377) tag_def_or_ref_opt ::= tags_def */
   -4,  /* (378) tag_def_or_ref_opt ::= TAGS NK_LP col_name_list NK_RP */
    0,  /* (379) stream_options ::= */
   -3,  /* (380) stream_options ::= stream_options TRIGGER AT_ONCE */
   -3,  /* (381) stream_options ::= stream_options TRIGGER WINDOW_CLOSE */
   -4,  /* (382) stream_options ::= stream_options TRIGGER MAX_DELAY duration_literal */
   -3,  /* (383) stream_options ::= stream_options WATERMARK duration_literal */
   -4,  /* (384) stream_options ::= stream_options IGNORE EXPIRED NK_INTEGER */
   -3,  /* (385) stream_options ::= stream_options FILL_HISTORY NK_INTEGER */
   -3,  /* (386) stream_options ::= stream_options DELETE_MARK duration_literal */
   -4,  /* (387) stream_options ::= stream_options IGNORE UPDATE NK_INTEGER */
    0,  /* (388) subtable_opt ::= */
   -4,  /* (389) subtable_opt ::= SUBTABLE NK_LP expression NK_RP */
    0,  /* (390) ignore_opt ::= */
   -2,  /* (391) ignore_opt ::= IGNORE UNTREATED */
   -3,  /* (392) cmd ::= KILL CONNECTION NK_INTEGER */
   -3,  /* (393) cmd ::= KILL QUERY NK_STRING */
   -3,  /* (394) cmd ::= KILL TRANSACTION NK_INTEGER */
   -3,  /* (395) cmd ::= KILL COMPACT NK_INTEGER */
   -2,  /* (396) cmd ::= BALANCE VGROUP */
   -4,  /* (397) cmd ::= BALANCE VGROUP LEADER on_vgroup_id */
   -4,  /* (398) cmd ::= MERGE VGROUP NK_INTEGER NK_INTEGER */
   -4,  /* (399) cmd ::= REDISTRIBUTE VGROUP NK_INTEGER dnode_list */
   -3,  /* (400) cmd ::= SPLIT VGROUP NK_INTEGER */
    0,  /* (401) on_vgroup_id ::= */
   -2,  /* (402) on_vgroup_id ::= ON NK_INTEGER */
   -2,  /* (403) dnode_list ::= DNODE NK_INTEGER */
   -3,  /* (404) dnode_list ::= dnode_list DNODE NK_INTEGER */
   -4,  /* (405) cmd ::= DELETE FROM full_table_name where_clause_opt */
   -1,  /* (406) cmd ::= query_or_subquery */
   -1,  /* (407) cmd ::= insert_query */
   -7,  /* (408) insert_query ::= INSERT INTO full_table_name NK_LP col_name_list NK_RP query_or_subquery */
   -4,  /* (409) insert_query ::= INSERT INTO full_table_name query_or_subquery */
   -1,  /* (410) literal ::= NK_INTEGER */
   -1,  /* (411) literal ::= NK_FLOAT */
   -1,  /* (412) literal ::= NK_STRING */
   -1,  /* (413) literal ::= NK_BOOL */
   -2,  /* (414) literal ::= TIMESTAMP NK_STRING */
   -1,  /* (415) literal ::= duration_literal */
   -1,  /* (416) literal ::= NULL */
   -1,  /* (417) literal ::= NK_QUESTION */
   -1,  /* (418) duration_literal ::= NK_VARIABLE */
   -1,  /* (419) signed ::= NK_INTEGER */
   -2,  /* (420) signed ::= NK_PLUS NK_INTEGER */
   -2,  /* (421) signed ::= NK_MINUS NK_INTEGER */
   -1,  /* (422) signed ::= NK_FLOAT */
   -2,  /* (423) signed ::= NK_PLUS NK_FLOAT */
   -2,  /* (424) signed ::= NK_MINUS NK_FLOAT */
   -1,  /* (425) signed_literal ::= signed */
   -1,  /* (426) signed_literal ::= NK_STRING */
   -1,  /* (427) signed_literal ::= NK_BOOL */
   -2,  /* (428) signed_literal ::= TIMESTAMP NK_STRING */
   -1,  /* (429) signed_literal ::= duration_literal */
   -1,  /* (430) signed_literal ::= NULL */
   -1,  /* (431) signed_literal ::= literal_func */
   -1,  /* (432) signed_literal ::= NK_QUESTION */
   -1,  /* (433) literal_list ::= signed_literal */
   -3,  /* (434) literal_list ::= literal_list NK_COMMA signed_literal */
   -1,  /* (435) db_name ::= NK_ID */
   -1,  /* (436) table_name ::= NK_ID */
   -1,  /* (437) column_name ::= NK_ID */
   -1,  /* (438) function_name ::= NK_ID */
   -1,  /* (439) view_name ::= NK_ID */
   -1,  /* (440) table_alias ::= NK_ID */
   -1,  /* (441) column_alias ::= NK_ID */
   -1,  /* (442) column_alias ::= NK_ALIAS */
   -1,  /* (443) user_name ::= NK_ID */
   -1,  /* (444) topic_name ::= NK_ID */
   -1,  /* (445) stream_name ::= NK_ID */
   -1,  /* (446) cgroup_name ::= NK_ID */
   -1,  /* (447) index_name ::= NK_ID */
   -1,  /* (448) expr_or_subquery ::= expression */
   -1,  /* (449) expression ::= literal */
   -1,  /* (450) expression ::= pseudo_column */
   -1,  /* (451) expression ::= column_reference */
   -1,  /* (452) expression ::= function_expression */
   -1,  /* (453) expression ::= case_when_expression */
   -3,  /* (454) expression ::= NK_LP expression NK_RP */
   -2,  /* (455) expression ::= NK_PLUS expr_or_subquery */
   -2,  /* (456) expression ::= NK_MINUS expr_or_subquery */
   -3,  /* (457) expression ::= expr_or_subquery NK_PLUS expr_or_subquery */
   -3,  /* (458) expression ::= expr_or_subquery NK_MINUS expr_or_subquery */
   -3,  /* (459) expression ::= expr_or_subquery NK_STAR expr_or_subquery */
   -3,  /* (460) expression ::= expr_or_subquery NK_SLASH expr_or_subquery */
   -3,  /* (461) expression ::= expr_or_subquery NK_REM expr_or_subquery */
   -3,  /* (462) expression ::= column_reference NK_ARROW NK_STRING */
   -3,  /* (463) expression ::= expr_or_subquery NK_BITAND expr_or_subquery */
   -3,  /* (464) expression ::= expr_or_subquery NK_BITOR expr_or_subquery */
   -1,  /* (465) expression_list ::= expr_or_subquery */
   -3,  /* (466) expression_list ::= expression_list NK_COMMA expr_or_subquery */
   -1,  /* (467) column_reference ::= column_name */
   -3,  /* (468) column_reference ::= table_name NK_DOT column_name */
   -1,  /* (469) column_reference ::= NK_ALIAS */
   -3,  /* (470) column_reference ::= table_name NK_DOT NK_ALIAS */
   -1,  /* (471) pseudo_column ::= ROWTS */
   -1,  /* (472) pseudo_column ::= TBNAME */
   -3,  /* (473) pseudo_column ::= table_name NK_DOT TBNAME */
   -1,  /* (474) pseudo_column ::= QSTART */
   -1,  /* (475) pseudo_column ::= QEND */
   -1,  /* (476) pseudo_column ::= QDURATION */
   -1,  /* (477) pseudo_column ::= WSTART */
   -1,  /* (478) pseudo_column ::= WEND */
   -1,  /* (479) pseudo_column ::= WDURATION */
   -1,  /* (480) pseudo_column ::= IROWTS */
   -1,  /* (481) pseudo_column ::= ISFILLED */
   -1,  /* (482) pseudo_column ::= QTAGS */
   -4,  /* (483) function_expression ::= function_name NK_LP expression_list NK_RP */
   -4,  /* (484) function_expression ::= star_func NK_LP star_func_para_list NK_RP */
   -6,  /* (485) function_expression ::= CAST NK_LP expr_or_subquery AS type_name NK_RP */
   -1,  /* (486) function_expression ::= literal_func */
   -3,  /* (487) literal_func ::= noarg_func NK_LP NK_RP */
   -1,  /* (488) literal_func ::= NOW */
   -1,  /* (489) noarg_func ::= NOW */
   -1,  /* (490) noarg_func ::= TODAY */
   -1,  /* (491) noarg_func ::= TIMEZONE */
   -1,  /* (492) noarg_func ::= DATABASE */
   -1,  /* (493) noarg_func ::= CLIENT_VERSION */
   -1,  /* (494) noarg_func ::= SERVER_VERSION */
   -1,  /* (495) noarg_func ::= SERVER_STATUS */
   -1,  /* (496) noarg_func ::= CURRENT_USER */
   -1,  /* (497) noarg_func ::= USER */
   -1,  /* (498) star_func ::= COUNT */
   -1,  /* (499) star_func ::= FIRST */
   -1,  /* (500) star_func ::= LAST */
   -1,  /* (501) star_func ::= LAST_ROW */
   -1,  /* (502) star_func_para_list ::= NK_STAR */
   -1,  /* (503) star_func_para_list ::= other_para_list */
   -1,  /* (504) other_para_list ::= star_func_para */
   -3,  /* (505) other_para_list ::= other_para_list NK_COMMA star_func_para */
   -1,  /* (506) star_func_para ::= expr_or_subquery */
   -3,  /* (507) star_func_para ::= table_name NK_DOT NK_STAR */
   -4,  /* (508) case_when_expression ::= CASE when_then_list case_when_else_opt END */
   -5,  /* (509) case_when_expression ::= CASE common_expression when_then_list case_when_else_opt END */
   -1,  /* (510) when_then_list ::= when_then_expr */
   -2,  /* (511) when_then_list ::= when_then_list when_then_expr */
   -4,  /* (512) when_then_expr ::= WHEN common_expression THEN common_expression */
    0,  /* (513) case_when_else_opt ::= */
   -2,  /* (514) case_when_else_opt ::= ELSE common_expression */
   -3,  /* (515) predicate ::= expr_or_subquery compare_op expr_or_subquery */
   -5,  /* (516) predicate ::= expr_or_subquery BETWEEN expr_or_subquery AND expr_or_subquery */
   -6,  /* (517) predicate ::= expr_or_subquery NOT BETWEEN expr_or_subquery AND expr_or_subquery */
   -3,  /* (518) predicate ::= expr_or_subquery IS NULL */
   -4,  /* (519) predicate ::= expr_or_subquery IS NOT NULL */
   -3,  /* (520) predicate ::= expr_or_subquery in_op in_predicate_value */
   -1,  /* (521) compare_op ::= NK_LT */
   -1,  /* (522) compare_op ::= NK_GT */
   -1,  /* (523) compare_op ::= NK_LE */
   -1,  /* (524) compare_op ::= NK_GE */
   -1,  /* (525) compare_op ::= NK_NE */
   -1,  /* (526) compare_op ::= NK_EQ */
   -1,  /* (527) compare_op ::= LIKE */
   -2,  /* (528) compare_op ::= NOT LIKE */
   -1,  /* (529) compare_op ::= MATCH */
   -1,  /* (530) compare_op ::= NMATCH */
   -1,  /* (531) compare_op ::= CONTAINS */
   -1,  /* (532) in_op ::= IN */
   -2,  /* (533) in_op ::= NOT IN */
   -3,  /* (534) in_predicate_value ::= NK_LP literal_list NK_RP */
   -1,  /* (535) boolean_value_expression ::= boolean_primary */
   -2,  /* (536) boolean_value_expression ::= NOT boolean_primary */
   -3,  /* (537) boolean_value_expression ::= boolean_value_expression OR boolean_value_expression */
   -3,  /* (538) boolean_value_expression ::= boolean_value_expression AND boolean_value_expression */
   -1,  /* (539) boolean_primary ::= predicate */
   -3,  /* (540) boolean_primary ::= NK_LP boolean_value_expression NK_RP */
   -1,  /* (541) common_expression ::= expr_or_subquery */
   -1,  /* (542) common_expression ::= boolean_value_expression */
    0,  /* (543) from_clause_opt ::= */
   -2,  /* (544) from_clause_opt ::= FROM table_reference_list */
   -1,  /* (545) table_reference_list ::= table_reference */
   -3,  /* (546) table_reference_list ::= table_reference_list NK_COMMA table_reference */
   -1,  /* (547) table_reference ::= table_primary */
   -1,  /* (548) table_reference ::= joined_table */
   -2,  /* (549) table_primary ::= table_name alias_opt */
   -4,  /* (550) table_primary ::= db_name NK_DOT table_name alias_opt */
   -2,  /* (551) table_primary ::= subquery alias_opt */
   -1,  /* (552) table_primary ::= parenthesized_joined_table */
    0,  /* (553) alias_opt ::= */
   -1,  /* (554) alias_opt ::= table_alias */
   -2,  /* (555) alias_opt ::= AS table_alias */
   -3,  /* (556) parenthesized_joined_table ::= NK_LP joined_table NK_RP */
   -3,  /* (557) parenthesized_joined_table ::= NK_LP parenthesized_joined_table NK_RP */
   -6,  /* (558) joined_table ::= table_reference join_type JOIN table_reference ON search_condition */
    0,  /* (559) join_type ::= */
   -1,  /* (560) join_type ::= INNER */
  -14,  /* (561) query_specification ::= SELECT hint_list set_quantifier_opt tag_mode_opt select_list from_clause_opt where_clause_opt partition_by_clause_opt range_opt every_opt fill_opt twindow_clause_opt group_by_clause_opt having_clause_opt */
    0,  /* (562) hint_list ::= */
   -1,  /* (563) hint_list ::= NK_HINT */
    0,  /* (564) tag_mode_opt ::= */
   -1,  /* (565) tag_mode_opt ::= TAGS */
    0,  /* (566) set_quantifier_opt ::= */
   -1,  /* (567) set_quantifier_opt ::= DISTINCT */
   -1,  /* (568) set_quantifier_opt ::= ALL */
   -1,  /* (569) select_list ::= select_item */
   -3,  /* (570) select_list ::= select_list NK_COMMA select_item */
   -1,  /* (571) select_item ::= NK_STAR */
   -1,  /* (572) select_item ::= common_expression */
   -2,  /* (573) select_item ::= common_expression column_alias */
   -3,  /* (574) select_item ::= common_expression AS column_alias */
   -3,  /* (575) select_item ::= table_name NK_DOT NK_STAR */
    0,  /* (576) where_clause_opt ::= */
   -2,  /* (577) where_clause_opt ::= WHERE search_condition */
    0,  /* (578) partition_by_clause_opt ::= */
   -3,  /* (579) partition_by_clause_opt ::= PARTITION BY partition_list */
   -1,  /* (580) partition_list ::= partition_item */
   -3,  /* (581) partition_list ::= partition_list NK_COMMA partition_item */
   -1,  /* (582) partition_item ::= expr_or_subquery */
   -2,  /* (583) partition_item ::= expr_or_subquery column_alias */
   -3,  /* (584) partition_item ::= expr_or_subquery AS column_alias */
    0,  /* (585) twindow_clause_opt ::= */
   -6,  /* (586) twindow_clause_opt ::= SESSION NK_LP column_reference NK_COMMA interval_sliding_duration_literal NK_RP */
   -4,  /* (587) twindow_clause_opt ::= STATE_WINDOW NK_LP expr_or_subquery NK_RP */
   -6,  /* (588) twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
   -8,  /* (589) twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_COMMA interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
   -7,  /* (590) twindow_clause_opt ::= EVENT_WINDOW START WITH search_condition END WITH search_condition */
   -4,  /* (591) twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_RP */
   -6,  /* (592) twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
    0,  /* (593) sliding_opt ::= */
   -4,  /* (594) sliding_opt ::= SLIDING NK_LP interval_sliding_duration_literal NK_RP */
   -1,  /* (595) interval_sliding_duration_literal ::= NK_VARIABLE */
   -1,  /* (596) interval_sliding_duration_literal ::= NK_STRING */
   -1,  /* (597) interval_sliding_duration_literal ::= NK_INTEGER */
    0,  /* (598) fill_opt ::= */
   -4,  /* (599) fill_opt ::= FILL NK_LP fill_mode NK_RP */
   -6,  /* (600) fill_opt ::= FILL NK_LP VALUE NK_COMMA expression_list NK_RP */
   -6,  /* (601) fill_opt ::= FILL NK_LP VALUE_F NK_COMMA expression_list NK_RP */
   -1,  /* (602) fill_mode ::= NONE */
   -1,  /* (603) fill_mode ::= PREV */
   -1,  /* (604) fill_mode ::= NULL */
   -1,  /* (605) fill_mode ::= NULL_F */
   -1,  /* (606) fill_mode ::= LINEAR */
   -1,  /* (607) fill_mode ::= NEXT */
    0,  /* (608) group_by_clause_opt ::= */
   -3,  /* (609) group_by_clause_opt ::= GROUP BY group_by_list */
   -1,  /* (610) group_by_list ::= expr_or_subquery */
   -3,  /* (611) group_by_list ::= group_by_list NK_COMMA expr_or_subquery */
    0,  /* (612) having_clause_opt ::= */
   -2,  /* (613) having_clause_opt ::= HAVING search_condition */
    0,  /* (614) range_opt ::= */
   -6,  /* (615) range_opt ::= RANGE NK_LP expr_or_subquery NK_COMMA expr_or_subquery NK_RP */
   -4,  /* (616) range_opt ::= RANGE NK_LP expr_or_subquery NK_RP */
    0,  /* (617) every_opt ::= */
   -4,  /* (618) every_opt ::= EVERY NK_LP duration_literal NK_RP */
   -4,  /* (619) query_expression ::= query_simple order_by_clause_opt slimit_clause_opt limit_clause_opt */
   -1,  /* (620) query_simple ::= query_specification */
   -1,  /* (621) query_simple ::= union_query_expression */
   -4,  /* (622) union_query_expression ::= query_simple_or_subquery UNION ALL query_simple_or_subquery */
   -3,  /* (623) union_query_expression ::= query_simple_or_subquery UNION query_simple_or_subquery */
   -1,  /* (624) query_simple_or_subquery ::= query_simple */
   -1,  /* (625) query_simple_or_subquery ::= subquery */
   -1,  /* (626) query_or_subquery ::= query_expression */
   -1,  /* (627) query_or_subquery ::= subquery */
    0,  /* (628) order_by_clause_opt ::= */
   -3,  /* (629) order_by_clause_opt ::= ORDER BY sort_specification_list */
    0,  /* (630) slimit_clause_opt ::= */
   -2,  /* (631) slimit_clause_opt ::= SLIMIT NK_INTEGER */
   -4,  /* (632) slimit_clause_opt ::= SLIMIT NK_INTEGER SOFFSET NK_INTEGER */
   -4,  /* (633) slimit_clause_opt ::= SLIMIT NK_INTEGER NK_COMMA NK_INTEGER */
    0,  /* (634) limit_clause_opt ::= */
   -2,  /* (635) limit_clause_opt ::= LIMIT NK_INTEGER */
   -4,  /* (636) limit_clause_opt ::= LIMIT NK_INTEGER OFFSET NK_INTEGER */
   -4,  /* (637) limit_clause_opt ::= LIMIT NK_INTEGER NK_COMMA NK_INTEGER */
   -3,  /* (638) subquery ::= NK_LP query_expression NK_RP */
   -3,  /* (639) subquery ::= NK_LP subquery NK_RP */
   -1,  /* (640) search_condition ::= common_expression */
   -1,  /* (641) sort_specification_list ::= sort_specification */
   -3,  /* (642) sort_specification_list ::= sort_specification_list NK_COMMA sort_specification */
   -3,  /* (643) sort_specification ::= expr_or_subquery ordering_specification_opt null_ordering_opt */
    0,  /* (644) ordering_specification_opt ::= */
   -1,  /* (645) ordering_specification_opt ::= ASC */
   -1,  /* (646) ordering_specification_opt ::= DESC */
    0,  /* (647) null_ordering_opt ::= */
   -2,  /* (648) null_ordering_opt ::= NULLS FIRST */
   -2,  /* (649) null_ordering_opt ::= NULLS LAST */
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
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s, pop back to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action",
        yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s.\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action");
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
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
      case 0: /* cmd ::= CREATE ACCOUNT NK_ID PASS NK_STRING account_options */
{ pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_EXPRIE_STATEMENT); }
#line 5117 "sql.c"
  yy_destructor(yypParser,353,&yymsp[0].minor);
        break;
      case 1: /* cmd ::= ALTER ACCOUNT NK_ID alter_account_options */
{ pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_EXPRIE_STATEMENT); }
#line 5123 "sql.c"
  yy_destructor(yypParser,354,&yymsp[0].minor);
        break;
      case 2: /* account_options ::= */
{ }
#line 5129 "sql.c"
        break;
      case 3: /* account_options ::= account_options PPS literal */
      case 4: /* account_options ::= account_options TSERIES literal */ yytestcase(yyruleno==4);
      case 5: /* account_options ::= account_options STORAGE literal */ yytestcase(yyruleno==5);
      case 6: /* account_options ::= account_options STREAMS literal */ yytestcase(yyruleno==6);
      case 7: /* account_options ::= account_options QTIME literal */ yytestcase(yyruleno==7);
      case 8: /* account_options ::= account_options DBS literal */ yytestcase(yyruleno==8);
      case 9: /* account_options ::= account_options USERS literal */ yytestcase(yyruleno==9);
      case 10: /* account_options ::= account_options CONNS literal */ yytestcase(yyruleno==10);
      case 11: /* account_options ::= account_options STATE literal */ yytestcase(yyruleno==11);
{  yy_destructor(yypParser,353,&yymsp[-2].minor);
#line 56 "sql.y"
{ }
#line 5143 "sql.c"
  yy_destructor(yypParser,355,&yymsp[0].minor);
}
        break;
      case 12: /* alter_account_options ::= alter_account_option */
{  yy_destructor(yypParser,356,&yymsp[0].minor);
#line 68 "sql.y"
{ }
#line 5151 "sql.c"
}
        break;
      case 13: /* alter_account_options ::= alter_account_options alter_account_option */
{  yy_destructor(yypParser,354,&yymsp[-1].minor);
#line 69 "sql.y"
{ }
#line 5158 "sql.c"
  yy_destructor(yypParser,356,&yymsp[0].minor);
}
        break;
      case 14: /* alter_account_option ::= PASS literal */
      case 15: /* alter_account_option ::= PPS literal */ yytestcase(yyruleno==15);
      case 16: /* alter_account_option ::= TSERIES literal */ yytestcase(yyruleno==16);
      case 17: /* alter_account_option ::= STORAGE literal */ yytestcase(yyruleno==17);
      case 18: /* alter_account_option ::= STREAMS literal */ yytestcase(yyruleno==18);
      case 19: /* alter_account_option ::= QTIME literal */ yytestcase(yyruleno==19);
      case 20: /* alter_account_option ::= DBS literal */ yytestcase(yyruleno==20);
      case 21: /* alter_account_option ::= USERS literal */ yytestcase(yyruleno==21);
      case 22: /* alter_account_option ::= CONNS literal */ yytestcase(yyruleno==22);
      case 23: /* alter_account_option ::= STATE literal */ yytestcase(yyruleno==23);
{ }
#line 5174 "sql.c"
  yy_destructor(yypParser,355,&yymsp[0].minor);
        break;
      case 24: /* ip_range_list ::= NK_STRING */
#line 86 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0)); }
#line 5180 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 25: /* ip_range_list ::= ip_range_list NK_COMMA NK_STRING */
#line 87 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0)); }
#line 5186 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 26: /* white_list ::= HOST ip_range_list */
#line 91 "sql.y"
{ yymsp[-1].minor.yy388 = yymsp[0].minor.yy388; }
#line 5192 "sql.c"
        break;
      case 27: /* white_list_opt ::= */
      case 188: /* specific_cols_opt ::= */ yytestcase(yyruleno==188);
      case 220: /* tags_def_opt ::= */ yytestcase(yyruleno==220);
      case 308: /* tag_list_opt ::= */ yytestcase(yyruleno==308);
      case 374: /* col_list_opt ::= */ yytestcase(yyruleno==374);
      case 376: /* tag_def_or_ref_opt ::= */ yytestcase(yyruleno==376);
      case 578: /* partition_by_clause_opt ::= */ yytestcase(yyruleno==578);
      case 608: /* group_by_clause_opt ::= */ yytestcase(yyruleno==608);
      case 628: /* order_by_clause_opt ::= */ yytestcase(yyruleno==628);
#line 95 "sql.y"
{ yymsp[1].minor.yy388 = NULL; }
#line 5205 "sql.c"
        break;
      case 28: /* white_list_opt ::= white_list */
      case 221: /* tags_def_opt ::= tags_def */ yytestcase(yyruleno==221);
      case 377: /* tag_def_or_ref_opt ::= tags_def */ yytestcase(yyruleno==377);
      case 503: /* star_func_para_list ::= other_para_list */ yytestcase(yyruleno==503);
#line 96 "sql.y"
{ yylhsminor.yy388 = yymsp[0].minor.yy388; }
#line 5213 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 29: /* cmd ::= CREATE USER user_name PASS NK_STRING sysinfo_opt white_list_opt */
{
                                                                                    pCxt->pRootNode = createCreateUserStmt(pCxt, &yymsp[-4].minor.yy965, &yymsp[-2].minor.yy0, yymsp[-1].minor.yy125);
                                                                                    pCxt->pRootNode = addCreateUserStmtWhiteList(pCxt, pCxt->pRootNode, yymsp[0].minor.yy388);
                                                                                  }
#line 5222 "sql.c"
        break;
      case 30: /* cmd ::= ALTER USER user_name PASS NK_STRING */
#line 104 "sql.y"
{ pCxt->pRootNode = createAlterUserStmt(pCxt, &yymsp[-2].minor.yy965, TSDB_ALTER_USER_PASSWD, &yymsp[0].minor.yy0); }
#line 5227 "sql.c"
        break;
      case 31: /* cmd ::= ALTER USER user_name ENABLE NK_INTEGER */
#line 105 "sql.y"
{ pCxt->pRootNode = createAlterUserStmt(pCxt, &yymsp[-2].minor.yy965, TSDB_ALTER_USER_ENABLE, &yymsp[0].minor.yy0); }
#line 5232 "sql.c"
        break;
      case 32: /* cmd ::= ALTER USER user_name SYSINFO NK_INTEGER */
#line 106 "sql.y"
{ pCxt->pRootNode = createAlterUserStmt(pCxt, &yymsp[-2].minor.yy965, TSDB_ALTER_USER_SYSINFO, &yymsp[0].minor.yy0); }
#line 5237 "sql.c"
        break;
      case 33: /* cmd ::= ALTER USER user_name ADD white_list */
#line 107 "sql.y"
{ pCxt->pRootNode = createAlterUserStmt(pCxt, &yymsp[-2].minor.yy965, TSDB_ALTER_USER_ADD_WHITE_LIST, yymsp[0].minor.yy388); }
#line 5242 "sql.c"
        break;
      case 34: /* cmd ::= ALTER USER user_name DROP white_list */
#line 108 "sql.y"
{ pCxt->pRootNode = createAlterUserStmt(pCxt, &yymsp[-2].minor.yy965, TSDB_ALTER_USER_DROP_WHITE_LIST, yymsp[0].minor.yy388); }
#line 5247 "sql.c"
        break;
      case 35: /* cmd ::= DROP USER user_name */
#line 109 "sql.y"
{ pCxt->pRootNode = createDropUserStmt(pCxt, &yymsp[0].minor.yy965); }
#line 5252 "sql.c"
        break;
      case 36: /* sysinfo_opt ::= */
#line 113 "sql.y"
{ yymsp[1].minor.yy125 = 1; }
#line 5257 "sql.c"
        break;
      case 37: /* sysinfo_opt ::= SYSINFO NK_INTEGER */
#line 114 "sql.y"
{ yymsp[-1].minor.yy125 = taosStr2Int8(yymsp[0].minor.yy0.z, NULL, 10); }
#line 5262 "sql.c"
        break;
      case 38: /* cmd ::= GRANT privileges ON priv_level with_opt TO user_name */
#line 117 "sql.y"
{ pCxt->pRootNode = createGrantStmt(pCxt, yymsp[-5].minor.yy207, &yymsp[-3].minor.yy453, &yymsp[0].minor.yy965, yymsp[-2].minor.yy560); }
#line 5267 "sql.c"
        break;
      case 39: /* cmd ::= REVOKE privileges ON priv_level with_opt FROM user_name */
#line 118 "sql.y"
{ pCxt->pRootNode = createRevokeStmt(pCxt, yymsp[-5].minor.yy207, &yymsp[-3].minor.yy453, &yymsp[0].minor.yy965, yymsp[-2].minor.yy560); }
#line 5272 "sql.c"
        break;
      case 40: /* privileges ::= ALL */
#line 122 "sql.y"
{ yymsp[0].minor.yy207 = PRIVILEGE_TYPE_ALL; }
#line 5277 "sql.c"
        break;
      case 41: /* privileges ::= priv_type_list */
      case 43: /* priv_type_list ::= priv_type */ yytestcase(yyruleno==43);
#line 123 "sql.y"
{ yylhsminor.yy207 = yymsp[0].minor.yy207; }
#line 5283 "sql.c"
  yymsp[0].minor.yy207 = yylhsminor.yy207;
        break;
      case 42: /* privileges ::= SUBSCRIBE */
#line 124 "sql.y"
{ yymsp[0].minor.yy207 = PRIVILEGE_TYPE_SUBSCRIBE; }
#line 5289 "sql.c"
        break;
      case 44: /* priv_type_list ::= priv_type_list NK_COMMA priv_type */
#line 129 "sql.y"
{ yylhsminor.yy207 = yymsp[-2].minor.yy207 | yymsp[0].minor.yy207; }
#line 5294 "sql.c"
  yymsp[-2].minor.yy207 = yylhsminor.yy207;
        break;
      case 45: /* priv_type ::= READ */
#line 133 "sql.y"
{ yymsp[0].minor.yy207 = PRIVILEGE_TYPE_READ; }
#line 5300 "sql.c"
        break;
      case 46: /* priv_type ::= WRITE */
#line 134 "sql.y"
{ yymsp[0].minor.yy207 = PRIVILEGE_TYPE_WRITE; }
#line 5305 "sql.c"
        break;
      case 47: /* priv_type ::= ALTER */
#line 135 "sql.y"
{ yymsp[0].minor.yy207 = PRIVILEGE_TYPE_ALTER; }
#line 5310 "sql.c"
        break;
      case 48: /* priv_level ::= NK_STAR NK_DOT NK_STAR */
#line 139 "sql.y"
{ yylhsminor.yy453.first = yymsp[-2].minor.yy0; yylhsminor.yy453.second = yymsp[0].minor.yy0; }
#line 5315 "sql.c"
  yymsp[-2].minor.yy453 = yylhsminor.yy453;
        break;
      case 49: /* priv_level ::= db_name NK_DOT NK_STAR */
#line 140 "sql.y"
{ yylhsminor.yy453.first = yymsp[-2].minor.yy965; yylhsminor.yy453.second = yymsp[0].minor.yy0; }
#line 5321 "sql.c"
  yymsp[-2].minor.yy453 = yylhsminor.yy453;
        break;
      case 50: /* priv_level ::= db_name NK_DOT table_name */
#line 141 "sql.y"
{ yylhsminor.yy453.first = yymsp[-2].minor.yy965; yylhsminor.yy453.second = yymsp[0].minor.yy965; }
#line 5327 "sql.c"
  yymsp[-2].minor.yy453 = yylhsminor.yy453;
        break;
      case 51: /* priv_level ::= topic_name */
#line 142 "sql.y"
{ yylhsminor.yy453.first = yymsp[0].minor.yy965; yylhsminor.yy453.second = nil_token; }
#line 5333 "sql.c"
  yymsp[0].minor.yy453 = yylhsminor.yy453;
        break;
      case 52: /* with_opt ::= */
      case 157: /* start_opt ::= */ yytestcase(yyruleno==157);
      case 161: /* end_opt ::= */ yytestcase(yyruleno==161);
      case 303: /* like_pattern_opt ::= */ yytestcase(yyruleno==303);
      case 388: /* subtable_opt ::= */ yytestcase(yyruleno==388);
      case 513: /* case_when_else_opt ::= */ yytestcase(yyruleno==513);
      case 543: /* from_clause_opt ::= */ yytestcase(yyruleno==543);
      case 576: /* where_clause_opt ::= */ yytestcase(yyruleno==576);
      case 585: /* twindow_clause_opt ::= */ yytestcase(yyruleno==585);
      case 593: /* sliding_opt ::= */ yytestcase(yyruleno==593);
      case 598: /* fill_opt ::= */ yytestcase(yyruleno==598);
      case 612: /* having_clause_opt ::= */ yytestcase(yyruleno==612);
      case 614: /* range_opt ::= */ yytestcase(yyruleno==614);
      case 617: /* every_opt ::= */ yytestcase(yyruleno==617);
      case 630: /* slimit_clause_opt ::= */ yytestcase(yyruleno==630);
      case 634: /* limit_clause_opt ::= */ yytestcase(yyruleno==634);
#line 144 "sql.y"
{ yymsp[1].minor.yy560 = NULL; }
#line 5354 "sql.c"
        break;
      case 53: /* with_opt ::= WITH search_condition */
      case 544: /* from_clause_opt ::= FROM table_reference_list */ yytestcase(yyruleno==544);
      case 577: /* where_clause_opt ::= WHERE search_condition */ yytestcase(yyruleno==577);
      case 613: /* having_clause_opt ::= HAVING search_condition */ yytestcase(yyruleno==613);
#line 145 "sql.y"
{ yymsp[-1].minor.yy560 = yymsp[0].minor.yy560; }
#line 5362 "sql.c"
        break;
      case 54: /* cmd ::= CREATE DNODE dnode_endpoint */
#line 148 "sql.y"
{ pCxt->pRootNode = createCreateDnodeStmt(pCxt, &yymsp[0].minor.yy965, NULL); }
#line 5367 "sql.c"
        break;
      case 55: /* cmd ::= CREATE DNODE dnode_endpoint PORT NK_INTEGER */
#line 149 "sql.y"
{ pCxt->pRootNode = createCreateDnodeStmt(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0); }
#line 5372 "sql.c"
        break;
      case 56: /* cmd ::= DROP DNODE NK_INTEGER force_opt */
#line 150 "sql.y"
{ pCxt->pRootNode = createDropDnodeStmt(pCxt, &yymsp[-1].minor.yy0, yymsp[0].minor.yy983, false); }
#line 5377 "sql.c"
        break;
      case 57: /* cmd ::= DROP DNODE dnode_endpoint force_opt */
#line 151 "sql.y"
{ pCxt->pRootNode = createDropDnodeStmt(pCxt, &yymsp[-1].minor.yy965, yymsp[0].minor.yy983, false); }
#line 5382 "sql.c"
        break;
      case 58: /* cmd ::= DROP DNODE NK_INTEGER unsafe_opt */
#line 152 "sql.y"
{ pCxt->pRootNode = createDropDnodeStmt(pCxt, &yymsp[-1].minor.yy0, false, yymsp[0].minor.yy983); }
#line 5387 "sql.c"
        break;
      case 59: /* cmd ::= DROP DNODE dnode_endpoint unsafe_opt */
#line 153 "sql.y"
{ pCxt->pRootNode = createDropDnodeStmt(pCxt, &yymsp[-1].minor.yy965, false, yymsp[0].minor.yy983); }
#line 5392 "sql.c"
        break;
      case 60: /* cmd ::= ALTER DNODE NK_INTEGER NK_STRING */
{ pCxt->pRootNode = createAlterDnodeStmt(pCxt, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0, NULL); }
#line 5397 "sql.c"
        break;
      case 61: /* cmd ::= ALTER DNODE NK_INTEGER NK_STRING NK_STRING */
{ pCxt->pRootNode = createAlterDnodeStmt(pCxt, &yymsp[-2].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0); }
#line 5402 "sql.c"
        break;
      case 62: /* cmd ::= ALTER ALL DNODES NK_STRING */
{ pCxt->pRootNode = createAlterDnodeStmt(pCxt, NULL, &yymsp[0].minor.yy0, NULL); }
#line 5407 "sql.c"
        break;
      case 63: /* cmd ::= ALTER ALL DNODES NK_STRING NK_STRING */
{ pCxt->pRootNode = createAlterDnodeStmt(pCxt, NULL, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0); }
#line 5412 "sql.c"
        break;
      case 64: /* cmd ::= RESTORE DNODE NK_INTEGER */
{ pCxt->pRootNode = createRestoreComponentNodeStmt(pCxt, QUERY_NODE_RESTORE_DNODE_STMT, &yymsp[0].minor.yy0); }
#line 5417 "sql.c"
        break;
      case 65: /* dnode_endpoint ::= NK_STRING */
      case 66: /* dnode_endpoint ::= NK_ID */ yytestcase(yyruleno==66);
      case 67: /* dnode_endpoint ::= NK_IPTOKEN */ yytestcase(yyruleno==67);
      case 330: /* sma_func_name ::= COUNT */ yytestcase(yyruleno==330);
      case 331: /* sma_func_name ::= FIRST */ yytestcase(yyruleno==331);
      case 332: /* sma_func_name ::= LAST */ yytestcase(yyruleno==332);
      case 333: /* sma_func_name ::= LAST_ROW */ yytestcase(yyruleno==333);
      case 435: /* db_name ::= NK_ID */ yytestcase(yyruleno==435);
      case 436: /* table_name ::= NK_ID */ yytestcase(yyruleno==436);
      case 437: /* column_name ::= NK_ID */ yytestcase(yyruleno==437);
      case 438: /* function_name ::= NK_ID */ yytestcase(yyruleno==438);
      case 439: /* view_name ::= NK_ID */ yytestcase(yyruleno==439);
      case 440: /* table_alias ::= NK_ID */ yytestcase(yyruleno==440);
      case 441: /* column_alias ::= NK_ID */ yytestcase(yyruleno==441);
      case 442: /* column_alias ::= NK_ALIAS */ yytestcase(yyruleno==442);
      case 443: /* user_name ::= NK_ID */ yytestcase(yyruleno==443);
      case 444: /* topic_name ::= NK_ID */ yytestcase(yyruleno==444);
      case 445: /* stream_name ::= NK_ID */ yytestcase(yyruleno==445);
      case 446: /* cgroup_name ::= NK_ID */ yytestcase(yyruleno==446);
      case 447: /* index_name ::= NK_ID */ yytestcase(yyruleno==447);
      case 489: /* noarg_func ::= NOW */ yytestcase(yyruleno==489);
      case 490: /* noarg_func ::= TODAY */ yytestcase(yyruleno==490);
      case 491: /* noarg_func ::= TIMEZONE */ yytestcase(yyruleno==491);
      case 492: /* noarg_func ::= DATABASE */ yytestcase(yyruleno==492);
      case 493: /* noarg_func ::= CLIENT_VERSION */ yytestcase(yyruleno==493);
      case 494: /* noarg_func ::= SERVER_VERSION */ yytestcase(yyruleno==494);
      case 495: /* noarg_func ::= SERVER_STATUS */ yytestcase(yyruleno==495);
      case 496: /* noarg_func ::= CURRENT_USER */ yytestcase(yyruleno==496);
      case 497: /* noarg_func ::= USER */ yytestcase(yyruleno==497);
      case 498: /* star_func ::= COUNT */ yytestcase(yyruleno==498);
      case 499: /* star_func ::= FIRST */ yytestcase(yyruleno==499);
      case 500: /* star_func ::= LAST */ yytestcase(yyruleno==500);
      case 501: /* star_func ::= LAST_ROW */ yytestcase(yyruleno==501);
#line 162 "sql.y"
{ yylhsminor.yy965 = yymsp[0].minor.yy0; }
#line 5454 "sql.c"
  yymsp[0].minor.yy965 = yylhsminor.yy965;
        break;
      case 68: /* force_opt ::= */
      case 94: /* not_exists_opt ::= */ yytestcase(yyruleno==94);
      case 96: /* exists_opt ::= */ yytestcase(yyruleno==96);
      case 351: /* analyze_opt ::= */ yytestcase(yyruleno==351);
      case 358: /* agg_func_opt ::= */ yytestcase(yyruleno==358);
      case 364: /* or_replace_opt ::= */ yytestcase(yyruleno==364);
      case 390: /* ignore_opt ::= */ yytestcase(yyruleno==390);
      case 564: /* tag_mode_opt ::= */ yytestcase(yyruleno==564);
      case 566: /* set_quantifier_opt ::= */ yytestcase(yyruleno==566);
#line 168 "sql.y"
{ yymsp[1].minor.yy983 = false; }
#line 5468 "sql.c"
        break;
      case 69: /* force_opt ::= FORCE */
      case 70: /* unsafe_opt ::= UNSAFE */ yytestcase(yyruleno==70);
      case 352: /* analyze_opt ::= ANALYZE */ yytestcase(yyruleno==352);
      case 359: /* agg_func_opt ::= AGGREGATE */ yytestcase(yyruleno==359);
      case 565: /* tag_mode_opt ::= TAGS */ yytestcase(yyruleno==565);
      case 567: /* set_quantifier_opt ::= DISTINCT */ yytestcase(yyruleno==567);
#line 169 "sql.y"
{ yymsp[0].minor.yy983 = true; }
#line 5478 "sql.c"
        break;
      case 71: /* cmd ::= ALTER CLUSTER NK_STRING */
{ pCxt->pRootNode = createAlterClusterStmt(pCxt, &yymsp[0].minor.yy0, NULL); }
#line 5483 "sql.c"
        break;
      case 72: /* cmd ::= ALTER CLUSTER NK_STRING NK_STRING */
{ pCxt->pRootNode = createAlterClusterStmt(pCxt, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0); }
#line 5488 "sql.c"
        break;
      case 73: /* cmd ::= ALTER LOCAL NK_STRING */
{ pCxt->pRootNode = createAlterLocalStmt(pCxt, &yymsp[0].minor.yy0, NULL); }
#line 5493 "sql.c"
        break;
      case 74: /* cmd ::= ALTER LOCAL NK_STRING NK_STRING */
{ pCxt->pRootNode = createAlterLocalStmt(pCxt, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0); }
#line 5498 "sql.c"
        break;
      case 75: /* cmd ::= CREATE QNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createCreateComponentNodeStmt(pCxt, QUERY_NODE_CREATE_QNODE_STMT, &yymsp[0].minor.yy0); }
#line 5503 "sql.c"
        break;
      case 76: /* cmd ::= DROP QNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createDropComponentNodeStmt(pCxt, QUERY_NODE_DROP_QNODE_STMT, &yymsp[0].minor.yy0); }
#line 5508 "sql.c"
        break;
      case 77: /* cmd ::= RESTORE QNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createRestoreComponentNodeStmt(pCxt, QUERY_NODE_RESTORE_QNODE_STMT, &yymsp[0].minor.yy0); }
#line 5513 "sql.c"
        break;
      case 78: /* cmd ::= CREATE BNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createCreateComponentNodeStmt(pCxt, QUERY_NODE_CREATE_BNODE_STMT, &yymsp[0].minor.yy0); }
#line 5518 "sql.c"
        break;
      case 79: /* cmd ::= DROP BNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createDropComponentNodeStmt(pCxt, QUERY_NODE_DROP_BNODE_STMT, &yymsp[0].minor.yy0); }
#line 5523 "sql.c"
        break;
      case 80: /* cmd ::= CREATE SNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createCreateComponentNodeStmt(pCxt, QUERY_NODE_CREATE_SNODE_STMT, &yymsp[0].minor.yy0); }
#line 5528 "sql.c"
        break;
      case 81: /* cmd ::= DROP SNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createDropComponentNodeStmt(pCxt, QUERY_NODE_DROP_SNODE_STMT, &yymsp[0].minor.yy0); }
#line 5533 "sql.c"
        break;
      case 82: /* cmd ::= CREATE MNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createCreateComponentNodeStmt(pCxt, QUERY_NODE_CREATE_MNODE_STMT, &yymsp[0].minor.yy0); }
#line 5538 "sql.c"
        break;
      case 83: /* cmd ::= DROP MNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createDropComponentNodeStmt(pCxt, QUERY_NODE_DROP_MNODE_STMT, &yymsp[0].minor.yy0); }
#line 5543 "sql.c"
        break;
      case 84: /* cmd ::= RESTORE MNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createRestoreComponentNodeStmt(pCxt, QUERY_NODE_RESTORE_MNODE_STMT, &yymsp[0].minor.yy0); }
#line 5548 "sql.c"
        break;
      case 85: /* cmd ::= RESTORE VNODE ON DNODE NK_INTEGER */
{ pCxt->pRootNode = createRestoreComponentNodeStmt(pCxt, QUERY_NODE_RESTORE_VNODE_STMT, &yymsp[0].minor.yy0); }
#line 5553 "sql.c"
        break;
      case 86: /* cmd ::= CREATE DATABASE not_exists_opt db_name db_options */
#line 205 "sql.y"
{ pCxt->pRootNode = createCreateDatabaseStmt(pCxt, yymsp[-2].minor.yy983, &yymsp[-1].minor.yy965, yymsp[0].minor.yy560); }
#line 5558 "sql.c"
        break;
      case 87: /* cmd ::= DROP DATABASE exists_opt db_name */
#line 206 "sql.y"
{ pCxt->pRootNode = createDropDatabaseStmt(pCxt, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 5563 "sql.c"
        break;
      case 88: /* cmd ::= USE db_name */
#line 207 "sql.y"
{ pCxt->pRootNode = createUseDatabaseStmt(pCxt, &yymsp[0].minor.yy965); }
#line 5568 "sql.c"
        break;
      case 89: /* cmd ::= ALTER DATABASE db_name alter_db_options */
#line 208 "sql.y"
{ pCxt->pRootNode = createAlterDatabaseStmt(pCxt, &yymsp[-1].minor.yy965, yymsp[0].minor.yy560); }
#line 5573 "sql.c"
        break;
      case 90: /* cmd ::= FLUSH DATABASE db_name */
#line 209 "sql.y"
{ pCxt->pRootNode = createFlushDatabaseStmt(pCxt, &yymsp[0].minor.yy965); }
#line 5578 "sql.c"
        break;
      case 91: /* cmd ::= TRIM DATABASE db_name speed_opt */
#line 210 "sql.y"
{ pCxt->pRootNode = createTrimDatabaseStmt(pCxt, &yymsp[-1].minor.yy965, yymsp[0].minor.yy424); }
#line 5583 "sql.c"
        break;
      case 92: /* cmd ::= COMPACT DATABASE db_name start_opt end_opt */
#line 211 "sql.y"
{ pCxt->pRootNode = createCompactStmt(pCxt, &yymsp[-2].minor.yy965, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 5588 "sql.c"
        break;
      case 93: /* not_exists_opt ::= IF NOT EXISTS */
#line 215 "sql.y"
{ yymsp[-2].minor.yy983 = true; }
#line 5593 "sql.c"
        break;
      case 95: /* exists_opt ::= IF EXISTS */
      case 365: /* or_replace_opt ::= OR REPLACE */ yytestcase(yyruleno==365);
      case 391: /* ignore_opt ::= IGNORE UNTREATED */ yytestcase(yyruleno==391);
#line 220 "sql.y"
{ yymsp[-1].minor.yy983 = true; }
#line 5600 "sql.c"
        break;
      case 97: /* db_options ::= */
#line 223 "sql.y"
{ yymsp[1].minor.yy560 = createDefaultDatabaseOptions(pCxt); }
#line 5605 "sql.c"
        break;
      case 98: /* db_options ::= db_options BUFFER NK_INTEGER */
#line 224 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_BUFFER, &yymsp[0].minor.yy0); }
#line 5610 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 99: /* db_options ::= db_options CACHEMODEL NK_STRING */
#line 225 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_CACHEMODEL, &yymsp[0].minor.yy0); }
#line 5616 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 100: /* db_options ::= db_options CACHESIZE NK_INTEGER */
#line 226 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_CACHESIZE, &yymsp[0].minor.yy0); }
#line 5622 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 101: /* db_options ::= db_options COMP NK_INTEGER */
#line 227 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_COMP, &yymsp[0].minor.yy0); }
#line 5628 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 102: /* db_options ::= db_options DURATION NK_INTEGER */
      case 103: /* db_options ::= db_options DURATION NK_VARIABLE */ yytestcase(yyruleno==103);
#line 228 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_DAYS, &yymsp[0].minor.yy0); }
#line 5635 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 104: /* db_options ::= db_options MAXROWS NK_INTEGER */
#line 230 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_MAXROWS, &yymsp[0].minor.yy0); }
#line 5641 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 105: /* db_options ::= db_options MINROWS NK_INTEGER */
#line 231 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_MINROWS, &yymsp[0].minor.yy0); }
#line 5647 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 106: /* db_options ::= db_options KEEP integer_list */
      case 107: /* db_options ::= db_options KEEP variable_list */ yytestcase(yyruleno==107);
#line 232 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_KEEP, yymsp[0].minor.yy388); }
#line 5654 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 108: /* db_options ::= db_options PAGES NK_INTEGER */
#line 234 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_PAGES, &yymsp[0].minor.yy0); }
#line 5660 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 109: /* db_options ::= db_options PAGESIZE NK_INTEGER */
#line 235 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_PAGESIZE, &yymsp[0].minor.yy0); }
#line 5666 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 110: /* db_options ::= db_options TSDB_PAGESIZE NK_INTEGER */
#line 236 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_TSDB_PAGESIZE, &yymsp[0].minor.yy0); }
#line 5672 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 111: /* db_options ::= db_options PRECISION NK_STRING */
#line 237 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_PRECISION, &yymsp[0].minor.yy0); }
#line 5678 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 112: /* db_options ::= db_options REPLICA NK_INTEGER */
#line 238 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_REPLICA, &yymsp[0].minor.yy0); }
#line 5684 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 113: /* db_options ::= db_options VGROUPS NK_INTEGER */
#line 240 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_VGROUPS, &yymsp[0].minor.yy0); }
#line 5690 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 114: /* db_options ::= db_options SINGLE_STABLE NK_INTEGER */
#line 241 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_SINGLE_STABLE, &yymsp[0].minor.yy0); }
#line 5696 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 115: /* db_options ::= db_options RETENTIONS retention_list */
#line 242 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_RETENTIONS, yymsp[0].minor.yy388); }
#line 5702 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 116: /* db_options ::= db_options SCHEMALESS NK_INTEGER */
#line 243 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_SCHEMALESS, &yymsp[0].minor.yy0); }
#line 5708 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 117: /* db_options ::= db_options WAL_LEVEL NK_INTEGER */
#line 244 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_WAL, &yymsp[0].minor.yy0); }
#line 5714 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 118: /* db_options ::= db_options WAL_FSYNC_PERIOD NK_INTEGER */
#line 245 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_FSYNC, &yymsp[0].minor.yy0); }
#line 5720 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 119: /* db_options ::= db_options WAL_RETENTION_PERIOD NK_INTEGER */
#line 246 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_WAL_RETENTION_PERIOD, &yymsp[0].minor.yy0); }
#line 5726 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 120: /* db_options ::= db_options WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-3].minor.yy560, DB_OPTION_WAL_RETENTION_PERIOD, &t);
                                                                                  }
#line 5736 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 121: /* db_options ::= db_options WAL_RETENTION_SIZE NK_INTEGER */
#line 252 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_WAL_RETENTION_SIZE, &yymsp[0].minor.yy0); }
#line 5742 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 122: /* db_options ::= db_options WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-3].minor.yy560, DB_OPTION_WAL_RETENTION_SIZE, &t);
                                                                                  }
#line 5752 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 123: /* db_options ::= db_options WAL_ROLL_PERIOD NK_INTEGER */
#line 258 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_WAL_ROLL_PERIOD, &yymsp[0].minor.yy0); }
#line 5758 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 124: /* db_options ::= db_options WAL_SEGMENT_SIZE NK_INTEGER */
#line 259 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_WAL_SEGMENT_SIZE, &yymsp[0].minor.yy0); }
#line 5764 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 125: /* db_options ::= db_options STT_TRIGGER NK_INTEGER */
#line 260 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_STT_TRIGGER, &yymsp[0].minor.yy0); }
#line 5770 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 126: /* db_options ::= db_options TABLE_PREFIX signed */
#line 261 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_TABLE_PREFIX, yymsp[0].minor.yy560); }
#line 5776 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 127: /* db_options ::= db_options TABLE_SUFFIX signed */
#line 262 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_TABLE_SUFFIX, yymsp[0].minor.yy560); }
#line 5782 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 128: /* db_options ::= db_options KEEP_TIME_OFFSET NK_INTEGER */
#line 263 "sql.y"
{ yylhsminor.yy560 = setDatabaseOption(pCxt, yymsp[-2].minor.yy560, DB_OPTION_KEEP_TIME_OFFSET, &yymsp[0].minor.yy0); }
#line 5788 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 129: /* alter_db_options ::= alter_db_option */
#line 265 "sql.y"
{ yylhsminor.yy560 = createAlterDatabaseOptions(pCxt); yylhsminor.yy560 = setAlterDatabaseOption(pCxt, yylhsminor.yy560, &yymsp[0].minor.yy443); }
#line 5794 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 130: /* alter_db_options ::= alter_db_options alter_db_option */
#line 266 "sql.y"
{ yylhsminor.yy560 = setAlterDatabaseOption(pCxt, yymsp[-1].minor.yy560, &yymsp[0].minor.yy443); }
#line 5800 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 131: /* alter_db_option ::= BUFFER NK_INTEGER */
#line 270 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_BUFFER; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5806 "sql.c"
        break;
      case 132: /* alter_db_option ::= CACHEMODEL NK_STRING */
#line 271 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_CACHEMODEL; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5811 "sql.c"
        break;
      case 133: /* alter_db_option ::= CACHESIZE NK_INTEGER */
#line 272 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_CACHESIZE; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5816 "sql.c"
        break;
      case 134: /* alter_db_option ::= WAL_FSYNC_PERIOD NK_INTEGER */
#line 273 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_FSYNC; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5821 "sql.c"
        break;
      case 135: /* alter_db_option ::= KEEP integer_list */
      case 136: /* alter_db_option ::= KEEP variable_list */ yytestcase(yyruleno==136);
#line 274 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_KEEP; yymsp[-1].minor.yy443.pList = yymsp[0].minor.yy388; }
#line 5827 "sql.c"
        break;
      case 137: /* alter_db_option ::= PAGES NK_INTEGER */
#line 276 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_PAGES; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5832 "sql.c"
        break;
      case 138: /* alter_db_option ::= REPLICA NK_INTEGER */
#line 277 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_REPLICA; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5837 "sql.c"
        break;
      case 139: /* alter_db_option ::= WAL_LEVEL NK_INTEGER */
#line 279 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_WAL; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5842 "sql.c"
        break;
      case 140: /* alter_db_option ::= STT_TRIGGER NK_INTEGER */
#line 280 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_STT_TRIGGER; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5847 "sql.c"
        break;
      case 141: /* alter_db_option ::= MINROWS NK_INTEGER */
#line 281 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_MINROWS; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5852 "sql.c"
        break;
      case 142: /* alter_db_option ::= WAL_RETENTION_PERIOD NK_INTEGER */
#line 282 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_WAL_RETENTION_PERIOD; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5857 "sql.c"
        break;
      case 143: /* alter_db_option ::= WAL_RETENTION_PERIOD NK_MINUS NK_INTEGER */
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yymsp[-2].minor.yy443.type = DB_OPTION_WAL_RETENTION_PERIOD; yymsp[-2].minor.yy443.val = t;
                                                                                  }
#line 5866 "sql.c"
        break;
      case 144: /* alter_db_option ::= WAL_RETENTION_SIZE NK_INTEGER */
#line 288 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_WAL_RETENTION_SIZE; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5871 "sql.c"
        break;
      case 145: /* alter_db_option ::= WAL_RETENTION_SIZE NK_MINUS NK_INTEGER */
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yymsp[-2].minor.yy443.type = DB_OPTION_WAL_RETENTION_SIZE; yymsp[-2].minor.yy443.val = t;
                                                                                  }
#line 5880 "sql.c"
        break;
      case 146: /* alter_db_option ::= KEEP_TIME_OFFSET NK_INTEGER */
#line 294 "sql.y"
{ yymsp[-1].minor.yy443.type = DB_OPTION_KEEP_TIME_OFFSET; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 5885 "sql.c"
        break;
      case 147: /* integer_list ::= NK_INTEGER */
#line 298 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0)); }
#line 5890 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 148: /* integer_list ::= integer_list NK_COMMA NK_INTEGER */
      case 404: /* dnode_list ::= dnode_list DNODE NK_INTEGER */ yytestcase(yyruleno==404);
#line 299 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0)); }
#line 5897 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 149: /* variable_list ::= NK_VARIABLE */
#line 303 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, createDurationValueNode(pCxt, &yymsp[0].minor.yy0)); }
#line 5903 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 150: /* variable_list ::= variable_list NK_COMMA NK_VARIABLE */
#line 304 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, createDurationValueNode(pCxt, &yymsp[0].minor.yy0)); }
#line 5909 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 151: /* retention_list ::= retention */
      case 182: /* multi_create_clause ::= create_subtable_clause */ yytestcase(yyruleno==182);
      case 185: /* multi_drop_clause ::= drop_table_clause */ yytestcase(yyruleno==185);
      case 192: /* column_def_list ::= column_def */ yytestcase(yyruleno==192);
      case 237: /* rollup_func_list ::= rollup_func_name */ yytestcase(yyruleno==237);
      case 242: /* col_name_list ::= col_name */ yytestcase(yyruleno==242);
      case 309: /* tag_list_opt ::= tag_item */ yytestcase(yyruleno==309);
      case 326: /* func_list ::= func */ yytestcase(yyruleno==326);
      case 433: /* literal_list ::= signed_literal */ yytestcase(yyruleno==433);
      case 504: /* other_para_list ::= star_func_para */ yytestcase(yyruleno==504);
      case 510: /* when_then_list ::= when_then_expr */ yytestcase(yyruleno==510);
      case 569: /* select_list ::= select_item */ yytestcase(yyruleno==569);
      case 580: /* partition_list ::= partition_item */ yytestcase(yyruleno==580);
      case 641: /* sort_specification_list ::= sort_specification */ yytestcase(yyruleno==641);
#line 308 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, yymsp[0].minor.yy560); }
#line 5928 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 152: /* retention_list ::= retention_list NK_COMMA retention */
      case 186: /* multi_drop_clause ::= multi_drop_clause NK_COMMA drop_table_clause */ yytestcase(yyruleno==186);
      case 193: /* column_def_list ::= column_def_list NK_COMMA column_def */ yytestcase(yyruleno==193);
      case 238: /* rollup_func_list ::= rollup_func_list NK_COMMA rollup_func_name */ yytestcase(yyruleno==238);
      case 243: /* col_name_list ::= col_name_list NK_COMMA col_name */ yytestcase(yyruleno==243);
      case 310: /* tag_list_opt ::= tag_list_opt NK_COMMA tag_item */ yytestcase(yyruleno==310);
      case 327: /* func_list ::= func_list NK_COMMA func */ yytestcase(yyruleno==327);
      case 434: /* literal_list ::= literal_list NK_COMMA signed_literal */ yytestcase(yyruleno==434);
      case 505: /* other_para_list ::= other_para_list NK_COMMA star_func_para */ yytestcase(yyruleno==505);
      case 570: /* select_list ::= select_list NK_COMMA select_item */ yytestcase(yyruleno==570);
      case 581: /* partition_list ::= partition_list NK_COMMA partition_item */ yytestcase(yyruleno==581);
      case 642: /* sort_specification_list ::= sort_specification_list NK_COMMA sort_specification */ yytestcase(yyruleno==642);
#line 309 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, yymsp[0].minor.yy560); }
#line 5945 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 153: /* retention ::= NK_VARIABLE NK_COLON NK_VARIABLE */
      case 154: /* retention ::= NK_MINUS NK_COLON NK_VARIABLE */ yytestcase(yyruleno==154);
#line 311 "sql.y"
{ yylhsminor.yy560 = createNodeListNodeEx(pCxt, createDurationValueNode(pCxt, &yymsp[-2].minor.yy0), createDurationValueNode(pCxt, &yymsp[0].minor.yy0)); }
#line 5952 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 155: /* speed_opt ::= */
      case 360: /* bufsize_opt ::= */ yytestcase(yyruleno==360);
#line 316 "sql.y"
{ yymsp[1].minor.yy424 = 0; }
#line 5959 "sql.c"
        break;
      case 156: /* speed_opt ::= BWLIMIT NK_INTEGER */
      case 361: /* bufsize_opt ::= BUFSIZE NK_INTEGER */ yytestcase(yyruleno==361);
#line 317 "sql.y"
{ yymsp[-1].minor.yy424 = taosStr2Int32(yymsp[0].minor.yy0.z, NULL, 10); }
#line 5965 "sql.c"
        break;
      case 158: /* start_opt ::= START WITH NK_INTEGER */
      case 162: /* end_opt ::= END WITH NK_INTEGER */ yytestcase(yyruleno==162);
#line 320 "sql.y"
{ yymsp[-2].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0); }
#line 5971 "sql.c"
        break;
      case 159: /* start_opt ::= START WITH NK_STRING */
      case 163: /* end_opt ::= END WITH NK_STRING */ yytestcase(yyruleno==163);
#line 321 "sql.y"
{ yymsp[-2].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_TIMESTAMP, &yymsp[0].minor.yy0); }
#line 5977 "sql.c"
        break;
      case 160: /* start_opt ::= START WITH TIMESTAMP NK_STRING */
      case 164: /* end_opt ::= END WITH TIMESTAMP NK_STRING */ yytestcase(yyruleno==164);
#line 322 "sql.y"
{ yymsp[-3].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_TIMESTAMP, &yymsp[0].minor.yy0); }
#line 5983 "sql.c"
        break;
      case 165: /* cmd ::= CREATE TABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def_opt table_options */
      case 167: /* cmd ::= CREATE STABLE not_exists_opt full_table_name NK_LP column_def_list NK_RP tags_def table_options */ yytestcase(yyruleno==167);
#line 331 "sql.y"
{ pCxt->pRootNode = createCreateTableStmt(pCxt, yymsp[-6].minor.yy983, yymsp[-5].minor.yy560, yymsp[-3].minor.yy388, yymsp[-1].minor.yy388, yymsp[0].minor.yy560); }
#line 5989 "sql.c"
        break;
      case 166: /* cmd ::= CREATE TABLE multi_create_clause */
#line 332 "sql.y"
{ pCxt->pRootNode = createCreateMultiTableStmt(pCxt, yymsp[0].minor.yy388); }
#line 5994 "sql.c"
        break;
      case 168: /* cmd ::= DROP TABLE multi_drop_clause */
#line 335 "sql.y"
{ pCxt->pRootNode = createDropTableStmt(pCxt, yymsp[0].minor.yy388); }
#line 5999 "sql.c"
        break;
      case 169: /* cmd ::= DROP STABLE exists_opt full_table_name */
#line 336 "sql.y"
{ pCxt->pRootNode = createDropSuperTableStmt(pCxt, yymsp[-1].minor.yy983, yymsp[0].minor.yy560); }
#line 6004 "sql.c"
        break;
      case 170: /* cmd ::= ALTER TABLE alter_table_clause */
      case 406: /* cmd ::= query_or_subquery */ yytestcase(yyruleno==406);
      case 407: /* cmd ::= insert_query */ yytestcase(yyruleno==407);
#line 338 "sql.y"
{ pCxt->pRootNode = yymsp[0].minor.yy560; }
#line 6011 "sql.c"
        break;
      case 171: /* cmd ::= ALTER STABLE alter_table_clause */
#line 339 "sql.y"
{ pCxt->pRootNode = setAlterSuperTableType(yymsp[0].minor.yy560); }
#line 6016 "sql.c"
        break;
      case 172: /* alter_table_clause ::= full_table_name alter_table_options */
#line 341 "sql.y"
{ yylhsminor.yy560 = createAlterTableModifyOptions(pCxt, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 6021 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 173: /* alter_table_clause ::= full_table_name ADD COLUMN column_name type_name */
#line 343 "sql.y"
{ yylhsminor.yy560 = createAlterTableAddModifyCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_ADD_COLUMN, &yymsp[-1].minor.yy965, yymsp[0].minor.yy412); }
#line 6027 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 174: /* alter_table_clause ::= full_table_name DROP COLUMN column_name */
#line 344 "sql.y"
{ yylhsminor.yy560 = createAlterTableDropCol(pCxt, yymsp[-3].minor.yy560, TSDB_ALTER_TABLE_DROP_COLUMN, &yymsp[0].minor.yy965); }
#line 6033 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 175: /* alter_table_clause ::= full_table_name MODIFY COLUMN column_name type_name */
#line 346 "sql.y"
{ yylhsminor.yy560 = createAlterTableAddModifyCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_UPDATE_COLUMN_BYTES, &yymsp[-1].minor.yy965, yymsp[0].minor.yy412); }
#line 6039 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 176: /* alter_table_clause ::= full_table_name RENAME COLUMN column_name column_name */
#line 348 "sql.y"
{ yylhsminor.yy560 = createAlterTableRenameCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_UPDATE_COLUMN_NAME, &yymsp[-1].minor.yy965, &yymsp[0].minor.yy965); }
#line 6045 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 177: /* alter_table_clause ::= full_table_name ADD TAG column_name type_name */
#line 350 "sql.y"
{ yylhsminor.yy560 = createAlterTableAddModifyCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_ADD_TAG, &yymsp[-1].minor.yy965, yymsp[0].minor.yy412); }
#line 6051 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 178: /* alter_table_clause ::= full_table_name DROP TAG column_name */
#line 351 "sql.y"
{ yylhsminor.yy560 = createAlterTableDropCol(pCxt, yymsp[-3].minor.yy560, TSDB_ALTER_TABLE_DROP_TAG, &yymsp[0].minor.yy965); }
#line 6057 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 179: /* alter_table_clause ::= full_table_name MODIFY TAG column_name type_name */
#line 353 "sql.y"
{ yylhsminor.yy560 = createAlterTableAddModifyCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_UPDATE_TAG_BYTES, &yymsp[-1].minor.yy965, yymsp[0].minor.yy412); }
#line 6063 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 180: /* alter_table_clause ::= full_table_name RENAME TAG column_name column_name */
#line 355 "sql.y"
{ yylhsminor.yy560 = createAlterTableRenameCol(pCxt, yymsp[-4].minor.yy560, TSDB_ALTER_TABLE_UPDATE_TAG_NAME, &yymsp[-1].minor.yy965, &yymsp[0].minor.yy965); }
#line 6069 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 181: /* alter_table_clause ::= full_table_name SET TAG column_name NK_EQ signed_literal */
#line 357 "sql.y"
{ yylhsminor.yy560 = createAlterTableSetTag(pCxt, yymsp[-5].minor.yy560, &yymsp[-2].minor.yy965, yymsp[0].minor.yy560); }
#line 6075 "sql.c"
  yymsp[-5].minor.yy560 = yylhsminor.yy560;
        break;
      case 183: /* multi_create_clause ::= multi_create_clause create_subtable_clause */
      case 511: /* when_then_list ::= when_then_list when_then_expr */ yytestcase(yyruleno==511);
#line 362 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-1].minor.yy388, yymsp[0].minor.yy560); }
#line 6082 "sql.c"
  yymsp[-1].minor.yy388 = yylhsminor.yy388;
        break;
      case 184: /* create_subtable_clause ::= not_exists_opt full_table_name USING full_table_name specific_cols_opt TAGS NK_LP expression_list NK_RP table_options */
#line 366 "sql.y"
{ yylhsminor.yy560 = createCreateSubTableClause(pCxt, yymsp[-9].minor.yy983, yymsp[-8].minor.yy560, yymsp[-6].minor.yy560, yymsp[-5].minor.yy388, yymsp[-2].minor.yy388, yymsp[0].minor.yy560); }
#line 6088 "sql.c"
  yymsp[-9].minor.yy560 = yylhsminor.yy560;
        break;
      case 187: /* drop_table_clause ::= exists_opt full_table_name */
#line 373 "sql.y"
{ yylhsminor.yy560 = createDropTableClause(pCxt, yymsp[-1].minor.yy983, yymsp[0].minor.yy560); }
#line 6094 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 189: /* specific_cols_opt ::= NK_LP col_name_list NK_RP */
      case 375: /* col_list_opt ::= NK_LP col_name_list NK_RP */ yytestcase(yyruleno==375);
#line 378 "sql.y"
{ yymsp[-2].minor.yy388 = yymsp[-1].minor.yy388; }
#line 6101 "sql.c"
        break;
      case 190: /* full_table_name ::= table_name */
#line 380 "sql.y"
{ yylhsminor.yy560 = createRealTableNode(pCxt, NULL, &yymsp[0].minor.yy965, NULL); }
#line 6106 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 191: /* full_table_name ::= db_name NK_DOT table_name */
#line 381 "sql.y"
{ yylhsminor.yy560 = createRealTableNode(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965, NULL); }
#line 6112 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 194: /* column_def ::= column_name type_name */
#line 388 "sql.y"
{ yylhsminor.yy560 = createColumnDefNode(pCxt, &yymsp[-1].minor.yy965, yymsp[0].minor.yy412, NULL, false); }
#line 6118 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 195: /* column_def ::= column_name type_name PRIMARY KEY */
#line 389 "sql.y"
{ yylhsminor.yy560 = createColumnDefNode(pCxt, &yymsp[-3].minor.yy965, yymsp[-2].minor.yy412, NULL, true); }
#line 6124 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 196: /* type_name ::= BOOL */
#line 394 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_BOOL); }
#line 6130 "sql.c"
        break;
      case 197: /* type_name ::= TINYINT */
#line 395 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_TINYINT); }
#line 6135 "sql.c"
        break;
      case 198: /* type_name ::= SMALLINT */
#line 396 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_SMALLINT); }
#line 6140 "sql.c"
        break;
      case 199: /* type_name ::= INT */
      case 200: /* type_name ::= INTEGER */ yytestcase(yyruleno==200);
#line 397 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_INT); }
#line 6146 "sql.c"
        break;
      case 201: /* type_name ::= BIGINT */
#line 399 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_BIGINT); }
#line 6151 "sql.c"
        break;
      case 202: /* type_name ::= FLOAT */
#line 400 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_FLOAT); }
#line 6156 "sql.c"
        break;
      case 203: /* type_name ::= DOUBLE */
#line 401 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_DOUBLE); }
#line 6161 "sql.c"
        break;
      case 204: /* type_name ::= BINARY NK_LP NK_INTEGER NK_RP */
#line 402 "sql.y"
{ yymsp[-3].minor.yy412 = createVarLenDataType(TSDB_DATA_TYPE_BINARY, &yymsp[-1].minor.yy0); }
#line 6166 "sql.c"
        break;
      case 205: /* type_name ::= TIMESTAMP */
#line 403 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_TIMESTAMP); }
#line 6171 "sql.c"
        break;
      case 206: /* type_name ::= NCHAR NK_LP NK_INTEGER NK_RP */
#line 404 "sql.y"
{ yymsp[-3].minor.yy412 = createVarLenDataType(TSDB_DATA_TYPE_NCHAR, &yymsp[-1].minor.yy0); }
#line 6176 "sql.c"
        break;
      case 207: /* type_name ::= TINYINT UNSIGNED */
#line 405 "sql.y"
{ yymsp[-1].minor.yy412 = createDataType(TSDB_DATA_TYPE_UTINYINT); }
#line 6181 "sql.c"
        break;
      case 208: /* type_name ::= SMALLINT UNSIGNED */
#line 406 "sql.y"
{ yymsp[-1].minor.yy412 = createDataType(TSDB_DATA_TYPE_USMALLINT); }
#line 6186 "sql.c"
        break;
      case 209: /* type_name ::= INT UNSIGNED */
#line 407 "sql.y"
{ yymsp[-1].minor.yy412 = createDataType(TSDB_DATA_TYPE_UINT); }
#line 6191 "sql.c"
        break;
      case 210: /* type_name ::= BIGINT UNSIGNED */
#line 408 "sql.y"
{ yymsp[-1].minor.yy412 = createDataType(TSDB_DATA_TYPE_UBIGINT); }
#line 6196 "sql.c"
        break;
      case 211: /* type_name ::= JSON */
#line 409 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_JSON); }
#line 6201 "sql.c"
        break;
      case 212: /* type_name ::= VARCHAR NK_LP NK_INTEGER NK_RP */
#line 410 "sql.y"
{ yymsp[-3].minor.yy412 = createVarLenDataType(TSDB_DATA_TYPE_VARCHAR, &yymsp[-1].minor.yy0); }
#line 6206 "sql.c"
        break;
      case 213: /* type_name ::= MEDIUMBLOB */
#line 411 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_MEDIUMBLOB); }
#line 6211 "sql.c"
        break;
      case 214: /* type_name ::= BLOB */
#line 412 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_BLOB); }
#line 6216 "sql.c"
        break;
      case 215: /* type_name ::= VARBINARY NK_LP NK_INTEGER NK_RP */
#line 413 "sql.y"
{ yymsp[-3].minor.yy412 = createVarLenDataType(TSDB_DATA_TYPE_VARBINARY, &yymsp[-1].minor.yy0); }
#line 6221 "sql.c"
        break;
      case 216: /* type_name ::= GEOMETRY NK_LP NK_INTEGER NK_RP */
#line 414 "sql.y"
{ yymsp[-3].minor.yy412 = createVarLenDataType(TSDB_DATA_TYPE_GEOMETRY, &yymsp[-1].minor.yy0); }
#line 6226 "sql.c"
        break;
      case 217: /* type_name ::= DECIMAL */
#line 415 "sql.y"
{ yymsp[0].minor.yy412 = createDataType(TSDB_DATA_TYPE_DECIMAL); }
#line 6231 "sql.c"
        break;
      case 218: /* type_name ::= DECIMAL NK_LP NK_INTEGER NK_RP */
#line 416 "sql.y"
{ yymsp[-3].minor.yy412 = createDataType(TSDB_DATA_TYPE_DECIMAL); }
#line 6236 "sql.c"
        break;
      case 219: /* type_name ::= DECIMAL NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
#line 417 "sql.y"
{ yymsp[-5].minor.yy412 = createDataType(TSDB_DATA_TYPE_DECIMAL); }
#line 6241 "sql.c"
        break;
      case 222: /* tags_def ::= TAGS NK_LP column_def_list NK_RP */
      case 378: /* tag_def_or_ref_opt ::= TAGS NK_LP col_name_list NK_RP */ yytestcase(yyruleno==378);
#line 426 "sql.y"
{ yymsp[-3].minor.yy388 = yymsp[-1].minor.yy388; }
#line 6247 "sql.c"
        break;
      case 223: /* table_options ::= */
#line 428 "sql.y"
{ yymsp[1].minor.yy560 = createDefaultTableOptions(pCxt); }
#line 6252 "sql.c"
        break;
      case 224: /* table_options ::= table_options COMMENT NK_STRING */
#line 429 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-2].minor.yy560, TABLE_OPTION_COMMENT, &yymsp[0].minor.yy0); }
#line 6257 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 225: /* table_options ::= table_options MAX_DELAY duration_list */
#line 430 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-2].minor.yy560, TABLE_OPTION_MAXDELAY, yymsp[0].minor.yy388); }
#line 6263 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 226: /* table_options ::= table_options WATERMARK duration_list */
#line 431 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-2].minor.yy560, TABLE_OPTION_WATERMARK, yymsp[0].minor.yy388); }
#line 6269 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 227: /* table_options ::= table_options ROLLUP NK_LP rollup_func_list NK_RP */
#line 432 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-4].minor.yy560, TABLE_OPTION_ROLLUP, yymsp[-1].minor.yy388); }
#line 6275 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 228: /* table_options ::= table_options TTL NK_INTEGER */
#line 433 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-2].minor.yy560, TABLE_OPTION_TTL, &yymsp[0].minor.yy0); }
#line 6281 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 229: /* table_options ::= table_options SMA NK_LP col_name_list NK_RP */
#line 434 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-4].minor.yy560, TABLE_OPTION_SMA, yymsp[-1].minor.yy388); }
#line 6287 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 230: /* table_options ::= table_options DELETE_MARK duration_list */
#line 435 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-2].minor.yy560, TABLE_OPTION_DELETE_MARK, yymsp[0].minor.yy388); }
#line 6293 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 231: /* alter_table_options ::= alter_table_option */
#line 437 "sql.y"
{ yylhsminor.yy560 = createAlterTableOptions(pCxt); yylhsminor.yy560 = setTableOption(pCxt, yylhsminor.yy560, yymsp[0].minor.yy443.type, &yymsp[0].minor.yy443.val); }
#line 6299 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 232: /* alter_table_options ::= alter_table_options alter_table_option */
#line 438 "sql.y"
{ yylhsminor.yy560 = setTableOption(pCxt, yymsp[-1].minor.yy560, yymsp[0].minor.yy443.type, &yymsp[0].minor.yy443.val); }
#line 6305 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 233: /* alter_table_option ::= COMMENT NK_STRING */
#line 442 "sql.y"
{ yymsp[-1].minor.yy443.type = TABLE_OPTION_COMMENT; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 6311 "sql.c"
        break;
      case 234: /* alter_table_option ::= TTL NK_INTEGER */
#line 443 "sql.y"
{ yymsp[-1].minor.yy443.type = TABLE_OPTION_TTL; yymsp[-1].minor.yy443.val = yymsp[0].minor.yy0; }
#line 6316 "sql.c"
        break;
      case 235: /* duration_list ::= duration_literal */
      case 465: /* expression_list ::= expr_or_subquery */ yytestcase(yyruleno==465);
#line 447 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 6322 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 236: /* duration_list ::= duration_list NK_COMMA duration_literal */
      case 466: /* expression_list ::= expression_list NK_COMMA expr_or_subquery */ yytestcase(yyruleno==466);
#line 448 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 6329 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 239: /* rollup_func_name ::= function_name */
#line 455 "sql.y"
{ yylhsminor.yy560 = createFunctionNode(pCxt, &yymsp[0].minor.yy965, NULL); }
#line 6335 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 240: /* rollup_func_name ::= FIRST */
      case 241: /* rollup_func_name ::= LAST */ yytestcase(yyruleno==241);
      case 312: /* tag_item ::= QTAGS */ yytestcase(yyruleno==312);
#line 456 "sql.y"
{ yylhsminor.yy560 = createFunctionNode(pCxt, &yymsp[0].minor.yy0, NULL); }
#line 6343 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 244: /* col_name ::= column_name */
      case 313: /* tag_item ::= column_name */ yytestcase(yyruleno==313);
#line 464 "sql.y"
{ yylhsminor.yy560 = createColumnNode(pCxt, NULL, &yymsp[0].minor.yy965); }
#line 6350 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 245: /* cmd ::= SHOW DNODES */
#line 467 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_DNODES_STMT); }
#line 6356 "sql.c"
        break;
      case 246: /* cmd ::= SHOW USERS */
#line 468 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_USERS_STMT); }
#line 6361 "sql.c"
        break;
      case 247: /* cmd ::= SHOW USER PRIVILEGES */
#line 469 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_USER_PRIVILEGES_STMT); }
#line 6366 "sql.c"
        break;
      case 248: /* cmd ::= SHOW db_kind_opt DATABASES */
#line 470 "sql.y"
{
                                                                                    pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_DATABASES_STMT);
                                                                                    setShowKind(pCxt, pCxt->pRootNode, yymsp[-1].minor.yy591);
                                                                                  }
#line 6374 "sql.c"
        break;
      case 249: /* cmd ::= SHOW table_kind_db_name_cond_opt TABLES like_pattern_opt */
#line 474 "sql.y"
{
                                                                                    pCxt->pRootNode = createShowTablesStmt(pCxt, yymsp[-2].minor.yy385, yymsp[0].minor.yy560, OP_TYPE_LIKE);
                                                                                  }
#line 6381 "sql.c"
        break;
      case 250: /* cmd ::= SHOW db_name_cond_opt STABLES like_pattern_opt */
#line 477 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_STABLES_STMT, yymsp[-2].minor.yy560, yymsp[0].minor.yy560, OP_TYPE_LIKE); }
#line 6386 "sql.c"
        break;
      case 251: /* cmd ::= SHOW db_name_cond_opt VGROUPS */
#line 478 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_VGROUPS_STMT, yymsp[-1].minor.yy560, NULL, OP_TYPE_LIKE); }
#line 6391 "sql.c"
        break;
      case 252: /* cmd ::= SHOW MNODES */
#line 479 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_MNODES_STMT); }
#line 6396 "sql.c"
        break;
      case 253: /* cmd ::= SHOW QNODES */
#line 481 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_QNODES_STMT); }
#line 6401 "sql.c"
        break;
      case 254: /* cmd ::= SHOW FUNCTIONS */
#line 482 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_FUNCTIONS_STMT); }
#line 6406 "sql.c"
        break;
      case 255: /* cmd ::= SHOW INDEXES FROM table_name_cond from_db_opt */
#line 483 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_INDEXES_STMT, yymsp[0].minor.yy560, yymsp[-1].minor.yy560, OP_TYPE_EQUAL); }
#line 6411 "sql.c"
        break;
      case 256: /* cmd ::= SHOW INDEXES FROM db_name NK_DOT table_name */
#line 484 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_INDEXES_STMT, createIdentifierValueNode(pCxt, &yymsp[-2].minor.yy965), createIdentifierValueNode(pCxt, &yymsp[0].minor.yy965), OP_TYPE_EQUAL); }
#line 6416 "sql.c"
        break;
      case 257: /* cmd ::= SHOW STREAMS */
#line 485 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_STREAMS_STMT); }
#line 6421 "sql.c"
        break;
      case 258: /* cmd ::= SHOW ACCOUNTS */
#line 486 "sql.y"
{ pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_EXPRIE_STATEMENT); }
#line 6426 "sql.c"
        break;
      case 259: /* cmd ::= SHOW APPS */
#line 487 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_APPS_STMT); }
#line 6431 "sql.c"
        break;
      case 260: /* cmd ::= SHOW CONNECTIONS */
#line 488 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_CONNECTIONS_STMT); }
#line 6436 "sql.c"
        break;
      case 261: /* cmd ::= SHOW LICENCES */
      case 262: /* cmd ::= SHOW GRANTS */ yytestcase(yyruleno==262);
#line 489 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_LICENCES_STMT); }
#line 6442 "sql.c"
        break;
      case 263: /* cmd ::= SHOW GRANTS FULL */
#line 491 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_GRANTS_FULL_STMT); }
#line 6447 "sql.c"
        break;
      case 264: /* cmd ::= SHOW GRANTS LOGS */
#line 492 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_GRANTS_LOGS_STMT); }
#line 6452 "sql.c"
        break;
      case 265: /* cmd ::= SHOW CLUSTER MACHINES */
#line 493 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_CLUSTER_MACHINES_STMT); }
#line 6457 "sql.c"
        break;
      case 266: /* cmd ::= SHOW CREATE DATABASE db_name */
#line 494 "sql.y"
{ pCxt->pRootNode = createShowCreateDatabaseStmt(pCxt, &yymsp[0].minor.yy965); }
#line 6462 "sql.c"
        break;
      case 267: /* cmd ::= SHOW CREATE TABLE full_table_name */
#line 495 "sql.y"
{ pCxt->pRootNode = createShowCreateTableStmt(pCxt, QUERY_NODE_SHOW_CREATE_TABLE_STMT, yymsp[0].minor.yy560); }
#line 6467 "sql.c"
        break;
      case 268: /* cmd ::= SHOW CREATE STABLE full_table_name */
#line 496 "sql.y"
{ pCxt->pRootNode = createShowCreateTableStmt(pCxt, QUERY_NODE_SHOW_CREATE_STABLE_STMT, yymsp[0].minor.yy560); }
#line 6472 "sql.c"
        break;
      case 269: /* cmd ::= SHOW QUERIES */
#line 497 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_QUERIES_STMT); }
#line 6477 "sql.c"
        break;
      case 270: /* cmd ::= SHOW SCORES */
#line 498 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_SCORES_STMT); }
#line 6482 "sql.c"
        break;
      case 271: /* cmd ::= SHOW TOPICS */
#line 499 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_TOPICS_STMT); }
#line 6487 "sql.c"
        break;
      case 272: /* cmd ::= SHOW VARIABLES */
      case 273: /* cmd ::= SHOW CLUSTER VARIABLES */ yytestcase(yyruleno==273);
#line 500 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_VARIABLES_STMT); }
#line 6493 "sql.c"
        break;
      case 274: /* cmd ::= SHOW LOCAL VARIABLES */
#line 502 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_LOCAL_VARIABLES_STMT); }
#line 6498 "sql.c"
        break;
      case 275: /* cmd ::= SHOW DNODE NK_INTEGER VARIABLES like_pattern_opt */
#line 503 "sql.y"
{ pCxt->pRootNode = createShowDnodeVariablesStmt(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[-2].minor.yy0), yymsp[0].minor.yy560); }
#line 6503 "sql.c"
        break;
      case 276: /* cmd ::= SHOW BNODES */
#line 504 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_BNODES_STMT); }
#line 6508 "sql.c"
        break;
      case 277: /* cmd ::= SHOW SNODES */
#line 505 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_SNODES_STMT); }
#line 6513 "sql.c"
        break;
      case 278: /* cmd ::= SHOW CLUSTER */
#line 506 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_CLUSTER_STMT); }
#line 6518 "sql.c"
        break;
      case 279: /* cmd ::= SHOW TRANSACTIONS */
#line 507 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_TRANSACTIONS_STMT); }
#line 6523 "sql.c"
        break;
      case 280: /* cmd ::= SHOW TABLE DISTRIBUTED full_table_name */
#line 508 "sql.y"
{ pCxt->pRootNode = createShowTableDistributedStmt(pCxt, yymsp[0].minor.yy560); }
#line 6528 "sql.c"
        break;
      case 281: /* cmd ::= SHOW CONSUMERS */
#line 509 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_CONSUMERS_STMT); }
#line 6533 "sql.c"
        break;
      case 282: /* cmd ::= SHOW SUBSCRIPTIONS */
#line 510 "sql.y"
{ pCxt->pRootNode = createShowStmt(pCxt, QUERY_NODE_SHOW_SUBSCRIPTIONS_STMT); }
#line 6538 "sql.c"
        break;
      case 283: /* cmd ::= SHOW TAGS FROM table_name_cond from_db_opt */
#line 511 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_TAGS_STMT, yymsp[0].minor.yy560, yymsp[-1].minor.yy560, OP_TYPE_EQUAL); }
#line 6543 "sql.c"
        break;
      case 284: /* cmd ::= SHOW TAGS FROM db_name NK_DOT table_name */
#line 512 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_TAGS_STMT, createIdentifierValueNode(pCxt, &yymsp[-2].minor.yy965), createIdentifierValueNode(pCxt, &yymsp[0].minor.yy965), OP_TYPE_EQUAL); }
#line 6548 "sql.c"
        break;
      case 285: /* cmd ::= SHOW TABLE TAGS tag_list_opt FROM table_name_cond from_db_opt */
#line 513 "sql.y"
{ pCxt->pRootNode = createShowTableTagsStmt(pCxt, yymsp[-1].minor.yy560, yymsp[0].minor.yy560, yymsp[-3].minor.yy388); }
#line 6553 "sql.c"
        break;
      case 286: /* cmd ::= SHOW TABLE TAGS tag_list_opt FROM db_name NK_DOT table_name */
#line 514 "sql.y"
{ pCxt->pRootNode = createShowTableTagsStmt(pCxt, createIdentifierValueNode(pCxt, &yymsp[0].minor.yy965), createIdentifierValueNode(pCxt, &yymsp[-2].minor.yy965), yymsp[-4].minor.yy388); }
#line 6558 "sql.c"
        break;
      case 287: /* cmd ::= SHOW VNODES ON DNODE NK_INTEGER */
#line 515 "sql.y"
{ pCxt->pRootNode = createShowVnodesStmt(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0), NULL); }
#line 6563 "sql.c"
        break;
      case 288: /* cmd ::= SHOW VNODES */
#line 516 "sql.y"
{ pCxt->pRootNode = createShowVnodesStmt(pCxt, NULL, NULL); }
#line 6568 "sql.c"
        break;
      case 289: /* cmd ::= SHOW db_name_cond_opt ALIVE */
#line 518 "sql.y"
{ pCxt->pRootNode = createShowAliveStmt(pCxt, yymsp[-1].minor.yy560,    QUERY_NODE_SHOW_DB_ALIVE_STMT); }
#line 6573 "sql.c"
        break;
      case 290: /* cmd ::= SHOW CLUSTER ALIVE */
#line 519 "sql.y"
{ pCxt->pRootNode = createShowAliveStmt(pCxt, NULL, QUERY_NODE_SHOW_CLUSTER_ALIVE_STMT); }
#line 6578 "sql.c"
        break;
      case 291: /* cmd ::= SHOW db_name_cond_opt VIEWS like_pattern_opt */
#line 520 "sql.y"
{ pCxt->pRootNode = createShowStmtWithCond(pCxt, QUERY_NODE_SHOW_VIEWS_STMT, yymsp[-2].minor.yy560, yymsp[0].minor.yy560, OP_TYPE_LIKE); }
#line 6583 "sql.c"
        break;
      case 292: /* cmd ::= SHOW CREATE VIEW full_table_name */
#line 521 "sql.y"
{ pCxt->pRootNode = createShowCreateViewStmt(pCxt, QUERY_NODE_SHOW_CREATE_VIEW_STMT, yymsp[0].minor.yy560); }
#line 6588 "sql.c"
        break;
      case 293: /* cmd ::= SHOW COMPACTS */
#line 522 "sql.y"
{ pCxt->pRootNode = createShowCompactsStmt(pCxt, QUERY_NODE_SHOW_COMPACTS_STMT); }
#line 6593 "sql.c"
        break;
      case 294: /* cmd ::= SHOW COMPACT NK_INTEGER */
#line 523 "sql.y"
{ pCxt->pRootNode = createShowCompactDetailsStmt(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0)); }
#line 6598 "sql.c"
        break;
      case 295: /* table_kind_db_name_cond_opt ::= */
#line 527 "sql.y"
{ yymsp[1].minor.yy385.kind = SHOW_KIND_ALL; yymsp[1].minor.yy385.dbName = nil_token; }
#line 6603 "sql.c"
        break;
      case 296: /* table_kind_db_name_cond_opt ::= table_kind */
#line 528 "sql.y"
{ yylhsminor.yy385.kind = yymsp[0].minor.yy591; yylhsminor.yy385.dbName = nil_token; }
#line 6608 "sql.c"
  yymsp[0].minor.yy385 = yylhsminor.yy385;
        break;
      case 297: /* table_kind_db_name_cond_opt ::= db_name NK_DOT */
#line 529 "sql.y"
{ yylhsminor.yy385.kind = SHOW_KIND_ALL; yylhsminor.yy385.dbName = yymsp[-1].minor.yy965; }
#line 6614 "sql.c"
  yymsp[-1].minor.yy385 = yylhsminor.yy385;
        break;
      case 298: /* table_kind_db_name_cond_opt ::= table_kind db_name NK_DOT */
#line 530 "sql.y"
{ yylhsminor.yy385.kind = yymsp[-2].minor.yy591; yylhsminor.yy385.dbName = yymsp[-1].minor.yy965; }
#line 6620 "sql.c"
  yymsp[-2].minor.yy385 = yylhsminor.yy385;
        break;
      case 299: /* table_kind ::= NORMAL */
#line 534 "sql.y"
{ yymsp[0].minor.yy591 = SHOW_KIND_TABLES_NORMAL; }
#line 6626 "sql.c"
        break;
      case 300: /* table_kind ::= CHILD */
#line 535 "sql.y"
{ yymsp[0].minor.yy591 = SHOW_KIND_TABLES_CHILD; }
#line 6631 "sql.c"
        break;
      case 301: /* db_name_cond_opt ::= */
      case 306: /* from_db_opt ::= */ yytestcase(yyruleno==306);
#line 537 "sql.y"
{ yymsp[1].minor.yy560 = createDefaultDatabaseCondValue(pCxt); }
#line 6637 "sql.c"
        break;
      case 302: /* db_name_cond_opt ::= db_name NK_DOT */
#line 538 "sql.y"
{ yylhsminor.yy560 = createIdentifierValueNode(pCxt, &yymsp[-1].minor.yy965); }
#line 6642 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 304: /* like_pattern_opt ::= LIKE NK_STRING */
#line 541 "sql.y"
{ yymsp[-1].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0); }
#line 6648 "sql.c"
        break;
      case 305: /* table_name_cond ::= table_name */
#line 543 "sql.y"
{ yylhsminor.yy560 = createIdentifierValueNode(pCxt, &yymsp[0].minor.yy965); }
#line 6653 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 307: /* from_db_opt ::= FROM db_name */
#line 546 "sql.y"
{ yymsp[-1].minor.yy560 = createIdentifierValueNode(pCxt, &yymsp[0].minor.yy965); }
#line 6659 "sql.c"
        break;
      case 311: /* tag_item ::= TBNAME */
#line 554 "sql.y"
{ yylhsminor.yy560 = setProjectionAlias(pCxt, createFunctionNode(pCxt, &yymsp[0].minor.yy0, NULL), &yymsp[0].minor.yy0); }
#line 6664 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 314: /* tag_item ::= column_name column_alias */
#line 557 "sql.y"
{ yylhsminor.yy560 = setProjectionAlias(pCxt, createColumnNode(pCxt, NULL, &yymsp[-1].minor.yy965), &yymsp[0].minor.yy965); }
#line 6670 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 315: /* tag_item ::= column_name AS column_alias */
#line 558 "sql.y"
{ yylhsminor.yy560 = setProjectionAlias(pCxt, createColumnNode(pCxt, NULL, &yymsp[-2].minor.yy965), &yymsp[0].minor.yy965); }
#line 6676 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 316: /* db_kind_opt ::= */
#line 562 "sql.y"
{ yymsp[1].minor.yy591 = SHOW_KIND_ALL; }
#line 6682 "sql.c"
        break;
      case 317: /* db_kind_opt ::= USER */
#line 563 "sql.y"
{ yymsp[0].minor.yy591 = SHOW_KIND_DATABASES_USER; }
#line 6687 "sql.c"
        break;
      case 318: /* db_kind_opt ::= SYSTEM */
#line 564 "sql.y"
{ yymsp[0].minor.yy591 = SHOW_KIND_DATABASES_SYSTEM; }
#line 6692 "sql.c"
        break;
      case 319: /* cmd ::= CREATE SMA INDEX not_exists_opt col_name ON full_table_name index_options */
#line 568 "sql.y"
{ pCxt->pRootNode = createCreateIndexStmt(pCxt, INDEX_TYPE_SMA, yymsp[-4].minor.yy983, yymsp[-3].minor.yy560, yymsp[-1].minor.yy560, NULL, yymsp[0].minor.yy560); }
#line 6697 "sql.c"
        break;
      case 320: /* cmd ::= CREATE INDEX not_exists_opt col_name ON full_table_name NK_LP col_name_list NK_RP */
#line 570 "sql.y"
{ pCxt->pRootNode = createCreateIndexStmt(pCxt, INDEX_TYPE_NORMAL, yymsp[-6].minor.yy983, yymsp[-5].minor.yy560, yymsp[-3].minor.yy560, yymsp[-1].minor.yy388, NULL); }
#line 6702 "sql.c"
        break;
      case 321: /* cmd ::= DROP INDEX exists_opt full_index_name */
#line 571 "sql.y"
{ pCxt->pRootNode = createDropIndexStmt(pCxt, yymsp[-1].minor.yy983, yymsp[0].minor.yy560); }
#line 6707 "sql.c"
        break;
      case 322: /* full_index_name ::= index_name */
#line 573 "sql.y"
{ yylhsminor.yy560 = createRealTableNodeForIndexName(pCxt, NULL, &yymsp[0].minor.yy965); }
#line 6712 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 323: /* full_index_name ::= db_name NK_DOT index_name */
#line 574 "sql.y"
{ yylhsminor.yy560 = createRealTableNodeForIndexName(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965); }
#line 6718 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 324: /* index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_RP sliding_opt sma_stream_opt */
#line 577 "sql.y"
{ yymsp[-9].minor.yy560 = createIndexOption(pCxt, yymsp[-7].minor.yy388, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), NULL, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 6724 "sql.c"
        break;
      case 325: /* index_options ::= FUNCTION NK_LP func_list NK_RP INTERVAL NK_LP duration_literal NK_COMMA duration_literal NK_RP sliding_opt sma_stream_opt */
#line 580 "sql.y"
{ yymsp[-11].minor.yy560 = createIndexOption(pCxt, yymsp[-9].minor.yy388, releaseRawExprNode(pCxt, yymsp[-5].minor.yy560), releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 6729 "sql.c"
        break;
      case 328: /* func ::= sma_func_name NK_LP expression_list NK_RP */
#line 587 "sql.y"
{ yylhsminor.yy560 = createFunctionNode(pCxt, &yymsp[-3].minor.yy965, yymsp[-1].minor.yy388); }
#line 6734 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 329: /* sma_func_name ::= function_name */
      case 554: /* alias_opt ::= table_alias */ yytestcase(yyruleno==554);
#line 591 "sql.y"
{ yylhsminor.yy965 = yymsp[0].minor.yy965; }
#line 6741 "sql.c"
  yymsp[0].minor.yy965 = yylhsminor.yy965;
        break;
      case 334: /* sma_stream_opt ::= */
      case 379: /* stream_options ::= */ yytestcase(yyruleno==379);
#line 597 "sql.y"
{ yymsp[1].minor.yy560 = createStreamOptions(pCxt); }
#line 6748 "sql.c"
        break;
      case 335: /* sma_stream_opt ::= sma_stream_opt WATERMARK duration_literal */
#line 598 "sql.y"
{ ((SStreamOptions*)yymsp[-2].minor.yy560)->pWatermark = releaseRawExprNode(pCxt, yymsp[0].minor.yy560); yylhsminor.yy560 = yymsp[-2].minor.yy560; }
#line 6753 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 336: /* sma_stream_opt ::= sma_stream_opt MAX_DELAY duration_literal */
#line 599 "sql.y"
{ ((SStreamOptions*)yymsp[-2].minor.yy560)->pDelay = releaseRawExprNode(pCxt, yymsp[0].minor.yy560); yylhsminor.yy560 = yymsp[-2].minor.yy560; }
#line 6759 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 337: /* sma_stream_opt ::= sma_stream_opt DELETE_MARK duration_literal */
#line 600 "sql.y"
{ ((SStreamOptions*)yymsp[-2].minor.yy560)->pDeleteMark = releaseRawExprNode(pCxt, yymsp[0].minor.yy560); yylhsminor.yy560 = yymsp[-2].minor.yy560; }
#line 6765 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 338: /* with_meta ::= AS */
#line 605 "sql.y"
{ yymsp[0].minor.yy424 = 0; }
#line 6771 "sql.c"
        break;
      case 339: /* with_meta ::= WITH META AS */
#line 606 "sql.y"
{ yymsp[-2].minor.yy424 = 1; }
#line 6776 "sql.c"
        break;
      case 340: /* with_meta ::= ONLY META AS */
#line 607 "sql.y"
{ yymsp[-2].minor.yy424 = 2; }
#line 6781 "sql.c"
        break;
      case 341: /* cmd ::= CREATE TOPIC not_exists_opt topic_name AS query_or_subquery */
#line 609 "sql.y"
{ pCxt->pRootNode = createCreateTopicStmtUseQuery(pCxt, yymsp[-3].minor.yy983, &yymsp[-2].minor.yy965, yymsp[0].minor.yy560); }
#line 6786 "sql.c"
        break;
      case 342: /* cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta DATABASE db_name */
#line 611 "sql.y"
{ pCxt->pRootNode = createCreateTopicStmtUseDb(pCxt, yymsp[-4].minor.yy983, &yymsp[-3].minor.yy965, &yymsp[0].minor.yy965, yymsp[-2].minor.yy424); }
#line 6791 "sql.c"
        break;
      case 343: /* cmd ::= CREATE TOPIC not_exists_opt topic_name with_meta STABLE full_table_name where_clause_opt */
#line 613 "sql.y"
{ pCxt->pRootNode = createCreateTopicStmtUseTable(pCxt, yymsp[-5].minor.yy983, &yymsp[-4].minor.yy965, yymsp[-1].minor.yy560, yymsp[-3].minor.yy424, yymsp[0].minor.yy560); }
#line 6796 "sql.c"
        break;
      case 344: /* cmd ::= DROP TOPIC exists_opt topic_name */
#line 615 "sql.y"
{ pCxt->pRootNode = createDropTopicStmt(pCxt, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 6801 "sql.c"
        break;
      case 345: /* cmd ::= DROP CONSUMER GROUP exists_opt cgroup_name ON topic_name */
#line 616 "sql.y"
{ pCxt->pRootNode = createDropCGroupStmt(pCxt, yymsp[-3].minor.yy983, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965); }
#line 6806 "sql.c"
        break;
      case 346: /* cmd ::= DESC full_table_name */
      case 347: /* cmd ::= DESCRIBE full_table_name */ yytestcase(yyruleno==347);
#line 619 "sql.y"
{ pCxt->pRootNode = createDescribeStmt(pCxt, yymsp[0].minor.yy560); }
#line 6812 "sql.c"
        break;
      case 348: /* cmd ::= RESET QUERY CACHE */
#line 623 "sql.y"
{ pCxt->pRootNode = createResetQueryCacheStmt(pCxt); }
#line 6817 "sql.c"
        break;
      case 349: /* cmd ::= EXPLAIN analyze_opt explain_options query_or_subquery */
      case 350: /* cmd ::= EXPLAIN analyze_opt explain_options insert_query */ yytestcase(yyruleno==350);
#line 626 "sql.y"
{ pCxt->pRootNode = createExplainStmt(pCxt, yymsp[-2].minor.yy983, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 6823 "sql.c"
        break;
      case 353: /* explain_options ::= */
#line 634 "sql.y"
{ yymsp[1].minor.yy560 = createDefaultExplainOptions(pCxt); }
#line 6828 "sql.c"
        break;
      case 354: /* explain_options ::= explain_options VERBOSE NK_BOOL */
#line 635 "sql.y"
{ yylhsminor.yy560 = setExplainVerbose(pCxt, yymsp[-2].minor.yy560, &yymsp[0].minor.yy0); }
#line 6833 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 355: /* explain_options ::= explain_options RATIO NK_FLOAT */
#line 636 "sql.y"
{ yylhsminor.yy560 = setExplainRatio(pCxt, yymsp[-2].minor.yy560, &yymsp[0].minor.yy0); }
#line 6839 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 356: /* cmd ::= CREATE or_replace_opt agg_func_opt FUNCTION not_exists_opt function_name AS NK_STRING OUTPUTTYPE type_name bufsize_opt language_opt */
#line 641 "sql.y"
{ pCxt->pRootNode = createCreateFunctionStmt(pCxt, yymsp[-7].minor.yy983, yymsp[-9].minor.yy983, &yymsp[-6].minor.yy965, &yymsp[-4].minor.yy0, yymsp[-2].minor.yy412, yymsp[-1].minor.yy424, &yymsp[0].minor.yy965, yymsp[-10].minor.yy983); }
#line 6845 "sql.c"
        break;
      case 357: /* cmd ::= DROP FUNCTION exists_opt function_name */
#line 642 "sql.y"
{ pCxt->pRootNode = createDropFunctionStmt(pCxt, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 6850 "sql.c"
        break;
      case 362: /* language_opt ::= */
      case 401: /* on_vgroup_id ::= */ yytestcase(yyruleno==401);
#line 656 "sql.y"
{ yymsp[1].minor.yy965 = nil_token; }
#line 6856 "sql.c"
        break;
      case 363: /* language_opt ::= LANGUAGE NK_STRING */
      case 402: /* on_vgroup_id ::= ON NK_INTEGER */ yytestcase(yyruleno==402);
#line 657 "sql.y"
{ yymsp[-1].minor.yy965 = yymsp[0].minor.yy0; }
#line 6862 "sql.c"
        break;
      case 366: /* cmd ::= CREATE or_replace_opt VIEW full_view_name AS query_or_subquery */
#line 666 "sql.y"
{ pCxt->pRootNode = createCreateViewStmt(pCxt, yymsp[-4].minor.yy983, yymsp[-2].minor.yy560, &yymsp[-1].minor.yy0, yymsp[0].minor.yy560); }
#line 6867 "sql.c"
        break;
      case 367: /* cmd ::= DROP VIEW exists_opt full_view_name */
#line 667 "sql.y"
{ pCxt->pRootNode = createDropViewStmt(pCxt, yymsp[-1].minor.yy983, yymsp[0].minor.yy560); }
#line 6872 "sql.c"
        break;
      case 368: /* full_view_name ::= view_name */
#line 669 "sql.y"
{ yylhsminor.yy560 = createViewNode(pCxt, NULL, &yymsp[0].minor.yy965); }
#line 6877 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 369: /* full_view_name ::= db_name NK_DOT view_name */
#line 670 "sql.y"
{ yylhsminor.yy560 = createViewNode(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965); }
#line 6883 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 370: /* cmd ::= CREATE STREAM not_exists_opt stream_name stream_options INTO full_table_name col_list_opt tag_def_or_ref_opt subtable_opt AS query_or_subquery */
#line 675 "sql.y"
{ pCxt->pRootNode = createCreateStreamStmt(pCxt, yymsp[-9].minor.yy983, &yymsp[-8].minor.yy965, yymsp[-5].minor.yy560, yymsp[-7].minor.yy560, yymsp[-3].minor.yy388, yymsp[-2].minor.yy560, yymsp[0].minor.yy560, yymsp[-4].minor.yy388); }
#line 6889 "sql.c"
        break;
      case 371: /* cmd ::= DROP STREAM exists_opt stream_name */
#line 676 "sql.y"
{ pCxt->pRootNode = createDropStreamStmt(pCxt, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 6894 "sql.c"
        break;
      case 372: /* cmd ::= PAUSE STREAM exists_opt stream_name */
#line 677 "sql.y"
{ pCxt->pRootNode = createPauseStreamStmt(pCxt, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 6899 "sql.c"
        break;
      case 373: /* cmd ::= RESUME STREAM exists_opt ignore_opt stream_name */
#line 678 "sql.y"
{ pCxt->pRootNode = createResumeStreamStmt(pCxt, yymsp[-2].minor.yy983, yymsp[-1].minor.yy983, &yymsp[0].minor.yy965); }
#line 6904 "sql.c"
        break;
      case 380: /* stream_options ::= stream_options TRIGGER AT_ONCE */
      case 381: /* stream_options ::= stream_options TRIGGER WINDOW_CLOSE */ yytestcase(yyruleno==381);
#line 692 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-2].minor.yy560, SOPT_TRIGGER_TYPE_SET, &yymsp[0].minor.yy0, NULL); }
#line 6910 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 382: /* stream_options ::= stream_options TRIGGER MAX_DELAY duration_literal */
#line 694 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-3].minor.yy560, SOPT_TRIGGER_TYPE_SET, &yymsp[-1].minor.yy0, releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 6916 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 383: /* stream_options ::= stream_options WATERMARK duration_literal */
#line 695 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-2].minor.yy560, SOPT_WATERMARK_SET, NULL, releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 6922 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 384: /* stream_options ::= stream_options IGNORE EXPIRED NK_INTEGER */
#line 696 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-3].minor.yy560, SOPT_IGNORE_EXPIRED_SET, &yymsp[0].minor.yy0, NULL); }
#line 6928 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 385: /* stream_options ::= stream_options FILL_HISTORY NK_INTEGER */
#line 697 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-2].minor.yy560, SOPT_FILL_HISTORY_SET, &yymsp[0].minor.yy0, NULL); }
#line 6934 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 386: /* stream_options ::= stream_options DELETE_MARK duration_literal */
#line 698 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-2].minor.yy560, SOPT_DELETE_MARK_SET, NULL, releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 6940 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 387: /* stream_options ::= stream_options IGNORE UPDATE NK_INTEGER */
#line 699 "sql.y"
{ yylhsminor.yy560 = setStreamOptions(pCxt, yymsp[-3].minor.yy560, SOPT_IGNORE_UPDATE_SET, &yymsp[0].minor.yy0, NULL); }
#line 6946 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 389: /* subtable_opt ::= SUBTABLE NK_LP expression NK_RP */
      case 594: /* sliding_opt ::= SLIDING NK_LP interval_sliding_duration_literal NK_RP */ yytestcase(yyruleno==594);
      case 618: /* every_opt ::= EVERY NK_LP duration_literal NK_RP */ yytestcase(yyruleno==618);
#line 702 "sql.y"
{ yymsp[-3].minor.yy560 = releaseRawExprNode(pCxt, yymsp[-1].minor.yy560); }
#line 6954 "sql.c"
        break;
      case 392: /* cmd ::= KILL CONNECTION NK_INTEGER */
#line 710 "sql.y"
{ pCxt->pRootNode = createKillStmt(pCxt, QUERY_NODE_KILL_CONNECTION_STMT, &yymsp[0].minor.yy0); }
#line 6959 "sql.c"
        break;
      case 393: /* cmd ::= KILL QUERY NK_STRING */
#line 711 "sql.y"
{ pCxt->pRootNode = createKillQueryStmt(pCxt, &yymsp[0].minor.yy0); }
#line 6964 "sql.c"
        break;
      case 394: /* cmd ::= KILL TRANSACTION NK_INTEGER */
#line 712 "sql.y"
{ pCxt->pRootNode = createKillStmt(pCxt, QUERY_NODE_KILL_TRANSACTION_STMT, &yymsp[0].minor.yy0); }
#line 6969 "sql.c"
        break;
      case 395: /* cmd ::= KILL COMPACT NK_INTEGER */
#line 713 "sql.y"
{ pCxt->pRootNode = createKillStmt(pCxt, QUERY_NODE_KILL_COMPACT_STMT, &yymsp[0].minor.yy0); }
#line 6974 "sql.c"
        break;
      case 396: /* cmd ::= BALANCE VGROUP */
#line 716 "sql.y"
{ pCxt->pRootNode = createBalanceVgroupStmt(pCxt); }
#line 6979 "sql.c"
        break;
      case 397: /* cmd ::= BALANCE VGROUP LEADER on_vgroup_id */
#line 717 "sql.y"
{ pCxt->pRootNode = createBalanceVgroupLeaderStmt(pCxt, &yymsp[0].minor.yy965); }
#line 6984 "sql.c"
        break;
      case 398: /* cmd ::= MERGE VGROUP NK_INTEGER NK_INTEGER */
#line 718 "sql.y"
{ pCxt->pRootNode = createMergeVgroupStmt(pCxt, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0); }
#line 6989 "sql.c"
        break;
      case 399: /* cmd ::= REDISTRIBUTE VGROUP NK_INTEGER dnode_list */
#line 719 "sql.y"
{ pCxt->pRootNode = createRedistributeVgroupStmt(pCxt, &yymsp[-1].minor.yy0, yymsp[0].minor.yy388); }
#line 6994 "sql.c"
        break;
      case 400: /* cmd ::= SPLIT VGROUP NK_INTEGER */
#line 720 "sql.y"
{ pCxt->pRootNode = createSplitVgroupStmt(pCxt, &yymsp[0].minor.yy0); }
#line 6999 "sql.c"
        break;
      case 403: /* dnode_list ::= DNODE NK_INTEGER */
#line 729 "sql.y"
{ yymsp[-1].minor.yy388 = createNodeList(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &yymsp[0].minor.yy0)); }
#line 7004 "sql.c"
        break;
      case 405: /* cmd ::= DELETE FROM full_table_name where_clause_opt */
#line 736 "sql.y"
{ pCxt->pRootNode = createDeleteStmt(pCxt, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 7009 "sql.c"
        break;
      case 408: /* insert_query ::= INSERT INTO full_table_name NK_LP col_name_list NK_RP query_or_subquery */
#line 745 "sql.y"
{ yymsp[-6].minor.yy560 = createInsertStmt(pCxt, yymsp[-4].minor.yy560, yymsp[-2].minor.yy388, yymsp[0].minor.yy560); }
#line 7014 "sql.c"
        break;
      case 409: /* insert_query ::= INSERT INTO full_table_name query_or_subquery */
#line 746 "sql.y"
{ yymsp[-3].minor.yy560 = createInsertStmt(pCxt, yymsp[-1].minor.yy560, NULL, yymsp[0].minor.yy560); }
#line 7019 "sql.c"
        break;
      case 410: /* literal ::= NK_INTEGER */
#line 749 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_UBIGINT, &yymsp[0].minor.yy0)); }
#line 7024 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 411: /* literal ::= NK_FLOAT */
#line 750 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_DOUBLE, &yymsp[0].minor.yy0)); }
#line 7030 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 412: /* literal ::= NK_STRING */
#line 751 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0)); }
#line 7036 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 413: /* literal ::= NK_BOOL */
#line 752 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_BOOL, &yymsp[0].minor.yy0)); }
#line 7042 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 414: /* literal ::= TIMESTAMP NK_STRING */
#line 753 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_TIMESTAMP, &yymsp[0].minor.yy0)); }
#line 7048 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 415: /* literal ::= duration_literal */
      case 425: /* signed_literal ::= signed */ yytestcase(yyruleno==425);
      case 448: /* expr_or_subquery ::= expression */ yytestcase(yyruleno==448);
      case 449: /* expression ::= literal */ yytestcase(yyruleno==449);
      case 451: /* expression ::= column_reference */ yytestcase(yyruleno==451);
      case 452: /* expression ::= function_expression */ yytestcase(yyruleno==452);
      case 453: /* expression ::= case_when_expression */ yytestcase(yyruleno==453);
      case 486: /* function_expression ::= literal_func */ yytestcase(yyruleno==486);
      case 535: /* boolean_value_expression ::= boolean_primary */ yytestcase(yyruleno==535);
      case 539: /* boolean_primary ::= predicate */ yytestcase(yyruleno==539);
      case 541: /* common_expression ::= expr_or_subquery */ yytestcase(yyruleno==541);
      case 542: /* common_expression ::= boolean_value_expression */ yytestcase(yyruleno==542);
      case 545: /* table_reference_list ::= table_reference */ yytestcase(yyruleno==545);
      case 547: /* table_reference ::= table_primary */ yytestcase(yyruleno==547);
      case 548: /* table_reference ::= joined_table */ yytestcase(yyruleno==548);
      case 552: /* table_primary ::= parenthesized_joined_table */ yytestcase(yyruleno==552);
      case 620: /* query_simple ::= query_specification */ yytestcase(yyruleno==620);
      case 621: /* query_simple ::= union_query_expression */ yytestcase(yyruleno==621);
      case 624: /* query_simple_or_subquery ::= query_simple */ yytestcase(yyruleno==624);
      case 626: /* query_or_subquery ::= query_expression */ yytestcase(yyruleno==626);
#line 754 "sql.y"
{ yylhsminor.yy560 = yymsp[0].minor.yy560; }
#line 7073 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 416: /* literal ::= NULL */
#line 755 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createValueNode(pCxt, TSDB_DATA_TYPE_NULL, &yymsp[0].minor.yy0)); }
#line 7079 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 417: /* literal ::= NK_QUESTION */
#line 756 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createPlaceholderValueNode(pCxt, &yymsp[0].minor.yy0)); }
#line 7085 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 418: /* duration_literal ::= NK_VARIABLE */
      case 595: /* interval_sliding_duration_literal ::= NK_VARIABLE */ yytestcase(yyruleno==595);
      case 596: /* interval_sliding_duration_literal ::= NK_STRING */ yytestcase(yyruleno==596);
      case 597: /* interval_sliding_duration_literal ::= NK_INTEGER */ yytestcase(yyruleno==597);
#line 758 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createDurationValueNode(pCxt, &yymsp[0].minor.yy0)); }
#line 7094 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 419: /* signed ::= NK_INTEGER */
#line 760 "sql.y"
{ yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_UBIGINT, &yymsp[0].minor.yy0); }
#line 7100 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 420: /* signed ::= NK_PLUS NK_INTEGER */
#line 761 "sql.y"
{ yymsp[-1].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_UBIGINT, &yymsp[0].minor.yy0); }
#line 7106 "sql.c"
        break;
      case 421: /* signed ::= NK_MINUS NK_INTEGER */
#line 762 "sql.y"
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_BIGINT, &t);
                                                                                  }
#line 7115 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 422: /* signed ::= NK_FLOAT */
#line 767 "sql.y"
{ yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_DOUBLE, &yymsp[0].minor.yy0); }
#line 7121 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 423: /* signed ::= NK_PLUS NK_FLOAT */
#line 768 "sql.y"
{ yymsp[-1].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_DOUBLE, &yymsp[0].minor.yy0); }
#line 7127 "sql.c"
        break;
      case 424: /* signed ::= NK_MINUS NK_FLOAT */
#line 769 "sql.y"
{
                                                                                    SToken t = yymsp[-1].minor.yy0;
                                                                                    t.n = (yymsp[0].minor.yy0.z + yymsp[0].minor.yy0.n) - yymsp[-1].minor.yy0.z;
                                                                                    yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_DOUBLE, &t);
                                                                                  }
#line 7136 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 426: /* signed_literal ::= NK_STRING */
#line 776 "sql.y"
{ yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0); }
#line 7142 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 427: /* signed_literal ::= NK_BOOL */
#line 777 "sql.y"
{ yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_BOOL, &yymsp[0].minor.yy0); }
#line 7148 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 428: /* signed_literal ::= TIMESTAMP NK_STRING */
#line 778 "sql.y"
{ yymsp[-1].minor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_TIMESTAMP, &yymsp[0].minor.yy0); }
#line 7154 "sql.c"
        break;
      case 429: /* signed_literal ::= duration_literal */
      case 431: /* signed_literal ::= literal_func */ yytestcase(yyruleno==431);
      case 506: /* star_func_para ::= expr_or_subquery */ yytestcase(yyruleno==506);
      case 572: /* select_item ::= common_expression */ yytestcase(yyruleno==572);
      case 582: /* partition_item ::= expr_or_subquery */ yytestcase(yyruleno==582);
      case 625: /* query_simple_or_subquery ::= subquery */ yytestcase(yyruleno==625);
      case 627: /* query_or_subquery ::= subquery */ yytestcase(yyruleno==627);
      case 640: /* search_condition ::= common_expression */ yytestcase(yyruleno==640);
#line 779 "sql.y"
{ yylhsminor.yy560 = releaseRawExprNode(pCxt, yymsp[0].minor.yy560); }
#line 7166 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 430: /* signed_literal ::= NULL */
#line 780 "sql.y"
{ yylhsminor.yy560 = createValueNode(pCxt, TSDB_DATA_TYPE_NULL, &yymsp[0].minor.yy0); }
#line 7172 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 432: /* signed_literal ::= NK_QUESTION */
#line 782 "sql.y"
{ yylhsminor.yy560 = createPlaceholderValueNode(pCxt, &yymsp[0].minor.yy0); }
#line 7178 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 450: /* expression ::= pseudo_column */
#line 844 "sql.y"
{ yylhsminor.yy560 = yymsp[0].minor.yy560; setRawExprNodeIsPseudoColumn(pCxt, yylhsminor.yy560, true); }
#line 7184 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 454: /* expression ::= NK_LP expression NK_RP */
      case 540: /* boolean_primary ::= NK_LP boolean_value_expression NK_RP */ yytestcase(yyruleno==540);
      case 639: /* subquery ::= NK_LP subquery NK_RP */ yytestcase(yyruleno==639);
#line 848 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, releaseRawExprNode(pCxt, yymsp[-1].minor.yy560)); }
#line 7192 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 455: /* expression ::= NK_PLUS expr_or_subquery */
#line 849 "sql.y"
{
                                                                                    SToken t = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-1].minor.yy0, &t, releaseRawExprNode(pCxt, yymsp[0].minor.yy560));
                                                                                  }
#line 7201 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 456: /* expression ::= NK_MINUS expr_or_subquery */
#line 853 "sql.y"
{
                                                                                    SToken t = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-1].minor.yy0, &t, createOperatorNode(pCxt, OP_TYPE_MINUS, releaseRawExprNode(pCxt, yymsp[0].minor.yy560), NULL));
                                                                                  }
#line 7210 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 457: /* expression ::= expr_or_subquery NK_PLUS expr_or_subquery */
#line 857 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_ADD, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7220 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 458: /* expression ::= expr_or_subquery NK_MINUS expr_or_subquery */
#line 862 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_SUB, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7230 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 459: /* expression ::= expr_or_subquery NK_STAR expr_or_subquery */
#line 867 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_MULTI, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7240 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 460: /* expression ::= expr_or_subquery NK_SLASH expr_or_subquery */
#line 872 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_DIV, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7250 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 461: /* expression ::= expr_or_subquery NK_REM expr_or_subquery */
#line 877 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_REM, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7260 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 462: /* expression ::= column_reference NK_ARROW NK_STRING */
#line 882 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &yymsp[0].minor.yy0, createOperatorNode(pCxt, OP_TYPE_JSON_GET_VALUE, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[0].minor.yy0)));
                                                                                  }
#line 7269 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 463: /* expression ::= expr_or_subquery NK_BITAND expr_or_subquery */
#line 886 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_BIT_AND, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7279 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 464: /* expression ::= expr_or_subquery NK_BITOR expr_or_subquery */
#line 891 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, OP_TYPE_BIT_OR, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7289 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 467: /* column_reference ::= column_name */
#line 902 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy965, createColumnNode(pCxt, NULL, &yymsp[0].minor.yy965)); }
#line 7295 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 468: /* column_reference ::= table_name NK_DOT column_name */
#line 903 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965, createColumnNode(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy965)); }
#line 7301 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 469: /* column_reference ::= NK_ALIAS */
#line 904 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createColumnNode(pCxt, NULL, &yymsp[0].minor.yy0)); }
#line 7307 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 470: /* column_reference ::= table_name NK_DOT NK_ALIAS */
#line 905 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0, createColumnNode(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0)); }
#line 7313 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 471: /* pseudo_column ::= ROWTS */
      case 472: /* pseudo_column ::= TBNAME */ yytestcase(yyruleno==472);
      case 474: /* pseudo_column ::= QSTART */ yytestcase(yyruleno==474);
      case 475: /* pseudo_column ::= QEND */ yytestcase(yyruleno==475);
      case 476: /* pseudo_column ::= QDURATION */ yytestcase(yyruleno==476);
      case 477: /* pseudo_column ::= WSTART */ yytestcase(yyruleno==477);
      case 478: /* pseudo_column ::= WEND */ yytestcase(yyruleno==478);
      case 479: /* pseudo_column ::= WDURATION */ yytestcase(yyruleno==479);
      case 480: /* pseudo_column ::= IROWTS */ yytestcase(yyruleno==480);
      case 481: /* pseudo_column ::= ISFILLED */ yytestcase(yyruleno==481);
      case 482: /* pseudo_column ::= QTAGS */ yytestcase(yyruleno==482);
      case 488: /* literal_func ::= NOW */ yytestcase(yyruleno==488);
#line 907 "sql.y"
{ yylhsminor.yy560 = createRawExprNode(pCxt, &yymsp[0].minor.yy0, createFunctionNode(pCxt, &yymsp[0].minor.yy0, NULL)); }
#line 7330 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 473: /* pseudo_column ::= table_name NK_DOT TBNAME */
#line 909 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0, createFunctionNode(pCxt, &yymsp[0].minor.yy0, createNodeList(pCxt, createValueNode(pCxt, TSDB_DATA_TYPE_BINARY, &yymsp[-2].minor.yy965)))); }
#line 7336 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 483: /* function_expression ::= function_name NK_LP expression_list NK_RP */
      case 484: /* function_expression ::= star_func NK_LP star_func_para_list NK_RP */ yytestcase(yyruleno==484);
#line 920 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-3].minor.yy965, &yymsp[0].minor.yy0, createFunctionNode(pCxt, &yymsp[-3].minor.yy965, yymsp[-1].minor.yy388)); }
#line 7343 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 485: /* function_expression ::= CAST NK_LP expr_or_subquery AS type_name NK_RP */
#line 923 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-5].minor.yy0, &yymsp[0].minor.yy0, createCastFunctionNode(pCxt, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), yymsp[-1].minor.yy412)); }
#line 7349 "sql.c"
  yymsp[-5].minor.yy560 = yylhsminor.yy560;
        break;
      case 487: /* literal_func ::= noarg_func NK_LP NK_RP */
#line 926 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0, createFunctionNode(pCxt, &yymsp[-2].minor.yy965, NULL)); }
#line 7355 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 502: /* star_func_para_list ::= NK_STAR */
#line 950 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, createColumnNode(pCxt, NULL, &yymsp[0].minor.yy0)); }
#line 7361 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 507: /* star_func_para ::= table_name NK_DOT NK_STAR */
      case 575: /* select_item ::= table_name NK_DOT NK_STAR */ yytestcase(yyruleno==575);
#line 959 "sql.y"
{ yylhsminor.yy560 = createColumnNode(pCxt, &yymsp[-2].minor.yy965, &yymsp[0].minor.yy0); }
#line 7368 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 508: /* case_when_expression ::= CASE when_then_list case_when_else_opt END */
#line 962 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, createCaseWhenNode(pCxt, NULL, yymsp[-2].minor.yy388, yymsp[-1].minor.yy560)); }
#line 7374 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 509: /* case_when_expression ::= CASE common_expression when_then_list case_when_else_opt END */
#line 964 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0, createCaseWhenNode(pCxt, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), yymsp[-2].minor.yy388, yymsp[-1].minor.yy560)); }
#line 7380 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 512: /* when_then_expr ::= WHEN common_expression THEN common_expression */
#line 971 "sql.y"
{ yymsp[-3].minor.yy560 = createWhenThenNode(pCxt, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)); }
#line 7386 "sql.c"
        break;
      case 514: /* case_when_else_opt ::= ELSE common_expression */
#line 974 "sql.y"
{ yymsp[-1].minor.yy560 = releaseRawExprNode(pCxt, yymsp[0].minor.yy560); }
#line 7391 "sql.c"
        break;
      case 515: /* predicate ::= expr_or_subquery compare_op expr_or_subquery */
      case 520: /* predicate ::= expr_or_subquery in_op in_predicate_value */ yytestcase(yyruleno==520);
#line 977 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createOperatorNode(pCxt, yymsp[-1].minor.yy668, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7401 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 516: /* predicate ::= expr_or_subquery BETWEEN expr_or_subquery AND expr_or_subquery */
#line 984 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-4].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createBetweenAnd(pCxt, releaseRawExprNode(pCxt, yymsp[-4].minor.yy560), releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7411 "sql.c"
  yymsp[-4].minor.yy560 = yylhsminor.yy560;
        break;
      case 517: /* predicate ::= expr_or_subquery NOT BETWEEN expr_or_subquery AND expr_or_subquery */
#line 990 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-5].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createNotBetweenAnd(pCxt, releaseRawExprNode(pCxt, yymsp[-5].minor.yy560), releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7421 "sql.c"
  yymsp[-5].minor.yy560 = yylhsminor.yy560;
        break;
      case 518: /* predicate ::= expr_or_subquery IS NULL */
#line 995 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &yymsp[0].minor.yy0, createOperatorNode(pCxt, OP_TYPE_IS_NULL, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), NULL));
                                                                                  }
#line 7430 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 519: /* predicate ::= expr_or_subquery IS NOT NULL */
#line 999 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-3].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &yymsp[0].minor.yy0, createOperatorNode(pCxt, OP_TYPE_IS_NOT_NULL, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), NULL));
                                                                                  }
#line 7439 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 521: /* compare_op ::= NK_LT */
#line 1011 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_LOWER_THAN; }
#line 7445 "sql.c"
        break;
      case 522: /* compare_op ::= NK_GT */
#line 1012 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_GREATER_THAN; }
#line 7450 "sql.c"
        break;
      case 523: /* compare_op ::= NK_LE */
#line 1013 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_LOWER_EQUAL; }
#line 7455 "sql.c"
        break;
      case 524: /* compare_op ::= NK_GE */
#line 1014 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_GREATER_EQUAL; }
#line 7460 "sql.c"
        break;
      case 525: /* compare_op ::= NK_NE */
#line 1015 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_NOT_EQUAL; }
#line 7465 "sql.c"
        break;
      case 526: /* compare_op ::= NK_EQ */
#line 1016 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_EQUAL; }
#line 7470 "sql.c"
        break;
      case 527: /* compare_op ::= LIKE */
#line 1017 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_LIKE; }
#line 7475 "sql.c"
        break;
      case 528: /* compare_op ::= NOT LIKE */
#line 1018 "sql.y"
{ yymsp[-1].minor.yy668 = OP_TYPE_NOT_LIKE; }
#line 7480 "sql.c"
        break;
      case 529: /* compare_op ::= MATCH */
#line 1019 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_MATCH; }
#line 7485 "sql.c"
        break;
      case 530: /* compare_op ::= NMATCH */
#line 1020 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_NMATCH; }
#line 7490 "sql.c"
        break;
      case 531: /* compare_op ::= CONTAINS */
#line 1021 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_JSON_CONTAINS; }
#line 7495 "sql.c"
        break;
      case 532: /* in_op ::= IN */
#line 1025 "sql.y"
{ yymsp[0].minor.yy668 = OP_TYPE_IN; }
#line 7500 "sql.c"
        break;
      case 533: /* in_op ::= NOT IN */
#line 1026 "sql.y"
{ yymsp[-1].minor.yy668 = OP_TYPE_NOT_IN; }
#line 7505 "sql.c"
        break;
      case 534: /* in_predicate_value ::= NK_LP literal_list NK_RP */
#line 1028 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, createNodeListNode(pCxt, yymsp[-1].minor.yy388)); }
#line 7510 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 536: /* boolean_value_expression ::= NOT boolean_primary */
#line 1032 "sql.y"
{
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-1].minor.yy0, &e, createLogicConditionNode(pCxt, LOGIC_COND_TYPE_NOT, releaseRawExprNode(pCxt, yymsp[0].minor.yy560), NULL));
                                                                                  }
#line 7519 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 537: /* boolean_value_expression ::= boolean_value_expression OR boolean_value_expression */
#line 1037 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createLogicConditionNode(pCxt, LOGIC_COND_TYPE_OR, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7529 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 538: /* boolean_value_expression ::= boolean_value_expression AND boolean_value_expression */
#line 1043 "sql.y"
{
                                                                                    SToken s = getTokenFromRawExprNode(pCxt, yymsp[-2].minor.yy560);
                                                                                    SToken e = getTokenFromRawExprNode(pCxt, yymsp[0].minor.yy560);
                                                                                    yylhsminor.yy560 = createRawExprNodeExt(pCxt, &s, &e, createLogicConditionNode(pCxt, LOGIC_COND_TYPE_AND, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), releaseRawExprNode(pCxt, yymsp[0].minor.yy560)));
                                                                                  }
#line 7539 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 546: /* table_reference_list ::= table_reference_list NK_COMMA table_reference */
#line 1061 "sql.y"
{ yylhsminor.yy560 = createJoinTableNode(pCxt, JOIN_TYPE_INNER, yymsp[-2].minor.yy560, yymsp[0].minor.yy560, NULL); }
#line 7545 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 549: /* table_primary ::= table_name alias_opt */
#line 1067 "sql.y"
{ yylhsminor.yy560 = createRealTableNode(pCxt, NULL, &yymsp[-1].minor.yy965, &yymsp[0].minor.yy965); }
#line 7551 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 550: /* table_primary ::= db_name NK_DOT table_name alias_opt */
#line 1068 "sql.y"
{ yylhsminor.yy560 = createRealTableNode(pCxt, &yymsp[-3].minor.yy965, &yymsp[-1].minor.yy965, &yymsp[0].minor.yy965); }
#line 7557 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 551: /* table_primary ::= subquery alias_opt */
#line 1069 "sql.y"
{ yylhsminor.yy560 = createTempTableNode(pCxt, releaseRawExprNode(pCxt, yymsp[-1].minor.yy560), &yymsp[0].minor.yy965); }
#line 7563 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 553: /* alias_opt ::= */
#line 1074 "sql.y"
{ yymsp[1].minor.yy965 = nil_token;  }
#line 7569 "sql.c"
        break;
      case 555: /* alias_opt ::= AS table_alias */
#line 1076 "sql.y"
{ yymsp[-1].minor.yy965 = yymsp[0].minor.yy965; }
#line 7574 "sql.c"
        break;
      case 556: /* parenthesized_joined_table ::= NK_LP joined_table NK_RP */
      case 557: /* parenthesized_joined_table ::= NK_LP parenthesized_joined_table NK_RP */ yytestcase(yyruleno==557);
#line 1078 "sql.y"
{ yymsp[-2].minor.yy560 = yymsp[-1].minor.yy560; }
#line 7580 "sql.c"
        break;
      case 558: /* joined_table ::= table_reference join_type JOIN table_reference ON search_condition */
#line 1083 "sql.y"
{ yylhsminor.yy560 = createJoinTableNode(pCxt, yymsp[-4].minor.yy684, yymsp[-5].minor.yy560, yymsp[-2].minor.yy560, yymsp[0].minor.yy560); }
#line 7585 "sql.c"
  yymsp[-5].minor.yy560 = yylhsminor.yy560;
        break;
      case 559: /* join_type ::= */
#line 1087 "sql.y"
{ yymsp[1].minor.yy684 = JOIN_TYPE_INNER; }
#line 7591 "sql.c"
        break;
      case 560: /* join_type ::= INNER */
#line 1088 "sql.y"
{ yymsp[0].minor.yy684 = JOIN_TYPE_INNER; }
#line 7596 "sql.c"
        break;
      case 561: /* query_specification ::= SELECT hint_list set_quantifier_opt tag_mode_opt select_list from_clause_opt where_clause_opt partition_by_clause_opt range_opt every_opt fill_opt twindow_clause_opt group_by_clause_opt having_clause_opt */
#line 1094 "sql.y"
{
                                                                                    yymsp[-13].minor.yy560 = createSelectStmt(pCxt, yymsp[-11].minor.yy983, yymsp[-9].minor.yy388, yymsp[-8].minor.yy560, yymsp[-12].minor.yy388);
                                                                                    yymsp[-13].minor.yy560 = setSelectStmtTagMode(pCxt, yymsp[-13].minor.yy560, yymsp[-10].minor.yy983);
                                                                                    yymsp[-13].minor.yy560 = addWhereClause(pCxt, yymsp[-13].minor.yy560, yymsp[-7].minor.yy560);
                                                                                    yymsp[-13].minor.yy560 = addPartitionByClause(pCxt, yymsp[-13].minor.yy560, yymsp[-6].minor.yy388);
                                                                                    yymsp[-13].minor.yy560 = addWindowClauseClause(pCxt, yymsp[-13].minor.yy560, yymsp[-2].minor.yy560);
                                                                                    yymsp[-13].minor.yy560 = addGroupByClause(pCxt, yymsp[-13].minor.yy560, yymsp[-1].minor.yy388);
                                                                                    yymsp[-13].minor.yy560 = addHavingClause(pCxt, yymsp[-13].minor.yy560, yymsp[0].minor.yy560);
                                                                                    yymsp[-13].minor.yy560 = addRangeClause(pCxt, yymsp[-13].minor.yy560, yymsp[-5].minor.yy560);
                                                                                    yymsp[-13].minor.yy560 = addEveryClause(pCxt, yymsp[-13].minor.yy560, yymsp[-4].minor.yy560);
                                                                                    yymsp[-13].minor.yy560 = addFillClause(pCxt, yymsp[-13].minor.yy560, yymsp[-3].minor.yy560);
                                                                                  }
#line 7612 "sql.c"
        break;
      case 562: /* hint_list ::= */
#line 1109 "sql.y"
{ yymsp[1].minor.yy388 = createHintNodeList(pCxt, NULL); }
#line 7617 "sql.c"
        break;
      case 563: /* hint_list ::= NK_HINT */
#line 1110 "sql.y"
{ yylhsminor.yy388 = createHintNodeList(pCxt, &yymsp[0].minor.yy0); }
#line 7622 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 568: /* set_quantifier_opt ::= ALL */
#line 1121 "sql.y"
{ yymsp[0].minor.yy983 = false; }
#line 7628 "sql.c"
        break;
      case 571: /* select_item ::= NK_STAR */
#line 1128 "sql.y"
{ yylhsminor.yy560 = createColumnNode(pCxt, NULL, &yymsp[0].minor.yy0); }
#line 7633 "sql.c"
  yymsp[0].minor.yy560 = yylhsminor.yy560;
        break;
      case 573: /* select_item ::= common_expression column_alias */
      case 583: /* partition_item ::= expr_or_subquery column_alias */ yytestcase(yyruleno==583);
#line 1130 "sql.y"
{ yylhsminor.yy560 = setProjectionAlias(pCxt, releaseRawExprNode(pCxt, yymsp[-1].minor.yy560), &yymsp[0].minor.yy965); }
#line 7640 "sql.c"
  yymsp[-1].minor.yy560 = yylhsminor.yy560;
        break;
      case 574: /* select_item ::= common_expression AS column_alias */
      case 584: /* partition_item ::= expr_or_subquery AS column_alias */ yytestcase(yyruleno==584);
#line 1131 "sql.y"
{ yylhsminor.yy560 = setProjectionAlias(pCxt, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), &yymsp[0].minor.yy965); }
#line 7647 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 579: /* partition_by_clause_opt ::= PARTITION BY partition_list */
      case 609: /* group_by_clause_opt ::= GROUP BY group_by_list */ yytestcase(yyruleno==609);
      case 629: /* order_by_clause_opt ::= ORDER BY sort_specification_list */ yytestcase(yyruleno==629);
#line 1140 "sql.y"
{ yymsp[-2].minor.yy388 = yymsp[0].minor.yy388; }
#line 7655 "sql.c"
        break;
      case 586: /* twindow_clause_opt ::= SESSION NK_LP column_reference NK_COMMA interval_sliding_duration_literal NK_RP */
#line 1153 "sql.y"
{ yymsp[-5].minor.yy560 = createSessionWindowNode(pCxt, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), releaseRawExprNode(pCxt, yymsp[-1].minor.yy560)); }
#line 7660 "sql.c"
        break;
      case 587: /* twindow_clause_opt ::= STATE_WINDOW NK_LP expr_or_subquery NK_RP */
#line 1154 "sql.y"
{ yymsp[-3].minor.yy560 = createStateWindowNode(pCxt, releaseRawExprNode(pCxt, yymsp[-1].minor.yy560)); }
#line 7665 "sql.c"
        break;
      case 588: /* twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
#line 1156 "sql.y"
{ yymsp[-5].minor.yy560 = createIntervalWindowNode(pCxt, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), NULL, yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 7670 "sql.c"
        break;
      case 589: /* twindow_clause_opt ::= INTERVAL NK_LP interval_sliding_duration_literal NK_COMMA interval_sliding_duration_literal NK_RP sliding_opt fill_opt */
#line 1160 "sql.y"
{ yymsp[-7].minor.yy560 = createIntervalWindowNode(pCxt, releaseRawExprNode(pCxt, yymsp[-5].minor.yy560), releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), yymsp[-1].minor.yy560, yymsp[0].minor.yy560); }
#line 7675 "sql.c"
        break;
      case 590: /* twindow_clause_opt ::= EVENT_WINDOW START WITH search_condition END WITH search_condition */
#line 1162 "sql.y"
{ yymsp[-6].minor.yy560 = createEventWindowNode(pCxt, yymsp[-3].minor.yy560, yymsp[0].minor.yy560); }
#line 7680 "sql.c"
        break;
      case 591: /* twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_RP */
#line 1164 "sql.y"
{ yymsp[-3].minor.yy560 = createCountWindowNode(pCxt, &yymsp[-1].minor.yy0, &yymsp[-1].minor.yy0); }
#line 7685 "sql.c"
        break;
      case 592: /* twindow_clause_opt ::= COUNT_WINDOW NK_LP NK_INTEGER NK_COMMA NK_INTEGER NK_RP */
#line 1166 "sql.y"
{ yymsp[-5].minor.yy560 = createCountWindowNode(pCxt, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0); }
#line 7690 "sql.c"
        break;
      case 599: /* fill_opt ::= FILL NK_LP fill_mode NK_RP */
#line 1176 "sql.y"
{ yymsp[-3].minor.yy560 = createFillNode(pCxt, yymsp[-1].minor.yy18, NULL); }
#line 7695 "sql.c"
        break;
      case 600: /* fill_opt ::= FILL NK_LP VALUE NK_COMMA expression_list NK_RP */
#line 1177 "sql.y"
{ yymsp[-5].minor.yy560 = createFillNode(pCxt, FILL_MODE_VALUE, createNodeListNode(pCxt, yymsp[-1].minor.yy388)); }
#line 7700 "sql.c"
        break;
      case 601: /* fill_opt ::= FILL NK_LP VALUE_F NK_COMMA expression_list NK_RP */
#line 1178 "sql.y"
{ yymsp[-5].minor.yy560 = createFillNode(pCxt, FILL_MODE_VALUE_F, createNodeListNode(pCxt, yymsp[-1].minor.yy388)); }
#line 7705 "sql.c"
        break;
      case 602: /* fill_mode ::= NONE */
#line 1182 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_NONE; }
#line 7710 "sql.c"
        break;
      case 603: /* fill_mode ::= PREV */
#line 1183 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_PREV; }
#line 7715 "sql.c"
        break;
      case 604: /* fill_mode ::= NULL */
#line 1184 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_NULL; }
#line 7720 "sql.c"
        break;
      case 605: /* fill_mode ::= NULL_F */
#line 1185 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_NULL_F; }
#line 7725 "sql.c"
        break;
      case 606: /* fill_mode ::= LINEAR */
#line 1186 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_LINEAR; }
#line 7730 "sql.c"
        break;
      case 607: /* fill_mode ::= NEXT */
#line 1187 "sql.y"
{ yymsp[0].minor.yy18 = FILL_MODE_NEXT; }
#line 7735 "sql.c"
        break;
      case 610: /* group_by_list ::= expr_or_subquery */
#line 1196 "sql.y"
{ yylhsminor.yy388 = createNodeList(pCxt, createGroupingSetNode(pCxt, releaseRawExprNode(pCxt, yymsp[0].minor.yy560))); }
#line 7740 "sql.c"
  yymsp[0].minor.yy388 = yylhsminor.yy388;
        break;
      case 611: /* group_by_list ::= group_by_list NK_COMMA expr_or_subquery */
#line 1197 "sql.y"
{ yylhsminor.yy388 = addNodeToList(pCxt, yymsp[-2].minor.yy388, createGroupingSetNode(pCxt, releaseRawExprNode(pCxt, yymsp[0].minor.yy560))); }
#line 7746 "sql.c"
  yymsp[-2].minor.yy388 = yylhsminor.yy388;
        break;
      case 615: /* range_opt ::= RANGE NK_LP expr_or_subquery NK_COMMA expr_or_subquery NK_RP */
#line 1204 "sql.y"
{ yymsp[-5].minor.yy560 = createInterpTimeRange(pCxt, releaseRawExprNode(pCxt, yymsp[-3].minor.yy560), releaseRawExprNode(pCxt, yymsp[-1].minor.yy560)); }
#line 7752 "sql.c"
        break;
      case 616: /* range_opt ::= RANGE NK_LP expr_or_subquery NK_RP */
#line 1206 "sql.y"
{ yymsp[-3].minor.yy560 = createInterpTimePoint(pCxt, releaseRawExprNode(pCxt, yymsp[-1].minor.yy560)); }
#line 7757 "sql.c"
        break;
      case 619: /* query_expression ::= query_simple order_by_clause_opt slimit_clause_opt limit_clause_opt */
#line 1213 "sql.y"
{
                                                                                    yylhsminor.yy560 = addOrderByClause(pCxt, yymsp[-3].minor.yy560, yymsp[-2].minor.yy388);
                                                                                    yylhsminor.yy560 = addSlimitClause(pCxt, yylhsminor.yy560, yymsp[-1].minor.yy560);
                                                                                    yylhsminor.yy560 = addLimitClause(pCxt, yylhsminor.yy560, yymsp[0].minor.yy560);
                                                                                  }
#line 7766 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 622: /* union_query_expression ::= query_simple_or_subquery UNION ALL query_simple_or_subquery */
#line 1223 "sql.y"
{ yylhsminor.yy560 = createSetOperator(pCxt, SET_OP_TYPE_UNION_ALL, yymsp[-3].minor.yy560, yymsp[0].minor.yy560); }
#line 7772 "sql.c"
  yymsp[-3].minor.yy560 = yylhsminor.yy560;
        break;
      case 623: /* union_query_expression ::= query_simple_or_subquery UNION query_simple_or_subquery */
#line 1225 "sql.y"
{ yylhsminor.yy560 = createSetOperator(pCxt, SET_OP_TYPE_UNION, yymsp[-2].minor.yy560, yymsp[0].minor.yy560); }
#line 7778 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 631: /* slimit_clause_opt ::= SLIMIT NK_INTEGER */
      case 635: /* limit_clause_opt ::= LIMIT NK_INTEGER */ yytestcase(yyruleno==635);
#line 1239 "sql.y"
{ yymsp[-1].minor.yy560 = createLimitNode(pCxt, &yymsp[0].minor.yy0, NULL); }
#line 7785 "sql.c"
        break;
      case 632: /* slimit_clause_opt ::= SLIMIT NK_INTEGER SOFFSET NK_INTEGER */
      case 636: /* limit_clause_opt ::= LIMIT NK_INTEGER OFFSET NK_INTEGER */ yytestcase(yyruleno==636);
#line 1240 "sql.y"
{ yymsp[-3].minor.yy560 = createLimitNode(pCxt, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0); }
#line 7791 "sql.c"
        break;
      case 633: /* slimit_clause_opt ::= SLIMIT NK_INTEGER NK_COMMA NK_INTEGER */
      case 637: /* limit_clause_opt ::= LIMIT NK_INTEGER NK_COMMA NK_INTEGER */ yytestcase(yyruleno==637);
#line 1241 "sql.y"
{ yymsp[-3].minor.yy560 = createLimitNode(pCxt, &yymsp[0].minor.yy0, &yymsp[-2].minor.yy0); }
#line 7797 "sql.c"
        break;
      case 638: /* subquery ::= NK_LP query_expression NK_RP */
#line 1249 "sql.y"
{ yylhsminor.yy560 = createRawExprNodeExt(pCxt, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, yymsp[-1].minor.yy560); }
#line 7802 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 643: /* sort_specification ::= expr_or_subquery ordering_specification_opt null_ordering_opt */
#line 1263 "sql.y"
{ yylhsminor.yy560 = createOrderByExprNode(pCxt, releaseRawExprNode(pCxt, yymsp[-2].minor.yy560), yymsp[-1].minor.yy164, yymsp[0].minor.yy109); }
#line 7808 "sql.c"
  yymsp[-2].minor.yy560 = yylhsminor.yy560;
        break;
      case 644: /* ordering_specification_opt ::= */
#line 1267 "sql.y"
{ yymsp[1].minor.yy164 = ORDER_ASC; }
#line 7814 "sql.c"
        break;
      case 645: /* ordering_specification_opt ::= ASC */
#line 1268 "sql.y"
{ yymsp[0].minor.yy164 = ORDER_ASC; }
#line 7819 "sql.c"
        break;
      case 646: /* ordering_specification_opt ::= DESC */
#line 1269 "sql.y"
{ yymsp[0].minor.yy164 = ORDER_DESC; }
#line 7824 "sql.c"
        break;
      case 647: /* null_ordering_opt ::= */
#line 1273 "sql.y"
{ yymsp[1].minor.yy109 = NULL_ORDER_DEFAULT; }
#line 7829 "sql.c"
        break;
      case 648: /* null_ordering_opt ::= NULLS FIRST */
#line 1274 "sql.y"
{ yymsp[-1].minor.yy109 = NULL_ORDER_FIRST; }
#line 7834 "sql.c"
        break;
      case 649: /* null_ordering_opt ::= NULLS LAST */
#line 1275 "sql.y"
{ yymsp[-1].minor.yy109 = NULL_ORDER_LAST; }
#line 7839 "sql.c"
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
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
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
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
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
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
  ParseARG_FETCH
  ParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/

  if (TSDB_CODE_SUCCESS == pCxt->errCode) {
    if(TOKEN.z) {
      pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_SYNTAX_ERROR, TOKEN.z);
    } else {
      pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_INCOMPLETE_SQL);
    }
  } else if (TSDB_CODE_PAR_DB_NOT_SPECIFIED == pCxt->errCode && TK_NK_FLOAT == TOKEN.type) {
    pCxt->errCode = generateSyntaxErrMsg(&pCxt->msgBuf, TSDB_CODE_PAR_SYNTAX_ERROR, TOKEN.z);
  }
#line 7912 "sql.c"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
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
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
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
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ParseCTX_FETCH
  ParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
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
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
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
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
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
      break;
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
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
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

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ParseFallback(int iToken){
#ifdef YYFALLBACK
  assert( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) );
  return yyFallback[iToken];
#else
  (void)iToken;
  return 0;
#endif
}
