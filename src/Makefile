INCLUDES := -I/usr/include/boost -I/home/terahz/rpi/cmake/include
LIBRARIES := -L/home/terahz/rpi/boost/lib -L/home/terahz/rpi/cmake/lib 
LIBS := -lwthttp -lwt -ldl -lboost_signals -lboost_thread -lboost_program_options -lboost_date_time -lboost_random -lboost_regex -lboost_system -lboost_filesystem
CXXFLAGS := -O3 -g -Wall -Werror $(INCLUDES) $(LIBRARIES) $(LIBS)
LDFLAGS := $(LIBS) 
RM := rm -rf

CXX := g++
#CXX := arm-unknown-linux-gnueabi-g++
NAME := Aquarius

all: $(NAME) copy

$(NAME): $(NAME).o AquariusPlugin.hpp PluginLoader.o
	$(CXX) $(CXXFLAGS) -Wl,-rpath,'$$ORIGIN/lib' $^ -o $@

copy:
ifdef DISTPATH
	cp $(NAME) $(DISTPATH)
endif
clean:
	$(RM)  *.o *.so* $(TEST)
