import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import UtilsModel 1.0

Dialog {
    id:formDialog
    visible: false
    width : 400
    height : 200
    title: "Add items"
    property var path;

    property var utils : Utils{}

    standardButtons: Dialog.Ok | Dialog.Cancel

    function editVideo()
    {
        if(radioText.checked == true)
        {
            utils.createVideoWithText(path, textField.text);

        }
        else
        {
            console.log("signal to utils to create shape")
        }
    }

    Connections{
        target: utils
        onSignalShowProgressBar:{
            progressBar.visible = show
        }
    }

    Grid {
        id: mainLayout
        columns: 2
        rowSpacing: 5
        columnSpacing: 5

        RadioButton {
            id: radioText
            checked: true
            text: qsTr("Text")

        }
        TextField { id: textField; }
        RadioButton {
            id: radioShape
            text: qsTr("Shape")

        }
        ComboBox {
            id:comboBox
            width: 200
            model: [ "Rectange", "Circle"]
        }

        Label { text: "Choose duration"}
        Slider {
            id:slider
            from: 5
            value: 5
            to: 60
        }
    }

    Dialog{
        id:progressBar
        visible:false
        standardButtons: Dialog.Cancel
        ProgressBar {
            indeterminate: true
        }

        onButtonClicked: console.log("Emit signal, Force creating video to stop!");
    }

    onAccepted: editVideo()
}
