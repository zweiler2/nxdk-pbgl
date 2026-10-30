#include <pbkit/pbkit.h>

#define PBGL_PUSH_IMPL
#include "push.h"

/* Recycle at 3/4 of the ring. A block is at most a few hundred dwords, 
 * so there is no way to
 * overshoot the real limit between two checks. */
#define PBGL_PUSH_LIMIT (PBKIT_PUSHBUFFER_SIZE / 4 * 3)

static uint32_t *block_start;
static uint32_t pushed_dwords;

uint32_t *pbgl_push_begin(void) {
    if (pushed_dwords >= PBGL_PUSH_LIMIT) {
        pb_reset();
        pushed_dwords = 0;
    }
    block_start = pb_begin();
    return block_start;
}

void pbgl_push_end(uint32_t *p) {
    pushed_dwords += (uint32_t)(p - block_start);
    pb_end(p);
}

void pbgl_push_reset(void) {
    pushed_dwords = 0;
}
