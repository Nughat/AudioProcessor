#include "AudioProcessor.h"
#include <iostream>
using namespace std;

int main() {

    AudioProcessor processor;
    vector<short> audioSamples{ 1, 4, 25, 15, 0, -7, -40, 10 };
    cout << "Content of vector prior to compressing: ";
    for (const auto &x: audioSamples) 
        cout << x << ' ';
    cout << endl;
    vector<short> compressedAudio;
    compressedAudio = processor.Compress( audioSamples, 10, 1.5 );
    cout << "Content of vector after compressing: ";
    for (const auto &x: compressedAudio) 
        cout << x << ' ';
    cout << endl;
    //CutOutSilence
    vector<short> audioSamples1{ 1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12 };
    cout << "Content of vector prior to cutting out silence: ";
    for (const auto &x: audioSamples1) 
        cout << x << ' ';
    cout << endl;
    vector<short> CutOutSilenceAudio;
    CutOutSilenceAudio = processor.CutOutSilence( audioSamples1, 10, 3 );
    cout << "Content of vector after cutting out silence: ";
    for (const auto &x: CutOutSilenceAudio) 
        cout << x << ' ';
    cout << endl;
    //StretchTwice
    vector<short> audioSamples2{ 1, 4, 23, -2, -28, 10 };
    cout << "Content of vector prior to stretching: ";
    for (const auto &x: audioSamples2) 
        cout << x << ' ';
    cout << endl;
    vector<short> stretchAudio;
    stretchAudio = processor.StretchTwice( audioSamples2 );
    cout << "Content of vector after stretching: ";
    for (const auto &x: stretchAudio) 
        cout << x << ' ';
    cout << endl;
    //Normalize
    vector<short> audioSamples3{ 1, 3, -2, 5, -4, 0 };
    cout << "Content of vector prior to normalizing (first example): ";
    for (const auto &x: audioSamples3) 
        cout << x << ' ';
    cout << endl;
    vector<short> normalizeAudio;
    normalizeAudio = processor.Normalize( audioSamples3, 10 );
    cout << "Content of vector after normalizing (first example): ";
    for (const auto &x: normalizeAudio) 
        cout << x << ' ';
    cout << endl;
    vector<short> audioSamples4{ -1, -30, 3, 15, 16, -7 };
    cout << "Content of vector prior to normalizing (second example): ";
    for (const auto &x: audioSamples4) 
        cout << x << ' ';
    cout << endl;
    vector<short> normalizeAudio1;
    normalizeAudio1 = processor.Normalize( audioSamples4, 20 );
    cout << "Content of vector after normalizing (second example): ";
    for (const auto &x: normalizeAudio1) 
        cout << x << ' ';
    cout << endl;
    return 0;
}