// binaryCelluarAutomataSynced.ck
Rhodey rhod => dac;

// Cellular Automata rule
110 => int rule;
12 => int rhythmLength;

// Cellular Automata binary input
1 => int input;
[0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26] @=> int pentatonicScale[];

while (true) {
    int output, lookup, state;
    for (0 => int i; i < rhythmLength; i++) {
        // Cellular Automata bit math logic
        if (i == 0) {
            (input >> rhythmLength - 1) | ((input & 3) << 1) => lookup;
        } else if (i == (rhythmLength - 1)) {
            ((input >> i) & 3) | ((input & 1) << 2) => lookup;
        } else {
            (input >> (i - 1)) & 7 => lookup;
        }

        // Cellular Automata bit math results
        (rule >> lookup) & 1 => state;
        (state << i) | output => output;

        if (state == 1) {
            rhod.noteOn(Math.random2f(0.4, 1.0));
            rhod.freq(Std.mtof(48 + pentatonicScale[i]));
        }

        PluginHost.nextSixteenth() => now;
    }

    output => input;
}
