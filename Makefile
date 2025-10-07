CC      ?= gcc
CFLAGS  += -shared -fPIC
LDFLAGS += -lXrandr -lX11 -ldl

SONAME   = XRRGetOutputInfoSafe.so

SRC      = XRRGetOutputInfoSafe.c

OBJ      = ${SRC:.c=.o}

all: ${SONAME}

.c.o:
	${CC} -c ${CFLAGS} $<

${SONAME}: ${OBJ}
	${CC} -o ${SONAME} ${OBJ} ${CFLAGS} ${LDFLAGS}

clean:
	rm -f ${OBJ} ${SONAME}

.PHONY: all clean
