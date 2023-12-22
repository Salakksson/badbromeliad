CC         		= gcc
CFLAGS        	= -Wall $(shell /home/been/Downloads/SDL2-2.28.5/x86_64-w64-mingw32/bin/sdl2-config --cflags --prefix=/usr/x86_64-w64-mingw32) -I/usr/include
LDFLAGS      	= -lSDL2main -lSDL2 -lGL -lSDL2_mixer -lmpg123 -lGLU -lGLEW -lSOIL -lSDL2_ttf -lm


DIR_SRC     = ./src
DIR_BUILD    = ./bin

TARGET         = game


EXE =

# Windows compilation flags

CC=x86_64-w64-mingw32-gcc
CFLAGS += -DWIN32
LDFLAGS      = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_mixer -lmpg123 -lglew32 -lglu32 -lSOIL -lSDL2_ttf -lm -mwindows
EXE += .exe


SRCS         = $(wildcard $(DIR_SRC)/*.c)
OBJS         = $(filter-out $(DIR_BUILD)/main.o, $(patsubst $(DIR_SRC)/%.c, $(DIR_BUILD)/%.o, $(SRCS)))

$(TARGET)$(EXE): $(OBJS) $(DIR_BUILD)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(DIR_BUILD)/*.o $(DIR_BUILD)/$(TARGET)$(EXE)