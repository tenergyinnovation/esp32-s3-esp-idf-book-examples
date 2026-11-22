#include "frame.h"

uint8_t crc8(const uint8_t *p, size_t n)        /* CRC-8 พหุนาม 0x07 */
{
    uint8_t crc = 0;
    while (n--) {
        crc ^= *p++;
        for (int i = 0; i < 8; i++) crc = (crc & 0x80) ? (uint8_t)((crc << 1) ^ 0x07) : (uint8_t)(crc << 1);
    }
    return crc;
}

size_t frame_build(uint8_t *out, const uint8_t *payload, uint8_t len)
{
    out[0] = FRAME_START; out[1] = len;
    for (int i = 0; i < len; i++) out[2 + i] = payload[i];
    out[2 + len] = crc8(&out[1], len + 1);
    return len + 3;
}

void frame_parser_reset(frame_parser_t *p) { p->state = WAIT_START; p->pos = 0; }

bool frame_parser_feed(frame_parser_t *p, uint8_t b, bool *crc_error)
{
    *crc_error = false;
    switch (p->state) {
    case WAIT_START: if (b == FRAME_START) p->state = WAIT_LEN; break;
    case WAIT_LEN:
        if (b == 0 || b > FRAME_MAX_LEN) { frame_parser_reset(p); break; }   // ความยาวผิด ทิ้ง
        p->len = b; p->pos = 0; p->state = WAIT_DATA; break;
    case WAIT_DATA:
        p->data[p->pos++] = b;
        if (p->pos == p->len) p->state = WAIT_CRC;
        break;
    case WAIT_CRC: {
        uint8_t tmp[FRAME_MAX_LEN + 1]; tmp[0] = p->len;
        for (int i = 0; i < p->len; i++) tmp[1 + i] = p->data[i];
        bool ok = (crc8(tmp, p->len + 1) == b);
        frame_parser_reset(p);
        if (!ok) { *crc_error = true; return false; }
        return true; }
    }
    return false;
}
