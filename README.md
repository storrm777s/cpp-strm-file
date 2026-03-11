Made for general C++ practice.

## Efficiency:
Currently, this way of storing pixel data, is really damn inefficient. This 1000x1000 pixel file (rawdata.strm) is 21.9mb!!
I believe that's around 150-200x bigger than most image files.

This wasn't built for efficiency however, but I do recognize that it isn't efficient at all.
## PD:
`PD[0'0:0,255,128]`

The program identifies the pixel data by looking for `PD[`, grabs everything past that but behind the next `'` character.

The program identifies that as the X coordinate, afterwards it looks past the `'` character but behind the `:` character.

You might've guessed it, that's identified as the Y coordinate.

Afterwards, it will loop through the rest of the info, It identifies the characters behind the next `,` as **R**GB,

then, behind the next `,` it identifies R**G**B, and finally RG**B**
```
title:Generated] // Self explanatory!
sizex:1000] // Self explanatory!
sizey:1000] // Self explanatory!

PD[0'0:0,255,128]
PD[1'0:69,185,223]
PD[2'0:138,116,253]
PD[3'0:95,159,245]
```
