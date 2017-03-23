//Random Midi Melody 2 v1.0
//By R Sena 2017


///----Editable variables---------------------------------

32 => int numberOfSteps;
10 => float silencePercent; //rests. from 0 to 100
36 => int baseMidiNote; //36 = C2, more at http://sonic-pi.mehackit.org/assets/img/midi_notes.png
2 => int plusOctaves; // 0 for one octave, 1 for two, etc

[ 0, 2, 4, 5, 7, 9, 11, 12 ] @=> int scale[]; //major scale
//[ 0, 2, 3, 5, 7, 8, 10, 12 ] @=> int scale[]; //minor scale //uncomment to use this instead
//Math.srandom( 9439 ); //random seed. same number will always give you the same sequence

////-----------------------------------------------------

int noteSequence[numberOfSteps];
generateSequence();

while(true) //play sequence
{
	for( int i; i < numberOfSteps; i++ )
	{
		if( noteSequence[i] != 0 )
		{
			playMidiNote( noteSequence[i] );
		}
    	PluginHost.sixteenth() => now;
	}
}


////-----Functions--------------------------------

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
    for (int i; i<numberOfSteps; i++)
    {
        if( silencePercent > Math.random2f( 0, 100 ) )
        {
            0 => noteSequence[i];
            continue;
        }
        baseMidiNote => int newNote;
        scale[Math.random2(0, scale.cap()-1)] +=> newNote;
        (Math.random2(0, plusOctaves)*12) +=> newNote;
        newNote => noteSequence[i];
    }
}