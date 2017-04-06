 #########################################################################################
 #                                                                                       #
 # PFC, pinam45 functions and classes                                                    #
 # Copyright (C) 2016 PINARD Maxime (maxime.pin@live.fr)                                 #
 #                                                                                       #
 # This software is provided 'as-is', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.           #
 # In NO EVENT will the authors be held liable for any damages arising from the          #
 # use of this software.                                                                 #
 #                                                                                       #
 # Permission is granted to anyone to use this software for any purpose,                 #
 # including commercial applications, and to alter it and redistribute it freely,        #
 # subject to the following restrictions:                                                #
 #                                                                                       #
 # 1. The origin of this software must not be misrepresented;                            #
 # you must not claim that you wrote the original software.                              #
 # If you use this software in a product, an acknowledgment                              #
 # in the product documentation would be appreciated but is not required.                #
 #                                                                                       #
 # 2. Altered source versions must be plainly marked as such,                            #
 # and must not be misrepresented as being the original software.                        #
 #                                                                                       #
 # 3. This notice may not be removed or altered from any source distribution.            #
 #                                                                                       #
 #########################################################################################

#=============================================================================
# Project related variables
EXENAME        = UTBM_IA41_Pogo
FILEIDENTIFIER1 = .cpp
FILEIDENTIFIER2 = .c
COMPILER1       = g++
COMPILER2       = gcc
COMPFLAGS1      = -pedantic -pedantic-errors -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion -Wextra -Wformat -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized -Wunreachable-code -Wwrite-strings
COMPFLAGS2      = -pedantic -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion -Wextra -Wfloat-equal -Wformat -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmissing-declarations -Wmissing-include-dirs -Wpointer-arith -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized -Wunreachable-code -Wwrite-strings -DDEBUG
COMPSTANDARD1   = -std=c++14
COMPSTANDARD2   = -std=c99
LINKS           = -lm
DBARGS          = -g -DDEBUG

BUILDDIR        = build/
OBJDIR          = $(BUILDDIR)obj/
SOURCEDIRS      = PFC_C/ConsoleControl/src/ Pogo/src/
INCLUDEDIRS     = /usr/include/ PFC_C/ConsoleControl/include/ PFC_Cpp/Dispatcher/include/ PFC_Cpp/Logger/include/ PFC_C/Logger/include/ Pogo/include/
LIBSDIRS        = /usr/lib/


#=============================================================================
# Commands variables
DISPLAY         = printf
MKDIR           = mkdir -p
RMDIR           = rmdir
RM              = rm -f
LD              = ld -r


#=============================================================================
# Other
VOIDECHO        = > /dev/null 2>&1


#=============================================================================
# Semi-automatic variables
EXEFINALOBJ     = $(OBJDIR)$(EXENAME).o
EXEFINAL        = $(BUILDDIR)$(EXENAME).elf
INCLUDEARGS     = $(addprefix -I,$(INCLUDEDIRS))
LIBARGS         = $(addprefix -L,$(LIBSDIRS))


#=============================================================================
# Automatic variables
SOURCES1        = $(foreach sourcedir,$(SOURCEDIRS),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER1)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER1)))
SOURCES2        = $(foreach sourcedir,$(SOURCEDIRS),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER2)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER2)))
OBJECTS1        = $(patsubst %$(FILEIDENTIFIER1),%.o,$(foreach sourcedir,$(SOURCEDIRS),$(subst $(sourcedir),$(OBJDIR),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER1)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER1)))))
OBJECTS2        = $(patsubst %$(FILEIDENTIFIER2),%.o,$(foreach sourcedir,$(SOURCEDIRS),$(subst $(sourcedir),$(OBJDIR),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER2)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER2)))))
OBJSUBDIRS      = $(sort $(OBJDIR) $(dir $(OBJECTS1)) $(dir $(OBJECTS2)))


#=============================================================================
# Special GNU make variables
VPATH           = $(SOURCEDIRS)


#=============================================================================
# Rules: Phony Targets
.PHONY: silent
silent:
	@make --silent $(EXEFINAL)

.PHONY: all
all: $(EXEFINAL)

.PHONY: debug
debug: COMPFLAGS1 += $(DBARGS)
debug: COMPFLAGS2 += $(DBARGS)
debug: $(EXEFINAL)

.PHONY: $(EXENAME)
$(EXENAME): $(EXEFINAL)

.PHONY: clean
clean:
	@$(DISPLAY) "\n\033[1;32m->\033[0m Cleaning files and folders...\n"
	@$(DISPLAY) " $(foreach file,$(OBJECTS1) $(OBJECTS2),\033[1;32m-\033[0m Removing file \033[0;33m$(file)\033[0m\n)"
	@$(RM) $(OBJECTS1) $(OBJECTS2)
	@$(DISPLAY) " \033[1;32m-\033[0m Removing file \033[0;33m$(EXEFINALOBJ)\033[0m\n"
	@$(RM) $(EXEFINALOBJ)
	@$(DISPLAY) " $(foreach folder,$(OBJSUBDIRS),\033[1;32m-\033[0m Removing folder \033[0;33m$(folder)\033[0m\n)"
	@$(RMDIR) $(OBJSUBDIRS) $(VOIDECHO) || true
	@$(RMDIR) $(OBJDIR) $(VOIDECHO) || true
	@$(DISPLAY) " \033[1;32m-\033[0m Removing file \033[0;33m$(EXEFINAL)\033[0m"
	@$(RM) $(EXEFINAL)
	@$(DISPLAY) "\n\n"

.PHONY : help
help:
	@$(DISPLAY) "\n\033[1;32m->\033[0m Valid targets for this Makefile:\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m silent\033[0m (the default if no target is provided)\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m all\033[0m\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m debug\033[0m\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m clean\033[0m\n"
	@$(DISPLAY) "\n"

#=============================================================================
# Rules: File Targets
$(EXEFINAL): $(EXEFINALOBJ)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Building \033[0;33m$(EXEFINAL)\033[0m from \033[0;33m$(OBJDIR)$(EXENAME).o\033[0m...   "
	@$(MKDIR) $(BUILDDIR)
	$(COMPILER1) $(LIBARGS) $(LINKS) $(EXEFINALOBJ) -o $(EXEFINAL)
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"
	@$(DISPLAY) "\n\n"

$(EXEFINALOBJ): $(OBJECTS1) $(OBJECTS2)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Merging objects files into \033[0;33m$(EXEFINALOBJ)\033[0m...   "
	$(LD) $(OBJECTS1) $(OBJECTS2) -o $(EXEFINALOBJ)
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"

$(OBJDIR)%.o: %$(FILEIDENTIFIER1)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Building \033[0;33m$@\033[0m from \033[0;33m$^\033[0m...   "
	@$(MKDIR) $(OBJDIR) $(OBJSUBDIRS)
	$(COMPILER1) $(COMPFLAGS1) $(COMPSTANDARD1) $(INCLUDEARGS) -c $^ -o $@
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"

$(OBJDIR)%.o: %$(FILEIDENTIFIER2)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Building \033[0;33m$@\033[0m from \033[0;33m$^\033[0m...   "
	@$(MKDIR) $(OBJDIR) $(OBJSUBDIRS)
	$(COMPILER2) $(COMPFLAGS2) $(COMPSTANDARD2) $(INCLUDEARGS) -c $^ -o $@
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"
