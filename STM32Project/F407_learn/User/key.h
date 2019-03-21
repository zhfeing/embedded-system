#ifndef __INC_KEY
#define __INC_KEY
#include <zhf_lib.h>

enum Key {NoKey = 0, Key0, Key1, Key2, Key_up};
enum ScanMode {Once, Continue};

void keyInit(void);
enum Key scanKey(enum ScanMode mode);

#endif
