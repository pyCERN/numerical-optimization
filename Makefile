# ===== Compiler =====
CXX := g++
CXXFLAGS := -std=c++20

# ===== Paths =====
ROOT := .
ALG_DIR := $(ROOT)/algorithm
TF_DIR  := $(ROOT)/test_functions
EXP_DIR := $(ROOT)/experiments
EIGEN_DIR := $(ROOT)/libs/eigen-5.0.0

# ===== Source files =====
ALG_SRC := \
	$(ALG_DIR)/optimizer/steepest_descent.cpp \
	$(ALG_DIR)/optimizer/newton.cpp \
	$(ALG_DIR)/step_size/backtrack_search.cpp \
	$(ALG_DIR)/step_size/fixed_step_size.cpp \
	$(ALG_DIR)/step_size/wolfe_search.cpp

TF_SRC := \
	$(TF_DIR)/rosenbrock.cpp

EXP_SRC := \
	$(EXP_DIR)/run_newton.cpp

SRCS := $(ALG_SRC) $(TF_SRC) $(EXP_SRC)
OBJS := $(SRCS:.cpp=.o)

# ===== Target =====
TARGET := run.exe

# ===== Include paths =====
INCLUDES := \
	-I$(ALG_DIR) \
	-I${TF_DIR} \
	-I${EIGEN_DIR}

# ===== Rules =====
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
