#pragma once

#include <QDataStream>
#include <QFile> // For seeks and device flags

class DataStream : public QDataStream
{
public:
	enum class Platform
	{
		PS3,
		X360,
		PC,
		PS4,
		NX
	};

	DataStream(QIODevice* device, Platform platform = Platform::PC);
	DataStream(Platform platform = Platform::PC);

	// Get the stream's current platform
	Platform getPlatform();

	// Set the stream's currrent platform and update details
	void setPlatform(Platform platform);

	// Get whether the stream reads and writes pointers as 32 or 64 bit
	bool getIs64Bit();

	// Set whether the stream reads and writes pointers as 32 or 64 bit
	void setIs64Bit(bool setting);

	// Reads a pointer from this stream into an integer variable
	void readPtr(qint64& ptr);

	// Writes an integer value to a pointer variable
	void writePtr(qint64 ptr);

	// Reads a size_t field from this stream into an integer variable
	void readSize(size_t& size);

	// Writes an integer value to a size_t variable
	void writeSize(size_t size);

	// Reads an unspecified number of bytes from this stream into a string
	// Ends when a null terminator is reached
	void readString(QString& string);

	// Reads a specified number of bytes from this stream into a string
	void readString(QString& string, quint32 length);

	// Writes a string to the stream, optionally limited to a maximum length and/or null terminated
	void writeString(QString string, bool nullTerminated = false, qint64 length = -1);

	// Reads a specified number of bytes from this stream to another stream, writing to a specified
	// offset in the other stream. By default, this offset is the current offset of this stream.
	// This is most useful for storing unknown data and padding to prevent data loss
	void readRawData(DataStream& stream, quint32 length, qint64 position = -1);

	// Get the current offset the device is reading/writing from
	qint64 pos();

	// Opens the device
	void open(QIODeviceBase::OpenMode mode);

	// Seeks to a specified offset in the device
	void seek(qint64 offset);

	QByteArray peek(qint64 maxlen);

	// Seeks to a position which is a specified length beyond the current offset
	void skip(qint64 length);

	// Closes the device
	void close();

private:
	Platform platform;
	bool is64Bit = false;

	// Set endianness based on platform (default is big endian)
	void setDefaultEndianness();

	// Set whether to read as 64 bit based on platform (default is false)
	void setDefaultIs64Bit();
};
