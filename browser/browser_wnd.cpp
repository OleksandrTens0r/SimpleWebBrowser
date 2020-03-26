#include "browser_wnd.h"
#include <iostream>

void web_view_load_changed(WebKitWebView* web_view, WebKitLoadEvent load_event, gpointer data)
{
    auto browser = static_cast<Browser_wnd*>(data);
    browser->m_address_bar.set_text(webkit_web_view_get_uri(web_view));
}

Browser_wnd::Browser_wnd() : m_go_button("_Go", true)
{
    set_title("browser");
    add(m_vbox);
    m_vbox.show();

    m_vbox.pack_start(m_hbox, Gtk::PACK_SHRINK);
    m_hbox.show();

    m_hbox.pack_start(m_address_bar, Gtk::PACK_EXPAND_WIDGET);
    m_address_bar.show();
    m_address_bar.set_text("https://doc.qt.io/qt-5/qt5-intro.html#qt-everywhere-on-mobile");

    m_address_bar.add_events(Gdk::KEY_PRESS_MASK);
    m_address_bar.signal_key_press_event().connect( sigc::mem_fun(*this, &Browser_wnd::on_address_key_press), false );
    m_go_button.signal_clicked().connect( sigc::mem_fun(*this, &Browser_wnd::on_go_clicked) );

    m_hbox.pack_start(m_go_button, Gtk::PACK_SHRINK);
    m_go_button.show();

    m_vbox.pack_start(m_scrolled_wnd, Gtk::PACK_EXPAND_WIDGET);
    m_scrolled_wnd.show();

    m_web_view =  WEBKIT_WEB_VIEW( webkit_web_view_new() );
    g_signal_connect(m_web_view, "load_changed", G_CALLBACK(web_view_load_changed), this);

    m_html = Glib::wrap( GTK_WIDGET( m_web_view ) );

    m_scrolled_wnd.add(*m_html);
    m_html->show();

    set_default_size(800, 600);
}

void Browser_wnd::on_go_clicked()
{
    std::string url = m_address_bar.get_text();
    m_html_loader.load_file(url);
    webkit_web_view_load_html(m_web_view, m_html_loader.load_file(url).c_str(), url.c_str());
}

bool Browser_wnd::on_address_key_press(GdkEventKey* event)
{
    if(event->keyval == GDK_KEY_Return)
    {
        m_address_bar.select_region(0, -1);
        on_go_clicked();
        return true;
    }

    return false;
}
