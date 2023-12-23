CC         	= gcc
CFLAGS		= -Wall -I/usr/include -I/usr/include/x86_64-linux-gnu -O0 -g
LDFLAGS		= -lSDL2main -lSDL2 -lGL -lSDL2_mixer -lSOIL -lSDL2_ttf -lm


DIR_SRC     = ./src
DIR_BUILD   = ./bin

TARGET      = game


SRCS        = $(wildcard $(DIR_SRC)/*.c)
OBJS        = $(filter-out $(DIR_BUILD)/main.o, $(patsubst $(DIR_SRC)/%.c, $(DIR_BUILD)/%.o, $(SRCS)))

# WASM flags
#CC          = emcc
#LDFLAGS     = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s USE_GLFW=3 --preload-file assets ./libs/SOIL.so
#DIR_BUILD   = ./webbin
#TARGET      = game.html

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) $(DIR_BUILD)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@cp ./$(TARGET) release
	@cp -r ./assets release

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: clean


clean:
	rm -rf $(DIR_BUILD)/*.o
