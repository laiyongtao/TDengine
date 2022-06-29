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

#ifndef _TD_SCHEDULER_INT_H_
#define _TD_SCHEDULER_INT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "os.h"
#include "tarray.h"
#include "planner.h"
#include "scheduler.h"
#include "thash.h"
#include "trpc.h"
#include "command.h"

#define SCHEDULE_DEFAULT_MAX_JOB_NUM 1000
#define SCHEDULE_DEFAULT_MAX_TASK_NUM 1000
#define SCHEDULE_DEFAULT_MAX_NODE_TABLE_NUM 200  // unit is TSDB_TABLE_NUM_UNIT

#define SCH_DEFAULT_TASK_TIMEOUT_USEC 10000000
#define SCH_MAX_TASK_TIMEOUT_USEC 60000000

#define SCH_TASK_MAX_EXEC_TIMES 5
#define SCH_MAX_CANDIDATE_EP_NUM TSDB_MAX_REPLICA

enum {
  SCH_READ = 1,
  SCH_WRITE,
};

enum {
  SCH_EXEC_CB = 1,
  SCH_FETCH_CB,
};

typedef enum {
  SCH_OP_NULL = 0,
  SCH_OP_EXEC,
  SCH_OP_FETCH,
} SCH_OP_TYPE;

typedef struct SSchTrans {
  void *pTrans;
  void *pHandle;
} SSchTrans;

typedef struct SSchHbTrans {
  SRWLatch  lock;
  int64_t   taskNum;
  SRpcCtx   rpcCtx;
  SSchTrans trans;
} SSchHbTrans;

typedef struct SSchApiStat {

#ifdef WINDOWS
  size_t avoidCompilationErrors;
#endif

} SSchApiStat;

typedef struct SSchRuntimeStat {

#ifdef WINDOWS
  size_t avoidCompilationErrors;
#endif

} SSchRuntimeStat;

typedef struct SSchJobStat {

#ifdef WINDOWS
  size_t avoidCompilationErrors;
#endif

} SSchJobStat;

typedef struct SSchStat {
  SSchApiStat      api;
  SSchRuntimeStat  runtime;
  SSchJobStat      job;
} SSchStat;

typedef struct SSchResInfo {
  SQueryResult*          queryRes;
  void**                 fetchRes;
  schedulerExecCallback  execFp; 
  schedulerFetchCallback fetchFp; 
  void*                  userParam;
} SSchResInfo;

typedef struct SSchedulerMgmt {
  uint64_t        taskId; // sequential taksId
  uint64_t        sId;    // schedulerId
  SSchedulerCfg   cfg;
  bool            exit;
  int32_t         jobRef;
  int32_t         jobNum;
  SSchStat        stat;
  SRWLatch        hbLock;
  SHashObj       *hbConnections;
} SSchedulerMgmt;

typedef struct SSchCallbackParamHeader {
  bool isHbParam;
} SSchCallbackParamHeader;

typedef struct SSchTaskCallbackParam {
  SSchCallbackParamHeader head;
  uint64_t                queryId;
  int64_t                 refId;
  uint64_t                taskId;
  int32_t                 execIdx;
  void                   *pTrans;
} SSchTaskCallbackParam;

typedef struct SSchHbCallbackParam {
  SSchCallbackParamHeader head;
  SQueryNodeEpId          nodeEpId;
  void                   *pTrans;
} SSchHbCallbackParam;

typedef struct SSchFlowControl {
  SRWLatch  lock;
  bool      sorted;
  int32_t   tableNumSum;
  uint32_t  execTaskNum;
  SArray   *taskList;      // Element is SSchTask*
} SSchFlowControl;

typedef struct SSchNodeInfo {
  SQueryNodeAddr addr;
  void          *handle;
} SSchNodeInfo;

typedef struct SSchLevel {
  int32_t         level;
  int8_t          status;
  SRWLatch        lock;
  int32_t         taskFailed;
  int32_t         taskSucceed;
  int32_t         taskNum;
  int32_t         taskLaunchedNum;
  int32_t         taskDoneNum;
  SArray         *subTasks;      // Element is SQueryTask
} SSchLevel;

