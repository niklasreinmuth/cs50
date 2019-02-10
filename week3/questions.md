# Questions

## What's `stdint.h`?

A header file which contains the definition of new integer types. With them, we can use fixed-width integer type lengths that are consistent everywhere.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To create fixed-width integers no matter on which system we run our program.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE`: 1 byte  
`DWORD`: 4 byte  
`LONG`: 4 byte  
`WORD`: 2 byte  

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The `bfType` -> file type. Must be **BM**. 

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size, in bytes, of the bitmap file.
`biSize` is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the bitmap is a top down DIB (device-independent bitmap) and it's origin is in the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the files in argv[1] and argv[2] could not be opened.

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

`size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`  
`fread()` reads _nmemb_ items of data, each _size_ bytes long, from the stream pointed to by _stream_, storing them at the location given by _ptr_.  
On success, `fread()` return the number of items read or written. This number equals the number of bytes transferred only when _size_ is 1.

-> We read one pixel at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

`int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;`
`int padding = (4 - (3          * 3                ) % 4) % 4;`
padding = 3.

## What does `fseek` do?

Sets the file position indicator for the file stream _stream_ to the value pointed to by offset.

`fseek(FILE *stream, long int offset, int whence)`
`stream` - file stream to modify
`offset` - number of characters to shift the position relative to _whence_
`whence` - position to which _offset_ is added. Can have one of the following values: `SEEK_SET, SEEK_CUR, SEEK_END`

## What is `SEEK_CUR`?

Moves the file pointer position to given location.
