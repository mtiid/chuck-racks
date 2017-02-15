// Eric Heep
// February 14th, 2017
// markovMelodySynced.ck

class Markov {

    0 => int currentRow;

    fun int[] generateChain(int inputChain[], float transitionMatrix[][], int order, int range) {
        /* Calculates an output chain based on the input and its probabilities.

        Parameters
        ----------
        inputChain : int array
            input chain that the output will be created from
        transitionMatrix : two dimensional float array
            collection of probabilities
        order : int
            Markov chain order
        range : int
            range of values that can be considered

        Returns
        -------
        outputChain : int array
            output chain
        */

        inputChain.size() => int length;
        int outputChain[length];

        // a new link for length of the array
        for (0 => int j; j < length; j++) {
            int row;

            // finds row index
            for (0 => int i; i < order; i++) {
               inputChain[(length - order + i + j) % length] => int element;
               (Math.pow(range, order - i - 1) * element) $ int +=> row;
            }

            // finds range of values
            float sum;
            for (0 => int i; i < range; i++) {
                transitionMatrix[row][i] +=> sum;
            }

            Math.random2f(0.0, sum) => float randomValue;

            // finds our next link for the chain
            0.0 => sum;
            for (0 => int i; i < range; i++) {
                transitionMatrix[row][i] +=> sum;
                if (randomValue < sum) {
                    i => outputChain[j];
                    break;
                }
            }
        }

        return outputChain;
    }

    fun int[][] generateSequenceCombinations(int order, int range) {
        Math.pow(range, order) => float size;

        if (order == 1) {
            int sequence[size$int][1];
            for (0 => int i; i < range; i++) {
                i => sequence[i][0];
            }
            return sequence;
        }
        else {
            int sequence[size$int][order];
            for (0 => int i; i < size; i++) {
                for (0 => int j; j < order; j++) {
                    i/Math.pow(range, j)$int % range => sequence[i][order - j - 1];
                }
            }

            return sequence;
        }
    }

    fun float[][] generateTransitionMatrix(int inputChain[], int order, int range) {
        /* Generates transition matrix from a chain.

        Parameters
        ----------
        inputChain : int[] array
            input chain that the output will be created from
        order : int
            Markov chain order
        range : int
            range of values that can be considered

        Returns
        -------
        transitionMatrix: int[][] array
            transition matrix
        */

        inputChain.size() => int length;
        Math.pow(range, order)$int => int rows;

        float transitionMatrix[rows][range];

        int element[range];
        int current[range];

        for (0 => int i; i < range; i++) {
            i => element[i];
        }

        int combination[range];
        0 => currentRow;

        generateSequenceCombinations(order, range) @=> int combinations[][];

        for (0 => int i; i < combinations.size(); i++) {
            for (int j; j < order; j++) {
                combinations[i][j] => combination[j];
            }

            int matches[0];

            // checks if current combination is in input chain
            for (0 => int j; j < length; j++) {
                0 => int matchSum;

                for (0 => int k; k < order; k++) {
                    if (inputChain[(length - order + k + j) % length] == combination[k]) {
                        1 +=> matchSum;
                    }
                }

                if (matchSum == order) {
                   matches << inputChain[j];
                }
            }
            matches.size() => int size;
            for (0 => int j; j < size; j++) {
                1.0/size +=> transitionMatrix[i][matches[j]];
            }
        }

        return transitionMatrix;
    }
}

fun int arrayMax(int arr[]) {
    int max;
    for (0 => int i; i < arr.size(); i++) {
        if (max < arr[i]) {
            arr[i] => max;
        }
    }
    return max;
}

/*
Enter a melody into into the base array of any desired length. The
order of the Markov chain determines how complex the transition matrix
is (the order is the major determining factor, a range of 4 and an order
of 1 creates a transition matrix of 4 values, whereas a range of 4 and an
order of 3 creates a transiton matrix of 64 values [4**3]).

A new chain is created every loop based on original base array, but you
can experiment with generating new transition matrices on the fly or changing
the order if you see fit.
*/

Markov markov;
SinOsc sin => dac;

// simple pentatonic melody
[0, 2, 4, 7, 0, 9, 0, 2, 4, 0, 9, 11, 0] @=> int base[];

60 => int rootNote;
2 => int order;
arrayMax(base) + 1 => int range;

base @=> int chain[];
markov.generateTransitionMatrix(base, order, range) @=> float transitionMatrix[][];

while (true) {
    for (0 => int i; i < chain.size(); i++) {
        sin.freq(Std.mtof(chain[i] + rootNote));

        //synced with daw (press play)
        PluginHost.sixteenth() => now;
    }
    markov.generateChain(base, transitionMatrix, order, range) @=> chain;
}
