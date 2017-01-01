SqrOsc osc => dac;
0.01=> osc.gain;
while(true) 
{
	Std.rand2(30, 80) => int randomMidiNote;
	Std.mtof( randomMidiNote )=> float noteFreq; // mtof == Midi To Frequency
	noteFreq => osc.freq;

	repeat ( Std.rand2(1, 3) ) //1,2 or 3 sixteenths 
	{
   		PluginHost.sixteenth()=>now; //synced with daw (press play)
	}
}