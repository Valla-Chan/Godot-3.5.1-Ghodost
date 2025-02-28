/**************************************************************************/
/*  resource.cpp                                                          */
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

#include "resource.h"

#include "core/core_string_names.h"
#include "core/io/resource_loader.h"
#include "core/os/file_access.h"
#include "core/os/os.h"
#include "core/script_language.h"
#include "scene/main/node.h" //only so casting works
#include "scene/property_utils.h"
#include "core/variant_parser.h"

#include <stdio.h>

void Resource::emit_changed() {
	emit_signal(CoreStringNames::get_singleton()->changed);
}

void Resource::_resource_path_changed() {
}

void Resource::set_path(const String &p_path, bool p_take_over) {
	if (path_cache == p_path) {
		return;
	}

	if (path_cache != "") {
		ResourceCache::lock.write_lock();
		ResourceCache::resources.erase(path_cache);
		ResourceCache::lock.write_unlock();
	}

	path_cache = "";

	ResourceCache::lock.read_lock();
	bool has_path = ResourceCache::resources.has(p_path);
	ResourceCache::lock.read_unlock();

	if (has_path) {
		if (p_take_over) {
			ResourceCache::lock.write_lock();
			Resource **res = ResourceCache::resources.getptr(p_path);
			if (res) {
				(*res)->set_name("");
			}
			ResourceCache::lock.write_unlock();
		} else {
			ResourceCache::lock.read_lock();
			bool exists = ResourceCache::resources.has(p_path);
			ResourceCache::lock.read_unlock();

			ERR_FAIL_COND_MSG(exists, "Another resource is loaded from path '" + p_path + "' (possible cyclic resource inclusion).");
		}
	}
	path_cache = p_path;

	if (path_cache != "") {
		ResourceCache::lock.write_lock();
		ResourceCache::resources[path_cache] = this;
		ResourceCache::lock.write_unlock();
	}

	_change_notify("resource_path");
	_resource_path_changed();
}

String Resource::get_path() const {
	return path_cache;
}

String Resource::get_filename() const {
	return path_cache.get_file().get_basename();
}

void Resource::set_subindex(int p_sub_index) {
	subindex = p_sub_index;
}

int Resource::get_subindex() const {
	return subindex;
}

void Resource::set_name(const String &p_name) {
	name = p_name;
	_change_notify("resource_name");
}
String Resource::get_name() const {
	return name;
}

bool Resource::editor_can_reload_from_file() {
	return true; //by default yes
}

void Resource::reload_from_file() {
	String path = get_path();
	if (!path.is_resource_file()) {
		return;
	}

	Ref<Resource> s = ResourceLoader::load(ResourceLoader::path_remap(path), get_class(), true);

	if (!s.is_valid()) {
		return;
	}

	List<PropertyInfo> pi;
	//inherits_state = s->inherits_state;
	copy_from(s);
}



Error Resource::copy_from(const Ref<Resource> &p_resource, bool p_copy_inheritance) {
	ERR_FAIL_COND_V(p_resource.is_null(), ERR_INVALID_PARAMETER);
	if (get_class() != p_resource->get_class()) {
		return ERR_INVALID_PARAMETER;
	}

	//reset_state(); //may want to reset state

	List<PropertyInfo> pi;
	p_resource->get_property_list(&pi);

	for (List<PropertyInfo>::Element *E = pi.front(); E; E = E->next()) {
		if (!(E->get().usage & PROPERTY_USAGE_STORAGE)) {
			continue;
		}
		if (E->get().name == "resource_path" ) {
			continue; //do not change path
		}
		if (!p_copy_inheritance && (E->get().name == "resource_inherits_state" || E->get().name == "script_instance")) {
			continue; //do not change inheritance/script if set not to
		}

		set(E->get().name, p_resource->get(E->get().name));
	}
	return OK;
}

// revert foreign properties to inherits value
void Resource::properties_revert_foreign() {
	if (!inherits_state.is_valid()) {
		return;
	}
	List<PropertyInfo> plist;
	get_property_list(&plist);

	Vector<String> proplist = _get_resfile_propnames();

	for (List<PropertyInfo>::Element *E = plist.front(); E; E = E->next()) {
		if (!(E->get().usage & PROPERTY_USAGE_STORAGE)) {
			continue;
		}
		if (E->get().name == "resource_path") {
			continue; //do not change path
		}
		if ((E->get().name == "resource_inherits_state" || E->get().name == "script_instance")) {
			continue; //do not change inheritance/script
		}

		String propname = E->get().name;
		if (inherits_state.is_valid()) { // && !is_inherited_state_property_value_saved(propname, get(propname))

			// HACK: if a property has a default value, and the res file does NOT have an override for that property,
			// then this property most likely needs to be reverted.

			if (get(propname) == PropertyUtils::get_property_default_value(this, propname, nullptr)) {
				if (proplist.find(propname) == -1) {
					this->set(propname, property_get_revert(propname));
					continue;
				}
			}

		}
		
	}
}

