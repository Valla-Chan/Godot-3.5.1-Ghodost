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

#include "text_display.h"
#include "core/print_string.h"
#include "core/project_settings.h"
#include "core/translation.h"
#include "scene/resources/dynamic_font.h"

void TextDisplay::set_align(Align p_align) {
}

TextDisplay::Align TextDisplay::get_align() const {
	return Align(0);
}

void TextDisplay::set_visible_characters(int p_amount) {
	/*
	visible_chars = p_amount;
	if (get_total_character_count() > 0) {
		percent_visible = (float)p_amount / (float)total_char_cache;
	}
	_change_notify("percent_visible");
	update();
	*/
}

int TextDisplay::get_visible_characters() const {
	return visible_chars;
}

int TextDisplay::get_total_character_count() const {
	/*
	if (word_cache_dirty) {
		const_cast<Label *>(this)->regenerate_word_cache();
	}

	return total_char_cache;
	*/
	return text.length();
}

void TextDisplay::set_percent_visible(float p_percent) {
	if (p_percent < 0 || p_percent >= 1) {
		visible_chars = -1;
		percent_visible = 1;

	} else {
		visible_chars = get_total_character_count() * p_percent;
		percent_visible = p_percent;
	}
	_change_notify("visible_chars");
	update();
}

float TextDisplay::get_percent_visible() const {
	return percent_visible;
}

int TextDisplay::get_visible_line_count() const {
	/*
	int line_spacing = get_constant("line_spacing");
	int font_h = get_font_scaled("font")->get_height() + line_spacing;
	int lines_visible = (get_size().height - get_stylebox("normal")->get_minimum_size().height + line_spacing) / font_h;

	if (lines_visible > line_count) {
		lines_visible = line_count;
	}

	if (max_lines_visible >= 0 && lines_visible > max_lines_visible) {
		lines_visible = max_lines_visible;
	}

	return lines_visible;*/
	return 0;
}

void TextDisplay::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_align", "align"), &TextDisplay::set_align);
	ClassDB::bind_method(D_METHOD("get_align"), &TextDisplay::get_align);

	ClassDB::bind_method(D_METHOD("set_visible_characters", "amount"), &TextDisplay::set_visible_characters);
	ClassDB::bind_method(D_METHOD("get_visible_characters"), &TextDisplay::get_visible_characters);
	ClassDB::bind_method(D_METHOD("get_total_character_count"), &TextDisplay::get_total_character_count);

	ClassDB::bind_method(D_METHOD("set_percent_visible", "percent_visible"), &TextDisplay::set_percent_visible);
	ClassDB::bind_method(D_METHOD("get_percent_visible"), &TextDisplay::get_percent_visible);

	ClassDB::bind_method(D_METHOD("get_visible_line_count"), &TextDisplay::get_visible_line_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "align", PROPERTY_HINT_ENUM, "Left,Center,Right,Fill"), "set_align", "get_align");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "visible_characters", PROPERTY_HINT_RANGE, "-1,128000,1", PROPERTY_USAGE_EDITOR), "set_visible_characters", "get_visible_characters");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_visible", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_percent_visible", "get_percent_visible");

}

TextDisplay::TextDisplay() {
	visible_chars = -1;
	percent_visible = 1;
}

TextDisplay::~TextDisplay() {
}
