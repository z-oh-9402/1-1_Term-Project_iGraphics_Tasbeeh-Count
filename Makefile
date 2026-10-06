CXXFLAGS ?= -O2 -Wall
LDLIBS = -lglut -lGLU -lGL

BUILD = build
TARGET = $(BUILD)/tasbeeh-count

all: $(TARGET)

$(TARGET): iMain.cpp iGraphics.h stb_image.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) iMain.cpp -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD):
	mkdir -p $@

# The game loads its images and data files by relative path, so it has to be
# run from the project folder.
run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