Vector<String> Resource::_get_resfile_propnames() const {
	Vector<String> propnames = {};
	Error err;
	String file = FileAccess::get_file_as_string(get_path(), &err);
	//auto path = get_path();
	

	if (err != OK) {
		return propnames;
	}
	// make sure the properties chunk is below "[resource]"
	// TODO: this probably causes some kind of issue with subresources.
	int start = file.find("[resource]");
	if (start == -1)
		return propnames;
	int end = file.find("\n\n", start);
	if (end == -1) {
		end = file.length();
	}

	file = file.substr(start, end - start);
	Vector<String> pairs = file.split("\n",false);
	
	for (size_t i = 0; i < pairs.size(); i++) {
		Vector<String> props_n_values = pairs[i].split("=",false);
		if (props_n_values.size() < 2) {
			continue;
		}
		propnames.push_back(props_n_values[0].strip_edges());
	}

	return propnames;

}

Ref<Resource> Resource::duplicate_for_local_scene(Node *p_for_scene, Map<Ref<Resource>, Ref<Resource>> &remap_cache) {
	List<PropertyInfo> plist;
	get_property_list(&plist);

	Ref<Resource> r = Object::cast_to<Resource>(ClassDB::instance(get_class()));
	ERR_FAIL_COND_V(r.is_null(), Ref<Resource>());

	r->local_scene = p_for_scene;

	for (List<PropertyInfo>::Element *E = plist.front(); E; E = E->next()) {
		if (!(E->get().usage & PROPERTY_USAGE_STORAGE)) {
			continue;
		}
		Variant p = get(E->get().name);
		if (p.get_type() == Variant::OBJECT) {
			RES sr = p;
			if (sr.is_valid()) {
				if (sr->is_local_to_scene()) {
					if (remap_cache.has(sr)) {
						p = remap_cache[sr];
					} else {
						RES dupe = sr->duplicate_for_local_scene(p_for_scene, remap_cache);
						p = dupe;
						remap_cache[sr] = dupe;
					}
				}
			}
		}

		r->set(E->get().name, p);
	}

	return r;
}

void Resource::configure_for_local_scene(Node *p_for_scene, Map<Ref<Resource>, Ref<Resource>> &remap_cache) {
	List<PropertyInfo> plist;
	get_property_list(&plist);

	local_scene = p_for_scene;

	for (List<PropertyInfo>::Element *E = plist.front(); E; E = E->next()) {
		if (!(E->get().usage & PROPERTY_USAGE_STORAGE)) {
			continue;
		}
		Variant p = get(E->get().name);
		if (p.get_type() == Variant::OBJECT) {
			RES sr = p;
			if (sr.is_valid()) {
				if (sr->is_local_to_scene()) {
					if (!remap_cache.has(sr)) {
						sr->configure_for_local_scene(p_for_scene, remap_cache);
						remap_cache[sr] = sr;
					}
				}
			}
		}
	}
}

Ref<Resource> Resource::duplicate(bool p_subresources) const {
	List<PropertyInfo> plist;
	get_property_list(&plist);

	Ref<Resource> r = (Resource *)ClassDB::instance(get_class());
	ERR_FAIL_COND_V(r.is_null(), Ref<Resource>());

	for (List<PropertyInfo>::Element *E = plist.front(); E; E = E->next()) {
		if (!(E->get().usage & PROPERTY_USAGE_STORAGE)) {
			continue;
		}
		Variant p = get(E->get().name);

		if ((p.get_type() == Variant::DICTIONARY || p.get_type() == Variant::ARRAY)) {
			r->set(E->get().name, p.duplicate(p_subresources));
		} else if (p.get_type() == Variant::OBJECT && (p_subresources || (E->get().usage & PROPERTY_USAGE_DO_NOT_SHARE_ON_DUPLICATE))) {
			RES sr = p;
			if (sr.is_valid()) {
				r->set(E->get().name, sr->duplicate(p_subresources));
			}
		} else {
			r->set(E->get().name, p);
		}
	}

	return r;
}

