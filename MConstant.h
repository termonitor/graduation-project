#ifndef __M_CONSTANT_H__
#define __M_CONSTANT_H__

//body
#define PARSER_STATE_SYNC 1
#define PARSER_STATE_SYNC_CHECK 2
#define PARSER_STATE_PAYLOAD_LENGTH 3
#define PARSER_STATE_PAYLOAD 4
#define PARSER_STATE_CHKSUM 5
#define PARSER_SYNC_BYTE 170 //AA
#define PARSER_EXCODE_BYTE 85 //55
#define MULTI_BYTE_CODE_THRESHOLD 127
#define PARSER_CODE_RAW 128 //80
#define RAW_DATA_BYTE_LENGTH 2
#define PARSER_CODE_POOR_SIGNAL 2
#define PARSER_CODE_EEG_POWER 131 //83
#define PARSER_CODE_ATTENTION 4
#define PARSER_CODE_MEDITATION 5
#define PARSER_CODE_HEARTRATE 3
#define PARSER_CODE_DEBUG_ONE 132
#define EEG_DEBUG_ONE_BYTE_LENGTH 5
#define PARSER_CODE_DEBUG_TWO 133
#define EEG_DEBUG_TWO_BYTE_LENGTH 3
#define EEG_POWER_BYTE 24
#define MINN 10
#define MAXN 100000000

#endif