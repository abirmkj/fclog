# fclog
#### Formatted console logger

Did you ever want to print logging messages to console for debugging, and wished it was color-coded? Of course, there are numerous full-fledged logging libraries out there that can do the task. But sometimes the effort of including them for a small project is just too much! 

Enter `fclog` - short for **F**ormmatted **C**onsole **LOG**ger - a wrapper around good old `std::cout` that prints color-coded debug messages to the terminal. Light enough to work on an embedded platform (well, one that supports C++ with `iostream`) like my friendly [Onion Omega 2+]()

# Usage

Download the two files, `fclog.h` and `fclog.cpp`, add them to your C++ project, and you're all set.

In your code initialize `fclog` like so:

```c++
  // This is the declaration -> void Logger(fclog::Severity min_severity = fclog::Severity::INFO, bool print_timestamp = false);
  fclog::Logger(/*min_severity = */fclog::Severity::NOTICE, /*print_timestamp = */true);
```
and then use the appropriate log function where needed...
```c++
  using namespace fclog; // -> use the functions without typing the namespace prefix everytime
  ...
  DEBUG() << "this is a" << " debug message" << std::endl;
  INFO() << "this is an" << std::endl << " informational message" << std::endl;
  ...
  int result = system("echo 'My Main Man'");
  ERROR_IF(result != 0) << "echo failed : this is a catastrophe!" << std::endl;
```

## Configurations

As seen from the declaration in `fclog.h`, 
```c++
  void Logger(fclog::Severity min_severity = fclog::Severity::INFO, bool print_timestamp = false);
```
`fclog` takes two configuration inputs at initialization: 
  1. Minimum log severity level (default: `INFO`) - an `enum`
  2. Whether to print timestamp to console (default: false) - a `boolean`

Just pass in the values you want, or nothing if you're happy with the defaults.

# For Developers

Simply put, `fclog` is a C-style wrapper around C++ functions (Blasphemy! I know!). Log severity levels are defined in an `enum` in the header file, `fclog.h`. The entire logic is implemented in a single "static" function called `logItem`. The declared functions `INFO()`, `DEBUG()`, `ERROR()`, etc. --and their `*_IF(...)` variants-- simply call `logItem` with appropriate prefixes and color codes to print.

In lieu of a `class` or `struct`, two (2) static "state variables" are used in `fclog.cpp`: 
  * `short min_log_level` - keeps track of the minimum log severity level chosen at initialization; messages are printed to console if the enum value is lower than `min_log_level` (check the function, `doLog()` and its usage for clarity);
  * `bool disp_time` - keeps track of whether to print a timestamp to the console; if `true` the timestamp is formatted as `std::put_time( /*std::tm*/&utm, "%F %T %Z  " )` and printed to console.

A third static variable,
  * `ostream cnull(0)` - represents a null output stream: it acts like `dev/null` and is used to bypass printing to console;

# (Better) Alternatives?
If you're looking to log to files, or want a full-fledged solution with file rotation etc., one of the following will be better for your application    
(in no particular order):
  * [ulog](https://github.com/Carabasen/ulog)
  * [plog](https://github.com/SergiusTheBest/plog)
  * [spdlog](https://github.com/gabime/spdlog) - I've used `spdlog` in other C++ (commercial) projects and it's fantastic!
  * [loguru](https://github.com/emilk/loguru)
  * [NanoLog](https://github.com/Iyengar111/NanoLog)

# Contributions

Currently, this module seems complete. I'm happy to receive feedback on code correctness and optimization. Also, if you have alternative suggestions, please share them.
