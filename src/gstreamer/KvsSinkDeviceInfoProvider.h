#ifndef __KVS_SINK_DEVICE_INFO_PROVIDER_H__
#define __KVS_SINK_DEVICE_INFO_PROVIDER_H__

#include <DefaultDeviceInfoProvider.h>

namespace com { namespace amazonaws { namespace kinesis { namespace video {
    class KvsSinkDeviceInfoProvider: public DefaultDeviceInfoProvider {// here we need to define the retry strategy instead of the default infinite backoff strategy
        uint64_t storage_size_mb_;
        uint64_t stop_stream_timeout_sec_;
    public:
        KvsSinkDeviceInfoProvider(uint64_t storage_size_mb, uint64_t stop_stream_timeout_sec):
                storage_size_mb_(storage_size_mb),
                stop_stream_timeout_sec_(stop_stream_timeout_sec) {}
        device_info_t getDeviceInfo() override;
    };
}
}
}
}

#endif //__KVS_SINK_DEVICE_INFO_PROVIDER_H__
