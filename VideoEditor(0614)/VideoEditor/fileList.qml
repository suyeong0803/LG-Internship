import QtQuick 2.0
import QtQuick.Controls.Windows 6.0
import QtQuick.Controls 6.2
import Qt.labs.platform 1.0
import QtMultimedia

window{
Component.onCompleted://view가 처음 실행될때 제일 처음으로 불려지는곳
    {
        listView.model.append({"list_text": "test text",
                                "list_button_text": "test button"})//listview에 선언한 임의의 모델 안에 데이터를 넣어준다.
        listView.model.append({"list_text": "test text",
                                "list_button_text": "test button"})
        listView.model.append({"list_text": "test text",
                                "list_button_text": "test button"})
        listView.model.append({"list_text": "test text",
                                "list_button_text": "test button"})

    }

    Component {//리스트 뷰의 틀을 만든다.
           id: contactDelegate
           Item {
               width: 800
               height: 100
               Text//리스트에 텍스트를 넣어주기 위해 텍스트 객체를 만들어준다.
               {
                   id:listView_Text
                   anchors.left: parent.left
                   anchors.leftMargin: 50
                   anchors.verticalCenter:  parent.verticalCenter
                   text:list_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
               }
               Button//리스트에 버튼을 넣어주기 위해 버튼 객체를 만들어준다.
               {
                   id:listView_Button
                   width:100
                   height:40
                   anchors.rightMargin: 30
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.right: parent.right
                   text: list_button_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
               }
               Rectangle//리스트의 구분선
               {
                   id:line
                   width:parent.width
                   anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                   height:1
                   color:"black"
               }

           }
       }
    ListView {
        id:listView
            anchors.fill: parent
            model: ListModel{}//임으로 만들 모델을 넣어준다.
            delegate: contactDelegate//delegate란 리스트 한개의 틀(틀을 하나 만들어서 그것들을 여러개 붙여놓은것이 리스트 뷰이다.)
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
}

}
