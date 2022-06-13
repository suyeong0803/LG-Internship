import QtQuick
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform
import QtMultimedia 5.0
//import ViewModel 1.0

Window {
    id: window
    width: 1000
    height: 750
    visible: true
    title: qsTr("Hello World")

    Button {
        id: openButton
        x: 762
        y: 25
        width: 90
        height: 32
        text: qsTr("open")
        onClicked:{
            folderDialog.open();
        }
    }

    Rectangle {
        id: rectangle
        x: 34
        y: 95
        width: 189
        height: 187
        color: "#cbcbcb"

        Text {
            id: inputInfo
            x: 15
            y: 16
            width: 156
            height: 152
            text: qsTr("Text")
            font.pixelSize: 12
        }
    }

    FolderDialog{
        id: folderDialog
        currentFolder: ""
        folder:StandardPaths.standardLocations
        onFolderChanged:{
            console.log();
            console.log(folder);
            VideoEditorViewModel.setInputInfo(folder);
            //myModel.setInputInfo(folder);
            //            myModel.setInputInfo(folder);
        }

    }

    Connections{
        target:VideoEditorViewModel
        onInputInfoChanged:{
            inputInfo.text=VideoEditorViewModel.inputInfo()
        }
        onRangeSliderChanged:{
            fromLabel.text=VideoEditorViewModel.fromRangeSlider();
            toLabel.text=VideoEditorViewModel.toRangeSlider();
        }
    }

    Rectangle {
        id: rectangle1
        x: 34
        y: 309
        width: 189
        height: 187
        color: "#cbcbcb"
        Text {
            id: outputInfo
            x: 15
            y: 16
            width: 156
            height: 152
            text: qsTr("Text")
            font.pixelSize: 12
            wrapMode: Text.WrapAnywhere
        }
    }

    Rectangle {
        id: rectangle2
        x: 245
        y: 94
        width: 707
        height: 351
        color: "#cbcbcb"

        Video {
            id: video
            x: 0
            y: 0
            source: "file:///D:/00000002REC/0000000200000001STRDEC0.mpg"
            width: 716
            height: 351

            onPlaying:{
                console.log("플레이");
            }

            onPaused:{
                console.log("일시정지");
            }

            onStopped:{
                console.log("스탑");
            }

            MouseArea {
                anchors.fill: parent
                anchors.rightMargin: 8
                anchors.bottomMargin: 0
                onClicked: {
                    video.play()
                }

                RoundButton {
                    id: playButton
                    x: 278
                    y: 367
                    text: "+"
                    onClicked:{
                        video.play()
                    }
                }

                RoundButton {
                    id: pauseButton
                    x: 326
                    y: 367
                    text: "+"
                    onClicked:{
                        video.pause()
                    }
                }

                RoundButton {
                    id: stopButton
                    x: 373
                    y: 367
                    text: "+"
                    onClicked:{
                        video.stop()
                    }
                }
            }

            focus: true
            Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video.seek(video.position - 5000)
            Keys.onRightPressed: video.seek(video.position + 5000)
        }
    }

    RangeSlider {
        id: rangeSlider
        x: 199
        y: 556
        width: 758
        height: 58
        layer.mipmap: false
        topPadding: 0
        spacing: 0
        focusPolicy: Qt.ClickFocus
        transformOrigin: Item.Center
        scale: 1
        snapMode: RangeSlider.NoSnap
        first.value: 0
        second.value: 1

        Label {
            id: fromLabel
            x: 0
            y: 49
            width: 75
            height: 19
            text: qsTr("from time")
        }

        Label {
            id: toLabel
            x: 706
            y: 49
            width: 52
            height: 19
            text: qsTr("to time")
        }




    }




}
