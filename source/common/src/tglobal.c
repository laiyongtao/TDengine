/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _DEFAULT_SOURCE
#include "os.h"

#include "taosdef.h"
#include "taoserror.h"
#include "tcompare.h"
#include "tconfig.h"
#include "tep.h"
#include "tglobal.h"
#include "tlog.h"
#include "tutil.h"
#include "ulog.h"

SConfig *tsCfg = NULL;

// cluster
char     tsFirst[TSDB_EP_LEN] = {0};
char     tsSecond[TSDB_EP_LEN] = {0};
char     tsLocalFqdn[TSDB_FQDN_LEN] = {0};
char     tsLocalEp[TSDB_EP_LEN] = {0};  // Local End Point, hostname:port
uint16_t tsServerPort = 6030;
int32_t  tsVersion = 30000000;
int32_t  tsStatusInterval = 1;  // second
bool     tsEnableTelemetryReporting = 0;

// common
int32_t tsRpcTimer = 300;
int32_t tsRpcMaxTime = 600;  // seconds;
bool    tsRpcForceTcp = 1;   // disable this, means query, show command use udp protocol as default
int32_t tsMaxShellConns = 50000;
int32_t tsMaxConnections = 50000;
int32_t tsShellActivityTimer = 3;  // second
float   tsNumOfThreadsPerCore = 1.0f;
int32_t tsNumOfCommitThreads = 4;
float   tsRatioOfQueryCores = 1.0f;
int32_t tsMaxBinaryDisplayWidth = 30;
bool    tsEnableSlaveQuery = 1;
bool    tsPrintAuth = 0;

/*
 * denote if the server needs to compress response message at the application layer to client, including query rsp,
 * metricmeta rsp, and multi-meter query rsp message body. The client compress the submit message to server.
 *
 * 0: all data are compressed
 * -1: all data are not compressed
 * other values: if the message payload size is greater than the tsCompressMsgSize, the message will be compressed.
 */
int32_t tsCompressMsgSize = -1;

/* denote if server needs to compress the retrieved column data before adding to the rpc response message body.
 * 0: all data are compressed
 * -1: all data are not compressed
 * other values: if any retrieved column size is greater than the tsCompressColData, all data will be compressed.
 */
int32_t tsCompressColData = -1;

/*
 * denote if 3.0 query pattern compatible for 2.0
 */
int32_t tsCompatibleModel = 1;

// client
int32_t tsMaxWildCardsLen = TSDB_PATTERN_STRING_DEFAULT_LEN;
int32_t tsMaxRegexStringLen = TSDB_REGEX_STRING_DEFAULT_LEN;

// the maximum number of results for projection query on super table that are returned from
// one virtual node, to order according to timestamp
int32_t tsMaxNumOfOrderedResults = 100000;

// 10 ms for sliding time, the value will changed in case of time precision changed
int32_t tsMinSlidingTime = 10;

// the maxinum number of distict query result
int32_t tsMaxNumOfDistinctResults = 1000 * 10000;

// 1 us for interval time range, changed accordingly
int32_t tsMinIntervalTime = 1;

// 20sec, the maximum value of stream computing delay, changed accordingly
int32_t tsMaxStreamComputDelay = 20000;

// 10sec, the first stream computing delay time after system launched successfully, changed accordingly
int32_t tsStreamCompStartDelay = 10000;

// the stream computing delay time after executing failed, change accordingly
int32_t tsRetryStreamCompDelay = 10 * 1000;

// The delayed computing ration. 10% of the whole computing time window by default.
float tsStreamComputDelayRatio = 0.1f;

int32_t tsProjectExecInterval = 10000;   // every 10sec, the projection will be executed once
int64_t tsMaxRetentWindow = 24 * 3600L;  // maximum time window tolerance

// the maximum allowed query buffer size during query processing for each data node.
// -1 no limit (default)
// 0  no query allowed, queries are disabled
// positive value (in MB)
int32_t tsQueryBufferSize = -1;
int64_t tsQueryBufferSizeBytes = -1;

// in retrieve blocking model, the retrieve threads will wait for the completion of the query processing.
bool tsRetrieveBlockingModel = 0;

// last_row(*), first(*), last_row(ts, col1, col2) query, the result fields will be the original column name
bool tsKeepOriginalColumnName = 0;

// long query death-lock
bool tsDeadLockKillQuery = 0;

// tsdb config
// For backward compatibility
bool tsdbForceKeepFile = false;

int32_t  tsDiskCfgNum = 0;
SDiskCfg tsDiskCfg[TFS_MAX_DISKS] = {0};

