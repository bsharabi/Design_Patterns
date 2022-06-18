#!make -f


# ----------------------------- Q1, Q2 ,Q3 ----------------------------
SOURCE_PATH_Q1-3=Q1-3_sources
OBJECT_PATH_Q1-3=Q1-3_objects

SOURCES_Q1-3=$(wildcard $(SOURCE_PATH_Q1-3)/*.cpp)
HEADERS_Q1-3=$(wildcard $(SOURCE_PATH_Q1-3)/*.hpp)
OBJECTS_Q1-3=$(subst Q1-3_sources/,Q1-3_objects/,$(subst .cpp,.o,$(SOURCES_Q1-3)))


# ----------------------------- Q4----------------------------
SOURCE_PATH_Q4=Q4_sources
OBJECT_PATH_Q4=Q4_objects

SOURCES_Q4=$(wildcard $(SOURCE_PATH_Q4)/*.cpp)
HEADERS_Q4=$(wildcard $(SOURCE_PATH_Q4)/*.hpp)
OBJECTS_Q4=$(subst Q4_sources/,Q4_objects/,$(subst .cpp,.o,$(SOURCES_Q4)))


# ----------------------------- Q5 ----------------------------

SOURCE_PATH_Q5=Q5_sources
OBJECT_PATH_Q5=Q5_objects

SOURCES_Q5=$(wildcard $(SOURCE_PATH_Q5)/*.cpp)
HEADERS_Q5=$(wildcard $(SOURCE_PATH_Q5)/*.hpp)
OBJECTS_Q5=$(subst Q5_sources/,Q5_objects/,$(subst .cpp,.o,$(SOURCES_Q5)))

# ----------------------------- Q6 ----------------------------

SOURCE_PATH_Q6=Q6_sources
OBJECT_PATH_Q6=Q6_objects

SOURCES_Q6=$(wildcard $(SOURCE_PATH_Q6)/*.cpp)
HEADERS_Q6=$(wildcard $(SOURCE_PATH_Q6)/*.hpp)
OBJECTS_Q6=$(subst Q6_sources/,Q6_objects/,$(subst .cpp,.o,$(SOURCES_Q6)))

CXX=clang++-9


CXXVERSION=c++2a

# CXXFLAGS=-std=$(CXXVERSION) -Werror -Wsign-conversion -I$(SOURCE_PATH_Q1-3) $(SOURCE_PATH_Q4) $(SOURCE_PATH_Q5) $(SOURCE_PATH_Q6)
CXXFLAGS_Q1-3=-std=$(CXXVERSION) -Werror -Wsign-conversion -I $(SOURCE_PATH_Q1-3)
CXXFLAGS_Q4=-std=$(CXXVERSION) -Werror -Wsign-conversion -I $(SOURCE_PATH_Q4) 
CXXFLAGS_Q5=-std=$(CXXVERSION) -Werror -Wsign-conversion -I $(SOURCE_PATH_Q5) 
CXXFLAGS_Q6=-std=$(CXXVERSION) -Werror -Wsign-conversion -I $(SOURCE_PATH_Q6) 

TIDY_FLAGS=-extra-arg=-std=$(CXXVERSION) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=*
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

run: main guard reactor singelton libDesign.a client
	./main 4551 && ./guard && ./singelton && ./reactor 8100

main: main1.o $(OBJECTS_Q1-3)
	$(CXX) $(CXXFLAGS_Q1-3) $^ -o $@ -pthread

guard:$(OBJECTS_Q4)
	$(CXX) $(CXXFLAGS_Q4) $^ -o $@ -pthread

singelton: $(OBJECTS_Q5)
	$(CXX) $(CXXFLAGS_Q5) $^ -o $@ -pthread

reactor:$(OBJECTS_Q6)
	$(CXX) $(CXXFLAGS_Q6) $^ -o $@ -pthread

client:client.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread


# test: TestRunner.o Test.o $(OBJECTS_Q1-3) $(OBJECTS_Q4) $(OBJECTS_Q5) $(OBJECTS_Q6)
# 	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

# test: TestRunner.o Test.o libDesign.a
# 	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

libDesign.a: $(OBJECTS_Q1-3) $(OBJECTS_Q4) $(OBJECTS_Q5) $(OBJECTS_Q6)
	ar -rcs libDesign.a  $(OBJECTS_Q1-3) $(OBJECTS_Q4) $(OBJECTS_Q5) $(OBJECTS_Q6) 

tidy:
	clang-tidy $(HEADERS) $(TIDY_FLAGS) --

%.o: %.c* $(HEADERS_Q1-3) $(HEADERS_Q4) $(HEADERS_Q5) $(HEADERS_Q6)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH_Q1-3)/%.o: $(SOURCE_PATH_Q1-3)/%.c* $(HEADERS_Q1-3)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH_Q4)/%.o: $(SOURCE_PATH_Q4)/%.cpp $(HEADERS_Q4)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH_Q5)/%.o: $(SOURCE_PATH_Q5)/%.cpp $(HEADERS_Q5)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH_Q6)/%.o: $(SOURCE_PATH_Q6)/%.cpp $(HEADERS_Q6)
	$(CXX) $(CXXFLAGS) --compile $< -o $@


run_m:
	./main
run_g:
	./guard
run_s:
	./singelton
run_r:
	./reactor

clean:
	rm -f libDesign.a $(OBJECTS_Q1-3) $(OBJECTS_Q4) $(OBJECTS_Q5) $(OBJECTS_Q6)  *.o Q5_sources/fd.txt test main guard reactor singelton client
