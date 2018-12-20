THE_OS := $(shell uname -s)

default:
	@echo "Detected OS: ${THE_OS}"
	$(MAKE) CC=gcc CXX=g++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -Wno-ignored-attributes -pipe -O3 -g -ffast-math -flto -march=native -std=c++14 -DNDEBUG'  \
		LDFLAGS='$(LDFLAGS) -flto -g' \
		cinkgo

debug:
	@echo "Detected OS: ${THE_OS}"
	$(MAKE) CC=gcc CXX=g++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -Wno-ignored-attributes -pipe -Og -g -std=c++14' \
		LDFLAGS='$(LDFLAGS) -g' \
		cinkgo

clang:
	@echo "Detected OS: ${THE_OS}"
	$(MAKE) CC=clang CXX=clang++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -Wno-missing-braces -Wno-mismatched-tags -O3 -ffast-math -flto -march=native -std=c++14 -DNDEBUG' \
		LDFLAGS='$(LDFLAGS) -flto -fuse-linker-plugin' \
		cinkgo

DYNAMIC_LIBS = -lboost_system -lboost_filesystem -lboost_program_options -lpthread -lz
LIBS =

ifeq ($(THE_OS),Linux)
# for Linux with OpenBLAS
#	CXXFLAGS += -I/usr/include/openblas -I./Eigen
#	DYNAMIC_LIBS += -lopenblas
#	DYNAMIC_LIBS += -lOpenCL
endif
ifeq ($(THE_OS),Darwin)
# for macOS (comment out the Linux part)
	LIBS += -framework Accelerate
	LIBS += -framework OpenCL
	CXXFLAGS += -I./Eigen
	CXXFLAGS += -I/System/Library/Frameworks/Accelerate.framework/Versions/Current/Headers
endif

# for MKL instead of OpenBLAS
#DYNAMIC_LIBS += -lmkl_rt
#CXXFLAGS += -I/opt/intel/mkl/include
#LDFLAGS  += -L/opt/intel/mkl/lib/intel64/

CXXFLAGS += -I.
CPPFLAGS += -MD -MP

sources = Cinkgo.cpp

objects = $(sources:.cpp=.o)
deps = $(sources:%.cpp=%.d)

-include $(deps)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

cinkgo: $(objects)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) $(DYNAMIC_LIBS)

clean:
	-$(RM) cinkgo $(objects) $(deps)

.PHONY: clean default debug clang
