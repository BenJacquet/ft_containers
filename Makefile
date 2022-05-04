NAME_FT = ft_containers

FT_OUTPUT = ft.log

STD_OUTPUT = std.log

DIFF_OUTPUT = diff.log

NAME_STD = std_containers

SRCS_FT = main_ft.cpp

SRCS_STD = main_std.cpp

INCS_FT =  iterator/iterator.hpp\
		iterator/iterator_traits.hpp\
		iterator/bidirectional_iterator.hpp\
		iterator/random_access_iterator.hpp\
		vector/vector.hpp\
		utils/utils.hpp\
		utils/type_traits.hpp

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

test : all
	@echo "$(_BLUE)generating the test output of ft containers >>> $(_PURPLE)ft.log$(_WHITE)"
	@./$(NAME_FT) > $(FT_OUTPUT)
	@echo "$(_BLUE)generating the test output of std containers >>> $(_PURPLE)std.log$(_WHITE)"
	@./$(NAME_STD) > $(STD_OUTPUT)
	@echo "$(_BLUE)generating the difference between them >>> $(_PURPLE)diff.log$(_WHITE)"
	@diff $(FT_OUTPUT) $(STD_OUTPUT) > $(DIFF_OUTPUT)
	@diff -i ft.log std.log > diff.log || /bin/true
	@echo "$(_GREEN)all good!$(_WHITE)"

all : $(NAME_FT) $(NAME_STD)

$(OBJS_FT) : $(INCS_FT)

$(OBJS_STD) : $(INCS_STD)
	@echo "$(_CYAN)generating the std version of main.cpp >>> $(_PURPLE)$(SRCS_STD)$(_WHITE)"
	cp $(SRCS_FT) $(SRCS_STD)
	sed -i -e "s/ft::vector/std::vector/g" $(SRCS_STD)
	sed -i -e "s/main_ft.cpp /main_std.cpp/g" $(SRCS_STD)
	$(CXX) $(CXXFLAGS) -c $(SRCS_STD)

$(NAME_FT) : $(OBJS_FT)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_FT)

$(NAME_STD) : $(OBJS_STD)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_STD)

clean :
	rm -rf $(OBJS_FT) $(OBJS_STD) $(FT_OUTPUT) $(STD_OUTPUT) $(DIFF_OUTPUT)

fclean : clean
	rm -rf $(NAME_FT) $(NAME_STD) $(SRCS_STD)

re : fclean test

.PHONY : all clean fclean re