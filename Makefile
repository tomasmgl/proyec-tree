# Makefile Complejo
# Compilacion de bilioteca math.h
LIBS = -lm

# Compilador
CC = g++

# Banderas del compilador
# Si la variable mode esta vacia se establece el modo de compilacion
# release
ifeq ($(mode),debug)
	CFLAGS = -g -Wall -DDEBUG
	TARGET = RUN_DEBUG
else
	mode = release
	CFLAGS = -g
	TARGET = RUN
endif

# Incluye los archivos .o y .c que estan en el directorio actual
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

# Incluye los archivos .h que estan en el directorio actual
HEADERS = $(wildcard *.hpp)

# Palabras que podrian se el nombre de un programa
.PHONY: default all clean

# Compilacion por defecto
all: information default
default: $(TARGET)

# Compila automaticamente solo archivos fuente que se han Modificado
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Preserva archivos intermedios
.PRECIOUS: $(TARGET) $(OBJECTS)

# Enlaza objetos y crea el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

# Borra arhivos .o
clean:
	-rm -rf *.o $(TARGET)

# Borrar archivos .o y el ejecutable
cleanall: clean
	-rm -rf $(TARGET)

information:
ifneq ($(mode),release)
ifneq ($(mode),debug)
	@echo "Modo de compilacion invalido"
	@echo "Por favor use 'make mode=realease' o 'make mode=debug'"
	@exit 1
endif
endif
#	@echo "Compilando en modo "$(mode)""
#	@echo ".........................."
