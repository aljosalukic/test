#include "Utils.h"
#include <QImage>
#include <QUrl>
#include <QVideoFrame>
#include <QVideoProbe>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QPainter>

const static QString DEFALT_ICON = "qrc:/images/Pictures/videoIcon.jpg";
const static QString RAW_FOLDER = "RawVideos";
const static QString EDITED_FOLDER = "EditedVideos";

const static QString TMP_FOLDER = "tmp";

Utils* Utils::m_instance = Q_NULLPTR;


Utils::Utils(QObject *parent) : QObject(parent),
    m_image(Q_NULLPTR)
{
    m_mediaPlayer = new QMediaPlayer();
    m_videoProbe = new QVideoProbe();

    m_videoProbe->setSource(m_mediaPlayer);

    bool ok = connect(m_videoProbe, &QVideoProbe::videoFrameProbed, this, &Utils::handleVideoProbed);
    Q_ASSERT(ok);
    ok = connect(m_mediaPlayer, &QMediaPlayer::stateChanged, this, &Utils::handleStateChanged);
    Q_ASSERT(ok);
}

Utils::~Utils()
{
    delete m_videoProbe;
    delete m_mediaPlayer;
}

Utils *Utils::getInstance()
{
    if (m_instance == Q_NULLPTR)
    {
        m_instance = new Utils();
    }
    return m_instance;
}

void Utils::initDirectories()
{
    QDir directory;
    directory.mkdir(RAW_FOLDER);
    directory.mkdir(EDITED_FOLDER);
}

QString Utils::createThumbnails(QString path)
{
    QString target = DEFALT_ICON;
    QDir directory(path);
    directory.cdUp();
    QFile file(path);

    QString filename = file.fileName();
    if(filename.endsWith(".avi"))
    {
        filename.chop(4);
        target = filename + ".jpg";

        if(QFile::exists(target))
        {
            return QString( "file:" + target);
        }
        QProcess process;

        bool ok = connect(&process, &QProcess::errorOccurred, this, [=](QProcess::ProcessError error){qDebug() << "error: "<< error;});
        Q_ASSERT(ok);
        ok = connect(&process, &QProcess::started, this, [=](){qDebug() << "Started";});
        Q_ASSERT(ok);

        QStringList arguments;

        QProcess ffmpeg;
        ffmpeg.start("ffmpeg" , QStringList()
                     << "-y"
                     << "-i" << QDir::toNativeSeparators(path)
                     << "-frames:v" << "1"
                     << "-q:v" << "1"
                     << "-f" << "image2"
                     << QDir::toNativeSeparators(target));
        ffmpeg.waitForFinished(-1);



        return QString( "file:" + target);
    }

    return target;
}

void Utils::createVideoWithText(QString path, QString text)
{
    QDir directory;
    directory.mkdir(TMP_FOLDER);

    m_text = text;
    m_path = path;
    m_FrameCounter = 0;
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(path));
    m_mediaPlayer->play();
}

void Utils::handleVideoProbed(QVideoFrame frame)
{
    m_FrameCounter++;
    QImage image = frame.image();
    QPainter painter;
    painter.begin(&image);
    painter.setPen(QPen(Qt::red));
    painter.setFont(QFont("Times", 20, QFont::Bold));
    painter.drawText(image.rect(), Qt::AlignCenter, m_text);
    painter.end();

    QString name = "tmp" + QString::number(m_FrameCounter);

    image.save(TMP_FOLDER + "/" + name + ".jpg");
}

void Utils::handleStateChanged(QMediaPlayer::State state)
{
    //ffmpeg -start_number n -i test_%d.jpg -vcodec mpeg4 test.avi
    if(state == QMediaPlayer::State::StoppedState)
    {
        QProcess process;

        bool ok = connect(&process, &QProcess::errorOccurred, this, [=](QProcess::ProcessError error){qDebug() << "error: "<< error;});
        Q_ASSERT(ok);
        ok = connect(&process, &QProcess::started, this, [=](){qDebug() << "Started";});
        Q_ASSERT(ok);

        //connect to finish process signal and do stuff there -> send signal to progressbar window, remove tmp directory, etc...

        QStringList arguments;

        QProcess ffmpeg;
        ffmpeg.start("ffmpeg" , QStringList()
                     << "-start_number" << "1"
                     << "-i" << "tmp%d.jpg"
                     << "-vcodec" << "mpeg4"
                     << QDir::toNativeSeparators("output.avi"));

        emit signalShowProgressBar(false);

    }
    else if(state == QMediaPlayer::State::PlayingState)
    {
        emit signalShowProgressBar(true);
    }
}
