#ifndef DIGITAL_COLORMAP_H
#define DIGITAL_COLORMAP_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtGui/QColor>

namespace digital
{
	class ColormapVisitor;

	class Colormap
		: public QObject
	{
		Q_OBJECT

	public:
		Colormap(int, QObject*);
		~Colormap();

        void accept(ColormapVisitor&);
		void addColor(int, const QColor&);
		int getRange() const;
		QColor getColorValue(int);

		
	private:
		void clear();
		void buildColorTable();

		QMap<int, QColor> m_colors;
		QColor* m_colorTable;
		int m_range;
	};
}

#endif // DIGITAL_COLORMAP_H
