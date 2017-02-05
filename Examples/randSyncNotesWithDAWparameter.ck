//By R Sena 2017

SqrOsc osc => LPF filter => dac;
0.01=> osc.gain;
spork ~ updateVolume();
spork ~ updateFilterCutoff();
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
		PluginParameters.getValue( "volume" ) => osc.gain;
		10::ms => now; //update rate
	}
}

fun void updateFilterCutoff()
{
	//do the same that you did for updateVolume() 
	//with a parameter called "cutoff"
	while(true)
	{
		//values from parameters are between 0 and 1
		PluginParameters.getValue( "cutoff" ) => float valueFromParam; 
		
		//since it's for frequency we want an exponential response
		valueFromParam * valueFromParam => float expValue; 

		//we have to scale it to the desired range of the filter (in Hz)
 		//Std.scalef(float value, float srcmin, float srcmax, float dstmin, float dstmax)
		Std.scalef( expValue, 0.0, 1.0, 50.0, 10000.0 ) => filter.freq;
		10::ms => now; //update rate
	}
}
