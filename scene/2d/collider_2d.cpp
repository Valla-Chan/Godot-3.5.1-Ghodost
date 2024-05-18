/**************************************************************************/
/*  collision_polygon_2d.cpp                                              */
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

#include "collider_2d.h"


void Collider2D::_update_in_shape_owner(bool p_xform_only) {
	parent->shape_owner_set_transform(owner_id, get_transform());
	if (p_xform_only) {
		return;
	}
	parent->shape_owner_set_disabled(owner_id, disabled);
	parent->shape_owner_set_one_way_collision(owner_id, one_way_collision);
	parent->shape_owner_set_one_way_collision_margin(owner_id, one_way_collision_margin);
}

void Collider2D::set_disabled(bool p_disabled) {
	disabled = p_disabled;
	update();
	if (parent) {
		parent->shape_owner_set_disabled(owner_id, p_disabled);
	}
}

bool Collider2D::is_disabled() const {
	return disabled;
}

void Collider2D::set_one_way_collision(bool p_enable) {
	one_way_collision = p_enable;
	update();
	if (parent) {
		parent->shape_owner_set_one_way_collision(owner_id, p_enable);
	}
	update_configuration_warning();
}

bool Collider2D::is_one_way_collision_enabled() const {
	return one_way_collision;
}

void Collider2D::set_one_way_collision_margin(float p_margin) {
	one_way_collision_margin = p_margin;
	if (parent) {
		parent->shape_owner_set_one_way_collision_margin(owner_id, one_way_collision_margin);
	}
}

float Collider2D::get_one_way_collision_margin() const {
	return one_way_collision_margin;
}

// VALLA EDITS
void Collider2D::set_use_override_color(const bool p_enable) {
	if (use_override_color == p_enable) {
		return;
	}

	use_override_color = p_enable;
	update();
}
bool Collider2D::get_use_override_color() const {
	return use_override_color;
}

void Collider2D::set_override_color(const Color p_override_color) {
	if (override_color == p_override_color) {
		return;
	}

	override_color = p_override_color;
	update();
}
Color Collider2D::get_override_color() const {
	return override_color;
}
//

void Collider2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_disabled", "disabled"), &Collider2D::set_disabled);
	ClassDB::bind_method(D_METHOD("is_disabled"), &Collider2D::is_disabled);
	ClassDB::bind_method(D_METHOD("set_one_way_collision", "enabled"), &Collider2D::set_one_way_collision);
	ClassDB::bind_method(D_METHOD("is_one_way_collision_enabled"), &Collider2D::is_one_way_collision_enabled);
	ClassDB::bind_method(D_METHOD("set_one_way_collision_margin", "margin"), &Collider2D::set_one_way_collision_margin);
	ClassDB::bind_method(D_METHOD("get_one_way_collision_margin"), &Collider2D::get_one_way_collision_margin);

	ClassDB::bind_method(D_METHOD("set_use_override_color"), &Collider2D::set_use_override_color);
	ClassDB::bind_method(D_METHOD("get_use_override_color"), &Collider2D::get_use_override_color);
	ClassDB::bind_method(D_METHOD("set_override_color"), &Collider2D::set_override_color);
	ClassDB::bind_method(D_METHOD("get_override_color"), &Collider2D::get_override_color);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "disabled"), "set_disabled", "is_disabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "one_way_collision"), "set_one_way_collision", "is_one_way_collision_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "one_way_collision_margin", PROPERTY_HINT_RANGE, "0,128,0.1"), "set_one_way_collision_margin", "get_one_way_collision_margin");
}

Collider2D::Collider2D() {
	set_notify_local_transform(true);
	parent = nullptr;
	owner_id = 0;
	disabled = false;
	one_way_collision = false;
	one_way_collision_margin = 1.0;
	use_override_color = false;
	override_color = Color(1.0, 1.0, 1.0, 0.35);
}
