// File: T07_class.cpp
#include <T07.class.hpp> // Access
#include <T07.class.hpp> // Arrays
#include <T07.class.hpp> // ConstOverload
#include <T07.class.hpp> // Consts
#include <T07.class.hpp> // Enums
#include <T07.class.hpp> // Floating_point
#include <T07.class.hpp> // Integral
#include <T07.class.hpp> // Pointers_and_References
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_T07_class(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // Integral file:T07.class.hpp line:16
		pybind11::class_<Integral, std::shared_ptr<Integral>> cl(M(""), "Integral", "");
		cl.def( pybind11::init( [](Integral const &o){ return new Integral(o); } ) );
		cl.def( pybind11::init( [](){ return new Integral(); } ) );
		cl.def_readwrite("i", &Integral::i);
		cl.def_readwrite("ui", &Integral::ui);
		cl.def_readwrite("l", &Integral::l);
		cl.def_readwrite("ul", &Integral::ul);
		cl.def("assign", (struct Integral & (Integral::*)(const struct Integral &)) &Integral::operator=, "C++: Integral::operator=(const struct Integral &) --> struct Integral &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // Floating_point file:T07.class.hpp line:24
		pybind11::class_<Floating_point, std::shared_ptr<Floating_point>> cl(M(""), "Floating_point", "");
		cl.def( pybind11::init( [](){ return new Floating_point(); } ) );
		cl.def_readwrite("f", &Floating_point::f);
		cl.def_readwrite("d", &Floating_point::d);
		cl.def_readwrite("ld", &Floating_point::ld);
	}
	{ // Arrays file:T07.class.hpp line:31
		pybind11::class_<Arrays, std::shared_ptr<Arrays>> cl(M(""), "Arrays", "");
		cl.def( pybind11::init( [](){ return new Arrays(); } ) );
	}
	{ // Pointers_and_References file:T07.class.hpp line:39
		pybind11::class_<Pointers_and_References, std::shared_ptr<Pointers_and_References>> cl(M(""), "Pointers_and_References", "");
	}
	{ // Consts file:T07.class.hpp line:50
		pybind11::class_<Consts, std::shared_ptr<Consts>> cl(M(""), "Consts", "");
		cl.def( pybind11::init( [](){ return new Consts(); } ) );
		cl.def( pybind11::init( [](Consts const &o){ return new Consts(o); } ) );
		cl.def_readonly("public_Integral", &Consts::public_Integral);
		cl.def_readonly("public_int", &Consts::public_int);
	}
	{ // Enums file:T07.class.hpp line:68
		pybind11::class_<Enums, std::shared_ptr<Enums>> cl(M(""), "Enums", "");
		cl.def( pybind11::init( [](){ return new Enums(); } ) );

		pybind11::enum_<Enums::E1>(cl, "E1", pybind11::arithmetic(), "")
			.value("E1V", Enums::E1V)
			.export_values();


		pybind11::enum_<Enums::E2>(cl, "E2", "")
			.value("E2V", Enums::E2::E2V);


		pybind11::enum_<Enums::E3>(cl, "E3", "");

	}
	{ // Access file:T07.class.hpp line:83
		pybind11::class_<Access, std::shared_ptr<Access>> cl(M(""), "Access", "");
		cl.def( pybind11::init( [](){ return new Access(); } ) );
		cl.def_readwrite("i", &Access::i);
		cl.def("foo_public", (void (Access::*)()) &Access::foo_public, "C++: Access::foo_public() --> void");
		cl.def_static("foo", (float (*)(double)) &Access::foo, "C++: Access::foo(double) --> float", pybind11::arg(""));
	}
	{ // ConstOverload file:T07.class.hpp line:103
		pybind11::class_<ConstOverload, std::shared_ptr<ConstOverload>> cl(M(""), "ConstOverload", "");
		cl.def( pybind11::init( [](){ return new ConstOverload(); } ) );
		cl.def("foo", (void (ConstOverload::*)(int)) &ConstOverload::foo, "C++: ConstOverload::foo(int) --> void", pybind11::arg(""));
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

void bind_T07_class(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(T07_class, root_module) {
	root_module.doc() = "T07_class module";

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

	bind_T07_class(M);

}

// Source list file: TEST/T07_class.sources
// T07_class.cpp
// T07_class.cpp

// Modules list file: TEST/T07_class.modules
// 