/*
 * minimum scale for whole system, millisecond by default
 * for TSDB_TIME_PRECISION_MILLI: 86400000L
 *     TSDB_TIME_PRECISION_MICRO: 86400000000L
 *     TSDB_TIME_PRECISION_NANO:  86400000000000L
 */
int64_t tsTickPerDay[] = {86400000L, 86400000000L, 86400000000000L};

// lossy compress 6
char tsLossyColumns[32] = "";  // "float|double" means all float and double columns can be lossy compressed.  set empty
                               // can close lossy compress.
// below option can take effect when tsLossyColumns not empty
double   tsFPrecision = 1E-8;                   // float column precision
double   tsDPrecision = 1E-16;                  // double column precision
uint32_t tsMaxRange = 500;                      // max range
uint32_t tsCurRange = 100;                      // range
char     tsCompressor[32] = "ZSTD_COMPRESSOR";  // ZSTD_COMPRESSOR or GZIP_COMPRESSOR

static void taosAddDataDir(int32_t index, char *v1, int32_t level, int32_t primary) {
  tstrncpy(tsDiskCfg[index].dir, v1, TSDB_FILENAME_LEN);
  tsDiskCfg[index].level = level;
  tsDiskCfg[index].primary = primary;
  uTrace("dataDir:%s, level:%d primary:%d is configured", v1, level, primary);
}

static void taosReadDataDirCfg(char *v1, char *v2, char *v3) {
  if (tsDiskCfgNum == 1) {
    SDiskCfg *cfg = &tsDiskCfg[0];
    uInfo("dataDir:%s, level:%d primary:%d is replaced by %s", cfg->dir, cfg->level, cfg->primary, v1);
  }
  taosAddDataDir(0, v1, 0, 1);
  tsDiskCfgNum = 1;
}

static void taosPrintDataDirCfg() {
  for (int32_t i = 0; i < tsDiskCfgNum; ++i) {
    SDiskCfg *cfg = &tsDiskCfg[i];
    uInfo(" dataDir: %s", cfg->dir);
  }
}

struct SConfig *taosGetCfg() {
  return tsCfg;
}

static int32_t taosLoadCfg(SConfig *pCfg, const char *inputCfgDir, const char *envFile, const char *apolloUrl) {
  char cfgDir[PATH_MAX] = {0};
  char cfgFile[PATH_MAX + 100] = {0};

  taosExpandDir(inputCfgDir, cfgDir, PATH_MAX);
  snprintf(cfgFile, sizeof(cfgFile), "%s" TD_DIRSEP "taos.cfg", cfgDir);

  if (cfgLoad(pCfg, CFG_STYPE_APOLLO_URL, apolloUrl) != 0) {
    uError("failed to load from apollo url:%s since %s\n", apolloUrl, terrstr());
    return -1;
  }

  if (cfgLoad(pCfg, CFG_STYPE_CFG_FILE, cfgFile) != 0) {
    if (cfgLoad(pCfg, CFG_STYPE_CFG_FILE, cfgDir) != 0) {
      uError("failed to load from config file:%s since %s\n", cfgFile, terrstr());
      return -1;
    }
  }

  if (cfgLoad(pCfg, CFG_STYPE_ENV_FILE, envFile) != 0) {
    uError("failed to load from env file:%s since %s\n", envFile, terrstr());
    return -1;
  }

  if (cfgLoad(pCfg, CFG_STYPE_ENV_VAR, NULL) != 0) {
    uError("failed to load from global env variables since %s\n", terrstr());
    return -1;
  }

  return 0;
}

static void taosAddClientLogCfg(SConfig *pCfg) {
  cfgAddDir(pCfg, "logDir", osLogDir(), 1);
  cfgAddFloat(pCfg, "minimalLogDirGB", 1.0f, 0.001f, 10000000, 1);
  cfgAddInt32(pCfg, "numOfLogLines", tsNumOfLogLines, 1000, 2000000000, 1);
  cfgAddBool(pCfg, "asyncLog", tsAsyncLog, 1);
  cfgAddInt32(pCfg, "logKeepDays", 0, -365000, 365000, 1);
  cfgAddInt32(pCfg, "cDebugFlag", cDebugFlag, 0, 255, 1);
  cfgAddInt32(pCfg, "uDebugFlag", uDebugFlag, 0, 255, 1);
  cfgAddInt32(pCfg, "rpcDebugFlag", rpcDebugFlag, 0, 255, 1);
  cfgAddInt32(pCfg, "tmrDebugFlag", tmrDebugFlag, 0, 255, 1);
  cfgAddInt32(pCfg, "jniDebugFlag", jniDebugFlag, 0, 255, 1);
}

