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

Rect2 SpriteBase::_edit_get_rect() const {
	return get_rect();
}

bool SpriteBase::_edit_use_rect() const {
	return get_sprite_texture().is_valid();
}
#endif

Ref<Texture> SpriteBase::get_sprite_texture() const {
	Ref<Texture> t;
	return t;
}

Rect2 SpriteBase::get_anchorable_rect() const {
	return get_rect();
}

void SpriteBase::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const {
	Rect2 base_rect;

	r_filter_clip = false;
	base_rect = Rect2(0, 0, get_sprite_texture()->get_width(), get_sprite_texture()->get_height());

	Size2 frame_size = base_rect.size;
	Point2 frame_offset = Point2(frame, frame);
	frame_offset *= frame_size;

	r_src_rect.size = frame_size;
	r_src_rect.position = base_rect.position + frame_offset;

	Point2 dest_offset = offset;
	if (centered) {
		dest_offset -= frame_size / 2;
	}
	//VALLA EDITS
	if (basealigned) {
		if (centered) {
			dest_offset.y -= frame_size.y / 2;
		} else {
			dest_offset.y -= frame_size.y;
		}
	}
	

	if (Engine::get_singleton()->get_use_gpu_pixel_snap() || force_pixel_snapping) {
		dest_offset = dest_offset.floor();
	}

	r_dst_rect = Rect2(dest_offset, frame_size);

	if (hflip) {
		r_dst_rect.size.x = -r_dst_rect.size.x;
	}
	if (vflip) {
		r_dst_rect.size.y = -r_dst_rect.size.y;
	}
}

void SpriteBase::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW: {
			if (get_sprite_texture().is_null()) {
				return;
			}

			RID ci = get_canvas_item();

			/*
			texture->draw(ci,Point2());
			break;
			*/

			Rect2 src_rect, dst_rect;
			bool filter_clip;
			_get_rects(src_rect, dst_rect, filter_clip);
			//get_sprite_texture()->draw_rect_region(ci, dst_rect, src_rect, Color(1, 1, 1), false, normal_map, filter_clip);

		} break;
	}
}

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

void SpriteBase::set_frame(int p_frame) {
	frame = p_frame;

	_change_notify("frame");
	//_change_notify("frame_coords");
	//emit_signal(SceneStringNames::get_singleton()->frame_changed);
}

int SpriteBase::get_frame() const {
	return frame;
}


bool SpriteBase::is_pixel_opaque(const Point2 &p_point) const {
	if (get_sprite_texture().is_null()) {
		return false;
	}

	if (get_sprite_texture()->get_size().width == 0 || get_sprite_texture()->get_size().height == 0) {
		return false;
	}

	Rect2 src_rect, dst_rect;
	bool filter_clip;
	_get_rects(src_rect, dst_rect, filter_clip);
	dst_rect.size = dst_rect.size.abs();

	if (!dst_rect.has_point(p_point)) {
		return false;
	}

	Vector2 q = (p_point - dst_rect.position) / dst_rect.size;
	if (hflip) {
		q.x = 1.0f - q.x;
	}
	if (vflip) {
		q.y = 1.0f - q.y;
	}
	q = q * src_rect.size + src_rect.position;

	Ref<Texture> texture = get_sprite_texture();
	bool is_repeat = texture->get_flags() & Texture::FLAG_REPEAT;
	bool is_mirrored_repeat = texture->get_flags() & Texture::FLAG_MIRRORED_REPEAT;
	if (is_repeat) {
		int mirror_x = 0;
		int mirror_y = 0;
		if (is_mirrored_repeat) {
			mirror_x = (int)(q.x / texture->get_size().width);
			mirror_y = (int)(q.y / texture->get_size().height);
		}
		q.x = Math::fmod(q.x, texture->get_size().width);
		q.y = Math::fmod(q.y, texture->get_size().height);
		if (mirror_x % 2 == 1) {
			q.x = texture->get_size().width - q.x - 1;
		}
		if (mirror_y % 2 == 1) {
			q.y = texture->get_size().height - q.y - 1;
		}
	} else {
		q.x = MIN(q.x, texture->get_size().width - 1);
		q.y = MIN(q.y, texture->get_size().height - 1);
	}

	return texture->is_pixel_opaque((int)q.x, (int)q.y);
}

Rect2 SpriteBase::get_rect() const {
	if (get_sprite_texture().is_null()) {
		return Rect2(0, 0, 1, 1);
	}

	Size2i s;


	s = get_sprite_texture()->get_size();

	Point2 ofs = offset;
	if (centered) {
		ofs -= Size2(s) / 2;
	}
	//VALLA EDITS
	if (basealigned) {
		if (centered) {
			ofs.y -= Size2(s).y / 2;
		} else {
			ofs.y -= Size2(s).y;
			//ofs.x -= Size2(s).x / 2;
		}
		
	}
	if (Engine::get_singleton()->get_use_gpu_pixel_snap() || force_pixel_snapping) {
		ofs = ofs.floor();
	}

	if (s == Size2(0, 0)) {
		s = Size2(1, 1);
	}

	return Rect2(ofs, s);
}

void SpriteBase::_validate_property(PropertyInfo &property) const {
	if (property.name == "frame") {
		property.hint = PROPERTY_HINT_RANGE;
		property.usage |= PROPERTY_USAGE_KEYING_INCREMENTS;
	}

	if (property.name == "frame_coords") {
		property.usage |= PROPERTY_USAGE_KEYING_INCREMENTS;
	}
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

	ClassDB::bind_method(D_METHOD("set_frame", "frame"), &SpriteBase::set_frame);
	ClassDB::bind_method(D_METHOD("get_frame"), &SpriteBase::get_frame);

	ClassDB::bind_method(D_METHOD("get_rect"), &SpriteBase::get_rect);

	ADD_SIGNAL(MethodInfo("frame_changed"));
	ADD_SIGNAL(MethodInfo("texture_changed"));

	ADD_GROUP("Offset", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "centered"), "set_centered", "is_centered");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "basealigned"), "set_basealigned", "is_basealigned");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "force_pixel_snapping"), "set_force_pixel_snapping", "get_force_pixel_snapping");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset"), "set_offset", "get_offset");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_h"), "set_flip_h", "is_flipped_h");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_v"), "set_flip_v", "is_flipped_v");
	ADD_GROUP("Animation", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "frame"), "set_frame", "get_frame");

}

SpriteBase::SpriteBase() {
	centered = true;
	basealigned = false;
	hflip = false;
	vflip = false;
	force_pixel_snapping = false;

	frame = 0;
}

SpriteBase::~SpriteBase() {
}
