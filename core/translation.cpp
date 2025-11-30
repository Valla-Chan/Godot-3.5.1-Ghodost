/**************************************************************************/
/*  translation.cpp                                                       */
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

#include "translation.h"

#include "core/io/resource_loader.h"
#include "core/os/os.h"
#include "core/project_settings.h"
#include "core/string/locales.h"

///////////////////////////////////////////////

PoolVector<String> Translation::_get_messages() const {
	PoolVector<String> msgs;
	msgs.resize(translation_map.size() * 2);
	int idx = 0;
	for (const Map<StringName, StringName>::Element *E = translation_map.front(); E; E = E->next()) {
		msgs.set(idx + 0, E->key());
		msgs.set(idx + 1, E->get());
		idx += 2;
	}

	return msgs;
}

PoolVector<String> Translation::_get_message_list() const {
	PoolVector<String> msgs;
	msgs.resize(translation_map.size());
	int idx = 0;
	for (const Map<StringName, StringName>::Element *E = translation_map.front(); E; E = E->next()) {
		msgs.set(idx, E->key());
		idx += 1;
	}

	return msgs;
}

void Translation::_set_messages(const PoolVector<String> &p_messages) {
	int msg_count = p_messages.size();
	ERR_FAIL_COND(msg_count % 2);

	PoolVector<String>::Read r = p_messages.read();

	for (int i = 0; i < msg_count; i += 2) {
		add_message(r[i + 0], r[i + 1]);
	}
}

void Translation::set_locale(const String &p_locale) {
	String univ_locale = TranslationServer::standardize_locale(p_locale);

	if (!TranslationServer::is_locale_valid(univ_locale)) {
		String trimmed_locale = TranslationServer::get_language_code(univ_locale);

		ERR_FAIL_COND_MSG(!TranslationServer::is_locale_valid(trimmed_locale), "Invalid locale: " + trimmed_locale + ".");

		locale = trimmed_locale;
	} else {
		locale = univ_locale;
	}

	if (OS::get_singleton()->get_main_loop()) {
		OS::get_singleton()->get_main_loop()->notification(MainLoop::NOTIFICATION_TRANSLATION_CHANGED);
	}
}

void Translation::add_context_message(const StringName &p_src_text, const StringName &p_xlated_text, const StringName &p_context) {
	if (p_context != StringName()) {
		WARN_PRINT("Translation class doesn't handle context.");
	}
	add_message(p_src_text, p_xlated_text);
}

StringName Translation::get_context_message(const StringName &p_src_text, const StringName &p_context) const {
	if (p_context != StringName()) {
		WARN_PRINT("Translation class doesn't handle context.");
	}
	return get_message(p_src_text);
}

void Translation::add_message(const StringName &p_src_text, const StringName &p_xlated_text) {
	translation_map[p_src_text] = p_xlated_text;
}

StringName Translation::get_message(const StringName &p_src_text) const {
	if (get_script_instance()) {
		return get_script_instance()->call("_get_message", p_src_text);
	}

	const Map<StringName, StringName>::Element *E = translation_map.find(p_src_text);
	if (!E) {
		return StringName();
	}

	return E->get();
}

void Translation::erase_message(const StringName &p_src_text) {
	translation_map.erase(p_src_text);
}

void Translation::get_message_list(List<StringName> *r_messages) const {
	for (const Map<StringName, StringName>::Element *E = translation_map.front(); E; E = E->next()) {
		r_messages->push_back(E->key());
	}
}

int Translation::get_message_count() const {
	return translation_map.size();
};

