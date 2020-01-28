/* NAppGUI Hello World */

#include "nappgui.h"
#include "ddraw.h"

typedef struct _app_t App;

struct _app_t
{
    Window *window;
    View *view;
    uint32_t face[6];
};

/*---------------------------------------------------------------------------*/

static void i_OnRedraw(App *app, Event *e)
{
    const EvDraw *params = event_params(e, EvDraw);
    color_t green = color_rgb(102, 153, 26);
    real32_t w = params->width / 3;
    real32_t h = params->height / 2;
    real32_t p = .15f;
    real32_t c = .15f;
    real32_t r = .35f;
    draw_clear(params->ctx, green);
    die_draw(params->ctx, 0.f, 0.f, w, h, p, c, r, app->face[0]);
    die_draw(params->ctx, w, 0.f, w, h, p, c, r, app->face[1]);
    die_draw(params->ctx, 2 * w, 0.f, w, h, p, c, r, app->face[2]);
    die_draw(params->ctx, 0.f, h, w, h, p, c, r, app->face[3]);
    die_draw(params->ctx, w, h, w, h, p, c, r, app->face[4]);
    die_draw(params->ctx, 2 * w, h, w, h, p, c, r, app->face[5]);
}

/*---------------------------------------------------------------------------*/

static void i_OnMoved(App *app, Event *e)
{
    bmem_shuffle_n(app->face, 6, uint32_t);
    view_update(app->view);
    unref(e);
}

/*---------------------------------------------------------------------------*/

static Layout *i_layout(App *app)
{
    Layout *layout = layout_create(1, 2);
    View *view = view_create(0);
    Slider *slider = slider_create();
    view_OnDraw(view, listener(app, i_OnRedraw, App));
    slider_OnMoved(slider, listener(app, i_OnMoved, App));
    layout_view(layout, view, 0, 0);
    layout_slider(layout, slider, 0, 1);
    layout_hsize(layout, 0, 600);
    layout_vsize(layout, 0, 400);
    layout_margin(layout, 10);
    layout_margin(layout, 10);
    layout_vmargin(layout, 0, 10);
    app->view = view;
    return layout;
}

/*---------------------------------------------------------------------------*/

static Panel *i_panel(App *app)
{
    Panel *panel = panel_create();
    Layout *layout = i_layout(app);
    panel_layout(panel, layout);
    return panel;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}

/*---------------------------------------------------------------------------*/

static App *i_create(void)
{
    App *app = heap_new0(App);
    Panel *panel = i_panel(app);    
    app->face[0] = 1;
    app->face[1] = 2;
    app->face[2] = 3;
    app->face[3] = 4;
    app->face[4] = 5;
    app->face[5] = 6;
    app->window = window_create(ekWNSTD, &panel);
    window_title(app->window, "Dice");
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
