// cBioMOL - open C++ and Python platform for BioMOLecular visualization and analysis
// -------------------------------------------------------------------
// This file contains source code for the cBioMOL computer program
// Copyright (C) 2025 Hannah Kullik, Martin Urban (hannah.kullik@studmail.w-hs.de,
// martin.urban@studmail.w-hs.de) Source code is available at <https://github.com/urban233/cBioMOL>
// -------------------------------------------------------------------
// It is unlawful to modify or remove this copyright notice.
// -------------------------------------------------------------------
// Please see the accompanying LICENSE file for further information.
// -------------------------------------------------------------------
// Primary author of this source file:
// Hannah Kullik
// -------------------------------------------------------------------
// Additional authors of this source file include:
//
// ==============================================================================
//
#include "../engine/Engine.hpp"

#include "PyMOL.h"
#include "PyMOLOptions.h"

cbiomol::Engine::Engine()
{
  m_IsRunning = false;

  // PyObject *pymol = nullptr; /* pymol object instance */
  // PyObject *pyoptions = Py_None;
  // int singleton = false;

  // if (!PyArg_ParseTuple(args, "O|Op", &pymol, &pyoptions, &singleton)) {
  //   return nullptr;
  // }

  // if (singleton && SingletonPyMOLGlobals) {
  //   PyErr_SetString(PyExc_RuntimeError, "Singleton already exists");
  //   return nullptr;
  // }

  CPyMOLOptions* options = PyMOLOptions_New();

  // if (pyoptions != Py_None) {
  //   PConvertOptions(options, pyoptions);
  // }

  m_PyMOL = PyMOL_NewWithOptions(options);
  PyMOLOptions_Free(options);

  // if (!I) {
  //   PyErr_SetString(PyExc_Exception, "PyMOL_NewWithOptions failed");
  //   return nullptr;
  // }

  // PyMOLGlobals *G = PyMOL_GetGlobals(I);

  // if (singleton) {
  //   SingletonPyMOLGlobals = G;
  // } else {
  //   // Creating a non-singleton instance disables auto-library mode
  //   auto_library_mode_disabled = true;
  // }

  G->P_inst = pymol::calloc<CP_inst>(1);
  G->P_inst->obj = pymol;
  G->P_inst->dict = PyObject_GetAttrString(pymol, "__dict__");
  Py_DECREF(G->P_inst->dict); // borrow reference

  PyObject *tmp = PyCapsule_New(I, nullptr, nullptr);
  PyObject_SetAttrString(pymol, "__pymol__", tmp);
  Py_DECREF(tmp);

  for (int a = 0; a < MAX_SAVED_THREAD; ++a) {
    G->P_inst->savedThread[a].id = -1;
  }
}
cbiomol::Engine::~Engine()
{
  if (m_PyMOL) {
    if (m_IsRunning == true) {
      PyMOL_Stop(m_PyMOL);
    }
  }
  PyMOL_Free(m_PyMOL);
  m_PyMOL = nullptr;
}

void init()
{
  // return PyCapsule_New(PyMOL_GetGlobalsHandle(I), nullptr, PyMOLGlobalsCapsuleDestructor);
}