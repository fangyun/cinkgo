#ifndef VERSION_H_
#define VERSION_H_

#include "build.h"

#define CINKGO_VERNUM 1.0
#define CINKGO_VERNUMS "1.0"
#define CINKGO_VERNAME "Xia"

#define CINKGO_VERSION  CINKGO_VERNUMS " (" CINKGO_VERNAME ")"
#define CINKGO_VERGIT   CINKGO_GIT_HASH " (" CINKGO_GIT_BRANCH ")"

#ifdef DCNN
    #define CINKGO_VERBUILD CINKGO_BUILD_TARGET " dcnn build, " CINKGO_BUILD_DATE
#else
    #define CINKGO_VERBUILD CINKGO_BUILD_TARGET " !dcnn build, " CINKGO_BUILD_DATE
#endif

#endif /* VERSION_H_ */
