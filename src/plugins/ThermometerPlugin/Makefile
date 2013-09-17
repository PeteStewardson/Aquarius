INCLUDES := -I/usr/include/boost -I../.. -I../../../../DS18B20/src 
LIBRARIES := -L/home/terahz/rpi/boost/lib -L/home/terahz/rpi/cmake/lib -L../../../../DS18B20/src 
LIBS := -lwthttp -lwt -lboost_signals -lboost_thread -lboost_program_options -lboost_date_time -lboost_random -lboost_regex -lboost_system -lboost_filesystem -lDS18B20 
LDFLAGS := $(LIBS) RM := rm -rf 
CXXFLAGS := -rdynamic -O3 -fPIC -g -Wall -Werror $(INCLUDES) $(LIBRARIES) $(LIBS)
CXX := g++
#CXX := arm-unknown-linux-gnueabi-g++
MAJOR := 0
MINOR := 1
NAME := ThermometerPlugin
VERSION := $(MAJOR).$(MINOR)
RM := rm -rf

all: $(NAME).so copy

$(NAME).so: $(NAME).o Thermometer.o
	$(CXX) $(CXXFLAGS) -rdynamic -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) -Wl,-rpath,'$$ORIGIN/lib' $^ -o $@
	
clean:
	$(RM) *.o *.so* 
	
copy:
ifdef DISTPATH
	cp $(NAME).so $(DISTPATH)
endif