void Translation::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_locale", "locale"), &Translation::set_locale);
	ClassDB::bind_method(D_METHOD("get_locale"), &Translation::get_locale);
	ClassDB::bind_method(D_METHOD("add_message", "src_message", "xlated_message"), &Translation::add_message);
	ClassDB::bind_method(D_METHOD("get_message", "src_message"), &Translation::get_message);
	ClassDB::bind_method(D_METHOD("erase_message", "src_message"), &Translation::erase_message);
	ClassDB::bind_method(D_METHOD("get_message_list"), &Translation::_get_message_list);
	ClassDB::bind_method(D_METHOD("get_message_count"), &Translation::get_message_count);
	ClassDB::bind_method(D_METHOD("_set_messages"), &Translation::_set_messages);
	ClassDB::bind_method(D_METHOD("_get_messages"), &Translation::_get_messages);

	BIND_VMETHOD(MethodInfo(Variant::STRING, "_get_message", PropertyInfo(Variant::STRING, "src_message")));

	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "messages", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "_set_messages", "_get_messages");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "locale"), "set_locale", "get_locale");
}

Translation::Translation() :
		locale("en") {
}

///////////////////////////////////////////////

void ContextTranslation::add_context_message(const StringName &p_src_text, const StringName &p_xlated_text, const StringName &p_context) {
	if (p_context == StringName()) {
		add_message(p_src_text, p_xlated_text);
	} else {
		context_translation_map[p_context][p_src_text] = p_xlated_text;
	}
}

StringName ContextTranslation::get_context_message(const StringName &p_src_text, const StringName &p_context) const {
	if (p_context == StringName()) {
		return get_message(p_src_text);
	}

	const Map<StringName, Map<StringName, StringName>>::Element *context = context_translation_map.find(p_context);
	if (!context) {
		return StringName();
	}
	const Map<StringName, StringName>::Element *message = context->get().find(p_src_text);
	if (!message) {
		return StringName();
	}
	return message->get();
}

///////////////////////////////////////////////

bool TranslationServer::is_locale_valid(const String &p_locale) {
	const char **ptr = locale_list;

	while (*ptr) {
		if (*ptr == p_locale) {
			return true;
		}
		ptr++;
	}

	return false;
}

String TranslationServer::standardize_locale(const String &p_locale) {
	// Replaces '-' with '_' for macOS Sierra-style locales
	String univ_locale = p_locale.replace("-", "_");

	// Handles known non-ISO locale names used e.g. on Windows
	int idx = 0;
	while (locale_renames[idx][0] != nullptr) {
		if (locale_renames[idx][0] == univ_locale) {
			univ_locale = locale_renames[idx][1];
			break;
		}
		idx++;
	}

	return univ_locale;
}

String TranslationServer::get_language_code(const String &p_locale) {
	ERR_FAIL_COND_V_MSG(p_locale.length() < 2, p_locale, "Invalid locale '" + p_locale + "'.");
	// Most language codes are two letters, but some are three,
	// so we have to look for a regional code separator ('_' or '-')
	// to extract the left part.
	// For example we get 'nah_MX' as input and should return 'nah'.
	int split = p_locale.find("_");
	if (split == -1) {
		split = p_locale.find("-");
	}
	if (split == -1) { // No separator, so the locale is already only a language code.
		return p_locale;
	}
	return p_locale.left(split);
}

void TranslationServer::set_locale(const String &p_locale) {
	String univ_locale = standardize_locale(p_locale);

	if (!is_locale_valid(univ_locale)) {
		String trimmed_locale = get_language_code(univ_locale);
		print_verbose(vformat("Unsupported locale '%s', falling back to '%s'.", p_locale, trimmed_locale));

		if (!is_locale_valid(trimmed_locale)) {
			ERR_PRINT(vformat("Unsupported locale '%s', falling back to 'en'.", trimmed_locale));
			locale = "en";
		} else {
			locale = trimmed_locale;
		}
	} else {
		locale = univ_locale;
	}

	if (OS::get_singleton()->get_main_loop()) {
		OS::get_singleton()->get_main_loop()->notification(MainLoop::NOTIFICATION_TRANSLATION_CHANGED);
	}

	ResourceLoader::reload_translation_remaps();
}

String TranslationServer::get_locale() const {
	return locale;
}

String TranslationServer::get_locale_name(const String &p_locale) const {
	if (!locale_name_map.has(p_locale)) {
		return String();
	}
	return locale_name_map[p_locale];
}

