# DataStream
A subclass of [QDataStream](https://doc.qt.io/qt-6/qdatastream.html) intended to make handling video game assets easier.

Changes include the following:
* Adds platform-based endianness differentiation
* Adds platform-based 32/64 bit pointer length differentiation
* Adds read/write support for pointers, size_t, and strings (both fixed-length and null-terminated)
* Makes seek(), peek(), pos(), open(), and close() available without calling device()
* Adds skip() for arbitrary-length skips (based on seek())
* Overloads readRawData() to read into a secondary DataStream (useful for maintaining a buffer with unknown data and/or padding)

This is by no means perfect or complete, but it's done everything I need it to so far. If someone else ends up using this, feel free to open a pull request with any changes you want added.
