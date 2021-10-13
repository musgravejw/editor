# Editor
A simple text editor

Heavily based on `antirez/kilo` and this [tutorial](https://viewsourcecode.org/snaptoken/kilo/index.html).

## Build

```
$ make
$ make install
$ editor [file]
```

## Commands
```
Ctrl-S to save
Ctrl-Q to quit
```

## Project
```
.
├── LICENSE
├── Makefile
├── README.md
├── bin
│   └── editor
├── editor.c
└── src
    ├── const.c
    ├── file.c
    ├── input.c
    ├── output.c
    └── terminal.c

2 directories, 10 files
```

## License
 * This project is licensed under an Apache-2.0 License.

Copyright (c) 2021, John Musgrave All rights reserved.
