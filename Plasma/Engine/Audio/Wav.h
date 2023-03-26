// By @ByCubed7 on Twitter

#pragma once

#include "../Resource.h"

#include "OpenAL/AL/al.h"
#include "OpenAL/AL/alc.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Wav : public Resource<Wav>
{
public:

    Wav();

    std::string filepath;

    uint8_t channels;
    int32_t sampleRate;
    uint8_t bitsPerSample;
    int32_t size;

    std::vector<char> data;

    char* getData() { return data.data(); }
    size_t getSize() { return data.size(); }

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

protected:
    Wav fromFile(const std::string filename) override;
    void clear() override;


private:
    static bool LoadWavHeader(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size);

};