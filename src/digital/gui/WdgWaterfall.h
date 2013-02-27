#ifndef DIGITAL_WDGWATERFALL_H
#define DIGITAL_WDGWATERFALL_H

#include <QtWidgets/QFrame>
#include <QtCore/QTimer>

namespace digital
{
	class Colormap;

	class WdgWaterfall
		: public QFrame
	{
		Q_OBJECT

	public:
		explicit WdgWaterfall(QWidget* parent);
		~WdgWaterfall(void);

		void init(int);
		void setDrawOverlay(bool);

	public slots:
		void addSpectrum(const QVector<double>&);
		void setPassband(int, int);
		
	protected:
		void paintEvent(QPaintEvent* event);
		void resizeEvent(QResizeEvent* event);
		void drawOverlay();

	private:
		void redraw();

		int			m_spectrumSize;
		QSize		m_size;
		QPixmap		m_waterfallPixmap;
		QTimer*		m_redrawTimer;

		QPixmap		m_overlayFrq;

		// use either of them
		Colormap*	m_colorMap;
		QColor		m_colorTable[256];

		int			m_passMin;
		int			m_passMax;
		int			m_border;
		bool		m_drawOverlay;
	};
}

#endif // DIGITAL_WDGWATERFALL_H
