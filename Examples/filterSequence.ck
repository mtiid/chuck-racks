//"Filter sequence" by Rodrigo Sena 2017
//use this as an audio effect on a channel

adc => LPF filter => dac;

ADSR env => blackhole;

env.set(10::ms, 100::ms, 0.0, 1::ms);

100.0 => float minFreq;
3000.0 => float maxFreq; //max frequency of the filter
[1.0, 0.0, 0.1, 0.5,
1.0, 0.0, 0.1, 1.0,
0.0, 0.8, 0.1, 0.1,
1.0, 0.0, 0.8, 0.5] @=> float freqSeq[]; //intensity of the filter (0-1) (1 == maxFreq)

50 => float minDecayInMs;
300 => float maxDecayInMs;

1.0 => float freqMultiplier;
spork ~ updateFilterEnv();

while(true)
{
    for( int i; i<freqSeq.cap(); i++ )
    {
        if( freqSeq[i] != 0.0 )
        {
            freqSeq[i] => freqMultiplier;
            Std.rand2f( minDecayInMs, maxDecayInMs)::ms => env.decayTime; //random variation in envelope decay time
            env.keyOn(1);
        }
        PluginHost.sixteenth()=>now;
        env.keyOff(1);
    }
}

fun void updateFilterEnv()
{
    while(true)
    {
        Std.scalef( env.value(), 0.0, 1.0, minFreq, maxFreq ) * freqMultiplier => filter.freq;
        1::ms=>now;
    }
}