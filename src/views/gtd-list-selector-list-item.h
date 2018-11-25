/* gtd-list-selector-list-item.h
 *
 * Copyright (C) 2016 Georges Basile Stavracas Neto <georges.stavracas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GTD_LIST_SELECTOR_LIST_ITEM_H
#define GTD_LIST_SELECTOR_LIST_ITEM_H

#include "gtd-types.h"

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTD_TYPE_LIST_SELECTOR_LIST_ITEM (gtd_list_selector_list_item_get_type())

G_DECLARE_FINAL_TYPE (GtdListSelectorListItem, gtd_list_selector_list_item, GTD, LIST_SELECTOR_LIST_ITEM, GtkListBoxRow)

GtkWidget*           gtd_list_selector_list_item_new             (GtdTaskList        *list);

G_END_DECLS

#endif /* GTD_LIST_SELECTOR_LIST_ITEM_H */