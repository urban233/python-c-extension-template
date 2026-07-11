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
#ifndef CBIOMOL_ENGINE_HPP
#define CBIOMOL_ENGINE_HPP

// @file Engine.hpp
// @brief Declares the `Engine` class, the central lifecycle manager for a CPyMOL session.
//
// `Engine` is a non-copyable, non-movable RAII wrapper around a `CPyMOL*` handle.
// It is responsible for:
//   - Initializing the underlying PyMOL C library on construction.
//   - Binding the C++ state to a Python PyMOL object so that the Python layer
//     can drive rendering and analysis through the same CPyMOL instance.
//   - Releasing all PyMOL resources deterministically on destruction,
//     preventing memory leaks and dangling pointers.
//
// Only one `Engine` instance should exist per PyMOL session. Creating multiple
// instances is prevented by the deleted copy/move operations.

#include <nanobind/nanobind.h>

// @brief Alias for the nanobind namespace used throughout this translation unit.
namespace nb = nanobind;

namespace cbiomol {
// @brief Central lifecycle manager for a CPyMOL session.
//
// Wraps a raw `CPyMOL*` pointer using RAII so that the PyMOL C library is
// always initialized before use and always shut down when the `Engine` goes
// out of scope — even if an exception is thrown.
//
// ### Ownership model
// `Engine` has *exclusive* ownership of the `CPyMOL*` handle stored in
// `m_PyMOL`. Copying or moving the handle would introduce shared or
// transferred ownership, both of which risk double-free corruption. All four
// copy/move special members are therefore explicitly deleted (Rule of Five).
//
// ### Thread safety
// `Engine` is not thread-safe. All calls into CPyMOL must be made from the
// thread that constructed the `Engine`, or external synchronization must be
// provided by the caller.
class Engine {
public:
  // @brief Constructs an `Engine` and starts a CPyMOL session.
  //
  // Initializes the CPyMOL C library, sets `m_IsRunning` to `true`, and
  // links the newly created `CPyMOL*` handle back into the Python `pymol`
  // object so that the Python layer can issue commands through the same
  // session.
  //
  // @param pymol  A nanobind handle to the Python PyMOL instance that will
  //               own and drive this session. The handle must remain valid
  //               for the entire lifetime of this `Engine`.
  //
  // @throws std::runtime_error if CPyMOL initialization fails (e.g. the
  //         underlying C library cannot allocate its global state).
  explicit Engine(nb::handle pymol);

  // @brief Destructs the `Engine` and shuts down the CPyMOL session.
  //
  // If `m_IsRunning` is `true`, calls the appropriate CPyMOL teardown
  // routine to flush buffers and free all PyMOL-managed memory, then sets
  // `m_PyMOL` to `nullptr`. This guarantees that resources are released
  // exactly once regardless of how the `Engine` goes out of scope.
  ~Engine();
  
  // All copy and move operations are deleted.
  //
  // Rationale: `m_PyMOL` is a raw owning pointer. Allowing copies would
  // produce two `Engine` objects that both believe they own the same
  // `CPyMOL*`, causing a double-free on destruction. Allowing moves would
  // leave the source in an indeterminate state that is difficult to reason
  // about safely. Deletion is the clearest, safest solution.
  //
  // @brief Copy construction is disabled — `Engine` owns a unique resource.
  Engine(const Engine&) = delete;

  // @brief Copy assignment is disabled — `Engine` owns a unique resource.
  Engine& operator=(const Engine&) = delete;

  // @brief Move construction is disabled — transfer of CPyMOL ownership is not supported.
  Engine(Engine&&) = delete;

  // @brief Move assignment is disabled — transfer of CPyMOL ownership is not supported.
  Engine& operator=(Engine&&) = delete;

  // @brief Exposes the internal `PyMOLGlobals*` to Python as an opaque capsule.
  //
  // Legacy PyMOL C API functions (e.g. those in `PyMOL_*.h`) expect a raw
  // `PyMOLGlobals*` pointer rather than a full C++ object. This method
  // wraps that pointer in a `nb::capsule` — a Python object that holds an
  // opaque C pointer — so Python extension code can pass it to those
  // functions without the pointer ever being exposed as a plain integer.
  //
  // The capsule is read-only from the Python side: it cannot be used to
  // modify or delete the underlying globals, only to pass to C API calls.
  //
  // @return A `nb::capsule` wrapping the `PyMOLGlobals*` held by `m_PyMOL`.
  // @note   The capsule is only valid while this `Engine` instance is alive.
  //         Storing it beyond the `Engine`'s lifetime results in undefined behavior.
  [[nodiscard]] nb::capsule get_globals_capsule() const;

private:
  // @brief Tracks whether the CPyMOL session is currently active.
  //
  // Set to `true` after successful initialization and to `false` after
  // teardown. Used by the destructor to guard against double-shutdown if
  // teardown is ever triggered explicitly before destruction.
  bool m_IsRunning;
};

} // namespace cbiomol

#endif // CBIOMOL_ENGINE_HPP
