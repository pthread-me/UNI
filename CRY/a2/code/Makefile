LIBRARY=$(HOME)/hub/library/lib
CC= g++ -std=c++23
FLAGS= -I$(LIBRARY)/include -g 
BIG_D_OPTIMIZATION = -Ofast
BUILD_DIR = build

WARNINGS = -Wall -Werror -Wpedantic -Wextra -Wformat -Wnrvo -Wnull-dereference \
					 -Winline 


SRC_FILES = main.cpp 
LIB_FILES= $(wildcard $(LIBRARY)/build/*.o)

TARGET= $(BUILD_DIR)/main

$(TARGET): $(SRC_FILES) $(LIB_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(WARNINGS) $(FLAGS) $^ -o $@ 	
#	@$(info $(LIB_FILES))     PRINTS THE VARIABLE

