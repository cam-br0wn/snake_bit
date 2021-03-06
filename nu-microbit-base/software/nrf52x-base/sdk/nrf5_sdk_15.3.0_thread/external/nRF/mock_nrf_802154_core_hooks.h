/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_NRF_802154_CORE_HOOKS_H
#define _MOCK_NRF_802154_CORE_HOOKS_H

#ifndef __STATIC_INLINE
#define __STATIC_INLINE
#else
#undef __STATIC_INLINE
#define __STATIC_INLINE
#endif
#define SUPPRESS_INLINE_IMPLEMENTATION

#include <nrf_802154_core_hooks.h>
#undef SUPPRESS_INLINE_IMPLEMENTATION
#undef __STATIC_INLINE
#define __STATIC_INLINE __STATIC_INLINE1

void mock_nrf_802154_core_hooks_Init(void);
void mock_nrf_802154_core_hooks_Destroy(void);
void mock_nrf_802154_core_hooks_Verify(void);




#define nrf_802154_core_hooks_terminate_IgnoreAndReturn(cmock_retval) nrf_802154_core_hooks_terminate_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void nrf_802154_core_hooks_terminate_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool cmock_to_return);
#define nrf_802154_core_hooks_terminate_ExpectAndReturn(term_lvl, req_orig, cmock_retval) nrf_802154_core_hooks_terminate_CMockExpectAndReturn(__LINE__, term_lvl, req_orig, cmock_retval)
void nrf_802154_core_hooks_terminate_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, nrf_802154_term_t term_lvl, req_originator_t req_orig, bool cmock_to_return);
typedef bool (* CMOCK_nrf_802154_core_hooks_terminate_CALLBACK)(nrf_802154_term_t term_lvl, req_originator_t req_orig, int cmock_num_calls);
void nrf_802154_core_hooks_terminate_StubWithCallback(CMOCK_nrf_802154_core_hooks_terminate_CALLBACK Callback);
#define nrf_802154_core_hooks_terminate_IgnoreArg_term_lvl() nrf_802154_core_hooks_terminate_CMockIgnoreArg_term_lvl(__LINE__)
void nrf_802154_core_hooks_terminate_CMockIgnoreArg_term_lvl(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_terminate_IgnoreArg_req_orig() nrf_802154_core_hooks_terminate_CMockIgnoreArg_req_orig(__LINE__)
void nrf_802154_core_hooks_terminate_CMockIgnoreArg_req_orig(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_transmitted_Ignore() nrf_802154_core_hooks_transmitted_CMockIgnore()
void nrf_802154_core_hooks_transmitted_CMockIgnore(void);
#define nrf_802154_core_hooks_transmitted_Expect(p_frame) nrf_802154_core_hooks_transmitted_CMockExpect(__LINE__, p_frame)
void nrf_802154_core_hooks_transmitted_CMockExpect(UNITY_LINE_TYPE cmock_line, const uint8_t* p_frame);
typedef void (* CMOCK_nrf_802154_core_hooks_transmitted_CALLBACK)(const uint8_t* p_frame, int cmock_num_calls);
void nrf_802154_core_hooks_transmitted_StubWithCallback(CMOCK_nrf_802154_core_hooks_transmitted_CALLBACK Callback);
#define nrf_802154_core_hooks_transmitted_ExpectWithArray(p_frame, p_frame_Depth) nrf_802154_core_hooks_transmitted_CMockExpectWithArray(__LINE__, p_frame, p_frame_Depth)
void nrf_802154_core_hooks_transmitted_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, uint8_t* p_frame, int p_frame_Depth);
#define nrf_802154_core_hooks_transmitted_IgnoreArg_p_frame() nrf_802154_core_hooks_transmitted_CMockIgnoreArg_p_frame(__LINE__)
void nrf_802154_core_hooks_transmitted_CMockIgnoreArg_p_frame(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_tx_failed_IgnoreAndReturn(cmock_retval) nrf_802154_core_hooks_tx_failed_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void nrf_802154_core_hooks_tx_failed_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool cmock_to_return);
#define nrf_802154_core_hooks_tx_failed_ExpectAndReturn(p_frame, error, cmock_retval) nrf_802154_core_hooks_tx_failed_CMockExpectAndReturn(__LINE__, p_frame, error, cmock_retval)
void nrf_802154_core_hooks_tx_failed_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const uint8_t* p_frame, nrf_802154_tx_error_t error, bool cmock_to_return);
typedef bool (* CMOCK_nrf_802154_core_hooks_tx_failed_CALLBACK)(const uint8_t* p_frame, nrf_802154_tx_error_t error, int cmock_num_calls);
void nrf_802154_core_hooks_tx_failed_StubWithCallback(CMOCK_nrf_802154_core_hooks_tx_failed_CALLBACK Callback);
#define nrf_802154_core_hooks_tx_failed_ExpectWithArrayAndReturn(p_frame, p_frame_Depth, error, cmock_retval) nrf_802154_core_hooks_tx_failed_CMockExpectWithArrayAndReturn(__LINE__, p_frame, p_frame_Depth, error, cmock_retval)
void nrf_802154_core_hooks_tx_failed_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, uint8_t* p_frame, int p_frame_Depth, nrf_802154_tx_error_t error, bool cmock_to_return);
#define nrf_802154_core_hooks_tx_failed_IgnoreArg_p_frame() nrf_802154_core_hooks_tx_failed_CMockIgnoreArg_p_frame(__LINE__)
void nrf_802154_core_hooks_tx_failed_CMockIgnoreArg_p_frame(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_tx_failed_IgnoreArg_error() nrf_802154_core_hooks_tx_failed_CMockIgnoreArg_error(__LINE__)
void nrf_802154_core_hooks_tx_failed_CMockIgnoreArg_error(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_tx_started_IgnoreAndReturn(cmock_retval) nrf_802154_core_hooks_tx_started_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void nrf_802154_core_hooks_tx_started_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool cmock_to_return);
#define nrf_802154_core_hooks_tx_started_ExpectAndReturn(p_frame, cmock_retval) nrf_802154_core_hooks_tx_started_CMockExpectAndReturn(__LINE__, p_frame, cmock_retval)
void nrf_802154_core_hooks_tx_started_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const uint8_t* p_frame, bool cmock_to_return);
typedef bool (* CMOCK_nrf_802154_core_hooks_tx_started_CALLBACK)(const uint8_t* p_frame, int cmock_num_calls);
void nrf_802154_core_hooks_tx_started_StubWithCallback(CMOCK_nrf_802154_core_hooks_tx_started_CALLBACK Callback);
#define nrf_802154_core_hooks_tx_started_ExpectWithArrayAndReturn(p_frame, p_frame_Depth, cmock_retval) nrf_802154_core_hooks_tx_started_CMockExpectWithArrayAndReturn(__LINE__, p_frame, p_frame_Depth, cmock_retval)
void nrf_802154_core_hooks_tx_started_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, uint8_t* p_frame, int p_frame_Depth, bool cmock_to_return);
#define nrf_802154_core_hooks_tx_started_IgnoreArg_p_frame() nrf_802154_core_hooks_tx_started_CMockIgnoreArg_p_frame(__LINE__)
void nrf_802154_core_hooks_tx_started_CMockIgnoreArg_p_frame(UNITY_LINE_TYPE cmock_line);
#define nrf_802154_core_hooks_rx_started_Ignore() nrf_802154_core_hooks_rx_started_CMockIgnore()
void nrf_802154_core_hooks_rx_started_CMockIgnore(void);
#define nrf_802154_core_hooks_rx_started_Expect() nrf_802154_core_hooks_rx_started_CMockExpect(__LINE__)
void nrf_802154_core_hooks_rx_started_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_nrf_802154_core_hooks_rx_started_CALLBACK)(int cmock_num_calls);
void nrf_802154_core_hooks_rx_started_StubWithCallback(CMOCK_nrf_802154_core_hooks_rx_started_CALLBACK Callback);
#define nrf_802154_core_hooks_rx_ack_started_Ignore() nrf_802154_core_hooks_rx_ack_started_CMockIgnore()
void nrf_802154_core_hooks_rx_ack_started_CMockIgnore(void);
#define nrf_802154_core_hooks_rx_ack_started_Expect() nrf_802154_core_hooks_rx_ack_started_CMockExpect(__LINE__)
void nrf_802154_core_hooks_rx_ack_started_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_nrf_802154_core_hooks_rx_ack_started_CALLBACK)(int cmock_num_calls);
void nrf_802154_core_hooks_rx_ack_started_StubWithCallback(CMOCK_nrf_802154_core_hooks_rx_ack_started_CALLBACK Callback);

#endif
