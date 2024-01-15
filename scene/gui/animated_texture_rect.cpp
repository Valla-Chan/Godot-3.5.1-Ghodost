/**************************************************************************/
/*  texture_rect.cpp                                                      */
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

#include "animated_texture_rect.h"
#include "core/core_string_names.h"
#include "servers/visual_server.h"
#include "core/os/os.h"
#include "scene/scene_string_names.h"

#ifdef TOOLS_ENABLED
#include "editor/editor_settings.h"
#endif

void AnimatedTextureRect::_validate_property(PropertyInfo &property) const {
	if (!frames.is_valid()) {
		return;
	}
	if (property.name == "animation") {
		property.hint = PROPERTY_HINT_ENUM;
		List<StringName> names;
		frames->get_animation_list(&names);
		names.sort_custom<StringName::AlphCompare>();

		bool current_found = false;

		for (List<StringName>::Element *E = names.front(); E; E = E->next()) {
			if (E->prev()) {
				property.hint_string += ",";
			}

			property.hint_string += String(E->get());
			if (animation == E->get()) {
				current_found = true;
			}
		}

		if (!current_found) {
			if (property.hint_string == String()) {
				property.hint_string = String(animation);
			} else {
				property.hint_string = String(animation) + "," + property.hint_string;
			}
		}
	}

	if (property.name == "frame") {
		property.hint = PROPERTY_HINT_RANGE;
		if (frames->has_animation(animation) && frames->get_frame_count(animation) > 1) {
			property.hint_string = "0," + itos(frames->get_frame_count(animation) - 1) + ",1";
		}
		property.usage |= PROPERTY_USAGE_KEYING_INCREMENTS;
	}
}

void AnimatedTextureRect::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_INTERNAL_PROCESS: {
			if (frames.is_null()) {
				return;
			}
			if (!frames->has_animation(animation)) {
				return;
			}
			if (frame < 0) {
				return;
			}
			if (!OS::get_singleton()->is_update_pending()) {
				return;
			}

			float remaining = get_process_delta_time();

			while (remaining) {
				float speed = frames->get_animation_speed(animation) * speed_scale;
				if (speed == 0) {
					return; //do nothing
				}

				if (timeout <= 0) {
					timeout = _get_frame_duration();

					int fc = frames->get_frame_count(animation);
					if ((!backwards && frame >= fc - 1) || (backwards && frame <= 0)) {
						if (frames->get_animation_loop(animation)) {
							if (backwards) {
								frame = fc - 1;
							} else {
								frame = 0;
							}

							emit_signal(SceneStringNames::get_singleton()->animation_finished);
						} else {
							if (backwards) {
								frame = 0;
							} else {
								frame = fc - 1;
							}

							if (!is_over) {
								is_over = true;
								emit_signal(SceneStringNames::get_singleton()->animation_finished);
							}
						}
					} else {
						if (backwards) {
							frame--;
						} else {
							frame++;
						}
					}

					update();
					_change_notify("frame");
					emit_signal(SceneStringNames::get_singleton()->frame_changed);
				}

				float to_process = MIN(timeout, remaining);
				remaining -= to_process;
				timeout -= to_process;
			}
		} break;

		case NOTIFICATION_DRAW: {
			if (frames.is_null()) {
				return;
			}
			// get the texture from the current frame of the current animation
			texture = frames->get_frame(animation, frame);
			if (texture == nullptr) {
				return;
			}

			Size2 size;
			Point2 offset;
			Rect2 region;
			bool tile = false;

			switch (stretch_mode) {
				case STRETCH_SCALE_ON_EXPAND: {
					size = expand ? get_size() : texture->get_size();
				} break;
				case STRETCH_SCALE: {
					size = get_size();
				} break;
				case STRETCH_TILE: {
					size = get_size();
					tile = true;
				} break;
				case STRETCH_KEEP: {
					size = texture->get_size();
				} break;
				case STRETCH_KEEP_CENTERED: {
					offset = (get_size() - texture->get_size()) / 2;
					size = texture->get_size();
				} break;
				case STRETCH_KEEP_ASPECT_CENTERED:
				case STRETCH_KEEP_ASPECT: {
					size = get_size();
					int tex_width = texture->get_width() * size.height / texture->get_height();
					int tex_height = size.height;

					if (tex_width > size.width) {
						tex_width = size.width;
						tex_height = texture->get_height() * tex_width / texture->get_width();
					}

					if (stretch_mode == STRETCH_KEEP_ASPECT_CENTERED) {
						offset.x += (size.width - tex_width) / 2;
						offset.y += (size.height - tex_height) / 2;
					}

					size.width = tex_width;
					size.height = tex_height;
				} break;
				case STRETCH_KEEP_ASPECT_COVERED: {
					size = get_size();

					Size2 tex_size = texture->get_size();
					Size2 scale_size(size.width / tex_size.width, size.height / tex_size.height);
					float scale = scale_size.width > scale_size.height ? scale_size.width : scale_size.height;
					Size2 scaled_tex_size = tex_size * scale;

					region.position = ((scaled_tex_size - size) / scale).abs() / 2.0f;
					region.size = size / scale;
				} break;
			}

			Ref<AtlasTexture> p_atlas = texture;

			if (p_atlas.is_valid() && region.has_no_area()) {
				Size2 scale_size(size.width / texture->get_width(), size.height / texture->get_height());

				offset.width += hflip ? p_atlas->get_margin().get_position().width * scale_size.width * 2 : 0;
				offset.height += vflip ? p_atlas->get_margin().get_position().height * scale_size.height * 2 : 0;
			}

			size.width *= hflip ? -1.0f : 1.0f;
			size.height *= vflip ? -1.0f : 1.0f;

			if (region.has_no_area()) {
				draw_texture_rect(texture, Rect2(offset, size), tile);
			} else {
				draw_texture_rect_region(texture, Rect2(offset, size), region);
			}

		} break;
	}
}

