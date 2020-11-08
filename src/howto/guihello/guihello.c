/* NAppGUI GUI Basics */
    
#include "nappgui.h"
#include "res.h"
#include "labels.h"
#include "buttons.h"
#include "sliders.h"
#include "form.h"
#include "popcom.h"
#include "textviews.h"
#include "baslayout.h"
#include "sublayout.h"
#include "subpanel.h"
#include "multilayout.h"
#include "scrollpanel.h"

typedef struct _app_t App;

struct _app_t
{
    Window *window;
    Layout *layout;
};

/*---------------------------------------------------------------------------*/

static void i_set_panel(Layout *layout, const uint32_t index)
{
    Panel *panel = NULL;
    switch (index) {
    case 0:
        panel = labels_single_line();
        break;
    case 1:
        panel = labels_multi_line();
        break;
    case 2:
        panel = labels_mouse_over();
        break;
    case 3:
        panel = buttons_basics();
        break;
    case 4:
        panel = popup_combo();
        break;
    case 5:
        panel = form_basic();
        break;
    case 6:
        panel = sliders();
        break;
    case 7:
        panel = textviews();
        break;
    case 8:
        panel = basic_layout();
        break;
    case 9:
        panel = sublayouts();
        break;
    case 10:
        panel = subpanels();
        break;
    case 11:
        panel = multilayouts();
        break;
    case 12:
        panel = scrollpanel();
        break;
    }

    layout_panel(layout, panel, 1, 0);
}

/*---------------------------------------------------------------------------*/

static void i_OnSelect(App *app, Event *e)
{
    const EvButton *p = event_params(e, EvButton);
    if (p->index != UINT32_MAX)
    {
        i_set_panel(app->layout, p->index);
        window_update(app->window);
    }
}

/*---------------------------------------------------------------------------*/

static Panel *i_panel(App *app)
{
    Panel *panel = panel_create();
    Layout *layout = layout_create(2, 1);
    ListBox *list = listbox_create();
    listbox_size(list, s2df(180, 256));
    listbox_add_elem(list, "Labels single line", NULL);
    listbox_add_elem(list, "Labels multi line", NULL);
    listbox_add_elem(list, "Labels mouse sensitive", NULL);
    listbox_add_elem(list, "Buttons", NULL);
    listbox_add_elem(list, "PopUp Combo", NULL);
    listbox_add_elem(list, "Form", NULL);
    listbox_add_elem(list, "Sliders", NULL);
    listbox_add_elem(list, "TextViews", NULL);
    listbox_add_elem(list, "Basic Layout", NULL);
    listbox_add_elem(list, "SubLayouts", NULL);
    listbox_add_elem(list, "Subpanels", NULL);
    listbox_add_elem(list, "Multi-Layouts", NULL);
    listbox_add_elem(list, "Scroll panel", NULL);
    listbox_selected(list, 0);
    listbox_OnSelect(list, listener(app, i_OnSelect, App));
    layout_listbox(layout, list, 0, 0);
    i_set_panel(layout, 0);
    panel_layout(panel, layout);
    layout_valign(layout, 0, 0, ekTOP);
    layout_valign(layout, 1, 0, ekTOP);
    layout_margin(layout, 10);
    layout_hmargin(layout, 0, 10);
    app->layout = layout;
    return panel;
}

/*---------------------------------------------------------------------------*/

static Window *i_window(App *app)
{
    Panel *panel = i_panel(app);
    Window *window = window_create(ekWNSTD, &panel);
    window_title(window, "NAppGUI GUI Basics");
    return window;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App *app, Event *e)
{
    unref(app);
    unref(e);
    osapp_finish();
}

/*---------------------------------------------------------------------------*/

static App *i_create(void)
{
    App *app = heap_new(App);
    gui_respack(res_respack);
    gui_language("");
    app->window = i_window(app);
    window_origin(app->window, v2df(500.f, 200.f));
    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_show(app->window);
    return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    window_destroy(&(*app)->window);
    heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/

#include "osmain.h"
osmain(i_create, i_destroy, "", App)