typedef struct SSchTaskProfile {
  int64_t startTs;
  int64_t execUseTime[SCH_TASK_MAX_EXEC_TIMES];
  int64_t waitTime;
  int64_t endTs;
} SSchTaskProfile;

typedef struct SSchTask {
  uint64_t             taskId;         // task id
  SRWLatch             lock;           // task lock
  int32_t              maxExecTimes;   // task may exec times
  int32_t              execIdx;        // task current execute try index
  SSchLevel           *level;          // level
  SRWLatch             planLock;       // task update plan lock
  SSubplan            *plan;           // subplan
  char                *msg;            // operator tree
  int32_t              msgLen;         // msg length
  int8_t               status;         // task status
  int32_t              lastMsgType;    // last sent msg type
  int64_t              timeoutUsec;    // taks timeout useconds before reschedule
  SQueryNodeAddr       succeedAddr;    // task executed success node address
  int8_t               candidateIdx;   // current try condidation index
  SArray              *candidateAddrs; // condidate node addresses, element is SQueryNodeAddr
  SHashObj            *execNodes;      // all tried node for current task, element is SSchNodeInfo
  SSchTaskProfile      profile;        // task execution profile
  int32_t              childReady;     // child task ready number
  SArray              *children;       // the datasource tasks,from which to fetch the result, element is SQueryTask*
  SArray              *parents;        // the data destination tasks, get data from current task, element is SQueryTask*
  void*                handle;         // task send handle 
  bool                 registerdHb;    // registered in hb
} SSchTask;

typedef struct SSchJobAttr {
  EExplainMode explainMode;
  bool         queryJob;
  bool         needFlowCtrl;
} SSchJobAttr;

typedef struct {
  int32_t     op;
  bool        sync;
} SSchOpStatus;

typedef struct SSchJob {
  int64_t          refId;
  uint64_t         queryId;
  SSchJobAttr      attr;
  int32_t          levelNum;
  int32_t          taskNum;
  SRequestConnInfo conn;
  SArray          *nodeList;   // qnode/vnode list, SArray<SQueryNodeLoad>
  SArray          *levels;    // starting from 0. SArray<SSchLevel>
  SQueryPlan      *pDag;  

  SArray          *dataSrcTasks; // SArray<SQueryTask*>
  int32_t          levelIdx;
  SEpSet           dataSrcEps;
  SHashObj        *taskList;
  SHashObj        *execTasks; // executing and executed tasks, key:taskid, value:SQueryTask*
  SHashObj        *flowCtrl;  // key is ep, element is SSchFlowControl

  SExplainCtx     *explainCtx;
  int8_t           status;  
  SQueryNodeAddr   resNode;
  tsem_t           rspSem;
  SSchOpStatus     opStatus;
  bool            *reqKilled;
  SSchTask        *fetchTask;
  int32_t          errCode;
  SRWLatch         resLock;
  SQueryExecRes    execRes;
  void            *resData;         //TODO free it or not
  int32_t          resNumOfRows;
  SSchResInfo      userRes;
  const char      *sql;
  SQueryProfileSummary summary;
} SSchJob;

extern SSchedulerMgmt schMgmt;

#define SCH_LOG_TASK_START_TS(_task)                          \
  do {                                                        \
    int64_t us = taosGetTimestampUs();                        \
    int32_t idx = (_task)->execIdx % SCH_TASK_MAX_EXEC_TIMES; \
    (_task)->profile.execUseTime[idx] = us;                    \
    if (0 == (_task)->execIdx) {                              \
      (_task)->profile.startTs = us;                          \
    }                                                         \
  } while (0)  

#define SCH_LOG_TASK_WAIT_TS(_task)                        \
  do {                                                    \
    int64_t us = taosGetTimestampUs();                    \
    int32_t idx = (_task)->execIdx % SCH_TASK_MAX_EXEC_TIMES; \
    (_task)->profile.waitTime += us - (_task)->profile.execUseTime[idx];    \
  } while (0)  


