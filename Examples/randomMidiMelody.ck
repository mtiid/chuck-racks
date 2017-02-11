//By R Sena 2017

[24,26,28,29,31,33,35,36] @=> int scale[]; 
int sequence[32]; //change number for different length sequences

Math.srandom( 9439 ); //random seed. change number for different sequences
generateSequence();

while(true)
{
	for( int i; i < sequence.cap(); i++ )
	{
		playMidiNote( sequence[i] );
    	PluginHost.sixteenth() => now;
	}
}

fun void playMidiNote(int midiNote)
{
	playMidiNote( midiNote, 127 );
}

fun void playMidiNote(int midiNote, int velocity)
{
 	spork ~ playNoteProcess( midiNote, velocity );
}

fun void playNoteProcess( int midiNote, int velocity ) //only used when sporking
{
	MidiMsg msg;
    
    0x90 => msg.data1; //note on
    midiNote => msg.data2;
    velocity => msg.data3;
	PluginHost.sendMidi( msg );

    PluginHost.sixteenth() => now;
    
    0x80 => msg.data1; //note off
    midiNote => msg.data2;
    0 => msg.data3;
    PluginHost.sendMidi( msg );
    
}

fun void generateSequence()
{
	for( int i; i<sequence.cap(); i++)
	{
		Math.random2(0, scale.cap()-1) => int randomScaleNote;
		scale[randomScaleNote] => sequence[i];
	}
}
