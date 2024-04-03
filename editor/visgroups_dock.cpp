/**************************************************************************/
/*  visgroups_dialogue.cpp                                                */
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

#include "visgroups_dock.h"

#include "core/print_string.h"
#include "editor_node.h"
#include "editor_scale.h"
#include "editor_settings.h"
#include "editor/node_dock.h"
#include "plugins/script_editor_plugin.h"
#include "scene/gui/label.h"

//////////////////////////////////////////

struct _VisgroupsDockMethodInfoSort {
	_FORCE_INLINE_ bool operator()(const MethodInfo &a, const MethodInfo &b) const {
		return a.name < b.name;
	}
};

void VisgroupsDock::_filter_changed(const String &p_text) {
	update_tree();
}


void VisgroupsDock::_notification(int p_what) {
	if (p_what == EditorSettings::NOTIFICATION_EDITOR_SETTINGS_CHANGED) {
		update_tree();
	}
}

void VisgroupsDock::_bind_methods() {
	ClassDB::bind_method("_filter_changed", &VisgroupsDock::_filter_changed);
	ClassDB::bind_method("update_tree", &VisgroupsDock::update_tree);
}

void VisgroupsDock::update_tree() {
	tree->clear();
	TreeItem *root = tree->create_item();

	TreeItem *group_nodes = _add_visgroup_item("Nodes", "Node", root);
	TreeItem *group_2d = _add_visgroup_item("2D Nodes", "Node2D", root);
	TreeItem *group_3d = _add_visgroup_item("3D Nodes", "Spatial", root);
	TreeItem *group_ui = _add_visgroup_item("User Interface", "Control", root);
	TreeItem *group_user = _add_visgroup_item("User Defined", "Node3D", root);

	// NODES
	{
		List<String> classlist_anim;
		classlist_anim.push_back("AnimationPlayer");
		classlist_anim.push_back("AnimationTree");
		classlist_anim.push_back("AnimationTreePlayer");
		_add_visgroup_item("Animation", classlist_anim, group_nodes);

		List<String> classlist_audio;
		classlist_audio.push_back("AudioStreamPlayer");
		_add_visgroup_item("Audio", classlist_audio, group_nodes);

		List<String> classlist_nav;
		classlist_nav.push_back("NavigationAgent");
		classlist_nav.push_back("NavigationAgent2D");
		classlist_nav.push_back("NavigationObstacle");
		classlist_nav.push_back("NavigationObstacle2D");
		_add_visgroup_item("Navigation", classlist_nav, group_nodes);
	}
	// 2D NODES
	{
		_add_visgroup_item("Cameras", "Camera2D", group_2d);

		List<String> classlist2d_sprites;
		classlist2d_sprites.push_back("Sprite");
		classlist2d_sprites.push_back("AnimatedSprite");
		_add_visgroup_item("Sprites", classlist2d_sprites, group_2d);

		List<String> classlist2d_bodies;
		classlist2d_bodies.push_back("RigidBody2D");
		classlist2d_bodies.push_back("PhysicsBody2D"); // parent class
		_add_visgroup_item("Bodies", classlist2d_bodies, group_2d);

		_add_visgroup_item("Areas", "Area2D", group_2d);

		List<String> classlist2d_colliders;
		classlist2d_colliders.push_back("CollisionShape2D");
		classlist2d_colliders.push_back("CollisionPolygon2D");
		_add_visgroup_item("Colliders", classlist2d_colliders, group_2d);

		_add_visgroup_item("Tilemaps", "TileMap", group_2d);

		List<String> classlist2d_paths;
		classlist2d_paths.push_back("Path2D");
		classlist2d_paths.push_back("PathFollow2D");
		_add_visgroup_item("Paths", classlist2d_paths, group_2d);

		List<String> classlist2d_lights;
		classlist2d_lights.push_back("Light2D");
		classlist2d_lights.push_back("LightOccluder2D");
		_add_visgroup_item("Lights", classlist2d_lights, group_2d);

		List<String> classlist2d_particles;
		classlist2d_particles.push_back("Particles2D");
		classlist2d_particles.push_back("CPUParticles2D");
		_add_visgroup_item("Particles", classlist2d_particles, group_2d);

		_add_visgroup_item("Raycasts", "Raycast2D", group_2d);

		_add_visgroup_item("Ysorts", "Ysort", group_2d);
	}
	// 3D NODES
	{
	}
	// UI NODES
	{
		List<String> classlistui_fields;
		classlistui_fields.push_back("LineEdit");
		classlistui_fields.push_back("TextEdit");
		classlistui_fields.push_back("SpinBox");
		_add_visgroup_item("Fields", classlistui_fields, group_ui);

		List<String> classlistui_labels;
		classlistui_labels.push_back("Label");
		classlistui_labels.push_back("RichTextLabel");
		_add_visgroup_item("Labels", classlistui_labels, group_ui);
	}

}

