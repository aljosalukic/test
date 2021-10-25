import QtQuick 2.0

Item {
    id:container
    width: parent.width
    height: parent.height

    signal clicked(string name)

    Rectangle{
        id:itemRect
        x: 0
        y: 0

        width: parent.width
        height: parent.height
        color: "#ba9393"

        Text {
            id: rawVideos
            text: qsTr("Raw videos")
            rotation: 0
            font.pointSize: 20
            style: Text.Sunken
            font.capitalization: Font.MixedCase
            font.bold: true
            width: 140
            opacity: 1
            color: "#ffffff"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            MouseArea {
                anchors.fill: parent
                anchors.rightMargin: -51
                anchors.bottomMargin: 0
                anchors.leftMargin: -49
                anchors.topMargin: 0
                onClicked:  { container.clicked("RawVideos")
                }
            }
        }

        Text {
            id: editedVideos
            text: qsTr("Edited videos")
            x: parent.width/2
            color: "#ffffff"
            anchors.top: rawVideos.bottom
            verticalAlignment: Text.AlignBottom
            styleColor: "#fff9f9"
            font.bold: true
            font.pointSize: 20
            rotation: 0
            scale: 1
            anchors.horizontalCenter: parent.horizontalCenter

            MouseArea {
                anchors.fill: parent
                anchors.rightMargin: -50
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                anchors.leftMargin: 0
                onClicked:  {  container.clicked("EditedVideos")
                }
            }

        }
    }

    function move()
    {
        //        container.width = parent.width *0.3
        container.x = 0
        anim.running = true
    }

    NumberAnimation
    {
        id:anim
        target: container
        properties: "width"
        from: container.parent.width
        to: container.parent.width *0.3
        duration: 500
    }
}
