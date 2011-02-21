#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = common_data_structures_test
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a

TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = ..
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc
CPPUTEST_USE_GCOV = Y
CPPUTEST_USE_EXTENSIONS = N

#SRC_DIRS is a list of source directories that make up the target library
#If test files are in these directories, their IMPORT_TEST_GROUPs need
#to be included in main to force them to be linked in.  By convention
#put them into an AllTests.h file in each directory
SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/lists \



#TEST_SRC_DIRS is a list of directories including 
# - A test main (AllTests.cpp by conventin)
# - OBJ files in these directories are included in the TEST_TARGET
# - Consequently - AllTests.h containing the IMPORT_TEST_GROUPS is not needed
# - 
TEST_SRC_DIRS = \
	.\
	lists\


#includes for all compiles	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  $(PROJECT_HOME_DIR)/include/lists\



##
# if cpputest_warningsflags are commented out the cpputest harness use standard cpputest warnings
#CPPUTEST_WARNINGFLAGS += -Wconversion -pedantic -Wshadow -Wextra -Wall -Winline #-pedantic-errors -Wunreachable-code  
#CPPUTEST_WARNINGFLAGS += -Wswitch-default -Wswitch-enum #-fno-stack-protector

#Flags to pass to ld
CPPUTEST_LDFLAGS += -rdynamic #-L/usr/lib 
LD_LIBRARIES += #-lstdc++  # -lustr

CPPUTEST_CFLAGS += -g -Wunreachable-code
CPPUTEST_CFLAGS += -std=gnu99


#CPPUTEST_CPPFLAGS += 
#CPPUTEST_CPPFLAGS += -g 


include $(CPPUTEST_HOME)/build/MakefileWorker.mk
