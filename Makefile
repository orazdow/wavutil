TARGET = wavwrite.exe

# comment out to use basedir
builddir = build/

SRC = main.cpp wavutil.cpp pa.cpp

SRCDIR_2 = lib
 
INCLUDE = -ID:/Libraries/portaudio/include 
INCLUDE += -Ilib
LIBS = -LD:/Libraries/portaudio/build 
LIBS += -lportaudio

CXX = g++
FLAGS = -Wall 

OBJECTS = $(addprefix $(builddir), $(addsuffix .o, $(basename $(notdir $(SRC)))))
TARGET :=  $(addprefix $(builddir), $(TARGET))

# compile objects
$(builddir)%.o: %.cpp
	$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@ $(LIBS)
	@echo $@

$(builddir)%.o: $(SRCDIR_2)/%.cpp
	$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $@ $(LIBS)
	@echo $@

all: make_dir $(TARGET)

# build exe
$(TARGET): $(OBJECTS)
	$(CXX) $(FLAGS) $^ -o $@ $(LIBS)


make_dir : $(builddir)

$(builddir):
	mkdir -p $(builddir)

clean:
	rm -f $(OBJECTS) $(TARGET)

cleanexe:
	rm -f $(TARGET)

print:
	@echo $(OBJECTS)
	@echo $(TARGET)

run:
	@./$(TARGET)