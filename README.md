
# 🎵 MP3 Tag Reader (C Project)

A command-line utility written in **C** that allows you to **read and edit ID3v2.3 tags** from `.mp3` files. It directly interacts with the binary structure of the file to retrieve and manipulate metadata such as **Title, Artist, Album, Year, and Genre**.

---

## 📌 Features

- ✅ Read metadata from `.mp3` files
- ✅ Supports ID3 version 2.3 tag validation
- ✅ Edit specific fields like:
  - `Title`
  - `Artist`
  - `Album`
  - `Year`
  - `Genre`
- ✅ Command-line interface
- ✅ Built using standard C libraries (portable and lightweight)
- ✅ Error handling for unsupported formats and invalid input

---

## 🛠️ Technologies Used

- **Language**: C  
- **Compilation**: GCC (recommended), Turbo C (legacy support)  
- **Platform**: Windows / Linux  
- **File I/O**: Binary mode operations on `.mp3` files

---

## 🚀 How to Compile & Run

### 🧾 Compile:
```bash
gcc main.c functions.c -o mp3reader
```

### 🔍 View MP3 Tags:
```bash
./mp3reader -v sample.mp3
```

### ✏️ Edit MP3 Tags:
```bash
./mp3reader -e -t "New Title" sample.mp3
```

### 📌 Replace:

- `-t` → Title  
- `-a` → Artist  
- `-A` → Album  
- `-y` → Year  
- `-g` → Genre  

### Example:
```bash
./mp3reader -e -a "Ed Sheeran" shape_of_you.mp3
```

---

## 📁 Project Structure

```
MP3-Tag-Reader/
├── main.c             # Entry point for the application
├── functions.c        # Contains logic for viewing/editing tags
├── headers.h          # Header file with declarations
├── sample.mp3         # Test MP3 file
├── shape_of_you.mp3   # Another test file
├── README.md          # Project documentation
└── .vscode/           # (Optional) VS Code settings
```

---

## 🧠 What I Learned

- Reading binary files in C  
- Parsing structured metadata (ID3 tags)  
- Handling command-line arguments  
- File validation and error checking  
- Working with file pointers and memory-safe string handling  

---

## 🤝 Contributions

Pull requests are welcome! If you spot a bug or want to enhance the functionality (like support for ID3v2.4), feel free to open an issue or submit a PR.

---

## 📜 License

This project is licensed under the MIT License.