PoolStringArray TranslationServer::get_loaded_locales() const {
	PoolStringArray locales;
	for (const Set<Ref<Translation>>::Element *E = translations.front(); E; E = E->next()) {
		const Ref<Translation> &t = E->get();
		ERR_FAIL_COND_V(t.is_null(), PoolStringArray());
		String l = t->get_locale();

		if (!locales.has(l)) {
			locales.push_back(l);
		}
	}

	locales.sort();
	return locales;
}

PoolStringArray TranslationServer::get_all_locales() {
	PoolStringArray locales;

	const char **ptr = locale_list;

	while (*ptr) {
		locales.push_back(*ptr);
		ptr++;
	}

	return locales;
}

PoolStringArray TranslationServer::get_all_standard_locales() {
	PoolStringArray locales;

	const char **ptr = locale_list;

	while (*ptr) {
		String locale_str = *ptr;
		if (locale_str.find("_") == -1) {
			locales.push_back(locale_str);
		}
		ptr++;
	}

	return locales;
}

PoolStringArray TranslationServer::get_all_locale_names() {
	PoolStringArray locales;

	const char **ptr = locale_names;

	while (*ptr) {
		locales.push_back(String::utf8(*ptr));
		ptr++;
	}

	return locales;
}

void TranslationServer::add_translation(const Ref<Translation> &p_translation) {
	translations.insert(p_translation);
}
void TranslationServer::remove_translation(const Ref<Translation> &p_translation) {
	translations.erase(p_translation);
}

void TranslationServer::clear() {
	translations.clear();
};

StringName TranslationServer::translate(const StringName &p_message) const {
	// Match given message against the translation catalog for the project locale.

	if (!enabled) {
		return p_message;
	}

	ERR_FAIL_COND_V_MSG(locale.length() < 2, p_message, "Could not translate message as configured locale '" + locale + "' is invalid.");

	// Locale can be of the form 'll_CC', i.e. language code and regional code,
	// e.g. 'en_US', 'en_GB', etc. It might also be simply 'll', e.g. 'en'.
	// To find the relevant translation, we look for those with locale starting
	// with the language code, and then if any is an exact match for the long
	// form. If not found, we fall back to a near match (another locale with
	// same language code).

	// Note: ResourceLoader::_path_remap reproduces this locale near matching
	// logic, so be sure to propagate changes there when changing things here.

	StringName res;
	String lang = get_language_code(locale);
	bool near_match = false;

	for (const Set<Ref<Translation>>::Element *E = translations.front(); E; E = E->next()) {
		const Ref<Translation> &t = E->get();
		ERR_FAIL_COND_V(t.is_null(), p_message);
		String l = t->get_locale();

		bool exact_match = (l == locale);
		if (!exact_match) {
			if (near_match) {
				continue; // Only near-match once, but keep looking for exact matches.
			}
			if (get_language_code(l) != lang) {
				continue; // Language code does not match.
			}
		}

		StringName r = t->get_message(p_message);
		if (!r) {
			continue;
		}
		res = r;

		if (exact_match) {
			break;
		} else {
			near_match = true;
		}
	}

	if (!res && fallback.length() >= 2) {
		// Try again with the fallback locale.
		String fallback_lang = get_language_code(fallback);
		near_match = false;

		for (const Set<Ref<Translation>>::Element *E = translations.front(); E; E = E->next()) {
			const Ref<Translation> &t = E->get();
			ERR_FAIL_COND_V(t.is_null(), p_message);
			String l = t->get_locale();

			bool exact_match = (l == fallback);
			if (!exact_match) {
				if (near_match) {
					continue; // Only near-match once, but keep looking for exact matches.
				}
				if (get_language_code(l) != fallback_lang) {
					continue; // Language code does not match.
				}
			}

			StringName r = t->get_message(p_message);
			if (!r) {
				continue;
			}
			res = r;

			if (exact_match) {
				break;
			} else {
				near_match = true;
			}
		}
	}

	if (!res) {
		return p_message;
	}

	return res;
}

