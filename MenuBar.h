//
// Created by Fenghe Xu on 2019-06-11.
//

#ifndef RENJU_MENUBAR_H
#define RENJU_MENUBAR_H

#include "GUI.h"



class MenuBar : Fl_Menu_Bar {
public:

    MenuBar(int width)
            :
            Fl_Menu_Bar(0, 0, width, 30)
            {
        // init the menu bar
        Fl_Menu_Item menuitems[] = {
                {"&Restart", FL_CTRL + 'r', 0, 0},
                {0}
        };

        // instantiate the menubar
        this->copy(menuitems);
    }

private:
//    void restart_cb(void)
//    {
//        return;
//    }
};


#endif //RENJU_MENUBAR_H
