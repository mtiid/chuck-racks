SqrOsc osc => dac;
0.01=> osc.gain;
spork ~ updateVolume();
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

fun void updateVolume()
{
	while(true)
	{
		//to use this you first have to create a parameter. 
		//click on the configure button for this plugin in your DAW
		//then click on the arrow on the top right of this window
		//add a parameter and rename it "volume"
		//you can the control this from your DAW using automation or midi control 
		PluginPanel.getValue( "volume" ) => osc.gain;
		10::ms => now;
	}
}