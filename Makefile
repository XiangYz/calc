ARM=0

ifeq ($(ARM),1)
COM_PREFIX=arm-linux-
APP_SUFFIX=_arm
else
COM_PREFIX=
APP_SUFFIX=
endif


myCalc${APP_SUFFIX} : Main.o Stack_Calc.o Stack_Trans.o
	${COM_PREFIX}gcc $^ --static -lm -o $@
Main.o : Main.c
	${COM_PREFIX}gcc -c -o $@ $^
Stack_Calc.o : Stack_Calc.c
	${COM_PREFIX}gcc -c -o $@ $^
Stack_Trans.o : Stack_Trans.c
	${COM_PREFIX}gcc -c -o $@ $^
	
.PHONY:clean
clean :
	rm -f *.o
