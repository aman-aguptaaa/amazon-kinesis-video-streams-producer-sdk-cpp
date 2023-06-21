#ifndef __KVS_SINK_DEVICE_INFO_PROVIDER_H__
#define __KVS_SINK_DEVICE_INFO_PROVIDER_H__

#include <DefaultDeviceInfoProvider.h>

namespace com { namespace amazonaws { namespace kinesis { namespace video {
    class KvsSinkDeviceInfoProvider: public DefaultDeviceInfoProvider {// here we need to define the retry strategy instead of the default infinite backoff strategy
        uint64_t storage_size_mb_;
    public:
        KvsSinkDeviceInfoProvider(uint64_t storage_size_mb): storage_size_mb_(storage_size_mb) {}
        device_info_t getDeviceInfo() override;
        // Test retry strategy callbacks

    protected:
        static STATUS createRetryStrategyFn(PKvsRetryStrategy);
        static STATUS getCurrentRetryAttemptNumberFn(PKvsRetryStrategy, PUINT32);
        static STATUS freeRetryStrategyFn(PKvsRetryStrategy);
        static STATUS executeRetryStrategyFn(PKvsRetryStrategy, PUINT64);
    };
}
}
}
}

#endif //__KVS_SINK_DEVICE_INFO_PROVIDER_H__
