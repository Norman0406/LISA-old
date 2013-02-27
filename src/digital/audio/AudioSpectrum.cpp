#include "AudioSpectrum.h"
#include "AudioSpectrumWorker.h"
#include "AudioDevice.h"
#include <QtCore/qmath.h>
#include <QtCore/qnumeric.h>
#include <QtCore/QThread>

namespace digital
{
	AudioSpectrum::AudioSpectrum(int fftSize, AudioSpectrumWindow wdType, QObject* parent)
		: QObject(parent), m_fftWorker(0), m_fftThread(0)
	{
		m_fftThread = new QThread(this);
		m_fftWorker = new AudioSpectrumWorker(fftSize, wdType);
		m_fftWorker->moveToThread(m_fftThread);
		
		connect(m_fftThread, &QThread::started, m_fftWorker, &AudioSpectrumWorker::run);
		connect(m_fftWorker, &AudioSpectrumWorker::finished, m_fftThread, &QThread::quit);
		connect(m_fftWorker, &AudioSpectrumWorker::finished, m_fftWorker, &AudioSpectrumWorker::deleteLater);
		connect(m_fftThread, &QThread::finished, m_fftThread, &AudioSpectrumWorker::deleteLater);
		connect(m_fftWorker, &AudioSpectrumWorker::dataReady, this, &AudioSpectrum::spectrumReady);
	}

	AudioSpectrum::~AudioSpectrum()
	{
		delete m_fftWorker;
		delete m_fftThread;
	}

	void AudioSpectrum::init()
	{
		// get default passband
		int passMin, passMax;
		getPassband(passMin, passMax);
		emit passbandChanged(passMin, passMax);

		// start thread
		m_fftThread->start();
	}

	void AudioSpectrum::compute(const QAudioFormat& format, const QByteArray& buffer)
	{
		// start processing FFT
		m_fftWorker->startFFT(format, buffer);
	}
	
	void AudioSpectrum::spectrumReady()
	{
		const QVector<double>& spectrumMagSq = m_fftWorker->getSpectrumMagSq();
		const QVector<double>& spectrumLog = m_fftWorker->getSpectrumLog();
		m_spectrumVis = spectrumLog;
		
		for (int i = 0; i < m_spectrumVis.size(); i++)
			m_spectrumVis[i] = spectrumLog[i] * 255;

		int passMin, passMax;
		getPassband(passMin, passMax);

		emit dataReady(m_spectrumVis, passMin, passMax);
	}

	int AudioSpectrum::getFFTSize() const
	{
		return m_fftWorker->getFFTSize();
	}
	
	int AudioSpectrum::getSpectrumSize() const
	{
		return m_fftWorker->getSpectrumSize();
	}
	
	void AudioSpectrum::setPassband(int min, int max)
	{
		m_fftWorker->setPassband(min, max);
		emit passbandChanged(min, max);
	}

	void AudioSpectrum::getPassband(int& min, int& max) const
	{
		m_fftWorker->getPassband(min, max);
	}
}
