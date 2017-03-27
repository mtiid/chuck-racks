SqrOsc osc => dac;
0.1=> osc.gain;

PluginHost.onBeat()=>now; //to sync on the first beat happening after hitting play
while(true)
{
    setRandPitch();
	PluginHost.wholeDur() => now;
	setRandPitch();
	PluginHost.halfDur() => now;
	setRandPitch();
	PluginHost.eighthDur() => now;
	setRandPitch();
	PluginHost.sixteenthDur() => now;
}


fun void setRandPitch()
{
 	Std.rand2(30, 80) => int randomMidiNote;
    Std.mtof( randomMidiNote )=> float noteFreq; // mtof == Midi To Frequency
    noteFreq => osc.freq;
}