/**************************************************************************/
/*  texture_rect.h                                                        */
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

#ifndef ANIMATED_TEXTURE_RECT_H
#define ANIMATED_TEXTURE_RECT_H

#include "scene/gui/control.h"
#include "scene/2d/animated_sprite.h"

class AnimatedTextureRect : public Control {
	GDCLASS(AnimatedTextureRect, Control);

public:
	enum StretchMode {
		STRETCH_SCALE_ON_EXPAND, //default, for backwards compatibility
		STRETCH_SCALE,
		STRETCH_TILE,
		STRETCH_KEEP,
		STRETCH_KEEP_CENTERED,
		STRETCH_KEEP_ASPECT,
		STRETCH_KEEP_ASPECT_CENTERED,
		STRETCH_KEEP_ASPECT_COVERED,
		STRETCH_KEEP_ASPECT_CENTERED_TILE,
		STRETCH_KEEP_CENTERED_TILE,
	};

private:

	// From AnimatedSprite
	Ref<SpriteFrames> frames;
	bool playing;
	bool backwards;
	StringName animation;
	int frame;
	float speed_scale;

	bool is_over;
	float timeout;
	//

	bool expand;
	bool hflip;
	bool vflip;
	Ref<Texture> texture; //TODO: use get_frame instead
	StretchMode stretch_mode;

	void _texture_changed();
	// From AnimatedSprite
	void _res_changed();

	float _get_frame_duration();
	void _reset_timeout();
	//

protected:
	void _notification(int p_what);
	virtual Size2 get_minimum_size() const;
	static void _bind_methods();
	virtual void _validate_property(PropertyInfo &property) const;

public:
	// Access SpriteFrames functions instead!
	//void set_texture(const Ref<Texture> &p_tex);
	//Ref<Texture> get_texture() const;

	void set_expand(bool p_expand);
	bool has_expand() const;

	void set_stretch_mode(StretchMode p_mode);
	StretchMode get_stretch_mode() const;


	// From AnimatedSprite
	void set_sprite_frames(const Ref<SpriteFrames> &p_frames);
	Ref<SpriteFrames> get_sprite_frames() const;

	void play(const StringName &p_animation = StringName(), const bool p_backwards = false);
	void stop();

	void set_playing(bool p_playing);
	bool is_playing() const;

	void set_animation(const StringName &p_animation);
	void set_animation_continue(const StringName &p_animation);
	//void set_animation(const StringName &p_animation = StringName(), const bool p_resetframe = true);
	StringName get_animation() const;

	void set_frame(int p_frame);
	int get_frame() const;

	void set_speed_scale(float p_speed_scale);
	float get_speed_scale() const;

	virtual String get_configuration_warning() const;
	virtual void get_argument_options(const StringName &p_function, int p_idx, List<String> *r_options) const;
	//

	void set_flip_h(bool p_flip);
	bool is_flipped_h() const;

	void set_flip_v(bool p_flip);
	bool is_flipped_v() const;


	AnimatedTextureRect();
	~AnimatedTextureRect();
};

VARIANT_ENUM_CAST(AnimatedTextureRect::StretchMode);

#endif // ANIMATED_TEXTURE_RECT_H