#define SCH_LOG_TASK_END_TS(_task)                        \
  do {                                                    \
    int64_t us = taosGetTimestampUs();                    \
    int32_t idx = (_task)->execIdx % SCH_TASK_MAX_EXEC_TIMES; \
    (_task)->profile.execUseTime[idx] = us - (_task)->profile.execUseTime[idx];    \
    (_task)->profile.endTs = us;                          \
  } while (0)  

#define SCH_TASK_TIMEOUT(_task) ((taosGetTimestampUs() - (_task)->profile.execUseTime[(_task)->execIdx % SCH_TASK_MAX_EXEC_TIMES]) > (_task)->timeoutUsec)

#define SCH_TASK_READY_FOR_LAUNCH(readyNum, task) ((readyNum) >= taosArrayGetSize((task)->children))

#define SCH_LOCK_TASK(_task) SCH_LOCK(SCH_WRITE, &(_task)->lock)
#define SCH_UNLOCK_TASK(_task) SCH_UNLOCK(SCH_WRITE, &(_task)->lock)

#define SCH_TASK_ID(_task) ((_task) ? (_task)->taskId : -1)
#define SCH_SET_TASK_LASTMSG_TYPE(_task, _type) do { if(_task) { atomic_store_32(&(_task)->lastMsgType, _type); } } while (0)
#define SCH_GET_TASK_LASTMSG_TYPE(_task) ((_task) ? atomic_load_32(&(_task)->lastMsgType) : -1)

#define SCH_IS_DATA_SRC_QRY_TASK(task) ((task)->plan->subplanType == SUBPLAN_TYPE_SCAN)
#define SCH_IS_DATA_SRC_TASK(task) (((task)->plan->subplanType == SUBPLAN_TYPE_SCAN) || ((task)->plan->subplanType == SUBPLAN_TYPE_MODIFY))
#define SCH_IS_LEAF_TASK(_job, _task) (((_task)->level->level + 1) == (_job)->levelNum)

#define SCH_SET_TASK_STATUS(task, st) atomic_store_8(&(task)->status, st)
#define SCH_GET_TASK_STATUS(task) atomic_load_8(&(task)->status)
#define SCH_GET_TASK_STATUS_STR(task) jobTaskStatusStr(SCH_GET_TASK_STATUS(task))

#define SCH_GET_TASK_HANDLE(_task) ((_task) ? (_task)->handle : NULL)
#define SCH_SET_TASK_HANDLE(_task, _handle) ((_task)->handle = (_handle))

#define SCH_SET_JOB_STATUS(job, st) atomic_store_8(&(job)->status, st)
#define SCH_GET_JOB_STATUS(job) atomic_load_8(&(job)->status)
#define SCH_GET_JOB_STATUS_STR(job) jobTaskStatusStr(SCH_GET_JOB_STATUS(job))

#define SCH_JOB_IN_SYNC_OP(job) ((job)->opStatus.op && (job)->opStatus.sync)
#define SCH_JOB_IN_ASYNC_EXEC_OP(job) (((job)->opStatus.op == SCH_OP_EXEC) && (!(job)->opStatus.sync))
#define SCH_JOB_IN_ASYNC_FETCH_OP(job) (((job)->opStatus.op == SCH_OP_FETCH) && (!(job)->opStatus.sync))

#define SCH_SET_JOB_NEED_FLOW_CTRL(_job) (_job)->attr.needFlowCtrl = true
#define SCH_JOB_NEED_FLOW_CTRL(_job) ((_job)->attr.needFlowCtrl)
#define SCH_TASK_NEED_FLOW_CTRL(_job, _task) (SCH_IS_DATA_SRC_QRY_TASK(_task) && SCH_JOB_NEED_FLOW_CTRL(_job) && SCH_IS_LEVEL_UNFINISHED((_task)->level))

