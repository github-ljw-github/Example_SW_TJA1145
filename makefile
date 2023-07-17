CFLAGS :=
SRCFILES :=

SRCFILES+= TJA1145FD_ApplHint.c NXP_TJA1145FD_Functions.c TJA1145FD_Application_Specific_Functions.c  uC_Specific_Function.c
# CFLAGS+=
CFLAGS+=-I.

OBJFILES+=$(SRCFILES:.c=.o)

all:$(OBJFILES)
	@echo done

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJFILES)