static void taosAddServerLogCfg(SConfig *pCfg) {
  cfgAddInt32(pCfg, "dDebugFlag", dDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "vDebugFlag", vDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "mDebugFlag", mDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "qDebugFlag", qDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "wDebugFlag", wDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "sDebugFlag", sDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "tsdbDebugFlag", tsdbDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "tqDebugFlag", tqDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "fsDebugFlag", fsDebugFlag, 0, 255, 0);
  cfgAddInt32(pCfg, "simDebugFlag", 143, 0, 255, 1);
  cfgAddInt32(pCfg, "debugFlag", 0, 0, 255, 1);
}

static void taosAddClientCfg(SConfig *pCfg) {
  char    defaultFqdn[TSDB_FQDN_LEN] = {0};
  int32_t defaultServerPort = 6030;
  char    defaultFirstEp[TSDB_EP_LEN] = {0};
  char    defaultSecondEp[TSDB_EP_LEN] = {0};
  taosGetFqdn(defaultFqdn);
  snprintf(defaultFirstEp, TSDB_EP_LEN, "%s:%d", defaultFqdn, defaultServerPort);
  snprintf(defaultSecondEp, TSDB_EP_LEN, "%s:%d", defaultFqdn, defaultServerPort);

  cfgAddString(pCfg, "firstEp", defaultFirstEp, 1);
  cfgAddString(pCfg, "secondEp", defaultSecondEp, 1);
  cfgAddString(pCfg, "fqdn", defaultFqdn, 1);
  cfgAddInt32(pCfg, "serverPort", defaultServerPort, 1, 65056, 1);
  cfgAddDir(pCfg, "tempDir", osTempDir(), 1);
  cfgAddString(pCfg, "configDir", configDir, 1);
  cfgAddString(pCfg, "scriptDir", configDir, 1);
  cfgAddFloat(pCfg, "minimalTempDirGB", 1.0f, 0.001f, 10000000, 1);
  cfgAddFloat(pCfg, "numOfThreadsPerCore", tsNumOfThreadsPerCore, 0, 10, 1);
  cfgAddInt32(pCfg, "maxTmrCtrl", tsMaxTmrCtrl, 8, 2048, 1);
  cfgAddInt32(pCfg, "rpcTimer", tsRpcTimer, 100, 3000, 1);
  cfgAddInt32(pCfg, "rpcMaxTime", tsRpcMaxTime, 100, 7200, 1);
  cfgAddBool(pCfg, "rpcForceTcp", tsRpcForceTcp, 1);
  cfgAddInt32(pCfg, "shellActivityTimer", tsShellActivityTimer, 1, 120, 1);
  cfgAddInt32(pCfg, "compressMsgSize", tsCompressMsgSize, -1, 100000000, 1);
  cfgAddInt32(pCfg, "compressColData", tsCompressColData, -1, 100000000, 1);
  cfgAddInt32(pCfg, "maxWildCardsLength", tsMaxWildCardsLen, 0, TSDB_MAX_FIELD_LEN, 1);
  cfgAddInt32(pCfg, "maxRegexStringLen", tsMaxRegexStringLen, 0, TSDB_MAX_FIELD_LEN, 1);
  cfgAddInt32(pCfg, "maxNumOfOrderedRes", tsMaxNumOfOrderedResults, 128, TSDB_MAX_ALLOWED_SQL_LEN, 1);
  cfgAddBool(pCfg, "keepColumnName", tsKeepOriginalColumnName, 1);
  cfgAddInt32(pCfg, "numOfCores", 1, 1, 100000, 1);
  cfgAddBool(pCfg, "enableCoreFile", 0, 1);
  cfgAddInt32(pCfg, "maxBinaryDisplayWidth", tsMaxBinaryDisplayWidth, 1, 65536, 1);
  cfgAddString(pCfg, "version", version, 1);
  cfgAddString(pCfg, "compatible_version", compatible_version, 1);
  cfgAddString(pCfg, "gitinfo", gitinfo, 1);
  cfgAddString(pCfg, "gitinfoOfInternal", gitinfoOfInternal, 1);
  cfgAddString(pCfg, "buildinfo", buildinfo, 1);
  cfgAddTimezone(pCfg, "timezone", osTimezone());
  cfgAddLocale(pCfg, "locale", osLocale());
  cfgAddCharset(pCfg, "charset", osCharset());
}

