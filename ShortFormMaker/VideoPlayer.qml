import QtQuick 2.0
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform 1.0
import QtMultimedia


Rectangle {
        id: rectangle1
        width: 480
        height: 270
        color: "#565656"
        property alias rectangle1Width: rectangle1.width
        property alias videoPlayerPosition:video.position
        property alias video:video
        property alias videoListModel:model

        Video {
            id: video
            anchors.fill:parent
            source: "file:///D:/videosample/sample1.mp4"
//            source: "file:///c:/users/yeeun/desktop/VideoSample/VideoSample1/sample1.mp4"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
//            loops:1

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
            onPlaying:{
                console.log("playing")
                console.log("플레이중"+video.source)
                for(var i=0;i<model.count;i++){
                    if(i>0 && video.source.toString().toLowerCase()==model.get(i).source.toString().toLowerCase()){
                        video.pause();
                    }
                }

                console.log(video.duration)
            }
            onPaused:{
                console.log("paused")
            }
            onStopped:{
                console.log("stopped")
                console.log(video.position+" "+video.duration)
                if(video.position!=0 && video.position==video.duration){
                    for(var i=0;i<model.count;i++){
                        console.log(video.source.toString().toLowerCase()+" "+model.get(i).source.toString().toLowerCase())
                        if(model.get(i).source.toString().toLowerCase()===video.source.toString().toLowerCase()){
                            playVideo(i+1);
                            break;
                        }
                    }
                }

            }
        }

        function playVideo(index,flag){
            video.source=model.get(index).source;
            video.play();
        }

//    ListModel {//리스트뷰에 담은 데이터들을 선언한다.
//        id:model
//        ListElement{
//            source:"file:///c:/Users/yeeun/Desktop/VideoSample/videosample1/sample1.mp4"
//            startTime:0
//            endTime:125952
//        }
//        ListElement{
//            source:"file:///c:/Users/yeeun/Desktop/VideoSample/videosample1/sample2.mp4"
//            startTime:125952
//            endTime:156478
//        }
//        ListElement{
//            source:"file:///c:/Users/yeeun/Desktop/VideoSample/videosample1/sample3.mp4"
//            startTime:156478
//            endTime:208645
//        }
//    }

    ListModel{
        id:model
        ListElement{
            source:"file:///D:/videosample/sample1.mp4"
            startTime:0
            endTime:91258
        }
        ListElement{
            source:"file:///D:/videosample/sample2.mp4"
            startTime:91258
            endTime:182049
        }
        ListElement{
            source:"file:///D:/videosample/sample3.mp4"
            startTime:182049
            endTime:273841
        }
        ListElement{
            source:"file:///D:/videosample/sample4.mp4"
            startTime:273841
            endTime:365233
        }
    }

    Slider {
        id: slider
        x: 0
        y: 287
        width: 480
        height: 29
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
        x: 169
        y: 322
        text: "+"
        onClicked: {
            var index=0;
            for(var i=0;i<model.count;i++){
                if(video.source.toString().toLowerCase()==model.get(i).source.toString().toLowerCase()){
                    index=i;
                }
            }
            console.log(model.get(index).startTime)
            video.setPosition(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration()-model.get(index).startTime)
            video.play();
        }
    }

    RoundButton {
        id: roundButton1
        x: 224
        y: 322
        text: "+"
        onClicked:{
            video.pause();
        }
    }

    RoundButton {
        id: roundButton2
        x: 278
        y: 322
        text: "+"
        onClicked:{
            video.stop();
        }
    }


    Text {
            id: text1
            x: 0
            y: 316
            width: 46
            height: 16
            color: "#ffffff"

            font.pixelSize: 12

            horizontalAlignment: Text.AlignLeft

            text: {
               var m = Math.floor(video.position / 60000)
               var ms = (video.position / 1000 - m * 60).toFixed(1)
               return `${m}:${ms.padStart(4, 0)}`
            }

    }
}
