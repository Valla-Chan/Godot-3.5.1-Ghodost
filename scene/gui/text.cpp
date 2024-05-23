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

void Text::_notification(int p_what) {
}

int Text::get_line_count() const {
	return 0;
}

int Text::get_visible_line_count() const {
	return 0;
}

int Text::get_total_character_count() const {
	return 0;
}

//void Text::set_align(Align p_align) {
//}

//Text::Align Text::get_align() const {
//	return Align(0);
//}


void Text::clear() {
	set_text("");
}

void Text::set_text(const String &p_string) {
}

String Text::get_text() const {
	return text;
}

void Text::set_visible_characters(int p_amount) {
}

int Text::get_visible_characters() const {
	return visible_characters;
}

void Text::set_percent_visible(float p_percent) {
	if (p_percent < 0 || p_percent >= 1) {
		visible_characters = -1;
		percent_visible = 1;

	} else {
		visible_characters = get_total_character_count() * p_percent;
		percent_visible = p_percent;
	}
	_change_notify("visible_characters");
	update();
}

float Text::get_percent_visible() const {
	return percent_visible;
}

void Text::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_align", "align"), &Text::set_align);
	//ClassDB::bind_method(D_METHOD("get_align"), &Text::get_align);
	ClassDB::bind_method(D_METHOD("set_text", "text"), &Text::set_text);
	ClassDB::bind_method(D_METHOD("get_text"), &Text::get_text);
	ClassDB::bind_method(D_METHOD("clear"), &Text::clear);

	ClassDB::bind_method(D_METHOD("get_line_count"), &Text::get_line_count);
	ClassDB::bind_method(D_METHOD("get_visible_line_count"), &Text::get_visible_line_count);
	ClassDB::bind_method(D_METHOD("get_total_character_count"), &Text::get_total_character_count);
	ClassDB::bind_method(D_METHOD("set_visible_characters", "amount"), &Text::set_visible_characters);
	ClassDB::bind_method(D_METHOD("get_visible_characters"), &Text::get_visible_characters);
	ClassDB::bind_method(D_METHOD("set_percent_visible", "percent_visible"), &Text::set_percent_visible);
	ClassDB::bind_method(D_METHOD("get_percent_visible"), &Text::get_percent_visible);

	//BIND_ENUM_CONSTANT(ALIGN_LEFT);
	//BIND_ENUM_CONSTANT(ALIGN_CENTER);
	//BIND_ENUM_CONSTANT(ALIGN_RIGHT);
	//BIND_ENUM_CONSTANT(ALIGN_FILL);

}

Text::Text(const String &p_text) {
	set_mouse_filter(MOUSE_FILTER_IGNORE);
	visible_characters = -1;
	percent_visible = 1;
	set_text(p_text);
}

Text::~Text() {
}
