#include <gamedata-stream.h>

GameDataStream::GameDataStream(QIODevice* device, Platform platform, FloatingPointPrecision precision)
	: platform(platform)
{
	// Set the device
	setDevice(device);
	
	// Set platform-specific details
	setPlatform(platform);

	// Set floating point precision
	setFloatingPointPrecision(precision);
}

GameDataStream::GameDataStream(Platform platform, FloatingPointPrecision precision)
	: platform(platform)
{
	// Set platform-specific details
	setPlatform(platform);

	// Set floating point precision
	setFloatingPointPrecision(precision);
}

// Get the stream's current platform
GameDataStream::Platform GameDataStream::getPlatform()
{
	return platform;
}

// Set the stream's current platform and update details
void GameDataStream::setPlatform(Platform platform)
{
	this->platform = platform;
	setDefaultEndianness();
	setDefaultIs64Bit();
}

// Get whether the stream reads and writes pointers as 32 or 64 bit
bool GameDataStream::getIs64Bit()
{
	return is64Bit;
}

// Set whether the stream reads and writes pointers as 32 or 64 bit
void GameDataStream::setIs64Bit(bool setting)
{
	is64Bit = setting;
}

// Reads a pointer from this stream into an integer variable
void GameDataStream::readPtr(qint64& ptr)
{
	if (!is64Bit)
		*this >> (qint32&)ptr;
	else
		*this >> ptr;
}

// Writes an integer value to a pointer variable
void GameDataStream::writePtr(qint64 ptr)
{
	if (!is64Bit)
		*this << (qint32)ptr;
	else
		*this << ptr;
}

// Reads a size_t field from this stream into an integer variable
void GameDataStream::readSize(size_t& size)
{
	if (!is64Bit)
		*this >> (quint32&)size;
	else
		*this >> size;
}

// Writes an integer value to a size_t variable
void GameDataStream::writeSize(size_t size)
{
	if (!is64Bit)
		*this << (quint32)size;
	else
		*this << size;
}

// Reads an unspecified number of bytes from this stream into a string
// Ends when a null terminator is reached
void GameDataStream::readString(QString& string)
{
	string.clear();
	char c;
	while (!device()->atEnd())
	{
		*this >> c;
		if (c == '\0')
			break;
		string.append(c);
	}
}

// Reads a specified number of bytes from this stream into a string
void GameDataStream::readString(QString& string, quint32 length)
{
	string = QString::fromLatin1((device()->read(length)));
}

// Writes a string to the stream, optionally limited to a maximum length and/or null terminated
void GameDataStream::writeString(QString string, bool nullTerminated, qint64 length)
{
	device()->write(string.toLatin1(), length == -1 ? string.size() : length);
	if (nullTerminated)
		*this << '\0';
}

// Reads a specified number of bytes from this stream to another stream, writing to a specified
// offset in the other stream. By default, this offset is the current offset of this stream.
// This is most useful for storing unknown data and padding to prevent data loss
void GameDataStream::readRawData(GameDataStream& stream, quint32 length, qint64 position)
{
	position != -1 ? stream.seek(position) : stream.seek(pos());
	stream.device()->write(device()->read(length));
}

// Get the current offset the device is reading/writing from
qint64 GameDataStream::pos()
{
	return device()->pos();
}

// Opens the device
void GameDataStream::open(QIODeviceBase::OpenMode mode)
{
	device()->open(mode);
}

// Seeks to a specified offset in the device
void GameDataStream::seek(qint64 offset)
{
	device()->seek(offset);
}

QByteArray GameDataStream::peek(qint64 maxlen)
{
	return device()->peek(maxlen);
}

// Seeks to a position which is a specified length beyond the current offset
void GameDataStream::skip(qint64 length)
{
	device()->seek(pos() + length);
}

// Closes the device
void GameDataStream::close()
{
	device()->close();
}

// Set endianness based on platform (default is big endian)
void GameDataStream::setDefaultEndianness()
{
	switch (platform)
	{
	case Platform::GC:
	case Platform::X360:
	case Platform::PS3:
	case Platform::WII:
	case Platform::WIIU:
		setByteOrder(QDataStream::BigEndian);
		break;
	default:
		setByteOrder(QDataStream::LittleEndian);
		break;
	}
}

// Set whether to read as 64 bit based on platform (default is false)
void GameDataStream::setDefaultIs64Bit()
{
	switch (platform)
	{
	case Platform::PS4:
	case Platform::NX:
		setIs64Bit(true);
		break;
	default:
		setIs64Bit(false);
		break;
	}
}