Size2 AnimatedTextureRect::get_minimum_size() const {
	if (!expand && !texture.is_null()) {
		return texture->get_size();
	} else {
		return Size2();
	}
}

// ADDED FROM ANIMATEDSPRITE
void AnimatedTextureRect::set_sprite_frames(const Ref<SpriteFrames> &p_frames) {
	if (frames.is_valid()) {
		frames->disconnect("changed", this, "_res_changed");
		frames->disconnect("frame_changed", this, "set_frame");
		frames->disconnect("animation_changed", this, "set_animation");
	}
	frames = p_frames;
	if (frames.is_valid()) {
		frames->connect("changed", this, "_res_changed");
		frames->connect("frame_changed", this, "set_frame");
		frames->connect("animation_changed", this, "set_animation");
	}

	if (!frames.is_valid()) {
		frame = 0;
	} else {
		set_frame(frame);
	}

	_change_notify();
	_reset_timeout();
	update();
	update_configuration_warning();
}

Ref<SpriteFrames> AnimatedTextureRect::get_sprite_frames() const {
	return frames;
}

void AnimatedTextureRect::set_frame(int p_frame) {
	if (!frames.is_valid()) {
		return;
	}

	if (frames->has_animation(animation)) {
		int limit = frames->get_frame_count(animation);
		if (p_frame >= limit) {
			p_frame = limit - 1;
		}
	}

	if (p_frame < 0) {
		p_frame = 0;
	}

	if (frame == p_frame) {
		return;
	}

	frame = p_frame;
	_reset_timeout();
	update();
	_change_notify("frame");
	emit_signal(SceneStringNames::get_singleton()->frame_changed);
}
int AnimatedTextureRect::get_frame() const {
	return frame;
}

void AnimatedTextureRect::set_speed_scale(float p_speed_scale) {
	float elapsed = _get_frame_duration() - timeout;

	speed_scale = MAX(p_speed_scale, 0.0f);

	// We adapt the timeout so that the animation speed adapts as soon as the speed scale is changed
	_reset_timeout();
	timeout -= elapsed;
}

float AnimatedTextureRect::get_speed_scale() const {
	return speed_scale;
}


void AnimatedTextureRect::_res_changed() {
	set_frame(frame);

	// Calling _change_notify("frame") and _change_notify("animation") instead wouldn't
	// make EditorInspector trigger calls to _validate_property(property) which would
	// lead to not updating valid values for "frame" and "animation" properties.
	_change_notify();

	update();
}

void AnimatedTextureRect::set_playing(bool p_playing) {
	if (playing == p_playing) {
		return;
	}
	playing = p_playing;
	_reset_timeout();
	set_process_internal(playing);
}

bool AnimatedTextureRect::is_playing() const {
	return playing;
}

void AnimatedTextureRect::play(const StringName &p_animation, const bool p_backwards) {
	backwards = p_backwards;

	if (p_animation) {
		set_animation(p_animation);
		if (frames.is_valid() && backwards && get_frame() == 0) {
			set_frame(frames->get_frame_count(p_animation) - 1);
		}
	}

	is_over = false;
	set_playing(true);
}

void AnimatedTextureRect::stop() {
	set_playing(false);
}

