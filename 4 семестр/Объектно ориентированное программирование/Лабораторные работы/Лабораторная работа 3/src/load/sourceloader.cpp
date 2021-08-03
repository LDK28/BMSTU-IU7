#include "sourceloader.h"

void FileLoader::open(const std::string &file_name)
{
    input_stream.open(file_name);

    is_open = true;
}
