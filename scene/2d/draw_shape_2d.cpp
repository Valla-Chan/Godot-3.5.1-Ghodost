/**************************************************************************/
/*  draw_shape_2d.cpp                                                     */
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

#include "draw_shape_2d.h"

#include "core/engine.h"
#include "scene/2d/area_2d.h"
#include "scene/resources/capsule_shape_2d.h"
#include "scene/resources/circle_shape_2d.h"
#include "scene/resources/concave_polygon_shape_2d.h"
#include "scene/resources/convex_polygon_shape_2d.h"
#include "scene/resources/line_shape_2d.h"
#include "scene/resources/rectangle_shape_2d.h"
#include "scene/resources/segment_shape_2d.h"
#include "editor/plugins/canvas_item_editor_plugin.h"

void DrawShape2D::_shape_changed() {
	update();
}

void DrawShape2D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW: {
			ERR_FAIL_COND(!is_inside_tree());

			if (!shape.is_valid()) {
				break;
			}

			rect = Rect2();
			shape->draw(get_canvas_item(), color);

			rect = shape->get_rect();
			rect = rect.grow(3);
		} break;
	}
}

void DrawShape2D::set_shape(const Ref<Shape2D> &p_shape) {
	if (p_shape == shape) {
		return;
	}
	if (shape.is_valid()) {
		shape->disconnect("changed", this, "_shape_changed");
	}
	shape = p_shape;
	update();

	if (shape.is_valid()) {
		shape->connect("changed", this, "_shape_changed");
	}

	update_configuration_warning();
}

void DrawShape2D::set_color(const Color &p_color) {
	color = p_color;
	update();
}
Color DrawShape2D::get_color() const {
	return color;
}

Ref<Shape2D> DrawShape2D::get_shape() const {
	return shape;
}

bool DrawShape2D::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
#ifdef TOOLS_ENABLED
	if (Engine::get_singleton()->is_editor_hint() && !CanvasItemEditor::get_singleton()->get_show_colliders()) {
		return false;
	}
#endif

	if (!shape.is_valid()) {
		return false;
	}

	return shape->_edit_is_selected_on_click(p_point, p_tolerance);
}

String DrawShape2D::get_configuration_warning() const {
	String warning = Node2D::get_configuration_warning();

	if (!shape.is_valid()) {
		if (warning != String()) {
			warning += "\n\n";
		}
		warning += TTR("A shape must be provided for DrawShape2D to function. Please create a shape resource for it!");
	} else {
		Ref<ConvexPolygonShape2D> convex = shape;
		Ref<ConcavePolygonShape2D> concave = shape;
		if (convex.is_valid() || concave.is_valid()) {
			if (warning != String()) {
				warning += "\n\n";
			}
			warning += TTR("Polygon-based shapes are not meant be used nor edited directly through the DrawShape2D node. Please use the Polygon2D node instead.");
		}
	}

	return warning;
}

void DrawShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_shape", "shape"), &DrawShape2D::set_shape);
	ClassDB::bind_method(D_METHOD("get_shape"), &DrawShape2D::get_shape);
	ClassDB::bind_method(D_METHOD("set_color", "color"), &DrawShape2D::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &DrawShape2D::get_color);
	ClassDB::bind_method(D_METHOD("_shape_changed"), &DrawShape2D::_shape_changed);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "shape", PROPERTY_HINT_RESOURCE_TYPE, "Shape2D"), "set_shape", "get_shape");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}

DrawShape2D::DrawShape2D() {
	rect = Rect2(-Point2(10, 10), Point2(20, 20));
	set_notify_local_transform(true);
}
