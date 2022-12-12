import QtQuick 2.0

Item {
    width: 200
    height: 200

    Rectangle {

        width: 100
        height: 100
        anchors.centerIn: parent

        color: "blue"

        Image {
            anchors.centerIn: parent
            objectName: "obj_img_123"
            //source: "qrc:/loading_img/loading_00000.png"
        }
    }
}
