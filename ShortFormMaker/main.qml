import QtQuick
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
//import QtQuick.Controls.Styles
import QtQuick.Controls.Material
import Qt.labs.platform
import QtMultimedia 5.0
import Qt.labs.folderlistmodel
import QtQuick.Window
//import QtQuick.Dialogs
//import "VideoPlayer.qml"
import ".."
//import ViewModel 1.0
import QtQuick.Layouts 1.0
//QQuickStyle::setStyle("Material");
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
        id: outputInfoRectangle
        x: 599
        y: 542
        width: 481
        height: 178
        color: "#565656"

        ScrollView {
            id: outputInfoScrollView
            x: 0
            y: 0
            width: 478
            height: 178

            Text {
                id: outputInfo
                x: 16
                y: 16
                width: 446
                height: 154
                color: "#ffffff"
                text: qsTr("Output Info")
                font.pixelSize: 12
                elide:Text.ElideRight

            }
        }

    }



    FolderDialog{
        id: folderDialog
        currentFolder: ""
        folder:StandardPaths.standardLocations
        onFolderChanged:{
            console.log(folder);
            VideoEditorViewModel.open(folder);
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

    //    function videoInfoList(list){
    //        console.log("실행")
    //        console.log("테스트: "+list)
    //        for(var i=0;i<list.size();i++){
    //            console.log(list[i].getVideoInfoName());
    ////            list[i].getVideoInfoName();
    //        }
    //    }

    function test(){
        console.log("Test")
    }

    Button {
        id: excuteButton
        x: 152
        y: 16
        width: 117
        height: 43
        text: qsTr("excute")
        Layout.preferredHeight: 43
        Layout.preferredWidth: 117
        onClicked:{
            if(rangeSlider.second.value-rangeSlider.first.value==0){
                popupText.text="영상 길이가 너무 짧습니다."
                popup.open();
                return;
            }
            else if((rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration()-rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration())>300000){
                popupText.text="영상 길이는 5분을 초과할 수 없습니다."
                popup.open();
                return;
            }

            saveDialog.open();
            //            console.log(videoPlayer1.video.source);
            //            console.log(savejsonog.currentFile)
            //            VideoEditorViewModel.setExcuteInfo(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration(),rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration())
            //            videoPlayer1.video.source=saveDialog.currentFile
        }
    }

    Connections{
        target:VideoEditorViewModel
        function onInputInfoChanged(){
            inputInfo.text=VideoEditorViewModel.inputInfo()
            var list=VideoEditorViewModel.fileInfo2();
            console.log(list);

            for (var prop in list) {
                        console.log("Object item:", prop, "=", list[prop])
                    }
            console.log(list.length);
            for(var i=0;i<list.length;i++){
                console.log("리스튼데여"+i);
                console.log(list.get(i).startTime);
                videoPlayer.videoListModel.append({"source": "file:///D:/conver/output_convert"+i+".mp4","startTime":list.get(i).startTime,"endTime":list.get(i).endTime});
            }

            //            inputInfo.text=VideoEditorViewModel.fileInfo()
            //            listView.model=VideoEditorViewModel.getListSize();

//            test();
            //            videoInfoList(VideoEditorViewModel.fileInfo());
            //            inputInfo.text=videoInfoList(VideoEditorViewModel.fileInfo());
        }
        function onRangeSliderChanged(){
//                        fromLabel.text=VideoEditorViewModel.fromRangeSlider();
            console.log("시간"+durationTime(VideoEditorViewModel.rangeSliderDuration()));
            toLabel.text=durationTime(VideoEditorViewModel.rangeSliderDuration());
        }
        function onOutputInfoChanged(){
            console.log("output")
            outputInfo.text=VideoEditorViewModel.outputInfo()
        }

    }

    Button {
        id: quitButton
        x: 963
        y: 16
        width: 117
        height: 43
        text: qsTr("quit")
        Layout.preferredHeight: 43
        Layout.preferredWidth: 117
        onClicked:{
            popup.open();
        }
    }

    VideoPlayer{
        id:videoPlayer
        x: 20
        y: 80
        visible: true
        rotation: 0
    }

    Button {
        id: openButton
        x: 20
        y: 16
        width: 117
        height: 43
        text: qsTr("open")
        Layout.preferredHeight: 43
        Layout.preferredWidth: 117
        onClicked:{
            folderDialog.open();
        }
    }

    Rectangle {
        id: inputInfoRectangle
        x: 20
        y: 542
        width: 478
        height: 178
        color: "#565656"

        ScrollView {
            id: inputInfoScrollView
            x: 0
            y: 0
            width: 478
            height: 178

            Text {
                id: inputInfo
                x: 15
                y: 8
                width: 446
                height: 154
                color: "#ffffff"
                text: qsTr("Input Info")
                elide: Text.ElideRight
                font.pixelSize: 12
            }

        }
    }

    Rectangle {
        id: rectangle
        x: 537
        y: 360
        width: 27
        height: 25
        color: "#ffffff"
    }

    RangeSlider {
        id: rangeSlider
        x: 20
        y: 478
        width: 478
        height: 44
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
            var secondValue=rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration();
            videoPlayer.video.position=secondValue;
            console.log("second value position: "+videoPlayer.video.position);
            console.log("video duration: "+videoPlayer.video.duration)
            if(secondValue>videoPlayer.video.duration){
                for(var i=0;i<videoPlayer.videoListModel.count;i++){
                    if(videoPlayer.videoListModel.get(i).startTime<=secondValue && secondValue<videoPlayer.videoListModel.get(i).endTime){
                        videoPlayer.video.source=videoPlayer.videoListModel.get(i).source.toString().toLowerCase();
                        console.log(videoPlayer.video.source);
                        videoPlayer.video.play();
                        //                        videoPlayer.video.paused();
                        videoPlayer.video.position=secondValue-videoPlayer.videoListModel.get(i).startTime;
                    }
                }
            }
            //            videoPlayer.videoPlayerPosition=rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration();

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
            x: 8
            y: 34
            width: 75
            height: 19
            color: "#ffffff"
            text: qsTr("0:00.0")
            styleColor: "#ffffff"

        }

        Label {
            id: toLabel
            x: 405
            y: 33
            width: 52
            height: 19
            color: "#ffffff"
            text: qsTr("")
            styleColor: "#ffffff"

        }
    }

    Text {
        id: text1
        x: 20
        y: 456
        color: "#ffffff"
        text: "구간선택"
        font.pixelSize: 12
        styleColor: "#ffffff"
    }

    VideoPlayer {
        id: videoPlayer1
        x: 600
        y: 80


    }

    FileDialog {
        id: saveDialog
        title: "Save Dialog"
        //                folder:  "file:///"  //Here you can set your default folder
        currentFile: "file:///" //The name of the item that you want to save
        fileMode: FileDialog.SaveFile

        onFileChanged:{
            console.log(saveDialog.currentFile)
            VideoEditorViewModel.excute(rangeSlider.first.value*VideoEditorViewModel.rangeSliderDuration(),rangeSlider.second.value*VideoEditorViewModel.rangeSliderDuration(),saveDialog.currentFile)
            videoPlayer1.video.source=saveDialog.currentFile
        }

    }

    Popup{
        id: popup
        x: 400
        y: 250
        width: 300
        height: 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            id: popupText
            width: 280
            height: 100
            color: "black"
            text: qsTr("Input Info")
            elide: Text.ElideRight
            font.pixelSize: 12
        }

        Button{
            id:checkButton
            x:100
            y:130
            text:"OK"
            onClicked:{
                popup.close();
            }
        }
    }

    Image {
        id: image
        x: 524
        y: 353
        width: 53
        height: 44
        source: "file:///D:/github_0620/Shortform/ShortFormMaker/right-arrow.png"
        fillMode: Image.PreserveAspectFit
    }











}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
