/**************************************************************************/
/*  animated_sprite.h                                                     */
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

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite_base.h"

class SpriteFrames : public Resource {
	GDCLASS(SpriteFrames, Resource);

	struct Anim {
		float speed;
		bool loop;
		Vector<Ref<Texture>> frames;

		Anim() {
			loop = true;
			//speed = 5;
			//valla edit
			speed = 10;
		}

		StringName normal_name;
	};

	Map<StringName, Anim> animations;

	Array _get_frames() const;
	void _set_frames(const Array &p_frames);

	Array _get_animations() const;
	void _set_animations(const Array &p_animations);

protected:
	static void _bind_methods();

public:
	// return the entire array of textures
	Vector<Ref<Texture>> get_animation_frames(const StringName &p_anim);
	//void set_animation_frames(const StringName &p_anim, Vector<Ref<Texture>>);

	void add_animation(const StringName &p_anim);
	bool has_animation(const StringName &p_anim) const;
	void remove_animation(const StringName &p_anim);
	void rename_animation(const StringName &p_prev, const StringName &p_next);

	void get_animation_list(List<StringName> *r_animations) const;
	Vector<String> get_animation_names() const;

	void set_animation_speed(const StringName &p_anim, float p_fps);
	float get_animation_speed(const StringName &p_anim) const;

	void set_animation_loop(const StringName &p_anim, bool p_loop);
	bool get_animation_loop(const StringName &p_anim) const;

	void add_frame(const StringName &p_anim, const Ref<Texture> &p_frame, int p_at_pos = -1);
	//void add_frames(const StringName &p_anim, const Vector<Ref<Texture>> &p_frames, int p_at_pos = -1);
	int get_frame_count(const StringName &p_anim) const;
	// Return texture from frame index
	_FORCE_INLINE_ Ref<Texture> get_frame(const StringName &p_anim, int p_idx) const {
		const Map<StringName, Anim>::Element *E = animations.find(p_anim);
		ERR_FAIL_COND_V_MSG(!E, Ref<Texture>(), "Animation '" + String(p_anim) + "' doesn't exist.");
		ERR_FAIL_COND_V(p_idx < 0, Ref<Texture>());
		if (p_idx >= E->get().frames.size()) {
			return Ref<Texture>();
		}

		return E->get().frames[p_idx];
	}

	_FORCE_INLINE_ Ref<Texture> get_normal_frame(const StringName &p_anim, int p_idx) const {
		const Map<StringName, Anim>::Element *E = animations.find(p_anim);
		ERR_FAIL_COND_V_MSG(!E, Ref<Texture>(), "Animation '" + String(p_anim) + "' doesn't exist.");
		ERR_FAIL_COND_V(p_idx < 0, Ref<Texture>());

		const Map<StringName, Anim>::Element *EN = animations.find(E->get().normal_name);

		if (!EN || p_idx >= EN->get().frames.size()) {
			return Ref<Texture>();
		}

		return EN->get().frames[p_idx];
	}

	void set_frame(const StringName &p_anim, int p_idx, const Ref<Texture> &p_frame) {
		Map<StringName, Anim>::Element *E = animations.find(p_anim);
		ERR_FAIL_COND_MSG(!E, "Animation '" + String(p_anim) + "' doesn't exist.");
		ERR_FAIL_COND(p_idx < 0);
		if (p_idx >= E->get().frames.size()) {
			return;
		}
		E->get().frames.write[p_idx] = p_frame;
	}
	void remove_frame(const StringName &p_anim, int p_idx);
	void clear(const StringName &p_anim);
	void clear_all();

	SpriteFrames();
};

class AnimatedSprite : public SpriteBase {
	GDCLASS(AnimatedSprite, SpriteBase);

	Ref<SpriteFrames> frames;
	bool playing;
	bool reversed;
	StringName animation;
	bool animation_locked;
	int frame;
	float speed_scale;

	bool is_over;
	float timeout;

	void _res_changed();

	float _get_frame_duration();
	void _reset_timeout();
	Rect2 _get_rect() const;

protected:
	static void _bind_methods();
	void _notification(int p_what);
	virtual void _validate_property(PropertyInfo &property) const;

public:
#ifdef TOOLS_ENABLED
	virtual Rect2 _edit_get_rect() const;
	virtual bool _edit_use_rect() const;
#endif

	virtual Rect2 get_anchorable_rect() const;

	void set_sprite_frames(const Ref<SpriteFrames> &p_frames);
	Ref<SpriteFrames> get_sprite_frames() const;

	void play(const StringName &p_animation = StringName(), const bool p_reversed = false);
	void stop();

	void set_reversed(const bool p_reversed);
	bool is_reversed();
	void set_playing(bool p_playing);
	bool is_playing() const;

	void set_animation(const StringName &p_animation);
	void set_animation_continue(const StringName &p_animation);
	StringName get_animation() const;

	void set_frame(int p_frame);
	int get_frame() const;

	void set_speed_scale(float p_speed_scale);
	float get_speed_scale() const;

	void set_animation_locked(bool p_lock);
	bool is_animation_locked() const;

	virtual String get_configuration_warning() const;
	virtual void get_argument_options(const StringName &p_function, int p_idx, List<String> *r_options) const;

	AnimatedSprite();
};

#endif // ANIMATED_SPRITE_H
