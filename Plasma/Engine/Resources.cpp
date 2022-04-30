// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Resources.h"

#include "Tilemaps/Tile.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <bit>

#include "lodepng.h"

#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype.h>  

// Cache any resources we load
std::map<std::string, Wav> Resources::wavs;


Wav Resources::LoadWav(const std::string file, std::string name)
{
    Wav wav;

    std::ifstream in(file, std::ios::binary);
    if (!in.is_open())
        std::cout << "ERROR: Could not open \"" << file << "\"" << std::endl;

    if (!LoadWavHeader(in, wav.channels, wav.sampleRate, wav.bitsPerSample, wav.size))
        std::cout << "ERROR: Could not load wav header of \"" << file << "\"" << std::endl;

    char* data = new char[wav.size];
    in.read(data, wav.size);

    wav.data = std::vector<char>(data, data + wav.size);

    wav.name = name;
    wav.filepath = file;

    wavs[name] = wav;
    return wav;
}

Wav Resources::GetWav(std::string name)
{
    return wavs[name];
}

bool Resources::LoadWavHeader(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size)
{
    char buffer[4];
    if (!file.is_open())
        return false;

    // the RIFF
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read RIFF" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cout << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
        return false;
    }

    // the size of the file
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read size of file" << std::endl;
        return false;
    }

    // the WAVE
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read WAVE" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "WAVE", 4) != 0)
    {
        std::cout << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
        return false;
    }

    // "fmt/0"
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read fmt/0" << std::endl;
        return false;
    }

    // this is always 16, the size of the fmt data chunk
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read the 16" << std::endl;
        return false;
    }

    // PCM should be 1?
    if (!file.read(buffer, 2))
    {
        std::cout << "ERROR: could not read PCM" << std::endl;
        return false;
    }

    // the number of channels
    if (!file.read(buffer, 2))
    {
        std::cout << "ERROR: could not read number of channels" << std::endl;
        return false;
    }

    // convert_to_int
    std::memcpy(&channels, buffer, 2);

    // sample rate
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read sample rate" << std::endl;
        return false;
    }
    // convert_to_int
    std::memcpy(&sampleRate, buffer, 4);

    // (sampleRate * bitsPerSample * channels) / 8
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
        return false;
    }

    // ?? dafaq
    if (!file.read(buffer, 2))
    {
        std::cout << "ERROR: could not read dafaq" << std::endl;
        return false;
    }

    // bitsPerSample
    if (!file.read(buffer, 2))
    {
        std::cout << "ERROR: could not read bits per sample" << std::endl;
        return false;
    }
    // convert_to_int
    std::memcpy(&bitsPerSample, buffer, 2);

    // data chunk header "data"
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read data chunk header" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "data", 4) != 0)
    {
        std::cout << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
        return false;
    }

    // size of data
    if (!file.read(buffer, 4))
    {
        std::cout << "ERROR: could not read data size" << std::endl;
        return false;
    }
    // convert_to_int
    std::memcpy(&size, buffer, 4);

    /* cannot be at the end of file */
    if (file.eof())
    {
        std::cout << "ERROR: reached EOF on the file" << std::endl;
        return false;
    }
    if (file.fail())
    {
        std::cout << "ERROR: fail state set on the file" << std::endl;
        return false;
    }

    return true;
}

//

std::vector<char> Resources::LoadWavFromFile(const std::string file)
{
    return std::vector<char>();
}