float AnimatedTextureRect::_get_frame_duration() {
	if (frames.is_valid() && frames->has_animation(animation)) {
		float speed = frames->get_animation_speed(animation) * speed_scale;
		if (speed > 0) {
			return 1.0 / speed;
		}
	}
	return 0.0;
}

void AnimatedTextureRect::_reset_timeout() {
	if (!playing) {
		return;
	}

	timeout = _get_frame_duration();
	is_over = false;
}

void AnimatedTextureRect::set_animation(const StringName &p_animation) {
	//void AnimatedTextureRect::set_animation(const StringName &p_animation, const bool p_resetframe) {
	ERR_FAIL_COND_MSG(frames == nullptr, vformat("There is no animation with name '%s'.", p_animation));
	ERR_FAIL_COND_MSG(frames->get_animation_names().find(p_animation) == -1, vformat("There is no animation with name '%s'.", p_animation));

	if (animation == p_animation) {
		return;
	}

	animation = p_animation;
	_reset_timeout();
	//if (p_resetframe) {
	set_frame(0);
	//}
	_change_notify();
	update();
}
void AnimatedTextureRect::set_animation_continue(const StringName &p_animation) {
	//void AnimatedTextureRect::set_animation(const StringName &p_animation, const bool p_resetframe) {
	ERR_FAIL_COND_MSG(frames == nullptr, vformat("There is no animation with name '%s'.", p_animation));
	ERR_FAIL_COND_MSG(frames->get_animation_names().find(p_animation) == -1, vformat("There is no animation with name '%s'.", p_animation));

	if (animation == p_animation) {
		return;
	}

	animation = p_animation;
	//_reset_timeout();
	//if (p_resetframe) {
	//set_frame(0);
	//}
	_change_notify();
	update();
}
StringName AnimatedTextureRect::get_animation() const {
	return animation;
}

String AnimatedTextureRect::get_configuration_warning() const {
	String warning = Control::get_configuration_warning();
	if (frames.is_null()) {
		if (warning != String()) {
			warning += "\n\n";
		}
		warning += TTR("A SpriteFrames resource must be created or set in the \"Frames\" property in order for AnimatedTextureRect to display frames.");
	}

	return warning;
}

void AnimatedTextureRect::get_argument_options(const StringName &p_function, int p_idx, List<String> *r_options) const {
#ifdef TOOLS_ENABLED
	const String quote_style = EDITOR_GET("text_editor/completion/use_single_quotes") ? "'" : "\"";
#else
	const String quote_style = "\"";
#endif

	if (p_idx == 0 && p_function == "play" && frames.is_valid()) {
		List<StringName> al;
		frames->get_animation_list(&al);
		for (List<StringName>::Element *E = al.front(); E; E = E->next()) {
			r_options->push_back(quote_style + String(E->get()) + quote_style);
		}
	}
	Node::get_argument_options(p_function, p_idx, r_options);
}
//


