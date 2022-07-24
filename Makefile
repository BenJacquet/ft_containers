NAME_FT = ft_containers

LOG_DIR = logs

FT_OUTPUT = logs/ft.log

STD_OUTPUT = logs/std.log

DIFF_OUTPUT = logs/diff.log

NAME_STD = std_containers

SRCS_FT = main_ft.cpp

SRCS_STD = main_std.cpp

INCS_FT =  iterator/iterator.hpp\
		containers/vector.hpp\
		containers/stack.hpp\
		containers/map.hpp\
		utils/utils.hpp\
		utils/type_traits.hpp\
		utils/algorithm.hpp\
		utils/utility.hpp

INCS_STD =  utils/utils.hpp

OBJS_FT = $(SRCS_FT:.cpp=.o)

OBJS_STD = $(SRCS_STD:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Colors
_BLACK = $'\033[30m
_RED = s$'\033[31m
_GREEN = $'\033[32m
_YELLOW = $'\033[33m
_BLUE = $'\033[34m
_PURPLE = $'\033[35m
_CYAN = $'\033[36m
_GREY = $'\033[37m
_WHITE = $'\033[0m

test : clean all
	@echo "$(_CYAN)Creating the logs folder >>> $(_PURPLE)$(LOG_DIR)$(_WHITE)"
	mkdir logs
	@echo "$(_CYAN)Generating the test output of std containers >>> $(_PURPLE)$(STD_OUTPUT)$(_WHITE)"
	./$(NAME_STD) > $(STD_OUTPUT)
	@echo "$(_CYAN)Generating the test output of ft containers >>> $(_PURPLE)$(FT_OUTPUT)$(_WHITE)"
	./$(NAME_FT) > $(FT_OUTPUT)
	@echo "$(_CYAN)Generating the diff between std and ft containers >>> $(_PURPLE)$(DIFF_OUTPUT)$(_WHITE)"
	-diff $(FT_OUTPUT) $(STD_OUTPUT) > $(DIFF_OUTPUT) || /bin/true
	@echo "$(_CYAN)Checking if $(_PURPLE)$(DIFF_OUTPUT)$(_WHITE) $(_CYAN)is empty...$(_WHITE)"
	-sh check_diff.sh $(DIFF_OUTPUT) || /bin/true

all : $(NAME_FT) $(NAME_STD)

$(OBJS_FT) : $(INCS_FT)

$(OBJS_STD) : $(INCS_STD)
	@echo "$(_CYAN)Generating the std version of main.cpp >>> $(_PURPLE)$(SRCS_STD)$(_WHITE)"
	cp $(SRCS_FT) $(SRCS_STD)
	sed -i -e "s/ft::/std::/g" $(SRCS_STD)
	sed -i -e "s/main_ft.cpp /main_std.cpp/g" $(SRCS_STD)
	$(CXX) $(CXXFLAGS) -c $(SRCS_STD)

$(NAME_FT) : $(OBJS_FT)
	@echo "$(_CYAN)Generating the ft binary >>> $(_PURPLE)$(NAME_STD)$(_WHITE)"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_FT)

$(NAME_STD) : $(OBJS_STD)
	@echo "$(_CYAN)Generating the std binary >>> $(_PURPLE)$(NAME_STD)$(_WHITE)"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_STD)

clean :
	@echo "$(_CYAN)Cleaning all objects and output files$(_WHITE)"
	rm -rf $(OBJS_FT) $(OBJS_STD) $(LOG_DIR)

fclean : clean
	@echo "$(_CYAN)Cleaning the binaries and $(SRCS_STD)$(_WHITE)"
	rm -rf $(NAME_FT) $(NAME_STD) $(SRCS_STD)

re : fclean test

.PHONY : all clean fclean re