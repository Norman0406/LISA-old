#include "WdgWaterfall.h"
#include "../main/Colormap.h"
#include "../main/ColormapVisitor.h"
#include <QtGui/QPainter>
#include <QtCore/qmath.h>

namespace digital
{
	WdgWaterfall::WdgWaterfall(QWidget* parent)
		: QFrame(parent), m_spectrumSize(0), m_redrawTimer(0),
		m_passMin(0), m_passMax(0), m_border(0), m_drawOverlay(true)
	{
		m_redrawTimer = new QTimer(this);
		m_redrawTimer->setTimerType(Qt::PreciseTimer);
		const int updateInterval = (1 / 30.0f) * 1000;	// fps
		m_redrawTimer->setInterval(updateInterval);
		connect(m_redrawTimer, &QTimer::timeout, this, &WdgWaterfall::redraw);
		m_redrawTimer->start();
	}

	WdgWaterfall::~WdgWaterfall(void)
	{
	}
	
	void WdgWaterfall::init(int specSize)
	{
		m_spectrumSize = specSize;

        ColormapBlue colormap;
        //ColormapFldigi colormap;
		m_colorMap = new Colormap(256, this);
        m_colorMap->accept(colormap);
        //m_colorMap->accept(colormap);
	}

	void WdgWaterfall::setDrawOverlay(bool draw)
	{
		m_drawOverlay = draw;
	}

	void WdgWaterfall::paintEvent(QPaintEvent*)
	{
		QPainter painter(this);
		painter.fillRect(rect(), Qt::black);

		if (m_drawOverlay)
			painter.drawPixmap(0, 0, m_overlayFrq);

		painter.drawPixmap(m_border, m_overlayFrq.height(), m_waterfallPixmap);

		//tell interface that its ok to signal a new line of fft data
		//m_pSdrInterface->ScreenUpdateDone();

		return;
	}

	void WdgWaterfall::resizeEvent(QResizeEvent*)
	{
		if(!size().isValid())
			return;
		
		if(m_size != size()) {
			// if changed, resize pixmaps to new screensize
			m_size = size();

			if (m_drawOverlay) {
				m_overlayFrq = QPixmap(m_size.width(), 50);
				drawOverlay();
			}
			
			QSize waterfallSize(m_size.width() - m_border * 2, m_size.height() - m_overlayFrq.height());
			if (m_waterfallPixmap.isNull()) {
				m_waterfallPixmap = QPixmap(waterfallSize);
				m_waterfallPixmap.fill(Qt::black);
			}
			else {
				m_waterfallPixmap = m_waterfallPixmap.scaled(waterfallSize,
					Qt::IgnoreAspectRatio, Qt::FastTransformation);
			}
		}
	}
	
	void WdgWaterfall::addSpectrum(const QVector<double>& spectrum)
	{
		const int width = m_waterfallPixmap.width();
		const int height = m_waterfallPixmap.height();

		// scroll waterfall pixmap down by 1 pixel
		m_waterfallPixmap.scroll(0, 1, 0, 0, width, height);

		QPainter painter(&m_waterfallPixmap);
		painter.setRenderHint(QPainter::SmoothPixmapTransform);

		// set scaling to the spectrum's coordinate system
		double scaleX = width / (double)spectrum.size();
		painter.scale(scaleX, 1);

		// draw fft data into pixmap in the spectrum's coordinate system
		for (int i = 0; i < spectrum.size(); i++) {
			double value = spectrum[i];
			
			int intVal = value;

			// clamp
			intVal = intVal > 255 ? 255 : intVal < 0 ? 0 : intVal;	
			
			QColor col = m_colorMap->getColorValue(intVal);

			painter.setPen(col);
			painter.drawPoint(i, 0);
		}

		//update();
	}

	void WdgWaterfall::setPassband(int passMin, int passMax)
	{
		// update passband and overlay if necessary
		if (passMax != m_passMax || passMin != m_passMin) {
			m_passMax = passMax;
			m_passMin = passMin;

			if (m_drawOverlay)
				drawOverlay();
		}
	}

	void WdgWaterfall::drawOverlay()
	{
		if (m_overlayFrq.isNull())
			return;

		const int width = m_overlayFrq.width();
		const int height = m_overlayFrq.height();

		m_overlayFrq.fill(Qt::black);

		QPainter painter(&m_overlayFrq);
		painter.setPen(Qt::white);
		
		// TEST
		//m_passMax = 3200;
		//m_passMin = 100;

		const double bigLineFrq = 200.0;	// big lines every x Hz
		const double smallLineFrq = 20.0;	// small lines every y Hz
		
		// set font
		QFont font = painter.font();
		font.setPixelSize(height / 3.5);
		painter.setFont(font);

		// get the border size
		const int borderPadding = 5;	// additional 5 px
		const double numBigLines = (m_passMax - m_passMin) / bigLineFrq;
		m_border = 0;
		for (int i = 0; i < (int)numBigLines + 1; i++) {
			QString text = QString::number(m_passMin + i * bigLineFrq);
			int textWidth = painter.fontMetrics().width(text);

			// adjust border size for waterfall widget
			if (i == 0 || i == numBigLines) {
				if (textWidth / 2 > m_border)
					m_border = textWidth / 2;
			}
		}
		m_border += borderPadding;
		
		// draw main line
		const int mainLinePos = height - height / 5;
		const int bigLineLength = height / 5;
		const int smallLineLength = height / 10;
		
		painter.drawLine(m_border, mainLinePos, (width - m_border), mainLinePos);
		
		const double bigLineDist = (width - m_border * 2) / numBigLines;

		// draw big lines
		for (int i = 0; i < (int)numBigLines + 1; i++) {
			int xPos = m_border + (int)(i * bigLineDist);
			
			QString text = QString::number(m_passMin + i * bigLineFrq);
			int textWidth = painter.fontMetrics().width(text);
			painter.drawText(xPos - textWidth / 2.0, height / 2.5, text);

			painter.drawLine(xPos, mainLinePos, xPos, mainLinePos - bigLineLength);
		}
		
		// draw small lines
		const double numSmallLines = (m_passMax - m_passMin) / smallLineFrq;
		const double smallLineDist = (width - m_border * 2) / numSmallLines;
		for (int i = 0; i < numSmallLines + 1; i++) {
			int xPos = m_border + (int)(i * smallLineDist);
			painter.drawLine(xPos, mainLinePos, xPos, mainLinePos - smallLineLength);
		}
	}

	void WdgWaterfall::redraw()
	{
		update();
	}
}
