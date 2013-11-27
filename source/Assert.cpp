#include "Assert.h"

// Assert.cpp
// Author J. Mills
// 9/15/2013

void assertFailed(char *file, int line, char *cond) {
	consoleDemoInit();
	printf("%s:%d: ASSERT(%s) failed!\n", file, line, cond);
}
