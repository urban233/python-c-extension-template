#include <nanobind/nanobind.h>

namespace nb = nanobind;

NB_MODULE(_cmd2, m)
{
  m.doc() = "Modern OOP API";

  nb::class_<cbiomol::Engine>(m, "Engine")
      .def(nb::init(), "Constructor for the Engine.");

  nb::class_<Protein>(m, "Protein")
      .def(nb::init(), "Initialize an empty Protein object.")
      .def("addingTwo", &Protein::addingTwo, "Adds two to the internal state of the protein.")
      .def("load", &Protein::load, "Loads the protein data from a file path.");
}
