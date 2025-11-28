## MiniZ

Copyright 2013-2014 RAD Game Tools and Valve Software
Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

#include "miniz.h"

mz_zip_archive zip;
memset(&zip, 0, sizeof(zip));

if (!mz_zip_reader_init_file(&zip, "data.zip", 0)) {
    std::cerr << "Failed to open ZIP\n";
}

int fileCount = mz_zip_reader_get_num_files(&zip);

for (int i = 0; i < fileCount; i++) {
    mz_zip_archive_file_stat stat;
    mz_zip_reader_file_stat(&zip, i, &stat);

    size_t size = 0;
    void* data = mz_zip_reader_extract_file_to_heap(&zip, stat.m_filename, &size, 0);

    std::string content((char*)data, size);
    mz_free(data);

    std::cout << "Extracted " << stat.m_filename << "\n";
}

mz_zip_reader_end(&zip);
