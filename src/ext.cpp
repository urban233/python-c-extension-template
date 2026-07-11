/**
 * @file ext.cpp
 * @brief Python bindings definition using nanobind.
 * @details This file defines the `_ext` module using `nanobind`. It specifies how 
 *          the C++ struct `Atom` and class `Molecule` are exposed, named, and mapped 
 *          into Python bindings, including methods, read/write attributes, read-only 
 *          properties, and memory reference policies.
 * @author Martin Urban
 * @date 2026-07-11
 */

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include "Atom.hpp"
#include "Molecule.hpp"

namespace nb = nanobind;

/**
 * @brief Definition of the Python C-Extension Module `_ext`.
 * @details Uses nanobind macros to bind C++ classes to the module object `m`.
 *          It configures documentation strings, class bindings, property/method mappings,
 *          and custom representations (`__repr__`).
 */
NB_MODULE(_ext, m) {
  m.doc() = "XYZ Molecular File Parser & Chemistry Extension";

  // Bind ext::Atom struct
  nb::class_<ext::Atom>(m, "Atom")
      .def(nb::init<std::string, double, double, double>(), 
           nb::arg("symbol"), nb::arg("x"), nb::arg("y"), nb::arg("z"),
           "Constructor to initialize an Atom instance.")
      .def_rw("symbol", &ext::Atom::symbol, "The chemical symbol.")
      .def_rw("x", &ext::Atom::x, "X coordinate in Angstroms.")
      .def_rw("y", &ext::Atom::y, "Y coordinate in Angstroms.")
      .def_rw("z", &ext::Atom::z, "Z coordinate in Angstroms.")
      .def("__repr__", [](const ext::Atom& a) {
        return "<Atom '" + a.symbol + "' (" + std::to_string(a.x) + ", " + 
               std::to_string(a.y) + ", " + std::to_string(a.z) + ")>";
      });

  // Bind ext::Molecule class
  nb::class_<ext::Molecule>(m, "Molecule")
      .def(nb::init<>(), "Constructs an empty Molecule instance.")
      .def_static("from_xyz_file", &ext::Molecule::FromXyzFile,
                  nb::arg("filepath"),
                  "Parses an XYZ file and returns a Molecule.")
      .def_prop_ro("comment", &ext::Molecule::GetComment,
                   "The title or metadata comment on the XYZ file.")
      .def_prop_ro("atom_count", &ext::Molecule::GetAtomCount,
                   "Total count of atoms in the molecule.")
      .def("get_atoms", &ext::Molecule::GetAtoms,
           nb::rv_policy::reference_internal,
           "Returns list of contained Atom objects (referenced internally).")
      .def("get_center_of_mass", &ext::Molecule::GetCenterOfMass,
           "Computes and returns the 3D geometric center [x, y, z].")
      .def("filter_by_element", &ext::Molecule::FilterByElement,
           nb::arg("symbol"),
           "Retrieves a subset list of atoms matching the given element symbol.");
}
