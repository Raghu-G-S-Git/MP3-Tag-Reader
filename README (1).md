
# MP3 Tag Reader

This is a simple C program that reads and displays ID3 tags (metadata) from MP3 files.

## Features

- Reads ID3v1 metadata from MP3 files
- Displays information like title, artist, album, year, genre, etc.
- Sample MP3 files included for testing

## Files

- `main.c`: Entry point of the program.
- `functions.c`: Contains the implementation of tag reading logic.
- `headers.h`: Header file for shared declarations.
- `.vscode/settings.json`: VS Code configuration.
- `sample.mp3`, `shape_of_you.mp3`: Sample MP3 files for testing.
- `a.out`: Compiled output (can be deleted and regenerated).

## Usage

### Compile the program

```bash
gcc main.c functions.c -o mp3reader
```

### Run the program

```bash
./mp3reader <filename.mp3>
```

Example:

```bash
./mp3reader sample.mp3
```

## Requirements

- GCC or any C compiler
- Unix-based OS (or modify for Windows)

## Notes

- Only ID3v1 tags are supported.
- Make sure the MP3 files have ID3v1 tags at the end of the file.

## License

This project is open-source and free to use.
