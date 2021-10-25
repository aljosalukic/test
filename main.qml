import QtQuick 2.15
import QtQuick.Window 2.15

import Model 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Edit videos")

    property var videoModel: VideoItemsModel{};

    function showVideos(name)
    {
        videoModel.updateListItems(name);

        if(listVideos.visible == false)
        {
            meniItems.move()
            listVideos.visible = true
            anim.running = true
        }

    }

    Meni{
        id:meniItems
        onClicked: {showVideos(name)}
    }

    VideoItem
    {
        id:listVideos
        visible: false
    }


    NumberAnimation
    {
        id:anim
        target: listVideos
        properties: "x"
        to: listVideos.parent.width *0.3
        from: listVideos.parent.width
        duration: 500
    }

    Component.onCompleted: { listVideos.setModel(videoModel)}
}
