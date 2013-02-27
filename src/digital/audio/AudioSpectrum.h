#ifndef DIGITAL_AUDIOSPECTRUM_H
#define DIGITAL_AUDIOSPECTRUM_H

#include <QtCore/QObject>
#include <QtMultimedia/QAudioFormat>
#include <QtCore/QVector>
#include <complex>

namespace digital
{	
	enum AudioSpectrumWindow {
		WT_RECT = 0,
		WT_HANNING,	// or HANN?
		WT_HAMMING,
		WT_BLACKMAN,
		WT_BLACKMANHARRIS,
	};

	class AudioSpectrumWorker;

	class AudioSpectrum
		: public QObject
	{
		Q_OBJECT

	public:
		// UNDONE: add blackman and blackman-harris
		// see here: http://en.wikipedia.org/wiki/Window_function#Hamming_window

		AudioSpectrum(int, AudioSpectrumWindow, QObject*);
		~AudioSpectrum();
		
		void init();
		int getFFTSize() const;
		int getSpectrumSize() const;
		void setPassband(int min, int max);
		void getPassband(int& min, int& max) const;

	public slots:
		void compute(const QAudioFormat& format, const QByteArray& buffer);
		void spectrumReady();

	signals:
		void dataReady(const QVector<double>&, int, int);
		void passbandChanged(int min, int max);

	private:		
		QVector<double> m_spectrumVis;
		AudioSpectrumWorker* m_fftWorker;
		QThread* m_fftThread;
	};
}

#endif // DIGITAL_AUDIOSPECTRUM_H