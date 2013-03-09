/***********************************************************************
*
* LISA: Lightweight Integrated System for Amateur Radio
* Copyright (C) 2013 Norman Link <norman.link@gmx.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***********************************************************************/

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
