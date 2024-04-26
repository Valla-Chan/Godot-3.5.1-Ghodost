/**************************************************************************/
/*  sprite.cpp                                                            */
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

#include "sprite_base.h"
#include "core/core_string_names.h"
#include "core/os/os.h"
#include "scene/main/viewport.h"
#include "scene/scene_string_names.h"

#ifdef TOOLS_ENABLED
Dictionary SpriteBase::_edit_get_state() const {
	Dictionary state = Node2D::_edit_get_state();
	state["offset"] = offset;
	return state;
}

void SpriteBase::_edit_set_state(const Dictionary &p_state) {
	Node2D::_edit_set_state(p_state);
	set_offset(p_state["offset"]);
}

void SpriteBase::_edit_set_pivot(const Point2 &p_pivot) {
	set_offset(get_offset() - p_pivot);
	set_position(get_transform().xform(p_pivot));
}

Point2 SpriteBase::_edit_get_pivot() const {
	return Vector2();
}

bool SpriteBase::_edit_use_pivot() const {
	return true;
}

bool SpriteBase::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	return is_pixel_opaque(p_point);
}

#endif


void SpriteBase::set_force_pixel_snapping(bool p_snapping) {
	force_pixel_snapping = p_snapping;
}

bool SpriteBase::get_force_pixel_snapping() const {
	return force_pixel_snapping;
}

void SpriteBase::set_centered(bool p_center) {
	centered = p_center;
	update();
	item_rect_changed();
}

bool SpriteBase::is_centered() const {
	return centered;
}

void SpriteBase::set_basealigned(bool p_basealign) {
	basealigned = p_basealign;
	update();
	item_rect_changed();
}

bool SpriteBase::is_basealigned() const {
	return basealigned;
}

void SpriteBase::set_offset(const Point2 &p_offset) {
	offset = p_offset;
	update();
	item_rect_changed();
	_change_notify("offset");
}
Point2 SpriteBase::get_offset() const {
	return offset;
}

void SpriteBase::set_flip_h(bool p_flip) {
	hflip = p_flip;
	update();
}
bool SpriteBase::is_flipped_h() const {
	return hflip;
}

void SpriteBase::set_flip_v(bool p_flip) {
	vflip = p_flip;
	update();
}
bool SpriteBase::is_flipped_v() const {
	return vflip;
}


bool SpriteBase::is_pixel_opaque(const Point2 &p_point) const {
	return true;
}


void SpriteBase::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_force_pixel_snapping", "snap"), &SpriteBase::set_force_pixel_snapping);
	ClassDB::bind_method(D_METHOD("get_force_pixel_snapping"), &SpriteBase::get_force_pixel_snapping);

	ClassDB::bind_method(D_METHOD("set_centered", "centered"), &SpriteBase::set_centered);
	ClassDB::bind_method(D_METHOD("is_centered"), &SpriteBase::is_centered);

	ClassDB::bind_method(D_METHOD("set_basealigned", "basealigned"), &SpriteBase::set_basealigned);
	ClassDB::bind_method(D_METHOD("is_basealigned"), &SpriteBase::is_basealigned);

	ClassDB::bind_method(D_METHOD("set_offset", "offset"), &SpriteBase::set_offset);
	ClassDB::bind_method(D_METHOD("get_offset"), &SpriteBase::get_offset);

	ClassDB::bind_method(D_METHOD("set_flip_h", "flip_h"), &SpriteBase::set_flip_h);
	ClassDB::bind_method(D_METHOD("is_flipped_h"), &SpriteBase::is_flipped_h);

	ClassDB::bind_method(D_METHOD("set_flip_v", "flip_v"), &SpriteBase::set_flip_v);
	ClassDB::bind_method(D_METHOD("is_flipped_v"), &SpriteBase::is_flipped_v);

	ClassDB::bind_method(D_METHOD("is_pixel_opaque", "pos"), &SpriteBase::is_pixel_opaque);

	ADD_GROUP("Offset", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "centered"), "set_centered", "is_centered");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "basealigned"), "set_basealigned", "is_basealigned");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "force_pixel_snapping"), "set_force_pixel_snapping", "get_force_pixel_snapping");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset"), "set_offset", "get_offset");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_h"), "set_flip_h", "is_flipped_h");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_v"), "set_flip_v", "is_flipped_v");

}

SpriteBase::SpriteBase() {
	centered = true;
	basealigned = false;
	hflip = false;
	vflip = false;
	force_pixel_snapping = false;
}

SpriteBase::~SpriteBase() {
}
