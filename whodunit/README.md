# Questions

## What's `stdint.h`?

'stdin.h' Is a headerfile in the standard C library. It provides the user with a set of typedefs, which specifies exact-width integer types and their min/max allowed values.
When you import data you can not always count on long and floats to be readily defined. Using these conventions you can be more specific with what you want from your integer types.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are integer types, where the number stands for the amount of bytes associated with the type. Depending on what you want to do with the type you need a specific amount of memory.
For instance for RGB colours you need for each colour 2 hexadecimal slots which is max 255 (= ff).
So it wouldnt make sense to use the 32 bits type of integer when you want to specify the amount of each colour.
Also, signed (int32_t) vs unsigned (uint32_t) integers show by their type the range they can hold. For unsigned integers can only hold positive numbers, which also makes sense for the RGB colours.
Whearas signed integers with 32 or 64 bits lend themselves better for complex calculations.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

in ASCII: 'B', 'M'

## What's the difference between `bfSize` and `biSize`?

biSize is the size of the BITMAPINFOHEADER, whearas bfSize is the full file size.

## What does it mean if `biHeight` is negative?

It means the bitmap image is top-down, with the startingpoint in the top-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

It is possible that there is not enough memory available for the computer to create the file.

## Why is the third argument to `fread` always `1` in our code?

There is only 1 item of date from which fread() has to read.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
(4 - (3 * 3) % 4) % 4 = 3 % 4 = 3q

## What does `fseek` do?

It sets the file position indicater to a position, using the second argument in the funcion as a pointer.

## What is `SEEK_CUR`?

SEEK_CUR is the wence argument in fseek(). It makes sure the skip over the padding to the next line ends in a suitable position, relative to the start of the file.
