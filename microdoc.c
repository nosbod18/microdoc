/// # microdoc - A tiny C/C++ comment to markdown parser written in C
///
/// ## About
/// `microdoc` is not a real documentation generator like [Doxygen](https://www.doxygen.nl/index.html) or
/// [Sphinx](https://www.sphinx-doc.org/en/master/). It simply takes input from `stdin`, formats it, then
/// prints it to `stdout`. This allows you to write markdown style comments in your C/C++ code, feed
/// it into `microdoc`, and redirect the resulting output wherever you like.
///
/// For example, this documentation can be generated in a file called `README.md` with
///
/// ```bash
/// gcc microdoc.c -o md && ./md < microdoc.c > README.md # Replace gcc with your compiler of choice
/// ```
///
/// An arbitrary number of files can be parsed at once either by listing them all
///
/// ```bash
/// ./md < a.c b.cc c.cpp [...] > README.md
/// ```
///
/// or using wildcards
///
/// ```bash
/// ./md < *.c > README.md
/// ```
///
/// or any other way input can be passed through `stdin`.
///
/// ## How it works
/// `microdoc` is extremely simple. The entire source without comments is only 9 lines.
/// - It scans `stdin` for any "///" comments
/// - If a "///" comment is found, it prints that line without the "///" to `stdout`
///
/// Thats it.
///
/// As an additional feature, you can wrap code in code blocks (\`\`\`) and `microdoc` will include
/// all lines until a closing \`\`\` is reached. This allows you to embed source code straight into
/// your documentation. For example,
///
/// ```c
/// /// This is a structure definition
/// /// ```c
/// typedef struct MyStruct {
///         int a;
///         float b;
/// } MyStruct;
/// /// ```
/// ```
/// will produce
///
/// This is a structure definition
/// ```c
/// typedef struct MyStruct {
///         int a;
///         float b;
/// } MyStruct;
/// ```
///
/// ## Dependencies
/// - Nothing but the C Standard Library
///
/// ## Credit
/// `microdoc` is based off of [pomd4c](https://github.com/andrew-canaday/pomd4c) and
/// [stddoc.c](https://github.com/r-lyeh/stddoc.c)
///
/// ## License
/// This software is available under 2 licenses -- choose whichever you prefer.
///
/// #### ALTERNATIVE A - MIT License
/// Copyright (c) 2021 Evan Dobson
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of
/// this software and associated documentation files (the "Software"), to deal in
/// the Software without restriction, including without limitation the rights to
/// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/// of the Software, and to permit persons to whom the Software is furnished to do
/// so, subject to the following conditions:
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// #### ALTERNATIVE B - Public Domain (www.unlicense.org)
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetuity of all present and future rights to
/// this software under copyright law.
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <string.h>
int main(void) {
        for (char line[2048] = {0}, code = 0; fgets(line, 2048, stdin);) {
                char const *cmt = strstr(line, "//""/") == line ? line + 3 + (line[3] == ' ') : NULL;
                cmt = cmt ? cmt : strstr(line, "--""-") == line ? line + 3 + (line[3] == ' ') : NULL;
                cmt = cmt ? cmt : strstr(line, "##""#") == line ? line + 3 + (line[3] == ' ') : NULL;
                code = strstr(line, "``""`") ? !code : code;
                printf("%s", code && !cmt ? line : cmt ? cmt : "");
        }
}
