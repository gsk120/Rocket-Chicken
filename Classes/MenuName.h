#ifndef __MENU_NAME_H__
#define __MENU_NAME_H__
#define COUNT 4
enum
{
    MENU_START = 0,
    MENU_OPTION,
    MENU_HELP,
    MENU_EXIT,
};

const std::string g_aTestNames[COUNT] = {
    "Start",
    "Option",
    "Help",
    "Exit",
};

#endif