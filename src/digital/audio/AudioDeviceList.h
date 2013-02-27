#ifndef HAM_DIGITAL_H
#define HAM_DIGITAL_H

#include <QtMultimedia/QAudioInput>

namespace ham
{
	class AudioDevice
		: public QIODevice
	{
		Q_OBJECT

	public:
		AudioDevice(const QAudioFormat&, QObject*);
		~AudioDevice();

		void start();
		void stop();

		qreal level() const { return m_level; }

		qint64 readData(char* data, qint64 maxlen);
		qint64 writeData(const char* data, qint64 len);

	signals:
		void update();

	private:
		const QAudioFormat m_format;
		quint32 m_maxAmplitude;
		qreal m_level;
	};
}

#endif // HAM_DIGITAL_H