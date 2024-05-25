/**************************************************************************/
/*  label.cpp                                                             */
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

#include "text.h"
#include "core/print_string.h"
#include "core/project_settings.h"
#include "core/translation.h"
#include "scene/resources/dynamic_font.h"

void Text::set_align(Align p_align) {
}

Text::Align Text::get_align() const {
	return Align(0);
}


void Text::set_font_size_override(int p_size) {
	if (p_size < 0 ){
		p_size = 0;
	}
	if (font_size_override != p_size) {
		font_scaled_cache.clear();
	}
	font_size_override = p_size;

	//minimum_size_changed();
	//set_size(get_size());
	_notification(NOTIFICATION_THEME_CHANGED);
	_notification(NOTIFICATION_RESIZED);
}

void Text::set_font_scale(float p_scale) {
	if (p_scale < 0) {
		p_scale = 0;
	}
	if (font_scale != p_scale) {
		font_scaled_cache.clear();
	}
	font_scale = p_scale;

	//minimum_size_changed();
	//set_size(get_size());
	_notification(NOTIFICATION_THEME_CHANGED);
	_notification(NOTIFICATION_RESIZED);
}

int Text::get_font_size_override() const {
	return font_size_override;
}

float Text::get_font_scale() const {
	return font_scale;
}

// return a scaled version of the main font
Ref<Font> Text::get_font_scaled(const String &p_font = "font") const {
	Ref<Font> font = get_font("font");
	Ref<DynamicFont> dynfont = font;
	if (font_size_override > 0 || (font_scale != 1.0 && font_scale > 0)) {
		if (font_scaled_cache.has(p_font) && font_scaled_cache[p_font].is_valid()) {
			return font_scaled_cache[p_font];
		}

		dynfont = dynfont->duplicate();
		if (font_size_override > 0)
			dynfont->set_size(font_size_override);
		if (font_scale != 1.0 && font_scale > 0)
			dynfont->set_size(dynfont->get_size() * font_scale);

		font = dynfont;
		font_scaled_cache[p_font] = font;
	}
	return font;
}


void Text::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_align", "align"), &Text::set_align);
	ClassDB::bind_method(D_METHOD("get_align"), &Text::get_align);

	ClassDB::bind_method(D_METHOD("set_font_size_override", "size"), &Text::set_font_size_override);
	ClassDB::bind_method(D_METHOD("set_font_scale", "scale"), &Text::set_font_scale);
	ClassDB::bind_method(D_METHOD("get_font_size_override"), &Text::get_font_size_override);
	ClassDB::bind_method(D_METHOD("get_font_scale"), &Text::get_font_scale);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "font_size_override", PROPERTY_HINT_RANGE, "0,128,1,false"), "set_font_size_override", "get_font_size_override");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "font_scale", PROPERTY_HINT_RANGE, "0.001,3,0.1,false"), "set_font_scale", "get_font_scale");

	BIND_ENUM_CONSTANT(ALIGN_LEFT);
	BIND_ENUM_CONSTANT(ALIGN_CENTER);
	BIND_ENUM_CONSTANT(ALIGN_RIGHT);
	BIND_ENUM_CONSTANT(ALIGN_FILL);

	BIND_ENUM_CONSTANT(VALIGN_TOP);
	BIND_ENUM_CONSTANT(VALIGN_CENTER);
	BIND_ENUM_CONSTANT(VALIGN_BOTTOM);
	BIND_ENUM_CONSTANT(VALIGN_FILL);
}

Text::Text() {
}

Text::~Text() {
}
