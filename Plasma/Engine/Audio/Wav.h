// By @ByCubed7 on Twitter

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <al.h>
//#include <alc.h>

struct Wav
{
    std::string name;
    std::string filepath;

    uint8_t channels;
    int32_t sampleRate;
    uint8_t bitsPerSample;
    int32_t size;

    std::vector<char> data;

    char* Data() { return data.data(); }
    size_t Size() { return data.size(); }

    ALenum Format() {

        ALenum format;
        if      (channels == 1 && bitsPerSample == 8)   format = AL_FORMAT_MONO8;
        else if (channels == 1 && bitsPerSample == 16)  format = AL_FORMAT_MONO16;
        else if (channels == 2 && bitsPerSample == 8)   format = AL_FORMAT_STEREO8;
        else if (channels == 2 && bitsPerSample == 16)  format = AL_FORMAT_STEREO16;
        else
        {
            std::cerr
                << "ERROR: unrecognised wave format: "
                << channels << " channels, "
                << bitsPerSample << " bps" << std::endl;
            return 0;
        }

        return format;
    }
};