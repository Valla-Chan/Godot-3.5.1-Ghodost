/**************************************************************************/
/*  label.h                                                               */
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

#ifndef LABEL_H
#define LABEL_H

#include "scene/gui/text.h"

class Label : public TextBase {
	GDCLASS(Label, TextBase);

public:

private:
	Align align;
	VAlign valign;
	String text;
	String xl_text;
	bool autowrap;
	bool clip;
	Size2 minsize;
	int line_count;
	bool uppercase;

	int get_longest_line_width() const;

	struct WordCache {
		enum {
			CHAR_NEWLINE = -1,
			CHAR_WRAPLINE = -2
		};
		int char_pos; // if -1, then newline
		int word_len;
		int pixel_width;
		int space_count;
		WordCache *next;
		WordCache() {
			char_pos = 0;
			word_len = 0;
			pixel_width = 0;
			next = nullptr;
			space_count = 0;
		}
	};

	bool word_cache_dirty;
	void regenerate_word_cache();

	float percent_visible;

	WordCache *word_cache;
	int total_char_cache;
	int visible_chars;
	int lines_skipped;
	int max_lines_visible;
	//VALLA EDITS
	Size2 extra_spacing;

protected:
	void _notification(int p_what);
	void _update_font_scale();

	static void _bind_methods();
	// bind helpers
public:
	virtual Size2 get_minimum_size() const;

	void set_align(Align p_align);
	Align get_align() const;

	void set_valign(VAlign p_align);
	VAlign get_valign() const;

	void set_text(const String &p_string);
	String get_text() const;

	void set_autowrap(bool p_autowrap);
	bool has_autowrap() const;

	void set_uppercase(bool p_uppercase);
	bool is_uppercase() const;


	void set_extra_spacing(Size2 p_amount);
	Size2 get_extra_spacing() const;

	void set_visible_characters(int p_amount);
	int get_visible_characters() const;
	int get_total_character_count() const;

	void set_clip_text(bool p_clip);
	bool is_clipping_text() const;

	void set_percent_visible(float p_percent);
	float get_percent_visible() const;

	void set_lines_skipped(int p_lines);
	int get_lines_skipped() const;

	void set_max_lines_visible(int p_lines);
	int get_max_lines_visible() const;

	int get_line_height() const;
	int get_line_count() const;
	int get_visible_line_count() const;

	Label(const String &p_text = String());
	~Label();
};

#endif // LABEL_H