void Resource::_set_path(const String &p_path) {
	set_path(p_path, false);
}

void Resource::_take_over_path(const String &p_path) {
	set_path(p_path, true);
}

RID Resource::get_rid() const {
	return RID();
}

void Resource::register_owner(Object *p_owner) {
	owners.insert(p_owner->get_instance_id());
}

void Resource::unregister_owner(Object *p_owner) {
	owners.erase(p_owner->get_instance_id());
}

void Resource::notify_change_to_owners() {
	for (Set<ObjectID>::Element *E = owners.front(); E; E = E->next()) {
		Object *obj = ObjectDB::get_instance(E->get());
		ERR_CONTINUE_MSG(!obj, "Object was deleted, while still owning a resource."); //wtf
		//TODO store string
		obj->call("resource_changed", RES(this));
	}
}

#ifdef TOOLS_ENABLED

uint32_t Resource::hash_edited_version() const {
	uint32_t hash = hash_djb2_one_32(get_edited_version());

	List<PropertyInfo> plist;
	get_property_list(&plist);

	for (List<PropertyInfo>::Element *E = plist.front(); E; E = E->next()) {
		if (E->get().usage & PROPERTY_USAGE_STORAGE && E->get().type == Variant::OBJECT && E->get().hint == PROPERTY_HINT_RESOURCE_TYPE) {
			RES res = get(E->get().name);
			if (res.is_valid()) {
				hash = hash_djb2_one_32(res->hash_edited_version(), hash);
			}
		}
	}

	return hash;
}

#endif

void Resource::set_local_to_scene(bool p_enable) {
	local_to_scene = p_enable;
}

bool Resource::is_local_to_scene() const {
	return local_to_scene;
}

Node *Resource::get_local_scene() const {
	if (local_scene) {
		return local_scene;
	}

	if (_get_local_scene_func) {
		return _get_local_scene_func();
	}

	return nullptr;
}

void Resource::setup_local_to_scene() {
	if (get_script_instance()) {
		get_script_instance()->call("_setup_local_to_scene");
	}
}

Node *(*Resource::_get_local_scene_func)() = nullptr;

void Resource::set_as_translation_remapped(bool p_remapped) {
	if (remapped_list.in_list() == p_remapped) {
		return;
	}

	ResourceCache::lock.write_lock();

	if (p_remapped) {
		ResourceLoader::remapped_list.add(&remapped_list);
	} else {
		ResourceLoader::remapped_list.remove(&remapped_list);
	}

	ResourceCache::lock.write_unlock();
}

bool Resource::is_translation_remapped() const {
	return remapped_list.in_list();
}

#ifdef TOOLS_ENABLED
//helps keep IDs same number when loading/saving scenes. -1 clears ID and it Returns -1 when no id stored
void Resource::set_id_for_path(const String &p_path, int p_id) {
	if (p_id == -1) {
		ResourceCache::path_cache_lock.write_lock();
		ResourceCache::resource_path_cache[p_path].erase(get_path());
		ResourceCache::path_cache_lock.write_unlock();
	} else {
		ResourceCache::path_cache_lock.write_lock();
		ResourceCache::resource_path_cache[p_path][get_path()] = p_id;
		ResourceCache::path_cache_lock.write_unlock();
	}
}

int Resource::get_id_for_path(const String &p_path) const {
	ResourceCache::path_cache_lock.read_lock();
	if (ResourceCache::resource_path_cache[p_path].has(get_path())) {
		int result = ResourceCache::resource_path_cache[p_path][get_path()];
		ResourceCache::path_cache_lock.read_unlock();
		return result;
	} else {
		ResourceCache::path_cache_lock.read_unlock();
		return -1;
	}
}
#endif

bool Resource::property_can_revert(const String &p_name) const {
	if (inherits_state.is_valid()) {
		bool value_valid;
		Variant value = get(p_name, &value_valid);
		if (!value_valid) {
			return false;
		}
		Variant inherits_value = inherits_state->get(p_name, &value_valid);
		if (!value_valid) {
			return false;
		}
		bool diff = PropertyUtils::is_property_value_different(value, inherits_value);
		return diff;
		
	} else {
		bool value_valid;
		Variant value = get(p_name, &value_valid);
		if (!value_valid) {
			return false;
		}
		Variant inherits_value = PropertyUtils::get_property_default_value(this, p_name, &value_valid);
		if (!value_valid) {
			return false;
		}
		bool diff = PropertyUtils::is_property_value_different(value, inherits_value);
		return diff;
	}
	
}

