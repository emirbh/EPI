# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
SRC_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(SRC_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

# Flags passed to the C++ compiler.
DEFINES += -DIDEBUG=1 -DDEVELOPMENT=1

# All tests produced by this Makefile.
TESTS = 05-primitive-types \
				06-arrays-and-strings \
				07-linked-lists \
				08-stacks-and-queues \
				09-binary-trees \
				10-heaps \
				11-searching \
				12-hash-tables \
				13-sorting \
				14-binary-search-trees \
				15-meta-algorithms \
				16-algorithms-on-graphs \
				17-intractability \
				18-parallel-computing

# All headers.  Usually you shouldn't change this definition.
HEADERS = $(SRC_DIR)/*.h \

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) *.o

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
SRCS_ = $(SRC_DIR)/*.cc $(SRC_DIR)/*.h $(HEADERS)

#
#	Build main files
#

05-primitive-types.o : $(SRC_DIR)/05-primitive-types.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/05-primitive-types.cc
06-arrays-and-strings.o : $(SRC_DIR)/06-arrays-and-strings.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/06-arrays-and-strings.cc
07-linked-lists.o : $(SRC_DIR)/07-linked-lists.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/07-linked-lists.cc
08-stacks-and-queues.o : $(SRC_DIR)/08-stacks-and-queues.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/08-stacks-and-queues.cc
09-binary-trees.o : $(SRC_DIR)/09-binary-trees.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/09-binary-trees.cc
10-heaps.o : $(SRC_DIR)/10-heaps.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/10-heaps.cc
11-searching.o : $(SRC_DIR)/11-searching.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/11-searching.cc
12-hash-tables.o : $(SRC_DIR)/12-hash-tables.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/12-hash-tables.cc
13-sorting.o : $(SRC_DIR)/13-sorting.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/13-sorting.cc
14-binary-search-trees.o : $(SRC_DIR)/14-binary-search-trees.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/14-binary-search-trees.cc
15-meta-algorithms.o : $(SRC_DIR)/15-meta-algorithms.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/15-meta-algorithms.cc
16-algorithms-on-graphs.o : $(SRC_DIR)/16-algorithms-on-graphs.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/16-algorithms-on-graphs.cc
17-intractability.o : $(SRC_DIR)/17-intractability.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/17-intractability.cc
18-parallel-computing.o : $(SRC_DIR)/18-parallel-computing.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEFINES) -c $(SRC_DIR)/18-parallel-computing.cc

#
#	Targets
#

05-primitive-types : 05-primitive-types.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
06-arrays-and-strings : 06-arrays-and-strings.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
07-linked-lists : 07-linked-lists.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
08-stacks-and-queues : 08-stacks-and-queues.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
09-binary-trees : 09-binary-trees.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
10-heaps : 10-heaps.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
11-searching : 11-searching.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
12-hash-tables : 12-hash-tables.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
13-sorting : 13-sorting.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
14-binary-search-trees : 14-binary-search-trees.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
15-meta-algorithms : 15-meta-algorithms.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
16-algorithms-on-graphs : 16-algorithms-on-graphs.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
17-intractability : 17-intractability.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
18-parallel-computing : 18-parallel-computing.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


#sample1_unittest.o : $(SRC_DIR)/sample1_unittest.cc \
#                     $(SRC_DIR)/sample1.h $(HEADERS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/sample1_unittest.cc