#define SCH_SET_JOB_TYPE(_job, type) (_job)->attr.queryJob = ((type) != SUBPLAN_TYPE_MODIFY)
#define SCH_IS_QUERY_JOB(_job) ((_job)->attr.queryJob) 
#define SCH_JOB_NEED_FETCH(_job) SCH_IS_QUERY_JOB(_job)
#define SCH_IS_WAIT_ALL_JOB(_job) (!SCH_IS_QUERY_JOB(_job))
#define SCH_IS_NEED_DROP_JOB(_job) (SCH_IS_QUERY_JOB(_job))
#define SCH_IS_EXPLAIN_JOB(_job) (EXPLAIN_MODE_ANALYZE == (_job)->attr.explainMode)
#define SCH_NETWORK_ERR(_code) ((_code) == TSDB_CODE_RPC_BROKEN_LINK || (_code) == TSDB_CODE_RPC_NETWORK_UNAVAIL)
#define SCH_SUB_TASK_NETWORK_ERR(_code, _len) (((_code) == TSDB_CODE_RPC_NETWORK_UNAVAIL || (_code) == TSDB_CODE_RPC_BROKEN_LINK) && ((_len) > 0))

#define SCH_IS_LEVEL_UNFINISHED(_level) ((_level)->taskLaunchedNum < (_level)->taskNum)
#define SCH_GET_CUR_EP(_addr) (&(_addr)->epSet.eps[(_addr)->epSet.inUse])
#define SCH_SWITCH_EPSET(_addr) ((_addr)->epSet.inUse = ((_addr)->epSet.inUse + 1) % (_addr)->epSet.numOfEps)
#define SCH_TASK_NUM_OF_EPS(_addr) ((_addr)->epSet.numOfEps)

#define SCH_JOB_ELOG(param, ...) qError("QID:0x%" PRIx64 " " param, pJob->queryId, __VA_ARGS__)
#define SCH_JOB_DLOG(param, ...) qDebug("QID:0x%" PRIx64 " " param, pJob->queryId, __VA_ARGS__)

#define SCH_TASK_ELOG(param, ...) \
  qError("QID:0x%" PRIx64 ",TID:0x%" PRIx64 " " param, pJob->queryId, SCH_TASK_ID(pTask), __VA_ARGS__)
#define SCH_TASK_DLOG(param, ...) \
  qDebug("QID:0x%" PRIx64 ",TID:0x%" PRIx64 " " param, pJob->queryId, SCH_TASK_ID(pTask), __VA_ARGS__)
#define SCH_TASK_DLOGL(param, ...) \
  qDebugL("QID:0x%" PRIx64 ",TID:0x%" PRIx64 " " param, pJob->queryId, SCH_TASK_ID(pTask), __VA_ARGS__)
#define SCH_TASK_WLOG(param, ...) \
  qWarn("QID:0x%" PRIx64 ",TID:0x%" PRIx64 " " param, pJob->queryId, SCH_TASK_ID(pTask), __VA_ARGS__)

#define SCH_ERR_RET(c) do { int32_t _code = c; if (_code != TSDB_CODE_SUCCESS) { terrno = _code; return _code; } } while (0)
#define SCH_RET(c) do { int32_t _code = c; if (_code != TSDB_CODE_SUCCESS) { terrno = _code; } return _code; } while (0)
#define SCH_ERR_JRET(c) do { code = c; if (code != TSDB_CODE_SUCCESS) { terrno = code; goto _return; } } while (0)

#define SCH_LOCK(type, _lock) (SCH_READ == (type) ? taosRLockLatch(_lock) : taosWLockLatch(_lock))
#define SCH_UNLOCK(type, _lock) (SCH_READ == (type) ? taosRUnLockLatch(_lock) : taosWUnLockLatch(_lock))


