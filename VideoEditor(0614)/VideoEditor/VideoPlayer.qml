import QtQuick 2.0
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform 1.0
import QtMultimedia

Rectangle {
        id: rectangle1
        width: 640
        height: 360
        color: "#dcdcdc"
        property alias rectangle1Width: rectangle1.width

        Video {
            id: video
            anchors.fill:parent
            source: "file:///D:/sample/sample2.mp4"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0

            MouseArea {
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                onClicked: {
                    video.play()
                }
            }

            function setPosition(position){
               video.position=position;
            }

            focus: true
            Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video.position = video.position - 5000
            Keys.onRightPressed: video.position = video.position + 5000
        }

    Slider {
        id: slider
        x: 0
        y: 381
        width: 640
        height: 22
        value: video.position/video.duration
        enabled:video.seekable
        to: 1.0
        onMoved:{
            console.log(value*video.duration);
            video.setPosition(value*video.duration)
        }
        live:true
    }

    RoundButton {
        id: roundButton
        x: 249
        y: 409
        text: "+"
        onClicked: {
            video.play();
        }
    }

    RoundButton {
        id: roundButton1
        x: 304
        y: 409
        text: "+"
        onClicked:{
            video.pause();
        }
    }

    RoundButton {
        id: roundButton2
        x: 358
        y: 409
        text: "+"
        onClicked:{
            video.stop();
        }
    }

    Text {
            id: text1
            x: 0
            y: 409
            width: 46
            height: 16

            font.pixelSize: 12

            horizontalAlignment: Text.AlignRight
            text: {
                var m = Math.floor(video.position / 60000)
                var ms = (video.position / 1000 - m * 60).toFixed(1)
                return `${m}:${ms.padStart(4, 0)}`
            }
        }
}