TranslationServer *TranslationServer::singleton = nullptr;

bool TranslationServer::_load_translations(const String &p_from) {
	if (ProjectSettings::get_singleton()->has_setting(p_from)) {
		PoolVector<String> translations = ProjectSettings::get_singleton()->get(p_from);

		int tcount = translations.size();

		if (tcount) {
			PoolVector<String>::Read r = translations.read();

			for (int i = 0; i < tcount; i++) {
				Ref<Translation> tr = ResourceLoader::load(r[i]);
				if (tr.is_valid()) {
					add_translation(tr);
				}
			}
		}
		return true;
	}

	return false;
}

void TranslationServer::setup() {
	String test = GLOBAL_DEF("locale/test", "");
	test = test.strip_edges();
	if (test != "") {
		set_locale(test);
	} else {
		set_locale(OS::get_singleton()->get_locale());
	}
	fallback = GLOBAL_DEF("locale/fallback", "en");
#ifdef TOOLS_ENABLED
	{
		String options = "";
		int idx = 0;
		while (locale_list[idx]) {
			if (idx > 0) {
				options += ",";
			}
			options += locale_list[idx];
			idx++;
		}
		ProjectSettings::get_singleton()->set_custom_property_info("locale/fallback", PropertyInfo(Variant::STRING, "locale/fallback", PROPERTY_HINT_ENUM, options));
	}
#endif
}

void TranslationServer::set_tool_translation(const Ref<Translation> &p_translation) {
	tool_translation = p_translation;
}

StringName TranslationServer::tool_translate(const StringName &p_message, const StringName &p_context) const {
	if (tool_translation.is_valid()) {
		StringName r = tool_translation->get_context_message(p_message, p_context);
		if (r) {
			return r;
		}
	}
	return p_message;
}

void TranslationServer::set_doc_translation(const Ref<Translation> &p_translation) {
	doc_translation = p_translation;
}

StringName TranslationServer::doc_translate(const StringName &p_message) const {
	if (doc_translation.is_valid()) {
		StringName r = doc_translation->get_message(p_message);
		if (r) {
			return r;
		}
	}
	return p_message;
}

void TranslationServer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_locale", "locale"), &TranslationServer::set_locale);
	ClassDB::bind_method(D_METHOD("get_locale"), &TranslationServer::get_locale);

	ClassDB::bind_method(D_METHOD("get_locale_name", "locale"), &TranslationServer::get_locale_name);

	ClassDB::bind_method(D_METHOD("translate", "message"), &TranslationServer::translate);

	ClassDB::bind_method(D_METHOD("add_translation", "translation"), &TranslationServer::add_translation);
	ClassDB::bind_method(D_METHOD("remove_translation", "translation"), &TranslationServer::remove_translation);

	ClassDB::bind_method(D_METHOD("clear"), &TranslationServer::clear);

	ClassDB::bind_method(D_METHOD("get_loaded_locales"), &TranslationServer::get_loaded_locales);
	ClassDB::bind_method(D_METHOD("get_all_locales"), &TranslationServer::get_all_locales);
	ClassDB::bind_method(D_METHOD("get_all_standard_locales"), &TranslationServer::get_all_standard_locales);
	ClassDB::bind_method(D_METHOD("get_all_locale_names"), &TranslationServer::get_all_locale_names);
}

void TranslationServer::load_translations() {
	String locale = get_locale();
	_load_translations("locale/translations"); //all
	_load_translations("locale/translations_" + locale.substr(0, 2));

	if (locale.substr(0, 2) != locale) {
		_load_translations("locale/translations_" + locale);
	}
}

TranslationServer::TranslationServer() :
		locale("en"),
		enabled(true) {
	singleton = this;

	for (int i = 0; locale_list[i]; ++i) {
		locale_name_map.insert(locale_list[i], String::utf8(locale_names[i]));
	}
}
