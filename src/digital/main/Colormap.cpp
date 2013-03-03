#include "Colormap.h"
#include "ColormapVisitor.h"
#include <QtCore/QDebug>

namespace digital
{
	Colormap::Colormap(int range, QObject* parent)
		: QObject(parent), m_range(range)
	{
		// create color table
		m_colorTable = new QColor[range];
		
		// standard color map
		addColor(0, Qt::black);
		addColor(range - 1, Qt::white);
		
		buildColorTable();
	}

	Colormap::~Colormap()
	{
		delete[] m_colorTable;
	}
	
	void Colormap::addColor(int pos, const QColor& color)
	{
		if (pos < 0 || pos >= m_range) {
			qWarning() << "color value position is out of range: " << pos;
			pos = pos < 0 ? 0 : pos >= m_range ? m_range : pos;
		}

		m_colors[pos] = color;
	}

	void Colormap::clear()
	{
		m_colors.clear();
	}

    void Colormap::accept(ColormapVisitor& visitor)
	{
		clear();
		visitor.visit(*this);
		buildColorTable();
	}

	int Colormap::getRange() const
	{
		return m_range;
	}

	void Colormap::buildColorTable()
	{
		// iterate through colors and create a color map
		for (QMap<int, QColor>::const_iterator it = m_colors.begin(); it != m_colors.end(); it++) {
			// get first color
			const int colorPos1 = it.key();
			const QColor col1 = it.value();

			// get next color
			QMap<int, QColor>::const_iterator itNext = it + 1;
			if (itNext != m_colors.end()) {
				const int colorPos2 = itNext.key();
				const QColor col2 = itNext.value();

				// create color map between the two colors
				for (int i = colorPos1; i < colorPos2; i++) {
					double val = 1 - ((i - colorPos1) / (float)(colorPos2 - colorPos1));

					// set interpolated color
					m_colorTable[i].setRgb(val * col1.red() + (1 - val) * col2.red(),
						val * col1.green() + (1 - val) * col2.green(),
						val * col1.blue() + (1 - val) * col2.blue());
				}
			}
			else {
				// set last color value
				m_colorTable[colorPos1] = col1;
			}
		}
	}

	QColor Colormap::getColorValue(int pos)
	{
		// check and clamp value
		if (pos < 0 || pos >= m_range) {
			qWarning() << "color value position is out of range: " << pos;
			pos = pos < 0 ? 0 : pos >= m_range ? m_range : pos;
		}

		// return color value
		return m_colorTable[pos];
	}
}