Variant Resource::property_get_revert(const String &p_name) const {
	Variant r_ret;
	if (inherits_state.is_valid()) {
		bool value_valid;
		Variant inherits_value = inherits_state->get(p_name, &value_valid);
		if (value_valid) {
			r_ret = inherits_value;
		}
	} else {
		bool value_valid;
		Variant inherits_value = PropertyUtils::get_property_default_value(this, p_name, &value_valid);
		if (value_valid) {
			r_ret = inherits_value;
		}
	}
	return r_ret;
}

void Resource::_validate_property(PropertyInfo &p_property) const {
	if (p_property.name == "resource_inherits") {
		p_property.hint_string = get_class();
	}
}

bool Resource::setup_inherits_state(const Ref<Resource> &p_resource, bool p_copy) {
	if (get_script_instance()) {
		return get_script_instance()->call("_setup_local_to_scene", p_resource);
	}

	ERR_FAIL_COND_V_MSG(p_resource.is_valid() && !is_class(p_resource->get_class_name()), false, "Resources must be of (or class inherit) the same class when setting up state inheritance");

	if (p_copy && p_resource.is_valid()) {
		copy_from(p_resource);
	}
	return true;
}

void Resource::copy_inherits_state(const Ref<Resource> &p_resource) {
	if (setup_inherits_state(p_resource, true)) {
		inherits_state = p_resource;
	}
}

void Resource::set_inherits_state(const Ref<Resource> &p_resource) {
	if (setup_inherits_state(p_resource, false)) {
		inherits_state = p_resource;
	}
}

Ref<Resource> Resource::get_inherits_state() const {
	return inherits_state;
}

bool Resource::is_inherited_state_property_value_saved(const StringName &p_name, const Variant &p_value) const {
	if (get_script_instance()) {
		return get_script_instance()->call("_is_inherited_state_property_value_saved", p_name, p_value);
	}

	bool default_value_valid;
	Variant default_value = inherits_state->get(p_name, &default_value_valid);
	if (!default_value_valid) {
		return true; // Not a default value, so save.
	}

	if (default_value.get_type() != Variant::NIL && bool(Variant::evaluate(Variant::OP_EQUAL, p_value, default_value))) {
		return false;
	}

	return true;
}

bool Resource::is_property_value_saved(const StringName &p_property, const Variant &p_value) const {
	if (!inherits_state.is_valid()) {
		Variant default_value = ClassDB::class_get_default_property_value(get_class(), p_property);

		if (default_value.get_type() != Variant::NIL && bool(Variant::evaluate(Variant::OP_EQUAL, p_value, default_value))) {
			return false;
		}

		return true;
	} else {
		return is_inherited_state_property_value_saved(p_property, p_value);
	}
}

void Resource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_path", "path"), &Resource::_set_path);
	ClassDB::bind_method(D_METHOD("take_over_path", "path"), &Resource::_take_over_path);
	ClassDB::bind_method(D_METHOD("get_path"), &Resource::get_path);
	ClassDB::bind_method(D_METHOD("get_filename"), &Resource::get_filename);
	ClassDB::bind_method(D_METHOD("set_name", "name"), &Resource::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Resource::get_name);
	ClassDB::bind_method(D_METHOD("get_rid"), &Resource::get_rid);
	ClassDB::bind_method(D_METHOD("set_local_to_scene", "enable"), &Resource::set_local_to_scene);
	ClassDB::bind_method(D_METHOD("is_local_to_scene"), &Resource::is_local_to_scene);
	ClassDB::bind_method(D_METHOD("get_local_scene"), &Resource::get_local_scene);
	ClassDB::bind_method(D_METHOD("setup_local_to_scene"), &Resource::setup_local_to_scene);
	ClassDB::bind_method(D_METHOD("copy_inherits_state", "base"), &Resource::copy_inherits_state);
	ClassDB::bind_method(D_METHOD("set_inherits_state", "base"), &Resource::set_inherits_state);
	ClassDB::bind_method(D_METHOD("get_inherits_state"), &Resource::get_inherits_state);
	ClassDB::bind_method(D_METHOD("is_property_value_saved", "property", "value"), &Resource::is_property_value_saved);
	ClassDB::bind_method(D_METHOD("emit_changed"), &Resource::emit_changed);

	ClassDB::bind_method(D_METHOD("property_can_revert", "name"), &Resource::property_can_revert);
	ClassDB::bind_method(D_METHOD("property_get_revert", "name"), &Resource::property_get_revert);


	ClassDB::bind_method(D_METHOD("duplicate", "subresources"), &Resource::duplicate, DEFVAL(false));
	ADD_SIGNAL(MethodInfo("changed"));
	ADD_GROUP("Resource", "resource_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "resource_local_to_scene"), "set_local_to_scene", "is_local_to_scene");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "resource_path", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_path", "get_path");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "resource_name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_inherits_state", PROPERTY_HINT_RESOURCE_TYPE, get_class_static()), "set_inherits_state", "get_inherits_state");

	BIND_VMETHOD(MethodInfo("_setup_local_to_scene"));
	BIND_VMETHOD(MethodInfo("_setup_inherits_state"));
	BIND_VMETHOD(MethodInfo("_is_inherited_state_property_value_saved", PropertyInfo(Variant::STRING, "property"), PropertyInfo(Variant::NIL, "value")));
}

