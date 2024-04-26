/**************************************************************************/
/*  sprite.h                                                              */
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

#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include "scene/2d/node_2d.h"
#include "scene/resources/texture.h"

class SpriteBase : public Node2D {
	GDCLASS(SpriteBase, Node2D);

	//Ref<Texture> texture;
	//Ref<Texture> normal_map;

	bool force_pixel_snapping;
	bool centered;
	bool basealigned;
	Point2 offset;

	bool hflip;
	bool vflip;

	int frame;

	void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const;

protected:
	void _notification(int p_what);

	static void _bind_methods();

	virtual void _validate_property(PropertyInfo &property) const;

public:
#ifdef TOOLS_ENABLED
	virtual Dictionary _edit_get_state() const;
	virtual void _edit_set_state(const Dictionary &p_state);

	virtual void _edit_set_pivot(const Point2 &p_pivot);
	virtual Point2 _edit_get_pivot() const;
	virtual bool _edit_use_pivot() const;
	virtual bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const;

	virtual Rect2 _edit_get_rect() const;
	virtual bool _edit_use_rect() const;
#endif

	bool is_pixel_opaque(const Point2 &p_point) const;

	virtual Ref<Texture> get_sprite_texture() const;

	void set_force_pixel_snapping(bool p_snapping);
	bool get_force_pixel_snapping() const;

	void set_centered(bool p_center);
	bool is_centered() const;

	void set_basealigned(bool p_basealign);
	bool is_basealigned() const;

	void set_offset(const Point2 &p_offset);
	Point2 get_offset() const;

	void set_flip_h(bool p_flip);
	bool is_flipped_h() const;

	void set_flip_v(bool p_flip);
	bool is_flipped_v() const;

	void set_frame(int p_frame);
	int get_frame() const;

	Rect2 get_rect() const;
	virtual Rect2 get_anchorable_rect() const;

	SpriteBase();
	~SpriteBase();
};

#endif // SPRITE_BASE_H