void AnimatedTextureRect::_bind_methods() {

	// From AnimatedSprite
	ClassDB::bind_method(D_METHOD("set_sprite_frames", "sprite_frames"), &AnimatedTextureRect::set_sprite_frames);
	ClassDB::bind_method(D_METHOD("get_sprite_frames"), &AnimatedTextureRect::get_sprite_frames);

	ClassDB::bind_method(D_METHOD("set_animation", "animation"), &AnimatedTextureRect::set_animation);
	ClassDB::bind_method(D_METHOD("set_animation_continue", "animation"), &AnimatedTextureRect::set_animation_continue);
	ClassDB::bind_method(D_METHOD("get_animation"), &AnimatedTextureRect::get_animation);

	ClassDB::bind_method(D_METHOD("set_playing", "playing"), &AnimatedTextureRect::set_playing);
	ClassDB::bind_method(D_METHOD("is_playing"), &AnimatedTextureRect::is_playing);

	ClassDB::bind_method(D_METHOD("play", "anim", "backwards"), &AnimatedTextureRect::play, DEFVAL(StringName()), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("stop"), &AnimatedTextureRect::stop);

	ClassDB::bind_method(D_METHOD("set_frame", "frame"), &AnimatedTextureRect::set_frame);
	ClassDB::bind_method(D_METHOD("get_frame"), &AnimatedTextureRect::get_frame);

	ClassDB::bind_method(D_METHOD("set_speed_scale", "speed_scale"), &AnimatedTextureRect::set_speed_scale);
	ClassDB::bind_method(D_METHOD("get_speed_scale"), &AnimatedTextureRect::get_speed_scale);

	ClassDB::bind_method(D_METHOD("_res_changed"), &AnimatedTextureRect::_res_changed);

	ADD_SIGNAL(MethodInfo("frame_changed"));
	ADD_SIGNAL(MethodInfo("animation_finished"));
	//

	ClassDB::bind_method(D_METHOD("set_expand", "enable"), &AnimatedTextureRect::set_expand);
	ClassDB::bind_method(D_METHOD("has_expand"), &AnimatedTextureRect::has_expand);
	ClassDB::bind_method(D_METHOD("set_flip_h", "enable"), &AnimatedTextureRect::set_flip_h);
	ClassDB::bind_method(D_METHOD("is_flipped_h"), &AnimatedTextureRect::is_flipped_h);
	ClassDB::bind_method(D_METHOD("set_flip_v", "enable"), &AnimatedTextureRect::set_flip_v);
	ClassDB::bind_method(D_METHOD("is_flipped_v"), &AnimatedTextureRect::is_flipped_v);
	ClassDB::bind_method(D_METHOD("set_stretch_mode", "stretch_mode"), &AnimatedTextureRect::set_stretch_mode);
	ClassDB::bind_method(D_METHOD("get_stretch_mode"), &AnimatedTextureRect::get_stretch_mode);
	ClassDB::bind_method(D_METHOD("_texture_changed"), &AnimatedTextureRect::_texture_changed);

	// From AnimatedSprite
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "frames", PROPERTY_HINT_RESOURCE_TYPE, "SpriteFrames"), "set_sprite_frames", "get_sprite_frames");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "animation"), "set_animation", "get_animation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "frame"), "set_frame", "get_frame");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "speed_scale"), "set_speed_scale", "get_speed_scale");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "playing"), "set_playing", "is_playing");
	//

	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "expand"), "set_expand", "has_expand");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stretch_mode", PROPERTY_HINT_ENUM, "Scale On Expand (Compat),Scale,Tile,Keep,Keep Centered,Keep Aspect,Keep Aspect Centered,Keep Aspect Covered"), "set_stretch_mode", "get_stretch_mode");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_h"), "set_flip_h", "is_flipped_h");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "flip_v"), "set_flip_v", "is_flipped_v");

	BIND_ENUM_CONSTANT(STRETCH_SCALE_ON_EXPAND);
	BIND_ENUM_CONSTANT(STRETCH_SCALE);
	BIND_ENUM_CONSTANT(STRETCH_TILE);
	BIND_ENUM_CONSTANT(STRETCH_KEEP);
	BIND_ENUM_CONSTANT(STRETCH_KEEP_CENTERED);
	BIND_ENUM_CONSTANT(STRETCH_KEEP_ASPECT);
	BIND_ENUM_CONSTANT(STRETCH_KEEP_ASPECT_CENTERED);
	BIND_ENUM_CONSTANT(STRETCH_KEEP_ASPECT_COVERED);
}

void AnimatedTextureRect::_texture_changed() {
	if (texture.is_valid()) {
		update();
		minimum_size_changed();
	}
}

/*
void AnimatedTextureRect::set_texture(const Ref<Texture> &p_tex) {
	if (p_tex == texture) {
		return;
	}

	if (texture.is_valid()) {
		texture->disconnect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");
	}

	texture = p_tex;

	if (texture.is_valid()) {
		texture->connect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");
	}

	update();
	minimum_size_changed();
}

Ref<Texture> AnimatedTextureRect::get_texture() const {
	return texture;
}*/

void AnimatedTextureRect::set_expand(bool p_expand) {
	expand = p_expand;
	update();
	minimum_size_changed();
}

bool AnimatedTextureRect::has_expand() const {
	return expand;
}

void AnimatedTextureRect::set_stretch_mode(StretchMode p_mode) {
	stretch_mode = p_mode;
	update();
}

AnimatedTextureRect::StretchMode AnimatedTextureRect::get_stretch_mode() const {
	return stretch_mode;
}

void AnimatedTextureRect::set_flip_h(bool p_flip) {
	hflip = p_flip;
	update();
}

bool AnimatedTextureRect::is_flipped_h() const {
	return hflip;
}

void AnimatedTextureRect::set_flip_v(bool p_flip) {
	vflip = p_flip;
	update();
}

bool AnimatedTextureRect::is_flipped_v() const {
	return vflip;
}

AnimatedTextureRect::AnimatedTextureRect() {

	expand = false;
	hflip = false;
	vflip = false;
	set_mouse_filter(MOUSE_FILTER_PASS);
	stretch_mode = STRETCH_SCALE_ON_EXPAND;

	// From AnimatedSprite
	frame = 0;
	speed_scale = 1.0f;
	playing = false;
	backwards = false;
	animation = "default";
	timeout = 0;
	is_over = false;
}

AnimatedTextureRect::~AnimatedTextureRect() {
}