Resource::Resource() :
		remapped_list(this) {
#ifdef TOOLS_ENABLED
	last_modified_time = 0;
	import_last_modified_time = 0;
#endif

	subindex = 0;
	local_to_scene = false;
	local_scene = nullptr;
}

Resource::~Resource() {
	if (path_cache != "") {
		ResourceCache::lock.write_lock();
		ResourceCache::resources.erase(path_cache);
		ResourceCache::lock.write_unlock();
	}
	if (owners.size()) {
		WARN_PRINT("Resource is still owned.");
	}
}

HashMap<String, Resource *> ResourceCache::resources;
#ifdef TOOLS_ENABLED
HashMap<String, HashMap<String, int>> ResourceCache::resource_path_cache;
#endif

RWLock ResourceCache::lock;
#ifdef TOOLS_ENABLED
RWLock ResourceCache::path_cache_lock;
#endif

void ResourceCache::clear() {
	if (resources.size()) {
		ERR_PRINT("Resources still in use at exit (run with --verbose for details).");
		if (OS::get_singleton()->is_stdout_verbose()) {
			const String *K = nullptr;
			while ((K = resources.next(K))) {
				Resource *r = resources[*K];
				print_line(vformat("Resource still in use: %s (%s)", *K, r->get_class()));
			}
		}
	}

	resources.clear();
}

void ResourceCache::reload_externals() {
}

bool ResourceCache::has(const String &p_path) {
	lock.read_lock();
	bool b = resources.has(p_path);
	lock.read_unlock();

	return b;
}
Resource *ResourceCache::get(const String &p_path) {
	lock.read_lock();

	Resource **res = resources.getptr(p_path);

	lock.read_unlock();

	if (!res) {
		return nullptr;
	}

	return *res;
}

void ResourceCache::get_cached_resources(List<Ref<Resource>> *p_resources) {
	lock.read_lock();
	const String *K = nullptr;
	while ((K = resources.next(K))) {
		Resource *r = resources[*K];
		p_resources->push_back(Ref<Resource>(r));
	}
	lock.read_unlock();
}

int ResourceCache::get_cached_resource_count() {
	lock.read_lock();
	int rc = resources.size();
	lock.read_unlock();

	return rc;
}

void ResourceCache::dump(const char *p_file, bool p_short) {
#ifdef DEBUG_ENABLED
	lock.read_lock();

	Map<String, int> type_count;

	FileAccess *f = nullptr;
	if (p_file) {
		f = FileAccess::open(String::utf8(p_file), FileAccess::WRITE);
		ERR_FAIL_COND_MSG(!f, "Cannot create file at path '" + String::utf8(p_file) + "'.");
	}

	const String *K = nullptr;
	while ((K = resources.next(K))) {
		Resource *r = resources[*K];

		if (!type_count.has(r->get_class())) {
			type_count[r->get_class()] = 0;
		}

		type_count[r->get_class()]++;

		if (!p_short) {
			if (f) {
				f->store_line(r->get_class() + ": " + r->get_path());
			}
		}
	}

	for (Map<String, int>::Element *E = type_count.front(); E; E = E->next()) {
		if (f) {
			f->store_line(E->key() + " count: " + itos(E->get()));
		}
	}
	if (f) {
		f->close();
		memdelete(f);
	}

	lock.read_unlock();
#else
	WARN_PRINT("ResourceCache::dump only with in debug builds.");
#endif
}
