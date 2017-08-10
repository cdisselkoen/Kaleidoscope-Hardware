/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware -- Kaleidoscope Hardware Base class
 * Copyright (C) 2017  Jesse Vincent
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/**
 * Forward declaration of the cRGB structure.
 *
 * The base class does not define the cRGB structure, that is left up to the
 * individual Hardware libraries. We do a forward declaration here, because the
 * base hardware has methods that depend on a cRGB structure.
 *
 * The structure will need to have at least three members: r, g, and b -
 * compilation will fail otherwise.
 */
typedef struct cRGB cRGB;

namespace kaleidoscope {
/** Kaleidoscope Hardware base class.
 * Essential methods all hardware libraries must implement.
 */
class Hardware {
 public:
  /**
   * @defgroup kaleidoscope_hardware_leds Kaleidoscope::Hardware/LEDs
   * @{
   */
  /**
   * Sync the LEDs with the underlying hardware. This should make sure that
   * changes made before this call are reflected on the device.
   */
  virtual void syncLeds(void) {}
  /**
   * Set the color of a per-key LED at a given row and column.
   *
   * Setting the color does not need to take effect immediately, it can be
   * delayed until @ref syncLeds is called.
   *
   * @param row is the logical row position of the key.
   * @param col is the logical column position of the key.
   * @param color is the color to set the LED to.
   */
  virtual void setCrgbAt(byte row, byte col, cRGB color) {}
  /**
   * Set the color of a per-key LED at a given LED index.
   *
   * Setting the color does not need to take effect immediately, it can be
   * delayed until @ref syncLeds is called.
   *
   * @param i is the LED index to change the color of.
   * @param color is the color to set it to.
   */
  virtual void setCrgbAt(uint8_t i, cRGB color) {}
  /**
   * Returns the color of the LED at a given index.
   *
   * @param i is the index of the LED to return the color of.
   *
   * @returns The color at the given position.
   */
  virtual cRGB getCrgbAt(uint8_t i) {
    cRGB c = {
      0, 0, 0
    };
    return c;
  }
  /** @} */

  /** @defgroup kaleidoscope_hardware_matrix Kaleidoscope::Hardware/Matrix
   * @{
   */
  /**
   * Scan the keyboard matrix, and act on it.
   */
  virtual void scanMatrix(void) = 0;
  /**
   * Read the state of the keyboard matrix.
   *
   * Do whatever is necessary to read the current keyboard state - but without
   * acting on it.
   *
   * This is primarily used by @ref scanMatrix, but may have other uses too.
   */
  virtual void readMatrix(void) = 0;
  /**
   * Act on the scanned keyboard matrix.
   *
   * Iterate through the scanned state (@see readMatrix), and act on any events.
   */
  virtual void actOnMatrixScan(void) = 0;
  /** @} */

  /** @defgroup kaleidoscope_hardware_masking Kaleidoscope::Hardware/Key masking
   *
   * Sometimes there are situations when one wants to ignore key events for a
   * while, to mask them out. Masked keys will be ignored until they are
   * released.
   *
   * This is implemented in the Hardware library because that knows best how
   * to mask efficiently, as this requires a deeper knowledge of the hardware,
   * which is all but hidden from the rest of the plugins.
   * @{
   */
  /**
   * Mask out a key.
   *
   * Masking a key out means that any other event than a release will be
   * ignored until said release.
   *
   * @param row is the row the key is located at in the matrix.
   * @param col is the column the key is located at in the matrix.
   */
  virtual void maskKey(byte row, byte col) = 0;
  /**
   * Unmask a key.
   *
   * Remove the mask - if any - for a given key. To be used when the mask
   * needs to be removed without the key being released.
   *
   * @param row is the row the key is located at in the matrix.
   * @param col is the column the key is located at in the matrix.
   */
  virtual void unMaskKey(byte row, byte col) = 0;
  /**
   * Check whether a key is masked or not.
   *
   * @param row is the row the key is located at in the matrix.
   * @param col is the column the key is located at in the matrix.
   *
   * @returns true if the key is masked, false otherwise.
   */
  virtual bool isKeyMasked(byte row, byte col) = 0;
  /** @} */

  /**
   * @defgroup kaleidoscope_hardware_misc Kaleidoscope::Hardware/Miscellaneous methods
   * @{
   */
  /**
   * Method to do any hardware-specific initialization.
   *
   * Called once when the device boots, this should initialize the device, and
   * bring it up into a useful state.
   */
  virtual void setup() = 0;
  /** @} */
};
}
