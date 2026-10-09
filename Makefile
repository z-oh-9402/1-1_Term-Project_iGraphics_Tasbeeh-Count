CXXFLAGS ?= -O2 -Wall
CFLAGS ?= -O2
LDLIBS = -lglut -lGLU -lGL -ldl -lpthread -lm

BUILD = build
TARGET = $(BUILD)/tasbeeh-count

all: $(TARGET)

$(TARGET): iMain.cpp iGraphics.h iSound.h stb_image.h $(BUILD)/miniaudio.o | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) iMain.cpp $(BUILD)/miniaudio.o -o $@ $(LDFLAGS) $(LDLIBS)

# miniaudio is large, so it is compiled once here instead of on every build
$(BUILD)/miniaudio.o: miniaudio.c miniaudio.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c miniaudio.c -o $@

$(BUILD):
	mkdir -p $@

# The game loads its images, sounds and data files by relative path, so it has
# to be run from the project folder.
run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
