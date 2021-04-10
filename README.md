## Sections
- [Sections](#sections)
- [Introduction](#introduction)
- [Note](#note)
- [Usage](#usage)
    - [Linux](#linux)
    - [Windows](#windows)

## Introduction
This is a resync tool made for srt files.
The binaries are avialable in the ''Excutables'' directory and the source code for linux development is made available.

I plan to keep the code **updated and add more features later** and reach an identical interface and probably identical source code.

## Note
The code was mainly **developed for linux**, then I decided to compile it on windows, but due to filesystem differences and problems with windows multithreading, I had to simplify the code on windows.

It still works as expected, just follow the guide and you'll have your subtitles resynced in no time.

## Usage
A file with the name **Resynced_** followd by **the name of the original file** will be created in **the directory where the original file resides**.
#### Linux
Just download the file found in **Excutables/Linux_64/SrtTimeShifter**, then **./** the file.

For, example:
> ./my super useful tools/SrtTimeShifter

#### Windows
Open the file found in **Excutables/Windows_32/Srt-Resync-Tool.exe**.

**Super Important note for windows users:**
when inserting the directory of the srt file, take care not to use the backward slash " \ "  between directories, insted use the foward slash character denoted as " / "

**For, example:**
> E:/my favourite movies/definetly not an Avengers movie/definetly not an Avengers movie.srt
