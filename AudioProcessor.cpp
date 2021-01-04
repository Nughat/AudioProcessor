/*
Title: AudioProcessor.cpp
Description: Implements a class AudioProcessor
Date: 11/27/20
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "AudioProcessor.h"

/*@param audio Vector of samples
@param threshold Determines which samples must be compressed
@param rate The compression rate
@pre thershold cannot be negative and rate cannot be below 1
@post If the calculations, certain samples will be compressed
@return Vector of compressed values*/
std::vector<short> AudioProcessor::Compress(const std::vector<short> & audio, short threshold, float rate)
{
    if (audio.empty()) //if empty vector return empty vector
        return {};
    if ((threshold < 0) || (rate < 1)) //if a parameter value is invalid throw exception
        throw std::invalid_argument("STOP!!! Invalid threshold or rate"); 
    std::vector<short> v = audio; //vector copy to hold new compressed values
    float comp_sample; //decimal result of compressed sample
    for (int i = 0; i < audio.size(); i++) //for every sample
    {
        if ((audio[i] > threshold) || (audio[i] < (-1*threshold))) //if the sample falls outside the threshold boundaries
        {
            comp_sample = (((abs(audio[i])-threshold)/rate)+threshold); //apply given formula to compress the sample  
            if ((int)comp_sample != comp_sample) //if the compressed sample turns out to be a decimal
                comp_sample = round(comp_sample); //round it
            if (audio[i] < 0) //if the original sample was negative
                comp_sample *= (-1); //reinstate the compressed sample as a negative value
            v[i] = comp_sample; //put compressed sample into vector of compressed values
        }
    }
    return v; //return vector of compressed values
} //end Compress

/*@param audio Vector of samples
@param level Determines what is considered a silence 
@param silenceLength Necessary length of silence to be cut out
@pre level cannot be negative and silenceLength cannot be below 1
@post If the removals are sucessful, only nonsilence samples and silence samples below a certain length will remain
@return Vector of silenced version of audio */
std::vector<short> AudioProcessor::CutOutSilence(const std::vector<short> & audio, short level, int silenceLength)
{
    if (audio.empty()) //if empty vector return empty vector
        return {};
    if (level < 0 || silenceLength < 1) //if a parameter value is invalid throw exception
        throw std::invalid_argument("STOP!!! Invalid level or silenceLength");
    std::vector<short> v; //vector to hold silenced version of audio 
    int counter = 0; //tracks length of silences
    for (int i = 0; i < audio.size(); i++) //for every sample
    {
        if ((audio[i] <= level) && (audio[i] >= (-1*level))) //if sample is a silence
        {
            counter++; //count all silence elements until a nonsilence element comes up
            if (i == audio.size()-1 && counter < silenceLength) //if the last element is a silence but is not long enough
                v.insert(v.end(), audio.end()-counter, audio.end()); //insert all the samples that were skipped over along with the last element
        }  
        else //encounter a nonsilence element
        {
            if (i == 0) //if the nonsilence element is the first element of the vector 
                v.push_back(audio[i]); //insert normally
            else //not the first element of the vector
            {
                if ((counter >= silenceLength)) //if silence is long enough
                    v.push_back(audio[i]);//skip over the silences and insert only the current nonsilence element
                if (counter < silenceLength) //if silence is not long enough
                    v.insert(v.end(), audio.begin()+(i-counter), audio.begin()+i+1); //insert silenced elements that were skipped over along with the current nonsilence element
            }             
            counter = 0; //reset the counter
        }
     }
     return v; //return vector of silenced version of audio 
} //end CutOutSilence

/*@param audio Vector of samples
@post If the calculations are successful, then there will be a vector with averages of the samples and the original samples
@return Vector of stretched version of audio*/
std::vector<short> AudioProcessor::StretchTwice(const std::vector<short> & audio)
{
    if (audio.empty()) //if empty vector return empty vector
        return {};
    std::vector<short> v; //vector to hold stretched version of audio
    float avg; //decimal result of stretched sample
    for (int i = 0; i < audio.size(); i++) //for every sample
    {
        v.push_back(audio[i]); //insert sample into vector
        if (i != audio.size()-1) //if sample is not the last element
        {                   
            avg = ((float)audio[i] + (float)audio[i+1])/2; //calculate average of current sample and next sample in audio
            if ((int)avg != avg) //if the average turns out to be a decimal
                avg = round(avg); //round it
            v.push_back(avg); //insert average into vector
        }
    }
    return v; //return vector of stretched version of audio
} //end StretchTwice

/*@param audio Vector of samples
@param normalizeTarget Determines the factor by which each sample will be proportionally increased
@pre normalizeTarget cannot be less than 1
@post If the calculations are successful, then there will be a vector of normalized values
@return Vector of normalized values*/
std::vector<short> AudioProcessor::Normalize(const std::vector<short> & audio, short normalizeTarget)
{
    if (audio.empty()) //if empty vector return empty vector
        return {};
    if (normalizeTarget < 1) //if a parameter value is invalid throw exception
        throw std::invalid_argument("STOP!!! Invalid normalizeTarget");
    std::vector<short> v = audio; //vector copy to hold normalized values
    std::sort(v.begin(), v.end()); //sort vector
    short max; //greatest absolute value in vector
    if (abs(v[0]) > v[v.size()-1]) //if the absolute value of the minimum value is greater than the maximum positive value
        max = abs(v[0]); //the maximum is the absolute value of the minimum value
    else //if not
        max = v[v.size()-1]; //the maximum is just the maximum positive value
    float factor =  (float)normalizeTarget/max; //calculate factor to multiply all other samples by
    float temp; //sample after proportional increase
    for (int i = 0; i < audio.size(); i++) //for every sample
    {
        temp = audio[i]*factor; //calculate the proportional increase
        if ((int)temp != temp) //if the changed sample turns out to be a decimal
            temp = round(temp); //round it
        v[i] = temp; //insert proportionalized sample into the vector
    }
    return v; //return vector of normalized values
} //end Normalize