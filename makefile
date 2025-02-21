PROJECT_NAME=SDL_Project
BUILD_DIR=build
CMAKE_GENERATOR='Unix Makefiles'
CMAKE_OPTIONS=-G $(CMAKE_GENERATOR)
PROGRAM_TO_BUILD=make
PROGRAM_TO_COVERAGE_SCRIPT=gcc

ifeq ($(CMAKE_GENERATOR),Ninja)
	PROGRAM_TO_BUILD=ninja
	PROGRAM_TO_COVERAGE_SCRIPT=ninja
else ifeq ($(CMAKE_GENERATOR),Unix Makefiles)
	PROGRAM_TO_BUILD=make
	PROGRAM_TO_COVERAGE_SCRIPT=gcc
endif

all: clean configure build

check: clean configure_all build run_tests run_tests_valgrind

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CMAKE_OPTIONS) ..

configure_all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CMAKE_OPTIONS) -DTESTS=ON -DCLANG_TIDY=ON -DCODE_COVERAGE=ON -DENABLE_VALGRIND=ON ..

clean:
	rm -rf $(BUILD_DIR)

build:
	@echo "\nBuilding project with $(PROGRAM_TO_BUILD)..."
	@cd $(BUILD_DIR) && $(PROGRAM_TO_BUILD) -j
	@echo "Build completed."
.PHONY: build


run:
	./$(BUILD_DIR)/bin/$(PROJECT_NAME)

run_tests:
	@echo "\nRunning tests..."
	./$(BUILD_DIR)/bin/GLTests -v

run_tests_valgrind:
	@echo "\nRunning tests with valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --log-file=logs/valgrind.log ./$(BUILD_DIR)/bin/GLTests

rebuild_and_run: build run

rebuild_and_tests: build run_tests run_tests_valgrind

clang-format-all-files:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) ! -path "./lib/*" ! -path "./$(BUILD_DIR)/*" -print -exec clang-format -i {} +

coverage:
	./scripts/coverage_html.sh $(PROGRAM_TO_COVERAGE_SCRIPT)
	open build/coverage/index.html > /dev/null 2>&1

help:
	@echo "Available targets:"
	@echo "  all                  	- Clean, configure, build, and run the project"
	@echo "  configure            	- Configure the project"
	@echo "  configure_all        	- Configure the project with tests and additional options"
	@echo "  clean                	- Clean the build directory"
	@echo "  build                	- Build the project"
	@echo "  run                  	- Run the project"
	@echo "  run_tests            	- Run tests"
	@echo "  rebuild_and_run      	- Rebuild the project and run"
	@echo "  rebuild_and_tests    	- Rebuild the project and run tests"
	@echo "  clang-format-all-files - Format all files using clang-format"
