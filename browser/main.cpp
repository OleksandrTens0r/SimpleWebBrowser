#include <gtkmm.h>
#include "browser_wnd.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "browser.apriorit");
    Browser_wnd win;
    return app->run(win);
}
