#include "KvsSinkStreamCallbackProvider.h"

LOGGER_TAG("com.amazonaws.kinesis.video.gstkvs");

using namespace com::amazonaws::kinesis::video;

STATUS
KvsSinkStreamCallbackProvider::streamConnectionStaleHandler(UINT64 custom_data,
                                                            STREAM_HANDLE stream_handle,
                                                            UINT64 time_since_last_buffering_ack) {
    UNUSED_PARAM(custom_data);
    LOG_DEBUG("Reported streamConnectionStale callback for stream handle " << stream_handle << ". Time since last buffering ack in 100ns: " << time_since_last_buffering_ack);
    return STATUS_SUCCESS;
}

STATUS
KvsSinkStreamCallbackProvider::streamErrorReportHandler(UINT64 custom_data,
                                                        STREAM_HANDLE stream_handle,
                                                        UPLOAD_HANDLE upload_handle,
                                                        UINT64 errored_timecode,
                                                        STATUS status_code) {
    LOG_ERROR("Reported stream error. Errored timecode: " << errored_timecode << " Status: 0x" << std::hex << status_code);
    auto customDataObj = reinterpret_cast<KvsSinkCustomData*>(custom_data);

    // ignore if the sdk can recover from the error
    if (!IS_RECOVERABLE_ERROR(status_code)) {
        customDataObj->stream_status = status_code;
    }

    return STATUS_SUCCESS;
}

STATUS
KvsSinkStreamCallbackProvider::droppedFrameReportHandler(UINT64 custom_data,
                                                         STREAM_HANDLE stream_handle,
                                                         UINT64 dropped_frame_timecode) {
    UNUSED_PARAM(custom_data);
    LOG_WARN("Reported droppedFrame callback for stream handle " << stream_handle << ". Dropped frame timecode in 100ns: " << dropped_frame_timecode);
    return STATUS_SUCCESS; // continue streaming
}

STATUS
KvsSinkStreamCallbackProvider::streamLatencyPressureHandler(UINT64 custom_data,
                                                            STREAM_HANDLE stream_handle,
                                                            UINT64 current_buffer_duration) {
    UNUSED_PARAM(custom_data);
    LOG_DEBUG("Reported streamLatencyPressure callback for stream handle " << stream_handle << ". Current buffer duration in 100ns: " << current_buffer_duration);
    return STATUS_SUCCESS;
}

STATUS
KvsSinkStreamCallbackProvider::streamClosedHandler(UINT64 custom_data,
                                                   STREAM_HANDLE stream_handle,
                                                   UPLOAD_HANDLE upload_handle) {
    UNUSED_PARAM(custom_data);
    LOG_DEBUG("Reported streamClosed callback for stream handle " << stream_handle << ". Upload handle " << upload_handle);
    return STATUS_SUCCESS;
}

STATUS KvsSinkStreamCallbackProvider::fragmentAckReceivedHandler(UINT64 custom_data,
                                  STREAM_HANDLE stream_handle,
                                  UPLOAD_HANDLE upload_handle,
                                  PFragmentAck fragment_ack) {
    LOG_INFO("KvsSinkStreamCallbackProvider::fragmentAckReceivedHandler")
    KvsSinkCustomData* customDataObj = reinterpret_cast<KvsSinkCustomData*>(custom_data);

    LOG_INFO("Reporting fragment ack received. Ack timecode " << fragment_ack->timestamp << "fragment_ack_type is " << fragment_ack->ackType);
    LOG_INFO("Other details of pFragmentAck -  SequenceNumber - " << fragment_ack->sequenceNumber << " timestamp - " << fragment_ack->timestamp);
    LOG_INFO("Yet another detail of pFragmentAck -  version - " << fragment_ack->version << " result - " << fragment_ack->result);

    g_signal_emit(G_OBJECT(customDataObj->kvsSink),
                  customDataObj->kvs_sink_signals[SIGNAL_ON_FIRST_FRAGMENT],
                  0,
                  fragment_ack->sequenceNumber,
                  fragment_ack->timestamp);
    return STATUS_SUCCESS;
}

STATUS KvsSinkStreamCallbackProvider::droppedFragmentReportHandler(UINT64 custom_data,
                                           STREAM_HANDLE stream_handle,
                                           UINT64 timecode) {
    LOG_INFO("KvsSinkStreamCallbackProvider::droppedFragmentReportHandler")
    return STATUS_SUCCESS;
}

STATUS KvsSinkStreamCallbackProvider::streamDataAvailableHandler(UINT64 custom_data,
                                         STREAM_HANDLE stream_handle,
                                         PCHAR stream_name,
                                         UPLOAD_HANDLE stream_upload_handle,
                                         UINT64 duration_available,
                                         UINT64 size_available) {
    LOG_INFO("KvsSinkStreamCallbackProvider::streamDataAvailableHandler")
    return STATUS_SUCCESS;
}

STATUS KvsSinkStreamCallbackProvider::streamReadyHandler(UINT64 custom_data, STREAM_HANDLE stream_handle) {
    LOG_INFO("KvsSinkStreamCallbackProvider::streamReadyHandler")
    return STATUS_SUCCESS;
}

STATUS KvsSinkStreamCallbackProvider::streamUnderflowReportHandler(UINT64 custom_data, STREAM_HANDLE stream_handle) {
    LOG_INFO("KvsSinkStreamCallbackProvider::streamUnderflowReportHandler")
    return STATUS_SUCCESS;
}
