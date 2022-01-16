PROG=main
ADITIONAL := timer.c 

CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk4`


${PROG}: ${PROG}.c ${ADITIONAL}
	${CC} -o ${PROG} ${PROG}.c ${ADITIONAL} ${CFLAGS}

clean:
	rm -f ${PROG}.o ${PROG} 