static void taosAddServerCfg(SConfig *pCfg) {
  cfgAddInt32(pCfg, "supportVnodes", 256, 0, 65536, 0);
  cfgAddDir(pCfg, "dataDir", osDataDir(), 0);
  cfgAddFloat(pCfg, "minimalDataDirGB", 2.0f, 0.001f, 10000000, 0);
  cfgAddInt32(pCfg, "numOfCommitThreads", tsNumOfCommitThreads, 1, 100, 0);
  cfgAddFloat(pCfg, "ratioOfQueryCores", tsRatioOfQueryCores, 0, 2, 0);
  cfgAddInt32(pCfg, "maxNumOfDistinctRes", tsMaxNumOfDistinctResults, 10 * 10000, 10000 * 10000, 0);
  cfgAddBool(pCfg, "telemetryReporting", tsEnableTelemetryReporting, 0);
  cfgAddInt32(pCfg, "maxConnections", tsMaxConnections, 1, 100000, 0);
  cfgAddInt32(pCfg, "maxShellConns", tsMaxShellConns, 10, 50000000, 0);
  cfgAddInt32(pCfg, "statusInterval", tsStatusInterval, 1, 30, 0);
  cfgAddInt32(pCfg, "minSlidingTime", tsMinSlidingTime, 10, 1000000, 0);
  cfgAddInt32(pCfg, "minIntervalTime", tsMinIntervalTime, 1, 1000000, 0);
  cfgAddInt32(pCfg, "maxStreamCompDelay", tsMaxStreamComputDelay, 10, 1000000000, 0);
  cfgAddInt32(pCfg, "maxFirstStreamCompDelay", tsStreamCompStartDelay, 1000, 1000000000, 0);
  cfgAddInt32(pCfg, "retryStreamCompDelay", tsRetryStreamCompDelay, 10, 1000000000, 0);
  cfgAddFloat(pCfg, "streamCompDelayRatio", tsStreamComputDelayRatio, 0.1, 0.9, 0);
  cfgAddInt32(pCfg, "queryBufferSize", tsQueryBufferSize, -1, 500000000000, 0);
  cfgAddBool(pCfg, "retrieveBlockingModel", tsRetrieveBlockingModel, 0);
  cfgAddBool(pCfg, "printAuth", tsPrintAuth, 0);
  cfgAddBool(pCfg, "slaveQuery", tsEnableSlaveQuery, 0);
  cfgAddBool(pCfg, "deadLockKillQuery", tsDeadLockKillQuery, 0);
}

static void taosSetClientLogCfg(SConfig *pCfg) {
  osSetLogDir(cfgGetItem(pCfg, "logDir")->str);
  osSetDataReservedSpace(cfgGetItem(pCfg, "minimalLogDirGB")->fval);
  tsNumOfLogLines = cfgGetItem(pCfg, "numOfLogLines")->i32;
  tsAsyncLog = cfgGetItem(pCfg, "asyncLog")->bval;
  tsLogKeepDays = cfgGetItem(pCfg, "logKeepDays")->i32;
  cDebugFlag = cfgGetItem(pCfg, "cDebugFlag")->i32;
  uDebugFlag = cfgGetItem(pCfg, "uDebugFlag")->i32;
  rpcDebugFlag = cfgGetItem(pCfg, "rpcDebugFlag")->i32;
  tmrDebugFlag = cfgGetItem(pCfg, "tmrDebugFlag")->i32;
  jniDebugFlag = cfgGetItem(pCfg, "jniDebugFlag")->i32;
}

static void taosSetServerLogCfg(SConfig *pCfg) {
  dDebugFlag = cfgGetItem(pCfg, "dDebugFlag")->i32;
  vDebugFlag = cfgGetItem(pCfg, "vDebugFlag")->i32;
  mDebugFlag = cfgGetItem(pCfg, "mDebugFlag")->i32;
  qDebugFlag = cfgGetItem(pCfg, "qDebugFlag")->i32;
  wDebugFlag = cfgGetItem(pCfg, "wDebugFlag")->i32;
  sDebugFlag = cfgGetItem(pCfg, "sDebugFlag")->i32;
  tsdbDebugFlag = cfgGetItem(pCfg, "tsdbDebugFlag")->i32;
  tqDebugFlag = cfgGetItem(pCfg, "tqDebugFlag")->i32;
  fsDebugFlag = cfgGetItem(pCfg, "fsDebugFlag")->i32;
}

