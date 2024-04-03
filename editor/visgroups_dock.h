/**************************************************************************/
/*  connections_dialog.h                                                  */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

/**
@author Juan Linietsky <reduzio@gmail.com>
*/

#ifndef VISGROUP_DOCK_H
#define VISGROUP_DOCK_H

#include "core/undo_redo.h"
#include "editor/editor_inspector.h"
#include "editor/scene_tree_editor.h"
#include "scene/gui/button.h"
#include "scene/gui/check_button.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/tree.h"

class PopupMenu;

//////////////////////////////////////////
class VisgroupsDock : public VBoxContainer {
	GDCLASS(VisgroupsDock, VBoxContainer);

	enum {
		BUTTON_VISIBILITY = 0,
	};

	Tree *tree;
	EditorNode *editor;

	LineEdit *search_box;

	void _filter_changed(const String &p_text);

	struct GroupData {
		Ref<Texture> icon;
		TreeItem *item;
		TreeItem *parent;
		List<String> classes;
		int index;
	};
	TreeItem* _add_visgroup_item(const String p_name, const String &p_class, Object *p_parent);
	TreeItem* _add_visgroup_item(const String p_name, const List<String> &p_classes, Object *p_parent);

	// map a group name to a list of class strings
	Map<String, GroupData> groups;

protected:
	void _notification(int p_what);
	static void _bind_methods();
	void _tree_button_pressed(Object *p_item, int p_column, int p_id);

public:
	void update_tree();

	VisgroupsDock(EditorNode *p_editor = nullptr);
	~VisgroupsDock();
};

#endif // CONNECTIONS_DIALOG_H
