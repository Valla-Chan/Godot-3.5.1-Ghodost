/**************************************************************************/
/*  collision_polygon_2d.h                                                */
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

#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include "scene/2d/node_2d.h"
#include "collision_object_2d.h"
#include "scene/resources/shape_2d.h"
#include "editor/plugins/canvas_item_editor_plugin.h"

class Collider2D;

class Collider2D : public Node2D {
	GDCLASS(Collider2D, Node2D);

protected:
	uint32_t owner_id;
	CollisionObject2D *parent;
	bool disabled;
	bool one_way_collision;
	bool use_override_color;
	Color override_color;
	float one_way_collision_margin;

	void _update_in_shape_owner(bool p_xform_only = false);

protected:
	static void _bind_methods();

public:

	void set_disabled(bool p_disabled);
	bool is_disabled() const;

	void set_one_way_collision(bool p_enable);
	bool is_one_way_collision_enabled() const;

	void set_one_way_collision_margin(float p_margin);
	float get_one_way_collision_margin() const;

	// VALLA EDITS
	void set_use_override_color(const bool p_enable);
	bool get_use_override_color() const;
	void set_override_color(const Color p_override_color);
	Color get_override_color() const;
	//

	Collider2D();
	
};

#endif // COLLIDER_2D_H
