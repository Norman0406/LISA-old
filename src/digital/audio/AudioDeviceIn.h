#ifndef DIGITAL_AUDIODEVICEIN_H
#define DIGITAL_AUDIODEVICEIN_H

#include "AudioDevice.h"
#include <QtMultimedia/QAudioRecorder>

namespace digital
{	
	class AudioDeviceIn
		: public AudioDevice
	{
		Q_OBJECT

	public:
		AudioDeviceIn(QObject*);
		~AudioDeviceIn();

		void start();
		void stop();

		const QByteArray& getBuffer(int);

	public slots:
		void notified();
		void stateChanged(QAudio::State);

	signals:
		void dataReady(const QAudioFormat&, const QByteArray& buffer);

	protected:
		void iInit(const QAudioDeviceInfo&);

	private:
		QAudioInput*	m_audioInput;
		QIODevice*		m_device;
		QByteArray		m_buffer;
	};
}

#endif // DIGITAL_AUDIODEVICEIN_H