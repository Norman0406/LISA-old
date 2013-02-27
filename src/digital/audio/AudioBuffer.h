#ifndef DIGITAL_AUDIOBUFFER_H
#define DIGITAL_AUDIOBUFFER_H

#include <QtCore/QIODevice>

namespace digital
{
	class AudioBuffer
		: public QIODevice
	{
		Q_OBJECT

	public:
		AudioBuffer(qint64, QObject*);
		~AudioBuffer();

		qint64 writeData(const char*, qint64);
		qint64 readData(char*, qint64);
		
		qint64 getSampleBuffer(QByteArray&, qint64) const;
		qint64 getSampleBuffer(char*, qint64) const;
		
	private:
		char* m_buffer;
		qint64 m_bufferSize;
		qint64 m_bufferLength;
		qint64 m_position;
	};
}

#endif // DIGITAL_AUDIOBUFFER_H