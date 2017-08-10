# Kaleidoscope-Hardware

![status][st:stable]

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

Base class for all hardware [Kaleidoscope][kaleidoscope] plugins. The base class
ensures that the hardware class itself implements all the methods required for
basic functionality. This allows other plugins to safely assume that the
`KeyboardHardware` object will implement at least the methods defined in the
base class.

 [kaleidoscope]: https://github.com/keyboardio/Kaleidoscope

## Using the plugin

Until a porting guide is ready, see
the [Kaleidoscope-Hardware-Model01][kaleidoscope:model01] or
the [Kaleidoscope-Hardware-Shortcut][kaleidoscope:shortcut] plugins for an
example how the base class can and should be used.

 [kaleidoscope:model01]: https://github.com/keyboardio/Kaleidoscope-Hardware-Model01
 [kaleidoscope:shortcut]: https://github.com/shortcutgg/Kaleidoscope-Hardware-Shortcut