// Add from single class
TreeItem* VisgroupsDock::_add_visgroup_item(const String p_name, const String &p_class, Object *p_parent) {
	List<String> nodeclasses;
	nodeclasses.push_back(p_class);
	return _add_visgroup_item(p_name, nodeclasses, p_parent);
}

// Add from list of classes
TreeItem* VisgroupsDock::_add_visgroup_item(const String p_name, const List<String> &p_classes, Object *p_parent) {

	TreeItem *parent = Object::cast_to<TreeItem>(p_parent);


	List<String> nodeclasses;
	int i = 0;
	while (i < p_classes.size()) {
		nodeclasses.push_back(p_classes[i]);
		i++;
	}

	GroupData groupdata = { EditorNode::get_singleton()->get_class_icon(p_classes[0]), nullptr, parent, nodeclasses, groups.size() };
	groups.insert(p_name, groupdata);

	// add tree item

	TreeItem *group = tree->create_item(parent, groups.size()-1);
	group->set_text(0, p_name);
	group->set_icon(0, EditorNode::get_singleton()->get_class_icon(p_classes[0]));
	group->add_button(0, get_icon("GuiVisibilityVisible", "EditorIcons"), BUTTON_VISIBILITY, false, TTR("Toggle Visibility"));
	group->set_collapsed(true);

	groupdata.item = group;
	return group;
}

void VisgroupsDock::_tree_button_pressed(Object *p_item, int p_column, int p_id) {

	TreeItem *item = Object::cast_to<TreeItem>(p_item);
	ERR_FAIL_COND(!item);

	NodePath np = item->get_metadata(0);

	Node *n = get_node(np);
	ERR_FAIL_COND(!n);

	// TODO: do something when pressed.
	int idx = item->get_button_by_id(0, BUTTON_VISIBILITY);
	ERR_FAIL_COND(idx == -1);
	item->set_button(0, idx, get_icon("GuiVisibilityHidden", "EditorIcons"));
}


VisgroupsDock::VisgroupsDock(EditorNode *p_editor) {
	editor = p_editor;
	set_name(TTR("Visgroups"));

	VBoxContainer *vbc = this;

	// Add visgroup filter
	search_box = memnew(LineEdit);
	search_box->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	search_box->set_placeholder(TTR("Filter Visgroups"));
	search_box->set_right_icon(get_icon("Search", "EditorIcons"));
	search_box->set_clear_button_enabled(true);
	search_box->connect("text_changed", this, "_filter_changed");
	vbc->add_child(search_box);

	tree = memnew(Tree);
	tree->set_columns(1);
	tree->set_select_mode(Tree::SELECT_ROW);
	tree->set_hide_root(true);
	vbc->add_child(tree);
	tree->set_v_size_flags(SIZE_EXPAND_FILL);
	tree->set_allow_rmb_select(true);

	tree->connect("button_pressed", this, "_tree_button_pressed");
	//tree->connect("item_selected", this, "_tree_item_selected");
	//tree->connect("item_activated", this, "_tree_item_activated");
	//tree->connect("item_rmb_selected", this, "_rmb_pressed");

	add_constant_override("separation", 3 * EDSCALE);

	update_tree();
}

VisgroupsDock::~VisgroupsDock() {
}
