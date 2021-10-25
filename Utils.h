#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QVideoFrame>
#include <QImage>

class QMediaPlayer;
class QVideoProbe;
class QImage;

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    ~Utils();

    static Utils* getInstance();
    void initDirectories();

    QString createThumbnails(QString path);

    Q_INVOKABLE void createVideoWithText(QString path, QString text);
signals:

private slots:
    void handleVideoProbed(QVideoFrame frame);


private:
    QString m_path;
    QString m_text;
    QString m_shape;
    quint64 m_FrameCounter;
    static Utils* m_instance;
    QMediaPlayer* m_mediaPlayer;
    QVideoProbe* m_videoProbe;
    QImage m_image;
};

#endif // UTILS_H
