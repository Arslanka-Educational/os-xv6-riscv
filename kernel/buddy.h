#include "types.h"

void bd_init(void *base, void *end);
void bd_free(void *p);
void *bd_malloc(uint64 nbytes);
