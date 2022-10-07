##
## EPITECH PROJECT, 2021
## nanotekspice
## File description:
## Makefile
##

SHELL	=	/bin/sh
CXX	=	g++
RM	= 	rm -rf

MAIN	=	src/main.cpp

SRC	=	src/Reception.cpp	\
		src/Process.cpp		\
		src/Kitchen.cpp		\
		src/Errors.cpp		\
		src/Prompt.cpp		\
		src/Utils.cpp		\
		src/Order.cpp		\
		src/Pizza.cpp		\
		src/Cook.cpp

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

LDFLAGS	=
CFLAGS	=	-Wall -Wextra
CPPFLAGS=	-I include

OK	=	\e[32m
RED	=	\e[91m
END	=	\e[0m

T_PRUNE	=

SRC_T	=	tests/unit_tests.cpp

NAME	=	plazza
PHONY	:=	all
DEBUG	=	0

define center_text
	echo -e "$(OK)>>>>\t$1$(END)"
endef

ifeq ($(DEBUG), 1)
	LDFLAGS += -fsanitize=address
	CFLAGS += -g -fsanitize=address
endif

all: $(NAME)

PHONY += $(NAME)
$(NAME): $(SRC) $(MAIN)
	@$(call center_text,$@)
	$(eval OBJ += $(MAIN:.cpp=.o))
	@$(MAKE) -s $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) && \
	echo -e "$(OK)[DONE]\t$($@)$(END)" || \
	echo -e "$(RED)[FAILURE]\t$($@)$(END)"

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< && \
	echo -e "$(OK)[OK]\t$<$(END)" || \
	echo -e "$(RED)[FAILURE]\t$<$(END)"

PHONY += rm_prompt
rm_prompt:
	@$(call center_text,Clean)

PHONY += clean
clean: rm_prompt
	@$(RM) $(OBJ) $(MAIN:.cpp=.o)
	@echo -e "$(RED)$(NAME) : Removed object files.$(END)"

PHONY += fclean
fclean: clean rm_prompt
	@$(RM) plazza
	@$(RM) tmp
	@echo -e "$(RED)$(NAME) : Removed plazza.$(END)"

PHONY += fltclean
fltclean: fclean

PHONY += re
re: fltclean all

.PHONY: $(PHONY)
