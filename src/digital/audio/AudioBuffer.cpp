#include "AudioBuffer.h"

namespace digital
{
	AudioBuffer::AudioBuffer(qint64 bufferSize, QObject* parent)
		: QIODevice(parent), m_bufferSize(bufferSize)
	{
		m_position = 0;
		m_bufferLength = 0;

		m_buffer = new char[m_bufferSize];
		memset(m_buffer, 0, m_bufferSize);
		open(QIODevice::ReadWrite);
	}

	AudioBuffer::~AudioBuffer()
	{
		delete[] m_buffer;
		close();
	}
		
	qint64 AudioBuffer::writeData(const char* data, qint64 len)
	{
		qint64 dataToWrite = len;

		if (m_position + len >= m_bufferSize) {
			// only write data unil the end is reached and reset position pointer.
			// the rest will be read immediately after in the next call
			dataToWrite = m_bufferSize - m_position;
			memcpy(&m_buffer[m_position], data, dataToWrite);
			m_position = 0;
		}
		else {
			// write data to the current buffer position and increment position pointer
			memcpy(&m_buffer[m_position], data, dataToWrite);
			m_position += dataToWrite;
		}

		// update buffer length
		m_bufferLength += dataToWrite;
		if (m_bufferLength > m_bufferSize)
			m_bufferLength = m_bufferSize;

		emit readyRead();	// correct?
		return dataToWrite;
	}
 
	qint64 AudioBuffer::readData(char* data, qint64 maxSize)
	{
		// not sure if this is working correctly in all cases
		return getSampleBuffer(data, maxSize);
	}

	qint64 AudioBuffer::getSampleBuffer(QByteArray& buffer, qint64 size) const
	{
		if (buffer.isEmpty())
			buffer = QByteArray(size, 0);
		else if (buffer.size() != size) {
			buffer.resize(size);
			buffer.fill(0);
		}

		return getSampleBuffer(buffer.data(), size);
	}

	qint64 AudioBuffer::getSampleBuffer(char* data, qint64 size) const
	{
		// return the (size) number of most recent bytes from the ring buffer

		if (!data)
			return 0;

		qint64 dataToRead = qMin(m_bufferSize, size);
		int readPos = m_position - dataToRead;
		if (readPos < 0) {
			qint64 firstPos = m_bufferSize + readPos;
			qint64 firstSize = -readPos;
			qint64 secondSize = m_position;
			
			memcpy(data, &m_buffer[firstPos], firstSize);
			memcpy(data + firstSize, &m_buffer[0], secondSize);
		}
		else
			memcpy(data, &m_buffer[readPos], dataToRead);
		
		return dataToRead;
	}
}
