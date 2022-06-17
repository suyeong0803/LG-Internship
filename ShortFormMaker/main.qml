import QtQuick
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform
import QtMultimedia 5.0
import Qt.labs.folderlistmodel
import QtQuick.Window
//import "VideoPlayer.qml"
import ".."
//import ViewModel 1.0
import QtQuick.Layouts 1.0

Window {
    id: window
    width: 1100
    height: 750
    visible: true
    color: "#272727"
    title: qsTr("ShortForm Maker")
    property alias rangeSlider:rangeSlider

    //    signal qmlSignalListUpdate();

    Rectangle {
        id: rectangle
        x: 570
        y: 434
        width: 496
        height: 183
        color: "#565656"

        Text {
            id: inputInfo
            x: 16
            y: 16
            width: 464
            height: 159
            color: "#ffffff"
            text: qsTr("Text")
            font.pixelSize: 12
            elide:Text.ElideRight

        }

    }



    FolderDialog{
        id: folderDialog
        currentFolder: ""
        folder:StandardPaths.standardLocations
        onFolderChanged:{
            console.log(folder);
            VideoEditorViewModel.setInputInfo(folder);
            folderModel.folder=folder;
            videoPlayer.video.pause();
        }


    }

    FolderListModel {
        id: folderModel
        /// Put here URL of folder with videos
        folder: "file:" + "/home/tro/Videos/"
        /// Put a list of file name filters
        nameFilters: ["*.mp4"]
        showDirs: false
        onStatusChanged: {
            if (folderModel.status == FolderListModel.Ready) {
                console.log('Folder Model Loaded')
                console.log("Folder list contains ", folderModel.count, "elements:")
                for (var i = 0; i < folderModel.count; ++i) {
//                    console.log("\t",i,folderModel.get(i,"fileName"))
//                    console.log("\t", i, folderModel.get(i, "fileURL"))
//                    videoPlayer.videoList.append({"source": folderModel.get(i,"fileUrl").toString(),"name":folderModel.get(i,"fileName")});
                }
            }
        }
    }

    function durationTime(duration){
        var m = Math.floor(duration / 60000)
        var ms = (duration / 1000 - m * 60).toFixed(1)
        return `${m}:${ms.padStart(4, 0)}`
    }

    function videoInfoList(list){
        console.log("실행")
        console.log("테스트: "+list)
        for(var i=0;i<list.size();i++){
            console.log(list[i].getVideoInfoName());
//            list[i].getVideoInfoName();
        }
    }

    function test(){
        console.log("Test")
    }

    Connections{
        target:VideoEditorViewModel
        function onInputInfoChanged(){
            inputInfo.text=VideoEditorViewModel.inputInfo()
//            inputInfo.text=VideoEditorViewModel.fileInfo()
            //            listView.model=VideoEditorViewModel.getListSize();
            test();
            videoInfoList(VideoEditorViewModel.fileInfo());
//            inputInfo.text=videoInfoList(VideoEditorViewModel.fileInfo());
        }
        function onRangeSliderChanged(){
            //            fromLabel.text=VideoEditorViewModel.fromRangeSlider();
            console.log("시간"+durationTime(VideoEditorViewModel.rangeSliderDuration()));
            toLabel.text=durationTime(VideoEditorViewModel.rangeSliderDuration());
        }

    }

    VideoPlayer{
        id:videoPlayer
        x: 50
        y: 50
        visible: true
        rotation: 0
    }

    RangeSlider {
        id: rangeSlider
        x: 41
        y: 462
        width: 471
        height: 127
        layer.mipmap: false
        topPadding: 0
        spacing: 0
        focusPolicy: Qt.ClickFocus
        transformOrigin: Item.Center
        scale: 1
        snapMode: RangeSlider.NoSnap
        first.value: 0


        first.onValueChanged: {
            console.log(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration()+" first value changed");
//            console.log(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration());
            //            video.position/video.duration
//            videoPlayer.videoPlayerPosition=rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration();
            var firstValue=rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration();
            videoPlayer.video.position=firstValue;
            console.log("first value position: "+videoPlayer.video.position);
            console.log("video duration: "+videoPlayer.video.duration)
            if(firstValue>videoPlayer.video.duration){
                for(var i=0;i<videoPlayer.videoListModel.count;i++){
                    if(videoPlayer.videoListModel.get(i).startTime<=firstValue && firstValue<videoPlayer.videoListModel.get(i).endTime){
                        videoPlayer.video.source=videoPlayer.videoListModel.get(i).source.toString().toLowerCase();
                        console.log(videoPlayer.video.source);
                        videoPlayer.video.play();
//                        videoPlayer.video.paused();
                        videoPlayer.video.position=firstValue-videoPlayer.videoListModel.get(i).startTime;
                    }
                }
            }

            //            video.play();
            //            videoPlayerPosition=rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration();
            //            video.setPosition(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration());
        }
        second.onValueChanged:{
            console.log(rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration()+" Second value changed");
            //            videoPlayer.videoPlayerPosition=rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration();
            videoPlayer.video.position=rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration();
            //            videoPlayer.videoPlayerPosition=rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration();
            //            sectionPlay(rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration());
        }

        function sectionPlay(secondValue){
            var secondPosition=secondValue;
            console.log(secondValue+" "+videoPlayer.video.position);
            //            videoPlayer.video.play();
            if(videoPlayer.video.seekable){
                console.log(videoPlayer.video.seek());
            }

            //            console.log(videoPlayer.video.seek(videoPlayer.video.position));
            //            console.log(secondValue+" "+videoPlayer.video.position);
            //            if(videoPlayer.video.seek()==secondPosition){
            //                videoPlayer.video.pause();
            //            }
        }



        Label {
            id: fromLabel
            x: 1
            y: 76
            width: 75
            height: 19
            color: "#ffffff"
            text: qsTr("0:00.0")
            styleColor: "#ffffff"

        }

        Label {
            id: toLabel
            x: 416
            y: 76
            width: 52
            height: 19
            color: "#ffffff"
            text: qsTr("")
            styleColor: "#ffffff"

        }
    }

    Text {
        id: text1
        x: 41
        y: 440
        color: "#ffffff"
        text: "구간선택"
        font.pixelSize: 12
        styleColor: "#ffffff"
    }

    VideoPlayer {
        id: videoPlayer1
        x: 570
        y: 50


    }


    RowLayout {
        x: 570
        y: 657
        width: 496
        height: 41

        Button {
            id: openButton
            text: qsTr("open")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 117
            onClicked:{
                folderDialog.open();
            }
        }

        Button {
            id: openButton1
            text: qsTr("excute")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 117
        }

        Button {
            id: openButton2
            text: qsTr("test")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 117
        }

        Button {
            id: openButton3
            text: qsTr("quit")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 117
        }
    }




}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}D{i:14}D{i:15}D{i:16}
}
##^##*/
