# chuck-racks
Chuck as a VST Plugin

ChucK-Racks makes it possible to write and execute ChucK programs as VST/AudioUnit plugins. The ChucK-Racks architecture supports the following features:

* Process incoming audio in ChucK (i.e. Audio FX plugins)
* Process MIDI events from the host in ChucK programs (MIDI FX plugins)
* Write synthesis plugins in ChucK that run as regular synthesizer audio plugins in a host/DAW
* Synchronize clock and beat-time between a host/session and ChucK
* Generate new MIDI/OSC events from ChucK (e.g. writing MIDI/OSC sequencer plugins)
* Automate variables in ChucK code using host automation lanes
