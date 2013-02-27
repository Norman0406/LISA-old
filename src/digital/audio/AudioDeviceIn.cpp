#include "AudioDeviceIn.h"
#include <QtCore/QtDebug>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCore/qendian.h>

namespace digital
{
	AudioDeviceIn::AudioDeviceIn(QObject* parent)
		: AudioDevice(parent), m_audioInput(0), m_device(0)
	{
	}

	AudioDeviceIn::~AudioDeviceIn()
	{
	}

	void AudioDeviceIn::iInit(const QAudioDeviceInfo& info)
	{
		// create the input
		m_audioInput = new QAudioInput(info, m_format, this);
		//const int NotifyIntervalMs = 10;
		//m_audioInput->setNotifyInterval(NotifyIntervalMs);
		//m_audioInput->setBufferSize(m_bufferSize);
	}
	
	void AudioDeviceIn::start()
	{
		m_audioInput->start(m_audioBuffer);

		//connect(m_audioInput, &QAudioInput::notify, this, &AudioDeviceIn::notified);
		connect(m_audioInput, &QAudioInput::stateChanged, this, &AudioDeviceIn::stateChanged);
	}

	void AudioDeviceIn::stop()
	{
	}
	
	void AudioDeviceIn::notified()
	{
		/*qWarning() << "bytesReady = " << m_audioInput->bytesReady()
				   << ", " << "elapsedUSecs = " << m_audioInput->elapsedUSecs()
				   << ", " << "processedUSecs = "<< m_audioInput->processedUSecs();*/

		//emit dataReady(m_format, m_outBuffer);
	}

	void AudioDeviceIn::stateChanged(QAudio::State state)
	{
		qDebug() << "state changed: " << state;
	}
	
	const QByteArray& AudioDeviceIn::getBuffer(int size)
	{
		m_audioBuffer->getSampleBuffer(this->m_buffer, size * sizeof(short));
		return m_buffer;
	}
}
