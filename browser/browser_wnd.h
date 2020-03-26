#pragma once

#include <gdk/gdk.h>
#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include "html_loader.h"

class Browser_wnd : public Gtk::Window
{
public:
    Browser_wnd();
    ~Browser_wnd() = default;

    friend void web_view_load_changed(WebKitWebView* web_view, WebKitLoadEvent load_event, gpointer data);
private:
    void on_go_clicked();
    bool on_address_key_press(GdkEventKey* event);
protected:
    WebKitWebView*      m_web_view;
    Gtk::Widget*        m_html;
    Html_loader         m_html_loader;
    Gtk::Entry			m_address_bar;
    Gtk::Button			m_go_button;
    Gtk::VBox			m_vbox;
    Gtk::HBox			m_hbox;
    Gtk::ScrolledWindow m_scrolled_wnd;
};