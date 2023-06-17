#ifndef __KVS_SINK_STREAM_CALLBACK_PROVIDER_H__
#define __KVS_SINK_STREAM_CALLBACK_PROVIDER_H__

#include "gstkvssink.h"
#include "Logger.h"

namespace com { namespace amazonaws { namespace kinesis { namespace video {
    class KvsSinkStreamCallbackProvider : public StreamCallbackProvider {
        std::shared_ptr<KvsSinkCustomData> data;
    public:
        KvsSinkStreamCallbackProvider(std::shared_ptr<KvsSinkCustomData> data) : data(data) {}

        UINT64 getCallbackCustomData() override {
            return reinterpret_cast<UINT64> (data.get());
        }

        StreamConnectionStaleFunc getStreamConnectionStaleCallback() override {
            return streamConnectionStaleHandler;
        };

        StreamErrorReportFunc getStreamErrorReportCallback() override {
            return streamErrorReportHandler;
        };

        DroppedFrameReportFunc getDroppedFrameReportCallback() override {
            return droppedFrameReportHandler;
        };

        StreamLatencyPressureFunc getStreamLatencyPressureCallback() override {
            return streamLatencyPressureHandler;
        }

        StreamClosedFunc getStreamClosedCallback() override {
            return streamClosedHandler;
        }

        FragmentAckReceivedFunc getFragmentAckReceivedCallback() override {
            return fragmentAckReceivedHandler;
        }

        DroppedFragmentReportFunc getDroppedFragmentReportCallback() override {
            return droppedFragmentReportHandler;
        }

        StreamDataAvailableFunc getStreamDataAvailableCallback() override {
            return streamDataAvailableHandler;
        }

        StreamReadyFunc getStreamReadyCallback() override {
            return streamReadyHandler;
        }

        StreamUnderflowReportFunc getStreamUnderflowReportCallback() override {
            return streamUnderflowReportHandler;
        }

    private:
        static STATUS
        streamConnectionStaleHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                     UINT64 last_buffering_ack);

        static STATUS
        streamErrorReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle, UPLOAD_HANDLE upload_handle, UINT64 errored_timecode,
                                 STATUS status_code);

        static STATUS
        droppedFrameReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                  UINT64 dropped_frame_timecode);

        static STATUS
        streamLatencyPressureHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                  UINT64 current_buffer_duration);

        static STATUS
        streamClosedHandler(UINT64 custom_data, STREAM_HANDLE stream_handle, UPLOAD_HANDLE upload_handle);

        static STATUS fragmentAckReceivedHandler(UINT64 custom_data,
                                                 STREAM_HANDLE stream_handle,
                                                 UPLOAD_HANDLE upload_handle,
                                                 PFragmentAck fragment_ack);

        static STATUS droppedFragmentReportHandler(UINT64 custom_data,
                                                   STREAM_HANDLE stream_handle,
                                                   UINT64 timecode);

        static STATUS streamDataAvailableHandler(UINT64 custom_data,
                                                 STREAM_HANDLE stream_handle,
                                                 PCHAR stream_name,
                                                 UPLOAD_HANDLE stream_upload_handle,
                                                 UINT64 duration_available,
                                                 UINT64 size_available);

        static STATUS streamReadyHandler(UINT64 custom_data, STREAM_HANDLE stream_handle);

        static STATUS streamUnderflowReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle);
    };
}
}
}
}


#endif //__KVS_SINK_STREAM_CALLBACK_PROVIDER_H__
