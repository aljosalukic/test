import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtMultimedia 5.15

import Model 1.0


Rectangle {
    width: parent.width*0.7
    height: parent.height
    x:parent.width *0.3

    function setModel(model: model)
    {
        view.model = model
    }

    function startPlayer(path)
    {
        dialog.visible = true
        dialog.setSource(path)
    }

    ListView {
        id: view
        anchors.fill: parent
        clip: true
        spacing: 10

        model: VideoItemsModel {}

        delegate: RowLayout {
            id: layout
            width: view.width

            Rectangle {
                Layout.fillWidth: true
                Layout.minimumWidth: 200
                Layout.preferredWidth: 200
                Layout.maximumWidth: 200
                Layout.minimumHeight: 100
                Image {
                    id: image
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: model.icon
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: startPlayer(model.path)
                }
            }


            Text {
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 150
                id: name
                text: model.name

                MouseArea{
                    anchors.fill: parent
                    onClicked: startPlayer(model.path)
                }
            }

            Button{
                id:editButton
                text: "Edit video"
                onClicked: {
                    formDialog.path = model.path
                    formDialog.visible = true
                }
            }
        }

        Dialog {
            id:dialog
            visible: false
            width : 800
            height : 600
            title: "Video player"

            function setSource(path)
            {
                player.source = "file:" +  path
                player.play()
            }

            contentItem: Rectangle {
                MediaPlayer {
                    id: player
                }

                VideoOutput {
                    id: videoOutput
                    source: player
                    anchors.fill: parent
                }
            }
        }

        FormDialog{
            id:formDialog
        }

    }
}
