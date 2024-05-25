/**************************************************************************/
/*  text.h                                                               */
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

#ifndef TEXT_H
#define TEXT_H

#include "scene/gui/control.h"

class Text : public Control {
	GDCLASS(Text, Control);

public:
	enum Align {
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT,
		ALIGN_FILL
	};

	enum VAlign {

		VALIGN_TOP,
		VALIGN_CENTER,
		VALIGN_BOTTOM,
		VALIGN_FILL
	};

protected:
	mutable Map<String,Ref<Font>> font_scaled_cache;
	static void _bind_methods();

public:
	int font_size_override = 0;
	float font_scale = 1.0;

	virtual void set_align(Align p_align);
	virtual Align get_align() const;


	void set_font_size_override(int p_size);
	int get_font_size_override() const;
	void set_font_scale(float p_scale);
	float get_font_scale() const;
	Ref<Font> get_font_scaled(const String &p_font) const;

	Text();
	~Text();
};

VARIANT_ENUM_CAST(Text::Align);
VARIANT_ENUM_CAST(Text::VAlign);

#endif // TEXT_H
