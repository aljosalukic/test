#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QVideoFrame>
#include <QMediaPlayer>


class QVideoProbe;
class QImage;

class Utils : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool value NOTIFY signalShowProgressBar)
public:
    explicit Utils(QObject *parent = nullptr);
    ~Utils();

    static Utils* getInstance();
    void initDirectories();

    QString createThumbnails(QString path);

    Q_INVOKABLE void createVideoWithText(QString path, QString text);

signals:
    void signalShowProgressBar(bool show);

private slots:
    void handleVideoProbed(QVideoFrame frame);
    void handleStateChanged(QMediaPlayer::State);

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
