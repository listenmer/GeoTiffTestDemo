#ifndef QGTIFREADER_H
#define QGTIFREADER_H

#include <QObject>
#include <QImage>
#include <QGeoCoordinate>
#include <QPoint>

#include "xtiffio.h"  /* for TIFF */
#include "geotiffio.h" /* for GeoTIFF */

class QGtifReader: public QObject
{
    Q_OBJECT
signals:
    void MapChanged();
    void zoomChanged(double zoom);

public:
    QGtifReader(const QString &filepath, QObject *parent = nullptr);
    ~QGtifReader();

    auto isVaild() const -> bool;

    auto setRect(const QRect &rect);

public:
    auto setZoom(double zoom, const QPoint &center = QPoint()) -> void;
    inline auto getZoom() const -> double;

    auto point2GeoCoordinate(const QPoint &pos) const -> QGeoCoordinate;
    auto geoCoordinate2Point(const QGeoCoordinate &coord) const -> QPoint;

    auto dragTo(const QPoint &pos) -> void;

    auto getMap() const -> QImage;

private:
    auto _buildMap() -> void;

    auto _loadSettings() -> void;
    auto _saveSettings() -> void;

private:
    double _zoom;
    QPoint _curMouseCenter;
    QImage _map;
    QImage _scaledMap;
    QRect  _rect;

    TIFF *_tif;  /* TIFF-level descriptor */
    GTIF *_gtif; /* GeoKey-level descriptor */

};

auto QGtifReader::getZoom() const -> double
{
    return _zoom;
}


#endif // QGTIFREADER_H