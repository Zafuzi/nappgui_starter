/*
 * NAppGUI-v1.1.1.2372 Cross-platform C SDK
 * © 2015-2020 Francisco Garcia Collado
 * All rights reserved
 * https://nappgui.com/en/legal/eula.html
 *
 * File: popup.h
 * https://nappgui.com/en/gui/popup.html
 *
 */

/* Pop-up button */

#include "gui.hxx"

__EXTERN_C

PopUp *popup_create(void);

void popup_OnSelect(PopUp *popup, Listener *listener);

void popup_tooltip(PopUp *popup, const char_t *text);

void popup_add_elem(PopUp *popup, const char_t *text, const Image *image);

void popup_set_elem(PopUp *popup, const uint32_t index, const char_t *text, const Image *image);

void popup_list_height(PopUp *popup, const uint32_t elems);

void popup_selected(PopUp *popup, const uint32_t index);

uint32_t popup_get_selected(const PopUp *popup);

__END_C
