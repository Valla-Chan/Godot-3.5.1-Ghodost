/**************************************************************************/
/*  rounded_rect_shape_2d.cpp                                             */
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

#include "rounded_rect_shape_2d.h"
#include "servers/physics_2d_server.h"
#include "servers/visual_server.h"

Vector<Vector2> RoundedRectShape2D::_get_points() const {
	Vector<Vector2> points;
	float width = get_extents().x;
	float height = get_extents().y;
	float radius = get_corner_radius();
	int corner_segments = 6; // Number of segments to approximate each corner

	// Top-left corner
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle), radius * sin(angle)) + Vector2(radius, height - radius));
	}

	// Top edge between top-left and top-right corners
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + Math_PI / 2.0), radius * sin(angle + Math_PI / 2.0)) + Vector2(width - radius, height - radius));
	}

	// Top-right corner
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + Math_PI), radius * sin(angle + Math_PI)) + Vector2(width - radius, radius));
	}

	// Right edge between top-right and bottom-right corners
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + 3 * Math_PI / 2.0), radius * sin(angle + 3 * Math_PI / 2.0)) + Vector2(radius, radius));
	}

	// Bottom-right corner
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle), radius * sin(angle)) + Vector2(radius, radius));
	}

	// Bottom edge between bottom-right and bottom-left corners
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + Math_PI / 2.0), radius * sin(angle + Math_PI / 2.0)) + Vector2(width - radius, height - radius));
	}

	// Bottom-left corner
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + Math_PI), radius * sin(angle + Math_PI)) + Vector2(width - radius, radius));
	}

	// Left edge between bottom-left and top-left corners
	for (int i = 0; i <= corner_segments; i++) {
		float angle = Math_PI / 2.0 * (i / (float)corner_segments);
		points.push_back(Vector2(radius * cos(angle + 3 * Math_PI / 2.0), radius * sin(angle + 3 * Math_PI / 2.0)) + Vector2(radius, height - radius));
	}

	return points;
}

bool RoundedRectShape2D::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	return Geometry::is_point_in_polygon(p_point, _get_points());
}

void RoundedRectShape2D::_update_shape() {
	Dictionary data = Dictionary();
	data["extents"] = extents;
	data["corner_radius"] = corner_radius;
	Physics2DServer::get_singleton()->shape_set_data(get_rid(), data);
	emit_changed();
}

void RoundedRectShape2D::draw(const RID &p_to_rid, const Color &p_color) {
	Vector<Vector2> points = _get_points();
	Vector<Color> col;
	col.push_back(p_color);
	VisualServer::get_singleton()->canvas_item_add_polygon(p_to_rid, points, col);
	if (is_collision_outline_enabled()) {
		VisualServer::get_singleton()->canvas_item_add_polyline(p_to_rid, points, col, 1.0, true);
		// Draw the last segment as it's not drawn by `canvas_item_add_polyline()`.
		VisualServer::get_singleton()->canvas_item_add_line(p_to_rid, points[points.size() - 1], points[0], p_color, 1.0, true);
	}
}

void RoundedRectShape2D::set_extents(const Vector2 &p_extents) {
	extents = p_extents;
	_update_shape();
}

Vector2 RoundedRectShape2D::get_extents() const {
	return extents;
}

void RoundedRectShape2D::set_corner_radius(real_t p_radius) {
	corner_radius = p_radius;
	_update_shape();
}

real_t RoundedRectShape2D::get_corner_radius() const {
	return corner_radius;
}

Rect2 RoundedRectShape2D::get_rect() const {
	return Rect2(-extents, extents * 2.0);
}

real_t RoundedRectShape2D::get_enclosing_radius() const {
	return extents.length();
}

void RoundedRectShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_corner_radius", "radius"), &RoundedRectShape2D::set_corner_radius);
	ClassDB::bind_method(D_METHOD("get_corner_radius"), &RoundedRectShape2D::get_corner_radius);

	ClassDB::bind_method(D_METHOD("set_extents", "extents"), &RoundedRectShape2D::set_extents);
	ClassDB::bind_method(D_METHOD("get_extents"), &RoundedRectShape2D::get_extents);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "extents"), "set_extents", "get_extents");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "corner_radius", PROPERTY_HINT_RANGE, "0.01,1024,0.01,or_greater"), "set_corner_radius", "get_corner_radius");
}

RoundedRectShape2D::RoundedRectShape2D() :
		Shape2D(Physics2DServer::get_singleton()->rounded_rect_shape_create()) {
	corner_radius = 5;
	extents = Vector2(10, 10);
	_update_shape();
}
