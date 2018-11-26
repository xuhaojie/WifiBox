//Import the declarative plugins
import QtQuick 2.11

//Implementation of the Button control.
Image {
    id: button
    //anchors.fill: parent
    property string normalImage: ""
    property string hoverImage: ""
    property string pressedImage: ""
    property int fontSize: 10
    property int borderWidth: 1
    property int borderRadius: 2
    scale: state === "Pressed" ? 0.96 : 1.0
    onEnabledChanged: state = ""
    signal clicked
    signal pressed
    signal released
    source : normalImage
    fillMode: Image.PreserveAspectFit

    //change the color of the button in differen button states
    states: [
        State {
            name: ""
            PropertyChanges {
                target: button
                source: normalImage
            }
        },
        State {
            name: "Hovering"
            PropertyChanges {
                target: button
                source: hoverImage.length > 1 ? hoverImage : normalImage
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: button
                source: pressedImage.length > 1 ? pressedImage : normalImage
            }
        }
    ]
/*
    //define transmission for the states
    transitions: [
        Transition {
            from: ""; to: "Hovering"
            ColorAnimation { duration: 200 }
        },
        Transition {
            from: "*"; to: "Pressed"
            ColorAnimation { duration: 10 }
        },
        Transition {
            from: "*"; to: ""
            ColorAnimation { duration: 10 }
        }
    ]
*/
    //Mouse area to react on click events
    MouseArea {
        hoverEnabled: true
        anchors.fill: button
        onEntered: { button.state='Hovering'}
        onExited: { button.state=''}
        onClicked: { button.clicked()}
        onPressed: {
            button.state="Pressed"
            button.pressed()
        }
        onReleased: {
            if (containsMouse)
              button.state="Hovering";
            else
              button.state="";
            button.released()

        }
    }
}
