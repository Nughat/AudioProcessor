# AudioProcessor
Implements an AudioProcessor class

# Compression
This function returns the compressed version of the given audio. 
“Compressed” means that any number from audio that is larger than 
threshold or smaller than -threshold has it’s “above the threshold” 
portion reduced rate time. rate is called “compression rate”.
For example, if threshold=1 and rate=2.0 than number/sample 3 is 
compressed to number/sample 2. This is because number 3 is “2 above 
the threshold of 1”. So, the “above the threshold part” is reduced 
rate times. For positive number/sample, the math looks like (3 – threshold)/rate + threshold = 2.
For negative number/sample, the situation is similar. Negative 
sample -3 for the same threshold and rate is compressed to -2. You 
can compress negative sample by turning it into positive, compressing 
it as positive and then just turning the result back into negative.
Compression can produce floating-point results because of the 
floating-point rate. The compression result should be rounded to the closest short. 
If both upper and lower shorts are equally far, chose the one with the larger absolute value.
If threshold is negative or rate is less than 1.0, throw the std::invalid_argument 
exception (similar to the std::out_of_range exception that you used in the previous assignments).
Example: audio={1, 4, 25, 15, 0, -7, -40, 10} , threshold=10,  rate=1.5
Output: {1, 4, 20, 13, 0, -7, -30, 10}

# Silence
Silence is a portion of audio where all numbers/samples are 
in the range [-level, level].CutOutSilince returns the version of audio 
where all silences of at least silenceLength length are removed.
If level<0 or silenceLength<1, throw the std::invalid_argument exception
Example: audio={1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12}, level=10, silenceLength=3
Output: {25, 56, -1, -2, -16, -20, 12} 
The portions of audio in bold are the portions which we cut out. 
Pay attention, the fragment {-1, -2} in the audio is also a silence but its 
length is below the minimum silenceLength so we leave it in the result.

# StretchTwice
Returns the version of audio where between each pair of original 
samples from audio an extra sample appears. This extra sample is 
an average (arithmetic mean) of the two original samples.
The average can be a floating-point value. In that case, it should 
be rounded to the closest short. If both upper and lower shorts 
are equally far, chose the one with the larger absolute value.
Example: audio={1, 4, 23, -2, -28, 10 }
Output: {1, 3, 4, 14, 23, 11, -2, -15, -28, -9, 10}

# Normalize
Normalize returns a version of audio where all samples are proportionally 
increases or decreased to ensure that the largest absolute value from all 
resulting samples is exactly normalizeTarget. While normalizing, you can 
get floating-point values. Such values should be rounded to the closest short. 
If both upper and lower shorts are equally far, chose the one with the 
larger absolute value. If normalizeTarget<1, throw the std::invalid_argument exception
Example 1: audio={1, 3, -2, 5, -4, 0}  normilizeTarget=10
Output: {2, 6, -4, 10, -8, 0}
Example 2: audio={-1, -30, 3, 15, 16, -7}  normilizeTarget=20
Output: {-1, -20, 2, 10, 11, -5}
