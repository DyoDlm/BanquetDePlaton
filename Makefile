NAME = philosophers

SDIR = srcs
HDIR = headers
TD1R = srcs/utils
TD3R = srcs/routines
TD4R = srcs/exit
ODIR = objs

CFLAGS = -Wall -Wextra -Werror -I$(HDIR) -pthread
DFLAGS = -fsanitize=address -g

SRCS = $(wildcard $(SDIR)/*.c) $(wildcard $(TD1R)/*.c) \
       $(wildcard $(TD3R)/*.c) \
       $(wildcard $(TD4R)/*.c) main.c

OBJS = $(addprefix $(ODIR)/, $(notdir  $(SRCS:.c=.o)))

all: $(NAME)
	@echo "Doing it *zbra*"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@
	@echo "VOILA ! Compilation faite."

$(ODIR)/%.o: $(SDIR)/%.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Placement des sources."

$(ODIR)/%.o: $(TD1R)/%.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Placement de tools 1."

$(ODIR)/%.o: $(TD2R)/%.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Placement de tools 2."

$(ODIR)/%.o: $(TD3R)/%.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Placement de tools 3."

$(ODIR)/%.o: $(TD4R)/%.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Placement de tools 4."

$(ODIR)/%.o: %.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@rm -rf $(ODIR)
	@echo "Nettoyage des fichiers objets effectué."

fclean: clean
	@rm -rf $(NAME)
	@echo "Nettoyage complet effectué."

re: fclean all

dbug: CLFAGS += $(DFLAGS)
dbug: re

.PHONY: all clean fclean re dbug
