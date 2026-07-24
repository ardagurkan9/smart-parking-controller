CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -Iinclude
BUILD_DIR := build

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

CONTROLLER_TEST := $(BUILD_DIR)/test_controller$(EXE)
ACCESS_TEST := $(BUILD_DIR)/test_access$(EXE)
VEHICLE_TEST := $(BUILD_DIR)/test_vehicle$(EXE)
TEST_BINS := $(CONTROLLER_TEST) $(ACCESS_TEST) $(VEHICLE_TEST)

.PHONY: all test clean

all: $(TEST_BINS)

test: $(TEST_BINS)
	./$(CONTROLLER_TEST)
	./$(ACCESS_TEST)
	./$(VEHICLE_TEST)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CONTROLLER_TEST): tests/test_controller.c src/controller.c include/controller.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) tests/test_controller.c src/controller.c -o $@

$(ACCESS_TEST): tests/test_access.c src/access.c src/controller.c include/access.h include/controller.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) tests/test_access.c src/access.c src/controller.c -o $@

$(VEHICLE_TEST): tests/test_vehicle.c src/vehicle.c include/vehicle.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) tests/test_vehicle.c src/vehicle.c -o $@

clean:
	rm -rf $(BUILD_DIR)
