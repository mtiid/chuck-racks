//Midi Chord Strummer - By R Sena 2017

//This works similarly to an arpeggiator
//Play midi notes into this and send midi out to another midi channel with an instrument


//=== edit this to change sequence ( 0-127 )======
[127, 0, 56, 12,
0, 127, 0, 0,
80, 100, 110, 120,
0, 0, 0, 127] @=> int velocitySequence[];

//================================

int midiNoteBuffer[0];

spork ~ midiMessageCatchProcess();
 
while(true)
{
	for( int i; i < velocitySequence.size(); i++ )
	{
		if( velocitySequence[i] != 0 )
		{
			playAllNotesInBuffer( velocitySequence[i] );
		}
    	PluginHost.sixteenth() => now;
	}
}

//-----------FUNCTIONS-------------------------

//---midi buffer functions-----
fun void printAllNotesInBuffer()
{
    for (int i; i < midiNoteBuffer.size(); i++)
    {
        <<<midiNoteBuffer[i]>>>;
    }
    <<<"All notes printed">>>;
}


fun void addNoteToBuffer( int noteNumber )
{
    for (int i; i < midiNoteBuffer.size(); i++)
    {
        if( midiNoteBuffer[i] == noteNumber )
        {
            return; // to avoid adding the same note twice to the buffer
        }
    }
    midiNoteBuffer << noteNumber;
}


fun void removeNoteFromBuffer( int noteNumber )
{
    for (int i; i < midiNoteBuffer.size(); i++)
    {
        if( midiNoteBuffer[i] == noteNumber )
        {
            for( i=>int j; j < midiNoteBuffer.size()-1; j++)
            {
                midiNoteBuffer[j+1] => midiNoteBuffer[j];
            }
            midiNoteBuffer.size( midiNoteBuffer.size()-1 );
            i--;
        }
    }
}

//-------Send midi note functions--------------------------------
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

fun void playAllNotesInBuffer( int velocity )
{
    for (int i; i < midiNoteBuffer.size(); i++)
    {
        playMidiNote( midiNoteBuffer[i], velocity );
    }
}

//-----midi in functions-------------------------

fun void midiMessageCatchProcess()
{
	MidiMsg msg;
	while( true )
	{
		PluginHost.onMidi() => now;
    	while( PluginHost.recvMidi(msg) )
    	{
    		if( msg.data1 == 0x90 ) //note on
            	{
					addNoteToBuffer( msg.data2 );
				}
			else if( msg.data1 == 0x80 ) //note off
				{
					removeNoteFromBuffer( msg.data2 );
				}
		}
	}
}