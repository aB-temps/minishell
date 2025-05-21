#ifndef TEXT_FORMATTING_H
# define TEXT_FORMATTING_H

#include <stdio.h>

// FOREGROUND COLORS
# define FG_BLACK "\e[30m"
# define FG_RED "\e[31m"
# define FG_GREEN "\e[32m"
# define FG_YELLOW "\e[33m"
# define FG_BLUE "\e[34m"
# define FG_MAGENTA "\e[35m"
# define FG_CYAN "\e[36m"

// BACKGROUND COLORS
# define BG_BLACK "\e[40m"
# define BG_RED "\e[41m"
# define BG_GREEN "\e[42m"
# define BG_YELLOW "\e[43m"
# define BG_BLUE "\e[44m"
# define BG_MAGENTA "\e[45m"
# define BG_CYAN "\e[46m"

// FORMAT
# define BOLD "\e[1m"
# define DIM "\e[2m"
# define UNDL "\e[4m"

// RESET
# define R_ALL "\e[0m"
# define R_BOLD "\e[21m"
# define R_DIM "\e[22m"
# define R_UL "\e[24m"
# define R_FG "\e[39m"
# define R_BG "\e[49m"

#endif