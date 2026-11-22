/* frame.h — รูปแบบแพ็กเก็ต: [0xAA][LEN][PAYLOAD...][CRC8]  CRC8 คิดจาก LEN และ PAYLOAD */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define FRAME_START   0xAA
#define FRAME_MAX_LEN 32

typedef struct {
    enum { WAIT_START, WAIT_LEN, WAIT_DATA, WAIT_CRC } state;
    uint8_t len, pos, crc;
    uint8_t data[FRAME_MAX_LEN];
    int64_t last_byte_us;
} frame_parser_t;

uint8_t crc8(const uint8_t *p, size_t n);
size_t  frame_build(uint8_t *out, const uint8_t *payload, uint8_t len);
void    frame_parser_reset(frame_parser_t *p);
/* ป้อนทีละ byte คืน true เมื่อได้แพ็กเก็ตสมบูรณ์ (CRC ถูก) */
bool    frame_parser_feed(frame_parser_t *p, uint8_t b, bool *crc_error);
