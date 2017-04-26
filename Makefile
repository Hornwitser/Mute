CPPFLAGS = -iquotesrc/
CXXFLAGS = -std=c++14 -pedantic -Wall -Wextra
LDFLAGS = -g

SOURCE_DIRS = src src/client src/server
BINARIES = bin/client.exe bin/server.exe
DOCS = docs/html

SOURCES = $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.cpp))
HEADERS = $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.hpp))
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(SOURCES))
BUILD_DIRS = $(patsubst src%,build%,$(SOURCE_DIRS))
DOC_SOURCES = $(SOURCES) $(HEADERS)


.PHONY: all clean

all: $(BINARIES) $(DOCS)

$(BUILD_DIRS) bin:
	mkdir $@

build/%.o: src/%.cpp | $(BUILD_DIRS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

bin/client.exe: $(filter-out build/server/%,$(OBJECTS)) | bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

bin/server.exe: $(filter-out build/client/%,$(OBJECTS)) | bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

docs/html: ${DOC_SOURCES} Doxyfile
	doxygen

# Make dependency files
build/%.d: src/%.cpp | $(BUILD_DIRS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -MM -MT "$(patsubst %.d,%.o,$@) $@" \
	       -MF $@

ifneq ($(MAKECMDGOALS),clean)
    include $(patsubst src/%.cpp,build/%.d,$(SOURCES))
endif

clean:
	rm -rf build $(BINARIES) $(DOCS)
