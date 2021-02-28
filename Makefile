SIMULATION_EXEC ?= simulation.out
TEST_EXEC ?= test.out

BUILD_DIR ?= build

ROULETTE_SRC_DIR ?= roulette

SIMULATION_SRC_DIR ?= simulation
SIMULATION_SRC = $(wildcard $(SIMULATION_SRC_DIR)/*.cpp) $(wildcard $(ROULETTE_SRC_DIR)/*.cpp) 
SIMULATION_OBJ = $(SIMULATION_SRC:%=$(BUILD_DIR)/simulation_%.o)
SIMULATION_DEP = $(SIMULATION_OBJ:.o=.d)
SIMULATION_INC_DIR := $(shell find $(SIMULATION_SRC_DIR) -type d) $(shell find $(ROULETTE_SRC_DIR) -type d)
SIMULATION_INC_FLAG := $(addprefix -I,$(SIMULATION_INC_DIR))

TEST_SRC_DIR ?= test
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cpp) $(wildcard $(ROULETTE_SRC_DIR)/*.cpp) 
TEST_OBJ = $(TEST_SRC:%=$(BUILD_DIR)/test_%.o)
TEST_DEP = $(TEST_OBJ:.o=.d)
TEST_INC_DIR := $(shell find $(TEST_SRC_DIR) -type d) $(shell find $(ROULETTE_SRC_DIR) -type d)
TEST_INC_FLAG := $(addprefix -I,$(TEST_INC_DIR))

CXXFLAGS = -MMD -MP -std=c++17

all: simulation test

simulation: $(BUILD_DIR)/$(SIMULATION_EXEC)

$(BUILD_DIR)/$(SIMULATION_EXEC): $(SIMULATION_OBJ)
	$(CXX) $(SIMULATION_OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/simulation_%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(SIMULATION_INC_FLAG) -c $< -o $@

test: $(BUILD_DIR)/$(TEST_EXEC)

$(BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(TEST_INC_FLAG) -DTEST -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEP)

MKDIR_P ?= mkdir -p