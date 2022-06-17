import QtQuick
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform
import QtMultimedia 5.0
import Qt.labs.folderlistmodel
import QtQuick.Window

import ".."
//import ViewModel 1.0

Window {
    id: window
    width: 1000
    height: 750
    visible: true
    title: qsTr("ShortForm Maker")

//    signal qmlSignalListUpdate();

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
        x: 700
        y: 94
        width: 257
        height: 457
        color: "#cbcbcb"

        Text {
            id: inputInfo
            x: 15
            y: 16
            width: 156
            height: 152
            text: qsTr("Text")
            font.pixelSize: 12
            elide:Text.ElideRight
            Component.onCompleted://view가 처음 실행될때 제일 처음으로 불려지는곳
            {
                console.log(VideoEditorViewModel.getListSize()+"개");
                for(var i=0;i<VideoEditorViewModel.getListSize();i++){
                    listView.model.append({"list_name_text":VideoEditorViewModel.getListName(i),
                                          "list_duration_text":VideoEditorViewModel.getListDuration(i),
                                          "list_path_text":VideoEditorViewModel.getListPath(i)})
                }
            }

//            onQmlSignalListUpdate:{//시그널이 호출되면 실행하는 함수
//                    console.log("onQmlSignalListUpdate called")
//                    listView.model.clear();//리스트 초기화
//                    for(var i = 0; i < connectEvent.getListSize(); i++){//리스트 초기화 후 다시 넣어줌
//                        listVies.model.append({"list_name_text":VideoEditorViewModel.getListName(i),
//                                              "list_duration_text":VideoEditorViewModel.getListDuration(i),
//                                              "list_path_text":VideoEditorViewModel.getListPath(i)})
//                    }
//                }

//            Component {//리스트 뷰의 틀을 만든다.
//                id: contactDelegate
//                Item {
//                    width: 250
//                    height: 50
//                    Text//리스트에 텍스트를 넣어주기 위해 텍스트 객체를 만들어준다.
//                    {
//                        id:listView_Text
//                        anchors.left: parent.left
//                        anchors.leftMargin: 30
//                        anchors.verticalCenter:  parent.verticalCenter
//                        width:parent.width/3
//                        text:list_name_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
////                        elide:Text.elideRight
//                    }
//                    Text//리스트에 텍스트를 넣어주기 위해 텍스트 객체를 만들어준다.
//                    {
//                        id:listView_Text2
//                        anchors.left: parent.left
//                        anchors.leftMargin: 100
//                        anchors.verticalCenter:  parent.verticalCenter
//                        width:parent.width/3
//                        text:list_duration_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
////                        elide:Text.elideLeft

//                    }
//                    Text//리스트에 텍스트를 넣어주기 위해 텍스트 객체를 만들어준다.
//                    {
//                        id:listView_Text3
//                        anchors.left: parent.left
//                        anchors.leftMargin: 170
//                        anchors.verticalCenter:  parent.verticalCenter
//                        width:parent.width/3
//                        text:list_path_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
////                        elide:Text.elideRight
//                    }
//                    Rectangle//리스트의 구분선
//                    {
//                        id:line
//                        width:parent.width
//                        anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
//                        height:1
//                        color:"black"
//                    }

//                }
//            }
//        }

//        ListView {
//            id:listView
//            x: 15
//            y: 185
//            anchors.fill: parent
//            anchors.leftMargin: 4
//            anchors.topMargin: 163
//            anchors.rightMargin: 4
//            anchors.bottomMargin: 77
//            model: ListModel{}//임으로 만들 모델을 넣어준다.
//            delegate: contactDelegate//delegate란 리스트 한개의 틀(틀을 하나 만들어서 그것들을 여러개 붙여놓은것이 리스트 뷰이다.)
//            //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
//            //focus: true
//            headerPositioning: ListView.OverlayHeader
//                header: Item {
//                    height: 40
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    Row {
//                        anchors.fill: parent
//                        Text {
//                            horizontalAlignment: Text.AlignHCenter
//                            width: parent.width / 3
//                            text: qsTr("파일명")
//                        }
//                        Text {
//                            horizontalAlignment: Text.AlignHCenter
//                            width: parent.width / 3
//                            text: qsTr("파일 길이")
//                        }
//                        Text {
//                            horizontalAlignment: Text.AlignHCenter
//                            width: parent.width / 3
//                            text: qsTr("파일 경로")
//                        }
//                    }
//                }
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
                    console.log("\t",i,folderModel.get(i,"fileName"))
                    console.log("\t", i, folderModel.get(i, "fileURL"))
//                    video.source=folderModel.get(i,"fileURL")
//                    video.play();
                }
            }
        }
    }

    Connections{
        target:VideoEditorViewModel
        onInputInfoChanged:{
            inputInfo.text=VideoEditorViewModel.inputInfo()
            inputInfo.text=VideoEditorViewModel.fileInfo()
//            listView.model=VideoEditorViewModel.getListSize();

        }
        onRangeSliderChanged:{
            fromLabel.text=VideoEditorViewModel.fromRangeSlider();
            toLabel.text=VideoEditorViewModel.toRangeSlider();
        }
    }

    VideoPlayer{
        id:videoPlayer
        x: 35
        y: 94
    }

    RangeSlider {
        id: rangeSlider
        x: 199
        y: 593
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

    Text {
        id: text1
        x: 74
        y: 614
        text: "구간선택"
        font.pixelSize: 12
    }




}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
