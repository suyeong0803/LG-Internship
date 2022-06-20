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

Dialog{
Popup{
   id: popup
   x: 400
   y: 250
   width: 300
   height: 200
   modal: true
   focus: true
   closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

   Button{
       id:checkButton
       text:"OK"
       onClicked:{
           popup.close();
       }
   }

//       onAccepted: console.log("Ok clicked")
//       onRejected: console.log("Cancel clicked")
}
}
