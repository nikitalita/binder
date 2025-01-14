// File: T11_override.cpp
#include <T11.override.hpp> // Base
#include <iterator> // __gnu_cxx::__normal_iterator
#include <memory> // std::allocator
#include <sstream> // __str__
#include <string> // std::basic_string
#include <string> // std::char_traits

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// Base file:T11.override.hpp line:21
struct PyCallBack_Base : public Base {
	using Base::Base;

	void foo_void() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const Base *>(this), "foo_void");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return Base::foo_void();
	}
	void foo_void_pure() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const Base *>(this), "foo_void_pure");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"Base::foo_void_pure\"");
	}
	int foo_int() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const Base *>(this), "foo_int");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<int>::value) {
				static pybind11::detail::override_caster_t<int> caster;
				return pybind11::detail::cast_ref<int>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<int>(std::move(o));
		}
		return Base::foo_int();
	}
	std::string foo_sring() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const Base *>(this), "foo_sring");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<std::string>::value) {
				static pybind11::detail::override_caster_t<std::string> caster;
				return pybind11::detail::cast_ref<std::string>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<std::string>(std::move(o));
		}
		return Base::foo_sring();
	}
	std::string & foo_sring_r() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const Base *>(this), "foo_sring_r");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<std::string &>::value) {
				static pybind11::detail::override_caster_t<std::string &> caster;
				return pybind11::detail::cast_ref<std::string &>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<std::string &>(std::move(o));
		}
		return Base::foo_sring_r();
	}
};

void bind_T11_override(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // Base file:T11.override.hpp line:21
		pybind11::class_<Base, std::shared_ptr<Base>, PyCallBack_Base> cl(M(""), "Base", "");
		cl.def( pybind11::init( [](){ return new PyCallBack_Base(); } ) );
		cl.def(pybind11::init<PyCallBack_Base const &>());
		cl.def_readwrite("s_", &Base::s_);
		cl.def("foo_void", (void (Base::*)()) &Base::foo_void, "C++: Base::foo_void() --> void");
		cl.def("foo_void_pure", (void (Base::*)()) &Base::foo_void_pure, "C++: Base::foo_void_pure() --> void");
		cl.def("foo_int", (int (Base::*)()) &Base::foo_int, "C++: Base::foo_int() --> int");
		cl.def("foo_sring", (std::string (Base::*)()) &Base::foo_sring, "C++: Base::foo_sring() --> std::string");
		cl.def("foo_sring_r", (std::string & (Base::*)()) &Base::foo_sring_r, "C++: Base::foo_sring_r() --> std::string &", pybind11::return_value_policy::automatic);
		cl.def("assign", (class Base & (Base::*)(const class Base &)) &Base::operator=, "C++: Base::operator=(const class Base &) --> class Base &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_T11_override(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(T11_override, root_module) {
	root_module.doc() = "T11_override module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	static std::vector<std::string> const reserved_python_words {"nonlocal", "global", };

	auto mangle_namespace_name(
		[](std::string const &ns) -> std::string {
			if ( std::find(reserved_python_words.begin(), reserved_python_words.end(), ns) == reserved_python_words.end() ) return ns;
			else return ns+'_';
		}
	);

	std::vector< std::pair<std::string, std::string> > sub_modules {
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = modules[p.first].def_submodule( mangle_namespace_name(p.second).c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_T11_override(M);

}

// Source list file: TEST/T11_override.sources
// T11_override.cpp
// T11_override.cpp

// Modules list file: TEST/T11_override.modules
// 
