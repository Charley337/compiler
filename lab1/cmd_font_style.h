#ifndef __CMD_FONT_STYLE__H__
#define __CMD_FONT_STYLE__H__

// 先设置字体颜色，后设置其他样式，否则其他样式会被清空

#define RESET_STYLE "\033[0m"

#define FONT_HIGHLIGHT "\033[1m"
#define FONT_UNDERLINE "\033[4m"
#define FONT_GLITTER "\033[5m"

#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_PURPLE "\033[45m"
#define BG_DEEPGREEN "\033[46m"
#define BG_WHITE "\033[47m"

#define FONT_BLACK "\033[;30m"
#define FONT_RED "\033[;31m"
#define FONT_GREEN "\033[;32m"
#define FONT_YELLOW "\033[;33m"
#define FONT_BLUE "\033[;34m"
#define FONT_PURPLE "\033[;35m"
#define FONT_DEEPGREEN "\033[;36m"
#define FONT_WHITE "\033[;37m"

#endif