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
//        Fl_Menu_Item menuitems[] = {
//                {"&Game", 0, 0, 0, FL_SUBMENU},
//                {"&Restart", 0, (Fl_Callback *)restart_cb, 0},
//                {0},
//                {0}
//
//        };
//
//        // instantiate the menubar
//        this->copy(menuitems);

        this->add("Options/One",   0, 0,(void*)this, FL_MENU_TOGGLE);
        this->add("Options/Two",   0, 0,(void*)this, FL_MENU_TOGGLE);
        this->add("Options/Three", 0, 0,(void*)this, FL_MENU_TOGGLE);
        this->activate();
    }

private:
    static void restart_cb(Fl_Widget*, void* v)
    {
        // maybe modified later to a more proper page
        std::cout << "v: " << v << std::endl;
        setStage(INITIAL_PAGE);
        return;
    }
};


#endif //RENJU_MENUBAR_H
