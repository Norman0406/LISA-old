#ifndef DIGITAL_AUDIODEVICE_H
#define DIGITAL_AUDIODEVICE_H

#include <QtMultimedia/QAudioInput>
#include "AudioBuffer.h"

namespace digital
{	
	// TODO: run inside a thread

	class AudioDevice
		: public QObject
	{
		Q_OBJECT

	public:
		virtual ~AudioDevice();

		void init();

		virtual void start() = 0;
		virtual void stop() = 0;

		static qreal pcmToReal(qint16 pcm);
		static qint16 realToPcm(qreal real);
		static qint64 audioLength(const QAudioFormat& format, qint64 microSeconds);

		const QAudioFormat& getFormat() const;
		
	signals:
		void dataReady(const QAudioFormat&, QByteArray& buffer, int dataLength);

	protected:
		AudioDevice(QObject*);

		virtual void iInit(const QAudioDeviceInfo&) = 0;

	//private:
		QAudioFormat		m_format;
		QIODevice*			m_device;
		QByteArray*         m_buffer;
		qint64              m_bufferSize;
		AudioBuffer*		m_audioBuffer;
	};
}

#endif // DIGITAL_AUDIODEVICE_H
