CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRC     = client.c server.c utils.c
BONUS_SRC = bonus/client_bonus.c bonus/server_bonus.c
TARGETS = client server
BTARGETS = bonus/client_bonus bonus/server_bonus
BDIR    = bonus

all: $(TARGETS)

client: client.o utils.o
	$(CC) $(CFLAGS) utils.o $< -o $@

server: server.o utils.o
	$(CC) $(CFLAGS) utils.o $< -o $@

bonus: $(BTARGETS)

bonus/client_bonus: bonus/client_bonus.o
	$(CC) $(CFLAGS) $< -o $@

bonus/server_bonus: bonus/server_bonus.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f client.o server.o bonus/client_bonus.o bonus/server_bonus.o

fclean: clean
	rm -f $(TARGETS) $(BTARGETS)

re: fclean all

.PHONY: all clean fclean re bonus