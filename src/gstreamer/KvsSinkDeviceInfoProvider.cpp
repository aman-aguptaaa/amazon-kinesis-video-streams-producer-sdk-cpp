#include "KvsSinkDeviceInfoProvider.h"

using namespace com::amazonaws::kinesis::video;

KvsSinkDeviceInfoProvider::device_info_t KvsSinkDeviceInfoProvider::getDeviceInfo(){
    auto device_info = DefaultDeviceInfoProvider::getDeviceInfo();
    // Set the storage size to user specified size in MB
    device_info.storageInfo.storageSize = static_cast<UINT64>(storage_size_mb_) * 1024 * 1024;

    device_info.clientInfo.kvsRetryStrategy = {NULL, NULL, KVS_RETRY_STRATEGY_DISABLED};
    device_info.clientInfo.kvsRetryStrategyCallbacks.createRetryStrategyFn = createRetryStrategyFn;
    device_info.clientInfo.kvsRetryStrategyCallbacks.getCurrentRetryAttemptNumberFn = getCurrentRetryAttemptNumberFn;
    device_info.clientInfo.kvsRetryStrategyCallbacks.freeRetryStrategyFn = freeRetryStrategyFn;
    device_info.clientInfo.kvsRetryStrategyCallbacks.executeRetryStrategyFn = executeRetryStrategyFn;

    return device_info;
}


STATUS KvsSinkDeviceInfoProvider::createRetryStrategyFn(PKvsRetryStrategy pKvsRetryStrategy) {
    STATUS retStatus = STATUS_SUCCESS;
    PExponentialBackoffRetryStrategyState pExponentialBackoffRetryStrategyState = NULL;

    CHK_STATUS(exponentialBackoffRetryStrategyCreate(pKvsRetryStrategy));
    CHK(pKvsRetryStrategy->retryStrategyType == KVS_RETRY_STRATEGY_EXPONENTIAL_BACKOFF_WAIT, STATUS_INTERNAL_ERROR);

    pExponentialBackoffRetryStrategyState = TO_EXPONENTIAL_BACKOFF_STATE(pKvsRetryStrategy->pRetryStrategy);

    pExponentialBackoffRetryStrategyState->exponentialBackoffRetryStrategyConfig.retryFactorTime = HUNDREDS_OF_NANOS_IN_A_MILLISECOND * 5;
    pExponentialBackoffRetryStrategyState->exponentialBackoffRetryStrategyConfig.maxRetryWaitTime = HUNDREDS_OF_NANOS_IN_A_MILLISECOND * 75;
    pExponentialBackoffRetryStrategyState->exponentialBackoffRetryStrategyConfig.maxRetryCount = 3;

    CleanUp:
    return retStatus;
}

STATUS KvsSinkDeviceInfoProvider::getCurrentRetryAttemptNumberFn(PKvsRetryStrategy pKvsRetryStrategy, PUINT32 pRetryCount) {
    return getExponentialBackoffRetryCount(pKvsRetryStrategy, pRetryCount);
}

STATUS KvsSinkDeviceInfoProvider::freeRetryStrategyFn(PKvsRetryStrategy pKvsRetryStrategy) {
    return exponentialBackoffRetryStrategyFree(pKvsRetryStrategy);
}

STATUS KvsSinkDeviceInfoProvider::executeRetryStrategyFn(PKvsRetryStrategy pKvsRetryStrategy, PUINT64 retryWaitTime) {
    return getExponentialBackoffRetryStrategyWaitTime(pKvsRetryStrategy, retryWaitTime);
}