static void taosSetClientCfg(SConfig *pCfg) {
  osSetTempDir(cfgGetItem(pCfg, "tempDir")->str);
  osSetDataReservedSpace(cfgGetItem(pCfg, "minimalTempDirGB")->fval);
  tstrncpy(tsFirst, cfgGetItem(pCfg, "firstEp")->str, TSDB_EP_LEN);
  tstrncpy(tsSecond, cfgGetItem(pCfg, "secondEp")->str, TSDB_EP_LEN);
  tstrncpy(tsLocalFqdn, cfgGetItem(pCfg, "fqdn")->str, TSDB_EP_LEN);
  tsServerPort = (uint16_t)cfgGetItem(pCfg, "serverPort")->i32;
  snprintf(tsLocalEp, sizeof(tsLocalEp), "%s:%u", tsLocalFqdn, tsServerPort);

  SConfigItem *pItem = cfgGetItem(pCfg, "timezone");
  osSetTimezone(pItem->str);
  uDebug("timezone format changed from %s to %s", pItem->str, osTimezone());
  cfgSetItem(pCfg, "timezone", osTimezone(), pItem->stype);

  taosGetSystemInfo();
  if (tsNumOfCores <= 1) {
    tsNumOfCores = 2;
  }

  bool enableCore = cfgGetItem(pCfg, "enableCoreFile")->bval;
  taosSetCoreDump(enableCore);

  // todo
  tsVersion = 30000000;
}

static void taosSetServerCfg(SConfig *pCfg) {
  osSetDataDir(cfgGetItem(pCfg, "dataDir")->str);
  osSetTempReservedSpace(cfgGetItem(pCfg, "minimalDataDirGB")->fval);

  tsQueryBufferSize = cfgGetItem(pCfg, "queryBufferSize")->i32;
  if (tsQueryBufferSize >= 0) {
    tsQueryBufferSizeBytes = tsQueryBufferSize * 1048576UL;
  }
}

int32_t taosCreateLog(const char *logname, int32_t logFileNum, const char *cfgDir, const char *envFile,
                      const char *apolloUrl, bool tsc) {
  SConfig *pCfg = cfgInit();
  if (pCfg == NULL) return -1;

  if (tsc) {
    taosAddClientLogCfg(pCfg);
  } else {
    taosAddClientLogCfg(pCfg);
    taosAddServerLogCfg(pCfg);
  }

  if (taosLoadCfg(pCfg, cfgDir, envFile, apolloUrl) != 0) {
    uError("failed to load cfg since %s", terrstr());
    cfgCleanup(pCfg);
    return -1;
  }

  if (tsc) {
    taosSetClientLogCfg(pCfg);
    taosSetAllDebugFlag(cfgGetItem(pCfg, "debugFlag")->i32);
  } else {
    taosSetClientLogCfg(pCfg);
    taosSetServerLogCfg(pCfg);
    taosSetAllDebugFlag(cfgGetItem(pCfg, "debugFlag")->i32);
  }

  if (taosInitLog(logname, logFileNum) != 0) {
    printf("failed to init log file since %s\n", terrstr());
    cfgCleanup(pCfg);
    return -1;
  }

  cfgCleanup(pCfg);
  return 0;
}

int32_t taosInitCfg(const char *cfgDir, const char *envFile, const char *apolloUrl, bool tsc) {
  if (tsCfg != NULL) return 0;
  tsCfg = cfgInit();

  if (tsc) {
    taosAddClientLogCfg(tsCfg);
    taosAddClientCfg(tsCfg);
  } else {
    taosAddClientLogCfg(tsCfg);
    taosAddServerLogCfg(tsCfg);
    taosAddClientCfg(tsCfg);
    taosAddServerCfg(tsCfg);
  }

  if (taosLoadCfg(tsCfg, cfgDir, envFile, apolloUrl) != 0) {
    uError("failed to load cfg since %s", terrstr());
    cfgCleanup(tsCfg);
    tsCfg = NULL;
    return -1;
  }

  if (tsc) {
    taosSetClientCfg(tsCfg);
  } else {
    taosSetClientCfg(tsCfg);
    taosSetServerCfg(tsCfg);
  }

  cfgDumpCfg(tsCfg, tsc, false);
  return 0;
}

void taosCleanupCfg() {
  if (tsCfg) {
    cfgCleanup(tsCfg);
    tsCfg = NULL;
  }
}

void taosCfgDynamicOptions(const char *option, const char *value) {
  if (strcasecmp(option, "debugFlag") == 0) {
    int32_t debugFlag = atoi(value);
    taosSetAllDebugFlag(debugFlag);
  }

  if (strcasecmp(option, "resetlog") == 0) {
    taosResetLog();
    cfgDumpCfg(tsCfg, 1, false);
  }
}