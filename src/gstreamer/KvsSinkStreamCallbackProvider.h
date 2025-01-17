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

                    StreamUnderflowReportFunc getStreamUnderflowReportCallback() override {
                        return streamUnderflowReportHandler;
                    }

                    BufferDurationOverflowPressureFunc getBufferDurationOverflowPressureCallback() override {
                        return bufferDurationOverflowPressureHandler;
                    }

                    StreamLatencyPressureFunc getStreamLatencyPressureCallback() override {
                        return streamLatencyPressureHandler;
                    }

                    StreamConnectionStaleFunc getStreamConnectionStaleCallback() override {
                        return streamConnectionStaleHandler;
                    }

                    DroppedFrameReportFunc getDroppedFrameReportCallback() override {
                        return droppedFrameReportHandler;
                    }


                    DroppedFragmentReportFunc getDroppedFragmentReportCallback() override {
                        return droppedFragmentReportHandler;
                    }


                    StreamErrorReportFunc getStreamErrorReportCallback() override {
                        return streamErrorReportHandler;
                    }

                    StreamClosedFunc getStreamClosedCallback() override {
                        return streamClosedHandler;
                    }

                    FragmentAckReceivedFunc getFragmentAckReceivedCallback() override {
                        return fragmentAckHandler;
                    }


                private:
                    static STATUS
                    streamUnderflowReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle);

                    static STATUS
                    bufferDurationOverflowPressureHandler(UINT64 custom_data, STREAM_HANDLE stream_handle, UINT64 remainDuration);

                    static STATUS
                    streamLatencyPressureHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                                 UINT64 current_buffer_duration);

                    static STATUS
                    streamConnectionStaleHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                                 UINT64 last_buffering_ack);


                    static STATUS
                    droppedFrameReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                              UINT64 dropped_frame_timecode);

                    static STATUS
                    droppedFragmentReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                                 UINT64 fragment_timecode);

                    static STATUS
                    streamErrorReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle,
                                             UPLOAD_HANDLE upload_handle, UINT64 errored_timecode,
                                             STATUS status_code);

                    static STATUS
                    streamClosedHandler(UINT64 custom_data, STREAM_HANDLE stream_handle, UPLOAD_HANDLE upload_handle);

                    static STATUS
                    fragmentAckHandler(UINT64 custom_data, STREAM_HANDLE stream_handle, UPLOAD_HANDLE upload_handle, PFragmentAck pFragmentAck);
                };
            }
        }
    }
}


#endif //__KVS_SINK_STREAM_CALLBACK_PROVIDER_H__
