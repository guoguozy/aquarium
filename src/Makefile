# Lines starting with the pound sign are comments.
#

EXECUTABLE = myprogram

# Recognised platforms are IRIX, Linux, SunOS
PLATFORM = $(shell uname -s)

# OPTIMISATION can be chosen to be either dbg or opt
OPTIMISATION = dbg

INCLUDEDIR =
LIBDIR =
LIBFILES =  -lglut  -lGL -lGLU -lm -lSOIL
IRIXLIBFILES = -lX11 -lXmu
SUNLIBFILES = -lX11 -lXmu

#INSTALLDIR = /projects/acmc/tools/bin


# CC is for the name of the C compiler. CPPFLAGS denotes pre-processor
# flags, such as -I options. CFLAGS denotes flags for the C compiler.
# CXXFLAGS denotes flags for the C++ compiler. You may add additional
# settings here, such as PFLAGS, if you are using other languages such
# as Pascal.


ifeq ($(OPTIMISATION), dbg)
	CFLAGS =  -g
endif


OUTPUTDIR = $(PLATFORM).$(OPTIMISATION)
LIBDIR := $(LIBDIR) $(patsubst %,%/$(PLATFORM).$(OPTIMISATION),$(LIBDIR))


# If we don't know the platform then take a punt on gnu stuff
#CC = gcc
#CXX = g++
#CFLAGS := $(CFLAGS) -Wall
#DEPFLAGS = -MM


# Set up some platform/compiler specific options
ifeq ($(findstring IRIX, $(PLATFORM)), IRIX)
	LIBDIR := $(LIBDIR) /usr/lib32 /usr/freeware/lib32
	LIBFILES := $(LIBFILES) $(IRIXLIBFILES)
	INCLUDEDIR := $(INCLUDEDIR) /usr/freeware/include
	LDFLAGS :=  -LANG:std
	CXX = CC
	CFLAGS = -fullwarn -D IRIX
	CXXFLAGS := $(CXXFLAGS) -LANG:std
	DEPFLAGS = -M
endif

ifeq ($(PLATFORM), Linux)
	CC = gcc
	CXX = g++
	CFLAGS := $(CFLAGS) -Wall -D Linux
	DEPFLAGS = -MM
endif

ifeq ($(PLATFORM), SunOS)
	CC = gcc
	CXX = g++
	LIBDIR := $(LIBDIR) /opt/local/lib
	LIBFILES := $(LIBFILES) $(SUNLIBFILES)
	INCLUDEDIR := $(INCLUDEDIR) /opt/local/include
	CFLAGS := $(CFLAGS) -Wall -D SunOS
	DEPFLAGS = -MM
endif

CXXFLAGS := $(CXXFLAGS) $(CFLAGS)

ifneq ($(strip $(LIBDIR)), )
	LIBDIR := $(patsubst %,-L%,$(LIBDIR))
	LDFLAGS := $(LDFLAGS) $(LIBDIR)
endif


ifneq ($(strip $(INCLUDEDIR)), )
	INCLUDEDIR := $(patsubst %,-I%,$(INCLUDEDIR))
	CPPFLAGS := $(CPPFLAGS) $(INCLUDEDIR)
endif



LINKCC = $(CXX)

# Now figure out the source files, object files and dependency files
OUTPUTDIRFORSED := $(subst /,\/,$(OUTPUTDIR))
SRCS := $(wildcard *.cpp)
OBJS := $(addprefix $(OUTPUTDIR)/,$(patsubst %.cpp,%.o,$(wildcard *.cpp))) \
		$(addprefix $(OUTPUTDIR)/,$(patsubst %.c,%.o,$(wildcard *.c)))
DEPS := $(patsubst %.o,%.d,$(OBJS))


# "all" is the default target. Simply make it point to myprogram.

all: $(OUTPUTDIR)/$(EXECUTABLE)

# Define the components of the program, and how to link them together.
# These components are defined as dependencies; that is, they must be
# made up-to-date before the code is linked.
$(OUTPUTDIR)/$(EXECUTABLE): $(DEPS) $(OBJS)
	$(LINKCC)  $(OBJS)  -o $(OUTPUTDIR)/$(EXECUTABLE) $(LDFLAGS) $(LIBFILES)

# Specify that the dependency files depend on the C source files.
# Specify that all .o files depend on .c files, and indicate how
# the .c files are converted (compiled) to the .o files.
$(OUTPUTDIR)/%.d: %.cpp
	-mkdir -p $(OUTPUTDIR)
	$(CXX) $(DEPFLAGS) $(CPPFLAGS) $< | sed 's/\([A-Za-z]*\.o\)/$(OUTPUTDIRFORSED)\/\1/' > $@
	$(CXX) $(DEPFLAGS) $(CPPFLAGS) $< | sed s/\\.o/.d/ | sed 's/\([A-Za-z]*\.o\)/$(OUTPUTDIRFORSED)\/\1/' > $@

$(OUTPUTDIR)/%.d: %.c
	-mkdir -p $(OUTPUTDIR)
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $< | sed 's/\([A-Za-z]*\.o\)/$(OUTPUTDIRFORSED)\/\1/' > $@
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $< | sed s/\\.o/.d/ | sed 's/\([A-Za-z]*\.o\)/$(OUTPUTDIRFORSED)\/\1/' > $@

$(OUTPUTDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(OUTPUTDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# note that we can't just rm $(OUTPUTDIR)/* as this would delete
# the source code as well if OUTPUTDIR = .
clean:
	-rm $(OUTPUTDIR)/$(EXECUTABLE) $(OBJS) $(DEPS) *~


explain:
	@echo "The following information represents your program:"
	@echo "Final executable name: $(EXECUTABLE)"
	@echo "Source files:     $(SRCS)"
	@echo "Object files:     $(OBJS)"
	@echo "Dependency files:   $(DEPS)"

depend: $(DEPS)
	@echo "Dependencies are now up-to-date."

#install: $(OUTPUTDIR)/$(EXECUTABLE)
#	@echo "Installing to $(INSTALLDIR)"
#	cp $(OUTPUTDIR)/$(EXECUTABLE) $(INSTALLDIR)

-include $(DEPS)
