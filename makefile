CC         = gcc
CFLAGS        = -Wall -I/usr/include
LDFLAGS      = -lSDL2main -lSDL2 -lGL -lSDL2_mixer -lSOIL -lSDL2_ttf -lm


DIR_SRC     = ./src
DIR_BUILD    = ./bin

TARGET         = game

SRCS         = $(wildcard $(DIR_SRC)/*.c)
OBJS         = $(filter-out $(DIR_BUILD)/main.o, $(patsubst $(DIR_SRC)/%.c, $(DIR_BUILD)/%.o, $(SRCS)))

$(TARGET): $(OBJS) $(DIR_BUILD)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@cp ./game release
	@cp -r ./assets release

.PHONY: clean

clean:
	rm -rf $(DIR_BUILD)/*.o $(DIR_BUILD)/$(TARGET)