void    schDeregisterTaskHb(SSchJob *pJob, SSchTask *pTask);
void    schCleanClusterHb(void* pTrans);
int32_t schLaunchTask(SSchJob *job, SSchTask *task);
int32_t schBuildAndSendMsg(SSchJob *job, SSchTask *task, SQueryNodeAddr *addr, int32_t msgType);
SSchJob *schAcquireJob(int64_t refId);
int32_t schReleaseJob(int64_t refId);
void    schFreeFlowCtrl(SSchJob *pJob);
int32_t schChkJobNeedFlowCtrl(SSchJob *pJob, SSchLevel *pLevel);
int32_t schDecTaskFlowQuota(SSchJob *pJob, SSchTask *pTask);
int32_t schCheckIncTaskFlowQuota(SSchJob *pJob, SSchTask *pTask, bool *enough);
int32_t schLaunchTasksInFlowCtrlList(SSchJob *pJob, SSchTask *pTask);
int32_t schLaunchTaskImpl(SSchJob *pJob, SSchTask *pTask);
int32_t schFetchFromRemote(SSchJob *pJob);
int32_t schProcessOnTaskFailure(SSchJob *pJob, SSchTask *pTask, int32_t errCode);
int32_t schBuildAndSendHbMsg(SQueryNodeEpId *nodeEpId, SArray* taskAction);
int32_t schCloneSMsgSendInfo(void *src, void **dst);
int32_t schValidateAndBuildJob(SQueryPlan *pDag, SSchJob *pJob);
void    schFreeJobImpl(void *job);
int32_t schMakeHbRpcCtx(SSchJob *pJob, SSchTask *pTask, SRpcCtx *pCtx);
int32_t schEnsureHbConnection(SSchJob *pJob, SSchTask *pTask);
int32_t schUpdateHbConnection(SQueryNodeEpId *epId, SSchTrans *trans);
int32_t schHandleHbCallback(void *param, SDataBuf *pMsg, int32_t code);
void    schFreeRpcCtx(SRpcCtx *pCtx);
int32_t schGetCallbackFp(int32_t msgType, __async_send_cb_fn_t *fp);
bool    schJobNeedToStop(SSchJob *pJob, int8_t *pStatus);
int32_t schProcessOnTaskSuccess(SSchJob *pJob, SSchTask *pTask);
int32_t schSaveJobQueryRes(SSchJob *pJob, SQueryTableRsp *rsp);
int32_t schProcessOnExplainDone(SSchJob *pJob, SSchTask *pTask, SRetrieveTableRsp *pRsp);
void    schProcessOnDataFetched(SSchJob *job);
int32_t schGetTaskInJob(SSchJob *pJob, uint64_t taskId, SSchTask **pTask);
void    schFreeRpcCtxVal(const void *arg);
int32_t schMakeBrokenLinkVal(SSchJob *pJob, SSchTask *pTask, SRpcBrokenlinkVal *brokenVal, bool isHb);
int32_t schAppendTaskExecNode(SSchJob *pJob, SSchTask *pTask, SQueryNodeAddr *addr, int32_t execIdx);
int32_t schExecStaticExplainJob(SSchedulerReq *pReq, int64_t *job, bool sync);
int32_t schExecJobImpl(SSchedulerReq *pReq, SSchJob *pJob, bool sync);
int32_t schUpdateJobStatus(SSchJob *pJob, int8_t newStatus);
int32_t schCancelJob(SSchJob *pJob);
int32_t schProcessOnJobDropped(SSchJob *pJob, int32_t errCode);
uint64_t schGenTaskId(void);
void    schCloseJobRef(void);
int32_t schExecJob(SSchedulerReq *pReq, int64_t *pJob, SQueryResult *pRes);
int32_t schAsyncExecJob(SSchedulerReq *pReq, int64_t *pJob);
int32_t schFetchRows(SSchJob *pJob);
int32_t schAsyncFetchRows(SSchJob *pJob);
int32_t schUpdateTaskHandle(SSchJob *pJob, SSchTask *pTask, bool dropExecNode, void *handle, int32_t execIdx);
int32_t schProcessOnTaskStatusRsp(SQueryNodeEpId* pEpId, SArray* pStatusList);
void    schFreeSMsgSendInfo(SMsgSendInfo *msgSendInfo);
char*   schGetOpStr(SCH_OP_TYPE type);
int32_t schBeginOperation(SSchJob *pJob, SCH_OP_TYPE type, bool sync);
int32_t schInitJob(SSchedulerReq *pReq, SSchJob **pSchJob);
int32_t schSetJobQueryRes(SSchJob* pJob, SQueryResult* pRes);
int32_t schUpdateTaskCandidateAddr(SSchJob *pJob, SSchTask *pTask, SEpSet* pEpSet);
int32_t schHandleRedirect(SSchJob *pJob, SSchTask *pTask, SDataBuf* pData, int32_t rspCode);


#ifdef __cplusplus
}
#endif

#endif /*_TD_SCHEDULER_INT_H_*/
