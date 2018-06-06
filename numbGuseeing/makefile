CC = gcc
COMPILE_PATH = $(shell pwd)

SRC = $(wildcard *.c) 
SRC += $(wildcard $(COMPILE_PATH)/module/*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

DEBUGMODE ?= YES
#DEBUGMODE ?= NO

CFLAGS = -g
CFLAGS += -I $(COMPILE_PATH)/module/

ifeq ($(DEBUGMODE),YES)
CFLAGS += -D__DEBUGMODE
endif
LIBS +=-L/usr/lib/i386-linux-gnu -lm

-include .depend

all:depend TARGET

#sinclude $(SRC:%.c=%.d)
depend:
#	$(DEP):%.d:%.c
#	$(CC) $(CFLAGS) -MM -MP -MT $@ -MF $(@:%.o=%.d) $<
#	@set -e; rm -f .deptmp; \
	$(CC) -MM $(CFLAGS) $(SRC) $(LIBS) > .deptmp; \
	sed 's,\($*\)\.o[ :]*,\1.o .depend : ,g' < .deptmp > .depend; \
	rm -f .deptmp
#   $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
#   sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#   rm -f $@.$$$$

TARGET:$(OBJ)
#	$(LINK.c) $^ -o $@	
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)
	
$(warning  $(OBJ))
#$(OBJ):$(SRC)
$(OBJ):%.o:%.c
#	$(COMPILE.c) $(CFLAGS) $< -o $@
	$(CC) -c $(CFLAGS) $< -o $@ $(LIBS)
#	$(CC) -c $< -o $@

.PHONY: clean all
clean:
	@rm -f $(OBJ)
	@rm -f TARGET
	@rm -f .depend
